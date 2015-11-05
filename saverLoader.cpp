#include "saverLoader.h"

using namespace std;
//File extension
const string SaverLoader::extension = ".map";
/**
 * Default Constructior
 * Name the fale unnamed.map
 */
SaverLoader::SaverLoader(){			//Initialize fileName to unnamed.map
    fileName = "";
    fileName.append("unnamed");
    fileName.append(SaverLoader::extension);
}
/**
 * Non-default Constructor
 * @param fn name of the file
 */
SaverLoader::SaverLoader(string fn){	// Initialize fileName to GivenName.map
    fileName = "";
    fileName.append(fn);				// Appends file name and extension
    fileName.append(SaverLoader::extension);
}
/**
 * Saves a given map into file
 */
void SaverLoader::save(Map& map){
    ofstream out(fileName.c_str());		//Opens or creates file
    saveMap(out, map);					// Save map info
    saveCountries(out, map);			//Save country list
    saveContinents(out, map);			//Save Continent list
    saveAdjencencies(out, map);			//Save connection between countries
    out.close();						//Close file
}
/**
 * gets the current date and time
 *
 * @returns date and time in format yyyy-mm-dd-hh:mm:ss
 */
char* SaverLoader::getTime(){
    time_t now = time(0);
    struct tm  tstruct;
    char* buf = new char(80);
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d-%x", &tstruct);

    return buf;
}
/**
 * Saves map information
 * @param out Stream with opened file
 * @param map map to be saved
 */
void SaverLoader::saveMap(ofstream& out, Map map){
    out << "[MAP]" << endl;
    out << "Last save: " << getTime() << endl;
    out << map.name << "\n\n";
}
/**
 * Saves countries
 * @param out Stream with opened file
 * @param map map whose countries will be saved
 */
void SaverLoader::saveCountries(ofstream& out, Map map){
    out << "[COUNTRIES]" << endl;
    out << map.numCountries << endl;
    for(int i = 0; i < map.numCountries; i++){			// For each country
        out << map.countries[i].id << "/" << map.countries[i].name // saves id/name/owner/troops
        << "/" << map.countries[i].owner << "/" << map.countries[i].troops << endl;
    }
    out << "\n";
}
/**
 * Saves Continent information
 * @param out Stream with opened file
 * @param map map whose continents will be saved
 */
void SaverLoader::saveContinents(ofstream& out, Map map){
    out << "[CONTINENTS]" << endl;
    out << map.numContinents << endl;
    for(int i = 0; i < map.numContinents; i++){	// for each continent in the map
        out << map.continents[i].name << "/" << map.continents[i].numCountries << endl; // Continent info
        for (int j = 0; j < map.continents[i].numCountries; j++){	// Each country inside continent
            out << map.continents[i].countries[j]  << endl;			// save country id
        }

    }
    out << "\n";
}
/**
 * Saves connections between countries
 * @param out Stream with opened file
 * @param map map with adjencecies
 */
void SaverLoader::saveAdjencencies(ofstream& out, Map map){
    out << "[ADJENCENCIES]" << endl;
    for (int i = 0; i < map.numCountries; i++)		// x axis of the
    {
        out << map.countries[i].id << "\t" << map.countries[i].name << endl;	// current country info
        for (int j = 0; j < map.numCountries; j++)		// y axis
        {
            out << map.adjencecies[i][j] << "\t";		// save true or false connection
        }
        out << "\n\n";
    }
}
/**
 * loads a map
 * @return pointer to loaded map
 */
Map* SaverLoader::load(){
	ifstream in(fileName.c_str());		//opens file for reading
	Map *map = new Map;					// new map object
	loadMap(in, map);					// load map info
	loadCountries(in, map);				// load countries
	loadContinents(in, map);			// load continents
	loadAdjacencies(in, map);			// load adjencencies
	in.close();							// close file
	return map;							// return pointer
}
/**
 * loads a map info
 * @param in input stream with opened file
 * @param map map being created
 */
void SaverLoader::loadMap(ifstream& in, Map* map){
	char s[256];
	in.getline(s, 256, '\n');
	in.getline(s, 256, '\n');
	in.getline(s, 256, '\n');		//Skips first file related lines
	map->name = s;					// saves map name
	in.getline(s, 256, '\n');
	return;
}
/**
 * loads countries
 * @param in input stream with opened file
 * @param map map being created
 */
void SaverLoader::loadCountries(ifstream& in, Map* map){
	char s[256];
	in.getline(s, 256, '\n');
	in.getline(s, 256, '\n');		// skips file readability lines

	int numCountries;
	numCountries = atoi(s);			// reads number of countries and parses it to integer
	Country* countries = new Country[numCountries];	// Creates new array of countries
	for(int i = 0; i < numCountries; i++){			// for each country
		in.getline(s, 256, '/');
		countries[i].id = atoi(s);					// Read id
		in.getline(s, 256, '/');
		countries[i].name = s;						// Read name
		in.getline(s, 256, '/');
		countries[i].owner = atoi(s);;				// read owner id
		in.getline(s, 256, '\n');
		countries[i].troops= atoi(s);				// read number of troops
	};
	in.getline(s, 256, '\n');
	map->numCountries = numCountries;				// number of countries in map
	map->countries = countries;						// puts countries array in map
}
/**
 * loads continents
 * @param in input stream with opened file
 * @param map map being created
 */
void SaverLoader::loadContinents(ifstream& in, Map* map){
	char s[256];
	in.getline(s, 256, '\n');			// ski'file redability line
	in.getline(s, 256, '\n');
	int numContinents;
	numContinents = atoi(s);			// reads number of continents
	cout << numContinents << endl;
	map->numContinents=numContinents;
	Continent* continents = new Continent[numContinents];		// creates array of continents
	for(int i = 0; i < numContinents; i++){						// for each continent in the file
		in.getline(s, 256, '/');
		continents[i].name = s;									// read name
		in.getline(s, 256, '\n');
		continents[i].numCountries = atoi(s);;					// number of countries in continent
		continents[i].countries = new int[continents[i].numCountries];
		for(int j =0; j < continents[i].numCountries; j++){		// for each country in that continent
			in.getline(s, 256, '\n');
			continents[i].countries[j]= atoi(s);				// read country id
		}
	}
	map->continents = continents;								// puts array of continents in map
}
/**
 * loads adjencency matrix
 * @param in input stream with opened file
 * @param map map being created
 */
void SaverLoader::loadAdjacencies(ifstream& in, Map* map){
	map->adjencecies = new bool*[map->numCountries];
	char s[256];
	in.getline(s, 256, '\n');
	for(int i = 0; i < map->numCountries; i++){			// for each country in map
		map->adjencecies[i] = new bool[map->numCountries];		// array of connected countries
		in.getline(s, 256, '\n');
		for(int j = 0; j < map->numCountries; j++){
			int adj;
			in.getline(s, 256, '\t');
			adj= atoi(s);;								// read true connection(1) or not connected (0)
			if(adj){
				map->adjencecies[i][j] = true;
			}else{
				map->adjencecies[i][j] = false;
			}
		}
		in.getline(s, 256, '\n');
	}
}




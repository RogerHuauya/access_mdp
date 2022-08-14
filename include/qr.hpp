#include <string>
#include <vector>
extern std::string password_key;
extern std::vector<std::string> hash_arr, dni_arr, name_arr;
bool qrDetector(float active_time);
void readAuthFile();
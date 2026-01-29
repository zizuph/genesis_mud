inherit "/std/object";

#include "/d/Shire/guild/smiths/smiths.h"

string get_forge_count(string name)
{
    string result = "Forge information for " + name + ":\n\n";
    
    setuid();
    seteuid(getuid());
    mapping data = restore_map(SMITHS_MASTER_LOG);
    foreach(string type, mapping info : data["SM_ForgedItems"]) {
        result += sprintf("%30s: %i items\n", type, info[capitalize(name)]);
    }
    
    return result;
}

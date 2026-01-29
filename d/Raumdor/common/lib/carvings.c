#include "defs.h"

string
carvings_description()
{
    int skill = TP->query_skill(SS_SPELLCRAFT);
    string result = "The carvings are runic span the entire wall, though " +
        "they blend in with the texture of the stone. "; 
    if (skill < 20)
        result += "Perhaps they are just decorative.";
    else if (skill < 40)
        result += "They look like magical glyphs of some kind.";
    else
        result += "They look like magical glyphs to ward off the undead.";

    return result + "\n";
}

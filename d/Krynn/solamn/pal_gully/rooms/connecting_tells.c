#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
string
get_tells()
{
    string cavtell;
    cavtell = one_of_list(({"An aghar dwarf runs past "
    +"being chased by an angry dewar dwarf.",
    "A dewar dwarf rushes past carrying an aghar prisoner.",
    "An aghar dwarf yells 'Me no like you' and "
    +"throws a petrified rat at a dewar before running off.",
    "A dewar dwarf runs past shouting 'I'm going to kill you "
    +"all'.", "A dewar dwarf runs past flailing his "
    +"axe in the air.", "An aghar dwarf runs past holding "
    +"his petrified rat in the air.",
    "Two dewar dwarves run past you, their hands bloody "
    +"from combat.", "Shouting erupts and then is suddenly cut short."}));
    return cavtell;
}
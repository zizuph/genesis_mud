#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
string
get_tells()
{
    string cavtell;
    cavtell = one_of_list(({"An aghar dwarf runs past "
    +"being chased by an angry dewar dwarf.",
    "A bloodied aghar dwarf is dragged of by a "
    +"group of dewar dwarves.",
    "A dewar dwarf rushes past carrying an "
    +"aghar prisoner.",
    "An aghar dwarf yells 'Me no like you' and "
    +"throws a petrified rat at a dewar.",
    "A dewar dwarf shouts 'I'm going to kill you "
    +"all' before thrusting his axe into "
    +"an aghar dwarf and carrying him off.", "A dewar "
    +"dwarf runs past flailing his "
    +"axe in the air.", "An aghar dwarf runs past holding "
    +"his petrified rat in the air.",
    "Two dewar dwarves walk past you, their hands bloody "
    +"from combat.", "Shouting erupts "
    +"and then is suddenly cut short."}));
    return cavtell;
}
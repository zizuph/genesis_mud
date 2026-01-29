#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
string
get_tells()
{
    string cavtell;
    cavtell = one_of_list(({"The lanterns flicker on the wall.",
      "Giggling can be heard echoing through the mine.",
      "An aghar dwarf runs past you, arms flailing.",
      "A crashing noise can be heard in the distance.",
      "An aghar dwarf skips past you carrying a dead lizard.",
      "Two aghar dwarves walk past you holding hands and singing.",
      "An aghar dwarf runs past you shouting 'Highbulp!'"}));
    return cavtell;
}
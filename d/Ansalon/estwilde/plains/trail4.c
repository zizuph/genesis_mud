#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit PLAINS_OUT;

void
reset_estwilde_room()
{
    return;
}

create_estwilde_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"goat trail","trail"}),
      "You find yourself walking along a faint "+
      "goat trail that climbs up the side of a "+
      "steep hill. So far, you've noticed no goats, "+
      "which is probably a good thing.\n");
    add_item(({"hardy grass","grass"}),
      "Hardy grass grows up along the side of the hill, "+
      "swaying slightly in the wind.\n");
    add_item(({"thorny bushes","bushes"}),
      "Thorny bushes grow all over the hill, making "+
      "travel rather painful to the hasty adventurer.\n");
    add_item(({"hill","steep hill"}),
      "The side of steep hill looms up before you.\n");

    add_exit(ROOM + "trail3","down","@@climb_down");
    add_exit(ROOM + "trail5","southeast","@@follow_trail");

    reset_estwilde_room();
}

int
climb_down()
{
    write("You carefully make your way down a steep "+
      "section of the hill...\n");
    return 0;
}

int
follow_trail()
{
    write("You push your way past some thorny bushes "+
      "as you make your way up the steep hill...\n");
    return 0;
}

string
short_descr()
{
    return "On a goat trail near the top of "+
    "a steep hill";
}

string
long_descr()
{
    return "You stand on a goat trail that climbs up "+
    "the side of a steep hill overlooking "+
    "the plains of Estwilde. Hardy grasses and thorny "+
    "bushes grow around you and across the path, making "+
    "travel frustrating, if not difficult. "+
    "\n";
}

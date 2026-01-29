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
      "You stand near the top of a steep hill. At the top "+
      "you notice a stone structure of some kind stands " +
      "alone, overlooking the plains beneath you.\n");
    add_item(({"structure","stone structure"}),
      "You can't make out many details about the stone "+
      "structure from here, but you think you can get "+
      "closer by following the trail to your southwest.\n");

    add_exit(ROOM + "trail4","northwest","@@follow_trail");
    add_exit(ROOM + "cairn_entry","southwest","@@follow_trail");

    reset_estwilde_room();
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

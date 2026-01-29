#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit BLOODSEA_OUT;

void
reset_bloodsea_room()
{
    return;
}

create_bloodsea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"cliff", "steep cliffs", "cliffs"}),
               "Steep cliffs rise high above you out of the waters of Horned Bay. " +
               "Dark and menacing, the cliffs seem unscalable from here.\n");
    add_item(({"bay","horned bay","bloodsea","blood sea"}), "The Horned Bay "+
               "stretches itself towards the northwest where it meets the Bloodsea.\n");
    add_item(({"water", "sea"}), "The water within the Bloodsea has "+
               "a strange and reddish colour. Rumour has it that the colour "+
               "is the result of the blood of many victims who lost their "+
               "lives during Krynn's most terrible hour, though it "+
               "could be the clay stirred up from the sea bottom by the "+
               "maelstrom.\n");
    add_item(({"village", "nethosak"}), "You can make out the "+
             "city of Nethosak, home of the minotaurs of Ansalon, far to the "+
             "east.\n");

    add_row_exit(BROOM + "5h", "west", 0, 1);
    add_row_exit(BROOM + "3h", "east", 0, 1);
    add_row_exit(BROOM + "4g", "south", 0, 1);
    add_row_exit(BROOM + "5i", "northwest", 0, 1);


    add_cmd_item(({"cliff","cliffs","steep cliffs"}),
      ({"climb", "scale"}),"@@climb_cliff");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_bloodsea_room();

}

string
climb_cliff()
{
    write("The cliffs are too steep to climb here.\n");
    say(QCTNAME(TP) + " tries to climb the cliffs here, but they are too steep.\n");
    return "";
}

void
set_sink_path(string sp)
{
    sink_path = "/d/Ansalon/balifor/flotsam/room/bottom_of_bay";
}

string
short_descr()
{
    return "The edge of Horned Bay against steep cliffs";
}
 
string
long_descr()
{
    return "You are against the steep cliffs that form the boundaries " +
       "of Horned Bay. " +bloodsea_desc()+
    "\n";
}
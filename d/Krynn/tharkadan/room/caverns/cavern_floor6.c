#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Krynn/common/clock/clock.h"

inherit CAVERNS_BASE;

void
reset_tharkadan_room()
{
    return;
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(CAVERNS + "cavern_floor7","northeast","@@check_slip");
    add_exit(CAVERNS + "cavern_floor3","north","@@check_slip");
    add_exit(CAVERNS + "cavern_floor5","northwest","@@check_slip");

    add_prop(ROOM_S_DARK_LONG, "A dark, cold cavern. Without a light " +
          "source it is too dark to see in here.\n"); 
    add_prop(ROOM_S_DARK_MSG, "The cavern is too dark to"); 
    add_prop(ROOM_I_LIGHT, DARKNESS_PASSIVE);

    add_item(({"cold cavern","cavern","throat","floor","icy floor"}),
        "You stand on the icy floor of a great cavern within the throat " +
        "of the ancient volcano you stand within. It is quite " +
        "slippery... if you are not careful you think it likely to lose " +
        "your footing.\n");
    add_item(({"ice","basalt","sheet of ice","sheet"}), "The floor of " +
        "the cavern is a thick sheet of ice and basalt, accumulated " +
        "over ages and blocking the throat of the volcano.\n");
    add_item(({"volcano","ancient volcano"}),
        "You stand within the throat of what was once an ancient " +
        "volcano, long dormant. Over time its great vent above you " +
        "filled with ice and fell in on itself, creating the great " +
        "cavern you now stand within.\n");
    reset_tharkadan_room();
}

string
short_descr()
{
    return "on the icy floor of a dark, cold cavern";
}

string
long_descr()
{
    return "You stand on the floor of the cavern, a thick sheet of " +
        "slippery ice and basalt that now blocks the throat of the " +
        "ancient volcano you stand within. \n";
}

int
check_slip()
{
   if(random(TP->query_stat(SS_DEX)) < random(200))
   {
      write("You slip on the icy floor of the cavern!\n");
      say(QCTNAME(TP) + " slips on the icy floor of the cavern!\n");
      return 1;
   }

   return 0;
}
#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit CAVERNS_BASE;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"cave",}));

void
reset_tharkadan_room()
{
    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(CAVERNS + "upper_mines1","northeast","@@enter_mines");
    add_exit(CAVERNS + "lava_vent5","south",0);

    add_prop(ROOM_S_DARK_LONG, "An ancient lava vent. Without a light " +
          "source it is too dark to see in here.\n"); 
    add_prop(ROOM_S_DARK_MSG, "It is too dark to"); 
    add_prop(ROOM_I_LIGHT, DARKNESS_PASSIVE);

    add_item(({"volcano","dormant volcano","vent","lava vent"}),
        "You stand within a lava vent of what was once an ancient " +
        "volcano, long dormant. Now it makes a large natural tunnel " +
        "leading deep underground.\n");
    add_item(({"tunnel","excavated tunnel"}), "To your northeast the " +
        "natural lava vent transitions to a tunnel clearly " +
        "excavated by skilled subterranean miners.\n");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "vent","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "an ancient lava vent, deep within a dormant volcano";
}

string
long_descr()
{
    return "You stand within an ancient lava vent that leads down into " +
        "the depths of a dormant volcano. To your south the vent leads " +
        "upwards while to your northeast the vent transitions from a " +
        "natural tunnel to one excavated by hand.\n";
}

int
enter_mines()
{
   write("You step out of the naturally formed lava vent into a tunnel " +
       "clearly excavated by skilled subterranean miners.\n");
   return 0;
}

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit POOLBOTTOM_IN;

void
reset_poolbottom_room()
{
	return;
}

create_poolbottom_room()
{
    set_short("spartan residential quarters of the school of High Magic");
    set_long("You stand in the spartan residential quarters within the eastern wing of " +
        "the school of High Magic. Lines of low wooden beds with thin sheets fill the room, " +
        "however there is little else that occupies this sparse room. " +
        "Clearly the Master of the school feels simple living conditions is conducive to " +
        "student learning!\nStudents of the school may <start here>.\n"); 

    add_item(({"low wooden beds","wooden beds","beds","bed","sheets","thin sheets","sheet"}),
        "Students who board at the school are required to sleep on hard beds, with only " +
        "a thin sheet to keep them warm. Certainly nothing that could be mistaken for a " +
        "creature comfort!\n");

    add_item(({"walls","sandstone walls","grey sandstone walls","high sandstone walls",
               "blocks","sandstone blocks","grey sandstone blocks"}),
       "The school has been build from grey sandstone blocks mined from quarries " +
       "far to the south near Pax Tharkas. The workmanship of the walls is seamless, " +
       "most likely done by a master dwarven mason.\n");

    add_exit(ROOM + "room","south",0);

    add_cmd_item("here", "start", "@@do_start");

    reset_poolbottom_room();
}

int
do_start()
{
   if(this_player()->query_guild_name_occ() != GUILD_NAME) 
   {
      notify_fail("Only students of High Magic can board at the school.\n");
      return 0;
   }
   TP->set_default_start_location(SOHM_STARTROOM);
   write("You are now a boarder at the school, and start here when you enter the realms.\n");
   return 1;
}
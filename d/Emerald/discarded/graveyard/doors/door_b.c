inherit "/std/door";
 
#include "/d/Emerald/defs.h"
 
void
create_door()
{
    set_door_id("gravestone");
    set_pass_command(({"u","up"}));
    set_door_name(({ "gravestone", "tombstone", "stone", "tomb" }));
    set_open_desc("Above you, there is an opening allowing you to go up.\n");
    set_closed_desc("Above you there seems to be an opening blocked by a stone.\n");
    set_door_desc("Is is a rather heavey-looking stone.\n");
    set_open_command("push");
    set_close_command("pull");
    set_open_mess( ({ "moves the stone, revealing an opening.\n",
		      "The gravestone moves to one side, revealing an opening!\n" }) );
    set_close_mess( ({ "moves the stone, covering the exit.\n",
		       "The gravestone moves, covering the opening!\n" }) );
    set_other_room( GRAVEYARD_DIR + "graveyard3");
    set_open(0);
}

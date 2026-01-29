/* temple/doors/trapdoor_b.c is cloned by temple/tunnel1.c */
inherit "/std/door";
 
#include "/d/Emerald/defs.h"
 
void create_door()
{
    ::create_door();
    set_door_id("trapdoor");
    set_pass_command(({"u", "up"}));
    set_door_name(({"hidden trapdoor", "trapdoor", "door"}));
    set_open_mess( ({ "opens the trapdoor.\n",
		      "The altar is tipped against the wall, revealing an opening.\n" }) );
    set_close_mess( ({ "closes the trapdoor.\n",
		       "The altar falls back to the floor, covering the opening.\n" }) );
    set_other_room(TEMPLE_DIR + "hall");
    set_open(0);
}

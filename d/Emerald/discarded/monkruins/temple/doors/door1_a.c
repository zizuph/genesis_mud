/* temple/doors/door1_a.c is cloned by temple/path4.c */
inherit "/std/door";

#include "/d/Emerald/defs.h"

void create_door()
{

    /* set_short("A large golden door"); */
    set_door_desc("   Before you is a large golden door. As you examine "+
      "it closer, you notice that there doesn't seem to be a knob "+
      "or door handle. There doesn't seem to be a visible key hole or any "+
      "other indication of a door lock either. You wonder how the door can "+
      "be sealed so tightly without a lock!\n\n");
    set_door_name( ({"door", "large door", "large golden door",
	"golden door"}) );
    set_door_id("templedoor");
    set_pass_command(({"e", "east"}));
    set_fail_pass("But the door is closed!\n");
    set_no_pick();
    set_locked(1);
    set_open(0);
    set_key(66602);
    set_other_room(TEMPLE_DIR + "entrance");
}

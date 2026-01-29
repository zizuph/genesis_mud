/* towncastle/doors/drawbridge_a.c is cloned by towncastle/entrance.c  */
inherit "/std/door";
 
#include "../default.h"
 
create_door()
{
    set_door_id("drawbridge");
    set_pass_command(({"n","north"}));
    set_door_name(({"heavy drawbridge","drawbridge","bridge"}));
    set_door_desc("It it an old, battered drawbridge.\n");
    set_open_desc("The drawbridge is down, allowing you to go north leaving the castle.\n");
    set_closed_desc("The drawbridge is up.\n");
    set_fail_pass("You start to climb the drawbridge, but must turn around "+
		  "at the top.\n");
    set_open_mess( ({ "turns a wheel, lowering the drawbridge.\n",
		      "The drawbridge is lowered with a screetching noise.\n" }) );
    set_close_mess( ({ "turns a wheel, raising the drawbridge.\n",
		       "The drawbridge is raised with a screetching noise.\n" }) );
    set_other_room(TCASTLE_DIR + "outside");
    set_open_command( ({ "lower" }) );
    set_close_command( ({ "raise" }) );
    set_open(1);
}

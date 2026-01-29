/* towncastle/doors/drawbridge_b.c is cloned by towncastle/outside.c */
inherit "/std/door";
 
#include "../default.h"
 
create_door()
{
    set_door_id("drawbridge");
    set_pass_command(({"s","south"}));
    set_door_name(({"heavy drawbridge","drawbridge","bridge"}));
    set_door_desc("It it an old, battered drawbridge.\n");
    set_open_desc("The drawbridge is down, allowing you to go south into the castle.\n");
    set_closed_desc("The drawbridge is up.\n");
    set_fail_pass("You start wading into the moat, but change your mind.\n");
    set_other_room(TCASTLE_DIR + "entrance");
    set_open_command( ({}) );
    set_close_command( ({}) );
    set_open(1);
}

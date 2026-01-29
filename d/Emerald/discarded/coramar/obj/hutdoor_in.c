/*
 * HUTDOOR_OUT.c
 * Door, outside Thanduin's hut
 * Alaron - Feb 1998
 */

#include "/d/Emerald/defs.h"
#include "../coramar.h"
#include "../dirheader.h"

inherit "/std/door";


void
create_door()
{
    set_door_name( ({"wooden door", "door",
	"small door"}) );
    set_door_id("_coramar_thanduin_hut_doors_");
    set_pass_command( ({"w", "west", "outside","leave","exit","out" }) );
    set_other_room(CORAMAR+"f70");
    
    set_lock_command("_you_will_never_be_able_to_lock_this_door_");
    set_open(0);

    set_knock_command( ({"knock", "hammer", "pound", "bang", "slam"}) );

    add_prop(DOOR_I_HEIGHT, 220);
}


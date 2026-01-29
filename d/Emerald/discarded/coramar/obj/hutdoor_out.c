/*
 * HUTDOOR_OUT.c
 * Door, outside Thanduin's hut
 * Alaron - Feb 1998
 */

#include "/d/Emerald/defs.h"
#include "../coramar.h"
#include "../dirheader.h"

inherit "/std/door";

void say_its_open();

void
create_door()
{
    set_door_name( ({"moss-covered door", "door",
	"small door"}) );
    set_door_id("_coramar_thanduin_hut_doors_");
    set_pass_command( ({"e", "east", "inside" }) );
    set_other_room(CORAMAR+"hut");
    
    set_lock_command("_you_will_never_be_able_to_lock_this_door_");
    set_open(0);

    set_knock_command( ({"knock", "hammer", "pound", "bang", "slam"}) );

    add_prop(DOOR_I_HEIGHT, 220);
}

int
knock_door(string str)
{
    if (!(::knock_door(str)))
	return 0;

    if (query_open()) return 0;

    if (present("thanduin", find_object(CORAMAR+"hut")))

    {
       set_alarm(3.0, 0.0, say_its_open);
       return 1;
    }
    return 1;
}

void
say_its_open()
{
     tell_room(environment(),"A muffled voice complains from the other side of "+
	"the door, \"Yes, yes, the door is unlocked! Come in and stop knocking before "+
	"you wake the dead!\"");
}

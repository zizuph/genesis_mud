// file name:        /d/Avenir/common/bazaar/admin/a8.c
// creator(s):       Lilith, Sept 97
// revisions:
// purpose:
// note:
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/bazaar/admin/admin_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/bazaar/admin/admin.h"

//not using smis for this placement. 
static object gate;
int alarm_id;
int close_the_gate();
void reset_admin_room() {    close_the_gate();    }

/* Now create the room.  */
void
create_admin_room()
{
    set_short("East of the fountain, outside the gate");
    set_long("A gate arches here, its beautiful dark wood gleaming "+
        "richly in the light of the Source. The trefoil fountain "+
        "shimmers under its sheet of water directly west, and "+
        "beyond it lies the Questioning Place. South and west is "+
        "the red-gold Tribunal building. ");

    add_outside();

    add_exit(BAZ_ADMIN +"a6", "north",  0);
    add_exit(BAZ_ADMIN +"a11", "south", 0);
    add_exit(BAZ_ADMIN +"fount", "west", 0);
   
    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"a5",  "northwest",  0, 1, 1);    
    add_exit(BAZ_ADMIN +"a10", "southwest",  0, 1, 1);       

    /* Place the third Gate */
    gate = clone_object(BAZAAR + "Obj/door/third_gate.c");
    gate->move(TO);  
    set_dircmd("east");  

    reset_admin_room();
}

int 
gate_check()
{
    write("The gates are closed. You cannot pass.\n");
    say(QCTNAME(TP) +" tries to go through the gates, but fails.\n");
    return 1;
}

int 
close_the_gate()
{
    object other_door;

    if (gate->query_open())
    {
        gate->do_close_door("");
        other_door = gate->query_other_door();
        other_door->do_close_door("The Third Gate swings closed.\n");
        gate->do_lock_door("The lock on the gate clicks as it closes.\n");
        other_door->do_lock_door("The lock on the gate clicks faintly.\n");
    }
    if(!gate->query_locked())
    {
        gate->do_lock_door("Click.");
        other_door->do_lock_door("Click.");
    }

    alarm_id = 0;
    return 1;
}


void
leave_inv(object to, object from)
{
    if (!alarm_id)
    alarm_id = set_alarm(20.0, 0.0, &close_the_gate());

    ::leave_inv(to,from);
}


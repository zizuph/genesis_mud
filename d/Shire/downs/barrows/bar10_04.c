/* End cave of a barrow
 * Based on Dondon's downs
 * -- Finwe, December 2001
 */

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>


inherit BAR_BASE;

int alarm_id;
int handle_status,  // status of handle 0 = it's not moved, 1 = moved 
    handle_pulled,  // number of times handle moved with wights in room
    exit_status;    // exit open or closed. 0 = closed, 1 = open
/*
void handle_moved();
*/
void
create_barrow_room()
{
    set_short("A dark passage inside a barrow");
    set_long("You stand in a large, circular cavern made of stone. " +
        "Some rotting corpses lay in a corner of the cavern, " +
        "unfortunate travellers lulled here by a wight. A feeling " +
        "of death permeates the room. There is a handle is " +
        "attached to the wall.\n");

    add_item(({"piles of dirt", "piles of earth", "clods of dirt", 
            "clods of earth", "dirt", "earth"}),
        "The piles of dirt are dark and lay in various sized " +
        "piles about the room. They have a rich, loamy look to them.\n");
    add_item(({"corpses", "rotting corpses", "skeletons"}),
        "They are travellers that were lured or fell into the " +
        "barrows who knows how long ang. Little remains of them " +
        "other than some rotting flesh and bones.\n");
    add_item(({"rotting flesh"}),
        "The rotting flesh partially covers the corpses, " +
        "revealing nothing more than bones.\n");
    add_item("bones",
        "The bones are grey colored with some teeth marks, " +
        "probably from rodents that have been chewing on them. " +
        "The bones poke out from the rotting flesh.\n");
    add_item(({"handle", "lever"}),"The handle is smooth yet " +
        "shows signs of rust. It has obviously has not been used " +
        "for a long time.\n");

    add_prop(ROOM_I_LIGHT, 0);    
    reset_shire_room();

    add_exit(BAR_DIR + "bar10_03", "west","@@check_exit@@");
    add_exit(BAR_DIR + "bar10_out", "down","@@check_handle@@");

}

init() {
    ::init();
    add_action("handle", "move");
    add_action("handle", "use");
    add_action("handle", "push");
    add_action("handle", "pull");
}


void reset_shire_room()
{
    handle_status = 0;  // handle reset to closed
    handle_pulled = 0;  // handle not pulled
    exit_status = 0;    // exit closed
    make_black_wight();
}

/* Have to kill the wight or fool him (sneak, hide, or be invis) to go back south*/
/*
int check_exit() 
{
    if (!present ("wight"))
    {
        return 0;
    }
    else if (TP->query_skill(SS_SNEAK) > 30)
    {
        write(" You manage to sneak past the wight.\n");
        say(QCTNAME(TP)+" managed to sneak past the wight.\n");
        return 0;
    }
    else if (TP->query_skill(SS_HIDE) > 40)
    {
        write ("You manage to hide from the wight and escape.\n");
        say (QCTNAME(TP)+" hides and escapes the Wight's attention.\n");
        return 0;
    }

    write ("Wight rasps: Nothing leaves here alive...\n");
    say ("Wight bars " + QCTNAME(TP) + " from leaving.\n");
    return 1;
}

int check_handle()
{
    if (exit_status==1)
    {
        write("You fall through a hole in the ground.\n\n");
        return 0;
    }

    write("There is no way to go there from here.\n");
    return 1;
}


int handle(string str)
{
    if (str == "handle" || str == "lever")
    {
        if (handle_status == 0) // handle not moved
        {            
            if (!present("wight"))
            {
            // Be strong, or teamed up with a strong guy 
                if (TP->query_stat(SS_STR) < 40) 
                {            
                    write("The handle moves a little.\n");
                    return 1;
                }
                handle_status=1; // handle moved
                exit_status=1;
                handle_moved();
                return 1;
            }
            // nope, not strong enough or wight in room when handle moved.
            if (handle_pulled!=3)
            {
                write("The wight rasps: NOOOoooooo....\n"+ 
                    "The wight raises his voice to an urgent scream.\n");
                say("The wight stops " + QCTNAME(TP) + " from moving " +
                    "the handle.\n" + 
                    "The wight raises his voice in a terrifying scream.\n");
                write("The wight touches the handle, freezing it in place.\n");
                alarm_id = set_alarm(3.0,0.0,"get_a_wight");
                return 1;
            }
            else
            {   
                write("The wight rasps: You shall never get free...\n");
                write("The handle moves slightly, but remains in place.\n");
                return 1;
            }
        }
        write("The handle has already been moved, opening up an exit.\n");
        return 1; 
    }
}

void handle_moved() 
{
    write ( "You push and pull and drag....\n" +
        "Slowly, with a squeaking sound the handle moves. The " +
        "floor begins to crumble beneath your feet and a gaping " +
        "hole appears.\n");
    say ( QCTNAME(TP)+" pushes and pulls at the handle.\n" +
        "Slowly, with a squeaking sound the handle moves. The " +
        "floor beneath your feet begins to crumble away and a " +
        "gaping hole appears.\n");
    exit_status = 1;
}

get_a_wight() 
{
    object wight;

    if (handle_pulled!=3)
    {   // only 3 per reset
        // Ordinarily we'd use make_black_wight() except that 
        // won't clone a wight if there's one in the room, and 
        // we want another to appear foolish morts who pull the 
        // handle, so we clone it this way.
        wight = clone_object(DOWNS_NPC + "wight")->move(this_object());
        tell_room(TO,"An ink black mist fills the room, then coalesces " +
        "into a black barrow wight.\n");
        handle_pulled++;
//	    tell_room((TO), "A grey mist seeps up from the ground " +
//        "and coalesces into a wight.\n", wight);
	}
        remove_alarm(alarm_id);
}
*/
/* 
 * This is a bit deep into the downs player has already passed 
 * some grey wights. Here the black (stronger) roam. The wight 
 * blocks the way south (you may sneak past him..skills skills..
 * or kill him, naturally. A handle.. cant be moved when wight 
 * is around, oh, and he calls in a friend if he see's you 
 * trying (always) (max 2 new wights per reset)  When rid of 
 * wights, you may use the handle (if STR>40) which opens a 
 * secret door in the next room.
 * Dondon oct 1993
 * 
 * Updated code.
 * -- Finwe, October 2000
 */


inherit "/d/Shire/room";

#include "defs.h"
#include "stdproperties.h"
#include "ss_types.h"
#include <macros.h>

/* Global variables */
int alarm_id;
int hc, getwight, eexit;
object wight;

create_room() {
    set_short("A large cavern");
    set_long("You have entered the inner part of the Downs. " +
        "This large cavern is bare of any decorations. An evil " +
        "feeling permeates the room and a smell of death " +
        "lingers in the air. There is some kind of handle on " +
        "the wall.\n");

    add_item(({"handle", "lever"}),"The handle is of a rocky " +
        "structure. It has obviously not been used for a long " +
        "time.\n");

    add_exit(STAND_DIR + "stone2_3", "south", "@@check_south" , 1);
/* Where is this room? 
    add_exit(STAND_DIR + "stone3_2", "north", 0 , 2);
 Removed by Sir Rogon, for the time being. */
    if (eexit==1)
    {
        add_exit(STAND_DIR + "pit2", "down", "@@check_down", 1);
    }

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,0);
    reset_room();	
}

reset_room() {

	hc=0;
	getwight=0;
	eexit=0;
	if (!present ("wight")) {
	wight = clone_object(STAND_DIR + "npc/wight");
	wight->set_aggressive(0);
	wight->set_attack_chance(0);
	wight->move(this_object());
	}
}

get_a_wight() 
{
    if (getwight!=3)
    {  /*Max 3 pr reset */
	wight = clone_object(STAND_DIR + "npc/wight");
	wight->set_aggressive(1);
	wight->set_attack_chance(90);
	wight->move(this_object());
	getwight++;
	tell_room((TO), "A grey mist seeps up from the ground " +
        "and coalesces into a wight.\n", wight);
	}
        remove_alarm(alarm_id);
}
		


/* Have to kill the wight or fool him (sneak, hide, or be invis) to go back south*/

int
check_south() 
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
int
check_down() {
	if (eexit==1) {
                write("You fall through a hole in the ground.\n\n");
		return 0;
		}
	write("There is no way to go there from here.\n");
	return 1;
}

init() {
    ::init();
    add_action("handle", "move");
    add_action("handle", "use");
    add_action("handle", "push");
    add_action("handle", "pull");
}


handle(str) {

	
	 if (str == "handle" || str == "lever") {
         if (hc==0){			/* Once every reset*/
		if (!present("wight")){
			/* Be strong, or teamed up with a strong guy */
			if (TP->query_stat(SS_STR) < 40) {			
			write("The handle moves a little.\n");
			return 1;
			}
			hc=1;	
			eexit=1;
			handle_moved();
            add_exit(STAND_DIR + "pit2", "down", "@@check_down", 1);

			return 1;
			}
			write("Wight rasps: NOOOoooooo....\n"
			    + "The wight raises his voice to an urgent scream.\n");
			say("The wight stops " + QCTNAME(TP) + " from moving the handle.\n"
			  + "The wight raises his voice in a terrifying scream.\n");
		
                        alarm_id = set_alarm(5.0,0.0,"get_a_wight");
        	        return 1;
			}
		
	
	write("The handle has already been moved, it's stuck.\n");
	return 1; 
	}
}

handle_moved() 
{
    write ( "You push and pull and drag....\n" +
	    "Slowly, with a squeaking sound the handle moves. The " +
        "floor begins to crumble beneath your feet and a gaping " +
        "hole appears.\n");
	say ( QCTNAME(TP)+" pushes and pulls at the handle.\n" +
	    "Slowly, with a squeaking sound the handle moves. The " +
        "floor beneath your feet begins to crumble away and a " +
        "gaping hole appears.\n");
/*calls a function in the next room*/	
/* call_other(STAND_DIR + "stone3_2", "h_moved"); */
}

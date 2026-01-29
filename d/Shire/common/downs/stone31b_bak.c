/* This is a bit deep into the downs
 * player has already passed some grey wights. Here the black (stronger) roam
 * The wight blocks the way south (you may sneak past him..skills skills..
 * or kill him, naturally. A handle.. cant be moved when wight is around, oh,
* and he calls in a friend if he see's you trying (always) (max 2 new wights per reset)
 * When rid of wights, you may use the handle (if STR>40) which opens a secret door
 * in the next room..
 * Dondon oct 1993
 */


inherit "/std/room";

#include "defs.h"
#include "stdproperties.h"
#include "ss_types.h"
#include <macros.h>
/* Global variables */
int alarm_id;
int hc, getwight, eexit;
object wight;

create_room() {
    set_short("Underground");
    set_long(
    	  "You have entered the inner part of the dawns.\n"
	+ "Here, the Black barrow wights roam in search of flesh.\n"
	+ "You dared come here, now face the consequences.\n"
	+ "There is some kind of handle on the wall.\n");

    add_item(({"handle", "lever"}),"The handle is of a rocky structure.\n"    
	  		 + "It has obviously not been used for a long time.\n");

    add_exit(STAND_DIR + "stone2_3", "south", "@@check_south" , 1);
/* Where is this room? 
    add_exit(STAND_DIR + "stone3_2", "north", 0 , 2);
 Removed by Sir Rogon, for the time being. */
    add_exit(STAND_DIR + "pit2", "down", "@@check_down", 1);
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

get_a_wight() {
		
		if (getwight!=3){  /*Max 3 pr reset */
		wight = clone_object(STAND_DIR + "npc/wight");
		wight->set_aggressive(1);
		wight->set_attack_chance(90);
		wight->move(this_object());
		getwight++;
		tell_room((TO), "A wight arrives from the north.\n", wight);
	}
        remove_alarm(alarm_id);
}
		


/* Have to kill the wight or fool him (sneak, hide, or be invis) to go back south*/

int
check_south() {
		if (!present ("wight")){
		return 0;
		}
		else if (TP->query_skill(SS_SNEAK) > 30) {
		write(" You manage to sneak past the wight.\n");
		say(QCTNAME(TP)+" managed to sneak past the wight.\n");
		return 0;
		}
		else if (TP->query_skill(SS_HIDE) > 40) {
		write ("You manage to hide from the wight and escape.\n");
		say (QCTNAME(TP)+" hides and escapes the Wight's attention.\n");
		return 0;
                }
		write ("Wight says: Hahh, live flesh don't leave here.\n");
		say ("Wight stops " + QCTNAME(TP) + " from leaving south.\n");
		return 1;
	}
int
check_down() {
	if (eexit==1) {
		write("You slide down a greasy tunnel");
		return 0;
		}
	write("You cannot enter there without moving the handle.\n");
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
			write("You are not strong enough to move the handle.\n");
			return 1;
			}
			hc=1;	
			eexit=1;
			handle_moved();
			return 1;
			}
			write("Wight says: HEY, wadda ya think ya doin..\n"
			    + "The wight raises his voice to an urgent scream.\n");
			say("Wight stops " + QCTNAME(TP) + " from moving the handle.\n"
			  + "Wight raises his voice in a terrifying scream.\n");
		
                        alarm_id = set_alarm(5.0,0.0,"get_a_wight");
        	        return 1;
			}
		
	
	write("The handle has already been moved, it's stuck.\n");
	return 1; 
	}
}

handle_moved() {
		write ( "You push and pull and drag....\n"
			+ "Slowly, with a squeaking sound the handle moves.\n"
			+ "You hear the sound of falling rocks from the north, the exit down is now open.\n");
		say ( QCTNAME(TP)+" pushes and pulls at the handle.\n"
			+ "Slowly, with a squeaking sound the handle moves.\n"
			+ "You can hear rocks falling to the north, the exit down is now open.\n");
			
				/*calls a function in the next room*/	
			/* call_other(STAND_DIR + "stone3_2", "h_moved"); */
}

// file name: d/Avenir/common/dead/catacombs/crypt/crypt_out
// creator(s):  Lilith, June 2021
// last update: Lilith & Zizuph, May-July 2021: finishing area for launch 
//              Lilith Sep 2021: Added statserv logging 
// note:      the outside of main entrance and exit from catacombs
// to-do:  	
//
inherit "/d/Avenir/common/dead/crypt_base";
#include "../dead.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/include/relation.h"
#include <macros.h>
#include <stdproperties.h>

#define OTHER_SIDE (CRYPT +"crypt_entr")

void open_door();
int enemy_test(object ob);
int door_closed;
public int query_closed() {    return door_closed;    }


public void
reset_domain_room()
{        
    door_closed = 1;
}

public void
create_crypt_room()
{
    set_short("A gated gave entrance");
    set_long("This cave is dominated by a gate that blocks further "
	    +"passage. Carved out of the white limestone cliff, the "
        +"walls of the cave have dark streaks that glisten wetly. "
        +"A dank fog flows through the gate toward encompassing "
        +"darkness. Waves of sadness and fatigue lap at you the "
        +"the same way the sea behind you laps at the shore.\n"
		+"There is an imposing iron gate to the south.\n");
   
    add_exit(PATH + "shore25", "north");
    add_exit(CRYPT + "crypt_entr","south", "@@try_south");
    reset_domain_room();

    add_item(({"gate", "iron gate", "imposing gate",  
       "imposing iron gate", "north gate", "seal"}),
       "This imposing iron gate has the trefoil seal of "
	   +"Sybarus emblazoned on it. It has an unusual "
	   +"lock. It is such a strong and unlikely gate "
	   +"that you find yourself wondering if it is "
	   +"designed to keep you out...or something else in.\n");
	add_item(({"lock", "unusual lock", "locking mechanism"}),
	    "The opening in this lock is for a skull-shaped "
		+"key.\n");
    add_cmd_item(({"gate", "iron gate", "imposing gate",  
         "imposing iron gate", "south gate", "on gate", "on iron gate"}), 
        ({"knock", "bang"}), "@@knock_gate");		
	add_item(({"sea", "ocean", "shore" }), "The dark sea stretches "
	    +"out as far as you can see, its murky black water "
        +"obscuring what lies beneath. The water laps gently "
		+"against the rocks of the shore, making them dark and slippery.\n");
	add_item(({"rock", "rocks", "shoreline", "granite", "feldspar" }),
        "The rocks that are scattered along the shoreline are of "
		+"many shapes and sizes, but all seem to be some sort of "
		+"granite interspersed with traces of gleaming feldspar.\n");
    add_item(({"dark streaks", "streak", "streaks", "slime", "algae"}),
	    "These dark streaks contrast jarringly with the white of the "
		+"limestone. It looks like some sort of slime or algae.\n");
		
	reset_domain_room();	
	
}

int
knock_gate()
{
    if (!query_closed())
    {
        notify_fail("The imposing iron gate is already open.\n");
        return 0;
    }

    write("You bang on the imposing iron gate.\n");
    say(QCTNAME(TP)+ " bangs on the imposing iron gate.\n");

    if (TP->query_prop(OBJ_I_INVIS) || TP->query_prop(OBJ_I_HIDE))
    {
        write("A ghostly head pops through the gate and looks "+
		    "around, then disappears.\n");
        say("A ghostly head pops through the gate and looks "+
		    "around, then disappears.\n");
        return 1;
    }
    if (enemy_test(TP))
    {
		write("A ghostly head pops through the gate and looks at you.\n");
	    write("A ghostly head says: Infidel begone!\n");
        say("A ghostly head pops through the gate and looks at "+ QTNAME(TP) +".\n"); 
	    say("A ghostly head says: Infidel begone!\n");
        return 1;
    }
	
	if (CHECK_QUEST_GATE(TP))
	{	   
	    write("A ghostly head pops through the gate and looks at you.\n");
	    write("A ghostly head says: I remember your face.\n");
        say("A ghostly head pops through the gate and looks at "+ QTNAME(TP) +".\n"); 
	    say("A ghostly head says: I remember your face.\n");
		open_door();
        set_alarm(8.0, -1.0, "close_door");
	    return 1;
    }       
	if (TP->query_prop(DMASK_PROP))
	{	   
	    write("A ghostly head pops through the gate and looks at you.\n");
	    write("A ghostly head says: I remember your face.\n");
        say("A ghostly head pops through the gate and looks at "+ QTNAME(TP) +".\n"); 
	    say("A ghostly head says: I remember your face.\n");
		open_door();
        set_alarm(8.0, -1.0, "close_door");
	    return 1;
    }       

    write("A ghostly head pops through the gate and looks at you.\n");
    write("A ghostly head says: I don't recognize your face. Go away.\n");
    say("A ghostly head pops through the gate and looks at "+ QTNAME(TP) +".\n"); 
	say("A ghostly head says: I don't recognize your face. Go away.\n");
	return 1;
}

int
enemy_test(object ob)
{
    if (IS_INFIDEL(ob))
        return 1;
    else
        return 0;
}

void
open_door()
{
    tell_room(TO,"The imposing iron gate crashes open.\n");
    tell_room(OTHER_SIDE,"The patient spirit opens the imposing iron gate.\n");
    door_closed = 0;
    return;
}
    
void
close_door()
{
    if (query_closed())
        return;

    tell_room(TO,"The imposing iron gate slams closed.\n");
    tell_room(OTHER_SIDE, "The patient spirit closes the imposing iron gate.\n");
    door_closed = 1;
    return;
}
    
int
try_south()
{   
    if (!interactive(TP))
        return 0;

    if (query_closed())
    {
        write("The imposing iron gate is closed.\n");
        return 1;
    }

    if (enemy_test(TP))
    {
        close_door();
        return 1;
    }
	
	open_door();
    write("You walk past the gate into a dim room.\n");
	STATSERV_LOG_EVENT("crypt", "Entered Crypt via gate");
    return 0;
}

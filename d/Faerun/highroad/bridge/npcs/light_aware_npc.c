#pragma strict_types
#pragma no_clone

#include "/d/Faerun/defs.h"
#include "defs.h"

//inherit FAERUN_NPC_BASE;

/*
 * Routines to make an NPC react to light changes 
 * in Faerun. Require support in the room code.
 *  
 * by Kehr, March 2007
 */

// Its a duplicate... same as in base_npc.c
void equip_me()
{
    object torch;
    
    torch = clone_object("/std/torch");
    torch -> set_short("wooden torch");
    torch -> set_long("It is a plain wooden torch that will burn for a while.\n");
    torch -> move (this_object());
} 
 
void do_light_torch()
{
	// check if it is still necessary
	
	if (environment(TO)->light()<1)
		command("light torch");	
}

void do_extinguish_torch()
{
	// check if it is still necessary
	// >1 because torch has +1 light - so it means someone else lit a torch as well
	if (environment(TO)->light()>1)
		command("extinguish torch");	
}

// light/extinguish code called via alarm to avoid race conditions
// when multiple npc's react to the same event 
void notify_light_level(int ln)
{
	float time;

	time = 3.0 + 3.0*rnd();
	
	if (ln<1)
		set_alarm(time, 0.0, do_light_torch);
	else
		set_alarm(time, 0.0, do_extinguish_torch); 	
}
	
void hook_torch_burned_out(object torch)
{
	tell_room(environment(), TO->short() + " curses silently and grabs a new torch.\n");
	command("drop torch");
	    
    equip_me();
}



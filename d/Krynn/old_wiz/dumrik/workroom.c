/*
 * /doc/workroom.c
 * Written 920624 by Quis
 * 
 * This function serves two main purposes.  First, it is example coding
 * of a workroom.  Second, it gives the apprentice wizard an easy way to
 * get back to the wizard island.
 */

#include "/d/Krynn/common/defs.h"
#include TIME_FLOW

inherit "/std/workroom";

/*
 * The following macros are intended to prevent lines from wrapping
 * around the screen, and avoid the wizard from having to put in explicit 
 * \n's.
 */

// #define BSN(s) break_string((s) + "\n",70)
#define BSNN(s) break_string((s) + "\n\n",70)


/*
 * This function is called when the workroom is loaded.  It sets up the
 * description of the room, and its exits.
 */
create_workroom()
{
    /* Here is an example of VBFC in the long description.  The long
     * description will be the string returned by the function "long_desc"
     */
    set_long("@@long_desc");
    set_short("Dumrik's workroom");

}

void init() {
  ::init();
  ADA("dq_int");
}

int dq_int() {
  int q;

  q = INTERRUPT_PERIOD("dragon_quest","harass solace");

  find_player("dumrik")->catch_msg("q=" + q + "\n");
  return 1;
}



/* 
 * This function simply returns a string.  Complex descriptions based on
 * the state of the room are possible.
 */

string
long_desc()
{
    return BSNN("You are in Dumrik's workroom. " +
         "This is quite a dizzy feeling. The room has no walls, no floor, and no " + 
         "ceiling, it seems like you are hanging in thin air. In all directions " +
	 "there is an infinite depth of clean transparent space.");
}






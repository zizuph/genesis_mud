/* Xak Tsorath coded by Percy */

#include "xlocal.h"

inherit  MARSHBASE

#include RND_MEET
#include <ss_types.h>
#include <macros.h>


object monster, room;

void
create_marsh() 
{
    set_short("The obelisk in the swamp");
    set_long("You are in the cursed lands, a truly dismal place in"
	     + " every sense of the word. All around you is a seemingly"
	     + " endless marsh swamp. Danger seems to ooze from it nauseous"
	     + " surface. There is an old ruined obelisk here that seems to"
	     + " have fallen over. It now crosses over a particularly nasty"
	     + " stretch of swamp and into a deserted city...\n");
    
    add_exit(TDIR + "entrance.c", "north", "@@cross_over", 5);
    add_exit(TDIR + "marsh1.c", "west", 0, 5);
    OUTSIDE;
    LIGHT;
    add_item("obelisk", "@@obelisk");
    set_alarm(0.1,0.0,"reset_room");
}

int
cross_over()
{
    write("You cross tenaciously over the ruined obelisk wondering"
	  + ", as it lurches dangerously under you, how on earth"
	  + " you got into this mess.\n");
    return 0;
}

string
obelisk()
{
    write("The obelisk seems to have once been a part of this now"
	  + " ruined city, which you guess to be Xak Tsaroth. It has long"
	  + " since been claimed by the marshlands and now just represents"
	  + " the lost magnificence this city must once have had, before the"
	  + " cataclysm.\n");
    return "";
}

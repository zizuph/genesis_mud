#include "defs.h"

object dragon;

void try_throw_out();

CONSTRUCT_ROOM {
    set_short("You are in the dragons lair!");
    set_long("You are in a dragon's lair.\n"+
	     "@@my_long@@");
    add_item(({"exit","exits","opening"}),
	     "It looks like there is an opening northwards too, behind the "+
	     "dragon, but I do not advice you to try to go there!");
    EXIT("big_hall","south");
    EXIT("losttrck","north");
    reset();
}

RESET_ROOM {
/*
    if (!dragon) {
	dragon = clone_object(MORIA_NPC+ "dragon");
        dragon->move(this_object());
    }
*/
}

int
query_dragons_lair() { return 1; }

string
my_long() {
    if (objectp(dragon) && present(dragon))
	return ("A dragon, fifty yards long, lies here sleeping in a huge room. "+
		"Fire and sulfur streams out of its big nostrils as it breathes. "+
		"It grunts and stirs asleep, but if you value your life, you "+
		"should not disturb it. Instead of passing it, consider "+
		"retreating slowly to the south, through the opening. It looks "+
		"like there is an opening northwards too, behind the dragon, "+
		"but I do not advice you to try to go there!\n");
    else if (present("Corpse of Dragon")) 
	return ("The very beeing seems to lie here, unable to attack. There is "+
		"an opening to the south towards a big hall. It looks like there "+
		"is an opening northwards too, behind the dragon, but I do not "+
		"advice you to try to go there!\n");
    else 
	return ("Luckily the dragon seems to be gone. However it may" +
        "come back anytime soon. There are two openings here--"+
        "one to the south to a big hall and another to the north " +
        "towards a strange room.");
}

try_throw_out() {
    if (!dragon)
	return;
    if (TP == dragon)
	return;
    if (present(dragon)) {
	if (present("lump of sulfur", TP))
	    return;
	if (present("lump of sulfur", TO) && random(8))
	    return;
	dragon->do_send_out(TP, 1);
    }
}

init()
{
    ::init();
    set_alarm(0.0, 0.0, &try_throw_out());
}

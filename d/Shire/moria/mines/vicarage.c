#include "defs.h"

object ikon;
int possible;

CONSTRUCT_ROOM {
    possible = 1;
    set_short("Vicarage.");
    set_long("You find yourself in the vicarage. This is a small room in "+
	     "which a roughly carved wood-cross displays the presence of a "+
	     "priest or a monk. There is a hole in the floor.\n");
    add_item(({"cross","wood-cross"}),
	     "This item is which who tells that this *is* a vicarage.");
    add_item("hole", "It leads down to a strange room.");
    add_item("floor",
	     "Except for the hole, there is nothing much to be said about it.");
    DOWN("losttrck");
    add_call("get", "[the] [wooden] 'cross' / 'wood-cross'", "my_get");
    add_call("fold", "[my] 'hands'", "my_pray");
    add_call("pray", "[to] [at] [the] [cross]", "my_pray");
    add_call("kneel", "[in] [front] [of] [down] [by] [cross]", "my_pray");
    reset();
}

RESET_ROOM {
    possible = 1;
//    if (!present("ikon"))
//	clone_object(MORIA_OBJ+"ikon")->move(this_object());
}

my_get()
{
    write("You wouldn't take that!\n"+
	  "If you did, I wouldn't be able to tell you\n"+
	  "what room you have entered!\n");
    return 1;
}

my_pray(string str)
{
    write("You kneel in front of the wooden cross, folding your hands, "+
	  "praying.\n");
    say(QCTNAME(TP)+" kneels in front of the wooden cross, "+
	"folding "+HIS_HER(TP)+" hands, praying.\n");

    if (!present("ikon") || !possible)
    {
	tell_room(environment(TP),"But nothing happens.\n");
	return 1;
    }
    tell_room(TO,
	"A loud voice rumbles: Your sins are forgiven, "+TP->query_name()+"!\n");
    if (TP->query_alignment() < 100)
	TP->set_alignment(200);
    possible = 0;
    return 1;
}

#include "defs.h"

int amount;

CONSTRUCT_ROOM
{
    set_short("In a hole in the ground");
    set_long(
	"You are standing in a hole in the ground. It is situated "+
	"by the end of a large slab of stone. The bottom of the hole "+
	"is covered with a slippery variegated green moss of some kind.\n");
    add_item("moss",
	"You could manage to grab a handful of it.");
    add_call(({"pick", "grab", "get", "take", "fetch"}),
    "[a] [hanful] [of] [grey] 'moss' / 'herbs'","pick");
    UP("byhole");
    amount = 2;
}

RESET_ROOM
{
    amount = 2;
}

int pick(string what)
{
    if (amount==0)
	return notify_fail(
	    "Sorry, but you can't "+query_verb()+" anymore moss now.\n");

    write("You "+query_verb()+" a handful of grey moss.\n");
    say(QCTNAME(TP)+" grabs a handful of grey moss.\n");
    clone_object(MORIA_HERB + "pindan")->move(TP); // For now.
    amount --;
    return 1;
}

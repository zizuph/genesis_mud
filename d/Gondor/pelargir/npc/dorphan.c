inherit "/d/Gondor/pelargir/npc/orphan.c";

#include "/d/Gondor/defs.h"

void
create_orphan()
{

    set_short("dirty orphan");
    set_pshort("dirty orphans");

    set_adj("dirty");

    add_chat("The grime from the street doesn't wash off very easy!");
    add_chat("How do you keep your clothes so clean?");
    add_chat("Hmm.. do you smell something?");
    add_chat("I just can't figure out why my parents left.");
    add_chat("The rats around here make great friends.");
    add_chat("I changed clothes just last week!");
    add_chat("The orphan master made me take a bath!  Ack!");
    add_chat("I'll bet I came from a noble family.");
    add_chat("Excuse me, would you like to take me home?");
    add_chat("When I grow up, I'm gonna join the rangers.");
    add_chat("My parents told me they'd be right back... two years ago.");
    add_chat("I get to leave when I'm sixteen, if i live that long.");
}


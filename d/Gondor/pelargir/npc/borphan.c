inherit "/d/Gondor/pelargir/npc/orphan.c";

#include "/d/Gondor/defs.h"

void
create_orphan()
{

    set_short("brave orphan");
    set_pshort("brave orphans");

    set_adj("brave");

    add_chat("You don't scare me, you big bully!");
    add_chat("I can kill a rat all by myself!");
    add_chat("The orphan master doesn't scare me! He isn't looking, is he?");
    add_chat("One day, I'll fight orcs for fun!");
    add_chat("I'm not sure this is any better than being homeless.");
    add_chat("I'll bet I came from a noble family.");
    add_chat("One day my mother will come for me, I'm sure of it!");
    add_chat("When I grow up, I'm gonna join the rangers.");
    add_chat("My parents told me they'd be right back... two years ago.");
    add_chat("When I grow up, I'll kill the orphan master.");
}


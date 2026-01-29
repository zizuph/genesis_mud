inherit "/d/Gondor/pelargir/npc/orphan.c";

#include "/d/Gondor/defs.h"

void
create_orphan()
{
    set_short("lonely orphan");
    set_pshort("lonely orphans");

    set_adj("lonely");

    add_chat("I'm lonely.");
    add_chat("One day, I'll be a big adventurer like you.");
    add_chat("Will you be my friend?");
    add_chat("I'm not sure this is any better than being homeless.");
    add_chat("One day my mother will come for me, I'm sure of it!");
    add_chat("Excuse me, would you like to take me home?");
    add_chat("I have three imaginary friends...sadly, they don't get along.");
    add_chat("I never even knew my parents.");
    add_chat("I've lived here all my life, What's it like outside?");
}



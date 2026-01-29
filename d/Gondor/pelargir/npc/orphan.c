inherit "/d/Gondor/pelargir/npc/pelargir_npc";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_orphan()
{
    add_chat("I'm not sure this is any better than being homeless.");
    add_chat("I'll bet I came from a noble family.");
    add_chat("One day my mother will come for me, I'm sure of it!");
    add_chat("Excuse me, would you like to take me home?");
    add_chat("When I grow up, I'm gonna join the rangers.");
    add_chat("My parents told me they'd be right back... two years ago.");
    add_chat("I have three imaginary friends...sadly, they don't get along.");
    add_chat("I get to leave when I'm sixteen, if i live that long.");
    add_chat("I never even knew my parents.");
    add_chat("I've lived here all my life, What's it like outside?");
    add_chat("When I grow up, I'll kill the orphan master.");
}

nomask void
create_pelargir_npc()
{
    int     rnd1 = random(11),
            rnd2 = random(11);

    set_name("orphan");
    set_race_name("human"); 
    set_short("orphan");
    set_pshort("orphans");
    set_long("A poor helpless orphan, given to wandering the streets "
      + "of Pelargir.\n");

    set_stats(({5 + rnd1, 5 + rnd2, 5 + (rnd1 + rnd2) / 2,
                5 + rnd2, 5 + rnd1, 5 + (rnd1 + rnd2) }));

    set_alignment(50);
    set_skill(SS_WEP_KNIFE, 20  +  rnd1 + rnd2);
    set_skill(SS_DEFENCE,   30  +  rnd1 - rnd2);
    set_skill(SS_AWARENESS, 20  +  rnd1 / 2 + rnd2);

    add_prop(LIVE_I_NEVERKNOWN,1);

    set_chat_time(30);

    create_orphan();
}

void
arm_me()
{
    FIX_EUID

    clone_object(PELAR_DIR + "obj/bknife")->move(TO);
    command("wield knife");

    clone_object(PELAR_DIR + "obj/bcoat")->move(TO);
    command("wear all");

    clone_object(PELAR_DIR + "obj/orpants")->move(TO);
    command("wear all");
}


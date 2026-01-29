/*
 *	/d/Gondor/pelargir/npc/ruffian.c
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/d/Gondor/pelargir/npc/pelargir_npc";

#include <ss_types.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/logkill.c"

void
create_ruffian()
{
    set_short("unkempt ruffian");
    set_pshort("unkempt ruffians");
    set_long(BSN("This man is anything but a model citizen; "
      + "poorly shaven, hair all askew, and from that glint "
      + "in his eye you might guess he is up to no good."));

    set_chat_time(30);
    add_chat("You think maybe this one's got any loot?");
    add_chat("I don't think the old lady was worth the trouble.");
    add_chat("hmm...if I could only steal a few more coins, I could "
      + "buy an orphan. Wouldn't a slave be nice?");
    add_chat("I'll bet Linyenwo has some loot worth taking!");

    set_default_answer(VBFC_ME("default_answer"));
}

nomask void
create_pelargir_npc()
{
    int     rnd1 = random(21),
            rnd2 = random(21);

    set_name("ruffian");
    set_race_name("human"); 

    set_stats(({15 + rnd1, 15 + rnd2, 15 + (rnd1 + rnd2) / 2, 
                20 + rnd1/2, 20 + rnd2, 5 + rnd1 + rnd2/2}));

    set_alignment(-150);

    set_skill(SS_WEP_KNIFE, 20 + rnd1);
    set_skill(SS_DEFENCE,   20 + rnd2);
    set_skill(SS_PARRY,     20 + rnd1 / 2);
    set_skill(SS_AWARENESS, 20 + rnd2);

    create_ruffian();
}

void
arm_me()
{
    FIX_EUID

    clone_object(WEP_DIR + "knife")->move(TO);
    command("wield knife");

    clone_object(PELAR_DIR + "obj/lvest")->move(TO);
    command("wear all");

    clone_object(MINAS_DIR + "obj/ctrousers")->move(TO);
    command("wear all");
}

string
default_answer()
{
    command("spit");
    command("say What? I don't know what you're gabbing about! Scram!");
    return "";
}


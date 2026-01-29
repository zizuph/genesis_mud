/* Sarr */
#include "defs.h"
inherit "/d/Raumdor/std/monster";
inherit "/d/Raumdor/lib/intro";


void
create_monster()
{
    ::create_monster();
    set_name("galbert");
    add_name("man");
    set_race_name("human");
    set_adj(({"old","man"}));
    set_short("old man");

    set_long("This is an old man whose wrinkled, brown skin covers "+
    "his tiny frame. Tatters of robes hangs from his limbs.\n");

    set_stats(({40,40,30,80,70,50}));
    set_skill(SS_DEFENCE,100);

    add_prop(LIVE_I_SEE_DARK,100);
    set_alignment(-800);
    set_act_time(5);
    set_title("the Aged Sage");
    add_act("ponder");
    add_act("think");
    add_act("hmm");

    set_default_answer("say I have nothing to say on that subject.", 1);
    add_ask(({"lore","ancient lore","help"}),
        "say I know of the beast lord.\n", 1);
    add_ask(({"lord","beast lord"}),
        "say The beast lord lives in some ruins. He "+
        "was created by a vile necromancer known as Zeelek.\n", 1);
    add_ask("staff of ages","say The staff of ages, yes, I might "+
        "know where to find such an item. The way is tricky, however, "+
        "and only those who know the secret way can find their way. I "+
        "have with me a few items that may help you.\n", 1);
    add_ask("items","@@itms@@",1);

}

string
itms()
{
    seteuid(getuid());
    clone_object(COMMON_OBJ_DIR + "figure1")->move(TO);
    clone_object(COMMON_OBJ_DIR + "figure2")->move(TO);
    clone_object(COMMON_OBJ_DIR + "figure3")->move(TO);
    command("give figures to "+TP->query_real_name());
    command("drop figures");
    return "say This is all I have, what they mean, I do not know. "+
    "Good luck.";
}

/*
 *	/d/Gondor/pelargir/npc/citizen.c
 *
 */
inherit "/d/Gondor/pelargir/npc/pelargir_npc.c";
inherit "/d/Gondor/common/lib/logkill";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/lib/defs.h"

void
create_citizen()
{
    set_chat_time(30);
    add_chat("Ahh! The fresh river air!");
    add_chat("Pelargir is beautiful all year round!");
    add_chat("There have been a surprising number of "+
       "strange visitors lately.");
    add_chat("Don't go to the poor section, only riff-raff live there.");
    add_chat("I love this town.");
    add_chat("I fear that there will be war soon!");
}

nomask void
create_pelargir_npc()
{
    int     rnd1 = random(21),
            rnd2 = random(21);

    set_name("citizen");
    set_race_name("human");

    set_gender(random(2));
    if (query_gender())
    {
        add_name("woman");
        add_pname("women");
    }
    else
    {
        add_name("man");
        add_pname("men");
    }

    add_prop(CONT_I_HEIGHT,   160 + rnd1 + rnd2);
    add_prop(CONT_I_WEIGHT, 60000 + rnd1 * 2000);
    add_prop(CONT_I_VOLUME, 55000 + rnd1 * 2000);    

    set_adj(({"dark-haired", "proud"}));
    switch (rnd1+rnd2)
    {
        case 0..10:
            set_adj("short");
            break;
        case 11..29:
            break;
        case 30..40:
            set_adj("tall");
            break;
    }
    switch(rnd1)
    {
        case 0..4:
            set_adj("thin");
            break;
        case 5..15:
            break;
        case 16..20:
            set_adj("fat");
            break;
    }

//  set_short("citizen of Pelargir");
//  set_pshort("citizens of Pelargir");
    set_long(BSN(CAP(LANG_ADDART(query_adjs()[0]))+" "+query_adjs()[1]
      + (query_gender() ? " woman" : " man")
      + ", a citizen of Pelargir, perhaps having a little "
      + "of the dunadan in lineage."));

    set_stats(({15 + rnd1, 15 + rnd2, 15 + (rnd1 + rnd2) / 2, 
                20 + rnd2 / 2, 20 + rnd1 / 2, 5 + rnd1 + rnd2}));
    set_alignment(150 + (rnd1 + rnd2) * 2);

    set_skill(SS_WEP_KNIFE, 20 + rnd1);
    set_skill(SS_DEFENCE,   20 + rnd2);
    set_skill(SS_PARRY,     20 + (rnd1 + rnd2) / 3);
    set_skill(SS_AWARENESS, 20 + (rnd1 + rnd2) / 2);

    add_prop(LIVE_I_NEVERKNOWN, 1);

    create_citizen();

    FIX_EUID

    MONEY_MAKE_CC(10 + rnd1)->move(TO);
    MONEY_MAKE_SC(1 + rnd2 / 2)->move(TO);
}

void
arm_me()
{
    clone_object(WEP_DIR + "knife")->move(TO);
    clone_object(MINAS_DIR + "obj/ltunic")->move(TO);
    clone_object(MINAS_DIR + "obj/ctrousers")->move(TO);
    command("wear all");
    command("wield all");
}


#include "defs.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
inherit "/d/Raumdor/std/guard_std";
inherit "/d/Raumdor/lib/intro";
inherit "/lib/unique";

void
create_monster()
{
    ::create_monster();
    set_name("gretchin");
    add_name("captain");
    add_name("guard");
    set_race_name("human");
    set_adj("strong");
    add_adj("stern");
    set_gender(1);
    set_short("captain of the royal guards of Drakmere");
    set_long(
      "This woman is the captain of the guards of Drakmere. Her cold blue " +
      "eyes regard you sternly. Her flowing blond hair peeks out from behind " +
      "her helm. Despite her curvy figure, you can tell that she is well " +
      "made, strong, and very quick. She takes her guarding job " +
      "seriously.\n");
    set_stats(STAT_ARRAY(170));
    set_alignment(DRAKMERE_ALIGN);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 70);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_2H_COMBAT, 100);
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1); /* won't accept gifts */
    add_prop(CONT_I_WEIGHT, 80000);    /* weights 80 kilo's */
    add_prop(CONT_I_HEIGHT, 195);      /* 195 cm high */
    set_hp(query_max_hp());            /* heal fully */
    set_title("the Captain of the royal guards of Drakmere");
    set_act_time(6);
    add_act("say What can I do for you?");
    add_act(
      "say The clouds seem to get darker every day. The days seem shorter as " +
      "time goes on.");
    add_act("say King Raumdor was a good man.");
    add_act("emote adjusts her armour.");
    add_act("hmm");
    set_cact_time(1);
    add_cact("say You will _not_ get away with this!");
    add_cact("say Die foul creature of hell!");
    add_cact("say Leave or DIE!");

    equip(({
      clone_unique(
        DRAKMERE_WEP_DIR + "h_sword", 15, DRAKMERE_WEP_DIR + "g_sword"),
      DRAKMERE_ARM_DIR + "dgcloak", DRAKMERE_ARM_DIR + "dgplate",
      DRAKMERE_ARM_DIR + "dcggreaves", DRAKMERE_ARM_DIR + "dghelm",
    }));
    MONEY_MAKE_GC(random(10))->move(TO, 1);
}

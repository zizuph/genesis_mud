/* trainer.c: Tyr city trainer: Serpine, 9/12/95. */
 
inherit "/d/Cirath/std/monster";
inherit "/d/Cirath/common/shiva_train";
#include "defs.h"
 
void set_up_skills()
{
    create_skill_raise();        
    sk_add_train(SS_APPR_MON, "appraise an opponent", "appraise enemy", 0, 30);
    sk_add_train(SS_APPR_OBJ, "appraise an object", "appraise object", 0, 30);
    sk_add_train(SS_LANGUAGE, "understand foreign languages", "language", 0, 20);
    sk_add_train(SS_ANI_HANDL, "handle animals", "animal handling", 0, 20);
    sk_add_train(SS_HUNTING, "hunt for a living", "hunting", 0, 30);
    sk_add_train(SS_AWARENESS, "notice things", "awareness", 0, 30);
    sk_add_train(SS_TRADING, "trade at a profit", "trading", 0, 30);
}
 
void 
create_monster()
{
    set_name(({ "sally", "trainer", "Errlog" }));
    set_title("the Mistress of Training");
    set_living_name("_Errlog_");
    set_race_name("human");
    set_adj("pretty");
    add_adj("young");
    set_gender(1);
    set_long("A lovely young lady who teaches a few skills to others.\n");
    set_stats(({ 15, 20, 15, 7, 10, 10 }));
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_WEP_SWORD, 100);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    refresh_mobile();
 
    set_up_skills();
    add_act("say I like it here, its such a nice place.");
    add_act("say Maybe one day i can buy myself a home.");
    add_act("say I like training people, it makes me feel lovely.");
    add_act("emote teaches some ciuboris skills.");
}
 
init_living()
{
    ::init_living();
    init_skill_raise();
}

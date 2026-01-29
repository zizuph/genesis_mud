/* trainer.c: Tyr city trainer: Serpine, 9/12/95. */
 
inherit "/d/Cirath/std/monster";
inherit "/d/Cirath/common/shiva_train";
#include "defs.h"
 
void set_up_skills()
{
    create_skill_raise();        
    sk_add_train(SS_WEP_SWORD, "fight with a sword", "sword", 0, 15);
    sk_add_train(SS_WEP_AXE, "fight with an axe", "axe", 0, 10);
    sk_add_train(SS_WEP_KNIFE, "fight with a knife", "knife", 0, 25);
    sk_add_train(SS_WEP_CLUB, "fight with a club", "club", 0, 20);
    sk_add_train(SS_APPR_MON, "appraise an opponent", "appraise enemy", 0, 30);
    sk_add_train(SS_ANI_HANDL, "handle animals", "animal handling", 0, 20);
    sk_add_train(SS_HUNTING, "hunt for a living", "hunting", 0, 30);
    sk_add_train(SS_AWARENESS, "notice things", "awareness", 0, 30);
    sk_add_train(SS_TRADING, "trade at a profit", "trading", 0, 30);
}
 
void 
create_monster()
{
    set_name(({ "vrena", "trainer", "Errlog" }));
    set_title("the Mistress of Training");
    set_living_name("_Errlog_");
    set_race_name("human");
    set_adj("angry");
    add_adj("young");
    set_gender(1);
    set_long("Once a Templar training the armies of Hamanu of Urik, "
            +"this young woman fell out of favor and was forced to "
            +"flee. In a magnanimous gesture Kalak granted sanctuary: "
            +"As much to annoy his rival as gain access to the tactics "
            +"of the enemy army.\nHer left ear has been cut off.\n");
    set_stats(({ 150, 200, 150, 75, 100, 100 }));
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_WEP_SWORD, 100);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    refresh_mobile();
 
    set_up_skills();
    add_act("say Hamanu was a fool to discard me.");
    add_act("say I wish Kalak would declare me one of his Templars.");
    add_act("say Training is the key to success.");
    add_act("emote teaches some Tyrians skills.");
}
 
void
arm_me()
{
    clone_object(TYR_WEP+"swrd_nrw.c")->move(TO);
    clone_object(TYR_ARM+"shld_chn.c")->move(TO);
    clone_object(TYR_ARM+"body_std.c")->move(TO);
    clone_object(TYR_ARM+"head_lth.c")->move(TO);
    clone_object(TYR_ARM+"legs_lth.c")->move(TO);
    clone_object(TYR_ARM+"arms_lth.c")->move(TO);
    command("wield all");
    command("wear all");
}
 
init_living()
{
    ::init_living();
    init_skill_raise();
}

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("aylmer");
    add_name("militiaman");
    add_pname("militiamen");
    set_race_name("human");
    set_adj("watchful");
    set_short("militiaman");
    set_pshort("militiamen");
    set_long("This ordinary-looking man is carefully scanning his "+
      "surroundings, alert to any possible danger. The patch sewed onto his "+
      "right arm of two crossed swords indicates he is a member of the Kabal "+
      "city militia.\n");
    set_stats(({45,40,45,30,30,40}));
    set_alignment(250);
    set_skill(SS_WEP_SWORD,70);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_PARRY,50);
    set_act_time(3);
    add_act("hmm");
    add_act("say You'd better move on.");
    add_act("poke all");
    add_act("emote carefully scans his surroundings.");
    set_cact_time(3);
    add_cact("say You will cease this senseless act now!");
    add_cact("say The city guards will kill you for this!");
    add_speak("You're a bit too curious for your own good.\n");
    set_knight_prestige(-3);
    set_alarm(1.0,0.0,"arm_me");
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
}
void
arm_me()
{
    object wep,arm;
    seteuid(getuid(TO));
    arm = clone_object("/d/Kalad/common/caravan/arm/cmscale");
    arm -> move(TO);
    command("wear all");
    wep = clone_object("/d/Kalad/common/caravan/wep/cmsword");
    wep -> move(TO);
    command("wield all");
    MONEY_MAKE_SC(random(20))->move(TO,1);
}
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("shout No fighting in the streets, " + ob->query_nonmet_name() + "!");
	command("kill " + lower_case(ob->query_real_name()));
    }
}
void
enter_inv(object obj, object from)
{
    if(from)
    {
	if(obj->short() == "a gold coin")
	    set_alarm(3.0,0.0,"return_leave",from);
    }
}

void
return_leave(object obj){
    if(present(obj, environment())){
	command("smile greedily");
	command("thank " + (obj->query_real_name()));
	command("s");
    }
}
void
emote_hook(string emote,object actor,string ad)
{
    if(emote == "grin")
	set_alarm(2.0,0.0,"return_grin",actor);
}

void
return_grin(object obj){
    if(present(obj, environment())){
        command("say What are you grinning at?");
	command("kick " + (obj->query_real_name()));
    }
}
void
init_living()
{
    ::init_living();
    if(interactive(TP))
	set_alarm(2.0,0.0,"return_arrive",TP);
}

void
return_arrive(object obj){
    if(present(obj, environment())){
	command("frown");
	command("poke " + (obj->query_real_name()));
	command("say Get out of here.");
    }
}

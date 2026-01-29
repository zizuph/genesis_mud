inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
inherit "/d/Kalad/lib/extra_long";

#include "/d/Kalad/defs.h"
/* by Antharanos */
int heal;
create_monster()
{
    ::create_monster();
    set_name("greyanna");
    add_name("priestess");
    set_race_name("drow");
    set_adj("stoic");
    add_adj("demure");
    set_long("An unremarkable-looking drow female, she appears, unlike most "+
      "drow females, to be quite in control of her emotions and almost shy "+
      "in her manner. The only thing that would lead anyone to think "+
      "otherwise is the intensity so evident in her eyes, something common "+
      "to the priestesses of Lolth.\nFrom the symbol of a black widow "+
	"spider perched atop two crossed halberds, it appears as if "+
	"she belongs to House Noquar.\n");
    set_gender(G_FEMALE);
    set_stats(({90,120,90,25,25,75}));
    set_skill(SS_UNARM_COMBAT,25);
    set_skill(SS_WEP_POLEARM,80);
    set_skill(SS_DEFENCE,75);
    set_skill(SS_PARRY,75);
    set_skill(SS_AWARENESS,90);
    set_skill(SS_SPELLCRAFT,90);
    set_skill(SS_HIDE,75);
    set_skill(SS_SNEAK,50);
    set_alignment(-900);
    set_knight_prestige(900);
    set_act_time(3);
    add_act("smirk");
    add_act("grin menacingly all");
    add_act("cackle dem");
    add_act("snarl all");
    add_act("hide");
    add_act("say Wael!");
    set_cact_time(3);
    add_cact("growl all");
    add_cact("say Quarvalsharess plynn dos!");
    add_cact("say Lolth plynn dos!");
    add_speak("There is nothing more enjoyable than the sacrifice of "+
      "iblith svirfnebli.\n");
    set_default_answer("Do not ask foolish questions!\n");
    add_ask(({"svirfnebli"}),"They are our greatest enemies, these "+
      "wretched little gnomes must all die.\n");
    set_title("Noquar, the Priestess of Lolth");
    add_prop(LIVE_I_SEE_DARK,10);
    add_prop(NPC_I_NO_RUN_AWAY,1);
}
void
emote_hook(string emote, object actor, string ad)
{
    if(emote == "spit")
	set_alarm(2.0,0.0,"return_arrive",actor);
}

void
return_arrive(object obj){
    if(present(obj, environment())){
	command("say Dos iblith! Usstan elgg dos!");
	command("kill " + lower_case(obj->query_real_name()));
    }
}
void
arm_me()
{
    object wep, arm;
    seteuid(getuid(TO));
    arm = clone_object(CPASS(arm/piwafwi));
    arm -> move(TO);
    arm = clone_object(CPASS(arm/dw_boots));
    arm -> move(TO);
    command("wear all");
    arm = clone_object(CPASS(drow/obj/h8_insignia));
    arm -> move(TO);
    wep = clone_object(CPASS(drow/wep/h8_pr_halberd));
    wep -> move(TO);
    command("wield all");
    MONEY_MAKE_GC(random(8))->move(TO,1);
}
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = TO;
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
	if (ob[i]->query_see_blood())
	    ob[i]->catch_msg(str);
}

int
special_attack(object enemy)
{

    int attacktype, i, penet;
    mixed* hitresult;
    string how;
    object me, *ob;
    me = TO;

    attacktype = random(5);
    if (attacktype == 1)
    {

	ob =  FILTER_LIVE(all_inventory(environment(me))) - ({ me });

	for (i = 0; i < sizeof(ob); i++)
	{
	    penet = 350 + random(150);
	    penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_COLD) / 50;
	    hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);

	    how = "not harmed";
	    if (hitresult[0] > 0)                  
		how == "barely frozen";
	    if (hitresult[0] > 10)
		how = "slightly frozen";
	    if (hitresult[0] > 20)
		how = "frozen quite badly";
	    if (hitresult[0] > 40)
		how = "frozen very badly";
	    if (hitresult[0] > 60)
		how = "utterly frozen";

	    ob[i]->catch_msg("You hear a rhythmic chanting and then a deadly eruption "+
	      "of frigid ice shoots forth from the priestess's hands at you!\n");
	    ob[i]->catch_msg("You were " + how + " by the blast of cold!\n");
	    tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the blast of cold!\n", ob[i]);

	    if (ob[i]->query_hp() <= 0)
		ob[i]->do_die(me);
	}
	return 1;
    }

    if (attacktype == 2)
    {
	if (heal == 5)
	{
	    return 0;
	}
	heal += 1;
	write("The priestess recites a prayer to Lolth.\n"+
	  "She is bathed in a soft red glow and appears healthier!\n");
	say("The priestess recites a prayer to Lolth.\n"+
	  "She is bathed in a soft red glow and appears healthier!\n");
	me->heal_hp(500);
	return 1;
    }
    return 0;
}

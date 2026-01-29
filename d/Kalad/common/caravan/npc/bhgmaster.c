#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#define QUEST_NAME "tabletquest"

int tablet;
string long;
object lord;

void
create_kalad_monster()
{
    set_name("entreri");
    add_name("lord");
    set_race_name("human");
    set_adj("cunning");
    add_adj("sadistic");
    set_long("This man is dressed in the attire of a noble, yet somehow "+
      "the clothes don't seem to fit him. Perhaps its the way he comes "+
      "across as sneaky and underhanded, as if he were some cutthroat "+
      "thief.\n");

    set_stats(({105, 175, 105, 90, 100, 100}));
    set_alignment(-100);

    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 60);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_HIDE, 90);
    set_skill(SS_SNEAK, 90);

    set_act_time(3);
    add_act(({"say Well well...what do we have here...visitors?", "smirk"}));
    add_act("say You must really want to see me if you've gone to all "+
      "this trouble just to get here.");
    add_act(({"hmm", "say Are you my new servants?", "laugh all"}));
    add_act(({"peer all", "say You're looking a bit flabby, forgot to do "+
	"your exercises huh?", "laugh all"}));
    add_act("say You really are quite boring.");
    add_act("emote fidgets with his necklace.");
    add_act(({"yawn", "say Why don't you kill yourself, just to amuse me."}));
    add_act("say What do you want?");
    add_act("show");
    set_cact_time(1);
    add_cact("say Oh come now! You didn't expect me to just keel over and "+
      "die from your paltry attacks, now did you?");
    add_cact("say My my, you truly are an incompetent wretch aren't you?");
    add_cact(({"smile confidently", "say After I kill you I think I'll "+
	"torture some peasants."}));
    add_cact("say Nothing personal, but I will kill you.");
    add_cact(({"enter wall", "sneak north"}));
    set_title("the Lord of the Trading Company");

    add_speak("You didn't really come here to chat with me, now did you?\n");

    set_default_answer("The Lord says: Quit wasting my time!\n");
    add_ask(({"job"}), "The Lord says: Hehe...I'll tell you what, if you "+
      "can help me out, I can help you out.\n"+
      "The Lord grins evilly.\n");
    add_ask(({"help"}), "The Lord says: Bring me the most valuable object in "+
      "all of Kalad, and I shall see to it that you are properly rewarded.\n");
    add_ask(({"object"}), "The Lord says: I can tell you no more! Go now! "+
      "We are probably being spied on by the powers above...so hurry!\n");
    add_ask(({"powers", "power"}), "The Lord says: The ones that rule the "+
      "heavens of course! Now hurry and fetch the object for me!\n");

    set_knight_prestige(100);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

    set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
    object wep, arm;
    seteuid(getuid(TO));

    arm = clone_object(ARM + "bgcape");
    arm->move(TO);
    arm = clone_object(ARM + "bgneck");
    arm->move(TO);
    arm = clone_object(OBJ + "lord");
    arm->move(TO);
    command("wear all");
    wep = clone_object(WEP + "bgdagger");
    wep->move(TO);
    command("wield all");
    MONEY_MAKE_GC(random(20))->move(TO, 1);
}

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me = TO;
    if (random(5))
	return 0;
    hitresult = enemy->hit_me(200 + random(200), W_BLUDGEON, me, -1);
    how = " without effect";
    if (hitresult[0] > 0)
	how == "";
    if (hitresult[0] > 10)
	how = " hard";
    if (hitresult[0] > 20)
	how = " very hard";
    if (hitresult[0] > 30)
	how = " extremely hard";
    if (hitresult[0] > 40)
	how = " so hard that the sickening sound of bone ripping through "+
	"torn flesh can be heard";
    me->catch_msg("You move behind your opponent and pummel him!\n"+
      capitalize(enemy->query_pronoun()) + " is pummeled"+
      how + ".\n");
    enemy->catch_msg(QCTNAME(me) + " moves behind you and pummels you!\n"+
      "You are pummeled" + how + ".\n");
    tell_watcher(QCTNAME(me) + " pummels " + QTNAME(enemy) + "!\n"+
      capitalize(enemy->query_pronoun()) + " is pummeled" +
      how + ".\n", enemy);
    if (enemy->query_hp() <= 0)
	enemy->do_die(me);
    return 1;
}

void
tablet_return()
{
    tablet = 1;
}

void
drop_the_object(object ob)
{
    if(!ob) return;
    command("say I do not need this.");
    command("drop " + OB_NAME(ob));
}

void
remove_the_object(object ob)
{
    command("read names");
    command("cackle");
    command("shout All glory and power is now mine!!!");
    command("emote raises the large stone tablet high above his head!");
    command("emote is engulfed in a blinding flash of light!");

    if(lord=present("lord", environment(TP)))
    {
	lord->remove_object();
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if(!from || !interactive(from))
	return;
    else
	set_this_player(from);

    if(MASTER_OB(ob) != CPASS + "obj/tablet")
    {
	set_alarm(2.0, 0.0, &drop_the_object(ob));
	return;
    }

    if(from->test_bit("Kalad", 0, 2))
    {
	write(query_The_name(from) + " laughs hysterically at you.\n");
	TP->catch_msg("You don't feel more experienced.\n");
    }
    else
    {
	write("The Lord says: Ahh! You have brought the tablet to me! "+
	    "You shall be richly rewarded!\n");
	TP->catch_msg("You feel much more experienced.\n");
	TP->add_exp(25000);
	TP->set_bit(0, 2);
	seteuid(getuid(TO));
	log_file(QUEST_NAME, extract(ctime(time()), 4, 15)+ " "+
	  capitalize(TP->query_real_name()) + " rewarded with 25000 xp, "+
	  "<"+TP->query_average_stat()+"> average stats.\n");
    }

    set_alarm(2.0, 0.0, &remove_the_object(ob));
}

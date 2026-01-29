inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("eban");
    add_name("kid");
    set_race_name("human");
    set_adj("sneaky");
    add_adj("little");
    set_short("kid");
    set_long("A scraggly little child. From his unkempt appearance and the lack "+
      "of any supervising adults nearby, you surmise that the little kid must "+
      "be an orphan.\n");
    default_config_npc(25);
    set_skill(SS_WEP_KNIFE,30);
    set_skill(SS_DEFENCE,30);
    set_skill(SS_PARRY,30);
    set_skill(SS_AWARENESS,15);
    set_skill(SS_PICK_POCKET,20);
    set_alignment(-25);
    set_knight_prestige(50);
    add_speak("I am so poor and hungry...I wish someone would come to my aid.\n");
    set_default_answer(VBFC_ME("otherrespons")); 
    add_ask(({"knife","about knife","give me the knife","knife",
	"the knife","give me knife"}),VBFC("askfurther"),1);
    trig_new("%w 'says:' 'knife' %s","giveknife");
    trig_new("%w 'says:' 'knife\n' %s","giveknife");
    set_act_time(6);
    add_act("emote shifts around uncomfortably.");
    add_act("emote looks around nervously.");
    add_act("emote sits in a corner.");
    add_act("peek all");
    add_act("emote says: 'Isn't this a pretty knife?' as he shows you the keen dagger.");
    add_speak("I wish someone would aid me.\n");
    set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
    object wep;
    seteuid(getuid(TO));
    wep = clone_object("/d/Kalad/common/port/wep/gdagger");
    wep -> move(TO);
    command("wield all");
    MONEY_MAKE_CC(random(50))->move(TO,1);
}
aid(string s)
{
    notify_fail("Aid whom?\n");

    if(s!="eban"&&s!="kid")
	return 0;

    seteuid(getuid(TO));

    TP->catch_msg("You help the kid by distracting a passing citizen.\n");

    if(!TP->test_bit("Kalad",0,3))
    {
	TP->add_exp(100);
	TP->set_bit(0,3);
	TP->catch_msg("You feel more experienced!\n");
    }

    say(QCTNAME(TP)+" helps the kid by distracting a passing citizen.\n");

    set_alarm(10.0,0.0,"citizen");

    return 1;
}

citizen()
{
    tell_room(E(TO),"The kid moves behind the citizen and quickly darts away.\n");
}

string
otherrespons(string s)
{
    command("emote just sobs pitifully.");
    return "";
}

string
askfurther(string s)
{
    if(!TP->test_bit("Kalad",0,3))
    {
	command("say What do you care about me?");
	command("say What have you done for me?");
	return "";
    }
    command("say I need someone's aid.");
    return "";
}

string
giveknife(string s)
{
    object ob;
    if(!TP->test_bit("Kalad",0,3))
    {
	command("say Why should I help you?");
	command("say Aid me and I'll aid you.");
	return "";
    }
    command("emote giggles mischievously. Here ya go!");
    command("drop dagger");
}

init_living()
{
    ::init_living();
    add_action("aid","aid");
}

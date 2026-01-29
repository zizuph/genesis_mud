inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include <money.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
object shipclerk;
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("seigarl");
    add_name("shipping clerk");
    add_name("clerk");
    set_race_name("human");
    set_adj("mousy");
    add_adj("little");
    set_short("shipping clerk");
    set_long("This short, brown-haired individual looks like your typical "+
      "clerk, small, unassuming and very meek. There seems to be nothing about "+
      "him that would mark him out in a crowd, so plain and boring is his "+
      "countenance.\n");
    set_stats(({50,75,50,60,60,55}));
    set_alignment(-50);
    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_AWARENESS,50);
    set_act_time(12);
    add_act("say Can I help you?");
    add_act("say Can you help me?");
    add_act("emote stands by patiently.");
    add_act("think something");
    add_act("yawn");
    add_act("stretch");
    set_cact_time(3);
    add_cact("say May the sea swallow you whole!");
    add_cact("spit");
    add_cact("say The company shall know of this wanton act of violence!");
    add_cact("scream");
    add_speak("I'm so tired...ever since I lost that ledger I haven't "+
      "had a good night's sleep.\n");
    set_default_answer("The shipping clerk just rubs his eyes wearily.\n");
    add_ask(({"help"}),"The shipping clerk says: I really need to get "+
      "some sleep...do you think you can help me get some?\n");
    add_ask(({"sleep"}),"The shipping clerk hits himself on the temples, "+
      "apparently to keep himself awake to answer your questions, but "+
      "appearing as if he were trying to knock himself into unconsciousness.\n");
    set_knight_prestige(100);
    set_title("the Shipping Clerk");
}
hit(string s)
{
    notify_fail("What do you want to hit?\n");
    if(s!="seigarl"&&s!="clerk")
	return 0;
    seteuid(getuid(TO));
    TP->catch_msg("You hit the clerk across the temples!\n");
    if(!TP->test_bit("Kalad",0,6))
    {
	TP->add_exp(1000);
	TP->set_bit(0,6);
	TP->catch_msg("You feel more experienced!\n");
    }
    say(QCTNAME(TP)+" hits the clerk across the temples!\n");
    set_alarm(3.0,0.0,"beaten");
    return 1;
}
beaten()
{
    tell_room(E(TO),"The shipping clerk collapses, unconscious, right into a large pile of parchments.\n");
    if(shipclerk = present("seigarl",environment(TO)))
    {
	shipclerk -> remove_object();
    }
}
init_living()
{
    ::init_living();
    add_action("hit","hit");
}

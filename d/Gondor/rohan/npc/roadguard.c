/*
 *	/d/Gondor/rohan/npc/roadguard.c
 *
 *	The Rohirrim soldiers guarding the roads.
 *
 *	Last modification:
 *	Gorboth, 1-nov-1995: Added hints for mosquito bites.
 *	Olorin, 1-nov-1995:  General update.
 *	12-Feb-1997, Olorin: Inherit borderguard to define
 *                           answers to questions.
 */
#pragma strict_types

inherit "/d/Gondor/rohan/npc/borderguard.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

//	Global variables
static  int     alarm_id;

void
create_monster()
{
    set_name(({"guard","road warden","road-warden","warden"}));
    set_race_name("human");
    set_short("tall road-warden");
    set_adj(({"tall","rohirrim"}));
    set_long(BSN("This is one of the road-wardens of Rohan, patrolling "
      + "the road keeping order and looking for crooks and thieves. "
      + "He looks quite competent in fighting, as all guards get "
      + "training with the garrison once a week."));
    set_pshort("tall road-wardens");

    default_config_npc( 55 + random(16));

    set_base_stat(SS_STR, 65 + random(11));
    set_base_stat(SS_CON, 65 + random(11));

    set_alignment(250+random(250));

    set_skill(SS_WEP_SWORD, 65 + random(11));
    set_skill(SS_DEFENCE,   50);
    set_skill(SS_PARRY,     50);
    set_skill(SS_AWARENESS, 20 + random(30));

    set_chat_time(5);
    add_chat("If you see any orcs on the plains, be sure to tell me!");
    add_chat("They say that the Mouths of the Entwash are haunted!");
    add_chat("Curunir is up to no good, I am sure of it!");
    add_chat("The Riders of Rohan are a blessing upon us all.");

    set_cchat_time(3);
    add_cchat("You have no business here, scoundrel! Leave now!");
    add_cchat("When Elfhelm gets word of this, you will regret your evil deeds!");
    add_cchat("Begone, vermin!");

    set_cact_time(3);
    add_cact("peer desp");
    add_cact("shout Alarm! I am beset upon by scoundrels!");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"bite", "bites", "mosquito", "mosquitoes", "mosquito bites",
        "itch", "itches", "cure", }), VBFC_ME("ask_mosquito"));
    add_ask(({"about danger", "about dangers", "danger","dangers"}), VBFC_ME("ask_danger"));
    add_ask(({"guild","ranger","rangers"}),VBFC_ME("ask_ranger"));
    add_ask(({"road"}),VBFC_ME("ask_road"));
    add_ask(({"bands","band","valley","valleys","dunlending","dunlendings"}),
        VBFC_ME("ask_dunlendings"));
    add_ask(({"edoras","capital"}), VBFC_ME("ask_edoras"));
    add_ask(({"the plains", "plain","plains"}), VBFC_ME("ask_plains"));
    add_ask(({"advice", "help"}), VBFC_ME("ask_help"));

    add_prop(LIVE_I_NEVERKNOWN, 1);
}

public void
arm_me()
{
    FIX_EUID

    clone_object(WEP_DIR + "rosword")->move(TO);
    command("wield sword");
    clone_object(ARM_DIR + "roshield")->move(TO);
    command("wear shield");
    clone_object(ARM_DIR + "rohelm")->move(TO);
    command("wear helm");
}

void
react_poison(object tp)
{
    alarm_id = 0;

    // do not give any hint if in combat!
    if (objectp(query_attack()))
        return;

    // check if the player is still here!
    if (!present(tp, ENV(TO)))
        return;

    command("ack");
    command("peer grim " + tp->query_real_name());
    command("say Those are some mighty nasty looking mosquito bites!");
    command("ponder");
    command("say North of here there used to be a pool near some sedge"
      + " which had a special kind of mud in it.");
    command("say Rubbing that stuff on your bites would always take"
      + " care of the itch.");

    return;
}

void
test_poison(object tp)
{
    object poison;

    // Do no give a hint all the time!
    if (random(3))
        return;

    if (poison = present("poison", tp))
    {
        if (poison->query_poison_type() != "mosquito")
            return;
        // check if the alarm is already active!
        if (!alarm_id || !sizeof(get_alarm(alarm_id)))
            alarm_id = set_alarm(3.0, 0.0, &react_poison(tp));
        return;
    }

    return;
}

void
init_living()
{
    ::init_living();

    test_poison(TP);
}

/* solemnian prestige */
public int query_knight_prestige() {return (-8);}

string
ask_mosquito()
{
    object  poison;

    if (objectp(poison = present("poison", TP)) &&
        (poison->query_poison_type() == "mosquito"))
    {
        if (!alarm_id || !sizeof(get_alarm(alarm_id)))
            alarm_id = set_alarm(3.0, 0.0, &react_poison(TP));
        return "";
    }

    command("say I don't know what you are talking about, "+TP->query_race_name()+"!");
    return "";
}


/*
 *  /d/Gondor/anorien/druedain/amon-din/npc/din_guard.c
 *
 *  This is a guard getting some training atop Amon Din.
 *
 *  July 1995 by Gorboth
 */

inherit "/std/monster";
inherit "/d/Gondor/common/lib/friend_or_foe";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

string
appearance()
{
    string *looks = ({"brazen","inexperienced","brown-haired",
                      "black-haired", "scruffy", "eager", "restless",
                      "pensive","bright-eyed","quiet"});
    return ONE_OF_LIST(looks);
}

public void
create_monster()
{
    set_name("guard");
    set_pname(({"men","humans","guards","young guards"}));
    set_pshort("young guards");
    add_name(({"man", "soldier"}));
    add_adj(({"young", appearance()}));
    set_short("young guard");
    set_race_name("human");
    set_long(BSN(
        "This soldier has likely spent a number of weeks here upon"
      + " the summit of Amon Din. He looks quite young, and it may"
      + " well be that his duties atop Amon Din are part of his"
      + " training in the armies of Minas Tirith."));
    set_alignment(200+10*random(24));
    default_config_npc(random(10)+53);
    set_base_stat(SS_CON,random(10)+62);
    set_skill(SS_WEP_SWORD, random(10)+70);
    set_skill(SS_AWARENESS, 20 + random(10));
    set_skill(SS_PARRY, 85);
    set_skill(SS_DEFENCE, 85);
    
    set_chat_time(60 + random(40));
    add_chat("Blast that magpie! Always thieving our things!");
    add_chat("Did Nierman wander off again? That slouch...");
    add_chat("The wood stores have gotten quite low again.");
    add_chat("Well of course its boring, but at least we have the view.");
    add_chat("Did you hear something on the roof?");
    add_chat("Hmmm... strange that more fuel has not arrived.");
    add_chat("We can ask the attendant, he will know.");

    set_cchat_time(15 + random(10));
    add_cchat("Fool! You dare to attack this tower?");
    add_cchat("None shall meddle with the beacon signal!");
    add_cchat("Fly, ere you are thrown from the hilltop!");

    set_act_time(35 + random(15));
    add_act("time");
    add_act("stretch");
    add_act("pat guard shoulder");

    set_cact_time(10 + random(2));
    add_cact("peer desperate");
    add_cact("shout Release the pigeons! We are under attack!");
    add_cact("growl slight");
}

public void
arm_me()
{
    object  wep, arm;
    FIX_EUID
    clone_object(WEP_DIR + "lsword")->move(TO);
    command("wield all");
    clone_object(ARM_DIR + "gchainmail")->move(TO);
    clone_object(ARM_DIR + "gshield")->move(TO);
    command("wear all");
}

// Dont forget about Solamnian prestige!

void
init_attack()
{
    object  victim;

    if (objectp(query_attack()))
        return;

    if ((victim = TP)->query_npc())
        return;

    if (query_friend_or_foe(victim) > -1 || !CAN_SEE_IN_ROOM(TO) ||
        !CAN_SEE(TO, victim))
        return;

    set_alarm(2.0, 0.0, "do_attack", victim);
}

void
do_attack(object victim)
{
    command("kill "+victim->query_real_name());
}

/*
 *  /d/Gondor/minas/npc/g7_guard_out.c
 *      Modified from /d/Gondor/minas/npc/citadel_guard.c
 *      Alto, 28 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/minas/npc/mtirith_monster.c";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/minas/lib/porter_defs.h"


#define INNER_MINAS "/d/Gondor/minas"
#define GONDOR_CLOCK            ("/d/Gondor/common/obj/clock")

object actor, *inv;

public string check_visitor();


public void
create_monster()
{
    if (!IS_CLONE) return;
    seteuid(getuid());
 

    ::create_monster();

    set_name(({"guard","cityguard","guard of the citadel"}));
    set_race_name("human");
    set_short("strong guard");
    set_long("This guard is one of the Guards of the Citadel. He is robed "
        + "in black and has a strange, high-crowned helmet with wings of "
        + "seabirds set above the long, close-fitting cheek-guards. Upon his "
        + "black surcoat you can see the embroidered image of a white tree "
        + "in blossom beneath a silver crown and many-pointed stars. This is "
        + "emblem of the heirs of Elendil, and none except the Guards of "
        + "the citadel wear it now.\n");
    set_adj(({"tall","strong"}));
    set_pshort("strong guards");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);


    set_alignment(400+random(80));

    default_config_npc(random(13)+58);

    set_base_stat(SS_CON,random(14)+62);
    set_skill(SS_WEP_SWORD, random(10)+100);
    set_skill(SS_WEP_POLEARM, random(10)+100);
    set_skill(SS_PARRY,100);
    set_skill(SS_DEFENCE,100);

    clone_object(INNER_MINAS + "/obj/gate_seven_key.c")->move(TO);

    set_chat_time(11);

    add_chat("None may pass except those on the business of the Steward.");
    add_chat("A storm is coming. Let us hope the city is prepared.");
    add_chat("Do not try the patience of the Lord. He is in a fell mood "
        + "this day.");
    add_chat("What is your business here, stranger?");
    add_chat("Have you news of Faramir?");

    set_act_time(10);
    add_act("emote looks closely at you.");
    add_act("emote adjusts his surcoat.");
    add_act("emote peers carefully about the area.");
    add_act("emote adjusts his winged helm.");
    add_act("hmm");
    add_act("pace");
    add_act("sigh");

    add_ask(({"to unlock gate", "unlock gate", "gate", "open gate", "open the gate",
        "open gates", "about gate", "to unlock the gate"}), &check_visitor());


    FIX_EUID;
    clone_object(WEP_DIR + "halberd")->move(TO);
    command("wield halberd");
    clone_object(ARM_DIR + "gchainmail")->move(TO);
    command("wear chainmail");
    clone_object(ARM_DIR + "winghelm")->move(TO);
    command("wear helm");
    clone_object(OBJ_DIR + "tower_surcoat")->move(TO);
    command("wear surcoat");

}


string
tod()
{
    return ((string)GONDOR_CLOCK->query_time_of_day());
}



string
close_gate()
{
    command("close seventh gate");
    command("lock seventh gate with key");
}

void
open_gate()
{
    switch (tod())
    {
    case "night":
    case "evening":
        command("say The Gate is closed for the "+tod()+", however, "
            + "so you must return in the morning.\n");
	       return;
	       break;
    default:
	       command("say You may pass!\n");
        command("unlock seventh gate with key");
        command("open seventh gate");
        set_alarm(7.0, 0.0, &close_gate());
   	return;
   	break;
    }
}


string
check_visitor()
{
    if (TP->query_wiz_level())
    {
        command("say But of course, Wizard.");
        command("bow");
        command("unlock seventh gate with key");
        command("open seventh gate");
        set_alarm(7.0, 0.0, &close_gate());
        return "";
    }

    if ((query_friend_or_foe(TP) < 0) && (!TP->query_wiz_level()))
    {
        command("scowl " + TP->query_real_name());
        command("say You are an enemy of the city!");
        command("say Begone!");
        return "";
    }

 
    if (TP->query_prop(QUESTING_FOR_PIPPIN))
    {
        TO->command("say I cannot allow you to pass without written "
           + "permission.\n");
        TO->command("scratch head");
        return "";
    }


    if (TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_PORTER_BIT))
    {
        TO->command("say I remember you, because you have provided "
          + "useful service to the Steward in the past.");
        set_alarm(1.0, 0.0, &open_gate());
        return "";
    }
  


    else
    {
        command("peer" + TP->query_real_name());
        command("say You have no business with the Steward. Begone!");
        return "";
    }
}



void
give_it_back(object ob, object from)
{
    string what, who;
    what = (ob->query_name());
    who = from->query_real_name();
    command("give " + what + " to " + who);
    command("say I have no interest in your things. Begone!");
}

void
return_note(object ob, object from)
{
    string what, who;
    what = (ob->query_short());
    who = from->query_real_name();

    if (from->query_prop(QUESTING_FOR_PIPPIN))
    {
        command("give " + what + " to " + who);
        set_alarm(2.0, 0.0, &command("say Ahh. Your permissions check out."));
        set_alarm(5.0, 0.0, &open_gate());
        return;
    }

    else
    {
        command("peer " + who);
        command("say You do not look the sort our Porter would trust. "
            + "Where did you get this? Begone!");
        return;
    }
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!objectp(from))
    {
    return;
    }

    if (ob->id("_stable_quest_note_"))
    {
        set_alarm(1.0, 0.0, &return_note(ob, from));
        return;
    }
    set_alarm(1.0, 0.0, &give_it_back(ob, from));
}





/* Knights will loose prestige on this one */
public int query_knight_prestige() { return -8; }


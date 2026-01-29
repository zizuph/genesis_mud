/*
 *   /d/Gondor/minas/npc/porter_noquest.c
 *
 *   The Porter at the Fen Hollen - pre fall of Isengard version.
 *
 *   Alto, 22 April 2001
 *
 */


#pragma strict_types

inherit "/d/Gondor/minas/npc/std_gondor_guard.c";
inherit "/std/act/action.c";
inherit "/std/act/domove";
inherit "/std/act/attack";


#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/lib/porter_defs.h"

#define INNER_MINAS "/d/Gondor/minas"

public void    give_key();

public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());
 

    ::create_monster();
    set_adj("vigilant");
    set_adj("grim-faced");
    set_living_name("fergil");
    set_name("Fergil");
    add_name("porter");
    add_name("fergil");
    add_name("guard");
    set_title("the Porter of the Fen Hollen");
    set_long("This is the Porter of the Fen Hollen. He stands "
        + "before the Closed Door to ensure that only the Lord "
        + "of the City or those bearing the token of the tombs "
        + "may pass beyond to the Houses of the Dead.\n");

    rnd = random(60);
    default_config_npc(120+rnd/2);
    set_base_stat(SS_DIS, 140 + rnd);
    set_alignment(350+rnd*10);
    set_skill(SS_WEP_SWORD, MIN(100, 75 + rnd));
    set_skill(SS_WEP_POLEARM, MIN(100, 75 + rnd));
    set_skill(SS_WEP_CLUB, MIN(100, 75 + rnd));
    set_skill(SS_WEP_AXE, MIN(100, 75 + rnd));
    set_skill(SS_WEP_KNIFE, MIN(100, 75 + rnd));
    set_skill(SS_PARRY, MIN(100, 75 + rnd));
    set_skill(SS_DEFENCE, MIN(100, 75 + rnd));
    add_prop(CONT_I_HEIGHT,170+rnd);
    add_prop(CONT_I_WEIGHT,85000+rnd*500);
    add_prop(CONT_I_VOLUME,80000+rnd*500); 

    clone_object(INNER_MINAS + "/obj/fen_hollen_key.c")->move(TO);
   
    set_chat_time(15);
    add_chat("There really is not much for me to do unless there is "
        + "a funeral.");
    add_chat("What a boring job I have. I would rather be up fighting "
        + "that traitor Saruman!");
    add_chat("The last time we had much business here was when old "
        + "Ecthelion died some thirty years back.");
    add_chat("You may not pass the Fen Hollen without a token of "
        + "the tombs.");

    set_cchat_time(5);
    add_cchat("Guards! Raise the alarm!");
    add_cchat("You will not pass, I say!");
    add_cchat("How dare you attempt the sanctity of the Hallows!");

    set_act_time(16);
    add_act("hmm");
    add_act("pace");
    add_act("sigh");

    add_ask_item(({"key", "for key"}), "@@give_key");
    add_ask_item(({"task", "quest", "help", "favour"}), "say Sorry, "
        + "I don't really need any help at the moment.");
    add_ask_item(({"firewood", "about firewood"}), "say Sorry, "
        + "I don't really need any help at the moment.");

    set_default_answer( ({ "say Excuse me?", "cough incoherently" }) );


    /* formerly QUEST related add_asks */

    add_ask_item(({"halfling", "hobbit"}), "say What is a hobbit?");
    add_ask_item(({"door", "fen hollen"}), "say This is the Closed Door, and "
        + "I am under orders to open it only for the Lord of the City or "
        + "those who bear the Token of the Tombs.");
    add_ask_item(({"lord of the city", "steward", "denethor"}), "say Lord "
        + "Denethor II is a wise and noble ruler. Some say he sees that "
        + "which lesser folk such as you and I cannot.");
    add_ask_item(({"city", "minas tirith", "sixth circle", "circle"}), "say "
        + "You must be a stranger here! This is the Sixth Circle of the "
        + "city of Minas Tirith. There are many things to see in the city, "
        + "although as the storm of war approaches most of us have little "
        + "time for leisure and sightseeing. I am surprised you do not know "
        + "this already, if Hunthor entrusted you with the password to this "
        + "circle!");
    add_ask_item(({"storm", "war"}), "say Have you been asleep for the past few "
        + "years? It is time to awaken! The eastern menace grows ever stronger, "
        + "and dark clouds gather upon that horizon.");
    add_ask_item(({"password", "passwords"}), "say If you do not know them, it is "
        + "not for me to share them with you. Go see Hunthor!");
    add_ask_item(({"hunthor"}), "say If you got this far into the city without "
        + "meeting him, you must be here by illegal means! Begone ere I fetch "
        + "the guards!");
    add_ask_item(({"stablemaster"}), "say Stablemaster Geradan? Yes, he is a good "
        + "friend of mine!");
    add_ask_item(({"shelf", "amon-din", "Amon-Din", "bundle", "watchtower",
        "storeroom"}), 
        "say The watchtower of Amon-Din lies to the northwest of the City.");
    add_ask_item(({"library", "city library", "City Library"}), "say Yes, "
        + "there is a great library in Minas Tirith. It is not in this circle, "
        + "however.");


    remove_prop(LIVE_I_NEVERKNOWN);

}


public void
return_giggle(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
    return;

    switch (random(3))
    {
    case 0:
        command("say Please conduct yourself in a respectful manner.");
        break;
    case 1:
        command("peer . "+ actor->query_real_name());
        break;
    case 2:
        command("scowl . " + actor->query_real_name());
        break;
    default:
        break;
    }
}

public void
return_laugh(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
  	 return;

    switch (random(3))
    {
    case 0:
        command("say Please show more respect for our dead Lords.");
	       break;
    case 1:
	       command("frown . " + actor->query_real_name());
	       break;
    case 2:
        command("say It is not proper to laugh so near Hallows.");
	       command("sigh .");
	       break;
    default:
        break;
    }
}

public void
emote_hook(string emote, object actor, string adverb = 0)
{
    if (!objectp(actor) || !interactive(actor))
        return 0;

    switch (emote)
        {
        case "giggle":
	           set_alarm(2.0, 0.0, &return_giggle(actor));
	           break;
        case "laugh":
	           set_alarm(2.0, 0.0, &return_laugh(actor));
	           break;
    }
}

void
return_introduce(object pl)
{
    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    command("introduce me to "+pl->query_real_name());
    return;
}

void
add_introduced(string who)
{
    object  pl = find_player(LOW(who));

    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    set_alarm(3.0, 0.0, &return_introduce(pl));
    return;
}


string
give_key()
{
    if (TP->query_wiz_level())
    {
        command("say But of course, Wizard.");
        command("bow");
        command("give key to " + TP->query_real_name());
        clone_object(INNER_MINAS + "/obj/fen_hollen_key.c")->move(TO);
        return "";
        
    }

    else
    {
        command("peer " + TP->query_real_name());
        command("say Do you bear the Token of the Tombs? Begone!");
    }
    return "";
}


void
init_attack()
{
    object  victim;

    if (objectp(query_attack()))
        return;

    if ((victim = TP)->query_npc())
        return;

    set_alarm(2.0, 0.0, "lock_door", victim);
}

string
lock_door()
{
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
        return "";

    if (TP->query_wiz_level())
    {
        command("say Greetings, Wizard.");
        command("bow " + TP->query_real_name());
        command("close door");
        command("lock door with key");
        
    }
    else
    {
        command("say Greetings.");
        command("close door");
        command("lock door with key");
    }
    return "";
}


public int
query_knight_prestige() { return -30; }


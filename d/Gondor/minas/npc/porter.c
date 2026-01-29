/*
 *   /d/Gondor/minas/npc/porter.c
 *
 *   The Porter at the Fen Hollen.
 *
 *   Alto, 22 April 2001
 *
 *   Quest code structure borrowed in part from Gwyneth
 *
 */


#pragma strict_types

inherit "/d/Gondor/minas/npc/std_gondor_guard.c";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/std/act/action.c";
inherit "/std/act/domove";
inherit "/std/act/attack";


#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <math.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/minas/lib/porter_defs.h"

#define INNER_MINAS "/d/Gondor/minas"

#define AREA_IDENT            92876243
#define AREA_RANGE            15

public void    give_key();
public string  send_pippin();
public string  send_firewood();
public string  send_hallows();
void           accept_key(object ob, object from);

int quest_in_progress = 0;
int denethor_in_progress = 0;

string *prooms = ({INNER_MINAS + "/citadel/north_lane1.c",
INNER_MINAS + "/citadel/north_lane2.c",
INNER_MINAS + "/citadel/north_lane3.c",
INNER_MINAS + "/citadel/north_lane4.c",
INNER_MINAS + "/citadel/north_lane5.c",
INNER_MINAS + "/citadel/north_lane6.c",
INNER_MINAS + "/citadel/north_lane7.c",
INNER_MINAS + "/citadel/south_lane1.c",
INNER_MINAS + "/citadel/south_lane2.c",
INNER_MINAS + "/citadel/south_lane3.c",
INNER_MINAS + "/citadel/south_lane4.c",
INNER_MINAS + "/citadel/south_lane5.c",
INNER_MINAS + "/citadel/south_lane6.c",
INNER_MINAS + "/citadel/battlement1.c",
INNER_MINAS + "/citadel/battlement10.c"});

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
    add_chat("Where is that halfling?");
    add_chat("I could really use some help. The Steward does not like "
        + "to be kept waiting.");
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
    add_ask_item(({"task", "quest", "help", "favour"}), "@@send_pippin");
    add_ask_item(({"firewood", "about firewood"}), "@@send_firewood");

    set_default_answer( ({ "say Excuse me?", "cough incoherently" }) );


    /* QUEST related add_asks */

    add_ask_item(({"halfling", "hobbit"}), "say Aye, a short little fellow "
        + "that they say the Steward has taken into his own service! Have "
        + "you seen him? He was supposed to help me with something.");
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
        + "friend of mine! I owe him a favour!");
    add_ask_item(({"shelf", "amon-din", "Amon-Din", "bundle", "watchtower",
        "storeroom"}), 
        "say The watchtower of Amon-Din lies to the northwest of the City.");
    add_ask_item(({"library", "city library", "City Library"}), "say Yes, "
        + "there is a great library in Minas Tirith. It is not in this circle, "
        + "however.");


    remove_prop(LIVE_I_NEVERKNOWN);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);


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

    if (TP->query_prop(QUESTING_FOR_HALLOWS))
    {
        command("say I already gave you a key! Did you lose it?");
        command("growl");
        return "";
    }


    if (TP->query_prop(FOUND_DENETHOR_BUNDLE))
    {
        set_alarm(1.0, 0.0, &send_hallows());
        return "";
    }

    else
    {
        command("peer " + TP->query_real_name());
        command("say Do you bear the Token of the Tombs? Begone!");
    }
    return "";
}


string
send_pippin()
{
    string pname, area;
    object player;
    int area_loc;

    player = this_player();
    pname = TP->query_real_name();
    area_loc = NAME_TO_RANDOM(pname, AREA_IDENT, AREA_RANGE);

    if ((query_friend_or_foe(TP) < 0) && (!TP->query_wiz_level()))
    {
        command("scowl " + TP->query_real_name());
        command("say You are an enemy of the city!");
        command("say Begone lest I call the guards!");
        return "";
    }

    if (TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_OAT_BIT))
    {
        TO->command("say Hmm. Well there was the matter of getting "
            + "firewood. Ask me about it sometime.");
        return "";
    }

    if (TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_PORTER_BIT))
    {
        TO->command("say Hmm. At the moment I do not require more help, "
            + "but I may need some in the future.");
        return "";
    }

    if (TP->query_prop(QUESTING_FOR_PIPPIN))
    {
        TO->command("say Did you find that halfling yet? No doubt the "
            + "Stablemaster can use his help! If the halfling will not "
            + "do it, I do not know who else can be spared from the war "
            + "efforts to take his place.");
        TO->command("sigh");
        return "";
    }


    if(quest_in_progress)
        TO->command("say I already sent someone else to look for him. "
            + "Perhaps you will turn out to be a better messenger.");

    TO->command("grumble");
    set_alarm(2.0, 0.0, &command("say A Prince of the Halflings arrived "
        + "in the city some days ago along with that strange old man "
        + "Mithrandir. From what I hear, and I heard it from a reliable "
        + "source, they were both borne on the back of a Mearas! And here "
        + "I thought those horses would only carry the King of Rohan!"));
    set_alarm(7.0, 0.0, &command("say That very same day, from what I "
        + "heard, the Lord Steward took the halfling to be in his own "
        + "Tower Guard. For a little fellow, he must be a mighty warrior! "
        + "Rumour has it that the Rohirrim are on their way, each with "
        + "a halfling on the back of his mount."));
    set_alarm(11.0, 0.0, &command("scratch head"));
    set_alarm(12.0, 0.0, &command("say Word came down from the tower this "
        + "morning that the little fellow was to do some work for me "
        + "today. I sent back up that I had a job for him, but here it is "
        + "many hours later and I have yet to see him!"));
    set_alarm(17.0, 0.0, &command("say Since you seem so interested, "
        + "I suspect you would be willing to at least deliver a message "
        + "to the halfling for me."));

    setuid();
    seteuid(getuid());
    clone_object(INNER_MINAS + "/obj/pippin_note.c")->move(TP);

    set_alarm(22.0, 0.0, &command("say Here is a missive for "
        + "the guards at the Seventh Gate. "
        + "Present it to them and they will let you pass. No doubt that "
        + "halfling is loitering somewhere about the place. Ask him about "
        + "Fergil the Porter to jog his memory."));

    TP->add_prop(QUESTING_FOR_PIPPIN, 1);

    set_alarm (25.0, 0.0, &player->catch_tell("Fergil scribbles a few words "
        + "onto a sheet of paper "
        + "and hands you a small missive.\n"));
    set_alarm (25.0, 0.0, &tell_room(environment(), "Fergil "
        + "scribbles a few words onto a sheet "
        + "of paper and hands " + QTNAME(TP) + " a small missive.\n", player));

    set_alarm(27.0, 0.0, &command("sigh"));

    setuid();
    seteuid(getuid());

    if(file_size(prooms[area_loc]) != -1)
    {
        prooms[area_loc]->teleledningsanka();
        if(!present("_stable_quest_hedge_", find_object(prooms[area_loc])))
        {
        clone_object(INNER_MINAS + "/obj/squest_hedge.c")->move(prooms[area_loc]);

        quest_in_progress = 1;
        }
    }
    else
        return "Quest failed to load. Please make a bug report.\n";

    return "";
}

string
send_firewood()
{
    object player;

    player = this_player();

    if ((query_friend_or_foe(TP) < 0) && (!TP->query_wiz_level()))
    {
        command("scowl " + TP->query_real_name());
        command("say You are an enemy of the city!");
        command("say Begone lest I call the guards!");
        return "";
    }

    if (!TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_OAT_BIT))
    {
        TO->command("say I believe my friend Geradan the Stablemaster "
            + "could use your help more than I can. Why don't you help "
            + "him first and then come back when you are finished?");
        return "";
    }
  

    if (TP->query_prop(QUESTING_FOR_BUNDLE))
    {
        command("say What are you waiting for? The Steward is not a "
            + "patient man in these dark times!");
        return "";
    }

    if (TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_DENETHOR_BIT))
    {
        TO->command("say Hmm. I do not seem to need any more help at "
            + "the moment. Perhaps you should go arm yourself for the "
            + "coming war!");
        return "";
    }
  

    if(denethor_in_progress)
        TO->command("say I already sent someone else to fetch some firewood, "
            + "but maybe you will be a little quicker to bring them "
            + "back.");

    TO->command("scratch");
    set_alarm(2.0, 0.0, &command("say I'm glad Geradan sent you my way. "
        + "You see, the Steward has sent down orders that a Servant of the "
        + "Tombs should fetch a large bundle of firewood "
        + "from the storage room at "
        + "Amon-Din and place it on his tomb."));
    set_alarm(7.0, 0.0, &command("boggle"));
    set_alarm(8.0, 0.0, &command("say A strange request to be sure, but these "
        + "are strange, dark times. It is not my place to question the wisdom "
        + "of the Ruling Steward."));
    set_alarm(12.0, 0.0, &command("worry"));
    set_alarm(13.0, 0.0, &command("say Trouble is, none of the Tombkeepers "
        + "are on duty today. With the war coming they are all busy with "
        + "other things. I, of course, cannot leave my post here at the Fen "
        + "Hollen."));
    set_alarm(18.0, 0.0, &command("say I would deeply appreciate your "
        + "help, friend. Geradan tells me you did a fine job filling in for "
        + "that halfling, and I need a trustworthy person for this "
        + "undertaking."));
    set_alarm(22.0, 0.0, &command("ponder"));
    set_alarm(23.0, 0.0, &command("say You should find a large bundle of "
        + "wood on a shelf in the storeroom at Amon-Din. When you have fetched "
        + "it, come back here and ask me for a key. I'll tell you exactly "
        + "where to put the bundle when you get back."));

    TP->add_prop(QUESTING_FOR_BUNDLE, 1);
    START_QUEST(TP, "MTIRITH DENETHOR QUEST");

    denethor_in_progress = 1;

    return "";
}


string
send_hallows()
{
    object player;

    player = this_player();


    TO->command("nod");
    set_alarm(2.0, 0.0, &command("say Ah, good. You found the storeroom. "
        + "If it is not too much trouble, I would like to deputize you as "
        + "a Servant of the Tombs. Then you can take the bundle down to the "
        + "House of Stewards and place it on the tomb of Denethor II."));
    set_alarm(7.0, 0.0, &command("think"));
    set_alarm(8.0, 0.0, &command("say I must warn you, though, such service "
        + "is not to be taken lightly. Servants of the Tombs are expected "
        + "to be of the highest calibre and honour. They are also expected "
        + "to know the lore and history of Gondor exceedingly well. Perhaps, "
        + "if "
        + "you do not know our history, you should visit the City Library. "
        + "There are several books there that will fill you in."));
    set_alarm(12.0, 0.0, &command("ponder"));
    set_alarm(13.0, 0.0, &command("say All Servants of the Tombs bear a "
        + "special token. Here is a Token of the Tombs. Keep it with you at "
        + "all times!"));

    setuid();
    seteuid(getuid());

    clone_object(INNER_MINAS + "/obj/tomb_token.c")->move(TP);

    set_alarm(15.0, 0.0, &player->catch_tell("The Porter hands you a shiny "
        + "metal token.\n"));
    set_alarm(15.0, 0.0, &tell_room(environment(), "The Porter hands " 
        + QTNAME(TP) + " a shiny metal token.\n", player));

    set_alarm(18.0, 0.0, &command("say I will also entrust you with a "
        + "key to the Fen Hollen. Please give it back to me when you have "
        + "completed your duties."));

    clone_object(INNER_MINAS + "/obj/fen_hollen_key.c")->move(TP);

    set_alarm(20.0, 0.0, &player->catch_tell("The Porter hands you a large "
        + "iron key.\n"));
    set_alarm(20.0, 0.0, &tell_room(environment(), "The Porter hands " 
        + QTNAME(TP) + " a large iron key.\n", player));

    set_alarm(22.0, 0.0, &command("say Remember, you must know the lore of "
        + "Gondor well, Servant of the Tombs."));

    set_alarm(23.0, 0.0, &command("bow"));

    TP->add_prop(QUESTING_FOR_HALLOWS, 1);

    return "";
}

void
accept_key(object ob, object from)
{
    string who;
    who = from->query_real_name();

    if (from->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_DENETHOR_BIT))
    {
        TO->command("say Hmm. I'm not sure where you got this, but you "
            + "you have no business with it now.");
        return;
    }

    if (from->query_prop(DELIVERED_DENETHOR_BUNDLE))
    {
    command("say Ah! You look as though you have seen a ghost!");
    set_alarm(1.0, 0.0, &command("chuckle"));
    set_alarm(2.0, 0.0, &command("say Thank you, Servant of the Tombs. With "
        + "folk as trusty as you in the Kingdom, there is hope we may yet "
        + "prevail."));
    set_alarm(5.0, 0.0, &command("smile gratefully"));

    from->add_prop(SENT_TO_DENETHOR, 1);

    set_alarm(7.0, 0.0, &command("say I am certain the Steward would like "
        + "to reward you in person. Ask the guards of the White Tower to open "
        + "the doors and you will be admitted. You will find Steward Denethor "
        + "in the throne room. Please ask him for your reward."));
    set_alarm(9.0, 0.0, &command("say Be well, friend."));
    set_alarm(10.0, 0.0, &command("bow"));
    return;
    }

    else
    {
    command("say Where did you get this? I'll just keep it!");
    return;

    }
}


void
give_it_back(object ob, object from)
{
    string what, who;
    what = (ob->query_name());
    who = from->query_real_name();
    command("give " + what + " to " + who);
    command("say I have no interest in such things!");
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!objectp(from))
    {
    return;
    }

    if (ob->id("_fen_hollen_key_"))
    {
        set_alarm(1.0, 0.0, &accept_key(ob, from));
        return;
    }
    set_alarm(1.0, 0.0, &give_it_back(ob, from));
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


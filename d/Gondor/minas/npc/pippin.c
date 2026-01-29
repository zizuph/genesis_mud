/* 
 * /d/Gondor/minas/npc/pippin.c  
 *
 * Peregrin Took of the Tower Guard
 *
 * Alto, 20 April 2001
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

object actor, *inv;

public string send_stable();

public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());

    set_adj("tall");
    add_adj("impertinent");
    set_living_name("peregrin");
    set_name("Peregrin");
    set_pname("hobbits");
    add_name("hobbit");
    add_name("halfling");
    add_name("peregrin");
    add_name("pippin");
    set_race_name("hobbit");
    set_title("son of Paladin, Guard of the Citadel");

    set_long("This hobbit is unusual in many regards. He is uncommonly "
        + "tall for a hobbit. He is also the only one of his kind to be "
        + "found in Minas Tirith. It also seems strange to see a halfling "
        + "dressed in the livery of Elendil, which clearly marks him "
        + "as a soldier in the elite Tower Guard. He sits upon the stone "
        + "bench dangling his legs.\n");

    rnd = random(60);
    default_config_npc(150+rnd/2);
    set_base_stat(SS_DIS, 150 + rnd);
    set_alignment(300+rnd*10);

    set_gender(0);
    set_skill(SS_WEP_SWORD,100+random(10));
    set_skill(SS_DEFENCE,100+random(10));
    set_skill(SS_PARRY,100+random(10));

    remove_prop(LIVE_I_NEVERKNOWN);

    set_chat_time(5);
    add_chat("How I should like a nice breakfast. Do these people ever "
        + "have it, or is it over? And when do they have dinner, and "
        + "where?");
    add_chat("I am little more than a boy in the reckoning of my own "
        + "people, and it will be four years yet before I come of age, "
        + "as we say in the Shire.");
    add_chat("I know of Black Riders. I will not speak of them now, so "
        + "near, so near.");
    add_chat("I am no warrior at all and dislike any thought of battle; "
        + "but waiting on the edge of one I can't escape is worst of "
        + "all.");
    add_chat("I left my best friend behind in Rohan, and I have no one "
        + "to talk or jest with.");
    add_chat("I hope the Porter has not grown impatient with me. He "
        + "will hopefully understand why I am late to return.");
    add_chat("These gulls are such annoying creatures, always begging "
        + "for food. Say, you wouldn't happen to have a spare sandwich "
        + "would you?");
    add_chat("Be careful near that embrasure!");
    add_chat("I could really use some help. Are you busy?");
    add_chat("Beware the Huorns! Even Isengard could not withstand "
        + "them when they became aroused.");


    set_act_time(6);
    add_act("emote scans the environment.");
    add_act("emote pats his rumbling tummy and sighs.");
    add_act("emote studies the clouds moving in from the east and "
        + "shivers.");
    add_act("emote adjusts his winged helm.");
    add_act("emote nibbles on a bit of cheese.");
    add_act("emote bites into an apple.");
    add_act("emote spreads a little butter onto a slice of bread.");
    add_act("emote strokes the hair on his feet absentmindedly.");
    add_act("emote dangles his hairy feet from the stone seat.");

    set_cact_time(2);
    add_cact("emote plants his feet wide apart and holds his shortsword "
        + "ready.");
    add_cact("emote shouts: For Gondor and the Shire!");
    add_cact("emote drops his shortsword and quicky picks it up again.");
    add_cact("emote tries to get his helmet out of his eyes.");

    set_default_answer( ({ "say Excuse me?", "cough incoherently" }) );

    add_ask_item(({"embrasure", "battlement"}), "say This is a "
        + "magnificent place "
        + "to take in the scenery and get a sniff of air. You can also "
        + "learn much about the general area if you scan the environment.");
    add_ask_item(({"breakfast", "dinner"}), "say Don't remind me! I am "
        + "about to "
        + "faint from undernourishment as it is!");
    add_ask_item(({"apple", "cheese", "butter", "slice", "bread"}), "say Oh, "
        + "this? Uh, you see, I .. er .. well that is I found this sitting "
        + "right here on this very bench! How sad it might have been to "
        + "let it go to waste!");
    add_ask_item(({"riders", "black riders", "nazgul"}), "say Do not ask "
        + "me to speak "
        + "of such things! They are near .. so near.");
    add_ask_item(({"battle", "war"}), "say War is drawing nigh. Scan "
        + "the environment "
        + "and see for yourself!");
    add_ask_item(({"friend", "best friend", "rohan", "merry", "meriadoc"}), 
        "say He "
        + "has been left behind in Rohan. Gandalf and I, well, we had to "
        + "leave in rather a hurry. Hopefully he is well, and not as lonely "
        + "as me.");
    add_ask_item(({"gandalf", "mithrandir"}), "say Gandalf? Do you "
        + "not know of him? "
        + "Of course the Big Folk and the Elves seem to always call him "
        + "Mithrandir. In any case, he is a mystery to most people, and even "
        + "though I have spent many months with him, I know him little "
        + "better. I feel, however, that he has something very important to "
        + "do in the coming war.");
    add_ask_item(({"gulls", "gull"}), "say Annoying, aren't "
        + "they?  Always begging for "
        + "food. Did I ask you about a sandwich, by the way?");
    add_ask_item(({"sandwich"}), "say Yes, do you have one?");
    add_ask_item(({"huorn", "huorns"}), "say Huorns are tall creatures "
        + "that seem more tree than person, but they can be extremely "
        + "dangerous when aroused! Don't be cutting the trees in their care! "
        + "They become very aroused when someone cuts a tree in the land of "
        + "the Ents.");
    add_ask_item(({"ents", "land of the ents"}), "say Huorns are a type of Ent. "
        + "They live in the forest of Fangorn, and sometimes can be found "
        + "in the Entwash.");
    add_ask_item(({"isengard", "saruman", "orthanc"}), "say The Ents control "
        + "Isengard now. They "
        + "have Saruman cooped up in his tower, Orthanc, and I wonder if they "
        + "will ever let him come down?");

    /* quest related asks */

    add_ask_item(({"porter", "porter of fen hollen", "fergil", "fergil the porter",
        "Fergil the Porter", "Fergil", "quest", "help", "task", "job"}),
        "@@send_stable");

    FIX_EUID;
    clone_object(INNER_MINAS + "/obj/pippin_sword")->move(TO);
    clone_object(ARM_DIR + "gchainmail")->move(TO);
    clone_object(ARM_DIR + "winghelm")->move(TO);
    clone_object(OBJ_DIR + "tower_surcoat")->move(TO);
    command("wear all");
    command("wield all");

}


public void
return_smile(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
    return;

    switch (random(3))
    {
    case 0:
        command("say How pleasant to see a happy face amid all these "
            + "grim-faced Big People!");
        break;
    case 1:
        command("smile . "+ actor->query_real_name());
        break;
    case 2:
        command("shake . " + actor->query_real_name());
        command("say A smile is always a welcome guest, as we say in "
            + "the Shire.");
        break;
    default:
        break;
    }
}

public void
return_grin(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
  	 return;

    switch (random(3))
    {
    case 0:
        command("say My dear friend Merry often grins just like that. "
            + "How I do miss him.");
        command("sigh .");
	       break;
    case 1:
	       command("tickle . " + actor->query_real_name());
	       break;
    case 2:
        command("say You seem very pleased with yourself!");
	       command("smile .");
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
        case "smile":
	           set_alarm(2.0, 0.0, &return_smile(actor));
	           break;
        case "grin":
	           set_alarm(2.0, 0.0, &return_grin(actor));
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

void
init_attack()
{
    object  victim;

    if (objectp(query_attack()))
        return;

    if ((victim = TP)->query_npc())
        return;

    set_alarm(2.0, 0.0, "sit_down", victim);
}

string
sit_down()
{
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
        return "";

    if (TP->query_wiz_level())
    {
        command("say Greetings, Wizard.");
        command("bow " + TP->query_real_name());
        command("sit seat");
        
    }
    else
    {
        command("say Hullo there! Won't you join me for a sniff of air?");
        command("sit seat");
    }
    return "";
}

string
send_stable()
{
    string pname;

    pname = TP->query_real_name();

    if ((query_friend_or_foe(TP) < 0) && (!TP->query_wiz_level()))
    {
        command("scowl " + TP->query_real_name());
        command("say You do not look the sort Fergil would send!");
        command("say Begone lest I call the guards!");
        return "";
    }

    if (TP->query_prop(QUESTING_FOR_GERADAN))
    {
        command("say Did you find the stables yet? I believe they are "
            + "somewhere on the Sixth Circle.");
        return "";
    }

    if (TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_PORTER_BIT))
    {
        TO->command("say Hmm. I do not seem to need any more help at "
            + "the moment. Perhaps you should go arm yourself for the "
            + "coming war!");
        return "";
    }
  

    if (TP->query_prop(QUESTING_FOR_PIPPIN))
    {
        command("say Ah yes, Fergil! Did he send you? No doubt he must "
            + "be growing very impatient with me.");
        set_alarm(2.0, 0.0, &command("blush"));
        set_alarm(5.0, 0.0, &command("say You see, the Prince of Dol "
            + "Amroth is expected to arrive soon, and I so very much do "
            + "not wish to miss the spectacle."));
        set_alarm(10.0, 0.0, &command("say I suppose I should give it up, "
            + "though, and do what my new duties demand."));
        set_alarm(12.0, 0.0, &command("sigh"));
        set_alarm(14.0, 0.0, &command("peer . " + pname));
        set_alarm(16.0, 0.0, &command("say Say, would you be willing to "
            + "help me out? I would be eternally grateful. Of course you "
            + "would. You look like such a kind person!"));
        set_alarm(20.0, 0.0, &command("say It is a small favour, really, "
            + "and should not take too much of your time. If you would "
            + "kindly visit Geradan, the Stablemaster of the Royal "
            + "Stables, he will put you right to work! Just ask him about "
            + "me, and he will figure out that you are there in my "
            + "place."));
 
        TP->add_prop(QUESTING_FOR_GERADAN, 1);

        set_alarm(25.0, 0.0, &command("say Oh, and if it is not too much "
            + "trouble, could you go right away? I am rather overdue!"));
        set_alarm(27.0, 0.0, &command("wave . " + pname));
        set_alarm(28.0, 0.0, &command("emote scans the environment."));


        return "";
    }

    else
        command("say I am sorry, I do not believe I know what you are "
            + "talking about.");

    return "";
}

public int
query_knight_prestige() { return -40; }


/*
 *   /d/Gondor/minas/npc/stablemaster.c
 *
 *   The Master of the Royal Stables.
 *
 *   Alto, 16 April 2001
 */


#pragma strict_types

inherit "/d/Gondor/minas/npc/std_gondor_guard.c";
inherit "/d/Gondor/common/lib/binbit.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/minas/lib/porter_defs.h"

#define WEP_ARRAY1 ({WEP_DIR + "dlongsword"})
#define WEP_ARRAY2 ({ARM_DIR + "gshield" })
#define ARM_ARRAY1 ({ARM_DIR + "ghelmet"})
#define ARM_ARRAY2 ({ARM_DIR + "schainmail"})

#define INNER_MINAS "/d/Gondor/minas"
#define OAT_QUEST_LOG ("/d/Gondor/minas/lib/oat_quest_log")


string       groom_horses();
void         reward_groom(object from);
void         give_it_back(object ob, object from);
void         accept_brush(object ob, object from);
string       find_oats();
string       ask_firewood();

int oat_in_progress = 0;



public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());
 

    ::create_monster();
    set_adj("good-natured");
    set_adj("dusty");
    set_living_name("geradan");
    set_name("Geradan");
    add_name("stablemaster");
    add_name("geradan");
    add_name("master");
    set_title("the Master of the Royal Stables");
    set_long("This is the Master of the Royal Stables. He is "
        + "entrusted with the care of the horses stabled here. "
        + "Born and raised on a farm in the Lossarnach, this "
        + "groom knows more about equestrian lore than any other in "
        + "the kingdom.\n");

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

    clone_object(INNER_MINAS + "/obj/horse_whip.c")->move(TO);


    set_chat_time(15);
    add_chat("Welcome! Do you have a horse that needs stabling?");
    add_chat("Where is that errand-boy with my oats?");
    add_chat("Not often we get a mearas in the stables. This one "
        + "is so regal he must be their Lord!");
    add_chat("We keep the north stable ever-ready for the return "
        + "of the King.");
    add_chat("If you are just going to stand there gawking, why "
        + "not be of some use! These horses could stand some grooming.");

    set_cchat_time(5);
    add_cchat("Guards! Raise the alarm!");
    add_cchat("If you leave now I may decide against killing you!");
    add_cchat("For Gondor!");

    set_act_time(7);
    add_act("grin");
    add_act("chuckle");
    add_act("smile");
    add_act("crack whip");
    add_act("emote picks a prickly green stem from the "
        + "seat of his trousers.");
    add_act("emote mutters about the greenery being too close to the paths "
        + "around here.");


    remove_prop(LIVE_I_NEVERKNOWN);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);


    set_default_answer( ({ "say Excuse me?", "cough incoherently" }) );


    add_ask_item(({"horse", "horses"}), "say This is where the riders of the "
        + "Steward stable their horses. None are in at the moment, "
        + "but we do have two very special horses stabled here.");
    add_ask_item(({"mearas", "shadowfax", "Shadowfax"}), "say Shadowfax is one "
        + "of the mightiest horses, in fact THE mightiest horse I have "
        + "ever seen. And I have seen the best of best from here to the "
        + "furthest plains of Rohan!");
    add_ask_item(({"north stable"}), "say We keep the stable to the north always "
        + "clean, with fresh straw and water, so that it will be ready for "
        + "the mount of the King, should he return.");
    add_ask_item(({"stem", "greenery", "paths", "path"}), "say Oh, I was walking "
        + "a path early this morning, minding my own business, when a hedge "
        + "suddenly tripped me! Er, well, at least that is how I think "
        + "it happened. I had a wee too much to drink last night.");
    add_ask_item(({"drink"}), "say Do you have any?");
    add_ask_item(({"whip"}), "say If these horses do not get groomed soon, I "
        + "am going to apply it to the backside of my lazy assistants!");
    add_ask_item(({"assistant", "assistants"}), "say You certainly do not see "
        + "them around here working! Perhaps they are all sleeping off "
        + "the spirits from last night. We did stay at the tavern rather "
        + "late! Pity though, as I could really use some help.");
    add_ask_item(({"hair", "horse hair"}), "say It gets into everything! "
        + "Between that and the dust, we stablehands find ourselves in "
        + "need of a good bath by the end of the day.");
    add_ask_item(({"dust"}), "say The horses kick up the dirt in here when "
        + "they exercise, and as a result no grass will really grow here. "
        + "Without grass to hold the soil together, it pretty much stays "
        + "dusty. Except, of course, when it rains. Then it just stays "
        + "muddy.");
    add_ask_item(({"bench"}), "say It is right over there in the corner. I am "
        + "not really sure why you need to ask me about it.");
    add_ask_item(({"stables"}), "say Feel free to go inside and look around.");
    add_ask_item(({"tool", "tools"}), "say There are a number of "
        + "tools stored on the bench. They are used for various tasks about "
        + "stable. Not all are useful for grooming, however.");
    add_ask_item(({"mallet"}), "say We use a mallet to tap the pegs into the "
        + "shoes of our horses. It is not very useful for grooming, however.");
    add_ask_item(({"crop"}), "say A crop is useful for motivating horses to run "
        + "about the stable and get some exercise. It is not, however, very "
        + "useful for grooming.");
    add_ask_item(({"rake"}), "say A rake is a wonderful tool for moving large "
        + "quantities of hay or straw. It is not very useful for grooming "
        + "horses, though.");
    add_ask_item(({"comb"}), "say Well, combs are useful for grooming people, "
        + "but they are rather inadequate for grooming horses.");
    add_ask_item(({"groom", "grooming"}), "say Grooming a horse is a serious "
        + "business. If you do not keep your head about you, the horse "
        + "might just kick you in the teeth. The most important thing to "
        + "remember is that the entire horse needs brushing out.");

    /* quest related asks */

    add_ask_item(({"brush"}), "say You will need a "
        + "good brush to groom the horses. If you cannot find one "
        + "on the bench, no doubt one of my knob-headed assistants misplaced "
        + "it. There is no telling where it might be.");
    add_ask_item(({"hobbit", "halfling", "Pippin", "Peregrin", "pippin",
        "peregrin"}), "@@groom_horses");
    add_ask_item(({"quest", "task", "job", "help"}), "say I often have "
        + "jobs and tasks "
        + "for those in search of work. That is no wonder, what with this "
        + "hobbit not showing up to help me.");
    add_ask_item(({"reward", "for reward", "about reward"}), "say Are you "
        + "finished? Where is your proof?");
    add_ask_item(({"oat", "oats", "faradan", "Faradan"}), "@@find_oats");
    add_ask_item(({"firewood"}), "@@ask_firewood");

    arm_me();
    refresh_mobile();

}


public void
return_giggle(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
    return;

    switch (random(3))
    {
    case 0:
        command("say Nice to see joy in such perilous times.");
        break;
    case 1:
        command("grin . "+ actor->query_real_name());
        break;
    case 2:
        command("smile . " + actor->query_real_name());
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
        command("say Laughter is truly the best medicine.");
	       break;
    case 1:
	       command("tickle . " + actor->query_real_name());
	       break;
    case 2:
        command("say I could use some help from the likes of you.");
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

public void 
set_arm_arrays()
{
  ::set_arm_arrays();
  wep1 = WEP_ARRAY1;
  wep2 = WEP_ARRAY2;
  arm1 = ARM_ARRAY1;
  arm2 = ARM_ARRAY2;
}

string
groom_horses()
{
    string pname;

    pname = TP->query_real_name();

    if ((query_friend_or_foe(TP) < 0) && (!TP->query_wiz_level()))
    {
        command("scowl " + TP->query_real_name());
        command("say You do not look the sort I would hire!");
        command("say Begone lest I call the guards!");
        return "";
    }

    if (TP->query_prop(QUESTING_FOR_BRUSH))
    {
        command("say What are you waiting for? Those horses need "
            + "grooming, and they need it now!");
        return "";
    }


    if (TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_OAT_BIT))
    {
        TO->command("say I think the horses are fine, and you have "
            + "helped me get some oats. Why don't you go see if Fergil "
            + "needs some help getting firewood?");
        return "";
    }


    if (TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_PORTER_BIT))
    {
        TO->command("say Actually, the horses are all groomed at the moment "
            + "and I need no help with them. What I could really use some "
            + "help with, however, is getting my hands on some oats!");
        return "";
    }

    if (TP->query_prop(QUESTING_FOR_GERADAN))
    {
        command("say Ah yes, The halfling Peregrin sent you, did he? "
            + "Fergil the Porter owes me a favour, and the halfling was to "
            + "have come in his stead. You look much stronger, however, "
            + "so it makes no difference to me who does the work, just as "
            + "long as the work gets done!");
        set_alarm(5.0, 0.0, &command("grin"));
        set_alarm(7.0, 0.0, &command("say My assistants seem to be very "
            + "scarce this morning, and the horses here in the stable "
            + "are very much in need of grooming. What would Lord Denethor, "
            + "or for that matter Lord Mithrandir, think were they to come "
            + "for their mounts and find them looking all shabby?"));
        set_alarm(12.0, 0.0, &command("say Remind me to take a bit of "
            + "hide off the backs of my assistants when they finally "
            + "drag their carcasses in."));
        set_alarm(14.0, 0.0, &command("crack whip"));
        set_alarm(15.0, 0.0, &command("smile . " + pname));
        set_alarm(16.0, 0.0, &command("say Good thing you came along, eh? "
            + "Now, the job I have for you is very simple. All you need "
            + "to do is groom two horses, that of the Steward, and also "
            + "that amazing Mearas Lord Mithrandir brought in."));
        set_alarm(21.0, 0.0, &command("say Both horses are stabled here, "
            + "so you will not need to go hunting about for them. I have "
            + "heard that a lot of the jobs around here require you to "
            + "go out looking for things. Seems like a big waste of time "
            + "to me!"));
        set_alarm(25.0, 0.0, &command("wink"));
        set_alarm(26.0, 0.0, &command("say Well, these horses need grooming, "
            + "and that is not likely to happen as long as we are standing "
            + "here jawing. Give me the tool you used when finished, "
            + "and I will see that you are compensated for your labours!"));

        TP->add_prop(QUESTING_FOR_BRUSH, 1);
        START_QUEST(TP, "MTIRITH PORTER QUEST");

        set_alarm(30.0, 0.0, &command("wave . " + pname));
        set_alarm(31.0, 0.0, &command("emote looks slightly impatient."));
        set_alarm(33.0, 0.0, &command("emote picks a prickly green stem "
            + "from the seat of his trousers."));

        return "";
    }

    else
        command("say Hmm. What makes you think I would have work for "
            + "you?");

    return "";
}


void
reward_groom(object from)
{
    string  who = from->query_real_name();

    if (!present(from, ENV(TO)))
        return;

    if (from->test_bit("Gondor", MTIRITH_PORTER_GROUP, MTIRITH_PORTER_BIT))
        return;

    MONEY_MAKE_PC(5)->move(TO);
    command("give platinum coins to " + who);

    from->set_bit(MTIRITH_PORTER_GROUP, MTIRITH_PORTER_BIT);
    from->add_exp_quest(MTIRITH_PORTER_EXP);
    from->catch_msg("You feel more experienced!\n");
    from->remove_prop(QUESTING_FOR_PIPPIN);
    from->remove_prop(QUESTING_FOR_GERADAN);
    from->remove_prop(QUESTING_FOR_BRUSH);
    from->remove_prop(GROOMED_STEWARD_MANE);
    from->remove_prop(GROOMED_STEWARD_BODY);
    from->remove_prop(GROOMED_STEWARD_TAIL);
    from->remove_prop(GROOMED_SHADOWFAX_MANE);
    from->remove_prop(GROOMED_SHADOWFAX_BODY);
    from->remove_prop(GROOMED_SHADOWFAX_TAIL);
    LOG_QUEST(from, MTIRITH_PORTER_EXP, "MTIRITH PORTER QUEST");
    return;
}


void
reward_bag(object from)
{
    string  who = from->query_real_name();

    if (!present(from, ENV(TO)))
        return;

    if (from->test_bit("Gondor", MTIRITH_PORTER_GROUP, MTIRITH_OAT_BIT))
        return;

    MONEY_MAKE_PC(20)->move(TO);
    command("give platinum coins to " + who);

    from->set_bit(MTIRITH_PORTER_GROUP, MTIRITH_OAT_BIT);
    from->add_exp_quest(MTIRITH_OAT_EXP);
    from->catch_msg("You feel more experienced!\n");
    from->remove_prop(QUESTING_FOR_FARADAN);
    from->remove_prop(QUESTING_FOR_OATS);
    from->remove_prop(FOUND_OAT_BRANCH);
    from->remove_prop(OATS_FROM_FARADAN);

    LOG_QUEST(from, MTIRITH_OAT_EXP, "MTIRITH OAT QUEST");
    return;
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


void
accept_brush(object ob, object from)
{
    string who;
    who = from->query_real_name();

    if (from->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_PORTER_BIT))
    {
        TO->command("say Hmm. I do not seem to need any more help at "
            + "the moment. Perhaps you should go arm yourself for the "
            + "coming war!");
        set_alarm(1.0, 0.0, &give_it_back(ob, from));
        return;
    }

    if (from->query_prop(GROOMED_STEWARD_MANE)
        && from->query_prop(GROOMED_STEWARD_BODY)
        && from->query_prop(GROOMED_STEWARD_TAIL)
        && from->query_prop(GROOMED_SHADOWFAX_MANE)
        && from->query_prop(GROOMED_SHADOWFAX_BODY)
        && from->query_prop(GROOMED_SHADOWFAX_TAIL)
        && from->query_prop(QUESTING_FOR_BRUSH))
    {
    command("say Ah! You have finished grooming the horses!");
    set_alarm(1.0, 0.0, &command("smile"));
    set_alarm(2.0, 0.0, &command("say I do hope it was not too much "
        + "trouble? No, I didn't think so."));
    set_alarm(5.0, 0.0, &command("grin"));

    ob->remove_object();

    set_alarm(7.0, 0.0, &command("thank " + who));
    set_alarm(9.0, 0.0, &reward_groom(from));
    return;
    }

    else
    {
    command("say What use is this to me? The horses need grooming!");
    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;

    }
}


void
accept_bag(object ob, object from)
{
    string who;
    who = from->query_real_name();

    if (from->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_OAT_BIT))
    {
        TO->command("say Hmm. I do not seem to need any more help at "
            + "the moment. Perhaps you should go arm yourself for the "
            + "coming war!");
        set_alarm(1.0, 0.0, &give_it_back(ob, from));
        return;
    }

    if (from->query_prop(OATS_FROM_FARADAN))
    {
    command("say Ah! You have brought me the special oats from Faradan!");
    set_alarm(1.0, 0.0, &command("smile"));
    set_alarm(2.0, 0.0, &command("say I do hope it was not too much "
        + "trouble? No, I didn't think so."));
    set_alarm(5.0, 0.0, &command("grin"));

    ob->remove_object();

    set_alarm(7.0, 0.0, &command("thank " + who));
    set_alarm(9.0, 0.0, &reward_bag(from));
    set_alarm(11.0, 0.0, &command("say By the way, while you were gone I "
        + "heard from my friend Fergil the Porter. He is looking for some "
        + "help with a tough job and wondered if I knew of someone he could "
        + "trust."));
    set_alarm(15.0, 0.0, &command("peer thoughtfully " + who));
    set_alarm(16.0, 0.0, &command("say You have helped me twice now, and I "
        + "think you are a very trustworthy helper! If you want to help him "
        + "out, just ask him about firewood."));
    return;
    }

    else
    {
    command("say I do not recall asking you for this!");
    set_alarm(1.0, 0.0, &give_it_back(ob, from));
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

    if (ob->id("_minas_horse_brush_"))
    {
        set_alarm(1.0, 0.0, &accept_brush(ob, from));
        return;
    }

    if (ob->id("_oat_quest_bag_"))
    {
        set_alarm(1.0, 0.0, &accept_bag(ob, from));
        return;
    }
    set_alarm(1.0, 0.0, &give_it_back(ob, from));
}

string
find_oats()
{
    object fnote;
    object wizone, wiztwo, wizthree;
    int age;
    string actor;
    object player;

    player = this_player();
    actor = TP->query_real_name();
    age = TP->query_age();

    if ((query_friend_or_foe(TP) < 0) && (!TP->query_wiz_level()))
    {
        command("scowl " + TP->query_real_name());
        command("say You do not look the sort I would hire!");
        command("say Begone lest I call the guards!");
        return "";
    }

    /* If player is younger than 23 days old, they cannot do this quest */

    if (age < 1000000)
    {
        command("say You seem a little young for this job. Why don't "
            + "you come back when you are a bit more experienced?");
        command("smile regretfully");
        return "";
    }


    if (!TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_PORTER_BIT))
    {
        TO->command("say Let's not get ahead of ourselves! I need help "
            + "getting these horses groomed first!");
        return "";
    }
  

    if (TP->query_prop(QUESTING_FOR_FARADAN))
    {
        command("say What are you waiting for? I need those oats, "
            + "and I need them now!");
        return "";
    }

    if (TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_OAT_BIT))
    {
        TO->command("say Hmm. I do not seem to need any more help at "
            + "the moment. Perhaps you should go arm yourself for the "
            + "coming war!");
        return "";
    }
  

    if(oat_in_progress)
        TO->command("say I already sent someone else to fetch some oats, "
            + "but maybe you will be a little quicker to bring them "
            + "back.");

    TO->command("smile");
    set_alarm(2.0, 0.0, &command("say When Lord Mithrandir brought in "
        + "that magnificent Meara Shadowfax, I knew that regular oats "
        + "would simply not do. My brother Faradan, a farmer in the "
        + "Lossarnach, grows the finest oats in all the Kingdom, and "
        + "normally he keeps me well-stocked. With the war coming, however, "
        + "it is difficult for him to deliver them."));
    set_alarm(7.0, 0.0, &command("sigh"));
    set_alarm(8.0, 0.0, &command("say I sent out one of my best groomsmen "
        + "yesterday to fetch a bag of Faradan's oats, but he never came "
        + "back. I hope he did not get waylaid on the road!"));
    set_alarm(12.0, 0.0, &command("worry"));
    set_alarm(13.0, 0.0, &command("say You look like a tough sort. I wonder "
        + "if you might be willing to risk the open road and bring me back "
        + "a bag of oats? Of course you would!"));
    set_alarm(18.0, 0.0, &command("say Of course he will not just give his "
        + "oats to just anybody. Let me write you a requisition."));

    setuid();
    seteuid(getuid());

    clone_object(INNER_MINAS + "/obj/faradan_note.c")->move(TP);

    TP->add_prop(QUESTING_FOR_FARADAN, 1);
    START_QUEST(TP, "MTIRITH OAT QUEST");

    oat_in_progress = 1;

    set_alarm(21.0, 0.0, &player->catch_tell("Geradan scribbles a few words "
        + "onto a sheet of paper "
        + "and hands you a small requisition.\n"));
    set_alarm(21.0, 0.0, &tell_room(environment(), "Geradan scribbles "
        + "a few words onto a sheet "
        + "of paper and hands " + QTNAME(TP) + " a small "
        + "requisition.\n", player));

    set_alarm(24.0, 0.0, &command("smile"));
    set_alarm(25.0, 0.0, &command("say Just give that to Faradan, and he "
        + "will provide you the oats to bring back. Please hurry!"));

    wizone = find_player("alto");
    wiztwo = find_player("gwyneth");
    wizthree = find_player("stern");

    wizone->catch_tell("A little pixie whispers into your ear: " +
        CAP(actor) + " just started the oat quest.\n");
    wiztwo->catch_tell("A little pixie whispers into your ear: " +
        CAP(actor) + " just started the oat quest.\n");
    wizthree->catch_tell("A little pixie whispers into your ear: " +
        CAP(actor) + " just started the oat quest.\n");

    write_file(OAT_QUEST_LOG, "Quest started by " + 
	       player->query_name() + " (" + 
	       player->query_average_stat() + ") on " + ctime(time()) +
	       ".\n");  

    return "";
}

string
ask_firewood()
{
    if (!TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_OAT_BIT))
    {
        TO->command("say I have a few things that need doing before you "
            + "need to worry about that.");
        return "";
    }

    command("say Yes, my friend Fergil the Porter needs some help getting "
        + "some. Didn't I already tell you that?");
    return "";

}


public int
query_knight_prestige() { return -30; }


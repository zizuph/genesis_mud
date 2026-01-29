/*
 *   /d/Gondor/minas/npc/faradan.c
 *
 *   A farmer of the Lossarnach involved in the oat quest.
 *
 *   Alto, 13 May 2001
 */


#pragma strict_types

inherit "/d/Gondor/std/monster";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/std/act/domove";
inherit "/std/act/action";

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
#define FANGORN_DIR "/d/Gondor/fangorn"

#define AREA_IDENT            96434318
#define AREA_RANGE            17

string *prooms = ({FANGORN_DIR + "/fangorn1.c",
FANGORN_DIR + "/fangorn2.c",
FANGORN_DIR + "/fangorn3.c",
FANGORN_DIR + "/fangorn4.c",
FANGORN_DIR + "/fangorn5.c",
FANGORN_DIR + "/fangorn6.c",
FANGORN_DIR + "/fangorn7.c",
FANGORN_DIR + "/fangorn8.c",
FANGORN_DIR + "/fangorn9.c",
FANGORN_DIR + "/fangorn10.c",
FANGORN_DIR + "/fangorn11.c",
FANGORN_DIR + "/fangorn12.c",
FANGORN_DIR + "/fangorn13.c",
FANGORN_DIR + "/fangorn14.c",
FANGORN_DIR + "/fangorn15.c",
FANGORN_DIR + "/fangorn16.c",
FANGORN_DIR + "/fangorn17.c"});

int branch_in_progress = 0;

public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());
 

    ::create_monster();
    set_adj("hard-natured");
    set_adj("grizzled");
    set_living_name("faradan");
    set_name("Faradan");
    add_name("farmer");
    add_name("faradan");
    set_race_name("human");

    set_title("of the Lossarnach");
    set_long("This is a farmer of the Lossarnach. His skin and hands "
        + "are worn and wrinkled from many years of work under the sun. "
        + "He looks like a pleasant fellow, and he smells of "
        + "good clean earth and oats.\n");

    rnd = random(60);
    default_config_npc(120+rnd/2);
    set_base_stat(SS_DIS, 140 + rnd);
    set_alignment(350+rnd*10);
    set_skill(SS_WEP_CLUB, MIN(100, 75 + rnd));
    set_skill(SS_WEP_POLEARM, MIN(100, 75 + rnd));
    set_skill(SS_PARRY, MIN(100, 75 + rnd));
    set_skill(SS_DEFENCE, MIN(100, 75 + rnd));
    add_prop(CONT_I_HEIGHT,170+rnd);
    add_prop(CONT_I_WEIGHT,85000+rnd*500);
    add_prop(CONT_I_VOLUME,80000+rnd*500); 

    setuid();
    seteuid(getuid());

    clone_object(INNER_MINAS + "/obj/faradan_rake.c")->move(TO);


    set_chat_time(15);
    add_chat("Welcome to my farm! Ahh, but how I love good hard work!");
    add_chat("I could really use some fertilizer.");
    add_chat("I grow the finest oats in the South Kingdom!");
    add_chat("My brother Geradan is a big shot up in the city.");
    add_chat("I do not really have all day to stand here jawing with "
        + "strangers. The fields need tilling.");

    set_cchat_time(5);
    add_cchat("Bloody strangers! Why don't you leave an honest man "
        + "in peace?");
    add_cchat("Have you nothing better to do than murder a farmer?");
    add_cchat("Confound you! I'll beat you within an inch of your life!");

    set_act_time(7);
    add_act("scratch head");
    add_act("emote wipes his brow.");
    add_act("smile honestly");
    add_act("peer thoughtfully");
    add_act("emote picks some dirt from beneath a fingernail.");
    add_act("emote puts one finger aside his nose and shows you "
        + "how to use a farmer's hanky. How disgusting!");


    remove_prop(LIVE_I_NEVERKNOWN);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);


    set_default_answer( ({ "say Excuse me?", "cough incoherently" }) );


    add_ask_item(({"farm", "farming", "fields", "field"}), "say I have "
        + "farmed this land for "
        + "my entire life, as did my father before me and his father "
        + "before him. It is good, clean and honest work. My brother, "
        + "however, always did pine for the city life, and now he lives "
        + "up there.");
    add_ask_item(({"brother", "geradan", "Geradan"}), "say If ever you "
        + "travel to the Sixth Circle of Minas Tirith, perhaps you will "
        + "meet my brother. He is Master of the Royal Stables, you know!");
    add_ask_item(({"father"}), "say He was a good and trusty Lossarnachman.");
    add_ask_item(({"sixth circle", "minas tirith", "city"}), "say Have "
        + "you never visited the great city of Minas Tirith? I've been there "
        + "a few times to visit my brother, and it is quite impressive.");
    add_ask_item(({"stables", "royal stables"}), "say That is where "
        + "my brother works. Quite a fancified operation they have going "
        + "there, if you ask me. More than simple folk need concern "
        + "themselves with, but that is just my own opinion.");
    add_ask_item(({"rake"}), "say I use it to till the soil, but it also "
        + "comes in handy when ruffians come onto my property with "
        + "dishonest intentions.");
    add_ask_item(({"lossarnach", "Lossarnach"}), "say City folks seem "
        + "to look down their noses a bit at us simple people out here "
        + "farming the land. But they will not turn their noses up at our "
        + "grain with the war coming!");
    add_ask_item(({"grain"}), "say Well what did you think we were growing "
        + "out here?");
    add_ask_item(({"fertilizer"}), "say I use it to supplement the growth "
        + "of my oats. I'm running low at the moment.");
    add_ask_item(({"kingdom", "south kingdom", "South Kingdom"}), "say "
        + "Why the kindom of Gondor, of course. Where did you think you "
        + "were?");

    /* quest related asks */

    add_ask_item(({"oat", "oats"}), "say I grow the best oats in the "
        + "South Kingdom. However, I am drastically low on the special "
        + "fertilizer I need to grow them!");
    add_ask_item(({"quest", "task", "job", "help"}), "say Well, I can "
        + "always use some help, but you don't expect me to hire just "
        + "anyone. Where are your credentials?");
    add_ask_item(({"reward", "for reward", "about reward"}), "say Are you "
        + "finished? Where is your proof?");
    add_ask_item(({"branch", "marsh oak", "oak"}), "say Yes, I need that "
        + "to make my special fertilizer. Do you have some?");
    add_ask_item(({"fangorn", "Fangorn", "forest"}), "say I hear it is "
        + "haunted! Not a safe place to be, especially if you mean harm "
        + "to the trees. Or so I have heard.");


    command("wield all");

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
        command("say What a happy soul. You would make a good farmer.");
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
        command("say Nothing like a good laugh to make the work go faster.");
	       break;
    case 1:
	       command("grin . " + actor->query_real_name());
	       break;
    case 2:
        command("say You lighten my heart with your laugh, stranger.");
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
reward_oat(object from)
{
    object player;
    string who;

    player = this_player();

    who = from->query_real_name();

    if (!present(from, ENV(TO)))
        return;

    if (from->test_bit("Gondor", MTIRITH_PORTER_GROUP, MTIRITH_OAT_BIT))
        return;

    from->add_prop(OATS_FROM_FARADAN, 1);


    setuid();
    seteuid(getuid());

    clone_object(INNER_MINAS + "/obj/oat_q_bag.c")->move(from);


    set_alarm(2.0, 0.0, &player->catch_tell("Faradan hands you a "
        + "bag of oats.\n"));
    set_alarm(2.0, 0.0, &tell_room(environment(), "Faradan hands " 
        + QTNAME(TP) + " a bag "
        + "of oats.\n", player));

    set_alarm(3.0, 0.0, &command("say There you are. One bag of my "
        + "finest oats! No doubt Geradan is waiting for them, so you "
        + "had best be on your way!"));
    
    return;
}


void
accept_note(object ob, object from)
{
    string who, area;
    int area_loc;

    who = from->query_real_name();

    area_loc = NAME_TO_RANDOM(who, AREA_IDENT, AREA_RANGE);

    command("say Hmm .. how interesting.\n");


    if (from->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_OAT_BIT))
    {
        TO->command("say Hmm. I would feel guilty putting you to further "
            + "work, my friend!");
        set_alarm(1.0, 0.0, &give_it_back(ob, from));
        return;
    }

    if (from->query_prop(QUESTING_FOR_OATS))
    {
        command("say What are you waiting for? Bring me the branch, "
            + "and I'll give you some oats!");
        return;
    }


    if (from->query_prop(QUESTING_FOR_FARADAN))
    {

    if(branch_in_progress)
        TO->command("say You aren't the first person my brother "
            + "sent over today. How odd. Well, I suppose I need all "
            + "help I can get.");

    command("emote looks over the requisition.");
    command("say Ah! My brother sent you!");
    set_alarm(1.0, 0.0, &command("smile"));
    set_alarm(3.0, 0.0, &command("say Nice to know he hasn't forgotten "
        + "about me, now that he lives up in the city. Of course he "
        + "usually remembers me when he needs my special oats!"));
    set_alarm(6.0, 0.0, &command("grin"));

    ob->remove_object();

    set_alarm(7.0, 0.0, &command("peer thoughtfully " + who));
    set_alarm(9.0, 0.0, &command("say Well, I do have a store of oats "
        + "set back for emergencies, but at the moment I am almost "
        + "entirely out of the special fertilizer I need to grow "
        + "them. That makes me quite a bit reluctant to part with any."));
    set_alarm(14.0, 0.0, &command("say I suppose if I had some more "
        + "fertilizer, I might be willing to send a bag with you."));
    set_alarm(17.0, 0.0, &command("scratch head"));
    set_alarm(19.0, 0.0, &command("say All I really need is some bark "
        + "from a marsh oak. Its ashes really spice up the soil!"));
    set_alarm(22.0, 0.0, &command("worry"));
    set_alarm(23.0, 0.0, &command("say You see, the only place I know "
        + "of to find marsh oak is up in Fangorn forest."));
    set_alarm(25.0, 0.0, &command("shiver"));
    set_alarm(26.0, 0.0, &command("say They say that place is haunted, "
        + "and I do not doubt it! They also say that you should never "
        + "go cutting on the trees there. Maybe the ghosts don't like it."));
    set_alarm(30.0, 0.0, &command("shrug"));
    set_alarm(31.0, 0.0, &command("say Whatever the case, I had me a fella "
        + "that knew the trick of getting some. Something to do with looking "
        + "at roots for clues, or something. I sent him to fetch some "
        + "last week, but he never returned. I wonder if the ghosts got "
        + "him at last?"));
    set_alarm(35.0, 0.0, &command("shudder"));

    from->add_prop(QUESTING_FOR_OATS, 1);
    
    set_alarm(36.0, 0.0, &command("say Hmm. If my brother sent you, he "
        + "must think you are a clever sort. Perhaps you can run up to "
        + "Fangorn and fetch me a branch from a marsh oak tree."));
    set_alarm(40.0, 0.0, &command("shake " + who));
    set_alarm(41.0, 0.0, &command("say Be careful! Just give me a "
        + "marsh oak branch when you get back, and I'll make sure you "
        + "get your oats."));

    setuid();
    seteuid(getuid());

    if(file_size(prooms[area_loc]) != -1)
    {
        prooms[area_loc]->teleledningsanka();
        if(!present("_oat_quest_roots_", find_object(prooms[area_loc])))
        {
        clone_object(FANGORN_DIR + "/obj/oat_q_roots.c")->move(prooms[area_loc]);

        branch_in_progress = 1;
        }
    }

    return;
    }

    else
    {
    command("say You do not seem the sort my brother would trust.\n");
    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;

    }
}


void
accept_branch(object ob, object from)
{
    string who;

    who = from->query_real_name();

    if (from->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_OAT_BIT))
    {
        TO->command("say Hmm. I seem to have already got a branch from you!");
        set_alarm(1.0, 0.0, &give_it_back(ob, from));
        return;
    }

    if (from->query_prop(FOUND_OAT_BRANCH))
    {
    command("say Ah! You have found a piece of marsh oak. Splendid!");
    set_alarm(1.0, 0.0, &command("smile"));
    set_alarm(2.0, 0.0, &command("say I do hope it was not too much "
        + "trouble? No, I didn't think so."));
    set_alarm(5.0, 0.0, &command("grin"));

    ob->remove_object();

    set_alarm(7.0, 0.0, &command("thank " + who));
    set_alarm(9.0, 0.0, &reward_oat(from));
    return;
    }

    else
    {
    command("say I do not remember asking you for this!\n");
    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;

    }
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (ob->id("_oat_quest_note_"))
    {
        set_alarm(1.0, 0.0, &accept_note(ob, from));
        return;
    }

    if (ob->id("_oat_quest_branch_"))
    {
        set_alarm(1.0, 0.0, &accept_branch(ob, from));
        return;
    }
    set_alarm(1.0, 0.0, &give_it_back(ob, from));
}


public int
query_knight_prestige() { return -30; }


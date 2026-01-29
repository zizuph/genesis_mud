/*  woman with 4 tours in Gont Port
 *  Coded by Amelia 2/27/98
 *
 *  1:  Finding a lost sandal
 *  2:  Fetching a macintosh apple
 *  3:  Finding a headache remedy
 *  4:  A bucket of clams for the bouillabase
 */

#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Earthsea/lib/remember";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>
#include "/d/Earthsea/quest_handler/quest_handler.h"

#define TASK_ASK   ({"help", "task", "job",\
    "about task", "about job", "quest", "about quest" })
#define SANDAL_ASK ({"sandal", "about sandal"})
#define APPLE_ASK ({"apple", "about apple",\
    "macintosh apple", "about macintosh apple"})
#define CLAM_ASK ({"clams", "about clams", "bouillabase",\
    "about soup", "about bouillabase" })
#define BUCKET "/d/Earthsea/gont/gont_city/obj/bucket"

//some temporary quest props
#define PLAYER_I_GOT_HEADACHE_TOUR "_player_i_got_headache_tour"
#define PLAYER_I_GOT_CLAM_TOUR "_player_i_got_clam_tour"
#define PLAYER_I_GOT_APPLE_TOUR "_player_i_got_apple_tour"
#define PLAYER_I_GOT_SANDAL_TOUR "_player_i_got_sandal_tour"

public void
create_earthsea_monster()
{
    set_name("thera");
    add_name("woman");
    add_name("mother");
    add_name("human");
    set_race_name("human");
    set_adj(({"long-haired", "dark-eyed"}));
    set_living_name("_thera_");
    set_title("Perrilan");
    set_long("A long-haired dark-eyed woman. You can see the spark of " +
        "wisdom in her dark eyes. She might have a task or two " +
        "for you to do.\nShe has lovely long wavy black hair.\n");
    set_gender(G_FEMALE);
    set_stats(({40, 60, 40, 90, 105, 40}));
    add_prop(OBJ_M_NO_ATTACK, "The woman looks at you "+
        "strangely, and you feel suddenly embarrassed.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The woman holds up "+
        "her hand and shouts loudly: Avert!\nThe spell "+
        "falls harmlessly on empty air.\n");
    set_act_time(60);
    add_ask(TASK_ASK, VBFC_ME("respond_task_ask"));
    add_ask(APPLE_ASK, VBFC_ME("respond_apple_ask"));
    add_ask(CLAM_ASK, VBFC_ME("respond_clam_ask"));
    add_ask(SANDAL_ASK, VBFC_ME("respond_sandal_ask"));
    set_default_answer(QCTNAME(this_object()) + " says: I don't understand "+
        "your question.\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    set_chat_time(90);
    add_act("emote stirs the kettle of soup.");
    set_height("normal");
    set_width("skinny");
}

/*******************************************************************
*  RESPONSES TO QUESTIONS
*******************************************************************/

public string
respond_task_ask()
{
    object bucket, tp = this_player();

    // CHECKS FOR TOURS ALREADY GIVEN (CAN'T DO MORE THAN ONE AT A TIME)

    if(tp->query_prop(PLAYER_I_GOT_SANDAL_TOUR))
    {
        command("ask "+ lower_case(tp->query_name()) + " "+
            "Did you find my sandal yet? If so, please give it to "+
            "me.");
        command("smile");
        return "";
    }

    if(tp->query_prop(PLAYER_I_GOT_APPLE_TOUR))
    {
        command("ask "+ lower_case(tp->query_name()) + " "+
            "Have you found that macintosh apple for me yet?");
        command("peer "+ lower_case(tp->query_name()));
        return "";
    }

    if(tp->query_prop(PLAYER_I_GOT_HEADACHE_TOUR))
    {
        command("ask "+ lower_case(tp->query_name()) + " "+
            "Have you got something for my headache yet?");
        command("emote rubs the temples of her forehead.");
        return "";
    }

    if(tp->query_prop(PLAYER_I_GOT_CLAM_TOUR))
    {
        command("ask "+ lower_case(tp->query_name()) + " "+
            "Did you fill the bucket yet? If so, please give it to "+
            "me.");
        command("hmm");
        return "";
    }

    // GIVES TOURS

    if(!QH_QUERY_QUEST_COMPLETED(tp, "sandal_tour"))
    {
        command("ask "+ lower_case(tp->query_name()) + " "+
            "Yesterday at the beach, I kicked off my sandals "+
            "to walk barefoot in the sand.  Somewhere on the way back "+
            "between the beach "+
            "and home I dropped one of them.");
        tp->add_prop(PLAYER_I_GOT_SANDAL_TOUR, 1);
        command("pout");
        command("ask "+ lower_case(tp->query_name()) + " "+
            "If you can find it and return it to me, I "+
            "can give you a nice reward.");
        command("wink");
        return "";
    }

    if(!QH_QUERY_QUEST_COMPLETED(tp, "good_apple_tour"))
    {
        command("ask "+ lower_case(tp->query_name()) + " "+
            "Please fetch me a nice red macintosh apple.");
        tp->add_prop(PLAYER_I_GOT_APPLE_TOUR, 1);
        command("smile");
        command("ask "+ lower_case(tp->query_name()) + " "+
            "They are my favorite!");
        return "";
    }

    if(!QH_QUERY_QUEST_COMPLETED(tp, "headache_cure_tour"))
    {
        command("ask "+ lower_case(tp->query_name()) + " "+
            "I have a terrible headache. If you could get me "+
            "something for this headache, I will reward you!");
        command("emote rubs the temples of her forehead.");
        tp->add_prop(PLAYER_I_GOT_HEADACHE_TOUR, 1);
        return "";
    }

    if(!QH_QUERY_QUEST_COMPLETED(tp, "clam_adventure"))
    {
        command("ask "+ lower_case(tp->query_name()) + " "+
            "I am making a bouillabase for supper, and I need some "+
            "fresh clams.");
        setuid();
        seteuid(getuid());
        bucket = clone_object(BUCKET);
        command("ask "+ lower_case(tp->query_name()) + " "+
            "Please fill this bucket with fresh live clams, and "+
            "return it to me. I find that live clams give the best "+
            "flavour.");
        tp->add_prop(PLAYER_I_GOT_CLAM_TOUR, 1);
        command("smile");

        if(bucket->move(tp))
        {
            command("emote places the bucket on the floor.");
            bucket->move(environment(this_object()));
            return "";
        }

        tp->catch_msg(QCTNAME(this_object()) + " gives you the bucket.\n", ({tp}));
        tell_room(environment(this_object()), QCTNAME(this_object()) + " gives a bucket "+
            "to " + QTNAME(tp) + ".\n", ({tp}));
        return "";
    }

    command("smile");
    command("ask "+ lower_case(tp->query_real_name()) + " "+
        "Thanks, but you have already helped me before.");
    return "";
}

public string
respond_sandal_ask()
{
    command("ask "+ lower_case(this_player()->query_name()) + " " +
        "I was carrying them in my hand while walking along ... " +
        "and I didn't notice where I lost it. It could be anywhere " +
        "between here and the beach.");
    command("think");
    return "";
}

public string
respond_clam_ask()
{
    command("ask " + lower_case(this_player()->query_name()) + " " +
        "My bouillabase recipe calls for a bucket of fresh clams.");
    return "";
}

public string
respond_apple_ask()
{
    if(this_player()->query_prop(PLAYER_I_GOT_APPLE_TOUR))
    {
        command("say I think there is a very nice apple tree "+
            "by Ten Alders village.");
        command("say Macintosh apples are my favourite.");
    }

    command("say Macintosh apples are my favourite ... ");
    return "";
}

private int
reward_sandal_tour(object sandal, object player)
{
    player->remove_prop(PLAYER_I_GOT_SANDAL_TOUR);

    if(!QH_QUERY_QUEST_COMPLETED(player, "sandal_tour"))
    {
        command("thank "+ lower_case(player->query_name()));
        QH_QUEST_COMPLETED(player, "sandal_tour");
        player->catch_tell("You feel more experienced!\n");
    }

    return 1;
}

private int
reward_headache_tour(object bark, object player)
{
    player->remove_prop(PLAYER_I_GOT_HEADACHE_TOUR);
    command("chew bark");
    command("say Oh my head feels much better now!");

    if(!QH_QUERY_QUEST_COMPLETED(player, "headache_cure_tour"))
    {
        command("thank "+ lower_case(player->query_name()));
        QH_QUEST_COMPLETED(player, "headache_cure_tour");
        player->remove_prop(PLAYER_I_GOT_HEADACHE_TOUR);
        player->catch_tell("You feel more experienced!\n");
    }

    return 1;
}

private int
reward_apple_tour(object apple, object player)
{
    player->remove_prop(PLAYER_I_GOT_APPLE_TOUR);
    command("eat apple");
    command("say Yumm!");

    if(!QH_QUERY_QUEST_COMPLETED(player, "good_apple_tour"))
    {
        command("thank "+ lower_case(player->query_name()));
        QH_QUEST_COMPLETED(player, "good_apple_tour");
        player->catch_tell("You feel more experienced!\n");
    }

    return 1;
}

private int
reward_clam_tour(object bucket, object player)
{
    if(!bucket->query_bucket_full())
    {
        command("give bucket to "+lower_case(player->query_name()));
        command("say Bring it back when it's full!");
        command("smile");
        return 1;
    }

    if(bucket->query_bucket_full() && 
        (!QH_QUERY_QUEST_COMPLETED(player, "clam_adventure")))
    {
        command("thank "+lower_case(player->query_name()));
        command("say Wonderful! This will make the bouillabase perfect!");
        command("emote rinses the clams in a basin of water, then "+
            "puts them into the steaming kettle.");
        bucket->remove_object();
        player->remove_prop(PLAYER_I_GOT_CLAM_TOUR);
        QH_QUEST_COMPLETED(player, "clam_adventure");
        player->catch_tell("You feel more experienced!\n");
        return 1;
    }

    return 1;
}

private int
return_stuff(object ob, object player)
{
    command("give "+ ob->query_name() + " to "+
        lower_case(player->query_name()));
    command("say No, thank you.");
    return 1;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(from) && (ob->query_theras_sandal()) &&
        from->query_prop(PLAYER_I_GOT_SANDAL_TOUR))
    {
        set_alarm(2.0, 0.0, &reward_sandal_tour(ob, from));
        return;
    }

    if(interactive(from) && (ob->query_good_apple()) &&
        from->query_prop(PLAYER_I_GOT_APPLE_TOUR))
    {
        set_alarm(2.0, 0.0, &reward_apple_tour(ob, from));
        return;
    }

    if(interactive(from) && (ob->query_herb_name() == "aspen bark") &&
        from->query_prop(PLAYER_I_GOT_HEADACHE_TOUR))
    {
        set_alarm(2.0, 0.0, &reward_headache_tour(ob, from));
        return;
    }

    if(interactive(from) && (ob->query_bucket_full()) &&
        from->query_prop(PLAYER_I_GOT_CLAM_TOUR))
    {
        set_alarm(2.0, 0.0, &reward_clam_tour(ob, from));
        return;
    }

    if(interactive(from) && (ob->id("bucket")) &&
        from->query_prop(PLAYER_I_GOT_CLAM_TOUR))
    {
        command("say Hmm ... I need a bucket full of live "+
            "clams ... Better try again.");
        set_alarm(2.0, 0.0, &return_stuff(ob, from));
        return;
    }

    if(interactive(from))
        set_alarm(2.0, 0.0, &return_stuff(ob, from));

    return;
}

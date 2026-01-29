/*
 * /d/Emerald/telberin/magic/npc/satherel.c
 *
 * This wise elf is a prominent member of the Telberin Mage Guild.
 * Having risen in esteem within their ranks, he has been honored
 * with the position of Door Warden, a high station despite its
 * emphasis on dealing with the common public. He has lost his
 * Apprentice lately, and has some things to say to the inquisitive
 * mortal about such things.
 *
 * Location: /d/Emerald/telberin/magic/mage_guild1.c
 *
 * Copyright (c) February 2002, by Cooper Sherry (Gorboth)
 *
 * - Added LIVE_M_NO_SILENCE
 * - Added additional checks to make sure that the disc transfer goes right
 * Shiva, Sept 10, 2003
 */

inherit "/d/Emerald/telberin/npc/telberin_elf";
inherit "/d/Genesis/lib/intro";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "/d/Emerald/quest_handler/quest_handler.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"

#ifndef LIVE_M_NO_SILENCE
#define LIVE_M_NO_SILENCE "_live_m_no_silence"
#endif

/* prototypes */
public void    create_telberin_elf();
public void    introduce(object who);
public void    react_intro(object tp);
public void    add_satherel_asks();
public void    ferry_answer();
public void    quake_answer();
public void    proud_answer();
public void    dead_answer();
public void    contact_answer();
public void    rillian_answer();
public void    missing_answer();
public void    location_answer();
public void    del_rimmon_answer();
public void    formandil_answer();
public void    eastern_plains_answer();
public void    maeltar_answer();
public void    quest_offer();
public void    complete_quest(object player);

/* definitions */
#define        QUEST_OFFER      "_rillian_quest_satherel_offer"


/*
 * Function name:        create_elf
 * Description  :        set up the npc
 */
public void
create_telberin_elf()
{
    set_living_name("satherel");
    set_name("satherel");
    add_name("satherel endan");
    set_adj("regal");
    set_adj("tall");

    set_title("Endan, Door Warden of the Telberin Mage Guild");

    set_short("tall regal elf");
    set_long("Dressed in long, flowing blue silk, this tall"
      + " elf has an air of knowledge and calm about him. His"
      + " stance suggests that he is fulfilling some kind of"
      + " duty by standing here.\n");

    config_elf(155);  /* He's a powerful enemy */

    set_act_time(7);
    add_act("emote peers outside, seemingly lost in thought.");
    add_act("emote mutters: Perhaps I do not deserve a new"
          + " apprentice.");
    add_act("emote rubs his brow, muttering: Rillian ... if only"
          + " I knew what has become of you!");
    add_act("emote tucks his hands into the folds of his robe.");
    add_act("emote sighs deeply, and peers outside.");
    add_act("emote utters softly to himself: Why did I not see it"
          + " in his behavior? Careless ...");
    add_act("emote surveys the room, looking at the people who"
          + " come and go.");

    set_cact_time(10);
    add_cact("emote tries desperately to avoid your attacks.");
    add_cact("emote peers at you in fear and anger.");
    add_cact("shout I need assistance! Some fool has attacked me!");
    add_cact("emote takes something from his pocket, and throws"
           + " it at you!");

    add_prop(OBJ_M_NO_ATTACK,
        "As you move to attack, the tall regal elf mutters a swift"
      + " word of command. Every muscle in your body freezes, and you"
      + " are unable to move. After a few seconds, you are released.\n");

    add_satherel_asks();
    set_job_response("It is my duty to greet visitors to this tower, and"
      + " see that nothing is amiss. What can I help you with?");

    setuid();
    seteuid(getuid());
} /* create_elf */


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(5)), 0.0, &react_intro(who));
} /* introduce */


/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("say Where did they go?");
        return;
    }

    command("introduce me");
} /* react_intro */


/*
 * Function name:        add_satherel_asks
 * Description  :        satherel has a dialogue tree
 *                       which gives the player clues about
 *                       going to explore Del Rimmon
 */
public void
add_satherel_asks()
{
    add_ask( ({ "apprentice", "student", "rillian",
                "new apprentice" }),
        VBFC_ME("rillian_answer"));
    add_ask( ({ "missing", "gone", "fate", "behavior",
                "his behavior", "foolish", "blame",
                "change", "changes", "changes in his behavior",
                "change in his behavior", "behavior change",
                "behavior changes",
                "careless", "idea", "missing apprentice" }),
        VBFC_ME("missing_answer"));
    add_ask( ({ "journey", "seek", "location", "where",
                "investigation", "seek him out",
                "plan", "plans", "his plan", "his plans",
                "north shore", "north shore of lake telberin" }),
        VBFC_ME("location_answer"));
    add_ask( ({ "outpost", "outposts", "del rimmon",
                "musing", "musings", "theory", "theories",
                "del rimmon outpost", "lake of del rimmon", "old outpost",
                "forgotten outpost", "old forgotten outpost" }),
        VBFC_ME("del_rimmon_answer"));
    add_ask( ({ "formandil" }),
        VBFC_ME("formandil_answer"));
    add_ask( ({ "battle", "battle of the western plains",
                "western plains" }),
        VBFC_ME("eastern_plains_answer"));
    add_ask( ({ "maeltar" }),
        VBFC_ME("maeltar_answer"));
    add_ask( ({ "proud", "proud of him", "make you proud" }),
        VBFC_ME("proud_answer"));
    add_ask( ({ "dead", "rillian dead", "dead apprentice" }),
        VBFC_ME("dead_answer"));
    add_ask( ({ "attempt", "attempt to contact", "contact",
                "disrupted", "disrupted contact", "contacted",
                "attempt to contact you",
                "his attempt to contact you" }),
        VBFC_ME("contact_answer"));
    add_ask( ({ "ferry", "ferry operator", "operator", "soldier",
                "soldiers", "garrison", "garrisons", 
                "garrison of soldiers", "garrisons of soldiers" }),
        VBFC_ME("ferry_answer"));
    add_ask( ({ "quake", "great quake", "earthquake" }),
        VBFC_ME("quake_answer"));
    add_ask( ({ "help", "assist", "quest", "task", "reward" }),
        VBFC_ME("quest_offer"));
} /* add_satherel_asks */



/*
 * Function name:        ferry_answer
 * Description  :        response to an add_ask
 */
public string
ferry_answer()
{
    command("say Are you familiar with the area of piers which are"
          + " outside the city walls? There is a ferry there that"
          + " transports replacement troops to the North Shore fairly"
          + " regularly.");
    return "";
} /* ferry_answer */


/*
 * Function name:        quake_answer
 * Description  :        response to an add_ask
 */
public string
quake_answer()
{
    command("say Some time ago, a great quake shook the lands of"
          + " Emerald. Despite its intensity, only a few buildings"
          + " in the City were damaged, and they only lightly so."
          + " I remember it most for the fact that on that day,"
          + " I was contacted for the last time by my apprentice.");
    command("sigh");
    return"";
} /* quake_answer */


/*
 * Function name:       dead_answer
 * Description  :       response to an add_ask
 */
public string
dead_answer()
{
    command("say Bad enough that it might be true, without us"
          + " speaking of such things!");
    return "";
} /* dead_answer */


/*
 * Function name:       contact_answer
 * Description  :       response to an add_ask
 */
public string
contact_answer()
{
    command("say I remember it perfectly. On the day that the"
          + " realm was shaken by a great quake, Rillian made"
          + " an attempt to contact me. He was in distress, and"
          + " there was great anguish in his thoughts. Somehow,"
          + " our communication was disrupted, and I could"
          + " learn nothing of his location or need. My duties"
          + " here prevent me from going to find him myself,"
          + " though it is very important to me. It has gotten"
          + " to the point where I would even be willing to"
          + " trust the matter to someone, if they were"
          + " willing to help me.");

    this_player()->add_prop(QUEST_OFFER, 1);

    return "";
} /* contact_answer */


/*
 * Function name:       proud_answer
 * Description  :       response to an add_ask
 */
public string
proud_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Proud ... yes, that is what he said. Though,"
              + " to be honest I could hardly have been any more"
              + " proud of him than I already was.");
        command("sigh");
        break;
    case 1:
        command("say Perhaps I should have praised his efforts more"
              + " often ... he was such a fine student.");
        command("frown sadly");
        break;
    case 2:
        command("say Had he not already done enough to impress me?"
              + " There was no need for further convincing!");
        command("grumble bitt");
        break;
    }
    return "";
} /* proud_answer */












/*
 * Function name:       rillian_answer
 * Description  :       response to an add_ask
 */
public string
rillian_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Rillian was his name. I have never had a more"
              + " promising apprentice.");
        command("sigh");
        break;
    case 1:
        command("say He has been missing now for a very long time."
              + " I fear that he is dead.");
        break;
    case 2:
        command("say How foolish of me that I did not notice the"
              + " changes in his behavior! I blame myself for"
              + " his fate.");
        break;
    }
    return "";
} /* rillian_answer */


/*
 * Function name:       missing_answer
 * Description  :       response to an add_ask
 */
public string
missing_answer()
{
    command("sigh");
    command("say Quite some time ago, my apprentice, Rillian,"
          + " took his leave of me quite suddenly, and without"
          + " adequate explanation. Despite my objections, he"
          + " insisted that he would make me quite proud of him."
          + " He would not tell me his plans, but it was clear that"
          + " he intended to leave the city to seek for something."
          + " Though he has not returned, my investigation"
          + " of the matter gives me a very good idea of where he"
          + " has gone. If only I had the time to go and seek him"
          + " out!");
    return "";
} /* missing_answer */


/*
 * Function name:       location_answer
 * Description  :       response to an add_ask
 */
public string
location_answer()
{
    command("nod");
    command("say Yes, I discovered from the ferry operator that"
          + " Rillian had travelled with a garrison of soldiers"
          + " to the north shore of Lake Telberin. There, he"
          + " quickly departed in the direction of the Blackwall"
          + " Mountains. I have often heard him speaking about"
          + " his theories on an old forgotten outpost which was"
          + " abandoned years ago at Del Rimmon. I suspect that he"
          + " has traveled to that forsaken place, though I do"
          + " not know what he seeks. If only his attempt to contact"
          + " me had not been disrupted!");
    return "";
} /* location_answer */


/*
 * Function name:       del_rimmon_answer
 * Description  :       response to an add_ask
 */
public string
del_rimmon_answer()
{
    command("say In a time long past, the Lake of Del Rimmon"
          + " was for a brief period the site of a great outpost"
          + " and training facility, erected by Formandil and"
          + " Maeltar who were among the greatest leaders in the"
          + " City. After their death, the outpost was mostly"
          + " abandoned. Few now even remember that it ever"
          + " existed. What has become of the outpost since that"
          + " time, I cannot imagine. However, my apprentice,"
          + " Rillian, often spoke of the place, and seemed intent"
          + " on exploring it. I should have paid more attention"
          + " to his musings ... Alas!");
    return "";
} /* del_rimmon_answer */


/*
 * Function name:       formandil_answer
 * Description  :       response to an add_ask
 */
public string
formandil_answer()
{
    command("say Formandil was the most prominent member of the"
          + " Protectorate of Telberin long ago, when Telberin"
          + " was a far greater city. He was slain along with the"
          + " finest soldiers in history at the tragic Battle"
          + " of the Western Plains.");
    return "";
} /* formandil_answer */


/*
 * Function name:       eastern_plains_answer
 * Description  :       response to an add_ask
 */
public string
eastern_plains_answer()
{
    command("say Long ago, the finest soldiers in the history of"
          + " our proud city rode to battle against a great and"
          + " terrible Army of Darkness. It is the saddest and most"
          + " black event in our history, for in that battle, we lost"
          + " nearly our entire military might. Both Formandil and"
          + " Maeltar were slain, as well as many other great elves."
          + " We have since recovered our military prowess, but for"
          + " a great time, there was great fear and sadness following"
          + " that fateful day.");
    return "";
} /* eastern_plains_answer */


/*
 * Function name:       maeltar_answer
 * Description  :       response to an add_ask
 */
public string
maeltar_answer()
{
    command("say Maeltar was a great and powerful elf who brought the"
          + " Order of Telan-Ri to the height of its power. His"
          + " wisdom and foresight were renowned throughout the land."
          + " His ability to pinpoint the location of enemy forces"
          + " is still legendary, many years after his tragic death"
          + " at the Battle of the Western Plains.");
    return "";
} /* maeltar_answer */



/*
 * Function name:        quest_offer
 * Description  :        here, satherel will offer players the quest
 */
public string
quest_offer()
{
    object disc;
    object quester = this_player();

    if (!MANAGER->query_rillian(quester))
    {
        if (!quester->query_prop(QUEST_OFFER))
        {
            command("say I'm not sure if you can help, but I am greatly"
                  + " troubled over my missing apprentice.");

            return "";
        }

        command("say If you are willing to help me locate my missing"
          + " apprentice, Rillian, I thank you. Please, take this disc."
          + " It is enchanted in such a way that I can connect to your"
          + " location should you use it. To summon my attention,"
          + " simply <incant iffinde> if you believe you have found"
          + " what I seek.");

        disc = clone_object("/d/Emerald/blackwall/delrimmon/obj/disc");

        MANAGER->set_rillian(quester, "Seeking");
        disc->move(quester, 1);

        if (disc)
        {
            if (present(disc, quester))
            {
                quester->catch_tell("You receive " + LANG_ASHORT(disc) + " from " +
                    query_the_name(quester) + ".\n");
            }
            else
            {
                quester->catch_tell(query_The_name(quester) + " tries to give you " +
                    LANG_ASHORT(disc) + ", but fails.\n");
                disc->remove_object();
            }
	
        }
        else
        {
            quester->catch_tell(query_The_name(quester) + " tries to give you " +
                "a disc, but fails.\n");
        }

        return "";
    }

    if (MANAGER->query_rillian(quester) == "Seeking")
    {
        command("say If you are able to find Rillian, I will reward"
          + " you. Take the disc I gave you into the Del Rimmon"
          + " Outposts, if you are able to locate them. There, you"
          + " can <incant iffinde> to summon me to any location"
          + " in which you believe you have found Rillian.");

        if (!present("_rillian_finder", quester))
        {
            command("say Ah, I see that you have lost the disc I"
              + " gave you before. Here is another. Please be more"
              + " careful with it in the future.");

            disc = clone_object("/d/Emerald/blackwall/delrimmon/obj/disc");
            disc->move(quester, 1);

            if (disc)
            {
                if (present(disc, quester))
                {
                    quester->catch_tell("You receive " + LANG_ASHORT(disc) + " from " +
                        query_the_name(quester) + ".\n");
                }
                else
                {
                    quester->catch_tell(query_The_name(quester) + " tries to give you " +
                        LANG_ASHORT(disc) + ", but fails.\n");
                    disc->remove_object();
                }

            }
            else
            {
                quester->catch_tell(query_The_name(quester) + " tries to give you " +
                    "a disc, but fails.\n");
            }
        }

        return "";
    }

    if (MANAGER->query_rillian(quester) == "Found")
    {
        command("say You have been most kind to help me. In return for"
          + " your assistance, I will grant you access to the lesser"
          + " library of our guild, which is located up the stairs to the east. It"
          + " is a pity that I was not able to get a definite read"
          + " on whether that was Rillian you found or not ... but"
          + " you have at least earned the opportunity to seek the"
          + " wisdom that is available to you here. Thank you.");

        if (disc = present("_rillian_finder", quester))
        {
            command("say The disc, if you please.");
            quester->catch_tell("You feel oddly unable to refuse, and return it"
              + " without hesitation.\n");
            disc->remove_object();
        }

        complete_quest(quester);
        MANAGER->set_rillian(quester, "Completed");

        return "";
    }

    if (MANAGER->query_rillian(quester) == "Completed")
    {
        command("say I thank you for the help you have already"
          + " given me. There is nothing more you can do.");
        return "";
    }
} /* quest_offer */


/*
 * Function name:        complete_quest
 * Description  :        reward the player, if such is appropriate
 */
public void
complete_quest(object player)
{
    if (!QH_QUERY_QUEST_COMPLETED(player, "torque_rillian") &&
         QH_QUEST_COMPLETED(player, "torque_rillian"))
    {
        player->catch_tell("You feel more experienced!\n");
    }
    else
    {
        player->catch_tell("You feel no more experienced.\n");
    }

    return;
} /* complete_quest */

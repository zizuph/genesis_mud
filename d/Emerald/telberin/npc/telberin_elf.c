/*
 *  /d/Emerald/telberin/npc/telberin_elf.c
 *
 *  The standard file for elves in Telberin.
 *
 *  Copyright (C) February 2002, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/elf";

#include <macros.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"


/* definitions */
#define GEM_TYPES       ({ ("quartz"),\
                           ("agate"),\
                           ("jasper"),\
                           ("coral"),\
                           ("turquoise"),\
                           ("amber"),\
                           ("carnelian"),\
                           ("garnet"),\
                           ("amethyst"),\
                           ("aquamarine"),\
                           ("jade"),\
                           ("lapis"),\
                           ("opal"),\
                        })

#define GEM_DIR         "/d/Genesis/gems/obj/"

/* prototypes */
public void        set_looks();
public void        create_telberin_elf();
public void        create_elf();
public void        add_telberin_asks();
public string      keepers_answer();
public string      job_answer();
public string      horse_answer();
public string      telberin_answer();
public string      raid_answer();
public string      emerald_answer();
public string      blackwall_answer();
public string      army_answer();
public string      dark_answer();
public string      val_shoreil_answer();
public string      telan_ri_answer();
public void        catch_question(string question);
public int         not_here_func();
public string      default_answer();
public string      name_answer();
public void        add_introduced(string name);
public void        react_intro(object tp);
public void        give_gems();


/* global variables */
static string       OrigQuestion;
public string       Job_Response;


public void        set_job_response(string s) { Job_Response = s; }
public string      query_job_response() { return Job_Response; }


/*
 * Function name:        set_looks
 * Description  :        give the npc a random short description
 *                       and adjectives.
 */
public void
set_looks()
{
    string *looks1 = ({ "tall", "elegant",
                        "quiet", "contemplative",
                        "slender", "striking", "attractive",
                        "brooding", "pale" });
    string *looks2 = ({ "keen-eyed", "narrow-framed",
                        "willowy", "graceful",
                        "stern-faced", "finely-dressed",
                        "gentle-eyed", "sharp-featured" });
    string  adj1 = ONE_OF_LIST(looks1);
    string  adj2 = ONE_OF_LIST(looks2);

    set_short(adj1 + " " + adj2 + " elf");
    add_adj( ({ adj1, adj2 }) );

    set_long("As with most of the denizens of Telberin, this"
      + " elf is a rather beautiful creature. There is a length"
      + " of limb and gracefulness of stature that sets them"
      + " apart from the other races of Emerald. More striking"
      + " is the aura of light that surrounds them at all"
      + " times.\n");
} /* set_looks */


/*
 * Function name:        create_telberin_elf
 * Description  :        dummy routine for inheriting files
 */
public void
create_telberin_elf()
{
}


/*
 * Function name:        create_elf
 * Description  :        set up some standard things for the
 *                       elves in Telberin
 */
public void
create_elf()
{
    set_looks();
    set_job_response("I'm afraid that what I do for a living is none"
      + " of your concern.");
    set_default_answer(VBFC_ME("default_answer"));
    add_telberin_asks();
    config_elf(50 + random(70));

    add_prop(OBJ_M_NO_ATTACK, "As you move to attack, a vision flashes " +
        "before you in your mind. In it, you see a circle of elves in deep " +
        "concentration, arrayed about a brightly glowing orb. As you are " +
        "drawn toward it, the orb pulses once with a fuzzy glow, and the " +
        "vision fades away in a shimmer of white light, leaving you in a " +
        "brief moment of peace.\n");

    create_telberin_elf();

    give_gems();

    set_not_here_func("not_here_func");
} /* create_elf */




/*
 * Function name:        add_telberin_asks
 * Description  :        these are the standard asks defined for the
 *                       elves of telberin. they can be redefined in
 *                       inheriting npcs for more specific responses
 */
public void
add_telberin_asks()
{
    add_ask( ({ "keeper", "keepers", "keepers of telberin",
               "elf", "elves", "protectorate",
               "protectorate of telberin" }),
        VBFC_ME("keepers_answer"));
    add_ask( ({ "horse", "horses", "breed" }),
        VBFC_ME("horse_answer"));
    add_ask( ({ "telberin", "city" }), 
        VBFC_ME("telberin_answer"));
//  add_ask( ({ "captain", "elf captain", "captain of the keepers",
//             "captain of the keepers of telberin",
//             "curan", "jesti mennan", "mennan" }),
//      VBFC_ME("captain_answer"));
    add_ask( ({ "raid", "raids", "recent raids", "insult",
                "raiders", "burning", "destruction", 
                "invaders", "attack", "attacks" }),
        VBFC_ME("raid_answer"));
    add_ask( ({"emerald"}),
        VBFC_ME("emerald_answer"));
    add_ask( ({ "blackwall", "mountains", "blackwall mountains",
               "home", "blackwall fortress", "fortress" }),
        VBFC_ME("blackwall_answer"));
    add_ask( ({ "orcs", "orc", "creatures",
                "creatures of darkness", "dark creatures",
                "troll", "trolls", "goblin", "goblins",
                "ogre", "ogres" }),
        VBFC_ME("army_answer"));
    add_ask( ({ "dark", "darkness" }),
        VBFC_ME("dark_answer"));
    add_ask( ({"val shoreil", "val_shoreil"}),
        VBFC_ME("val_shoreil_answer"));
    add_ask( ({ "telan ri", "god", "telan-ri" }),
        VBFC_ME("telan_ri_answer"));
    add_ask( ({ "job", "occupation", "work", "career" }),
        VBFC_ME("job_answer"));
} /* add_telberin_asks */



/*
 * Function name:       keepers_answer
 * Description  :       response to an add_ask
 */
public string
keepers_answer()
{
    switch (random(3))
    {
    case 0:
        command("say The Keepers of Telberin have redoubled their"
              + " efforts in light of the recent raids.");
        break;
    case 1:
        command("say We in Telberin are proud of our people. We"
              + " will not so easily fall to a few disorganized"
              + " raiders from the mountains.");
        break;
    case 2:
        command("say Our motives are with the light, and our"
              + " military is strong.");
        break;
    }
    return "";
} /* keepers_answer */


/*
 * Function name:        job_answer
 * Description  :        repond to an add_ask
 */
public string
job_answer()
{
    command("smile polite");
    command("say " + Job_Response);

    return "";
} /* job_answer */


/*
 * Function name:       horse_answer
 * Description  :       response to an add_ask
 */
public string
horse_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Telberin has the finest breed of horses.");
        break;
    case 1:
        command("say Our horses aid us not only in the fields,"
              + " but on the battlefield also!");
    case 2:
        command("say Soon, our fair horses will be marching to"
              + " make war.");
        break;
    }
    return "";
} /* horse_answer */


/*
 * Function name:       telberin_answer
 * Description  :       response to an add_ask
 */
public string
telberin_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Telberin is proud, and fair. These raids have"
              + " done nothing to diminish its greatness.");
        break;
    case 1:
        command("say Our city will rise above this recent insult,"
              + " and we will drive the darkness from Emerald"
              + " once and for all!");
        break;
    case 2:
        command("say Telberin! Fairest Jewel of all Emerald. We"
              + " will make her great once again.");
        break;
    }
    return "";
} /* telberin_answer */


/*
 * Function name:       raid_answer
 * Description  :       response to an add_ask
 */
public string
raid_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Yes, not long ago our fair city was attacked"
              + " by foul raiders, and parts of it destroyed!");
        break;
    case 1:
        command("say These creatures of darkness will pay for their"
              + " actions! Telberin will never fall to such"
              + " as they.");
        break;
    case 2:
        command("say At first, it looked quite bad. The city walls"
              + " were breached, as we were taken by surprise. But"
              + " once the Protectorate and Keepers had mobilized,"
              + " the invaders were quickly driven back or"
              + " destroyed.");
        break;
    }
    return "";
} /* raid_answer */


/*
 * Function name:       emerald_answer
 * Description  :       response to an add_ask
 */
public string
emerald_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Emerald is a fair and wonderful land. How I long"
              + " for it to be cleansed of all darkness.");
        break;
    case 1:
        command("say We will eventually spread light into the far"
              + " corners of our fair domain.");
        break;
    case 2:
        command("say Personally, I have not been to many places which"
              + " are not near the City itself. Emerald is a very"
              + " large realm.");
        break;
    }
    return "";
} /* emerald_answer */


/*
 * Function name:       blackwall_answer
 * Description  :       response to an add_ask
 */
public string
blackwall_answer()
{
    switch (random(3))
    {
    case 0:
        command("say The Blackwall Mountains are in many places filled"
              + " with the creatures of darkness!");
        break;
    case 1:
        command("say We have lost much of our foothold in the Mountains,"
              + " and now they are filling with orcs, and other, more"
              + " dark beings.");
        break;
    case 2:
        command("say I have never been to the mountains. Few go there"
              + " anymore who are not in our armies.");
        break;
    }
    return "";
} /* blackwall_answer */


/*
 * Function name:       army_answer
 * Description  :       response to an add_ask
 */
public string
army_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Orcs, goblins, trolls, ogres ... terrible"
              + " and filthy creatures! We must rid Emerald of"
              + " their kind.");
        break;
    case 1:
        command("say Many such creatures attacked the city"
              + " recently. We will make them pay.");
        break;
    case 2:
        command("say The presence of these creatures is but a sign"
              + " of the fact that darkness is again rising in"
              + " Emerald. What could be behind it?");
        break;
    }
    return "";
} /* army_answer */


/*
 * Function name:       dark_answer
 * Description  :       response to an add_ask
 */
public string
dark_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Darkness once ruled all of Emerald. We do not"
              + " wish to see it return.");
        break;
    case 1:
        command("say There is nothing more terrible than darkness.");
        break;
    case 2:
        command("say Let us speak no more of it! Such evil has already"
              + " consumed enough of my thoughts.");
        break;
    }
    return "";
} /* dark_answer */


/*
 * Function name:       val_shoreil_answer
 * Description  :       response to an add_ask
 */
public string
val_shoreil_answer()
{
    switch (random(3))
    {
    case 0:
        command("say That name must never be spoken.");
        break;
    case 1:
        command("say God of Darkness! Why do you invoke his"
              + " terrible name?");
        break;
    case 2:
        command("say Name him not! Do you wish to bring darkness"
              + " upon us?");
        break;
    }
    return "";
} /* val_shoreil_answer */


/*
 * Function name:       telan_ri_answer
 * Description  :       response to an add_ask
 */
public string
telan_ri_answer()
{
    switch (random(3))
    {
    case 0:
        command("say We do his will, and light flourishes as a result.");
        break;
    case 1:
        command("say Our God and Maker. He shall deliver us from these"
              + " times of trouble.");
        break;
    case 2:
        command("say It is our goal to please him, and spread light"
              + " to all of Emerald.");
        break;
    }
    return "";
} /* telan_ri_answer */


/*
 * Function name:       catch_question
 * Description  :       intercept /std/act/asking.c's catch_question() to:
 *                      1) strip leading "for", "about" and trailing "?"
 *                      2) remember the original question
 * Arguments:           string question -- whatever the player asked
 */
public void
catch_question(string question)
{
    string      *tmp_arr,                       /* preps/verbs of interest */
                stuff1, stuff2, stuff3;         /* tmp strings */

    if (objectp(query_attack()))
    {
        return; /* no answers if fighting */
    }

    OrigQuestion = question;
    if (strlen(question))
    {
        /* strip off leading "for", "about" and trailing " ?" */
        tmp_arr = ({ "for", "about" });
        if (parse_command(question, ({}), "%p %s", tmp_arr, stuff1))
        {
            question = stuff1;
        }
        if (sscanf(question, "%s ?", stuff1) ||
            sscanf(question, "%s?", stuff1))
        {
            question = stuff1;
        }
    }
    ::catch_question(question);
} /* catch_question */


/*
 * Function name:       not_here_func
 * Description  :       called when player asks question & leaves
 * Returns      :       0 -> don't answer the question
 */
public int
not_here_func()
{
     command("peer");
     command("shout Nice talking with you!");
     return 0;
} /* not_here_func */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    string      question = query_question();

    if (strlen(question))
    {
        DEBUG_LOG(TP->query_real_name()+" questions an elf: '"+
            ((question != OrigQuestion) ? OrigQuestion+"' -> '" : "")+
                question+"'\n");
    }
    command("smile . "+this_player()->query_real_name());
    command("say I'm not sure I have much to say about that.");
    return "";
} /* default_answer */


/* 
 * Function name:       name_answer
 * Description  :       respond to questions about name
 *
 */
public string
name_answer()
{
    object      tp = TP;

    /* probably unnecessary, since we set not_here_func, but ... */
    if (!objectp(tp))
    {
        return "";
    }

        command("sneer");
        command("say It is good to meet you, "+
            TP->query_race_name()+".");
        command("say I wish you well.");

    return "";
} /* name_answer */


/*
 * Function name:       add_introduced
 * Description  :       Add the name of a living who has introduced to us
 * Arguments    :       string name -- name of the introduced living
 */
public void
add_introduced(string name)
{
    /* wizards always know the npc name, so query_met() is true.
     * however, assume that if a wiz intro'd, we should respond
     */
    if (interactive(TP) &&
        CAN_SEE_IN_ROOM(TO) &&
        CAN_SEE(TO, TP) &&
        (!TP->query_met(query_name()) ||
         TP->query_wiz_level()))
    {
        set_alarm(1.0 + (2.0 * rnd()), 0.0, &react_intro(TP));
    }
} /* add_introduced */


/*
 * Function name:        react_intro
 * Description  :        respond to introduction
 * Arguments    :        object tp -- the person who intro'd
 */
public void
react_intro(object tp)
{
    if (ENV(tp) != ENV())
    {
        command("hmm");
        return;
    }

    switch(random(6))
    {
    case 0:
        command("bow court "+tp->query_real_name());
        break;
    case 1:
        command("say Well met. You are a visitor to these lands, yes?");
        break;
    case 2:
        command("say What a curious name.");
        break;
    case 3:
        command("say Ah, very good to meet you.");
        break;
    case 4: 
        command("smile .");
        command("nod polite");

        break;
    case 5:
        command("say So nice to see some new faces around.");
        break;
    }
} /* react_intro */


/*
 * Function name:        give_gems
 * Description  :        give some of the elves gems
 */
public void
give_gems()
{
    object  gem;

    if (!random(3))
    {
        return;
    }

    if (!present("gem", this_object()))
    {
        gem = clone_object(GEM_DIR + ONE_OF_LIST(GEM_TYPES));
        gem->move(this_object());
    }
} /* give_gems */


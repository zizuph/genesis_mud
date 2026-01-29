/*
 * The lighthouse keeper at Pelargir
 *
 * /d/Gondor/pelargir/npc/lumendil.c
 *
 * Copyright (C) September 2, 1998 by Ron Miller (Tyr)
 *
 * Revision history:
 *    6/7/99: beacon tending added by Tyr
 *    6/28/99: incorporated Gnadnar's suggestions by Tyr
 */

#pragma strict_types

inherit "/d/Gondor/std/monster";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/pelargir/beacon_defs.h"

/* prototypes */
public void    create_gondor_monster();
public void    react_intro(object tp);
public void    add_introduced(string str);
public void    enter_inv(object ob, object from);
public void    return_object(object ob, object from);
public void    check_quest_obj(object ob, object from);
public string  ask_help();
public void    reward_player();
public void    activate_beacon();
public void    sunrise();
public void    sunset();

/*
 * Function name:    create_gondor_monster
 * Description:      create the lighthouse keeper, Lumendil
 */
public void
create_gondor_monster()
{
    FIX_EUID;    

    set_name( ({ "lumendil", "man", "keeper" }) );
    set_living_name("lumendil");
    set_race_name("human");
    set_title("the Lighthouse Keeper of Pelargir");
    set_adj( ({ "wary", "grey-haired" }) );

    set_long(BSN("He is a wizened old man with wispy grey hair and "+
        "faded blue eyes. Years of worry and battles with the elements "+
        "are deeply etched into the lines of his face."));

    default_config_npc(45 + random(10));

    set_base_stat(SS_CON, 75);
    set_base_stat(SS_INT, 75);
    set_base_stat(SS_WIS, 70);

    set_skill(SS_WEP_KNIFE,65);
    set_skill(SS_DEFENCE,75);
    set_skill(SS_PARRY,95);
    set_alignment(500);

    set_whimpy(25);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_chat_time(15 + random(15));
    add_chat("Hooligans from the town below keep stealing parts "+
        "of my beacon!");
    add_chat("The ship captains get really upset when this "+
        "lighthouse isn't operating properly.");
    add_chat("Life in this lighthouse is a living hell, not knowing "+
        "from one day to the next whether I'll be able to keep "+
        "the beacon working or not.");
    add_chat("Few things are more frightening than navigating "+
        "dangerous waters in the dark.");
    add_chat("The view from up here is one of the few rewards of "+
        "this thankless job.");
    add_chat("One more dark night without this beacon working and "+
        "I fear Carastur will have my head!");
    add_chat("The sunsets can be quite lovely from up here.");
    add_chat("Shipping traffic here in Pelargir increased when "+
        "the ship captains learned this lighthouse had been built.");
    add_chat("Loneliness is the worst thing about this job. And "+
        "if Carastur comes up to visit, it's only to pass along "+
        "complaints from the ship captains.");

    set_cchat_time(5 + random(10));
    add_cchat("Help! I'm being attacked!");
    add_cchat("You Idiot! All I do is tend the lighthouse!");
    add_cchat("Killing me will gain you nothing, you Fool!");
    add_cchat("I've never been much of a fighter, but since "+
        "you insist, I'll do my best.");
    add_cchat("I hope they throw you into the darkest of the dungeons "+
         "for this!");
    add_cchat("Sombody help me!");
    add_cchat("Please stop, I'm far too old and feeble to make this "+
        "worth your while.");
    add_cchat("What could you possibly hope to gain by killing me, "+
        "you fool?");

    add_ask( ({"help", "quest", "task"}), ask_help);
    
    add_ask( ({ "about carastur", "carastur" }) , 
        "say Lord Carastur is the ruler of Pelargir. I am afraid he would " +
	"not treat me kindly if he discovered that the beacon was gone.", 1);

    add_ask( ({ "lighthouse" }) , "say The beacon of this lighthouse is "+
        "all that saved many a ship from an unpleasant fate on the "+
        "shoals just outside our harbour.", 1);

    add_ask( ({ "about beacon", "beacon" }) , "say This beacon has three "+
        "critical components: a lantern, a mirror and a lens.  At "+
        "least when it's working, it does!", 1);

    add_ask( ({ "about hooligans", "hooligans" }) ,"say Ne'er-do-wells from "+
        "the town have made a business of helping the Corsairs disrupt "+
        "shipping here for fun and profit! They steal parts of my "+
        "beacon and trade them to the Corsairs for shares of their "+
        "ill-gotten gains.", 1);

    add_ask( ({ "about corsair", "corsair", "about corsairs", "corsairs" }) ,
        "say Corsairs indeed! That's just a polite way to say "+
        "pirates! They don't really want my beacon parts, they just "+
        "want it out of service so the ships going in and out of the "+
        "harbour will wreck on the shoals. Then they can plunder them "+
        "without a lot of that messy fighting stuff.", 1);

    add_ask( ({ "about lens", "lens", "about mirror", "mirror", "about "+
        "lantern", "lantern", "beacon parts", "parts" }) , "say I'm not "+
        "really sure what the Corsairs do with my beacon parts after "+
        "they steal them. Passing travellers occasionally mention "+
        "rumors of finding lighthouse parts near spots where the "+
        "scoundrels make camp.", 1);

    add_ask( ({ "rumors", "spots", "camp", "camps" }) , "say Corsairs are a "+
        "secretive lot...that's their stock in trade. They try to "+
        "maintain an air of respectability by carrying passengers from "+
        "several piers scattered about. If I had to guess, I'd say "+
        "their camps are well hidden, but not too far from their "+
        "piers.", 1);

    add_ask( ({ "pier", "piers" }) , "say The Corsairs never miss a chance "+
        "to make a quick copper or two. They make passenger runs from "+
        "a number of piers throughout the land. The closest one is "+
        "a short walk from the south city gate.", 1);

    add_ask( ({ "water", "waters", "dark" }) , "say Just take a look out the "+
        "window toward the river. Those shoals you see so clearly "+
        "from up here are almost invisible when you're on a boat down "+
        "on the river.", 1);

    set_equipment( ({ (WEP_DIR + "knife"),
                      (MINAS_DIR + "obj/ltunic"),
                      (OBJ_DIR + "oilflask") }) );
}   /* end create_gondor_monster */


/* Handling introductions to living */
void
react_intro(object tp)
{
    if (!present(tp, ENV(TO)))
    {
        command("shrug");
        return;
    }

    command("introduce me to "+tp->query_real_name());
    command("say Welcome to my lighthouse, " + tp->query_name() + "!");
} /* end react_intro */

public void
add_introduced(string str)
{
    if (!interactive(TP) ||
        TP->query_met(query_name()))
    {
        return;
    }
    set_alarm(2.0 + 5.0 * rnd(), 0.0, &react_intro(TP));
} /* end add_introduced */

/*
 * Function name:       enter_inv
 * Description  :       respond to gifts
 * Arguments    :       object ob -- the object we're given
 *                      object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(from) ||
        !objectp(ob) ||
        !living(from))
    {
        return;
    }

    if (file_name(ENV()) != LAMPROOM)
    {
        set_alarm(0.5, 0.0, &return_object(ob, from));
    }

    else if (ob->id(LANTERN_NAME) ||
             ob->id(MIRROR_NAME) ||
             ob->id(LENS_NAME))
    {
        set_alarm(1.0, 0.0, &check_quest_obj(ob, from));
    }

    else
    {
        set_alarm(0.5, 0.0, &return_object(ob, from));
    }
} /* end enter_inv */

/*
 * Function name:       return_object
 * Description  :       return gifts of no interest
 * Arguments    :       object ob -- the gift
 *                      object from -- its source
 */
public void
return_object(object ob, object from)
{
    string      name;
    object      env = ENV();

    if (ob->id("coin"))
    {
        command("smile");
        command("say Many thanks! All donations are greatly "+
                "appreciated.");
        return;
    }

    if (file_name(env) == LAMPROOM)
    {
        command("say I thank you kindly for that, but right now I "+
            "have no need of it.");
    }

    else
    {
        command("say Perhaps I can use that the next time I'm at the "+
            "beacon.");
    }

    if (objectp(from) &&
        ENV(from) == env)
    {
        name = from->query_real_name();
        command("give "+OB_NAME(ob)+" to "+name);
    }

    /* do the following even if we did "give". it can't hurt,
     * and is good insurance in case give failed
     */
    command("drop "+OB_NAME(ob));
    if (ENV(ob) == TO)
    {
        ob->move(env, 1);
    }
} /* end return_object */

/*
 * Function name:       check_quest_obj
 *
 * Description  :       Lumie puts beacon parts in brackets
 * Arguments    :       object ob -- the lens, mirror or lantern
 *                      object from -- its source
 */
public void
check_quest_obj(object ob, object from)
{
    object      bracket,
                env = ENV();
                string   name;

    if (ob->id(LENS_NAME))
    {
        bracket = present("lens bracket", env);
        if (!objectp(bracket))
        {
            env->reset_room();
            /* lets assume that it must exist now */
            bracket = present("lens bracket", env);
        }

        if (!sizeof(all_inventory(bracket)))
        {
            command("say Most excellent! Thanks for your help.");
            command("put lens in lens bracket");
	    TP->add_prop(LENS_NAME, 1);
        }

        else
        {
            /* lens already in bracket */
            command("say I'm using the spare lens right now. "+
            "Perhaps that one will prove more useful if you bring "+
            "it back another time.");
 
            if (objectp(from) &&
                ENV(from) == env)
            {
                name = from->query_real_name();
                command("give "+OB_NAME(ob)+" to "+from->
                    query_real_name());
                command("drop "+OB_NAME(ob));

                if (ENV(ob) == TO)
                {
                    /* paranoia */
                    ob->move(env, 1);
                }
            }
        }
    }

    if (ob->id(MIRROR_NAME))
    {
        bracket = present("mirror bracket", env);

        if (!objectp(bracket))
        {
            env->reset_room();
            /* lets assume that it must exist now */
            bracket = present("mirror bracket", env);
        }

        if (!sizeof(all_inventory(bracket)))
        {
            command("say Outstanding! We'll have this thing repaired "+
                    "in no time.");
            command("put mirror in mirror bracket");
	    TP->add_prop(MIRROR_NAME, 1);
        }

        else
        {
            /* mirror is already in bracket */
            command("say I'm using the spare mirror right now. "+
                "Perhaps that one will prove more useful if you bring "+
                "it back another time.");

            if (objectp(from) &&
                ENV(from) == env)
            {
                name = from->query_real_name();
                command("give "+OB_NAME(ob)+" to "+from->
                    query_real_name());
                command("drop "+OB_NAME(ob));

                if (ENV(ob) == TO)
                {
                    /* paranoia */
                    ob->move(env, 1);
                }
            }
        }
    }

    if (ob->id(LANTERN_NAME))
    {
        bracket = present("lantern bracket", env);

        if (!objectp(bracket))
        {
            env->reset_room();
            /* lets assume that it must exist now */
            bracket = present("lantern bracket", env);
        }

        if (!sizeof(all_inventory(bracket)))
        {
            command("say This is most helpful, indeed. I am truly in "+
                    "your debt.");
            command("put lantern in lantern bracket");
	    TP->add_prop(LANTERN_NAME, 1);
        }

        else
        {
            /* lantern is already in bracket */
            command("say I'm using my last spare lantern right now. "+
                "Perhaps that one will prove more useful if you bring "+
                "it back another time.");

            if (objectp(from) &&
                ENV(from) == env)
            {
                name = from->query_real_name();
                command("give "+OB_NAME(ob)+" to "+from->
                    query_real_name());
                command("drop "+OB_NAME(ob));

                if (ENV(ob) == TO)
                {
                    /* paranoia */
                    ob->move(env, 1);
                }
            }
        }
    }
    
    activate_beacon();
} /* end check_quest_obj */

/*
 * Function name:       activate_beacon()
 *
 * Description  :       Lumie puts the beacon in service
 */
public void
activate_beacon()
{
    string timestr;
    object env = ENV(),
           bracket,
           lantern;

    if (file_name(env) == LAMPROOM)
    {
        switch (env->lantern_state())
        {
            case NONE_HERE:
            break;

            case LENS_HERE:
            /* FALLTHROUGH */

            case LANTERN_HERE:
            /* FALLTHROUGH */

            case MIRROR_HERE:
            command("say Now if we can only recover the other parts.");
            break;

            case LENS_LANTERN_HERE:
            /* FALLTHROUGH */

            case LENS_MIRROR_HERE:
            /* FALLTHROUGH */

            case LANTERN_MIRROR_HERE:
            command("say This is real progress! Only one more part is "+
                     "lacking!");
            break;

            case ALL_HERE:
            command("say At last, I can finally warn the ships of the "+
                     "dangers below!");
            command("emote fills the lantern with oil from the nearby "+
                     "keg.");
	    if (TP->query_prop(LANTERN_NAME) && TP->query_prop(MIRROR_NAME) &&
		TP->query_prop(LENS_NAME))
		reward_player();
            /* we know that the lantern bracket and lantern are in place,
             * since state is ALL_HERE. no need to call objectp().
             */
            bracket = present(LANTERN_BRACKET, env);
            lantern = present(LANTERN_NAME, bracket);
            lantern->set_time(4000);
  
            if ((timestr = env->tod()) == "evening" ||
                timestr == "night" ||
                timestr == "early morning")
            {
                command("emote lights the lantern.");
                lantern->light_me();
            }
            break;
        }
    }
} /* end activate_beacon */

public void
reward_player()
{
    string name = TP->query_real_name();
    command("say to " + name + " Thank you very much!");

    FIX_EUID
    if (!TP->test_bit("Gondor", PELARGIR_LIGHTHOUSE_GROUP,
		      PELARGIR_LIGHTHOUSE_BIT))
    {
        TP->set_bit(PELARGIR_LIGHTHOUSE_GROUP, PELARGIR_LIGHTHOUSE_BIT);
        TP->add_exp_quest(PELARGIR_LIGHTHOUSE_EXP);
	TP->adjust_alignment(200);
        TP->catch_tell("You feel more experienced!\n");
        LOG_QUEST(TP, PELARGIR_LIGHTHOUSE_EXP, "PELARGIR LIGHTHOUSE");
    }
}

/*
 * Function name:       sunrise()
 *
 * Description  :       Lumie tends the beacon at sunrise
 */
public void
sunrise()
{
    object env = ENV(),
           bracket,
           lantern;

    if ((file_name(env) == LAMPROOM) && 
        env->lantern_state() == ALL_HERE)
    {
        command("say I'd better save all the oil I can for the "+
                "coming nights. ");
        command("emote extinguishes the lantern.");
        bracket = present(LANTERN_BRACKET, env);
        lantern = present(LANTERN_NAME, bracket);

        /* we know that the lantern bracket and lantern are in place,
         * since state is ALL_HERE. no need to check objectp().
         */
        lantern->extinguish_me();
    }
}  /* end sunrise */    

/*
 * Function name:       sunset()
 *
 * Description  :       Lumie tends the beacon at sundown
 */
public void
sunset()
{
    object env = ENV(),
           bracket,
           lantern;

    if ((file_name(env) == LAMPROOM) &&
       env->lantern_state() == ALL_HERE)
    {
        command("say Time to prepare for a long night's vigil.");
        command("emote refills the lantern with oil from the "+
                "nearby keg and lights it. ");
        bracket = present(LANTERN_BRACKET, env);
        lantern = present(LANTERN_NAME, bracket);

        /* we know that the lantern bracket and lantern are in place,
         * since state is ALL_HERE. no need to check objectp().
         */
        lantern->set_time(4000);
        lantern->light_me();
    }
}  /* end sunset () */

public string
ask_help()
{
    string answer;
    int state;
    
    if (file_name(environment()) == LAMPROOM)
    {
	state = environment()->lantern_state();
	if (state ==  NONE_HERE)
        {
	    command("say Would you really help me?");
	    command("smile hopefully");
	    command("say This lighthouse helps guide the ship captains "+
                    "safely into the harbour below. But hooligans from "+
                    "down in the city keep sneaking up here and "+
                    "stealing the critical parts of my beacon.");
            command("say The admiral of the fleet says the ship "+
                    "captains may refuse to dock here if we cannot "+
                    "guide them safely into port.");
 	    command("say I would be eternally grateful if you would "+
                    "find the stolen parts and bring them back to me "+
                    "so I can do my job here.");
            START_QUEST(TP, "PELARGIR LIGHTHOUSE");
	}
	else if (state == ALL_HERE)
        {
	    command("say It's nice of you to ask, but I have " +
		    "everything I need at the moment.");
	    command("smile");
	}
	else // Some parts here
        {
	    if (TP->query_prop(LANTERN_NAME) || TP->query_prop(MIRROR_NAME) ||
		TP->query_prop(LENS_NAME))
	    {
		command("ponder");
		command("say I still need your help to find the other parts" +
			" of the beacon.");
	    }
	    else
            {
		command("say Thank you very much, someone else is "+
                        "already helping me at the moment.");
	    }
	}
    }
    else
    {
	command("say Uh, not now thanks. First I need to find my way " +
		"back to top floor.");
    }
    return "";
}

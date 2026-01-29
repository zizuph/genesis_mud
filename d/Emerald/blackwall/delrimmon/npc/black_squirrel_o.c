/*
 *  /d/Emerald/blackwall/delrimmon/obj/black_squirrel.c
 *
 *  This is a little squirrel that can by picked up and carried
 *  around by the clever adventurer. Orcs don't like it much.
 *
 *  Copyright (c) July, 1997 by Gorboth (Cooper Sherry)
 */
#pragma strict_types

inherit "/d/Gondor/std/monster.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public string  squirrel_long();
public mixed   squirrel_gift();
public mixed   get_squirrel();
public void    eat_acorn();
public string  squirrel_actions();
public void    squirrel_escape();
public string  squirrel_attacked();
public int     feed_squirrel(object ob);
public void    ignore_object(object obj);
public void    enter_inv(object ob, object from);
public void    show_hook(object ob);


/* global variables */
public int    Eating_Acorn = 0;
static mixed *Squirrel_Messages = ({
                 " chitters rapidly.",
                 " crouches suddenly.",
                 " stops perfectly still, peering at you intently.",
                 " darts rapidly to and fro.",
                 " dives into a nearby bush, and then jumps out again.",
                 " twitches its whiskers at you.",
                 " peers intently at you.",
                 " scampers vigorously around you.",
               });

public void  set_acorn(int i)    { Eating_Acorn = i; }
public int   query_acorn()       { return Eating_Acorn; }


/*
 * function name:        create_gondor_monster
 * description  :        set up the npc
 */
public void
create_gondor_monster()
{
    set_name("squirrel");
    add_name(({ "animal","creature","rodent" }));
    add_pname(({ "animals","creatures","rodents" }));
    add_adj(({"tiny","black","small","little",}));
    set_race_name("rodent");

    set_short("tiny black squirrel");
    set_long(squirrel_long);

    default_config_npc(7);
    add_prop(CONT_I_WEIGHT, 50);
    add_prop(CONT_I_VOLUME, 200); /* little fella */
    add_prop(OBJ_M_NO_ATTACK, squirrel_attacked);
    add_prop(OBJ_M_NO_GET, get_squirrel);
    add_prop(NPC_M_NO_ACCEPT_GIVE, squirrel_gift);

    set_act_time(1);
   /*
    * The added argument in add_act() allows the action to
    * be performed even when the squirrel is not in a room
    * where a mortal is present. I do this so that the
    * actions will be performed should the squirrel find
    * itself in someone's inventory. If you don't understand,
    * or do not agree, please read the code in eat_acorn().
    */
    add_act(VBFC_ME("squirrel_actions"), 1);
} /* create_gondor_monster */


/*
 * function name:        squirrel_long
 * description  :        describe the squirrel, variable
 *                       for if it is eating an acorn or not
 * returns      :        string -- the squirrel description
 */
public string
squirrel_long()
{
    string  squirrel_txt = "This squirrel seems to be ";

    if (!Eating_Acorn)
    {
        squirrel_txt += "rather hungry.";
    }
    else
    {
        squirrel_txt += "very excited about the acorn it is eating.";
    }

    squirrel_txt += " Smaller and more dextrous than many woodland"
                  + " creatures, it looks quite able to avoid the grasp"
                  + " of anyone it does not trust. This tiny black"
                  + " creature looks like it could almost fit right"
                  + " into your pocket.";

    if (interactive(environment()))
    {
        squirrel_txt += " It is sitting quietly in your lap.";
    }

    return BSN(squirrel_txt);
} /* squirrel_long */


/*
 * function name:        squirrel_gift
 * description  :        if the squirrel is eating an acorn, it does
 *                       not care about gifts, and doesn't accept
 *                       any.
 * returns      :        string -- failure message if eating
 *                       0 -- we let them get a gift.
 */
public mixed
squirrel_gift()
{
    if (Eating_Acorn)
    {
        return " is too busy eating the acorn to pay attention to"
             + " anything else you could offer it.\n";
    }

    return 0;
} /* squirrel_gift */


/*
 * function name:        get_squirrel
 * description  :        players may try to get the squirrel, but unless
 *                       the creature is distracted by its yummy meal,
 *                       it will scamper out of reach.
 * returns      :        string -- failure text,
 *                       0 -- ok, we let the player get them
 */
public mixed
get_squirrel()
{
    if (Eating_Acorn)
        return 0;

    return BSN("The squirrel scampers out of your reach, and"
            + " then stops to peer at you again, chittering"
            + " hungrily.");
} /* get squirrel */


/*
 * function name:        eat_acorn
 * description  :        this function is called whenever the squirrel
 *                       tries to do an add_act, and it is eating the
 *                       acorn. Each call reduces the size of the acorn,
 *                       and delivers an appropriate message to the
 *                       player
 */
public void
eat_acorn()
{
    object  tp = ENV(TO);
    string  eattxt = "The squirrel nibbles hungrily on"
                    + " the acorn it is clutching.";

    if (Eating_Acorn < 3)
    {
        eattxt = "The squirrel seems to have nearly finished"
               + " eating the acorn it is clutching.";
    }

    if (interactive(tp))
    {
        if (Eating_Acorn < 2)
        {
            tell_object(tp, BSN("Having finished eating the acorn,"
                              + " the squirrel suddenly realizes"
                              + " where it is."));
            set_alarm(1.0, 0.0, &squirrel_escape());
            all_inventory(TO)->remove_object();
            Eating_Acorn = 0;
            return;
        }

        tell_object(tp, BSN(eattxt));
    }

    else
    {
        if (Eating_Acorn < 2)
        {
            tell_room(tp, BSN("With a final nibble, the squirrel"
                            + " devours the last morsel that remains"
                            + " of the acorn, and looks up again,"
                            + " chittering hungrily."));
            Eating_Acorn = 0;
            return;
        }

        tell_room(tp, BSN(eattxt));
    }

    Eating_Acorn--;
    return;
} /* eat_acorn */


/*
 * function name:        squirrel_actions
 * description  :        this is our VBFC for add_act. if the squirrel
 *                       is eating an acorn, we have it nibble away
 *                       at its morsel, otherwise, we just return one
 *                       of various squirrel emotions.
 * returns      :        an emotion, or an empty string if Eating_Acorn
 */
public string
squirrel_actions()
{
    if (Eating_Acorn)
    {
        eat_acorn();
        return "";
    }

    return "emote" + ONE_OF_LIST(Squirrel_Messages);
} /* squirrel_actions */


/*
 * function name:        squirrel_escape
 * description  :        if the squirrel is held by someone, it jumps
 *                       out of their inventory. it tries to run away
 */
public void
squirrel_escape()
{
    object tp = ENV(TO);

    if (interactive(environment()))
    {
        tp->catch_msg(BSN("The squirrel leaps from your clutches,"
          + " chittering madly!"));
        tell_room(ENV(tp), "Without warning, a squirrel"
          + " leaps from " + QTNAME(tp) + "'s clutches"
          + ", chittering madly!\n", tp);
        TO->move(ENV(tp));
        TO->move(ENV(ENV(TO)));
    }

    this_object()->run_away();
    return;
} /* squirrel_escape */


/*
 * function name:        squirrel_attacked
 * description  :        if the squirrel is attacked, we make it
 *                       try to escape.
 * returns      :        string -- a message telling the player
 *                                 what happened.
 */
public string
squirrel_attacked()
{
    set_alarm(1.0, 0.0, &squirrel_escape());

    return BSN("As the squirrel realizes what you are about to"
             + " do, it scurries out of reach.");
} /* squirrel_attacked */


/*
 * function name:        feed_squirrel
 * description  :        we set the status of Eating_Acorn to true
 *                       if the squirrel has indeed been given an
 *                       acorn.
 * arguments    :        object ob -- what the squirrel was given
 * returns      :        1
 */
public int
feed_squirrel(object ob)
{
    tell_room(ENV(TO), BSN(
        "The squirrel is absolutely enthralled with the acorn."
      + " Sitting perfectly still, it begins chewing frantically at"
      + " the tasty morsel."));

    if (ob->id("_del_rimmon_acorn"))
    {
        set_acorn(ob->query_acorn_size());
        return 1;
    }

    set_acorn(1);

    return 1;
} /* feed_squirrel */


/*
 * function name:        ignore_object
 * description  :        called when the squirrel is not interested
 *                       in something it has been given.
 * arguments    :        object obj -- what the squirrel was given
 */
public void
ignore_object(object obj)
{
    string  obname = OB_NAME(obj);

    command("drop " + obname);
    tell_room(ENV(TO), BSN(
        "The squirrel sniffs at the " + obj->short()
      + " and then scampers away, uninterested."));

    return;
} /* ignore_object */


/*
 * function name:        enter_inv
 * description  :        we want to let the squirrel eat acorns it finds,
 *                       so we make that check here.
 * arguments    :        object ob -- what entered the inv
 *                       object from -- where it came from
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (ob->id("acorn"))
    {
        set_alarm(1.0, 0.0, &feed_squirrel(ob));
        return;
    }

    set_alarm(0.5, 0.0, &ignore_object(ob));
    return;
} /* enter_inv */

/*
 * function name: show_hook
 * description  : this hook is called whenever an item is 'shown' to this
 *                living. It is shown by this_player().
 * arguments    : object ob - the object shown.
 */
public void
show_hook(object ob)
{
    if (!ob->id("acorn"))
    {
        WRITE("The squirrel sniffs at the " + ob->short()
            + " and then scampers away, uninterested.");
        return;
    }

    WRITE("The squirrel sniffs hungrily at the " + ob->short()
        + " and then scampers back a few paces, peering at you"
        + " intensely.");
    return;
} /* show_hook */

/*
 *  /d/Emerald/blackwall/delrimmon/antique_dealer.c
 *
 *  This file has functions which allow certain individuals who
 *  inherit it to respond to antique weapons with interest.
 *
 *  Copyright (c) December 1998, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "/d/Emerald/quest_handler/quest_handler.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    check_for_antique(object tp);
public int     react_to_antique(object obj, object player);
public int     trade_antique(object antique, object trader);
public void    show_hook(object ob);
public string  antique_ask();

/*
 * function name:        check_for_antique
 * description  :        we look to see if the player has anything
 *                       on them that we think looks valuable
 */
public void
check_for_antique(object tp)
{
    object  antique;

    if (QH_QUERY_QUEST_COMPLETED(tp, "antique_sword"))
    {
        return;
    }

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, tp))
    {
        return;
    }

    if (objectp(antique = present("_del_rimmon_antique_sword", tp)))
    {
        command("gasp");
        command("say to " +tp->query_real_name()
              + " That rusty sword ... you simply must let me see it!");
        command("peer hopefully " +tp->query_real_name());
        return;
    }

    return;
} /* check_for_antique */

/*
 *  function name:        react_to_antique
 *  description  :        the npcs reacts to having been given an
 *                        antique that s/he finds interesting
 *  arguments    :        obj - the object in question,
 *                        player - the person who gave it to us
 *  returns      :        1 - if we react to it, 0 - otherwise
 */
public int
react_to_antique(object obj, object player)
{
    if (obj->id("_del_rimmon_antique_sword"))
    {
        if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, player))
        {
            command("say What is going on? I can't see you!");
            command("drop " + obj->short());
        
            return 1;
        }

        if (QH_QUERY_QUEST_COMPLETED(player, "antique_sword"))
        {
            command("say Ahh ... so you've found another! Well,"
              + " I still treasure the one you found me. I'm"
              + " afraid I cannot afford buying another from"
              + " you.");
            command("give " +obj->short()+ " to "
              + player->query_real_name());

            return 1;
        }      

        if (obj->query_found() != player)
        {
            command("say Heavens! Whoever it was that gave you that"
              + " sword has found a great treasure indeed! I would"
              + " very much like to speak to them in person.");
            command("give " +obj->query_short()+ " to "
              + player->query_real_name());

            return 1;
        }

        if (player->query_prop("_del_rimmon_antique_trade"))
        {
            command("say to " +player->query_real_name()
                  + " Yes, it truly is a remarkable find!"
                  + " My offer still stands. 'Trade' it to me, and"
                  + " I'll give you the platinum coins.");
            command("give " +obj->short()+ " to "
                  + player->query_real_name());

            return 1;
        }

        command("say to " +player->query_real_name()
              + " This is remarkable! Hundreds and hundreds of years"
              + " old, and still in such condition!");
        command("say to " +player->query_real_name()
              + " 'Trade' this to me, and I'll give you five platinum"
              + " coins.");
        player->add_prop("_del_rimmon_antique_trade", 1);
        command("give " +obj->query_short()+ " to "
              + player->query_real_name());

        return 1;
    }

    return 0;
} /* react_to_antique */

/*
 * function name:        trade_antique
 * description  :        the npc trades something for the antique
 * returns      :        1 - success, 0 - failure
 */
public int
trade_antique(object antique, object trader)
{
    trader->catch_msg("You trade the rusty sword to " + QTNAME(TO)
        + ", who excitedly whisks it out of sight.\n");
    say(QTNAME(trader) + " trades a rusty sword to " + QCTNAME(TO)
        + ", who excitedly whisks it out of sight.\n", trader);

    MONEY_MAKE_PC(5)->move(TO, 1);
    antique->remove_object();
    command("give 5 platinum coins to " + trader->query_real_name());

    if (QH_QUEST_COMPLETED(trader, "antique_sword"))
    {
        trader->catch_tell("You feel more experienced!\n");
    }

    trader->add_prop("_del_rimmon_antique_trade", 0);


    return 0;
} /* trade_antique */

/*
 * function name: show_hook
 * description  : this hook is called whenever an item is 'shown' to this
 *                living. It is shown by this_player().
 * arguments    : object ob - the object shown.
 */
public void
show_hook(object ob)
{
    object  player = TP;

    react_to_antique(ob, player);
} /* show_hook */

/*
 * function name:        antique_ask
 * description  :        the npc might have something to say about
 *                       the antique sword, if the player has it
 */
public string
antique_ask()
{
    command("say I have a passion for antique weapons"
          + " from Telberin's past. Show me any you have!");
    return "";
} /* antique_ask */

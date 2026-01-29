/*
 * Code for the Officers of the Rangers of the North
 *
 * Contains commands to take in new members and expel members.
 *
 * Copyright, Rolf Braun aka Elessar, Genesis 1998.
 */

#include "/d/Gondor/defs.h"
#include "ranger_defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <formulas.h>

int
expel_ranger(string str)
{
    object player, tp = TP;
    string  who, reason;

    if (!strlen(str))
        NFN0("Expel <who> because <reason>?");

    if (sscanf(str, "%s because %s", who, reason) != 2)
        NFN0("Expel <who> because <reason>?");

    who = LOW(who);

    if (!(player = find_player(who)))
    {
        if (!NORTH_MASTER->query_member(who))
        {
            write("That is not a Ranger of the North.\n");
            return 1;
        }
        NORTH_MASTER->expel_member(who, reason);
        write("You expel " + CAP(who) + " from the Rangers of the North "
          + "because " + reason + ".\n");
        return 1;
    }
    else
    {
        if (!IS_NRANGER(player))
        {
            write(CAP(who) + " is not a Ranger of the North!\n");
            return 1;
        }
        write("You expel " + CAP(who) + " from the Rangers of the North "
          + "because " + reason + ".\n");
        player->catch_msg("Captain " + tp->query_name() + " expels you "
          + "from the Rangers of the North!\n");
        NORTH_MASTER->expel_player(who, reason);
        return 1;
    }
    return 1;
}

int
release_ranger(string str)
{
    object player, tp = TP;
    string  who, reason;

    if (!strlen(str))
        NFN0("Release <who> because <reason>?");

    if (sscanf(str, "%s because %s", who, reason) != 2)
        NFN0("Release <who> because <reason>?");

    who = LOW(who);

    if (!(player = find_player(who)))
    {
        if (!NORTH_MASTER->query_member(who))
        {
            write("That is not a Ranger of the North.\n");
            return 1;
        }
        NORTH_MASTER->release_member(who, reason);
        write("You release " + CAP(who) + " from the Rangers of the North "
          + "allowing for an honourable discharge.\n");
        return 1;
    }
    else
    {
        if (!IS_NRANGER(player))
        {
            write(CAP(who) + " is not a Ranger of the North!\n");
            return 1;
        }
        write("You release " + CAP(who) + " from the Rangers of the North "
          + "allowing " + player->query_objective() + " an honourable discharge.\n");
        player->catch_msg("Captain " + tp->query_name() + " releases you "
          + "from the Rangers of the North, allowing you to leave with honour.\n");
        NORTH_MASTER->release_player(who, reason);
        return 1;
    }
    return 1;
}

int
offer_to_join(string str)
{
    object  player, 
            recobj,
            tp = TP;
    string  name;

    if (!strlen(str))
        NFN0("Offer what? Offer position to someone?");
    if (sscanf(str, "position to %s", name) != 1)
        NFN0("Offer position to who?");

    name = LOW(name);
    if (!(player = find_player(name)))
        NFN0("You don't see " + CAP(name) + " here.");
    if (!present(player, ENV(tp)))
        NFN0("You don't see " + OBJECTIVE(player) + " here.");

    if (player->query_guild_name_occ())
    {
        NFN0("You have a feeling " + QCTNAME(player) + " wouldn't be interested.");
    }
    if (!IS_DUNADAN(player))
    {
        NFN0("It would be against all traditions to accept someone who is not "
          + "of Dunadan heritage into the Rangers of the North.");
    }
    if (player->query_alignment() < 150)
    {
        NFN0("You think twice as you somehow sense that " + QTNAME(player)
          + " might not be all that trustworthy.");
    }

    write("You offer to make " + CAP(name) + " a Ranger of the North.\n");
    player->catch_msg(QCTNAME(tp) + " offers you a position within the ranks of the "
      + "Rangers of the North. Do you wish to accept?\n");
    write_file(NORTH_LOG, tp->query_name() + " offers " + CAP(name)
      + " to join the Rangers of the North. " + ctime(time()) + ".\n");
    FIX_EUID
    recobj = clone_object(RANGER_NORTH_DIR + "obj/recruit_obj");
    recobj->set_recruiter(tp);
    recobj->set_recruit(player);
    recobj->move(player);
    return 1;
}


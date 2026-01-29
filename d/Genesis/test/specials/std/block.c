/*
 * /d/Genesis/specials/std/block.c
 *
 * This is the block ability. It blocks by placing a block shadow
 * on the person being blocked. The block shadow will do all the
 * necessary checking.
 *
 * Created by Novo, adapted to use resolve_task by Petros
 */
 
#pragma strict_types

#include "defs.h"

inherit TIMED_ABILITY_LIB;


#define BLOCK_SH ("/d/Genesis/specials/std/block_sh")
#define BLOCK_LOG ("/d/Genesis/log/BLOCK_LOG")

#ifndef SS_BLOCK
#define SS_BLOCK 26
#endif

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include "/std/combat/combat.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define TP            this_player()
#define TO            this_object()
#define QSW           query_shadow_who()
#define POSS(obj)     obj->query_possessive()
#define PRO(obj)      obj->query_pronoun()
#define OBJ(obj)      obj->query_objective()
#define SHORT(obj)    obj->short()

public mixed * target_block(object actor, string str);

public void config_ability()
{
    ::config_ability();
    set_ability_time(0);
    set_ability_name("block");
    set_ability_offensive(1);
    
    set_ability_target(target_block);
}


/* No prepare to block message */
static void ability_msg(object actor,mixed * targets,string arg)
{
}

private string
composite_living_vbfc(mixed players)
{
    string result;
    
    result = "";
    switch (sizeof(players))
    {
    case 0:
        break;
            
    case 1:
        result = QTNAME(players[0]);
        break;
    
    case 2:
        result = QTNAME(players[0]) + " and " + QTNAME(players[1]);
        break;
    
    default:       
        foreach (object player : players[..-2])
        {
            result += QTNAME(player) + ", ";
        }
        result += "and " + QTNAME(players[-1..][0]);
    }
    
    return result;
}

static void resolve_ability(object actor, mixed * items, 
            mixed * targets, int * resist, mixed * results)
{
    object blockee, block_shadow;
    object * other_blockers;
    string exit, blocker_msg, blockee_msg, watcher_msg;
    string coblocker_msg, coblockers;
    string blocker_name, blockee_name, room_name;
    int already_blocking;
    
    blockee = targets[0][0];
    exit = targets[0][1];
    if (!blockee->has_block_shadow())
    {
        seteuid(getuid());
        block_shadow = clone_object(BLOCK_SH);
        block_shadow->shadow_me(blockee);
    }
    
    room_name = MASTER_OB(environment(actor));
    if (interactive(actor))
    {
        blocker_name = capitalize(actor->query_real_name());
    }
    else
    {
        blocker_name = MASTER_OB(actor);
    }
    if (interactive(blockee))
    {
        blockee_name = capitalize(blockee->query_real_name());
    }
    else
    {
        blockee_name = MASTER_OB(blockee);
    }
    send_debug_message("block", blocker_name + " blocks "
                     + blockee_name + " at the " + exit
                     + " exit in the room " 
                     + room_name + ".",
                       BLOCK_LOG);
    other_blockers = blockee->query_blockers_for_exit(exit);
    already_blocking = IN_ARRAY(actor, other_blockers);
    other_blockers -= ({ actor });
    if (already_blocking)
    {
        actor->catch_msg("You have already placed yourself between the "
                       + exit + " exit and " + QTNAME(blockee) + ".\n");
        return;
    }
    else if (sizeof(other_blockers) == 0)
    {
        blocker_msg = "You move to place yourself between " 
                    + QTNAME(blockee) + " and the " + exit + " exit.\n";
        blockee_msg = QCTNAME(actor) + " moves to place "
                    + actor->query_objective() + "self between you and "
                    + "the " + exit + " exit.\n";
        watcher_msg = QCTNAME(actor) + " moves to place "
                    + actor->query_objective() + "self between "
                    + QTNAME(blockee) + " and the " + exit + " exit.\n";
    }
    else
    {
        coblockers = composite_living_vbfc(other_blockers);
        blocker_msg = "You join " + coblockers + " in blocking the "
                    + exit + " exit against " + QTNAME(blockee) + ".\n";
        blockee_msg = QCTNAME(actor) + " joins " + coblockers + " in "
                    + "blocking the " + exit + " exit against you.\n";
        coblocker_msg = QCTNAME(actor) + " joins you in blocking the "
                      + exit + " exit against " + QTNAME(blockee) +  ".\n";
        watcher_msg = QCTNAME(actor) + " joins " + coblockers + " in "
                    + "blocking the " + exit + " exit against "
                    + QTNAME(blockee) + ".\n";
        other_blockers->catch_msg(coblocker_msg);                    
    }
    // Show the messages to the people involved.
    actor->catch_msg(blocker_msg);    
    blockee->catch_msg(blockee_msg);
    tell_room(environment(actor), watcher_msg, 
              ({ actor, blockee }) + other_blockers);
    // Now add the blocker.
    blockee->add_blocker(actor, exit);
}



public mixed *
target_block(object actor, string str)
{
    if (!actor->query_skill(SS_BLOCK))
    {
        actor->catch_msg("What?\n");
        return ({ });
    }

    if (!strlen(str))
    {
        actor->catch_msg("Block who from going where?\n");
        return ({ });
    }

    string location="";
    
    object * candidates = 
        FILTER_LIVE(all_inventory(environment(actor)) - ({ actor }));
    
    mixed match;
    
    if (!parse_command(str,candidates,"%w [exit] 'for' / 'to' %l",
                    location,match) &&
        !parse_command(str,candidates,"%l [from] [going] %w",
                    match,location)  &&
        !parse_command(str,({ }),"%w [exit]",location))
    {
        actor->catch_msg("Block who from going where?\n");
        return ({ });
    }
    
    if (match && pointerp(match))
    {
        match=match[1];
    }
    else
    {
        match=actor->query_attack();
    }
    
    if (!objectp(match))
    {
        actor->catch_msg("Block who from going where?\n");
        return ({ });
    }
    
    // Get all the normal exits
    string * names =({ });
    
    mixed exits=environment(actor)->query_exit();

    for (int i=1;i<sizeof(exits);i+=3)
    {
        names+=({ exits[i] });
    }

    if (member_array("climb",get_localcmd(actor))>=0)
    {
        names+=({ "climb" });
    }

    if (member_array("swim",get_localcmd(actor))>=0)
    {
        names+=({ "swim" });
    }

    // Now check for door exits
    object * objects = all_inventory(environment(actor));
    foreach (object obj : objects)
    {
        // Check if it's a door
        if (IN_ARRAY("/std/door.c", inherit_list(obj))
            && sizeof(obj->query_pass_command()) > 0)
        {
            names += obj->query_pass_command();
            break;
        }
    }

    if (!sizeof(names) || member_array(location,names)<0)
    {
        actor->catch_msg("You find no "+location+" exit to block.\n");
        return ({ });
    }

    return ({  ({ match, location }) });

}

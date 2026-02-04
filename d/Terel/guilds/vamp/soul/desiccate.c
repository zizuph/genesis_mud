/*
 * Changelog:
 *  November 2009 - Adding code to allow draining of blood from corpses when
 *                  they are desiccated. Petros
 */
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>

/*
void
do_desiccate(object ob)
{
    string sh = "@@short:" + file_name(ob) + "@@";
    object env, *players, *can_see_actor, *can_see_corpse;

    env = ((environment(ob) == this_player()) ? 
        environment(this_player()) : environment(ob));
    players = FILTER_PLAYERS(all_inventory(env));
    can_see_actor = can_see_corpse = FILTER_CAN_SEE_IN_ROOM(players);
    can_see_actor = FILTER_CAN_SEE(can_see_actor - ({ this_player() }), this_player());
    can_see_corpse = FILTER_CAN_SEE(can_see_corpse, ob);

    this_player()->catch_msg("You place your hands on the " + sh + 
        " and focus your power.\n");
    can_see_actor->catch_msg(QCTNAME(this_player()) + " places " + 
        this_player()->query_possessive() + " hands on " + sh + ".\n");

    map(all_inventory(ob), &->move(environment(ob)));

    can_see_corpse->catch_msg("The " + sh + 
        " decays into a desiccated pile of dust.\n");

    ob->remove_object();
}
*/

public void
do_desiccate(object corpse)
{
    string player_message, watcher_message;
    object player = this_player();
    
    if (corpse->has_vampire_drained_corpse_shadow())
    {
        player_message = "Seeing the " + corpse->short() + " already "
            + "drained of blood, you place your hands up it and focus "
            + "your power.\n";
    }
    else
    {
        player_message = "You draw up the " + corpse->short() + " and sink "
            + "your teeth into it and drain it of all blood. Satisfied, you "
            + "cast it aside and focus your power upon it.\n";
        // Draining the corpse of blood gives some blood to the player.
        player->add_blood(3 + random(3));
    }
    
    watcher_message = QCTNAME(player) + " picks up the " + corpse->short()
        + " and places " + player->query_possessive() + " hands "
        + "upon it.\n";
        
    player->catch_tell(player_message);
    tell_room(environment(player), watcher_message, ({ player }));
    
    // Remove the corpse and tell everyone in the room about it.
    tell_room(environment(player), "The " + corpse->short() + " decays into "
        + "a desiccated pile of dust.\n");

    map(all_inventory(corpse), &->move(environment(corpse)));
        
    corpse->remove_object();
}

int
desiccate(string str)
{
    mixed *obs;
    object *corpses;

    if (!CAN_SEE_IN_ROOM(this_player()))
    {
         notify_fail("You can't see anything, though!\n");
         return 0;
    }

    notify_fail(capitalize(query_verb()) + " what?\n");
    if (!strlen(str))
    {
        return 0;
    }
    
    object corpse = PARSE_COMMAND_ONE(str, 0, "[the] %i");
    if (!objectp(corpse))
    {
        return 0;
    }
    
    
    if (!IS_CORPSE_OBJECT(corpse))
    {
        notify_fail("You cannot " + query_verb() + " that.\n");
        return 0;
    }
    
    do_desiccate(corpse);
    
    return 1;
}

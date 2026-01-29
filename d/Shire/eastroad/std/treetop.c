#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

/*
 * Yeah, lets not reveal invis and people we can't see. That's stupid.
 */
void
notify_room(string room, object player, string direction)
{
    if (this_object()->query_prop(OBJ_I_LIGHT) <= 0)
        return;

    if (player->query_prop(OBJ_I_HIDE) > 0 || player->query_prop(OBJ_I_INVIS) > 0)
        return;

    tell_room(room, QCTNAME(player) + " " + direction + "\n");
}

void
tell_tree(string s) 
{
    notify_room("/d/Shire/bree/rooms/road/treetop", this_player(), s);
}

void
tell_tree_fort(string s) 
{
    notify_room("/d/Shire/bree/rooms/road/treetop_fort", this_player(), s);
}


/*
 * /d/Genesis/login/creation.c
 *
 * Room players are sent to when they are supposed to start the
 * characther creation sequence.
 *
 * The room itself is not seend, it'll just start the process
 * that resides in a separate object.
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <login.h>

#define CREATION_OBJECT "_genesis_creation_ob"

void
start_creation(object player)
{
    object ob, player_save;
    
    player_save = this_player();        
    set_this_player(player);
    
    if (ob = player->query_prop(CREATION_OBJECT))
    {
        ob->remove_object();
    }
    
    ob = clone_object(LOGIN_MENU);
    player->add_prop(CREATION_OBJECT, ob);
    ob->start();

    set_this_player(player_save);
}

void
end_creation(object player)
{
    object ob;
    
    if (ob = player->query_prop(CREATION_OBJECT))
    {
        ob->remove_object();
    }
}

void
create_room()
{
    set_short("");
    set_long("\n");
    
    add_prop(ROOM_M_NO_TELEPORT, 1);
}

void
enter_inv(object player, object from)
{
    object ob;
    ::enter_inv(player, from);

    if (player->query_ghost() & GP_BODY)
    {
        set_alarm(0.0, 0.0, &start_creation(player));
    }
}

void
leave_inv(object player, object to)
{
    ::leave_inv(player, to);
    end_creation(player);    
}


/* 
 * /d/Calia/fireball/surround/locker_room.c 
 * 
 * The locker room in the Firedrome. Here players may hire lockers 
 * if they are booked for a match. 
 * It's the players' access point to the arena. 
 *
 * Coded by Maniac@Genesis, October 1997 
 *
 * Revised by Maniac, January, April 1999
 * 
 * Copyright (C) Miguel Leith 1997  
 */

#include "defs.h"
#include FIREBALL_HEADER

inherit FIREBALL_OUTSIDE_ROOM; 

#include <macros.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>

#define FIREBALL_EQUIPMENT_ID "_calia_fireball_equipment_id"

int enter_arena(); 

mapping lockers; 
static object *about_to_move, *ready_to_move;

void
create_room()
{
    set_short("Locker room"); 
    set_long("You are in the locker room of the Firedrome, where " +
             "players leave their gear prior to fireball games. " +
             "Metal lockers extend in all directions through a " +
             "gridlike network of corridors. You can hear " +
             "a slow metronomic drip of water that echoes off " +
             "hard stone and resonates dully through cold metal. " +
             "You may <lstore> your items in a locker " +
             "here or <lclaim> them back. East is an archway " +
             "leading to the arid daylight of the arena.\n");  

    add_item(({"locker", "lockers", "corridors", "network", }), 
             "You see nothing special.\n"); 

    add_item(({"archway" }), "The archway is made of black marble. " +
           "There are four red symbols on it: a dagger, a scorpion, " + 
           "a sickle and an arrow.\n");  

    add_prop(ROOM_I_INSIDE, 1); 
    add_prop(ROOM_M_NO_ATTACK, "The guards will not permit fighting " +
             "in the locker room.\n"); 
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "The guards will not permit " +
             "aggression of any kind in the locker room.\n"); 
    add_prop(ROOM_M_NO_MAGIC, "The guards will not permit magic " +
             "of any kind in the locker room.\n"); 

    seteuid(getuid()); 
    restore_object(FIREBALL_LOCKER_SAVE); 
    if (!lockers)
        lockers = ([ ]); 

    about_to_move = ({ }); 
    ready_to_move = ({ }); 

    add_exit(FIREBALL_FOYER, "west");  
    add_exit(FIREBALL_ARENA+"ar_1_6", "east", enter_arena); 
}


int
lockable(object o)
{
    return !(stringp(o->query_auto_load()) ||
             o->query_prop(OBJ_M_NO_DROP) ||
             o->id(FIREBALL_EQUIPMENT_ID));
}


int
has_lockable_items(object player)
{
    return sizeof(filter(deep_inventory(player), lockable));
}


private void
move_to_arena(object pl)
{
    if (objectp(present(pl, this_object()))) { 
        about_to_move -= ({ pl }); 
        ready_to_move += ({ pl }); 
        pl->command("$east"); 
        return;
    } 
    about_to_move -= ({ pl }); 
}


int
fireball_equipment(object ob)
{
    return ob->id(FIREBALL_EQUIPMENT_ID); 
}


private void
equip_player_with(object pl, string path) 
{
    object ob;

    if (!(ob = clone_object(path))->move(pl)) {
        tell_object(pl, "A guard gives " + LANG_ASHORT(ob) + 
                        " to you.\n"); 
        tell_room(environment(pl), "A guard gives " + LANG_ASHORT(ob) +
                                   " to " + QTNAME(pl) + ".\n", pl); 
        ob->add_name(FIREBALL_EQUIPMENT_ID); 
    } 
}


private void
equip_player(object pl)
{
    if (!present(FIREBALL_EQUIPMENT_ID, pl)) { 
        equip_player_with(pl, FIREBALL_OBJ + "suit"); 
        equip_player_with(pl, FIREBALL_OBJ + "helm"); 
    } 
}


void
reset_locker_times(object *players) 
{
    object locker; 
    int i; 

    for (i = 0; i < sizeof(players); i++) 
        if (objectp(locker = lockers[players[i]->query_real_name()])) 
            locker->reset_locker_time();  
} 


private void
unequip_player(object pl)
{
    object *oblist;
    string str; 

    if (objectp(lockers[pl->query_real_name()])) 
        tell_object(pl, "\nDon't forget to claim your stuff back from " +
                        "your locker if you've finished playing!\n"); 

    if (!sizeof(oblist = filter(deep_inventory(pl), fireball_equipment)))
        return;   

    str = COMPOSITE_DEAD(oblist); 

    oblist->remove_object(); 
    tell_object(pl, "A guard takes " + str +  " from you.\n"); 
    tell_room(environment(pl), "A guard takes " + str +
                               " from " + QTNAME(pl) + ".\n", pl); 
}


int
enter_arena()
{
    object tp = this_player(); 

    if (member_array(tp, about_to_move) > -1) {
        write("You are already headed in that direction.\n"); 
        return 1;
    } 

    if (!FIREBALL_GAME_HANDLER->query_current_player(tp)) {
        write("The guards will not permit anyone but those " +
              "involved in the current game to enter the arena.\n"); 
        return 1; 
    } 

    if (has_lockable_items(tp)) { 
        write("The guards will not permit you to enter the arena yet! " + 
              "You will have to <lstore> some of your inventory in " +
              "a locker before you may pass.\n"); 
        return 1;
    } 

    if (tp->query_intoxicated() > 20) {
        write("The guards will not permit you to enter the arena " +
              "in a state of intoxication!\n"); 
        return 1; 
    } 

    if (sizeof(tp->query_magic_effects())) {
        write("One of the guards with training in magic notices that " +
              "you have a spell cast on you, and refuses to let you " +
              "enter the arena.\n"); 
        return 1; 
    } 

    if (tp->query_npc() || tp->query_wiz_level()) 
        return 0; 

    if (member_array(tp, ready_to_move) > -1) {
        ready_to_move -= ({ tp }); 
        return 0; 
    }

    write("You prepare to enter the arena.\n"); 
    about_to_move += ({ tp }); 
    set_alarm(1.5, 0.0, &move_to_arena(tp)); 
    return 1;
}


void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to); 
    if (living(ob) && IS_FIREBALL_ARENA_ROOM(to)) 
        set_alarm(0.0, 0.0, &equip_player(ob)); 
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 
    
    if (living(ob) && IS_FIREBALL_ARENA_ROOM(from)) 
        set_alarm(0.0, 0.0, &unequip_player(ob)); 
}


void
remove_object()
{
    seteuid(getuid()); 
    save_object(FIREBALL_LOCKER_SAVE); 
    ::remove_object();  
}


int
claim()
{
    object player, locker;
    string rn;

    if (!objectp(player = this_player()))  
        return 0;

    if (!objectp(locker = lockers[player->query_real_name()])) { 
        notify_fail("No locker is currently registered in your name.\n"); 
        return 0;
    } 

    locker->claim(player); 
    return 1;
}


int
store()
{
    object player, locker;
    string rn;

    if (!objectp(player = this_player()))  
        return 0;

    if (!FIREBALL_GAME_HANDLER->query_current_player(player)) {
        write("The guards will not permit anyone but those " +
              "involved in the current game to store items in " +
              "the lockers.\n"); 
        return 1; 
    } 

    if (!objectp(locker = lockers[rn = player->query_real_name()])) { 
        locker = clone_object(FIREBALL_OBJ+"locker"); 
        lockers[rn] = locker; 
    } 

    locker->store(player); 
    return 1;
}


void
init()
{
    ::init(); 
    add_action(claim, "lclaim"); 
    add_action(store, "lstore"); 
}

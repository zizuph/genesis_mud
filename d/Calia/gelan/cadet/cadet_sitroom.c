
/*  
    The sitting room for Cadets of Gelan.
    Only cadets should be able to walk into here, 
    no graduates. 

    Coded by Maniac@Genesis, October 1998

    Copyright (C) Miguel Leith 1998
*/

#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "cadet.h"

object *sitting; 

int
gc_query_private_room()
{
    return 1;
}


void
create_room()
{
    set_short("Sitting room");
    set_long("Lanterns on the " +
             "walls cast dim golden light across a room " +
             "furnished by several low round " +
             "wooden tables surrounded by cushioned seats. " +
             "Paintings of striking landscapes adorn the " +
             "walls and woven rugs cover the floor." + 
             VBFC_ME("sitting_desc")); 

    add_prop(ROOM_I_INSIDE, 1);
    sitting = ({ }); 

    add_item(({"lantern", "lanterns"}), 
             "Brass lanterns hang from hooks on the walls " +
             "casting dim light over the room.\n"); 

    add_item(({ "seat", "seats" }), 
              "The low seats are made of matt varnished wood " +
              "and have thin leather cushions.\n"); 

    add_item(({"leather cushions", "leather cushion", "cushion", 
               "cushions" }), 
             "They are thin but seem reasonably comfortable.\n"); 

    add_item(({"floor", "boards", "hardwood boards"}), 
             "The floor consists of neatly swept hardwood boards " +
             "covered by woven rugs.\n"); 

    add_item(({"rugs", "rug", "woven rug", "woven rugs"}), 
              "Woven rugs made of durable material in simple " +
              "diamond patterns of black and silver cover the " +
              "floor.\n"); 

    add_item(({"table", "tables", 
               "low table", "low tables", 
               "wooden table", "wooden tables", 
               "round table", "round tables" }), 
               "The low round wooden tables are made of " +
               "oak and are matt varnished.\n"); 

    add_item(({"wall", "walls" }), 
               "Paintings of landscapes adorn them.\n"); 

    add_item(({"painting", "paintings", "landscape", "landscapes"}), 
         "The paintings depict various landscapes of Calia. " +
         "They show a great central forest abundant with wildlife, " +
         "a great lake on the plains, a mountain with sheer grey rock " +
         "faces capped by a plateau, a wide blue green sea with " +
         "a shoreline of white beaches and craggy rocks and a " +
         "mysterious misty isle of ancient ruins.\n"); 

    add_exit(GC_MESSROOM, "north"); 
}


void
leave_inv(object ob, object to)
{
   if (member_array(ob, sitting) > -1) {
       ob->set_no_show_composite(0); 
       tell_object(ob, "You stand up.\n"); 
       tell_room(this_object(), 
                 QCTNAME(ob) + " stands up.\n", ob); 
       sitting -= ({ ob }); 
   } 
   ::leave_inv(ob, to); 
}


string 
sitting_desc()
{
    string str;
    int tp_sit; 
    object tp = this_player(); 

    sitting -= ({ 0 }); 
    if ((tp_sit = member_array(tp, sitting)) != -1) { 
        str = " You are sitting on a seat"; 
        sitting = exclude_array(sitting, tp_sit, tp_sit); 
    } 
    else
        str = ""; 

    if (sizeof(sitting)) { 
        if (tp_sit == -1) {
            if (sizeof(sitting) == 1) 
                str += " Sitting on a seat here is "; 
            else
                str += " Sitting on seats here are "; 
        } 
        else {
            if (sizeof(sitting) == 1)
                str += ", as is "; 
            else
                str += ", as are "; 
        } 

        map(sitting, &->set_no_show_composite(0)); 
        str += COMPOSITE_LIVE(sitting); 
        map(sitting, &->set_no_show_composite(1)); 
        str += "."; 
    }
    else {
        if (tp_sit != -1)
            str += "."; 
    }

    if (tp_sit != -1)
        sitting += ({ tp }); 
    return (str + "\n"); 
}


int
sit_down(string str)
{
    object tp = this_player(); 

    if (strlen(str) && str != "down" && 
        str != "seat" && str != "on seat" &&
        str != "at table") { 
        notify_fail("Sit down?\n"); 
        return 0;
    } 

    if (tp->query_prop(OBJ_I_HIDE)) {
        notify_fail("You can't do that and remain hidden.\n"); 
        return 0;
    } 

    if (member_array(tp, sitting) > -1) {
        notify_fail("You are already sitting!\n"); 
        return 0;
    } 

    write("You sit down on a seat.\n");
    say(QCTNAME(tp) + " sits down on a seat.\n");  
    tp->set_no_show_composite(1); 
    sitting += ({ tp }); 
    return 1;
}


int
get_up(string str)
{
    object tp = this_player(); 
    string verb = query_verb(); 
    
    if ((str == "up" && verb != "rise") || 
        (!stringp(str) && verb != "get")) {

        if (member_array(tp, sitting) == -1) { 
            notify_fail("You are not sitting down.\n"); 
            return 0;
        } 
        tp->set_no_show_composite(0); 
        write("You stand up.\n"); 
        say(QCTNAME(tp) + " stands up.\n"); 
        sitting -= ({ tp }); 
        return 1;
    } 
     
    return 0;
}


int
sit_block(string str)
{
    if (member_array(this_player(), sitting) > -1) {
        write("Stand up first!\n"); 
        return 1;
    }
    return 0; 
}


void
init()
{
    ::init(); 
    add_action(sit_down, "sit"); 
    add_action(get_up, "get"); 
    add_action(get_up, "rise"); 
    add_action(get_up, "stand"); 
    add_action(sit_block, "north");
    add_action(sit_block, "kill"); 
    add_action(sit_block, "assist"); 
    add_action(sit_block, "sneak"); 
    add_action(sit_block, "hide");  
}

/*
 * File         : /d/Genesis/start/hobbit/town/post.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/12/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The post office will be a simple standard post office that throws
 *        the reader at you when you go in and take it back when you
 *        leave. Nothing fancy. Teach the newbie what to expect from a
 *        post office. OK, I actually added some random scribble to
 *        examine just to test some VBFC functionality. Eventually it will
 *        be possible for the clients of this post office to add there own
 *        scribble.
 * 
 * TODO         :
 *        - Add interactive scribble
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

#pragma strict_types

/* inherits */
inherit "/std/room";
inherit "/d/Genesis/lib/post";



/* includes */
#include <stdproperties.h> 
#include <macros.h> 

#include "../hobbit.h"

/* defines */



/* prototypes */
void create_room();
void reset_room();

/* globals */
object reader;

/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("The village post office");
    set_long(
      "A desk along the inner wall in this small room contains a " +
      "collection of inscriptions from people reading or writing " +
      "messages here. Indeed, in this post office anyone can read or " +
      "write messages using the gnomish mail reader gizmo residing at " +
      "the corner of the desk.\n");
    add_item(({ "crevice", "crevices" }), 
      "It is possible to see some copper coins among the rubish that " +
      "has fallen down through the crevices in the floor. \n");
    add_item("desk", 
      "A furniture made of oak, filled with scribble witnessing about " +
      "love and despair. \n");
    add_item("floor", 
      "Crevices in the floor allows efficient cleaning of this room. \n");
    add_item("gizmo", 
      "AVerySofisticatedLittleMachineThatHasBeenBroughtHereByGnomes \n");
    add_item(({ "scribble", "inscriptions" }), 
      "@@get_scribble@@ \n");
    add_item("smell", 
      "A smell of sweat, oak furniture and a little oil can be " +
      "inhalated here. \n");
    add_item(({ "wall", "walls" }), 
      "The walls are made of dried mud painted in a light brown color. \n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG,
      "It's dark, you can't see anything.\n");
    add_prop(ROOM_S_DARK_MSG,
      "The darkness makes it impossible to");
    add_prop(ROOM_S_EXIT_FROM_DESC,
      "from the post office.");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/12/99.\n");
    
    add_exit("villageroad5.c", "north");
    
    
    
    reset_room();
}
/*
 * Function name:       reset_room
 * Description  :       replenish npc & stuff, if needed
 */
void
reset_room()
{
    setuid();
    seteuid(getuid());
    
}

/*
 * Function name: init()
 * Description  :  init the post functions
 */
void
init()
{
    ::init();
    post_init();
}

/*
 * Function name: leave_inv()
 * Description  :  handle special exit from post office
 */
void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}
/*
 * Function name: get_scribble()
 * Description  :  handle random descriptions
 */
string
get_scribble()
{
    string s;
    s  = "Someone was thoughtful: \"";
    switch(random(5))
    {
        case 0:
        {
            s = s + "Earth to begin with, earth to go...";
            break;
        }
        case 1:
        {
            s = s + "A nice sword divides any problem into smaller ones.";
            break;
        }
        case 2:
        {
            s = s + "Mom!!";
            break;
        }
        case 3:
        {
            s = s + "Get a delivery tour in the shipping office.";
            break;
        }
        case 4:
        {
            s = s + "Dorm, my master and protector!";
            break;
        }
        default:
        {
            s = s + "Sheena rocks!";
        }
    }
    return s + "\"";
}



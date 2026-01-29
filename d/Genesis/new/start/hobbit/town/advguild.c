/*
 * File         : /d/Genesis/start/hobbit/town/advguild.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/20/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The adventurer's guild will have the standard features with a
 *        scarred female hobbit trainer that has not forgotten the time
 *        she spent as a professional killer. Now she teaches all and
 *        everybody how to defend themselves and stay out of trouble. The
 *        guild room has a doorway through to the Pub, which shares this
 *        building but has a separate entrance from the street.
 * 
 * TODO         :
 *        Add NPC trainer, Let NPC chat about the benefits of beeing in
 *         good shape, Let NPC chat about good and bad armour, Let NPC chat
 *         about good and bad weapons, Let NPC chat about his memories from
 *         the war, Make gong make some noice
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

#pragma strict_types

/* inherits */
inherit "/std/room";
inherit  "/lib/skill_raise";
inherit  "/lib/guild_support";


/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include <ss_types.h>

#include "../hobbit.h"

/* defines */



/* prototypes */
void create_room();
void reset_room();
void set_up_skills();
string get_scribble();



/* globals */
object Trainer;

/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("The adventurers guild");
    set_long(
      "Low wooden benches are lined up around the walls in this rather " +
      "large room. Four tripods with torches corners the thick training " +
      "rug in the middle and spreads light throughout the room. A brass " +
      "gong hangs on the back wall draped by two banners. Some rumble " +
      "can be heard from the nearby pub south of here.\n");
    add_item(({ "banner", "first banner" }), 
      "The banner is black with a red cross in the middle. \n");
    add_item("banners", 
      "Two banners hangs on each side of the big brass gong. \n");
    add_item(({ "bench", "benches" }), 
      "The sturdy benches are all marked by many years of cuts and " +
      "scribble from adepts training here. \n");
    add_item("ceiling", 
      "The ceiling is the inside of the reed roof. \n");
    add_item("cuts", 
      "The cuts are made with sharp weapons. \n");
    add_item("east wall", 
      "A gong and two banners hangs on the eastern wall. \n");
    add_item("floor", 
      "Robust timber loggs cut in halfs have been used to build the " +
      "floor and covered with a large training rug. \n");
    add_item("gong", 
      "The brass gong is about 1 meter in diameter and used in " +
      "ceremonies and training events. \n");
    add_item(({ "rug", "training rug" }), 
      "A large training rug ensures that the adepts does not hurt " +
      "themselves while learning the different techniques teached " +
      "here. \n");
    add_item("scribble", get_scribble);
    add_item("second banner", 
      "The banner is white with a yellow circle in the middle. \n");
    add_item("smell", 
      "A thick smell of sweat and torches can be found here. \n");
    add_item("tripod", 
      "The tripod is made of three long poles tied together in one " +
      "end to hold lit torches. \n");
    add_item("tripods", 
      "Four sturdy tripods marks each corner of the training rug. \n");
    add_item(({ "walls", "wall" }), 
      "The walls here are bare except for the east wall. \n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG,
      "It's dark, you can't see anything.\n");
    add_prop(ROOM_S_DARK_MSG,
      "The darkness makes it impossible to");
    add_prop(ROOM_S_EXIT_FROM_DESC,
      "from the Adventurers guild.");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/20/99.\n");

    add_exit("pub.c", "south");
    add_exit("villageroad3.c", "west");


    set_up_skills();

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
    if (!objectp(Trainer))
    {
	Trainer = clone_object(EX_MON + "trainer");
	Trainer->move(this_object(), 1);
	tell_room(TO, QCTNAME(Trainer) + " appears suddenly from a dark corner.\n");
    }

}

/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();
    sk_add_train(SS_ACROBAT, "move easily", "acrobat", 0, 20);
    sk_add_train(SS_ALCHEMY, "mix potions", "alchemy", 0, 20);
    sk_add_train(SS_AWARENESS, "perceive", "awareness", 0, 30);
    sk_add_train(SS_BLIND_COMBAT, "fight while blind", "blindfighting", 0, 20);
    sk_add_train(SS_CLIMB, "climb", "climb", 0, 30);
    sk_add_train(SS_DEFENSE, "dodge attacks", "defense", 0, 20);
    sk_add_train(SS_LOC_SENSE, "avoid getting lost", "location sense", 0, 30);
    sk_add_train(SS_SNEAK, "move unoticed", "sneak", 0, 20);
    sk_add_train(SS_UNARM_COMBAT, "fight unarmed", "unarmed combat", 0, 30); 
    sk_add_train(SS_WEP_SWORD, "fight with swords", "unarmed combat", 0, 30); 
    sk_add_train(SS_WEP_POLEARM, "fight with polearms", "unarmed combat", 0, 30); 
}

/*
 * Function name: init
 * Description:   Initialize new commands for player that enters room
 */
void
init()
{
    ::init();
    init_skill_raise();
    init_guild_support();

    // Check if the NPC is here and let him check the player
    if (Trainer && present(Trainer))
    {
	Trainer->set_visitor(this_player());
    }
}

/*
 * Function name: leave_inv
 * Description:   Called when things leaves this room
 */
void
leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);
}

/*
 * Function name: get_scribble
 * Description  :  handle random descriptions
 */
string
get_scribble()
{
    string s;
    s  = "Someone has written: \"";
    switch(random(5))
    {
    case 0:
	{
	    s = s + "I won, I'm am the greatest!";
	    break;
	}
    case 1:
	{
	    s = s + "My sword is your master.";
	    break;
	}
    case 2:
	{
	    s = s + "I hate cheaters!";
	    break;
	}
    case 3:
	{
	    s = s + "Learn and improve skills to get fit for adventures.";
	    break;
	}
    case 4:
	{
	    s = s + "Next time, next time, just wait...";
	    break;
	}
    default:
	{
	    s = s + "Sheena rocks!";
	}
    }
    return s + "\"\n";
}



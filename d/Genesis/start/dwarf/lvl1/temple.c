/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Revision: Updated the 'pray' sequence to conform with current ghost
 *           routines as of Dec. 09/96 - Khail
 *
 *           Changed the start routines to allow all base "dwarf" races
 *           to start here. query_race_name -> query_race 08/97 - Karath
 *
 * Added newbie poster
 * TAPAKAH, 25/05/2005
 * Added newbie portal
 * TAPAKAH, 17/07/2005
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Genesis/login/login.h"
#include "../defs.h"

void
create_room()
{
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_NO_ATTACK, 1);
    
    set_short("Temple");
    
    set_long(BS("\nYou are standing inside a cave of truly gigantic"+
		" dimensions. The calm surface of a pool ripples slightly"+
		" above you. A feeling of calm and restfulness permeates"+
                " the atmosphere. This is the place where lost souls come"+
                " and seek solid form, by praying to the ancient dwarf gods."+
		" You notice some dwarven runes in the ceiling.\n"));

    add_item(({ "pool", "floating pool" }), 
	     BS("The placid surface of the pool shows only small ripples and reflections of the torches and candles in the cave. The pool seems to be contained in a golden bowl of truly heroic dimensions. Turned the other way around it could easily be made to contain an entire herd of gnomes. Just trying to calculate its worth leaves you dizzy and mumbling numbers under your breath for several minutes.\n"));

    seteuid(getuid());

    room_add_object("/d/Genesis/start/FAQ/faq_book");
    room_add_object("/d/Genesis/start/newbie/poster");
    room_add_object("/d/Genesis/start/newbie/portal");

    add_exit(LVL1 + "board", "west");
    add_prop(ROOM_I_INSIDE, 1);
    add_item("runes","They look dwarvish.\n");
    add_cmd_item("runes","read","@@read");

    add_cmd_item("water","drink","You would not drink this holy water would you?\n");
}

string
read()
{
    if(TP->query_race() != "dwarf")
        return "You don't understand them.\n";
    else
        return "The runes read: If you are a dwarf you may 'start here'.\n";
}

int
start(string s)
{
    if(s =="here" && TP->query_race() == "dwarf")
    {
        TP->set_default_start_location(TP->query_def_start());
        write("Ok.\n");
        return 1;
    }
  
    write("Either you can't type or you are not a dwarf. Please try again.\n");
    return 1;
}

int
pray(string str)
{
    object goo_blob;
    
    if (TP->query_race() != "dwarf" && TP->query_race() != "ghost")
    {
	if (!TP->query_invis())
	    say(BS(QCTNAME(TP) + " performs some sort of wierd ritual. A slimy stinking glob of goo suddenly drops on " + TP->query_possessive() + " head and a bolt of lightning strikes " + TP->query_possessive() + " behind.\n"));


	write(BS("A blob of stinking goo drops on you from above and a bolt of lightning strikes your bottom!\n"));
	goo_blob = clone_object(D_OBJ + "goo_blob");
	goo_blob->move(TP, 1);
	
	return 1;
    }

    if (!TP->query_invis())
	say(BS(QCNAME(TP) + " spreads " + TP->query_possessive() + " arms in a gesture of supplication. A gush of water suddenly erupts from the pool, wetting " + TP->query_objective() + " thoroughly.\n"));

  /*
   * First we see if the player has a ghost_player.c object.
   * If this is the fact, we'll make sure they've got a ghost
   * var set so the death mark will function, and then give
   * a new death mark to try to repeat the death sequence.
   */
    if (MASTER_OB(TP) == LOGIN_NEW_PLAYER)
    {
      /*
       * Player is a physical ghost. Make sure the ghost
       * var is 33 (GP_DEAD | GP_BODY) and send them to
       * the bodies room.
       */
	write("Water rushes down upon you from the pool, " +
            "washing you away to another place.\n");
        say(QCTNAME(TP) + " is engulfed in a flood of " +
            "water from the pool. When the water washes " +
            "away, " + TP->query_pronoun() + " is gone.\n");
        TP->set_ghost(GP_DEAD | GP_BODY);       
        TP->move_living("M", "/d/Genesis/login/bodies", 1, 0);
        say(QCTNAME(TP) + " arrives in a flash of light.\n");
	return 1;
    }

  /*
   * Ok, the player isn't using a ghost_player.c object, but we
   * have to make sure it's not a normal player with a ghost
   * var set running around. That's an easy repair by just
   * removing the ghost variable.
   */
    else if (TP->query_ghost())
    {
        TP->set_ghost(0);
	write("After a quick shower from the pool, you are resurrected.\n");
	say(BS(QCNAME(TP) + " appears in solid form on the stone.\n"));
        return 1;
    }

    write("Water gushes down from the pool above you, making you wet to the skin.\n" +
	  "But nothing else happens.\n");
    return 1;
}

void
init()
{
    add_action(pray, "pray");
    add_action(start,"start");

    ::init();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(!from)
	return;

    if (file_name(from) == "/d/Genesis/login/skills")
	say(BS(QCNAME(TP) + " falls headlong out of the pool but miraculously twists to land on " + ob->query_possessive() + " feet.\n"));
}

string
wizinfo()
{
    return("This is the default dwarf startinglocation. Many years ago,\n"+
	   "the mighty wizard Mrpr created this temple, and its surroundings\n"+
	   "were created by Gresolle. Please 'pray' for a pleasant surprise.\n"+
	   "\n\nThis small city is located inside a huge mountain, and\n"+
	   "was built approx. 400 years ago, by skilled dwarven engineers.\n"+
	   "The dwarves were forced to move here from the volcano island\n"+
	   "Carisca, when their former home was invaded by foul creatures.\n"+
	   "As they moved into the mountain, they were attacked by evil\n"+
	   "orcs, and after 100 years of fighting against the orc army the\n"+
	   "dwarves managed to drive away the orcs, at the battle of Andaluphin\n"+
	   "which is a small plateau high up in the mountains, a few miles\n"+
	   "north of here.\n"+
	   "\nQuestions about this place can be directed to Gresolle, who\n"+
	   "hopefully remembers how it is built.\n");
}

int
query_no_snoop()
{
    return 1;
}

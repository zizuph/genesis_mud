/* Throw command was borrowed from the code
 * by Kazz/Boriska from the outpost-Sybarus
 * monster boat.
 * -Arman
 *
 * Improved some of the clues for the neidar guru quest
 * -Arman 29 August 2016
 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#pragma save_binary

inherit DWARF_OUT;

#include "river_drink.h"

#define PLAYER_I_KILLED_SHALE  "_player_i_killed_neidar_shale"
#define CAIRN "/d/Ansalon/estwilde/plains/cairn_entry"

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

object ghost;

int do_drop(string str);

void
reset_dwarf_room()
{
    return;
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"bubbling stream","stream"}),
      "@@bubbling_stream_desc");
    add_item(({"bank","ground","grass"}),
      "The ground at the bank of the stream is covered with short " +
      "browny-green grass.\n");
    add_item(({"valley","hills"}),
      "You stand in a large valley nestled between two hills in the " +
      "middle of Estwilde.\n");
    add_item(({"community","stone buildings","buildings"}),
      "Over the stream to your southeast stand a number of stone buildings. " +
      "Smoke rises lazily from a number of chimneys, telling you " +
      "these finely crafty buildings are occupied.\n");
    add_item(({"memorial stone","stone","carved memorial stone"}),
      "A small memorial stone has been set here amongst " +
      "the grass. On it, written in dwarven runes is the " +
      "following:\n" +
      "\n" +
      "   In memory of Karyth Stormbolt, who in\n" +
      "   her grief threw herself into Argin's stream.\n" +
      "\n" +
      "   Her sorrow and shaming shall not be forgotten.\n\n");

    add_exit(IRON + "r7","northeast",0);
    add_exit(IRON + "r4","northwest",0);

    add_prop(LIVE_I_CAN_FISH, "freshwater");

    add_cmd_item(({"stream","from stream","water"}),"drink","@@drink_water");

    reset_dwarf_room();
}

string
bubbling_stream_desc()
{
   if(TP->query_prop(PLAYER_I_KILLED_SHALE) &&
           TP->query_prop(GIVEN_GURU_QUEST) && !TP->query_prop(FREED_SPIRIT))
      return "A bubbling stream flows past you here from the northeast. You " +
           "feel a sense of anticipation as you look in to it, and a strong " +
           "urge to throw something in to the stream.\n";
   else if(TP->query_prop(GIVEN_GURU_QUEST) && !TP->query_prop(FREED_SPIRIT))
      return "A bubbling stream flows past you here from the northeast. You feel " +
           "a sense of anger and unresolved vengeance as you look in to the " +
           "stream.\nA vision suddenly fills your mind of you standing " +
           "over the corpse of of a clanless hill dwarf in a distant forest, " +
           "his battle-worn neidar waraxe falling lifelessly from his hands.\n";
   else
      return "A bubbling stream flows past you here from the northeast.\n";
}


void
init()
{
    ::init();
    add_action(do_drop, "drop" );
    add_action(do_drop, "throw");
}


string
short_descr()
{
    return "At the bank of a bubbling stream";
}

string
long_descr()
{
    return "You stand at the bank of a bubbling stream that runs " +
    "past you from the northeast down to the southwest. Across " +
    "the stream to your southeast, nestled in the middle of this " +
    "valley, is a small community of stone buildings of dwarven " +
    "make. The ground at your feet is covered with short, browny-" +
    "green grass, lush from its proximity to the stream. A " +
    "small carved memorial stone has been set here amongst " +
    "the grass.\n";
}

private void
msg_drop(string text) 
{
    TP->catch_msg("You throw the " + text + " into the bubbling "+
      "stream. It swiftly disappears from sight.\n");
    say(QCTNAME(TP) + " throws the " + text + " into the bubbling "+
      "stream It swiftly disappears from sight.\n");
}

void
start_ghost()
{
    write("\n\n\nThe water of the stream begins to bubble madly...\n" +
      "A radiant figure suddenly rises from the streams depths!\n");
    say("\n\n\nThe water of the stream begins to bubble madly...\n" +
      "A radiant figured suddenly rises from the streams depths!\n");
    ghost = clone_object(LIVING + "ghost_karyth");
    ghost->move(TO);
    ghost->quest_spool();
    CAIRN->unlock_cairn_door();
}

private int
process_dropped(int num, object ob, string text)
{
    int n_heap;
    object tp = this_player();
    string obj_short;

    // do not destroy undroppable things like guild items or poisons.
    if (ob->query_prop(OBJ_M_NO_DROP))
	return 0;

    if (function_exists("create_heap", ob)) 
    {   
	n_heap = ob->num_heap();

	if (ABS(num) > n_heap) 
	    return 0;
	if (num < 0)
	    num = 1; 

	msg_drop(text);

	if (num == n_heap)
	    ob->remove_object(); // generous, nothing left.
	else
	    ob->set_heap_size(n_heap - num); //substract dropped stuff from heap.
	return 1;
    }
    else 
    { // not heap
	if (num != 1)
	    return 0; // do not handle 'drop two swords in stream'
	obj_short = ob->short();

        if(obj_short == "battle-worn neidar waraxe")
        {
	    if(TP->query_prop(PLAYER_I_KILLED_SHALE) &&
	      TP->query_prop(GIVEN_GURU_QUEST) &&
              !TP->query_prop(FREED_SPIRIT))
	    {
	     TP->add_prop(FREED_SPIRIT, 1);
	     set_alarm(2.0, 0.0, &start_ghost());
	    }
	    if(!TP->query_prop(PLAYER_I_KILLED_SHALE) &&
	      TP->query_prop(GIVEN_GURU_QUEST) &&
              !TP->query_prop(FREED_SPIRIT))
            {
             write("\n\nThe water of the stream bubbles slightly.\n" +
                 "A shiver runs up your spine as a faint gasp " +
                 "of wind blows past you, faintly sounding like " +
                 "dwarven words whispered to you from a great " +
                 "distance: 'Corl lokhar Shale...'\n\n");
             say("\n\nThe water of the stream bubbles slightly.\n" +
                 "A shiver runs up your spine as a faint gasp " +
                 "of wind blows past you.'\n\n");
            }
        }

	msg_drop(obj_short);
	ob->remove_object(); // let them sink stuff if they want
	return 1;
    }
}

int
do_drop(string str) 
{
    object ob;
    int num;
    string text;

	if (!stringp(str)) // runtime fix when no argument passed. Milan 21.7.2004
		return 0;

    // parse_command working on empty list is fast like sscanf
    // We need the text because ob->short() does not work correclty
    // with heaps. %o below will match the heap before split.
    if (!parse_command(str, ({0}), "[the] %s 'in' [to] [the] [bubbling] 'stream'", text))
	return 0;

    notify_fail("Drop what in the stream?\n");

    // drop coin in water or drop steak in water go here
    if (parse_command(str, all_inventory(TP), "[the] %o 'in' [to] [the] [bubbling] 'stream'", ob))  
	return process_dropped(1, ob, text);

    // drop second coin in water or drop 2 steaks in water go here
    if (parse_command(str, all_inventory(TP), "%d [the] %o 'in' [to] [the] [bubbling] 'stream'",
	num, ob))  
	return process_dropped(num, ob, text);
    return 0;
}

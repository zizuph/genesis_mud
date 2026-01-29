/*
 *  The hotel room of the Red Eye Inn
 *  
 *  copied from the hotel room in Re Albi 
 *
 *  created by unknown 
 *  modified for The Sleeping Stallion by Olorin on 6-jan-93
 *  modified for the Red Eye Inn by Olorin on 1-aug-93
 */
#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul";

#include "/d/Gondor/common/lib/gs_include.c"
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define ITEM_ARRAY ({MORGUL_DIR+"obj/ithil_cloak", \
                     MORGUL_DIR+"obj/ltunic", \
                     MORGUL_DIR+"obj/maingauche", \
                     WEP_DIR+"dagger", \
                     WEP_DIR+"knife", \
                     ARM_DIR+"fjacket", \
                     ARM_DIR+"ltrousers", \
                     MORGUL_DIR+"obj/shield", \
                     MORGUL_DIR+"obj/blackcap"})

public void    reset_room();

static object  item;

public void
create_morgul_room()
{
    set_extraline("A flight of stairs leads down to the main room. "
      + "Rubbish lies piled in the corners of the room, "
      + "and the air is stale. "
      + "If you have bought a key from the "
      + "innkeeper downstairs, you can spend the night here by typing "
      + "'start here'.");
    set_road(9);
    set_short_desc("upstairs in the Red Eye Inn");

    add_exit(MORGUL_DIR + "city/rooms/inn", "down","@@check_exit", 2);

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(OBJ_S_SEARCH_FUN,"do_search");
    add_item(({"heaps","garbage","rubbish","corner","corners"}), BSN(
	"In all corners of the room you find large heaps of garbage " +
	"and refuse. Probably people just dropped here what they did " +
	"need anymore. "));

    set_alarm(3.0, 0.0, &reset_room());
}

public int
start(string s)
{
    object ob;

    if (TP->query_temp_start_location() == MORGUL_DIR + "city/rooms/hotel")
    {
	write("You have already checked in!\n");
	return 1;
    }
    if(!(ob=present("_the_key_to_the_red_eye_inn_",TP)))
    {
	write("You don't have the key you need!\n");
	return 1;
    }
    NF("start where?\n");
    if(s!="here") return 0;

    ob->remove_object();

    TP->set_temp_start_location(MORGUL_DIR + "city/rooms/hotel");

    write("You notice that the small wooden key crumbles to dust in your "
	+ "hand. Suddenly you are confident that you will start here the next "
	+ "time you enter the game.\n");
    return 1;
}

string
do_search(object searcher, string str)
{
    string x;
    write("Searching through the pile of garbage makes you sick.\n");
    say("With horror you notice that " + QTNAME(searcher) +
      "searches through the stinking pile of garbage.\n");
    NF("Reluctantly you sift through the garbage pile, but you don't " +
      "find anything of interest.\n");
    if(!item) return 0;
    item->move(TO);
    say(QCTNAME(searcher) + 
      " seems to have found something of interest among all that garbage.\n");
    x = "Among all the garbage you find an old " + item->query_name() + ".\n";
    item = 0;
    return x;
}

void
reset_room()
{
    remove_prop(ROOM_M_NO_TELEPORT);
    add_prop(ROOM_M_NO_TELEPORT_FROM, "The Dark Lord of Arda prevents your magicks " +
                                 "to work properly and you can not teleport to your " +
                                 "destination.\n");

    if(item) return;
    seteuid(getuid(TO));
    item = clone_object(ITEM_ARRAY[random(sizeof(ITEM_ARRAY))]);
    if(function_exists("create_object",item) == "/std/armour")
    {
	item->set_ac( (item->query_ac() > 10 ? 10 : item->query_ac()) );
	item->set_condition(4);
	item->set_armour_hits(50);
    }
    else if(function_exists("create_object",item) == "/std/weapon");
    {
	item->set_hit( (item->query_hit() > 10 ? 10 : item->query_hit()) );
	item->set_pen( (item->query_pen() > 10 ? 10 : item->query_pen()) );
	item->set_corroded(4);
	item->set_dull(4);
	item->set_hits(50);
    }
}

public void
init()
{
    ::init();
    add_action(start, "start");
}


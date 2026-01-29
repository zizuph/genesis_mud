/*
 * Gont Realbi sandy beach file
 *
 * To be inherited by beach rooms
 *
 * Finwe May 1997.
 * This file is called by the beach rooms and contains 
 * terrain related information.
 * 
 * Modified by Ckrik Nov 1997.
 * Tide functions added. New descriptions added.
 * 
 * Modified by Amelia Jan. 1998
 * Include a search routine for beach debris
 * Added room tells
 * Added enter_inv to start room tells
 */

#pragma strict_types
#pragma no_clone

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/lib/room_tell";

#define TIDE "/d/Earthsea/gont/beach/tides"
#define CLAMS_MAX 5
#define MAX_FIND 3

#include "check_tide.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"

#define OBJ_DIR "/d/Earthsea/gont/beach/obj/"

private int num_searched, clams_dug = 0;

public void create_beach() { }

public int
dig(string str)
{
    object paralyze, to = this_object(), tp = this_player();

    if(!str || !parse_command(str, to, "[for] 'clam' / 'clams'"))
    {
        return notify_fail("Dig for what? Clams?\n");
    }

    write("You kneel down on the sand and start digging " +
        "a hole next to the sea.\n");
    say(QCTNAME(tp) + " kneels down on the sand and starts " +
        "digging a hole in the sand next to the sea.\n", tp);
  
    seteuid(getuid());

    paralyze = clone_object(OBJ_DIR + "dig_paralyze");
    paralyze->set_room(to);
    paralyze->move(tp, 1);

    return 1;
}

public int
air(string s)
{
    if(!strlen(s) || !parse_command(s,this_object(),"[the] [sea] 'air'"))
        return notify_fail("Smell what? The air?\n");;

    write("You breathe the fresh, salty sea air deep in your lungs, " +
          "tasting it on your lips.\nMmmm.....\n" +
          "There is no place like the sweet lands of the Archipelago.\n");
    say(QCTNAME(this_player()) + " takes a deep breath, smiling happily.\n");

    return 1;
}

public int
bath()
{
    object tp = this_player();

    write("You lie down for a short while, and when you rise you have "+
        "a nice tan.\n");
    say(QCTNAME(tp) + " sunbathes for a while.\n");
    tp->add_prop(LIVE_S_SOULEXTRA, "tanned");

    return 1;
}

public string
tide_tell()
{
    int tide = TIDE->query_tide_level();

    if(tide >= 3)
    {
        return "The ocean water swells and a giant wave comes " +
        "crashing from the sea. It smashes into the " +
        "beach bringing the cold salt water surging " + 
        "to your feet.\n";
    }

    if(tide <= 1)
    {
        return "The calm water of the lower tide brings the " +
        "small beach crustaceans out of their homes.\n";
    }

    return "A wave crashes in and washes up some seaweed " +
           "and shells.\n";
}

public void
set_searched(int num)
{
    num_searched = num;
    return;
}

public int
query_num_searched()
{
    return num_searched;
}

public void
set_clams_dug(int x)
{
    clams_dug = x;
}

public int
query_clams_dug()
{
    return clams_dug;
}

public string
find_stuff(object player, string str)
{
    object ob;

    if((str == "debris" || str == "shore" ||
        str == "sand" || str == "for shell" || 
        str == "here" || str == "for shells") &&
        (query_num_searched() < MAX_FIND))
    {
        setuid();
        seteuid(getuid(this_object()));

        if(TIDE->query_tide_level() > 2)
            return "Hmm ... you find nothing interesting around here. "+
            "Everything must be under water.\n";

        switch(random(7))
        {
            case 0:
                ob = clone_object(OBJ_DIR + "driftwood");
            break;

            case 1:
                ob = clone_object(OBJ_DIR + "coconut");
            break;

            case 2:
                ob = clone_object(OBJ_DIR + "flotsam");
            break;

            case 3:
                ob = clone_object(OBJ_DIR + "jetsam");
            break;

            case 4:
                ob = clone_object(OBJ_DIR + "old_l_shoe");
            break;

            case 5:
                ob = clone_object(OBJ_DIR + "old_r_shoe");
            break;

            default:
                ob = clone_object(OBJ_DIR + "shell");
        }

        set_searched(query_num_searched() + 1);
        if (ob->move(player))
            ob->move(environment(player));
        return "You find " + LANG_ASHORT(ob) + "!\n";
    }

    return "You find nothing of value.\n";
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

public void
reset_room()
{
    ::reset_room();

    num_searched = 0;
    clams_dug = 0;
}

public void
init()    
{
    ::init();

    add_action(air, "smell");
    add_action(bath, "sunbathe");
    add_action(bath, "tan");

    add_action(dig, "dig");
    add_action(check_tide, "check");
}

public string
tide_dependent()
{
    switch(TIDE->query_tide_level())
    {
        case 0:
            return "Low waters have left most of the sand " +
            "exposed. Small calm waves wet the sand " +
            "bordering the sea, dying it a slightly darker " +
            "tone. ";
        break;
        case 1:
            return "Calm waves wash up debris from the sea. " +
            "Seaweed, kelp, and bits of broken shells litter " +
            "the beach. ";
        break;
        case 2:
            return "Waves splash against the beach, cooling " +
            "the area a bit. Deposits of debris, brought from " +
            "sea decorate the area. ";
        break;
        case 3:
            return "Most of the low lying areas of the " +
            "sandy beach are covered by the sea now. "+
            "Large waves crash in to beach wetting areas that " +
            "were previously high and dry. ";
        break;
        case 4:
            return "Enormous swells driven by the tide send " +
            "gigantic waves ramming into the beach. Sea water " +
            "rushes to you feet, soaking them every time a wave " +
            "crashes onto the beach. ";
    }

    return "";
}

public string
beach_desc()
{
    switch(random(3))
    {
        case 0:
            return 
            "The golden sand of the beach glows warmly in the " +
            "sun. Sun light bounces lightly off the sand, bathing " +
            "the whole area in light. This is a popular place for " +
            "people to come and relax as they enjoy the ocean. The " +
            "sand is hot as the sun warms it. " + 
            "@@tide_dependent@@";
        break;
        case 1:
            return 
            "White sand covers this part of the shoreline. " +
            "It is inviting and looks soft as it fills your " +
            "view of the beach. A slight breeze brings in " +
            "fresh smelling air from the open sea and puffy white " +
            "clouds float overhead, casting patchy shadows all " +
            "over the beach. " + "@@tide_dependent@@";
        break;
        case 2:
            return 
            "The sandy beach gleams in the sun as you walk " +
            "across it. The sun beats down on you mercilessly, " +
            "as it heats you. Various debris is scattered across " +
            "the sand, some of it crunching under feet. Inland, " +
            "hills rise above you, blocking your view. " +
            "Nevertheless, signs of life can be seen. " +
            "@@tide_dependent@@";
        break;
        default:
            return 
            "A sandy beach covers this part of the island. " +
            "It stretches out to the sea and to the hills behind " +
            "you. Here and there you see the remains of what the " +
            "sea has washed ashore, some of it worthless, while " +
            "some looks useful. " + "@@tide_dependent@@";
    }
}

public void
create_earthsea_room()
{
    set_short("A sandy beach");
    set_long(beach_desc());
    add_prop(OBJ_S_SEARCH_FUN, "find_stuff");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_SALTBEACH);
    add_item ("sand",
      "The sand is soft to the touch. It is white with bits of " +
      "fine gravel mixed in with it. The sand is warm as it is " +
      "bathed by the sunlight all day.\n");
    add_item("debris",
      "Debris washed in from the tides litters the beach, "+
      "some of it imported from far away lands that has "+
      "found its way to these shores.\n");
    add_item(({"shore","shores","shoreline","coastline","coast"}),
      "The shores of the beach are scattered with bits of " +
      "shells, seaweed, and an occasional piece of driftwood.\n");
    add_item(({"shells", "shell"}), 
      "Shells are scattered here and there across the beach.\n");
    add_item("seaweed", 
      "There are few stray pieces of seaweed washed up on " +
      "the shore.\n");
    add_item(({"driftwood","wood"}), 
      "A few pieces of driftwood dot the coastline here and " +
      "there.\n");
    add_item("hills", 
      "The hill of the island rise up in solitary defiance of " +
      "the sea. Here and there stray wisps of smoke rise from " +
      "chimneys betraying the existence of a small town "+
      "further down south.\n");
    add_item(({"tide","tides"}),
      "The eternal tides rise and fall at the whim of the " +
      "relentless sea. Why don't you check it?\n");
    set_tell_time(120);
    add_tell(&tide_tell());
    reset_room();

    create_beach();
}

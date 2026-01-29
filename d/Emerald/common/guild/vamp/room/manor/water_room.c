/*
 * Water
 * Louie 2006
 */
  
#pragma strict_types
#include "defs.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include <stdproperties.h>
#include <language.h>
#define SHORE_ROOM (VAMP_ROOM_DIR+"manor/entry")
#define CAVE_ROOM (VAMP_ROOM_DIR+"manor/cave_entrance")

//proto
int do_swim(string str);
int do_climb(string str);
void
create_vamp_room()
{
    set_short("treading water");
    set_long("You are floating in a large body of water.  "+
        "Near you is a cliff face that rises high above you, "+
        "and much too sheer to climb.  "+
        "Along the base of the cliff are large rocks which have "+
        "eroded and fallen to their current locations long ago.  "+
        "It would appear your only option is to attempt to swim "+
        "to shore.  "+
        "\n");
    

    add_item(({"water"}),
        "Water, water everywhere but not a drop to drink.  "+
        "\n");

    add_item(({"ledge","lip","stone lip","low lip","low stone lip",
        "balcony ledge","balcony"}),
        "Far above you is the balcony, you can barely see it from here.  "+
        "\n");

    add_item(({"shore","exit","out","shore line"}),
        "Far away you can see the shore, which you can swim to "+
        "in order to escape this water.  "+
        "\n");

    add_item(({"cliff", "cliff face"}),
        "The cliff rises high above you.\n");

    add_item(({"rocks","bottom of the cliff","bottom of cliff"}),
        "At the bottom of the cliff is a multitude of rocks of various "+
        "sizes.  "+
        "Most of them likely broke off of the cliff face and fell here.  "+
        "\n");

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 0);
    
}

public void
enter_inv(object ob, object from) 
{
    ::enter_inv(ob, from);
    
    if (living(ob)) {
        say(QCTNAME(ob)+" hits the water with a tremendous splash!\n");
    } 
}

void
init() {
    ::init();
    add_action(do_swim, "swim");
    add_action(do_climb, "climb");
}

int do_swim(string str)
{
    if (!strlen(str))
    {
        notify_fail("Swim to shore?\n");
        return 0;
    }

    if (str == "to shore"
        || str =="shore"
        || str =="to the shore")
    {
        write("You swim towards the shore.\n");
        say(QCTNAME(this_player())+" swims towards the shore.\n");
        this_player()->move_living("M",SHORE_ROOM,1, 0);
        return 1;
    }

    if (str =="to the cave entrance"
        || str =="to cave entrance"
        || str =="to cave"
        || str =="cave"
        || str =="cave entrance")
    {
        write("You swim towards where you think the cave entrance was.\n");
        say(QCTNAME(this_player())+" swims towards some rocks.\n");
        this_player()->move_living("M",CAVE_ROOM,1,0);
        return 1;
    }

    if (str =="towards some rocks"
        || str =="to rocks"
        || str =="to the rocks"
        || str =="rocks"
        || str =="some rocks")
    {
        notify_fail("You are surrounded by rocks.  If you don't know "+
            "specifically where you are going, you'll never get there.\n");
        return 0;
    }

    notify_fail("Swim to shore?\n");
    return 0;
}

int do_climb(string str)
{
    notify_fail("It is impossible to climb anywhere from here.\n");
    return 0;
}

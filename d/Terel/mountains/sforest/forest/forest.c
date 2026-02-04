/* This comment tells emacs to use c++-mode -*- C++ -*- */
// Southern Forest surrounding the road leading to 
// the Stonehold
// Tomas  -- Jan 2000

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/include/herb_arrs.h"

inherit STDROOM;
inherit "/d/Terel/std/room_tell.c";
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])
#define DEFAULT    MOUNTAIN_DIR + "sforest/forest/"

object pebble;

init()
{
    ::init();
    start_room_tells();
}


public void
create_room()
{
    ::create_room();
    set_short("@@short_desc@@");
    set_long("@@long_desc@@");

    add_item(({"snow covered road","snowy road","road"}),
       "The snow covered road leads north and southward "+
       "through a densely populated forest, which grows " +
       "on either side of the road.\n");

    add_item(({"forest","trees","undergrowth", "bushes",
               "shrubs","plants","evergreens","floor",
               "ground","shrub","plant","evergreen",
               "bush"}),
       "The evergreens loom high overhead creating a " +
       "semi-shaped canopy over the road. Dense undergrowth " +
       "covers the forest floor on either sides of the road.\n");

    set_up_herbs( ({ ONE_OF_LIST(FOREST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FOREST_HERBS),
                  }),
                  ({"trees","bushes","undergrowth",
                    "plants","shrub","tree"}) , 3 );


    set_tell_time(300 + random(200));
    add_tell("You hear birds chirping off in the distance.\n");
    add_tell("The wind whips through the trees, creating " +
       "an erie howling sound.\n");
    add_tell("Something scurrys past in the brush next to you.\n");
    add_tell("The leaves from the trees sway in the icy cold " +
             "breeze.\n");
    add_tell("You catch something furry run from one bush " +
             "to another in the corner of your eye.\n");

    add_cmd_item(({"rocks","rock","pebble","pebbles"}),
                 ({"collect","gather","get"}),"@@get_pebble");

    add_cmd_item(({"air","forest","trees","plants"}),
                   "smell","@@smell_air");    

    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
  
    reset_room();

}

// Smell the air, forest, plants
public string
smell_desc()
{
    return "The air smells of fresh evergreens.\n";
}



public int
do_smell(string str)
{
    write(smell_desc());
    return 1;
}


//Forest Objects

get_pebble()
{
    object pebble;

    seteuid(getuid(TO));
    pebble = clone_object(CALATHIN_DIR + "houses/obj/pebble");
    pebble->move(TP);
    write("You pickup a pebble from the ground.\n");
       say(QCTNAME(TP) + " reaches down and picks up a pebble.\n");
    return 1;
}



string short_desc()
{
    switch(random(5))
        {
                case 0:
                        return "In the Dragon Tooth Mountains";
                        break;
                case 1:
                        return "Deep in a forest of the foothills of the " +
                        "Dragon Tooth Mountains";
                        break;
                case 2:
                        return "In the foothills of the Dragon Tooth Mountains";
                        break;
                case 3:
                        return "Somewhere in a snow-covered forest";
                        break;
                case 4:
                        return "Lost in a snow-covered forest";
                        break;
                default:
                        return "In a snow-covered forest";
                        break;
        }
}

 

string long_desc()
{
    switch(random(5))
        {
                case 0:
                        return "long desc #0\n";
                    add_item(("zero"),"long desc item zero\n");
                        break;
                case 1:
                        return "long desc #1\n";
                    add_item(("one"),"long desc item one\n");
                        break;
                case 2:
                        return "long desc #2\n";
                    add_item(("two"),"long desc item two\n");
                        break;
                case 3:
                        return "long desc #3\n";
                    add_item(("three"),"long desc item three\n");
                        break;
                case 4:
                        return "long desc #4\n";
                    add_item(("four"),"long desc item four\n");
                        break;
                default:
                        return "Default long desc\n";
                    add_item(("default"),"long desc item default\n");
                        break;
        }
}



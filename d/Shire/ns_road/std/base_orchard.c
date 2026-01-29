/*
 * Base orchard room for Westfarthing
 * Finwe, February 2020
 */

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

//inherit "/std/room";
inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";
inherit HERB_SEARCH;

#define FRUIT    ({ "apple"})
#define MAX_FRUIT     5

int fruit;
int fruit_counter;

void create_orchard() {}

public void        leave_inv(object ob, object dest);

create_area_room()
{
    set_areadesc("well tended orchard");
    set_area("in central");
    set_areaname("Southfarthing");
    set_land("the Shire");
    set_short("A large apple orchard");
//    set_long("@@orchard_desc@@\n");

    set_long(short() + ". \n");


    add_item(({"path","ground"}),
        "There is no visible path, just green grass growing beneath " +
        "the trees.\n");
    add_item(({"tree", "trees", "fruit trees", "orchard"}),
        "The fruit trees are tall and evenly spaced in the orchard. " +
        "They are very old looking andhave been meticulously " +
        "pruned and cared for. @@tree_descr@@\n");

    create_orchard();
    fruit_counter = 0;
    reset_shire_room();
//
//    add_item(({"bees", "honeybees", "honeybee", "bumblebees", "bumblebee"}),
//        &bees_descr());
//    add_item(({"birds", "bird"}),
//        &bird_descr());
//    add_item(({"fruit"}),
//        &fruit_descr());
//
}

init()
{
    ::init();
//    add_action("get_fruit", "get");
    add_action("get_fruit", "pick");

}

string get_fruit(string str)
{
    object picked_fruit;

    if(fruit_counter < MAX_FRUIT)
    {
        if(str == "fruit" || str == "apple")
        {
            picked_fruit = clone_object(FRUIT_DIR + "apple");
            write ("You reach up into the branches of a fruit tree and pick a " +
                picked_fruit->query_short() + ".\n");
            say (QCTNAME(this_player()) + " picks some fruit from a tree.\n");
            picked_fruit->move(this_player(), 1);
            fruit_counter++;
        }
        else
        {
            write("Pick what, an apple?\n");
        }
    }
    else
    {
        write("All the fruit has been picked.\n");
    }
    return "";
}


check_fruit(str)
{
    int ran_fr;
    int ran_fl;
    string what_fruit;
    object picked_fruit;

    ran_fr = random(sizeof(FRUIT));
    what_fruit = FRUIT[ran_fr];

        if (fruit_counter >= MAX_FRUIT)
        {
            write ("You notice that all the fruit has been picked.\n");
            return 1;
        }
        else
        {
            fruit_counter = fruit_counter + 1;
            get_fruit(str);
            return 1;
        }
}

void reset_shire_room()
{
    ::reset_shire_room;
    fruit_counter = 0;
}


string tree_descr()
{
    switch (fruit_counter)
    {
      case "0":
        return "The trees are full of fruit, all ready to be picked. ";
        break;
      case "1..3":
        return "A lot of fruit hangs from the tree branches. ";
        break;
      case "4":
        return "Most of the fruit has been picked from the trees. ";
        break;
      case "5":
        return "All the fruit has been picked from the trees. ";
        break;
    }
}


leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
}

/*****************************************************************************/
string road_desc1()
{
    return "The large orchard is full of fruit trees, growing in straight, " +
        "evenly spaced rows. Grass carpets the ground beneath the trees. ";
}

string road_desc2()
{
    return "The large orchard is full of fruit trees, growing in straight, " +
        "evenly spaced rows. The meticulously groomed trees grow in a " +
        "carpet of green grass. ";
}

string road_desc3()
{
    return "Well tended fruit trees grow here. The branches are thick " +
        "and able to hold a lot of fruit. The trees grow in straight " +
        "rows and are meticulously pruned. A carpet of green " +
        "grass covers the ground beneath the trees. ";
}

string road_desc4()
{
    return "Tall fruit trees grow in straight rows here. The branches " +
        "are thick and able to hold a lot of fruit. A carpet of green " +
        "grass covers the ground beneath the trees. ";
}

string road_desc5()
{
    return "The orchard is full of large trees with thick branches. " +
        "Beneath the trees grows a carpet of green grass. ";
}
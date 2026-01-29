/*
 * Base orchard room for Faerie
 * Finwe, August 2004
 *
 * Updated 6/12/19 so that the tree and fruit
 * descriptions would change when all the fruit
 * was picked.
 * --Raymundo
 */
 
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_OUTDOOR_BASE;
inherit "/d/Gondor/open/room_chairs/room_chairs";
 
#define FRUIT    ({ "fig", "mango", "pear", "peach"})                   
#define MAX_FRUIT     5         /* maximum num of fruits in each room */
#define QUEST_NAME_PROP "_fruit_quest"
#define PICKED_FRUIT    "_i_picked_fruit"

int fruit;
int fruit_counter;
 
void reset_room();
void create_orchard_room() {}

public void	    leave_inv(object ob, object dest);
  
create_faerun_room()
{
    ::create_faerun_room();
    extraline = "More descr here.";

    reset_room();
 
    add_item(({"path","ground"}),
        "There is no visible path, just green grass growing beneath " +
        "the trees.\n");
    add_item(({"tree", "trees", "fruit trees", "orchard"}),
        "The fruit trees are tall and evenly spaced in the orchard. " +
        "They have been meticulously pruned and cared for.\n");
/*
    add_item(({"grass", "green grass", "lawn"}),
        "Green grass grows throughout the orchard. It is a deep emerald " +
        "color, thick and lush, and comes up past your ankles.\n"); 
*/
    add_item(({"orchard"}),
        "This is an area north of the town. Fruit trees have been " +
        "planted and grow in straight rows.\n");
   
    create_orchard_room();
//    set_add_fences();
    fruit = 0;

    add_item(({"bees", "honeybees", "honeybee", "bumblebees", "bumblebee"}),
        "They are thumb-sized and bounce from blossom to blossom. They are yellow with black bands.\n");
    add_item(({"birds", "bird"}),
        "The birds are different sizes and brightly colored. Their songs echo through the garden.\n");
    add_item(({"fruit", "fruits"}), "@@fruit_desc@@");

}
//This sets the description of fruit in the trees.
 string
 fruit_desc()
 {
    if (fruit_counter == MAX_FRUIT)
     {
         return("You don't see any fruit in the trees. It appears they have "
            + "all been picked!\n");
     }
     else
     {
        return("They are multi-colored and fresh looking. The fruit hangs "
        + "invitingly from the trees, ready to be picked.\n");   
     }
 }
 
init()
{
    ::init();
    add_action("sniff_air", "sniff");
    add_action("sniff_air", "smell");
    add_action("pick_fruit", "pick");
   
}
 
string get_fruit(string str)
{
    object picked_fruit;

    if (TP->query_prop(QUEST_NAME_PROP))
    {
        TP->add_prop(PICKED_FRUIT,1);
    }

    picked_fruit = clone_object(FRUIT_DIR + str);
    picked_fruit->move(this_player(), 1);
    write ("You pick a " + picked_fruit->query_short() + ".\n");
 
    say (QCTNAME(this_player()) + " picks some fruit from a tree.\n");

}

sniff_air(str)
{
    if ((str == "air"))
    {
        write ("You take a deep breath. The heady fragrance leaves " +
               "you smiling contendedly.\n");
        say (QCTNAME(this_player()) + " takes a deep breath and " +
             "sighs contentedly.\n");
        return 1;
    }
    else
    {
        write ("You wrinkle your nose.\n");
        say (QCTNAME(this_player()) + " wrinkles their noise.\n");
        return 0;
    }
    return 1;
}
 
pick_fruit(str)
{
    int ran_fr;

    ran_fr = ONE_OF_LIST((FRUIT));

    if(!str)
    {
        write("Pick what, fruit?\n");
        return 1;
    }


    if (fruit_counter == MAX_FRUIT)
    {
        write ("You notice all the fruit has been picked.\n");
        return 1;
    }
    else
    {

    switch(str)
    {
        case "pear":
        {
            get_fruit(str);
            break;
        }

        case "mango":
        {
            get_fruit(str);
            break;
        }
        case "fig":
        {
            get_fruit(str);
            break;
        }
        case "mango":
        {
            get_fruit("mango");
            break;
        }

        case "fruit":
        {
            get_fruit(ran_fr);
            break;
        }
        default:
        {
            write("Pick what, fruit?\n");
            return 1;

        }
    }
     
        fruit_counter = fruit_counter + 1;
        return 1;
    }
 
}
 
 
void
reset_room()
{
    fruit_counter = 0;

}
 
/*
void
enter_inv(object ob, object from)
{
   start_room_tells();
   ::enter_inv(ob, from);
}
*/ 



leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
} 

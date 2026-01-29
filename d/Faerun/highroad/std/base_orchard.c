/*
 * Base orchard room for Faerie
 * Finwe, August 2004
 */
 
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_OUTDOOR_BASE;
inherit "/d/Gondor/open/room_chairs/room_chairs";
 
#define FRUIT    ({ "fig", "mango", "pear", "peach"})                   
#define MAX_FRUIT     5         /* maximum num of fruits in each room */
#define BENCH   "ornate silver bench"
#define LAWN    "thick green grass"

int fruit;
int fruit_counter;
 
void reset_room();
void create_orchard_room() {}

public string	look_at(string arg);	/* VBFC for chairs */
public void	    leave_inv(object ob, object dest);
  
create_faerun_room()
{
    setuid(); 
    seteuid(getuid());
    
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

    add_chair(LAWN,
	          "[down] [on] / [the] [thick] [green] 'grass'", 99);
    add_item( ({ "grass", "thick", "green"}), &look_at(LAWN) );
    add_chair(BENCH,
	          "[down] [on] / [the] [ornate] [silver] 'bench'", 4);
    add_item( ({ "bench", "silver bench", "ornate silver bench"}), 
            &look_at(BENCH) );

    
    create_orchard_room();
//    set_add_fences();
    fruit = 0;

    add_item(({"bees", "honeybees", "honeybee", "bumblebees", "bumblebee"}),
        "They are thumb-sized and bounce from blossom to blossom. They are yellow with black bands.\n");
    add_item(({"birds", "bird"}),
        "The birds are different sizes and brightly colored. Their songs echo through the garden.\n");
    add_item(({"fruit"}),
        "They are multi-colored and fresh looking. The fruit hangs invitingly from the trees, ready to be picked.\n");

}
 
init()
{
    ::init();
    add_action("sniff_air", "sniff");
    add_action("sniff_air", "smell");
    add_action("check_fruit", "pick");
    init_room_chairs();	/* add chair verbs */
   
}
 
string get_fruit(string str)
{
    object picked_fruit;
    picked_fruit = clone_object(FRUIT_DIR + str);
    picked_fruit->move(this_player(), 1);
    write ("You pick a " + picked_fruit->query_short() + ".\n");
 
    say (QCTNAME(this_player()) + " picks some fruit from a tree.\n");

}

string pick_fruit(string str)
{
    object picked_fruit;
    string chosen_fruit;

    picked_fruit = clone_object("/d/Faerun/highroad/obj/fig");
    picked_fruit->move(TP,1);
    write ("You pick a " + picked_fruit->query_short() + ".\n");

/*
    switch(str)
    {
        case "pear":
        {
//            write(str + "\n");
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
        picked_fruit = clone_object(FRUIT_DIR(ONE_OF_LIST(FRUIT)));
        picked_fruit->move(TO,1);
        write ("You pick a " + picked_fruit->query_short() + ".\n");
        say(QCTNAME(TP) + " picks some fruit from a tree.\n");
        
            break;
        } 
    }
*/
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
 
check_fruit(str)
{
    int ran_fr;
    int ran_fl;
    string what_fruit;
    object picked_fruit;

    ran_fr = random(sizeof(FRUIT));
    what_fruit = FRUIT[ran_fr];
    if (fruit_counter == MAX_FRUIT)
    {
        write ("You notice that all the fruit has been picked.\n");
        return 1;
    }
    else
    {
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
/*
string
orchard_desc(string str)
{
    str = "";
    switch(room_num)
    {
        case 0:
            return "The large orchard is full of fruit trees, growing in " +
                "straight, evenly spaced rows. Grass carpets the ground " +
                "beneath the trees. ";
            break;
        case 1:
            return "The orchard is large and full of fruit trees. They " +
                "are well cared for and grow in a carpet of green grass. An ornate silver bench is under a tree. ";
            break;
        case 2:
            return "Well tended fruit trees grow here. They grow in straight " +
                "rows and are meticulously pruned. Under the trees is set an ornate silver bench. ";
            break;
        default:
            return "Tall fruit trees grow in straight rows here. The branches " +
                "are thick and able to hold a lot of fruit. A carpet of " +
                "green grass covers the ground beneath the trees. A single silver bench is set beneath the trees. ";
            break;
     }
}
*/


leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */


/*
 * Function name:	look_at
 * Description	:	VBFC to describe chair/sofa + occupants
 * Arguments	:	string arg -- what's being looked at
 *				      null str -> it's the room
 * Returns	:	string -- the description
 */
public string
look_at(string arg)
{
    /* ok, the descs are a little lame, but you get the idea ... */
    switch ( arg )
    {
    case LAWN:
	    return "The green grass grows throughout the orchard. It is a deep emerald " +
        "color, thick and lush, and comes up past your ankles. You can " +
        "probably sit down on the grass.\n"+
	sitting_on_chair(LAWN, this_player(), 0);
    break;
    case BENCH:
    	return "The bench is ornate and made of silver. It sits under " +
            "a tree, and looks inviting. You can probably sit on it.\n"+
	sitting_on_chair(BENCH, this_player(), 0);
    break;


    }
} /* look_at */

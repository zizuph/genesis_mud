/* Mortis 12.2005 
 * Way to enter wood?  Found by smell?
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit MERCH_BASE;

#define FLED_GROVE        "_palanthas_fled_shoikan_grove"

string
query_to_jail()
{
  return "east";
}

void
create_palan_room()
{
    SHORT("a deserted street before a grove of oak trees");
    LONG("You stand upon an eerily deserted street. Tall buildings " +
        "rise on either side of you - shops and dwellings of all kind - " +
        "all well-kept but clearly long abandoned. At the end of the street " +
        "rises a grove of enormous oak trees that radiate a chill colder " +
        "than anything you have felt before.\n");

    ITEM(({"deserted street"}),
        "You stand upon a deserted street. Clean and well-kept, but eerily " +
        "deserted. At the end of the street stands a grove of enormous oak " +
        "trees - the Shoikan Grove.\n");

    ITEM(({"abandoned buildings", "tall buildings", "shops", "dwellings"}),
        "On either side of the street stand tall buildings, well-kept " +
        "and clearly of a prosperous neighbourhood, however all long " +
        "abandoned.\n");

    ITEM(({"oak", "oaks", "tree", "trees", "grove", "shoikan grove",
        "oak trees","enormous oaks","enormous oak trees"}),
	"To your south is a grove of enormous oaks, although much larger " +
        "than any you've ever seen. A chill radiates from the grove, " +
        "a paralyzing unnatural cold more severe than anything you have " +
        "felt before.\n");

	EXIT(MERCH + "wr2", "north", 0, 0);
	EXIT(MERCH + "s_grove", "south", "@@dont_go_south", 0);

}

void
flee_room(object ob)
{
    ob->catch_tell("\nYou feel yourself prey to the most unreasoning " +
        "terror you have ever experienced. And whatever is causing " +
        "it is located in the grove to your south!\n\nYou decide to " +
        "get yourself away from whatever is in that grove as fast " +
        "as you can!\n\n");
    tell_room(TO, QCTNAME(ob)+ " is suddenly overcome with irrational " +
        "fear and flees!\n", ob, ob);  
    ob->add_panic(500);
    ob->add_prop(FLED_GROVE, 1);
    ob->set_whimpy_dir("north");
    ob->run_away();
}

void
add_grove_panic(object ob)
{
    if(!present(ob, TO))
        return;

    if(ob->query_panic() > 400)
    {
       set_alarm(0.5,0.0, &flee_room(ob));
    }
    ob->add_panic(80);
    if(random(2))
        ob->catch_tell("You feel quite uneasy here, and would much " +
            "prefer to be somewhere else.\n");
    else
        ob->catch_tell("The hairs on the back of your neck stand up, and " +
            "you feel your heart rate increase irrationally.\n");
    set_alarm(50.0,0.0, &add_grove_panic(ob));
}

void
stay_in_room(object ob)
{
    ob->catch_tell("You feel a sense of irrational terror wash over you as " +
        "you walk down this street! However your protection spell takes " +
        "the edge off your fear, allowing you to still make rational " +
        "decisions... for now.\n");
    set_alarm(10.5,0.0, &add_grove_panic(ob));
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob))
        return;
 
    if (!(ob->has_protect_dragonfear_shadow()) && 
        !(ob->query_wiz_level()))
    {
       set_alarm(1.5,0.0, &flee_room(ob));
    }

    if (ob->has_protect_dragonfear_shadow())
    {
       set_alarm(1.5,0.0, &stay_in_room(ob));
    }
    else if (!ob->query_wiz_level())
    {
       set_alarm(0.5,0.0, &add_grove_panic(ob));
    }
}

int
dont_go_south()
{
    if (!(TP->has_protect_dragonfear_shadow()) && 
        !(TP->query_wiz_level()))
    {
        write("You can't go south! You are paralysed to the spot by " +
            "irrational fear... fear generating from the grove of oaks " +
            "to your south!\n");
        return 1;
    }

    if(TP->query_prop(FLED_GROVE))
    {
        write("You can't bring yourself to attempt to approach the grove " +
            "again. The irrational fear is still too fresh in your mind.\n");
        return 1;
    }

    write("You force yourself south towards the edge of the grove of " +
        "enormous oaks...\n");
    return 0;
}
/* Mortis 11.2005 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

inherit "/cmd/std/command_driver";
inherit NOBLE_ROOMBASE;

#define SPYPARK             (NOBLE + "park")

void
create_palan_room()
{
	SHORT("In a crawlspace underneath a hedge of bushes");
	LONG("A small crawlspace under a hedge of bushes, this hollow has been "
	+ "dug out by small animals, the clawmarks and scratchings of which are "
	+ "present everywhere.  From this vantage point you can see how thick "
	+ "the hedge is, ten feet, as thick as it is high.  You can also spy "
	+ "on what's going on in the park to the east.  You can crawl west "
	+ "or squirm east to leave the crawlspace.\n");

	ITEM(({"base", "roots"}), "Thick roots as wide as small trees rise from "
	+ "the ground up to the heights of the hedge.  These bushes must be old "
	+ "and very well tended.  There's enough room between the roots to "
	+ "crawl west or squirm east.\n");

	add_smell("svampire", "Misty air blowing south off the bay mingles here "
	+ "with the smells of lush, wet greenery to the east and human food "
	+ "to the southwest where the smell of blood is also strong.");
    add_smell("morgul", "Misty air blowing south off the bay mingles here "
	+ "with the smell of greenery to your east and cooking to the southwest.");
	add_smell("human", "Misty air blowing south off the bay mingles here with "
	+ "the smell of lush greenery to the east and fresh cooking to the "
	+ "southwest.");
	add_smell("elf", "Misty air blowing south off the bay mingles here with "
	+ "the scent of lush greenery, flowers, and water from the park over "
	+ "the hedge to the east and the smells of human food cooking to the "
	+ "southwest.");
	add_smell("goblin", "The fresh smells of dirt and green things from the "
	+ "east mix here with human food to the southwest and misty air blowing "
	+ "south off the bay.");
	add_smell("dwarf", "Misty air blowing south off the bay mingles here "
	+ "with the smells of greenery to your east and warm human food cooking "
	+ "to the southwest.");
	add_smell("hobbit", "Misty air blowing south off the bay mingles here "
	+ "with the fresh smells of a lush green park through the hedges to "
	+ "your east and a human inn to the southwest which, judging by the "
	+ "smells of cooking, most assuredly has a well stocked kitchen.");
	add_smell("gnome", "There's moisture in the air blowing south off the "
	+ "bay.  Adding to its salty flavor are the smells of plant life and "
	+ "flowing water to the east and human cooking odours to the "
	+ "southwest.");
	add_smell("minotaur", "Misty air blowing south off the bay mingles here "
	+ "with the lush, wet scents of green growing things to the east and "
	+ "human food to the southwest.");
	add_smell("halfhuman", "Misty air blowing south off the bay mingles here "
	+ "with the smell of lush greenery to the east and fresh cooking to the "
	+ "southwest.");
	add_smell("halfelf", "Misty air blowing south off the bay mingles here "
	+ "with the not unfamiliar smells of human cooking to your southwest "
	+ "and lush, wet greenery with a hint of flowers to your east.");
	add_smell("orc", "Misty air blowing south off the bay mingles here with "
	+ "the smells of human food to the southwest and water, dirt, and "
	+ "plants to your east.");
	add_smell("hobgoblin", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a well run inn to the southwest and a lush park "
	+ "over the hedges to your east.");
	add_smell("kender", "Misty air blowing south off the bay mingles here "
	+ "with the bright smells of plants and bushes and trees and no doubt "
	+ "pretty flowers over the imposing hedge to your east and warm cooking "
	+ "along with who knows how many interesting objects from the inn to "
	+ "the southwest perhaps.");
	add_smell("noldor", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a human cultured park on the other side of the "
	+ "hedges to your east.  From the southwest comes the typical smell of "
	+ "an active noble human inn.");
	add_smell("unknown", "You smell the park to your east and inn to the "
	+ "southwest, but your race is unknown to the immortals!  Please mail "
	+ "Mortis with your race.");


	CMD("west", "crawl", "@@crawl_west");
	CMD("east", "squirm", "@@squirm_east");

}

crawl_west() 
{ 
  write("You crawl west out from under the hedge.\n"); 
  this_player()->move_living("crawling out from between the roots under "
  + "the hedge", NOBLE + "n09", 0, 0);
  return ""; 
}

squirm_east()
{ 
  write("You squirm east out from under the hedge.\n");
  this_player()->move_living("crawling out from between the roots under "
  + "the hedge", NOBLE + "park", 0, 0); 
  return ""; 
}


void
init()
{
    ::init();
    add_action("spy", "spy");
	add_action("spy", "spy on");
	add_action("health", "health");
}

mixed
return_obj_in_hedge()
{
    return (all_inventory(TO));
}

int
spy(string str)
{
    object spyee, *inv, *obs, *ppl;
    string desc, *ctants;
    int i;

    if (!strlen(str))
    {
        write(SPYPARK->long());
        inv = (SPYPARK->return_obj_in_park());
        obs = FILTER_SHOWN(FILTER_DEAD(inv));
        ppl = FILTER_LIVE(inv);
 
        if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
        write(desc + ".\n");
 
        if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
        write(desc + ".\n");
 
        for (i = 0; i < sizeof(ppl); i++)
        {
            ctants = map(ppl[i]->query_enemy(-1), "fights", this_object(),
            ppl[i]);
 
            if (sizeof(ctants))
            ctants -= ({ 0 });
 
            if (sizeof(ctants) == 1)
              desc = LD_FIGHT1(ctants[0]);
            else if (sizeof(ctants) > 1)
              desc = LD_FIGHT_MANY(ctants);
            else
              desc = 0;
 
            if (desc)
              write(LD_FIGHT_DESC(desc, ppl[i]));
         }
         return 1;
    }
 
    if(spyee = (SPYPARK->return_in_park(str)))
    {
        write(spyee->long());
        return 1;
    }
    write("Spy on what in the park?\n");
    return 1;
}

/* get_proc_text and show_subloc_health copied from /cmd/live/state.c  */

private varargs string
get_proc_text(int num, mixed maindesc, int turnpoint, mixed subdesc)
{
    int a, b, c, d,j;
    mixed subs;

    if (!sizeof(maindesc))
        return ">normal<";

    if (num < 0)
        num = 0;
    if (num > 99)
        num = 99;

    j = sizeof(maindesc) * num / 100;    
    
    if (!pointerp(subdesc))
        subs = SD_STAT_DENOM;
    else if (sizeof(subdesc))
        subs = subdesc;
    else
        return maindesc[j];

    a = num - (j * 100 / sizeof(maindesc));

    b = (sizeof(subs) * a * sizeof(maindesc)) / 100;

    if (j < turnpoint)
        b = (sizeof(subs) - 1) - b;

    return subs[b] + maindesc[j];
}

private string
show_subloc_health(object on, object for_obj)
{
    int hp, mhp;

    hp = on->query_hp();
    mhp = on->query_max_hp();
    if (mhp == 0)
        mhp = 1;

    return get_proc_text((hp * 100) / mhp, SD_HEALTH, 0, ({}) );
}


private int
health_park()
{
 object *obs, *people;
 int i, size;

 obs = FILTER_LIVE(SPYPARK->return_obj_in_park());
 people = FILTER_CAN_SEE(obs,this_player());

 size = sizeof(people);

 if(size < 1)
 {
  write("You cannot see anyone in the park!\n");
 }
 else
 {
  for(i = 0; i < size; i++)
  {
   write(people[i]->query_The_name(this_player()) + " is " +
         show_subloc_health(people[i], this_player()) + ".\n");
  }
 }

 return 1;
}

public int
health(string str)
{
 if(str == "park") return health_park();
 return 0;
}

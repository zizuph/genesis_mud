/* created by Aridor 06/21/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

void
flood_message(int i)
{
    if (i == 1)
      tell_room(TO,"Suddenly, a thunderous noise can be heard from the southeast, " +
		"swelling more and more.\n" +
		"A flood washes along the river, taking everything along. When the " +
		"initial noise clears, you can see that the water level has risen " +
		"so high that the pier here is actually useful now.\n");
    else
      tell_room(TO,"Without notice, the water level of the river drops rapidly, " +
		"until you can only see a broad but shallow stream in the " +
		"wide river bed.\n");
}

int
flooded()
{
    return OTHERSIDE->flooded();
}

int 
flood_closed()
{
    int i = flooded();
    if (i)
      write("There is no obvious exit down due to the high water level.\n");
    return i;
}

void
create_splains_room()
{
    set_short("Ferry landing.\nA weathered sign stands crookedly here");
    set_long("@@my_long@@");

    add_exit(NEWSEA, "south");
    add_exit(ROOM + "road9","north");
    add_exit(ROOM + "pier","northeast");
    add_exit(FORD,"down","@@flood_closed@@",3,1);

    add_item(({"river","water"}),
	     "It is a river alright! Except this one might " +
	     "be a little mightier than any river you've seen so far.\n");
    add_item(({"pier"}),
	     "A declining path leads down to the water from here.\n");
    add_item(({"weathered sign","sign"}),
             "This weathered sign indicates that a ferry now runs across " +
             "the Vingaard River when the water level is high.\n");
}

string
my_long()
{
    if (flooded())
      return ("A river stops your tracks! This is the mighty " +
	      "Vingaard River flowing lazily to the northeast. " +
	      "The pier continues along the river to the northeast. The water " +
	      "seems to be very high currently, almost nipping over the " +
	      "pier here. " +
	      "Across the river you can barely make out another " +
	      "road continuing.\n");
    return ("A river stops your tracks! This is the mighty " +
	    "Vingaard River flowing lazily to the northeast. The water " +
	    "seems low and there is a good stretch of shore between " +
	    "the pier and the water. " +
	    "The pier continues along the river to the northeast. " +
	    "Across the river you can barely make out another " +
	    "road continuing.\n");
}


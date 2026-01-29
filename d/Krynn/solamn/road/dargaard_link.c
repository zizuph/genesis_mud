/* Aridor, 08/98 */

#include "local.h"
#include <filter_funs.h>
#define MAX_UNDEAD  2

inherit ROOM_BASE

int max_undead = MAX_UNDEAD;
object undead = 0;

void
reset_road_room()
{
    max_undead = MAX_UNDEAD;
    if (!undead)
	return;

    if (FILTER_PLAYERS(all_inventory(TO)) != ({}))
	return;

    undead->remove_object();
    undead = 0;
}

void
create_road_room()
{
    set_short("A track at the base of the mountains");
    set_long("You are on a track leading northwest across the plains " +
      "and southeast up into the mountains. Here, the plains end " +
      "and the mountains rise before you. At this point, the " +
      "mountain range continues northeast and southwest. From " +
      "here, you can see a fortress located high up in the " +
      "mountains, set up on a ridge.\n");

    add_item(({"bushes", "trees"}), "Trees and bushes grow here and " +
      "there across the vast plains.\n");
    add_item(({"plains", "plains of solamnia"}),
      "These are the Plains of Solamnia, spreading out before you " +
      "to the north, northwest and west. Bushes and trees are " +
      "scattered about the plains.\n");
    add_item(({"track"}),
      "The track you are standing upon leads northwest across the " +
      "plains, and southeast up into the mountains. The track " +
      "seems to be used very rarely, and parts are already " +
      "overgrown.\n");
    add_search(({"track"}), 5, "search_track", 1);
    add_item(({"mountains", "range", "mountain range",
	"dargaard mountains"}),
      "These mountains are known as the Dargaard Mountains. You are " +
      "near the northern end of the range. From here, the mountains " +
      "stretch out for many miles to the south. " +
      "They look very dark and ominous, especially around " +
      "the fortress, which is located close to the top.\n");
    add_item(({"fortress", "keep", "dargaard keep"}),
      "The fortress high up in the mountains is known as Dargaard "+
      "Keep. It appears blackened as if it had been burnt,  and an " +
      "unnatural darkness seems to radiate from it. You cannot make out any details, " +
      "since the keep is too far away.\n");
    add_item(({"ridge", "clefts", "ridges", "valleys", "peaks"}),
      "There are many ridges, clefts, valleys and peaks visible from " +
      "here. They form the mountains which rise up in front of you " +
      "to the southeast. On one ridge, very high up near the top, " +
      "you can see a fortress.\n");


    if (LOAD_ERR(ROAD_OBJECT))
    {
	write("Bug! please report immediately.\n");
	return;
    }

    add_exit("", "west", "@@enter_map:" + ROAD_OBJECT + "|D@@",6,1);
    add_exit("", "north","@@enter_map:" + ROAD_OBJECT + "|D@@",6,1); 
    add_exit("", "northwest","@@enter_map:" + ROAD_OBJECT + "|D@@",3,0); 
    add_exit(DARGAARD_LINK, "southeast", "@@closed@@",3,0);
}

int
closed()
{
    write("The track leads upwards, but after a few metres, " +
      "you are unable to follow it any further. You decide " +
      "to turn back.\n");
    return 1;
}

string
search_track(object searcher, string str)
{
    set_alarm(5.0,0.0, "rise_undead", searcher);
    return "You discover traces of fresh blood on the ground here!\n";
}

void
rise_undead(object searcher)
{
    if (max_undead == 0)
	return;

    if (!undead)
    {
	undead = clone_object(UNDEAD);
	max_undead--;
    }

    tell_room(TDIR + "dargaard_link", "The ground beneath you begins " +
      "to tremble suddenly... and then, pushing " +
      "its way out of the crumbling soil, a skeletal hand " +
      "reaches towards you, revealing an unholy " +
      "warrior from ages past!\n");
    undead->move_living("M", TO);
    undead->command("kill " + searcher->query_real_name());
}

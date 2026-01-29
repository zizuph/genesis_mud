
/*
*	coder(s):	Amelia
*	history:		coded 22/4/95
*/

inherit "/std/room";
inherit "/d/Calia/sea/level0/wade_base";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/mountain/defs.h"
#include "wade.h"
#define CLAMROOM "/d/Calia/sea/level0/clam_room"
#define TP this_player()

int searches, oysters, lucky;

void
reset_room()
{
    oysters = 15 + random(20);
    lucky = (oysters/2)+random(oysters/2);
    searches = 0;
}

void
create_room()
{
	::create_level0();
	set_short("Further from shore...");
	set_long("You are standing waist deep in the sea, further from "+
		"shore.  The blue-green sea is all around "+
		"you, and feels warm and refreshing.  There are seabirds "+
		"fishing here. "+"@@extra_desc");

	add_item((({"sea", "blue-green sea", "water"})),
		("The water is clear and a perfect temperature. "+
		"You can look down all the way to the bottom.\n"));
	add_item((({"seabirds", "pelicans", "pelican", "sea gulls"})),
		("There are pelicans and sea gulls flying around, "+
		"apparently hunting for fish.\n"));
		
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE, 0);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_TYPE, ROOM_IN_WATER);


	set_tell_time(110);
	add_tell("Pelicans soar gracefully overhead.\n");
	add_tell("Suddenly a pelican dives in, catching a fish.\n");
	add_tell("A large wave splashes over your head.\n");
	add_tell("Far out to sea the sailboat tacks to the north.\n");
	add_tell("Far away the sailboat tacks to the northwest.\n");
    add_item((({"oyster", "oysters", "oyster bed", "shellfish"})),
        "You look down through the clear water, and see "+
        "what looks like an oyster bed on the sea bottom. "+
       "There are grey shellfish clustered together.\n");
    add_prop(OBJ_S_SEARCH_FUN, "find_oyster");
    add_prop(OBJ_I_SEARCH_TIME, 5);
    reset_room();
	
}

void
init()
{
	::init();
	add_action("dive", "swim");
    add_action("dive","wade");
}
int
dive(string where)
{
	if((where=="northeast")||(where=="ne")||(where==""))
	{
    tell_room(environment(TP), QCTNAME(TP)+" swims off "+
        "to the northeast.\n",TP);
    TP->catch_msg("You swim off to the northeast.\n");
    TP->move_living("M",CLAMROOM,1);
    tell_room(CLAMROOM,QCTNAME(TP)+" swims in from the southwest.\n",TP);
	return 1;
	}
	notify_fail("Swim where?\n");
	return 0;
}

string
extra_desc()
{
	return
	"The sea extends west all the way to where it "+
	"merges with the horizon. Far away in the northwest you can see "+
	"a ship that heads away from the busy dock of Gelan. "+
	"In the south the landscape is dominated by Mt. Kyrus. "+
    "The water is very clear, and as you look down to the bottom, "+
    "you see some grey shellfish, "+
    "lots of them, on the seafloor. "+
        "From here you can wade or swim to the northeast.\n";
}

string
find_oyster(object searcher, string str)
{
    object oyster, meat, tp;

    tp = this_player();
    if (str == "here for oyster" || str == "here for oysters" ||
        str == "oysterbed" || str == "oyster bed" || str == "oysters")
        {
        if (searches <= oysters)
        {
        searches++;
        seteuid(getuid(TO));
        oyster = clone_object(OYSTER);
        if (searches == lucky)
        {
            oyster->add_black_pearl();
        }
        oyster->move(tp);
        return "You found an oyster.\n";
        }
        return "You don't find any more oysters.  Perhaps you "+
            "should come back later.\n";
        }
    return "You found nothing interesting here.\n";
}

int query_lucky() { return "Lucky = "+lucky; }
int query_searches() { return "Searches = "+searches; }
int query_oysters() { return "Oysters = "+oysters; }

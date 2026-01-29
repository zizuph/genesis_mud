/*
 *      /d/Gondor/ithilien/nforest/ridge3.c
 *
 *      Coded 1993 by Olorin.
 *
 *      Modification log:
 *      31-Jan-1997, Olorin: Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define HE(x)		(x)->query_pronoun() 

/* how hard is it to find the way up the cedar? */
#define HARD_TO_FIND	60  
/* how hard is it to climb up the cedar? */
#define HARD_TO_CLIMB	20  
#define ITHILIEN_RIDGE_FOUND_ROCK	"_ithilien_ridge_found_rock"

public string  exa_rock();
public void    make_smoke();
public string  do_search(object searcher, string str);

public void
create_area_room()
{
    set_areatype(2);
    set_areadesc("thicket on a stony ridge");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar and cypress");
    set_extraline( 
        "The ridge is completely overgrown by a thicket of bushes, " +
        "which are blocking the view in all directions. In the midst " +
        "of the thicket there are a few cypress trees and two large " +
        "cedars rising many feet into the sky. The bushes are impenetrable " +
        "all around you, only to the east there is the small opening " +
        "through which you came.");
    add_item( ({ "bush", "bushes", "thicket", }), BSN(
        "The bushes are much higher than you are and the foliage is very dense, " +
        "so that the view in all directions is effectively blocked. The bushes " +
        "are impenetrable in all directions, only to the east there is the " +
        "small opening through which you came here."));
    add_item( ({ "cypress", "cypress tree", "cypresses", "cypress trees", }),
	BSN("In the midst of the thicket there are a few cypress trees. They " +
        "are not very tall, standing in the shadow of two giant cedars. The " +
        "branches of the cypresses are mere twigs that probably could hardly " +
        "hold a large bird."));
    add_item( ({ "forest", "tree", "trees", }), BSN(
        "In the midst of the thicket there are a few cypress trees. They are " +
        "not very tall, standing in the shadow of two giant cedars. The cedar " +
        "closer to you is even larger than the one a bit farther away."));
    add_item( ({ "cedar", "cedars", "cedar tree", "cedar trees", }), BSN(
        "These are two giant trees, rising many feet into the sky. The one " +
        "next to you is even larger than the one a bit farther away. Both " +
        "cedars are truly impressive. A closer look might be worthwhile. " +
        "Glancing up along the thick trunks you notice that there are no " +
        "branches within easy reach. But high above you you can see large " +
        "boughs covered with thick green needles and cones."));
    add_item( ({ "large cedar", "larger cedar", "first cedar", "nearer cedar",
		 "closer cedar", "next cedar", }), BSN(
        "This is a really giant cedar tree. You estimate its height to about " +
        "120 feet. The trunk is so thick that three men could not embrace it. " +
        "The branches start high above your head, far out of the reach of your " +
        "hands."));
    add_item( ({ "farther cedar", "second cedar","other cedar", 
		 "smaller cedar"}), BSN(
        "This is a giant tree with an enourmous trunk, even though it is " +
        "smaller than the cedar nearer to you. The lowest branches of this " +
        "cedar are well outside your reach, too - at least those that you can " +
        "see from where you are standing. Perhaps a closer inspection of the " +
        "smaller cedar might turn something up?"));

    add_item( ({ "rock", "large rock", }), exa_rock);

    set_up_herbs( ({ HERB_DIR + "attanar",  HERB_DIR + "chervil", 
		     HERB_DIR + "hemlock",  HERB_DIR + "laurel",
		     HERB_DIR + "marjoram", HERB_DIR + "savory", }), 
		 ({ "forest", "ground", "field", "flowers", }), 3);

    add_exit(ITH_DIR + "nforest/ridge2", "east", 0, 1, 1);

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
}

public int
do_climb(string str)
{
    string  adj;
    int     climb_skill, 
            risk, 
            hurt;

    NFN("Climb what?");
    if (!strlen(str))
	return 0;

    str = LOW(str);

    if ((sscanf(str,"%s cedar", adj) == 1)  || 
	(sscanf(str,"%s tree", adj) == 1))
    {
	if (member_array(adj, ({ "small", "smaller", "farther", "second" }) ) > -1)
	{
	    write("The lowest branches of the cedar tree are still far " +
		  "out of your reach.\n");
	    return 1;
	}
	
	if (member_array(adj, ({ "large", "larger", "first", "nearer",
				 "closer", "next", }) ) > -1)
	{
	    write("You cannot climb the " + adj + " cedar. " +
		  "The lowest branches of the tree are far out of reach.\n");
	    return 1;
	}

	return 0;
    }

    if (member_array(str, ({ "cedar", "tree", "trees", "cedars",
			     "cedar tree", "cedar trees", }) ) > -1)
    {
	write("Which one of the two cedar trees do you want to climb, " +
	      "the nearer or the farther one?\n");
	return 1;
    }

    if (member_array(str, ({ "cypress", "cypress tree", "cypress trees",
			     "cypresses" }) ) > -1)
    {
	write("You cannot climb any of the cypress trees. " +
	      "Their branches are too thin by far.\n");
	return 1;
    }

    if ((sscanf(str, "%s rock", adj) == 1) || (str == "rock"))
    {
	if (!TP->query_prop(ITHILIEN_RIDGE_FOUND_ROCK))
	{
	    NFN("You cannot see any rock here.");
	    return 0;
	}
	else
	{
	    climb_skill = TP->query_skill(SS_CLIMB);
	    risk = HARD_TO_CLIMB + random(HARD_TO_CLIMB);
	    if (climb_skill > risk)
	    {
		write(BS("Skilled as you are you manage to climb the large rock.\n"));
		tell_room(TO, QCTNAME(TP) + " climbs a rock.\n",TP);
		TP->move_living("up the rock", ITH_DIR + "nforest/on_rock", 1);
	    }
	    else
	    {
		write("You try to climb the large rock.\n" +
		      "Clumsily you try to find hold in the cracks.\n" +
		      "Suddenly you slip ... \n" +
		      "You fall down the rock, painfully hitting sharp edges.\n");
		hurt = (risk - climb_skill) * risk / 4;
		tell_room(TO, QCTNAME(TP) + " tries to climb a rock.\n" +
			  HE(TP) + " slips and falls down from the rock.\n",TP);
		TP->reduce_hit_point(hurt);
	    }
	}
	return 1;
    }
    return 0;
}

public string
do_search(object searcher, string str)
{
    string  adj;
    int     aware_skill = TP->query_skill(SS_AWARENESS),
            int_stat    = TP->query_stat(SS_INT);

    if (!strlen(str)) 
	return 0;

    if ((sscanf(str,"%s cedar", adj) == 1)  || 
	(sscanf(str,"%s tree", adj) == 1))
    {
	if (member_array(adj, ({ "small", "smaller", "farther", "second" }) ) > -1)
	{
	    if ((aware_skill + int_stat) > 
		(HARD_TO_FIND / 2 + random(HARD_TO_FIND)))
	    {
		TP->add_prop(ITHILIEN_RIDGE_FOUND_ROCK, 1);
		return BSN("When you circle the smaller cedar, hidden in " +
			   "the midst of thick bushes, you find a large " +
			   "rock rising on the other side of the thick trunk.");
	    }
	    else
	    {
		return BSN("You do not find anything interesting. But you " +
			   "feel that there is something important here " +
			   "that you are missing because you are not paying " +
			   "attention.");
	    }
	}
	if (member_array(adj, ({ "large", "larger", "first", "nearer",
				 "closer", "next", }) ) > -1)
	{
	    return BSN("Your search reveals nothing special. Walking " +
		       "around the thick trunk of the " + adj + " cedar, " +
		       "you realize that it is impossible to climb this tree. " +
		       "All of the branches are far out of your reach. You " +
		       "wonder if the smaller cedar is as inaccessible as " +
		       "this one.");
	}
	return 0;
    }

    if (member_array(str, ({ "cedar", "tree", "trees", "cedars", 
			     "cedar tree", "cedar trees", }) ) > -1)
    {
	return BSN("With two cedars to search at the same time you " +
		   "start running to and fro between them, not able " +
		   "to decide where to start. Finally, you realize " +
		   "that it is impossible. Perhaps you should try to " +
		   "search either the nearer or the farther cedar first?");
    }

    return herb_search(searcher,str);
}

string
exa_rock()
{
    if (!TP->query_prop(ITHILIEN_RIDGE_FOUND_ROCK))
	return "You find no rock.\n";
    return BSN("On the far side of the farther cedar there is a large " +
	       "weather-worn rock. Several large cracks might make it " +
	       "possible for a skilled climber to reach the top of the rock.");
}

public void
living_check()
{
    object  fire, 
           *cont;

    if (!objectp(fire = present("fire", TO))) 
	return;

    cont = FILTER_LIVE(all_inventory(TO));
    if (!sizeof(cont))
	set_alarm(1.0, 0.0, make_smoke);
    return;
}

public void
make_smoke()
{
    object fire;
    if (!objectp(fire = present("fire", TO))) 
	return;
  
    tell_room(TO, "Smoke from the " + fire->short() + " is rising into the sky.\n");

    (ITH_DIR + "nforest/on_rock")->make_smoke(fire);
    (ITH_DIR + "nforest/lbranch")->make_smoke(fire);
    (ITH_DIR + "nforest/mbranch")->make_smoke(fire);
    (ITH_DIR + "nforest/lookout")->make_smoke(fire);

   set_alarm(10.0, 0.0, living_check);
   return;
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(!objectp(ob) || !objectp(to)) 
	return;
    if (!living(ob)) 
	return;
  
    if (!objectp(present("fire", TO)))
	return;
    set_alarm(1.0, 0.0, living_check);
    return;
}

public void
init()
{
    ::init();
    add_action(do_climb, "climb");
}

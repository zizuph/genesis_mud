#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

/* how hard is it to find the way up the oak? - random(x) */
#define HARD_TO_FIND   35

/* how hard is it to climb up the oak? - x + random(x) */
#define HARD_TO_CLIMB  20

string  exa_rock();
int     do_climb(string str);
void    make_smoke();
void    living_check();

/* alarm ids */
static int	Check_id,
		Smoke_id;

void
create_area_room()
{
    set_areatype(2);
    set_areadesc("hog-back of land");
    set_area("southern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("ash and oak");
    set_extraline("The small rising is completely overgrown by a thicket of "
      + "gorse-bushes and briars. Out of the bushes a few small ash trees "
      + "and two giant oaks are rising. Only to the east can you see a "
      + "narrow passage leading out of the thicket.");
    add_item(({"bush","bushes","thicket"}),BSN(
        "The bushes are much higher than you are, and the dense foliage and "
      + "intertwining branches block your view in all directions. Only to the "
      + "east, there is the small opening through which you came here."));
    add_item(({"ash","ash tree","ashes","ash trees"}),BS(
    "In the midst of the thicket there are a few ash trees. They are " +
    "not very tall, standing in the shadow of two giant oaks. The branches " +
    "of the ashes are mere twigs that probably could hardly hold a large bird. \n"));
    add_item(({"forest","tree","trees"}), BS(
    "In the midst of the thicket there are a few ash trees. They are " +
    "not very tall, standing in the shadow of two giant oaks. The oak closer " +
    "to you is even larger than the one a bit farther away. \n"));
    add_item(({"oak","oaks","oak tree","oak trees"}), BS(
    "These are two giant trees, rising many feet into the sky. The one next " +
    "to you is even larger than the one a bit farther away. Both oaks " +
    "are truly impressive. A closer look might be worthwhile. Glancing " +
    "up along the thick trunks you notice that there are no branches " +
    "within easy reach. But high above you you can see large boughs " +
    "covered with thick green leaves and acorns. \n"));
    add_item(({"large oak","larger oak","first oak","nearer oak",
	       "closer oak","next oak"}), BS(
    "This is a really giant oak tree. You estimate its height to about " +
    "120 feet. The trunk is so thick that three men could not embrace it. " +
    "The branches start high above your head, far out of the reach of your " +
    "hands. \n"));
    add_item(({"farther oak","further oak","second oak","other oak","smaller oak"}), BS(
    "This is a giant tree with an enormous trunk, even though it is " +
    "smaller than the oak nearer to you. The lowest branches of this " +
    "oak are well outside your reach, too - at least those that you can " +
    "see from where you are standing. Perhaps a closer inspection of the " +
    "smaller oak might turn something up? \n"));

    add_item(({"rock","large rock"}), exa_rock);

    add_exit(ITH_DIR + "sforest/thicket2", "east", 0, 1);

    set_up_herbs( ({ HERB_DIR + "red_pepper",
                     HERB_DIR + "savory",
                     HERB_DIR + "laurel", 
                     HERB_DIR + "basil",
                     HERB_DIR + "attanar", }),
                  ({"forest","ground","field","flowers",}), 3);
    set_noshow_obvious(1);
}

void
init()
{
    ::init();
    add_action(do_climb, "climb");
}

int
do_climb(string str)
{
    string adj, dummy;
    int climb_skill, risk, hurt;

    if (!strlen(str))
    {
	write("Climb what? \n");
	return 1;
    }
    if (sscanf(str,"%s oak", adj) == 1  || sscanf(str,"%s tree", adj) == 1)
    {
	switch (adj)
	{
	case "small":
	case "smaller":
	case "further":
	case "farther":
	case "second":
	    write(BS("The lowest branches of the oak tree are still "
	      + "far out of your reach.\n"));
	    return 1;
	case "large":
	case "larger":
	case "first":
	case "nearer":
	case "closer":
	case "next":
	    write(BS("You cannot climb the " + adj
	      + " oak. The lowest branches of the tree are far out of reach.\n"));
	    return 1;
	}
    }

    switch (str)
    {
    case "oak":
    case "tree":
    case "trees":
    case "oaks":
	write(BS("Which one of the two oak trees do you want to climb, "
	  + "the nearer or the farther one?\n"));
	return 1;
    case "ash":
    case "ash tree":
    case "ash trees":
    case "ashes":
	write(BS("You cannot climb any of the ash trees. "
	  + "Their branches are too thin by far. \n"));
	return 1;
    }
    
    if (sscanf(str,"%s rock", adj) == 1 || str == "rock" )
    {
	if(!TP->query_prop("_ithilien_thicket_found_rock"))
	{
	    write(BS("You cannot see any rock here.\n"));
	    return 1;
	}
	else
	{
	    climb_skill = TP->query_skill(SS_CLIMB);
	    risk = HARD_TO_CLIMB + random(HARD_TO_CLIMB);
	    if(climb_skill > risk)
	    {
		write(BS("Skilled as you are you manage to climb the large rock.\n"));
		tell_room(TO,QCTNAME(TP) + " climbs a rock.\n",TP);
		TP->move_living("up the rock",ITH_DIR + "sforest/on_rock",1);
	    }
	    else
	    {
		write("You try to climb the large rock.\n"
		    + "Clumsily you try to find hold in the cracks.\n"
		    + "Suddenly you slip ... \n"
		    + "You fall down the rock, painfully hitting sharp edges.\n");
		hurt = (risk - climb_skill) * risk / 4;
		TP->reduce_hit_point(hurt);
		tell_room(TO,QCTNAME(TP) + " tries to climb a rock.\n",TP);
		tell_room(TO,QCTNAME(TP) + " slips and falls down from the rock.\n",TP);
	    }
	}
	return 1;
    }
    write("Climb what?\n");
    return 1;
}

mixed
herb_search(object searcher, string str)
{
    object  tp = TP;
    int     aware_skill = tp->query_skill(SS_AWARENESS),
            int_stat = tp->query_stat(SS_INT);
    string  adj,
            dummy;

    if (!strlen(str))
        return 0;

    if (sscanf(str,"%s oak", adj) == 1)
    {
        switch (adj)
        {
        case "small":
        case "smaller":
        case "further":
        case "farther":
        case "second":
            if ((aware_skill + int_stat) > random(HARD_TO_FIND))
            {
                tp->add_prop("_ithilien_thicket_found_rock",1);
                return BSN("When you circle the smaller oak, hidden in the "
                  + "midst of thick bushes, you find a large rock rising on "
                  + "the other side of the thick trunk.");
            }
            else
            {
                return BSN("You do not find anything interesting. But you "
                  + "feel that there is something important here that you "
                  + "are missing because you are not paying attention.");
            }
            break;
        case "large":
        case "larger":
        case "first":
        case "nearer":
        case "closer":
        case "next":
            return BSN("Your search reveals nothing special. Walking around "
              + "the thick trunk of the " + adj + " oak, you realize that "
              + "it is impossible to climb this tree. All of the branches "
              + "are far out of your reach. You wonder if the smaller oak "
              + "is as inaccessible as this one.");
            break;
        }
    }
    if (str == "oak tree" || str == "oak trees" ||
        str == "oak" || str == "oaks" || str == "tree" || str == "trees")
    {
        return BSN("With two oaks to search at the same time you start "
          + "running to and fro between them, not able to decide where to "
          + "start. Finally, you realize that it is impossible. Perhaps "
          + "you should try to search either the nearer or the farther oak "
          + "first?");
    }
    return ::herb_search(searcher,str);
}

string
exa_rock()
{
    if (!TP->query_prop("_ithilien_thicket_found_rock"))
        return "You find no rock.\n";
    return BSN("On the far side of the farther oak there is a large "
      + "weather-worn rock. Several large cracks might make it possible "
      + "for a skilled climber to reach the top of the rock.");
}

void
leave_inv(object ob, object to)
{
  object fire;

  ::leave_inv(ob, to);

  if(!ob || !to) return;
  if(!living(ob)) return;
  
  if(!(fire = present("fire",TO))) return 0;
  if (!Check_id)
      Check_id = set_alarm(1.0, 0.0, living_check);
  return;
}

void
living_check()
{
  object fire, *cont;

  Check_id = 0;
  if (!Smoke_id &&
      objectp(fire = present("fire",TO)) &&
      !sizeof(cont = FILTER_LIVE(all_inventory(TO))))
  {
      Smoke_id = set_alarm(1.0, 0.0, make_smoke);
  }
  return;
}

void
make_smoke()
{
  object fire;

  Smoke_id = 0;

  if(!(fire = present("fire",TO))) return;
  
  tell_room(TO,"Smoke from the " + fire->short() + " is rising into the sky.\n");
   (ITH_DIR + "sforest/on_rock")->make_smoke(fire);
   (ITH_DIR + "sforest/lbranch")->make_smoke(fire);
   (ITH_DIR + "sforest/mbranch")->make_smoke(fire);
   (ITH_DIR + "sforest/lookout")->make_smoke(fire);
  if (!Check_id)
  {
      Check_id = set_alarm(10.0, 0.0, living_check);
  }
  return;
}

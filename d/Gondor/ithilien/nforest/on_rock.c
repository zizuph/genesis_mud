/*
 *      /d/Gondor/ithilien/nforest/on_rock.c
 *
 *      Coded 1993 by Olorin.
 *
 *      Modification log:
 *      31-Jan-1997, Olorin: Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

/* how hard is it to climb up the cedar? - x + random(x) */
#define HARD_TO_CLIMB	40  
#define ITHILIEN_RIDGE_LOOK_BRANCH	"_ithilien_ridge_look_branch"

public string exa_branches();
public string exa_tree();

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("rock");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar");
    set_extraline( 
    "You are on top of the large rock. The thick bushes still block the view in all " +
    "directions. The rock is standing next to the smaller of the two cedar trees " +
    "growing here. The thick boughs of the cedar start spreading out from the trunk " +
    "over your head. They are densely covered with green needles.");
    add_item(({"bush","bushes","thicket"}),BS(
    "The bushes are much higher than you are and the foliage is very dense, " +
    "so that the view in all directions is effectively blocked. \n"));
    add_item(({"cypress","cypress tree","cypresses","cypress trees","forest","trees"}),
        BSN("In the midst of the thicket there are a few cypress trees. They " +
        "are not very tall, standing in the shadow of the two giant cedars."));
    add_item(({"cedars","cedar trees"}), BSN(
    "These are two giant trees, rising many feet into the sky. The one farther " +
    "from you is even larger than the one that is rising next to the rock one which " +
    "you are standing. Both cedars do not have any branches close to the ground."));
    add_item(({"large cedar","larger cedar","first cedar","farther cedar",
	       "further cedar","other cedar"}), BSN(
    "This is a really giant cedar tree. You estimate its height to about " +
    "120 feet. The trunk is so thick that three men could not embrace it. " +
    "The branches start high above your head, far out of the reach of your " +
    "hands."));
    add_item(({"tree","cedar","cedar tree","closer cedar","nearer cedar",
	       "second cedar","next cedar","small cedar","smaller cedar"}), 
	     exa_tree);
    add_item( ({"branch", "branches", "bough", "boughs", }), 
	     exa_branches);
    add_cmd_item( ({ "branch", "bough", }), "pull", 
		 "You pull at the branch, however it is too thick to " +
		 "budge it, so this will not ease your climb.\n");

    add_item( ({ "rock", "large rock", }), BSN(
        "The large rock on which you are standing is rather weather-beaten. " +
        "Cracks are running through it, making it possible to climb the " +
        "rock for a skilled climber."));

    (ITH_DIR + "nforest/lookout")->load_me();
}

public string
exa_branches()
{ 
    TP->add_prop(ITHILIEN_RIDGE_LOOK_BRANCH, 1);
    return BSN("The branches of this cedar tree are densely covered " +
	       "with thick green needles. Most of the branches are " +
	       "far out of your reach, but there is one bough right " +
	       "over the rock you are standing on. If you are " +
	       "proficient enough at climbing and if you are agile " +
	       "enough, you just might manage to climb onto it.");
}

public string
exa_tree()
{
    TP->add_prop(ITHILIEN_RIDGE_LOOK_BRANCH, 1);
    return BSN("This is a giant tree with an enormous trunk, even " +
	       "though it is smaller than the other cedar. " + 
	       "The branches of this cedar tree are densely covered " +
	       "with thick green needles. Most of the branches are " +
	       "far out of your reach, but there is one bough right " +
	       "over the rock you are standing on. If you are " +
	       "proficient enough at climbing and if you are agile " +
	       "enough, you just might manage to climb onto it.");
}

void
fall_branch(int hit)
{
    int     dex_stat  = TP->query_skill(SS_DEX);

    write("You fall down from the branch, painfully landing on the " +
	  "top of the rock.\n");
    tell_room(TO, QCTNAME(TP) + " falls down from the branch, " +
	      "painfully landing on top of the rock.\n", TP);
    TP->reduce_hit_point(hit);
    if (dex_stat < HARD_TO_CLIMB)
    {
	write("Landing on top of the rock, you lose your hold and continue " +
	      "to fall down from the rock.\n" +
	      "You tumble down from the rock, hurting yourself on sharp edges.\n");
	TP->reduce_hit_point( 5 * (HARD_TO_CLIMB - dex_stat));
	tell_room(TO, "Landing on top of the rock, " + QTNAME(TP) +
		  " continues to fall, tumbling down from the rock.\n", TP);
	TP->move_living("M", ITH_DIR + "nforest/ridge3");
	tell_room(ENV(TP), QCTNAME(TP) + " arrives falling down from above.\n", TP);
    }
}

void
climb_branch()
{
    write("You manage to pull yourself up onto the lowest branch of the cedar.\n");
    tell_room(TO, CAP(QTNAME(TP)) + " manages to pull " + TP->query_objective() +
	      "self up onto the lowest branch of the cedar.\n", TP);
    TP->move_living("M",ITH_DIR + "nforest/lbranch");
    tell_room(ENV(TP), QCTNAME(TP) + " arrives climbing onto the tree " +
	      "from the rock below.\n", TP);
}

public int
do_climb(string str)
{
    int     climb_skill, 
            acrobat_skill, 
            dex_stat, 
            risk, 
            hurt, 
            cap;

    if (!strlen(str))
    {
	NFN("Climb what?");
	return 0;
    }

    if (member_array(str, ({ "cedar", "branch", "bough", "onto branch", 
			     "onto bough", "on branch", "on branch", 
			     "tree" }) ) > -1)
    {
	if (!TP->query_prop(ITHILIEN_RIDGE_LOOK_BRANCH))
	{
	    write(BSN("Before trying to climb the tree, you should perhaps " +
		      "first look at it to find out how to accomplish that feat."));
	}
	else
	{
	    climb_skill   = TP->query_skill(SS_CLIMB);
	    acrobat_skill = TP->query_skill(SS_ACROBAT);
	    dex_stat      = TP->query_stat(SS_DEX);

	    risk = HARD_TO_CLIMB + random(HARD_TO_CLIMB);
	    cap = climb_skill + acrobat_skill + dex_stat/2;
	    tell_room(TO, CAP(QCTNAME(TP)) +
		      " tries to climb onto the lowest branch of the cedar.\n", TP);

	    if (cap > risk)
	    {
		if (IS_EVIL(TP) && 
		    present("sniper", find_object(ITH_DIR + "nforest/lookout")))
		{
		    write("As you try to climb onto the lowest branch of " +
			  "the cedar, you are suddenly hit by an arrow " +
			  "fired from above.\n");
		    tell_room(TO, "Suddenly, " + QCTNAME(TP) + 
			      " is hit by an arrow fired from above.\n", TP);
		    TP->reduce_hit_point(50);
		    if (cap > 2*risk)
		    {
			write("You almost lose your balance.\n" +
			      "Just barely, you manage to keep your hold " +
			      "on the branch.\n");
			tell_room(TO, QCTNAME(TP) + " almost loses " + 
				  TP->query_possessive() + " balance.\n" +
				  "But then, " + TP->query_pronoun() +
				  " manages barely to keep " + TP->query_possessive() +
				  " hold on the branch.\n", TP);
			climb_branch();
		    }
		    else
		    {
			write("Hit by the arrow, you let go of the branch.\n");
			tell_room(TO,"Hit by the arrow, " + QTNAME(TP) + 
				  " lets go of the branch.\n",TP);
			fall_branch(8*risk - cap);
		    }
		}
		else 
		    climb_branch();
	    }
	    else 
		fall_branch(5*risk-cap);
	}
	return 1;
    }
    else if (str == "down")
    {
	climb_skill = TP->query_skill(SS_CLIMB);
	dex_stat = TP->query_stat(SS_DEX);
	cap = climb_skill + dex_stat / 3;
	write("You try to climb down from the rock.\n");
	if (cap > random(2 * HARD_TO_CLIMB))
	{
	    write("You manage to climb down the rock.\n");
	}
	else
	{
	    write("As you try to climb down the rock, you slip.\n" +
		  "You tumble down from the rock, hurting yourself on sharp edges.\n");
	    tell_room(TO,BS(QCTNAME(TP) + " tries to climb down the rock, but " + 
			    TP->query_pronoun() + " slips and falls down.\n"),TP);
	    TP->reduce_hit_point(5*HARD_TO_CLIMB - cap);
	}
	TP->move_living("M",ITH_DIR + "nforest/ridge3");
	tell_room(ENV(TP),QCTNAME(TP) + " arrives from above.\n",TP);
	return 1;
    }
    NFN("Climb what?");
    return 0;
}

void
drop_item(object ob)
{
  string down_room;

  down_room = ITH_DIR + "nforest/ridge3";
  if (ob && present(ob))
  {
    tell_room(TO, "The " + ob->query_name() + " falls down from the rock onto the forest floor.\n");
    ob->move(down_room);
    tell_room(down_room, CAP(LANG_ADDART(ob->query_name())) + " falls down from above.\n");
  }
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!living(ob)) 
	set_alarm(1.0, 0.0, &drop_item(ob));
}

void
make_smoke(object fire)
{
    tell_room(TO,"Smoke from " + LANG_ADDART(fire->short()) + 
	      " is rising from below into the sky.\n");
    return;
}

public void
init()
{
    ::init();
    add_action(do_climb, "climb");
}

/*
 *	/d/Gondor/ithilien/nforest/lbranch.c
 *
 *	Coded 1993 by Olorin.
 *
 *	Modification log:
 *	27-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

/* how hard is it to climb up the cedar? - x + random(x) */
#define HARD_TO_CLIMB  20  
/* how hard is it to evade the arrows? - x + random(x) */
#define HARD_TO_EVADE  50  

public string describe();
public void   reset_room();

static int    Num_Arrow  = 200;
static string Extra_Line;

public void
create_gondor()
{
    set_short("the lowest branch of a giant cedar");
    Extra_Line =
	"This is the lowest branch of the cedar. Below the branch a large " +
        "rock is rising in a thicket of bushes close to the tree trunk. Thick " +
	"branches covered with green needles block the view in all directions. " +
        "You can climb up, or you might manage to climb down from the branch " +
	"onto the rock.";
    set_long(describe);
    add_item(({"bush","bushes","thicket"}),
	     "The cedar is surrounded by a dense thicket of bushes.\n");
    add_item(({"cypress","cypress tree","cypresses","cypress trees","forest","tree","trees"}),BS(
    "In the midst of the thicket there are a few cypress trees. They are " +
    "not very tall, standing in the shadow of the two giant cedars. \n"));
    add_item(({"cedars","cedar trees"}), BS(
    "These are two giant trees, rising many metres into the sky. The one farther " +
    "from you is even larger than the one you have climbed.  \n"));
    add_item(({"large cedar","larger cedar","first cedar","farther cedar","further cedar","other cedar"}), BS(
    "This is a really giant cedar tree. You estimate its height to about " +
    "forty meters. The trunk is so thick that three men could not embrace it. \n"));
    add_item(({"cedar","cedar tree","closer cedar","nearer cedar","second cedar","next cedar","smaller cedar"}), BS(
    "This is a giant tree with an enourmous trunk, even though it is smaller than the other cedar. \n"));
    add_item(({"branch","branches","bough","boughs","needles"}), BS(
    "All the branches of the cedar tree are densely covered with thick green needles. " +
    "The branch you are standing on is the lowest branch of the cedar. " +
    "It is thicker than a man's thigh and probably could hold several people. " +
    "The other branches are similar. Growing closely together, they block " +
    "the view in all directions, but you might manage to climb further up.\n"));
    add_item(({"rock","large rock"}), BS(
    "The large rock is directly under the branch on which you are standing. " +
    "Cracks are running through the rock, and there are several sharp edges " +
    "which probably would hurt you if you fell down from the branch onto the rock. \n" ));

    set_noshow_obvious(1);
}

public void
reset_room()
{
    Num_Arrow = 200;
}

public string
describe()
{
    object  clock = find_object(CLOCK);
    string  time  = tod(),
            long_descf = "You are in a giant cedar in a forest "
		+ "somewhere in northern Ithilien. ";

    if (!clock->query_war()) 
    {
	switch (time)
	{
	case "night":
	    long_descf += "Darkness rules the fields of Ithilien now in the nightime. ";
	    switch (clock->query_moon())
	    {
	    case "full":
		long_descf += "A full moon gives some light though. ";
		break;
	    case "dark":
		long_descf += "The sky is covered with dark clouds, "
		    + "and not even the moon shines through. ";
		break;
	    default:
		long_descf += "The moon gives a little light though. ";
		break;
	    }
	    break;
	case "afternoon":
	    long_descf += "The light of day shines across Ithilien. "+
		"It is afternoon. ";
	    break;
	case "morning":
	    long_descf += "The sun is on its way up on the morning sky to the east. ";
	    break;
	case "noon":
	    long_descf += "The sun is almost at its peak on its way across the sky. "+
		"It is the middle of the day in Middle-Earth. ";
	    break;
	case "evening":
	    long_descf += "The sun is setting in the west, coloring the sky golden red. ";
	    break;
	case "early morning":
	    long_descf += "The sun is rising in the east, casting long shadows "+
		"across Ithilien. ";
	    break;
	}
    }
    else 
    {
	switch (time)
	{
	case "evening":
	case "night":
	case "early morning":
	    long_descf += "Massive dark clouds cover the sky, making it " +
		"difficult to distinguish night and day. The clouds seem " +
		"to be coming from the east, where Mordor lies. You suspect " +
		"it is night now, as it is as dark as it can get. ";
	    break;
	case "morning":
	    long_descf += "A thick cover of clouds prevent the sun from " +
		"shining on the lands of Ithilien, and it is almost as " +
		"dark as at night. However you gather that it is probably " +
		"morning, as it is getting a bit lighter than earlier. ";
	    break;
	case "noon":
	    long_descf += "A dark mass of clouds seems to be rolling in from "+
        "the east, covering the sky above Ithilien. It is not much lighter now than "+
          "it usually is at night, but still you suspect it is the middle of the day. ";
	    break;
	case "afternoon":
	    long_descf += "A thick mass of clouds cover the sky, making it "+
        "difficult to see far. You suspect that it is afternoon, as it is getting "+
          "a bit darker than earlier. ";
	    break;
	}
    }
    if (Extra_Line) 
	long_descf += Extra_Line;
    return BSN(long_descf);
}

void
fall_branch(int hit)
{
  write(BS("You try to climb higher.\n"));
  write(BS("Suddenly you slip ...\n"));
  tell_room(TO,QCTNAME(TP) + " tries to climb higher into the tree, but slips.\n",TP);
  TP->reduce_hit_point(hit);
  write(BS("You lose your last hold on the branch you were trying to climb.\n"));
  write(BS("You fall down again, but you manage to stop your fall on the lowest branch of the tree.\n"));
  tell_room(TO,capitalize(TP->query_pronoun()) + " loses his hold and falls down again.\n",TP);
}

void
climb_branch()
{
  write(BS("Stepping from branch to branch, you manage to climb higher. \n"));
  tell_room(TO,"Stepping from branch to branch, " + QTNAME(TP) + " manages to climb higher.\n",TP);
  TP->move_living("M",ITH_DIR + "nforest/mbranch");
  tell_room(ENV(TP), QCTNAME(TP) + " arrives climbing up from below.\n",TP);
}

void
climb_rock()
{
  write(BS("You climb down from the branch onto the top of the rock.\n"));
  tell_room(TO,QCTNAME(TP) + " climbs down from the branch onto the top of the rock.\n",TP);
  TP->move_living("M",ITH_DIR + "nforest/on_rock");
  tell_room(ENV(TP), QCTNAME(TP) + " arrives climbing down from the cedar.\n",TP);
  return;
}

void
fall_rock(int hit)
{
  write("You try to climb down from the branch.\n");
  write("Suddenly you slip ...\n");
  tell_room(TO,QCTNAME(TP) + " tries to climb down from the branch, but slips.\n",TP);
  TP->reduce_hit_point(hit);
  write(BS("You fall down from the branch and painfully land on the top of the rock.\n"));
  tell_room(TO,capitalize(TP->query_pronoun()) + " falls down from the branch and lands on top of the rock.\n",TP);
  TP->move_living("M",ITH_DIR + "nforest/on_rock");
  tell_room(ENV(TP), QCTNAME(TP) + " arrives falling down from above.\n",TP);
  return;
}

int
do_climb(string str)
{
  int climb_skill, dex_stat, risk, hurt, cap;

  if(!str)
  {
    write("Climb what? \n");
    return 1;
  }

  climb_skill = TP->query_skill(SS_CLIMB);
  dex_stat = TP->query_stat(SS_DEX);
  risk = HARD_TO_CLIMB + random(HARD_TO_CLIMB);
  cap = climb_skill + dex_stat/2;

  if (str == "cedar" || str == "branch" || str == "bough" || str == "tree")
  {
    write(BS("Climb up or down?\n"));
    return 1;
  }

  if (str == "up")
  {
    if(cap > risk) climb_branch();
    else fall_branch(5*(risk-cap));
  }
  else if(str == "down")
  {
    risk = risk + random(HARD_TO_CLIMB);
    if(cap > risk) climb_rock();
    else fall_rock(5*(risk-cap));
  }
  else write("Climb what? \n");
  return 1;
}

void
arrow_hit(object tp)
{
  int dex_stat, risk, hurt;

  if(!present(tp->query_real_name(),TO)) return;
  if(tp->query_hp() < 50)
  {
    set_alarm(30.0, 0.0, &arrow_hit(tp));
    return;
  }

  if(!present("ranger",find_object(ITH_DIR + "nforest/lookout")))
  {
    set_alarm(30.0, 0.0, &arrow_hit(tp));
    return;
  }

  if(Num_Arrow == 0) return;

  if(IS_EVIL(tp))
  {
    dex_stat = tp->query_stat(SS_DEX);
    risk = HARD_TO_EVADE + random(HARD_TO_EVADE) + random(HARD_TO_EVADE);
    if(dex_stat > risk)
    {
      write(BS("An arrow narrowly misses you.\n"));
      tell_room(TO,"An arrow narrowly misses " + QTNAME(tp) + ".\n",TP);
    }
    else
    {
      write(BS("You are hit by an arrow fired from above.\n"));
      tell_room(TO,QCTNAME(tp) + " is hit by an arrow fired from above.\n",TP);
      tp->reduce_hit_point(50);
    }
    Num_Arrow--;
    set_alarm(itof(random(20+(200-Num_Arrow))), 0.0, &arrow_hit(tp));
  }
  return;
}

void
drop_item(object ob)
{
  string down_room;

  down_room = ITH_DIR + "nforest/on_rock";
  if (ob && present(ob))
  {
    tell_room(TO, "The " + ob->query_name() + " falls down onto the rock.\n");
    ob->move(down_room);
    tell_room(down_room, CAP(LANG_ADDART(ob->query_name())) + " falls down from the cedar.\n");
    down_room->drop_item(ob);
  }
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if(!living(ob)) 
    set_alarm(1.0, 0.0, &drop_item(ob));
  else if(IS_EVIL(ob))
    set_alarm(itof(random(10)), 0.0, &arrow_hit(TP));
}

void
make_smoke(object fire)
{
  tell_room(TO,"Smoke from " + LANG_ADDART(fire->short()) + " is rising from below into the sky.\n");
  return;
}

void
init()
{
    ::init();
    add_action(do_climb,"climb");
}

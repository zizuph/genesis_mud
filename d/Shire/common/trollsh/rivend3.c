/* File: /d/Shire/common/trollsh/rivend3.c */

#include "defs.h"
#include "/d/Shire/common/include/task.h"
#include <macros.h>
#include <language.h>
#include <ss_types.h>

#define GUARDT_FILE STAND_DIR + "npc/guardt"
inherit "/d/Shire/common/lib/eastroad";	/*master object*/

inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "w";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }



object guardt;

create_eastroad()
{
    set_short("Great Eastroad");
    set_long(
	"You are walking south of the great forest Trollshaws. " +
	"Here the road makes a turn southeast and west. Northeast " +
	"of you is a small ridge. The forest is very "+
	"thick here, obscuring your view of the woods.\n");

    add_item(({"eastroad", "road" }),
        "The road is wide and appears to be in constant use.\n");
    add_item(({"gravel"}),
	    "The gravel is rough and covers the road.\n");
    add_item(({"large trees", "trees"}),
        "Various tall firs and deciduous trees grow alongside " +
        "the road. They are tall, blocking the sky.\n");
    add_item("stunted trees",
        "They grow in various spots, dwarfed by their taller " +
        "neighbors. The stunted trees look like they have " +
        "survived the roughest treatment and defy the elements.\n");
    add_item(({"hill", "slippery hill","ridge"}),
    	"You might want to try to climb up there.\n");
/*
    guardt = clone_object(GUARDT_FILE);
    guardt->move(TO);
 */

    add_exit(STAND_DIR + "rivend4", "southeast", 0);
    add_exit(STAND_DIR + "rivend2", "west", 0);
    add_exit("/d/Shire/common/trollsh/shaws1","northeast",0,2);
}

public void
enter_inv(object ob, object from)
{
	string *names;
	::enter_inv(ob, from);
	names = ob->query_names();
	if(ob->id(npc_name))
	{
		if (!move_alarm || !sizeof(get_alarm(move_alarm)))
		{
			move_alarm = set_alarm(50.0 + rnd() * 20.0, 0.0, &move_patrol(ob));
		}
	return;
	}
}

/*
reset_room()
{

  if (!guardt) { guardt = clone_object(GUARDT_FILE);
    guardt->move(TO);
    }
}
 */
/*    add_call("climb", "[up] [the] 'hill' / 'up' / 'northeast'", "do_climb");
int

do_climb()
{
    string mess;

    if (TP->query_fatigue() < 25)
    {
	write("You are too exhausted to do an act like that.\n");
	return 0;
    }

    if (TP->resolve_task(DIFF_HARD, ({ SS_CLIMB, TS_DEX })) > 0)
    {
	write("You successfully climb up the hill.\n");
	say(QCTNAME(TP) + " successfully climbs up the hill.\n");

	TP->add_fatigue(-10);
	TP->move_living("M", STAND_DIR + "trollsh1");

	write("You feel more tired as you reach the top of the hill.\n");
	say(QCTNAME(TP) + " arrives climbing up the hill.\n");
	return 1;
    }
    else
    {
	write("You start climbing up the hill.\n");
	write("But as you reach the upper slope, you miss foothold,\n" +
	      "and slide back down to the bottom.\n");
	write("A small landslide sweeps across your head.\n");

	say(QCTNAME(TP) + " starts climbing up the hill.\n");
	say("But as " + HE_SHE(TP) + " reaches the upper slope, ");
	say(HE_SHE(TP) + " misses " + HIS_HER(TP) + " foothold, " +
	    "and slides back down to where you stand.\n" +
	    "A small landslide sweeps across " + QCTNAME(TP) + "'s head.\n");

	mess = " head suddenly pops up over the ridge to the southwest"+
	       " and gets a frightened look before it disappears down again," +
	       " real fast!!!\n";
	tell_room(STAND_DIR + "trollsh1", ({
	    break_string(CAP(LANG_POSS(TP->query_met_name())) + mess, 76),
	    break_string(CAP(LANG_POSS(TP->query_nonmet_name())) + mess, 76),
	    "" }));
	TP->add_fatigue(-20);
	return 1;
    }
}
*/

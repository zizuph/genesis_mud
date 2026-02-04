inherit "/std/object.c";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message) 	break_string(message,75)
#define PS(message)	process_string(message)
#define TP              this_player
#define TO              this_object

void
init()
{
    ::init();
    add_action("do_tear", "tear");
    add_action("do_tear", "rip");
    add_action("do_tear", "slice");
    add_action("do_tear", "cut");
}

void
create_object()
{
    set_name("tapestry");
    add_adj(({"ornate", "threadbare", "middle", "second", "north", "northern"}));
    set_short("ornate but threadbare tapestry, covering an entire wall");
    set_pshort("ornate but threadbare tapestries, each covering an entire wall");
    set_long(BS("This immense tapestry covers the entire northern wall. In " 
    + "once-brilliant colors now long faded, the fine, carefully woven silk "
    + "depicts a complex battle scene with amazing detail. Elves and humans "
    + "fight a tremendous war, weaving a intricate dance of death across "
    + "trampled fields. Above the battle plain, on an overhanging ledge with "
    + "a commanding view of the carnage below, a noble Elvish king appears to "
    + "be casting a final spell. A dark cloud of arrows descends from "
    + "the sky, and the outlook seems bleak for the Elvish defenders. The "
    + "artistry of the tapestry is sublime; almost you hear the screams of the dying and the "
    + "pleas of the wounded.\n"));
    
    add_prop(OBJ_M_NO_GET, BS("Strange...your hand seems to turn to lead as "
    + "you reach for the tapestry. Somehow you cannot muster the strength "
    + "even to rip down the silken cloth.\n"));
    
}

int
do_tear(string str)
{
    object ob1, ob2;

    if (!stringp(str)) {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (explode(str+" ", " ")[0]=="tapestry" || str=="tapestries")
    {
	notify_fail("Which tapestry do you wish to "+query_verb()+"?\n");
	return 0;
    }
    if (!parse_command(str, environment(TP()), "%o 'with' %o", ob1, ob2))
    {
	notify_fail(capitalize(query_verb())+" what with what?\n");
	return 0;
    }
    if (ob2==present("thane_quest_sword",TP()))
    {
	if (ob1==TO())
	{
	    write(BS("You grasp the ancient sword firmly in hand and rend the "
	    + "northern tapestry with a single effortless swipe. The silken cloth "
	    + "parts; through the gap you see, not a blank stone wall, but a "
	    + "huge battlefield swarming with frenetic activity. In your ears echo "
	    + "the sounds of battle: clash of metal, thunder of hoofbeats, and the "
	    + "screams of the dying reach out and embrace you. Now the slit in the "
	    + "tapestry issues a brilliant white light, and you feel yourself "
	    + "falling, falling through a fissure in time itself. As if from a "
	    + "great distance, you see yourself step through the tapestry...\n"));
	    TP()->move_living("X", MANSION+"battlefield_1.c");
	    say(BS((QCTNAME(TP())+" grasps an ancient sword and slices a "
	    + "tapestry down the middle. Suddenly a brilliant white light envelopes "
	    + QTNAME(TP())+", and "+TP()->query_pronoun()+" disappears before your "
	    + "eyes!\n")));
	    return 1;
	}
	else return 0;
    }
    else 
 	if (ob1==TO())
	{
	    write(BS("Though the silk of the tapestry seems quite delicate, nothing "
	    + "you do with the "+ob2->query_name()+" has the slightest effect. It is "
	    + "as if these tapestries were protected by a power whose key you have yet "
	    + "to find.\n"));
	    return 1;
	}
	else return 0;
}

inherit "/std/object.c";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)	break_string(message,75)
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
    add_adj(({"ornate", "threadbare", "third", "east", "eastern"}));
    set_short("ornate but threadbare tapestry, covering an entire wall");
    set_pshort("ornate but threadbare tapestries, each covering an entire wall");
    set_long(BS("Covering the entire eastern wall, the final tapestry concludes "
    + "the story of the ancient interracial war. The elvish army lies in "
    + "tatters; defeated warriors retreat hastily before the onslaught of "
    + "human barbarians, drunk on the destruction and carnage they have already "
    + "wrought. Everywhere lay charred and mutilated bodies, their twisted "
    + "frames mute witness to the horror of a war without cause. Behind the "
    + "human armies a dark Presence gloats, a black vile patch that seems to "
    + "taint even the evils of war. But out of the disordered Elvish forces a "
    + "single horseman rides, his sword aloft and burning with the light of a "
    + "thousand stars! The artistry of the tapestry is sublime; you can almost "
    + "feel the heat of the battlefield, and hear the hushed silence descend as "
    + "all eyes turn towards the ultimate confrontation of Light and Dark.\n"));
    
    add_prop(OBJ_M_NO_GET, BS("Strange...your hand seems to turn to lead as "
    + "you reach for the tapestry. Somehow you cannot muster the strength "
    + "even to rip down the silken cloth.\n"));
    
}

string
msg()
{
    return QCTNAME(TP())+" grasps an ancient sword and slices a "
    + "tapestry down the middle. Suddenly a brilliant flash of light "
    + "blinds you and a deafening thunderclap rolls through your body. "
    + "When your sight returns the tapestry is whole once again, and "
    + QTNAME(TP()) + " is getting up from the floor, visibly shaken.\n";
}

int
do_tear(string str)
{
    object ob1, ob2;
    
    if (explode(str+" ", " ")[0]=="tapestry" || str=="tapestries" || str=="")
    {
	notify_fail("Which tapestry do you wish to "+query_verb()+"?\n");
	return 0;
    }
    if (!parse_command(str, environment(TP()), "%o 'with' %o", ob1, ob2))
    {
	write(capitalize(query_verb())+" what with what?\n");
	return 1;
    }
    if (ob2==present("thane_quest_sword",TP()))
    {
	if (ob1==TO())
	{
	    ob2->remove_object();
	    write(BS("You grasp the ancient sword firmly in hand and rend the "
	    + "western tapestry with a single effortless swipe. As the silken "
	    + "cloth parts you hear somewhere a scream, remote as an old memory, yet "
	    + "frighteningly loud, as though the source were nearby. A thought "
	    + "passes through your mind, but it is not your own: 'Fool! You have "
	    + "chosen the wrong moment! Here my help comes too late...' "
	    + "The thought fades as if receeding into the distance. Sword and "
	    + "tapestry disappear in a blinding flash of light; a tremendous "
	    + "thunderclap throws you across the room. Suddenly the tapestry "
	    + "is there again, whole, but the ancient sword has vanished!\n"));
	    say(BS(VBFC(msg())));
	    return 1;
	}
	else return 0;
    }
    else 
 	if (ob1==TO())
	{
	    write(BS("Though the silk of the tapestry seems quite delicate, nothing "
	    + "you do with the "+ob2->query_name()+" has the slightest effect. It is "
	    + "as if these tapestries were protected by a power whose key you have yet"
	    + "to find.\n"));
	    return 1;
	}
	else return 0;
}



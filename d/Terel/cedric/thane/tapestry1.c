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
    add_adj(({"ornate", "threadbare", "first", "west", "western"}));
    set_short("ornate but threadbare tapestry, covering an entire wall");
    set_pshort("ornate but threadbare tapestries, each covering an entire wall");
    set_long(BS("Covering the entire western wall, the story of this "
    + "immense tapestry commences with an army of elves, preparing "
    + "for battle on a vast silver plain. With strange rituals the fair "
    + "warriors resign themselves to the deaths they must cause. Across the "
    + "plain, held back only by the thick fog of early morning, an army of "
    + "barbaric humans prepare for the battle in their own fashion, brawling and "
    + "carousing. Behind the humans a vast shape moves, a shape so dark your "
    + "eyes cannot even focus upon it. The artistry of the tapestry is sublime; "
    + "you fancy you can hear the hushed murmur of troops and beasts as they wait for "
    + "the fog to break.\n"));
    
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
    
    if (explode(str+" ", " ")[0]=="tapestry" || str=="tapestries")
    {
	write("Which tapestry do you wish to "+query_verb()+"?\n");
	return 1;
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
	    + "chosen the wrong moment! Here I cannot help, and you cannot follow...' "
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



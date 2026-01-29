/* mangle.c
   Tintin 920106 */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "login.h" 

int length, width;
mixed *pos;
int *proc;

/*
 * Prototypes
 */
public void mangle_player(object pl, int l, int w);

/*
 * Function name: create_room
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */
void
create_room()
{

    set_short("mangle room");
    set_long("You are in a small room. One side of the room is\n" +
	     "occupied by an enormous mangle with a slide leading\n" +
	     "into the interior of the machine. You can see that the\n" +
	     "rollers of the mangle are constantly moving. On the wall\n" +
	     "by the machine there are two large dials. One is marked\n" +
	     "LENGTH and has the positions 'extremely short', 'very short',\n" +
	     "'short', 'normal', 'tall', 'very tall', extremely tall  and\n" +
	     "'random'. The other one is marked WIDTH and has the settings\n" +
	     "'very skinny', 'skinny', 'lean', 'normal', 'plump', 'fat',\n" +
	     "'very fat' and 'random'.");
    pos = ({
	HEIGHTDESC + ({"random"}),
	WIDTHDESC + ({"random"}),
	});
    proc = SPREAD_PROC;
    add_item( ({ "dial", "dials", "knob", "knobs" }),
	      "@@show_dials");
    add_item( ({ "machine", "mangle" }),
	      "The mangle is a huge contraption with a cast iron frame\n" +
	      "and lots of belts, rollers and wheels inside.\n");
    add_prop(ROOM_I_INSIDE, 1);

    length = random(7);
    width = random(7);
}

public string
show_dials()
{
    return 
	"The LENGTH dial is set to " + pos[0][length] + ".\n" +
	"The WIDTH dial is set to " + pos[1][width] + ".\n";
}
    

/*
 * Function name: init
 * Description  : Add commands etc.
 */
public void
init()
{
    add_action("all_cmd", "", 1);
}

/*
 * Function name: long
 * Description  : Modify the behaviour of long
 */
public varargs mixed
long(string arg)
{
    mixed str;

    str = ::long(arg);

    if (arg)
	return str;

    str += "\n" + show_dials();

    if (this_player()->query_ghost() & GP_MANGLE)
	str += "\nYou are still rather shapeless. Something that the\n" +
	    "machine in front of you could change.\n";
    else if (!this_player()->query_ghost())
	str += "\nYou get a strong feeling that this is not a place for\n" +
	    "the living. You should probably leave as fast as you can. You\n" +
            "can see a small hatch by the side of the machine that could\n" +
            "take you out of here.\n";
    else 
	str += "\nWell, get going! You have your features left to fix.\n";
    return str;
}

/*
 * Function name: enter_cmd
 * Description  : Catch all player commands. Take care of the legal ones
 *                and throw all the others away
 */
public void 
enter_cmd(string str)
{
    if (!str)
    {
	write("Enter what?\n");
	return;
    }

    switch (str)
    {
    case "hatch":
	if(this_player()->query_ghost())
	{
	    write("Enter what?\n");
	    return;
	}
	this_player()->move_living("through hatch", 
				   this_player()->query_def_start());
	break;
 
    case "mangle":
    case "machine":
	/* This is where the player gets modified. Awfully hardcoded
	    Im afraid
	 */
	mangle_player(this_player(), length, width); 
	break;
    default:
	write("Enter what?\n");
	break;
    }
}

public void
turn_cmd(string str)
{
    string knob, set;
    int i;

    if (!str)
    {
	write(capitalize(query_verb()) + " what?\n");
	return;
    }
    if (!parse_command(str, ({ }),
		       "[dial] / [knob] %w [dial] / [knob] [to] %s",
		       knob, set))
    {
	write(capitalize(query_verb()) + " what?\n");
	return;
    }

    /* Yes, this is ugly, I know */
    switch (lower_case(knob))
    {
    case "length":
	if (set == "normal")
	    set = "of normal length";
	i = member_array(set, pos[0]);
	if (i == (sizeof(pos[0]) - 1))
	    length = random(sizeof(pos[0]) -1);
	else if (i >= 0)
	    length = i;
	else
	{
	    write("What value do you want to set it to?\n");
	    return;
	}
	break;
    case "width":
	if (set == "normal")
	    set = "of normal width";
	i = member_array(set, pos[1]);
	if (i == (sizeof(pos[1]) - 1))
	    length = random(sizeof(pos[1]) -1);
	else if( i >= 0)
	    width = i;
	else
	{
	    write("What value do you want to set it to?\n");
	    return;
	}
	break;
    default:
	write("Which knob do you want to turn?\n");
	return;
    }
    write("You set the " + knob + " dial to " + set + ".\n");
    say(break_string(QCTNAME(this_interactive()) +
		     " sets the " + knob + " to " + set + ".\n",76));
}
/*
 * Function name: all_cmd
 * Description  : Catch all player commands. Take care of the legal ones
 *                and throw all the others away
 */
public int
all_cmd(string str)
{
    switch(query_verb())
    {
    case "depart":
	say(QCTNAME(this_player()) + " enters the mangle.\n");
	return 1;
	break;
    case "arrive":
    case "glance":
    case "say":
    case "quit":
    case "Goto":
    case "goto":
    case "look":
    case "exa":
    case "examine":
    case "who":
    case "home":
    case "sysbug":
    case "idea":
    case "praise":
    case "save":
    case "typo":
    case "bug":
	return 0;
	break;
    case "enter":
	enter_cmd(str);
	return 1;
	break;
    case "set":
    case "turn":
	turn_cmd(str);
	return 1;
	break;
    case "help":
	write("You are supposed to mangle your body into shape.\n");
	write("You set the dials with for example:\n");
	write("   'set length short' or 'turn dial width to random'\n");
	write("When you have done so, you enter the mangle with:\n");
	write("          'enter mangle'\n");
	return 1;
	break;
    default:
	if (this_player()->query_wiz_level() > 40)
            return 0;
	write("That is not possible here.\n");
	return 1;
    }
}

/*
 * Function name: mangle_player
 * Description:   Mangle a player into shape and move to the next room
 * Arguments:     pl: player to mangle
 */
public void 
mangle_player(object pl, int l, int w)
{
    int myl, myw;
    int *attr;

    if (!(pl->query_ghost() & GP_MANGLE))
	return;

    set_this_player(pl);

    write("You enter the mangle. You can feel it starting to shape your\n");
    write("shapeless body. Strangely enough, it is not painful...\n");

    attr = RACEATTR[pl->query_race_name()];

    if (!sizeof(attr))
    {
	write("You have a bad body, go get a better one.\n");
	pl->set_ghost(pl->query_ghost() | GP_BODY);
	pl->ghost_start();
    }

    myl = (attr[0] * proc[l]) / 100 - random(attr[0] / 10);
    myw = (attr[5] * myl * (w + 7) / 10);
    if (random(2))
	myw = myw - random(myw * attr[5] / 8000);
    else
	myw = myw + random(myw * attr[5] / 5000);

    pl->add_prop(CONT_I_HEIGHT, myl);
    pl->add_prop(CONT_I_WEIGHT, myw);
    pl->add_prop(CONT_I_VOLUME, myw);
    
    write("...you are slowly passed through the mangle and after a while\n");
    write("you come out of it as a new " + pl->query_race_name() + ".\n\n");

    pl->set_ghost(pl->query_ghost() & ~GP_MANGLE);

    if (pl->query_ghost() & GP_FEATURES)
	pl->move_living("X", PATH + "features");
    else if (pl->query_ghost() & GP_SKILLS)
	pl->move_living("X", PATH + "skills");
    else
    {
	pl->set_ghost(0);
	pl->ghost_ready();
    }
}

 

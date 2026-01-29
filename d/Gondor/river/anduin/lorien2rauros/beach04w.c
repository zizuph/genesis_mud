/*
 * /d/Gondor/river/anduin/lorien2rauros/beach04w.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 65 miles downstream from the silverlode, the campsite for day 2.
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";
inherit "/d/Gondor/common/lib/dig";

#include <wa_types.h>		/* for W_SLASH */
#include <composite.h>		/* for COMPOSITE_WORDS */
#include <macros.h>		/* for QCTNAME */
#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"

#define	RIVER		(LORIEN_TO_RAUROS_DIR+"river04")
#define	NAMES_FILE	(LORIEN_TO_RAUROS_DIR+"beach04w_names")

#define GEMS_LIST	({ "amber", "agate", "jasper", "onyx",  \
                   	   "garnet", "jade", "beryl", })
#define	NGEMS	7

/* prototypes */
public void	create_shore_room();
public void	reset_room();
public void	init();
public void	leave_inv(object ob, object dest);
public string	exa_bark();
public int	carve_bark(string arg);
public int	dig_results(object digger);

string	*Names;
static string	Namestr;
static int	Gem_here;

/*
 * Function name:	create_shore_room
 * Description	:	set up the beach
 */
public void
create_shore_room()
{
    FIX_EUID;

    restore_object(NAMES_FILE);
    switch (sizeof(Names))
    {
    case 0:
	Namestr = " The name 'Gnadnar' has been carved into the bark.";
	Names = ({ "'Gnadnar'" });
	break;
    case 1:
	Namestr = " The name "+Names[0]+" has been carved into the bark.";
	break;
    default:
	Namestr = " The names "+COMPOSITE_WORDS(Names)+
	    " have been carved into the bark.";
	break;
    }

    set_short("small patch of sand");
    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"A venerable oak towers above, its thick roots almost completely "+
	"enclosing this small patch of sand. The only opening "+
	"is to the east, where the Great River rolls past.");
    set_tod_landtype("sand");
    set_tod_landname("the Hill-lands");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("east",
	({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );

    add_exit("river04", "east", 0, 2, 1);
    set_no_exit_msg( ({ "northeast", "north", "northwest", "west",
	"southwest", "south", "southeast" }),
	BSN("The tangled roots make it impossible to move in "+
	    "that direction."));

    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", "waters", "water", }),
	&exa_water(RIVER,
	    "The waters of the Anduin are deep, swift and silent.\n"));

    add_item( ({ "hill", "hills", "land", "hill-lands",
    	"shore", "shores", "river bank", "river banks", "bank", "banks" }),
	BSN("All that can be seen of this shore is the giant oak tree. "+
	    "On the far side of the river trees overhang the water, "+
	    "blocking all view of the lands beyond."));
    add_item( ({ "far side", "side", "eastern shore", "east shore",
	"eastern bank", "east bank", }),
	BSN("Trees grow thickly along the far side of the river, "+
	    "blocking all views to the east."));
    add_item( ({ "western shore", "west shore", "western bank",
	"west bank", }),
	BSN("All that can be seen from here is the "+
	    "giant oak and its enclosing roots."));
    add_item( ({ "great trees", "trees", "forest" }),
	BSN("Across the Anduin, great trees overhang the river."));
    add_item( ({ "venerable oak", "giant oak", "oak tree", "venerable tree",
	"oak", "giant tree", "tree" }),
	BSN("The oak is a giant of the forest. Your outstretched arms "+
	    "would reach barely one-quarter of the way around its trunk, "+
	    "and its roots are as thick as your wrists."));
    add_item( ({ "trunk", }),
	BSN("The massive trunk is covered with rough gray bark."));
    add_item( ({ "thick bark", "rough bark", "gray bark", "bark" }),
	exa_bark);
    add_item( ({ "surface", "furrows", "ridges" }),
	BSN("Deep furrows and ridges roughen the surface of the bark."));
    add_item( ({ "enclosing root", "enclosing roots", "thick root",
	"massive root", "massive roots", "cage", "root", "thick roots",
	"roots" }),
	BSN("The massive roots twist around the small sandy area "+
	    "almost as if forming a cage."));
    add_item( ({ "small sandy area", "sandy area", "area", "small patch",
	"small patch of sand", "patch of sand", "patch", "resting place" }),
	BSN("Tucked into the river bank below a giant oak, the "+
	    "small sandy area is enclosed by the tree's roots."));
    add_item( ({ "coarse gray and brown sand", "coarse gray sand",
    	"coarse brown sand", "coarse sand", "gray and brown sand",
	"gray sand", "brown sand", "sand", "ground", }),
	BSN("Coarse gray and brown sand provides a soft resting place "+
	    "beneath the oak."));

    add_cmd_item( ({ "thick bark", "rough bark", "gray bark", "bark" }),
	({ "touch", "feel" }),
	BSN("Your fingers snag on furrows and ridges in the bark."));
    add_cmd_item( ({ "venerable oak", "giant oak", "oak tree",
	"venerable tree", "oak", "giant tree", "tree" }),
	({ "climb" }),
	BSN("Trying to climb the massive oak is like trying to scale a "+
	    "sheer wall. You make no progress at all."));

    set_drink_from( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", }) );

    set_dig_pattern("[in] [the] [coarse] [gray] [and] "+
	"[brown] 'sand' / 'here'");
    set_dig_message("in the sand");

    reset_room();

} /* create_onwater */


/*
 * Function name:	reset_room
 * Description	:	reset the gem
 */
public void
reset_room()
{
    ::reset_room();
    Gem_here = 1;
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add drink and "carve" verbs
 */
public void
init()
{
    ::init();
    init_drink();
    add_action(carve_bark,	"carve");
    add_action(dig_here,	"dig");
} /* init */


/*
 * Function name:	leave_inv
 * Description	:	be sure digging alarm is cleared if digger
 *			manages to leave in spite of paralyze
 * Arguments	:	object ob -- the departing object
 *			object dest -- its destination
 */
public void
leave_inv(object ob, object dest)
{
    stop_digging(ob);
    ::leave_inv(ob, dest);
} /* leave_inv */


/*
 * Function name:	exa_bark
 * Description	:	VBFC for bark description + carved names
 * Returns	:	string -- the description
 */
public string
exa_bark()
{
    return BSN("The bark is thick, gray and appears rough to the touch." +
	   Namestr);
} /* exa_bark */


/*
 * Function name:	carve_bark
 * Description	:	handle carving name into the bark
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
carve_bark(string arg)
{
    object	tp = TP,
		*weapons;
    string	tpname;
    int		s;

    if (!strlen(arg))
    {
	NF0("Carve what where?\n");
    }

    arg = LOW(arg);
    tpname = tp->query_real_name();

    /* accept: carve gnadnar in/into/on the [adjectives] bark or trunk,
     * carve bark, carve name in/into/on bark, etc etc of course, this
     * will accept "carve my in/into/on bark", but we can probably 
     * live with that.
     */
    if (!parse_command(arg, ({ }),
        "[my] [name] ["+tpname+"] / ['"+tpname+"'] [in] / [into] / [on] "+
	"[the] [thick] [rough] [gray] 'bark' / 'trunk'"))
    {
	NF0("Carve what where?\n");
    }

    if (!sizeof(weapons = tp->query_weapon(-1)))
    {
	NF0("You cannot carve with your bare hands.\n");
    }
    if (!sizeof(filter(weapons, &operator(&)(W_SLASH) @ &->query_dt())))
    {
	NF0("You don't seem to be wielding a suitable tool for carving.\n");
    }

    s = sizeof(Names);
    if (tpname[0..0] != "'")
    {
	tpname = "'"+CAP(tpname)+"'";
    }
    if (member_array(tpname, Names) >= 0)
    {
	NF0("You already have carved your name into the bark.\n");
    }

    /*
     * construct Namestr here, instead of every time someone looks at
     * the bark.
     *
     * sizeof(Names) should always be > 0, but paranoia requires we test ...
     */
    if (s > 0)
    {
	Names += ({ tpname });
	Namestr = " The names "+COMPOSITE_WORDS(Names)+
	    " have been carved into the bark.";
    }
    else
    {
	Namestr = " The name "+tpname+" has been carved into the bark.";
	Names = ({ tpname });
    }

    write("You carve your name into the bark.\n");
    SAY(" carves something into bark.");
    save_object(NAMES_FILE);
    return 1;
} /* carve_bark */




/*
 * Function name:	dig_results
 * Description	:	give results of digging
 * Arguments	:	object digger -- the person digging
 */
public void
dig_results(object digger)
{
    object	gem;
    if (!Gem_here)
    {
	tell_object(digger, "You find nothing buried in the sand.\n");
	return;
    }
    Gem_here = 0;
    gem = clone_object(OBJ_DIR+"gems");
    gem->set_gem_type(GEMS_LIST[random(NGEMS)]);
    tell_object(digger, "You find "+gem->short()+" buried in the sand!\n");
    if (gem->move(digger))
    {
	tell_object(digger, "Oops, you dropped it.\n");
	gem->move(TO, 1);
    }
    tell_room(TO,
	QCTNAME(digger)+" finds something buried in the sand.\n",
	digger);
} /* dig_results */

/*
 * yard.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit E_STD + "vale.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include <composite.h>
#include <files.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>
#include "/d/Gondor/open/room_chairs/room_chairs.h"
#include "room_trees.h"

#include TERRAIN_TYPES

#define CHAIR_NAME "rock"
#define APPLE_NAME "apple tree"
#define PLUM_NAME  "plum tree"

#define I_PATTERN      0
#define I_CAPACITY     1
#define I_OCCUPANTS    2
#define I_PREP         3

/* Global variables */
static mapping Room_trees = ([]);

static int     Mentioned;
static int     Multiples;

/* Prototypes */
public void           create_area_room();
public void           leave_inv(object ob, object dest);
public string         look_at(string arg);
public int            do_climb(string arg);
public varargs string sittin_in_tree(string name, object for_obj, 
				     int namesonly, int definite = 1);
public varargs int    add_tree(string name, string parse_pat, 
			       int capacity = 1, string prep = "in",
			       int mentioned = 1, int multiples = 0);
public varargs void   do_climb_msgs(object pl, string prep, string name, 
				    int definite = 1);
public void           do_climb_down_msgs(object pl, string name);
public void           climb_down(object tp, string name, int domsg);
int                   do_say(string arg);

/*
 * Function name:    create_area_room()
 * Definition   :    Creates the room.
 */
public void
create_area_room()
{
    set_short("In the vale of Erech");
    set_areatype(AREATYPE_FARMLAND); /* Areatype, check ~Gondor/defs.h
				      * for specifications */
    set_area("central");             /* southern, central or northern */
    set_areadesc("garden");           /* jupp */
    set_grass("long");               /* grass description */
    set_areaname("Erech");           /* name of the area */
    set_extraline("Several fruit trees fill the garden with the bright " +
        "colours of fresh fruit and the intoxicating scent of flowers.");
                                     /* set extra longdesc */
  
    add_item("field", "You find no field.\n");
    add_item("furrow", "You find no furrow.\n");
    vale_items();
    add_chair(CHAIR_NAME, "[down] [on] [the] 'rock'", 2, "on");
    add_item("rock", &look_at(CHAIR_NAME));
    add_tree(APPLE_NAME, "[up] [into] [apple] 'tree'", 1, "in");
    add_tree(PLUM_NAME, "[up] [into] [plum] 'tree'", 2, "in");
    add_item( ({ "tree", "trees", "apple tree", "apple trees", "plum tree",
	"plum trees" }), &look_at(APPLE_NAME));
     
    
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_herbs("garden");

    add_exit(E_FARM + "house.c", "east", 0, 3, 0);
}

public void
init()
{
    ::init();
    init_room_chairs();
    add_action(do_climb, "climb");
    add_action(no_hide, "hide");
    add_action(do_say, "say");
    add_action(do_say, "'", 2); 
    if (this_player()->query_wiz_level())
    {
	add_action(no_hide, "invis");
    }
}

public void
leave_inv(object ob, object dest)
{
    string treename,
      vb = query_verb();

    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
    
    if (living(ob) && vb != "In" && vb != "At")
    {
	ob->unset_no_show_composite();
	if (strlen(treename = ob->query_prop(LIVE_S_SITTING)))
	{
	    climb_down(ob, treename, 1);
	}
    }
}

public string
look_at(string arg)
{
    switch(arg)
    {
    case CHAIR_NAME:
        return "This a rather strange rock. It almost looks like a chair. " +
	    sitting_on_chair(CHAIR_NAME, this_player(), 0);
    case APPLE_NAME:
    case PLUM_NAME:
      return "Various trees are scattered around the garden. Some look " +
	"like they could be easily climbed, and some look rather impossible. " +
	sittin_in_tree(APPLE_NAME, this_player(), 0) + 
	sittin_in_tree(PLUM_NAME, this_player(), 0) +
	" The branches are laden with fruit.\n";
    }
}

public varargs string
sittin_in_tree(string name, object for_obj, int namesonly, int definite = 1)
{
    mixed       *treeptr;
    object      *occupants, others;
    int         i, s;
    string      *names, desc;

    if (!strlen(name) || !pointerp(treeptr = Room_trees[name]) ||
	!(s = sizeof(occupants = treeptr[I_OCCUPANTS])))
    {
	return "";
    }

    if (!objectp(for_obj))
    {
	for_obj = this_player();
    }

    if (s == 1)
    {
	if (occupants[0] != for_obj)
	{
	    desc = occupants[0]->query_Art_name(for_obj) + " is";
	}
	else
	{
	    desc = "You are";
	}
    }
    else
    {
	if ((i = member_array(for_obj, occupants)) < 0)
	{
	    names = occupants->query_art_name(for_obj);
	}
	else
	{
	    others = exclude_array(occupants, i, i);
	    names = others->query_art_name(for_obj) + ({ "you" });
	}
	desc = capitalize(COMPOSITE_WORDS(names)) + " are";
    }

    if (!namesonly)
    {
	if (Multiples)
	{
	    if (s == 1)
	    {
		desc += " sitting " + treeptr[I_PREP] + " one of the " + 
		    LANG_PWORD(name) + ".";
	    }
	    else
	    {
		desc += " sitting " + treeptr[I_PREP] + " the " + 
		    LANG_PWORD(name) + ".";
	    }
	}
	else if (definite)
	{
	    desc += " sitting " + treeptr[I_PREP] + " the " + name + ".";
	}
	else
	{
	    desc += " sitting " + treeptr[I_PREP] + " " + LANG_ADDART(name) + ".";
	}
    }

    return desc;
}

public varargs int
add_tree(string name, string parse_pat, int capacity = 1, string prep = "in",
	 int mentioned = 1, int multiples = 0)
{
    if (strlen(name) && strlen(parse_pat))
    {
	Room_trees[name] = ({ parse_pat, capacity, ({}), prep });
	Mentioned = mentioned;
	Multiples = multiples;
	return 1;
    }
    return 0;
}

public int
remove_tree(string name)
{
    if (strlen(name) && pointerp(Room_trees[name]))
    {
	m_delete(Room_trees, name);
	return 1;
    }
    return 0;
}

public int
do_climb(string arg)
{
    mixed     *indices, *treeptr;
    object    *occupants, tp = this_player();
    int       cap, i, ntrees, s;
    string    treename;

    if (strlen(tp->query_prop(LIVE_S_SITTING)))
    {
        if (arg == "down")
	{
	    treename = tp->query_prop(LIVE_S_SITTING);
	    climb_down(tp, treename, 1);
	    return 1;
	}
	notify_fail("How can you climb here?\n");
	return 0;
    }

    if (tp->query_prop(OBJ_I_HIDE) || tp->query_prop(OBJ_I_INVIS) ||
	tp->query_invis())
    {
	write("Climbing would reveal your presence.\n");
	return 1;
    }

    indices = m_indices(Room_trees);
    if (!(ntrees = sizeof(indices)))
    {
        notify_fail("Climb what?\n");
	return 0;
    }

    s = strlen(arg);
    for (i = 0; i < ntrees; i++)
    {
	treeptr = Room_trees[indices[i]];
	if (!s || arg == "up" || arg == indices[i] || 
	    parse_command(arg, ({}), treeptr[I_PATTERN]))
	{
	    occupants = treeptr[I_OCCUPANTS];
	    if (sizeof(occupants) < treeptr[I_CAPACITY])
	    {
	        tp->set_no_show_composite(1);
		tp->add_subloc(TREE_S_SUBLOC, this_object());
		tp->add_prop(LIVE_S_SITTING, indices[i]);
		treeptr[I_OCCUPANTS] += ({ tp });
		do_climb_msgs(tp, treeptr[I_PREP], indices[i], Mentioned);
		return 1;
	    }
		notify_fail("There's no branches left for you in the " +
			    indices[i] + ".\n");
		return 0;
	}
    }
    notify_fail("Climb what?\n");
    return 0;
}

public varargs void
do_climb_msgs(object pl, string prep, string name, int definite = 1)
{
    string tmpstr;

    if (!Multiples && definite)
    {
	tmpstr = " the " + name;
    }
    else
    {
	tmpstr = " " + LANG_ADDART(name);
    }
    write("You climb up " + prep + tmpstr + ".\n");
    say(QCTNAME(this_player()) + " climbs up " + prep + tmpstr + ".\n");
}

public void
climb_down(object tp, string name, int domsg)
{
    mixed    *treeptr;

    tp->unset_no_show_composite();
    tp->remove_subloc(TREE_S_SUBLOC);
    tp->remove_prop(LIVE_S_SITTING);

    if (domsg)
    {
        do_climb_down_msgs(tp, name);
    }

    if (pointerp(treeptr = Room_trees[name]))
    {
	treeptr[I_OCCUPANTS] -= ({ tp });
    }
    else
    {
	TREE_LOG_ERR("no tree '" + name + "' for " + tp->query_name() + ".\n");
    }
}

public void
do_climb_down_msgs(object pl, string name)
{
    write("You climb down from the " + name + ".\n");
    say(QCTNAME(this_player()) + " climbs down from the " + name + ".\n");
}

public string
show_subloc(string subloc, object pl, object for_obj)
{
    string      name;
    mixed       *treeptr;

    if (this_player()->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
	return "";
    }

    if (subloc != TREE_S_SUBLOC)
    {
	return pl->show_subloc(subloc, pl, for_obj);
    }

    if (strlen(name = pl->query_prop(LIVE_S_SITTING)) &&
	pointerp(treeptr = Room_trees[name]))
    {
	if (Mentioned)
	{
	    name = " the " + name;
	}
	else
	{
	    name = " " + LANG_ADDART(name);
	}
	if (for_obj != pl)
	{
	    return capitalize(pl->query_pronoun()) + " is sitting " +
	      treeptr[I_PREP] + name + ".\n";
	}
	return "You are sitting " + treeptr[I_PREP] + name + ".\n";
    }
    return "";
}


int
do_say(string arg)
{
    if (strlen(this_player()->show_cont_subloc(TREE_S_SUBLOC, this_player())))
        tell_room(this_object(), "From the branches, ", ({ this_player() }));
    CMD_LIVE_SPEECH->say(arg);
}

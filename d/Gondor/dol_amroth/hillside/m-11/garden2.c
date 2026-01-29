/*
 * hillside/m-11/garden2.c
 *
 * Skippern 20(c)02
 *
 * A luxury estate in Dol Amroth. It should be possible to search for herbs
 *  here, aswell dig in the ground and search for stuff. To leave the garden
 *  you should climb up into the large oak and jump down on the roof.
 * Corrently there is a conflict between the herb code and the other search
 *  code.
 */
inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/drink_water";
inherit "/d/Gondor/common/lib/herbsearch";
inherit "/d/Gondor/open/room_chairs/room_chairs";
inherit "/d/Gondor/common/lib/dig";

#include "../../defs.h"
#include "../defs.h"
#include <composite.h>
#include <files.h>
#include <language.h> 
#include <macros.h>
#include <options.h>
#include <stdproperties.h>
#include "/d/Gondor/open/room_chairs/room_chairs.h"
#include "/d/Gondor/erech/farm/room_trees.h"
#include "/d/Gondor/defs.h"

inherit DOL_LIB + "garden";
 
#define CHAIR_NAME "rock"
#define TREE_NAME "pine tree"

#define I_PATTERN      0
#define I_CAPACITY     1
#define I_OCCUPANTS    2
#define I_PREP         3

/* Globale variables */
string          herbarea,
                *herbs;
static mapping  Room_trees = ([]);
static int      Thing_here, Shovel_here;
static int      Mentioned;
static int      Multiples;

/* Prototypes */
public void           leave_inv(object ob, object dest);
public string         look_at(string arg);
public int            do_climb(string arg);
public varargs string sittin_in_tree(string name, object for_obj,
                                     int namesonly, int definite = 1);
public varargs int    add_sit_tree(string name, string parse_pat,
                               int capacity = 1, string prep = "in",
                               int mentioned = 1, int multiples = 0);
public varargs void   do_climb_msgs(object pl, string prep, string name,
                                    int definite = 1);
public void           do_climb_down_msgs(object pl, string name);
public void           climb_down(object tp, string name, int domsg);
int                   do_say(string arg);
public void           climb_roof(object tp, string name, int domsg);
public void           dig_results(object digger);
/* The code */

void
create_gondor()
{
    FIX_EUID;

    set_short("A path through a garden");
    set_long("This is a beautiful garden, filled with bushes, flowers " +
	     "and trees. Near the house you find four statues, and in " +
	     "the middle of the garden stands a fountain in the middle " +
	     "of a small pound. In the far end of the garden, under the " +
	     "hedge is a dark shed.\n");

    /* Flowers: lilly, rose, tulip */
    add_item( ({ "flower", "flowers", "flower bed", "flower beds" }),
        "Both sides along the path beautiful beds with flowers. " +
	"There are all kinds of beautiful flowers in all colors.\n");
    /* Bushes: */
    add_item( ({ "bush", "bushes" }), "Bushes covers the base of the " +
	      "statues giving a sweet sent in the air.\n");
    add_item( ({ "tree", "trees" }), "As collumns reaching for the sky " +
	      " is some large trees scatered in the garden. You see some " +
	      "cypresses, hawthorns, maples, oaks and aspen trees here.\n");
    add_tree( ({ "cypress", "hawthorn", "maple", "oak", "aspen" }) );
    add_item("fountain", "In the middle of the garden a marble godess " +
	     "stands and pours water out of a vase and into a small pound.\n");
    add_item("pound", "In the middle of the garden there is a small pound. " +
	     "In the pound small waterlillys float, and when you look " +
	     "closely you notices fish swiming under the surface.\n");
    add_item( ({ "statue", "statues" }), "Four stout men carved out of " +
	      "white marble guards the front door.\n");
    add_item( ({"shed","dark shed"}), "This is a dark shed.\n"); 

    add_chair(CHAIR_NAME, "[down] [on] [the] 'rock'", 2, "on");
    add_item("rock", &look_at(CHAIR_NAME));
    add_sit_tree(TREE_NAME, "[up] [into] [plum] 'tree'", 2, "in");
    add_item( ({ "tree", "trees", "pine tree", "pine" }), &look_at(TREE_NAME));

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 5);

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_AMROTH_GARDEN);
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    set_drink_from( ({"pool", "pound", "fountain"}) );

    set_dig_pattern("[in] [the] [nice] [soft] 'soil' / 'dirt' / 'here'");
    set_dig_message("in the soft soil");
    set_dig_tools( ({ "shovel", "stick", "sword",
			"knife", "dagger", "axe" }) );
    /*
    herbs = HERB_MASTER->query_herbs( ({ "plains", "middle earth", "garden", 
					     "frout"}) );
    herbs = ({ one_of_list(herbs), one_of_list(herbs), one_of_list(herbs) });
    set_up_herbs(herbs, ({ "ground", "garden" }) );
    */
    reset_room();
}

void
init()
{
    ::init();
    init_drink();
    init_room_chairs();
    add_action(do_climb, "climb");
    add_action(no_hide, "hide");
    add_action(do_say, "say");
    add_action(do_say, "'", 2);
    add_action(dig_here, "dig");
    if (this_player()->query_wiz_level())
    {
        add_action(no_hide, "invis");
    }
}

void
reset_room()
{
    ::reset_room();
    Thing_here = 1;
    Shovel_here = 1;
}

string query_items_here() { return "Char="+Thing_here+", Shovel="+Shovel_here+
				".\n"; }

public void
leave_inv(object ob, object dest)
{
    string treename,
	vb = query_verb();

    stop_digging(ob);
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
        return "A strange rock, it almost looks like a chair. " +
            sitting_on_chair(CHAIR_NAME, this_player(), 0);
    case TREE_NAME:
      return "A huge pine stands close to the house. It looks like " +
	  "you might be able to climb to the roof from the pine. " +
	  sittin_in_tree(TREE_NAME, this_player(), 0) +
	  "\n";
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
            desc += " sitting " + treeptr[I_PREP] + " " + LANG_ADDART(name) +
		".";
        }
    }

    return desc;
}

public varargs int
add_sit_tree(string name, string parse_pat, int capacity = 1, 
	     string prep = "in", int mentioned = 1, int multiples = 0)
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
	else if (arg == "roof" || arg == "to roof")
	{
	    treename = tp->query_prop(LIVE_S_SITTING);
	    climb_roof(tp, treename, 0);
	    return 1;
	}
        notify_fail("How can you climb here?\n");
        return 0;
    }

    if (tp->query_prop(OBJ_I_HIDE) || tp->query_prop(OBJ_I_INVIS) ||
        tp->query_invis())
    {
        write("You decide not to climb, since that would probably reveal " +
	      "your presence.\n");
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
	    notify_fail("There's no brances left for you in the " +
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
climb_roof(object tp, string name, int domsg)
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
    write("You climb down from the tree and to the roof.\n");
    say(this_player()->query_nonmet_name() + "leaves climbing down " +
	"to the roof.\n");
    this_player()->move_living("M", DOL_HILLS + "m-11/roof", 1, 0);
    say(this_player()->query_nonmet_name() + " arrives from above.\n");

}


public void
do_climb_down_msgs(object pl, string name)
{
    write("You climb down from the " + name + ".\n");
    say(QCTNAME(this_player()) + " climbs down from a " + name + ".\n");
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

/*
 * Function name:       dig_results
 * Description  :       mask this routine to handle results of digging.
 * Arguments    :       object digger -- the person digging
 */
public void
dig_results(object digger)
{
    object      thing, token;
    if (!Thing_here)
    {
        tell_object(digger, "You find nothing buried in the soil\n");
	return;
    }
    Thing_here = 0;
    thing = clone_object(DOL_OBJ + "quest/charm");
    if (present("I_do_quest_token.c", digger))
    {
	token = present("I_do_quest_token.c", digger);
	if (token->query_task() == DOL_Q_TORMIR_CAHRM 
	    && token->query_part() == 1)
	    token->set_part(2);
    }
    tell_object(digger, "You find "+thing->short()+" buried in the soil!\n");
    if (thing->move(digger))
    {
        write("Oops, you dropped it.\n");
	thing->move(TO);
    }
    tell_room(TO,
	QCTNAME(digger)+" finds something buried in the soil.\n", digger);
} 

/*
 * Function name:       do_search
 * Description  :       handle searching the room & items
 * Arguments    :       object tp       this player
 *              :       string arg      whatever the player searched
 * Returns      :       string -- describes the result of the search.
 *
 * players can search any of the room items, plus "here".
 * we are interested in:
 *      "shed", "dark shed", "the shed", "the dark shed",
 *      or any of the above with "for shovel"
 *      or "for tool" appended.
 * we reject (return null str) for anything else.
 * we also return null str if there is no tools in the shed.
 *
 * when the returned string is null, the mudlib will give the default
 * "Your search reveals nothing special." message to the player.
 */
public string
do_search(object tp, string arg)
{
    string      msg,
                saymsg,
                target;
    object      ob;

    /* arg will never be null. if player does just "search",
     * mudlib will set arg to "here".
     */
    arg = LOW(arg);
    /*
    if (arg == "here")
    {
        return BSN("You poke aimlessly around the room, "+
		   "but find nothing interesting.");
    }
    */
    /* this will accept "search dark shed", but what the heck.
     * see /d/Gondor/common/doc/parse_command/README for more info.
     */
    if (parse_command(arg, ({}),
	  "[the] [dark] 'shed' [for] %s", target))
    {
    }
    else
    {
        return "";
    }

    if (strlen(target))
    {
        if (target == "shovel")
	{
	    if (!Shovel_here)
	    {
	        return "";
	    }
	}
	else
        {
	    return "";
        }
    }
    else
    {
        /* they didn't specify what to search for. we know that
	 * at least one object is present, and possibly both are.
	 * if only one, choose that one; else choose at random.
	 */ 
	target = "shovel";
    }

    /* success */
    if (target == "shovel")
    {
        ob = clone_object(DOL_OBJ + "quest/shovel");
	Shovel_here = 0;
    }
    msg = "You find "+LANG_ADDART(ob->short())+" hidden in the shed.\n";
    saymsg = QCTNAME(tp)+" finds something in the shed.\n";

    if (ob->move(tp))
    {
        /* tp can't hold it -- probably too heavy */
        msg += "Oops, you dropped it.\n";
	saymsg += QCTNAME(tp)+" drops "+LANG_ADDART(ob->short())+".\n";
	ob->move(TO, 1);
    }

    /* other people in the room will always see tp search.
     * this call to say() will let them see tp find stuff.
     *
     * if the hidden object is a quest item, you may want to delete this
     * call to say(), and the lines above that initialize saymsg, so that
     * bystanders don't learn where stuff is hidden just by watching.
     */
    say(saymsg);

    return msg;
}

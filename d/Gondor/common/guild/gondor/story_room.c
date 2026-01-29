/*
 * /d/Gondor/common/guild/gondor/story_room.c
 * Written by Stern 29 February 2000
 *
 * This room is the room for the RoN story book that was rescued
 * from the RoN guild when it was closed. 
 * It is based on the room in RoN where it was located: 
 ** /d/Gondor/common/guild/north/song_room.c
 **
 ** Revision history:
 ** 	10-Dec-1997, Gnadnar:	general cleanup and
 **				add working fireplace
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/new_library.c";
inherit "/d/Gondor/open/fireplace/fireplace";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include <composite.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"
#include "/d/Gondor/open/fireplace/fireplace.h"

#define	RESET_WOOD	10
#define BENCH_NAME   "wooden bench"
#define BENCH_CAPACITY 12

object gScroll;

public int	book_index();
public string	fire_desc(string arg);
public void     leave_inv(object ob, object to);
/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("a small cozy room behind the library");
    set_long(fire_desc);
    set_parse_pattern("[the] [small] 'fireplace'");
    add_chair(BENCH_NAME,
        "[down] [on] [one] [of] [the] [wooden] 'benches' / 'bench'",
        BENCH_CAPACITY, "on");
    add_item( ({ "small fireplace", "stone fireplace",
	"small stone fireplace", "fireplace" }), &fire_desc("fireplace"));
    add_item( ({ "flame", "flames", "fire" }), &fire_desc("fire"));

    /* add "... in fireplace" items so players may examine the wood/ashes 
     * in the fireplace even if they have wood/ashes in their inventory.
     */
    add_item( ({ "wood", "firewood", "wood in fireplace",
	         "firewood in fireplace" }),
	&fire_desc("wood"));
    add_item( ({ "ash", "ashes", "ash in fireplace", "ashes in fireplace" }),
	&fire_desc("ashes"));
    add_item( ({ "smokestack", "stack" }),
	"It's a plain smokestack. It starts somewhat above the hearth and " +
        "disappears into the ceiling.\n");

    add_item( ({ "wooden bench", "wooden benches", "bench", "benches",
        "sturdy bench", "sturdy benches", "oak bench", "oak benches",
        "sturdy oak bench", "sturdy oak benches", "sturdy wooden bench", 
        "sturdy wooden benches"}),
        "The sturdy oak benches are bolted against all walls but for " +
        "the one with the door. They are not too comfortable but can " +
        "hold quite a few people. An oversized book lies on one of the " +
        "benches. The cover simply states: 'Storybook of the Rangers', " +
        "and in smaller print 'started by the legendary Rangers of the " +
        " North'.\n");
    add_item( ({"book", "storybook", "oversized book", "green book"}), BSN(
	"The large green book has "
        + "decorations of gold upon it. Written upon the front is "
        + "the title: Storybook of the Rangers, and in smaller print: " +
        "started by the legendary " +
        "Rangers of the North. It is the book that was rescued from the " +
        "Tower of Fornost. You can "
        + "open it to see the index of stories, or you can even "
        + "\"write story' of your own, to add in the book.")); 
    add_item( ({ "stone", "wall", "walls" }), BSN(
	"The walls are smooth stone, skillfully set so that "+
	"no crack or seam is visible."));
    add_item( ({ "floor", "dark green rug", "green rug", "rug" }), BSN(
	"A dark green rug covers the stone floor."));
    add_item( ({ "ceiling" }), BSN(
	"The ceiling is simply smooth stone."));


    add_cmd_item( ({"book","storybook","oversized book","green book"}),
        "open", book_index);
    add_cmd_item( ({"book","storybook","oversized book","green book"}),
        "read", "You should rather open it and look at the index.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(RANGER_DIR + "library/rog_library"  , "east", 0, 1);
    set_library_name("The Storyroom of the Rangers");
    set_read_cmd("read");
    set_list_cmd("list");
    set_book_type("story");
    set_save_path(RANGER_DIR+"north/stories/stories");
    set_write_dir(RANGER_DIR+"north/stories");
    set_log_file("guild");
    set_up_library();

    reset_room();
}


/* Function name:	reset_room
 * Description	:	replenish the fire if necessary
 */
public void
reset_room()
{
    set_wood(RESET_WOOD);
    if ( query_fire_state() != FIRE_BURNING )
    {
	/* use an imaginary ranger to light the fire ... */
	tell_room(TO,
	    "A brown-cloaked hooded female human enters.\n");
	tell_room(TO,
	    "The brown-cloaked hooded female human puts some wood "+
	    "in the fireplace.\n");
	tell_room(TO,
	    "The brown-cloaked hooded female human lights the wood "+
	    "in the fireplace.\n");
	tell_room(TO,
	    "The brown-cloaked hooded female human leaves east.\n");
	set_fire_state(FIRE_BURNING);
    }

    if (!objectp(gScroll))
    {
        gScroll = clone_object(RANGER_DIR + "newspells/obj/pigeon_scroll");
        gScroll->move(this_object(), 1);
    }
}

/*
 * Function name:	lib_hook_read 
 * Description	:	read a story
 *                      (redefined to allow reading from a book
 *                      instead of shelf)
 * Arguments    :       int j: book(type) nr
 *                      object p: reader
 */
void
lib_hook_read(int j, object p)   /* REDEFINED */
{
    write("You read the "+booktype+" titled \""
      + capitalize(descrs[j])+"\".\n");
    say(QCTNAME(p)+" reads a "+booktype+" "+p->query_pronoun()
      + " found in the large green book.\n",p);
}

int
book_index()
{
  if (!sizeof(names)) return lib_hook_lib_empty();
  do_list("stories");
  return 1;
}


/*
 * Function name:	init
 * Description	:	add verbs for fire and book
 */
public void
init()
{   
    ::init();
 //   post_init();  
    init_room_chairs(); /* add chair verbs */
    init_fire();
    init_library();
}

int query_write_priv(object pl)
{
    if (IS_RANGER(pl) ||
      SECURITY->query_wiz_dom(pl->query_name()) == "Gondor")
    return 1;
  return 0;
}

int query_remove_priv(object pl)
{
  if (SECURITY->query_wiz_dom(pl->query_name()) == "Gondor"
    || GONDOR_MASTER->is_officer(pl->query_real_name()))
    return 1;
  return 0;
}

void
lib_hook_finish_book(int sec)
{
  if (sec)
    write("You drop your story into the mailbox of the Council.\n");
  else
    write("You finish your story, and add it in the large book.\n");
  say(QCTNAME(this_player())+" finishes writing a story.\n");
}

int
query_secure_add(object pl)
{
  return 0;
}

int
lib_hook_lib_empty()
{
  NF("There are no stories in the storybook.\n");
  return 0;
}

int lib_hook_no_remove_priv()
{
  NF("You are not allowed to remove any stories.\n");
  return 0;
}

int lib_hook_remove_fail_empty()
{
  NF("But the book is empty, there are no stories to remove?\n");
  return 0;
}

int lib_hook_remove_no_name()
{
  NF("There is no story by that name in the book!\n");
  return 0;
}

int do_list(string str)
{
  int i,j;
  string txt;
  if (strlen(str) && (str != "stories")) {
    NF("List what? The stories in the book, perhaps?\n");
    return 0;
    }
  if (!sizeof(names)) return lib_hook_lib_empty();
  txt = "These are the stories that you can read in the book:\n";
  for (i=0; i<sizeof(names); i++)
    txt += sprintf("%-20s %-55s\n", names[i], descrs[i]);
  write(txt);
  return 1;
}

int do_return(string s) { return 0; }
int do_borrow(string s) { return 0; }


/*
 * Function name:	fire_desc
 * Descripiton	:	VBFC for room and items that vary w fire
 * Arguments	:	string arg -- what we're looking at
 * Returns	:	string description
 */
public string
fire_desc(string arg)
{
    int		fire_state = query_fire_state();
    string	tmpstr;

    switch ( arg )
    {

    case "fireplace":
	switch ( fire_state )
	{
	case FIRE_BURNING:
	     return BSN("The stone fireplace in the center of the room " +
                "is not large, but holds a cheerful fire.");
	case FIRE_UNLIT_WOOD:
	     return BSN("The small stone fireplace in the center of the " +
                "room holds a stack of unlit wood.");
	default:	/* FIRE_ASHES */
	     return BSN("The small stone fireplace in the center of the " +
                "room is empty.");
	}

    case "fire":
	if ( fire_state == FIRE_BURNING )
	{
	    return BSN(
		({
		"Flames dance in the fireplace.",
		"The fire casts a warm glow over the room.",
		"The fire is burning brightly.",
		})[random(3)] );

	}
	return BSN("You find no fire.");

    case "wood":
	switch ( fire_state )
	{
	case FIRE_BURNING:
	    return BSN("The wood in the fireplace burns brightly, emiting "+
		"a pleasant warmth.");
	case FIRE_UNLIT_WOOD:
	   return BSN("Unlit wood is piled in the fireplace.");
	default:	/* FIRE_ASHES */
	    return BSN("You find no firewood.");
	}

    case "ashes":
	switch ( fire_state )
	{
	case FIRE_BURNING:
	    return BSN("Beneath the brightly burning fire, "+
		"ashes cover the bottom of the fireplace.");
	case FIRE_UNLIT_WOOD:
	    return BSN("Beneath the wood, "+
		"ashes cover the bottom of the fireplace.");
	default:	/* FIRE_ASHES */
	    return BSN("Ashes cover the bottom of the fireplace.");
	}

    default:	/* room description */
	if ( fire_state == FIRE_BURNING )
	    tmpstr = " A merry fire casts its glow over the room.";
	else
	    tmpstr = "";
        return BSN(
	    "The room for tales is small and plain, but cozy. " +
            "In the middle of the "+
	    "room a fireplace sits on the floor. One can walk around it, " +
            "and sit on one of the sturdy oak benches that are bolted to " +
            "the walls. A smokestack starts just high enough above the " +
            "hearth that, when sitting on a bench, one can still see the " +
            "opposite side of the room. " + tmpstr);
    }
    /* NOTREACHED */
}

/*
 * Function name:       leave_inv
 * Description  :       mask parent to be sure that departing players
 *                      are removed from chair/sofa occupants
 * Arguments    :       object ob -- the departing object
 *                      object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand
 * by the exit efunc check_sitting().
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object to)
{
 //   post_leave_inv(ob, to);

    ::leave_inv(ob, to);
    leave_inv_room_chairs(ob, to);
}


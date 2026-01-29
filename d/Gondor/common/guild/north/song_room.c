/*
 * /d/Gondor/common/guild/north/song_room.c
 *
 * Revision history:
 * 	10-Dec-1997, Gnadnar:	general cleanup and
 *				add working fireplace
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/new_library.c";
inherit "/d/Gondor/open/fireplace/fireplace";

#include <composite.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/north/lib/ranger_defs.h"
#include "/d/Gondor/open/fireplace/fireplace.h"

#define	RESET_WOOD	10

public int	sit_on_bench();
public int	book_index();
public string	fire_desc(string arg);


/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("the room for songs and tales");
    set_long(fire_desc);
    set_parse_pattern("[the] [small] 'fireplace'");

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


    add_item( ({ "comfortable chair", "chair" }),
        "The storyteller usually sit in this chair.\n");
    add_item( ({ "bench", "benches" }),
        "The oak benches look rather comfortable.\n");
    add_item( ({"pillars","pillar"}),
        "The pillars are very sturdy and made of beech.\n");
    add_item( ({ "wooden table", "sturdy table", "table" }), BSN(
	"On the sturdy table lies an oversized, green and golden book. "+
        "The cover simply states: Storybook of the Rangers of the North."));
    add_item( ({"book", "storybook", "oversized book", "green book"}), BSN(
	"The large green book has "
        + "decorations of gold upon it. Written upon the front is "
        + "the title: Storybook of the Rangers of the North. You can "
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
    add_cmd_item(({ "on chair", "in chair" }), "sit",
        "You don't want to sit in the storyteller's chair!\n");
    add_cmd_item(({ "on benches", "on the benches", "on bench", 
                        "on the bench" }), "sit", sit_on_bench);

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(RANGER_NORTH_DIR + "r_corridor"  , "north", 0, 1);
    add_exit(RANGER_NORTH_DIR + "n_corridor"  , "west" , 0, 1);
    add_exit(RANGER_NORTH_DIR + "e_corridor"  , "south", 0, 1);
    add_exit(RANGER_NORTH_DIR + "meeting_room", "east" , 0, 1);
    set_library_name("The Songroom of the Rangers of the North");
    set_read_cmd("read");
    set_list_cmd("list");
    set_book_type("story");
    set_save_path(RANGER_DIR+"north/stories/stories");
    set_write_dir(RANGER_DIR+"north/stories");
    set_log_file("guild");
    set_up_library();

    if (file_size(CHESS_GAME + ".c") > 0)
        clone_object(CHESS_GAME)->move(TO);
    else
        log_file("errors", file_name(TO) + 
            " >>>>> "+CHESS_GAME+" not found!\n");

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
	    "A grey-cloaked hooded female human enters.\n");
	tell_room(TO,
	    "The grey-cloaked hooded female human puts some wood "+
	    "in the fireplace.\n");
	tell_room(TO,
	    "The grey-cloaked hooded female human lights the wood "+
	    "in the fireplace.\n");
	tell_room(TO,
	    "The grey-cloaked hooded female human leaves west.\n");
	set_fire_state(FIRE_BURNING);
    }
}


int
sit_on_bench()
{
    WRITE("You sit down for a bit, but the storyteller "+
	"isn't here. You rise again.");
    say(QCTNAME(TP) + " sits down on a bench but rises quickly again.\n");
    return 1;
}

int
book_index()
{
  if (!sizeof(names)) return lib_hook_lib_empty();
  do_list("stories");
  return 1;
}

/*
 * In this room the story teller will be located. 
 * He will tell stories and sing songs if asked for. 
 */



/*
 * Function name:	init
 * Description	:	add verbs for fire and book
 */
public void
init()
{
    ::init();
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
    || NORTH_MASTER->is_officer(pl->query_real_name()))
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
	     return BSN("The stone fireplace is not large, but "+
		"it holds a cheerful fire.");
	case FIRE_UNLIT_WOOD:
	     return BSN("The small stone fireplace holds a stack of "+
		"unlit wood.");
	default:	/* FIRE_ASHES */
	     return BSN("The small stone fireplace is empty.");
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
	    "The room for songs and tales is dominated by four wooden "+
	    "pillars, standing in a single row in the center of the room. "+
	    "Between the innermost pillars is a wooden table, on which "+
	    "rests a large book.  Benches line the walls, and a comfortable "+
	    "chair is pulled up in front of the fireplace." +
	    tmpstr);
    }
    /* NOTREACHED */
}

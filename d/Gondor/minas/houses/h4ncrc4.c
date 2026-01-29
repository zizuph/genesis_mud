/*
 *  This is the study of Gimilzor. It is part of a quest coded jointly 
 *  by Olorin, Denbarra and Arren.
 *
 *  The key to the wallsafe can be found in the following hiding places:
 *    1 : exa behind small drawer
 *    2 : lift flagstone
 *    3 : lift seat
 *    4 : turn boar
 *    5 : lift odd candle
 *
 *
 *    Modification log:
 *        02 March 2007, Toby: Removed all BSN and added some '\n'
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/minas/quest/pw5_defs.h";

#define NO_OF_HIDING    5
#define NO_OF_SUSPECTS  8

#define DRAWER_DESC "The drawers contain spare writing materials which"\
                  + " are similar to those on the top of the desk. There"\
                  + " are many large drawers, yet only a single small"\
                  + " one."
#define SMALL_DRAWER_DESC "The small drawer contains some inkpots. "\
      + "You also notice that the drawer has less depth than the others."
#define CHEST_DESC "The small chest looks old, it's made of oak with "\
      + "silver fittings. Inside, you find maps, covering the whole bottom."
#define LID_DESC "On the lid of the chest there are several silver "\
      + "fittings. In the middle there is a star, while in each corner "\
      + "there is an animal head."

int    key_is_taken = 0;
int    wallsafe_is_found = 0;
object safe;

public void	create_gondor();
public string	behind_drawer();
public mixed	do_move(string str);
public int	do_roll(string str);
public int	do_open(string str);
public int	do_turn(string str);
public int	do_smash(string str);
public int	do_read(string str);
public int	get_key(object detective, int i);
public string	which_document();
public string	do_search(object detective, string str);
public void	reset_room();
public int	do_hide(string str);
public void	init();

public void
create_gondor()
{
    set_short("study");
    set_long(
        "This is the study of this palatial residence. "
      + "Against the outer wall of the building, under a window, sits "
      + "a desk with a chest beside it. A rather ordinary chair is by the "
      + "desk. On the opposite side is a large and comfortable chair. "
      + "While shelves line the other three walls, "
      + "the middle of the room is occupied by a large map table. "
      + "Candelabra are placed strategically around the room to afford "
      + "nighttime illumination. In a corner some stairs are leading down "
      + "onto the ground floor.\n");

    add_item(({ "study", "room" }), 
        "Around the room you see evidence of a true scholar, typical of the "
      + "Dunedain.\n");
    add_item("window", 
        "The window is looking out over the garden that is east of the house "
      + "between the house and the Fourth Wall of the city.\n");
    add_item(({ "walls", "stone walls" }), 
        "Bookshelves line three of the stone walls. Beside the window the "
      + "walls are covered by valuable tapestries.\n"); 
    add_item(({ "stairs", "flight of stairs", "steps" }), 
        "The stone steps are leading down to the ground floor of the "
      + "building.\n");
    add_item("corner", "In the corner are only the stairs.\n");
    add_item(({ "floor", "stone floor" }),
        "The stone floor is covered by a worn brown rug.\n");
    add_item(({ "table", "map table" }), 
        "This large table dominates the center of the room. Tacked upon it "
      + "are splendid maps of the known world, both old and new.\n"); 
    add_item(({ "map", "maps" }), 
        "Some are large maps of kingdoms, and there are a few rare traders' "
      + "maps which show safe routes and rest points. There is even a "
      + "speculative map of the legendary realm of Beleriand.\n");
    add_item(({"beleriand", "map of beleriand", }), 
        "The map is beautifully drawn, and decorated with touches of "
      + "gilt and a delicate wash of colour.\n");
    add_item(({ "tapestries", "tapestry" }), 
        "The valuable tapestries are mainly in brown, grey, and black in "
      + "this room. Probably the lord of the house considered more colourful "
      + "tapestries as an unwelcome distraction during his studies.\n");
    add_item(({ "shelf", "shelves", "bookshelves", "bookcases" }), 
        "These shelves are filled with books and scrolls, "
      + "both old and new. The collection here is quite enviable and "
      + "probably contains great lore. The shelves themselves are made of "
      + "fine mahogany.\n");
    add_item(({ "old books", "new books", "binding", "bindings", "page",
	"pages", "volume", "volumes", "book", "books" }), 
	"Some of the books look quite old; their bindings are worn "
      + "and spotted, and their pages loose. Others appear to be all "
      + "but new.\n");
    add_item(({ "scroll", "scrolls" }), 
	"Scrolls are tucked in among the books, filling every space on "
      + "the shelves.\n");
    add_item(({ "blank scroll", "blank scrolls" }), 
	"Some blank scrolls are stacked in the back corner of the desk.\n");
    add_item(({ "inkpots", "quills", "writing materials" }),
        "These are ordinary writing materials.\n");
    add_item("ceiling", "The ceiling looks discoloured in one spot.\n");
    add_item(({ "discoloured spot", "ceiling spot" }), 
        "You stand on the chair and look at the discoloured spot. It seems "
      + "that the ceiling has been repaired recently.\n");
    add_item(({ "comfortable chair", "reading chair", "reading-chair" }), 
        "This chair is large and rather plush, designed to be a "
      + "comfortable reading chair. It sits opposite the other chair in the "
      + "room and seems to be made for a night of reading.\n");

    add_item("desk", 
        "This desk is large and holds many drawers. It is covered with "
      + "papers and documents, and is rather poorly organized. A small stand "
      + "holds feather quills and inkpots of various colours. There are a few "
      + "blank scrolls which have been prepared for formal writing stacked "
      + "in the back corner of the desk. The desk sits below a window "
      + "benefiting from the daytime illumination.\n");
    add_item(({ "documents", "document", "ious", "iou", "papers" }), 
        which_document);
    add_item(({ "drawer", "drawers" }), DRAWER_DESC + "\n");
    add_item("small drawer", SMALL_DRAWER_DESC + "\n");
    add_item(({ "behind small drawer", "behind the small drawer" }),
        behind_drawer);

    add_item(({ "chest", "small chest" }), CHEST_DESC + "\n");
    add_item(({ "bottom", "bottom of chest" }), 
        "The bottom, as the rest of the chest, is made of oak. "
      + "It sounds sturdy.\n");
    add_item(({ "fittings", "silver fittings", "lid" }), LID_DESC +"\n");
    add_item(({ "heads", "animal heads", "animal head" }),
        "There are four different animal heads; bear, boar, lion "
      + "and tiger.\n");
    add_item(({ "star", "bear", "lion", "tiger" }),
        "It is of very fine workmanship.\n");
    add_item(({ "boar", "boar head" }),
        "It is of very fine workmanship, but it looks askew.\n");

    add_item(({ "chair", "chairs" }), 
      	"A rather ordinary chair is by the desk, and on the opposite "
      + "side is a large and comfortable chair.\n");
    add_item(({ "ordinary chair", "desk chair", "desk-chair" }), 
        "The slender chair is high-backed and made of stained oak. "
      + "Both the back and the seat have a thin leather upholstery.\n");
    add_item(({ "leather upholstery", "upholstery", "strip" }), 
        "While the entire seat is covered by leather, the back has only a "
      + "vertical strip.\n");
    add_item(({ "back", "back of chair" }),
        "The high back adds to the slenderness of the chair.\n");
    add_item(({ "seat", "leather seat" }),
        "The seat feels somewhat loose.\n");

    add_item(({ "rug", "worn rug", "brown rug" }),
        "The worn rug covers a large part of the floor.\n");
    add_item(({ "under rug", "under worn rug", "underneath rug",
	"underneath worn rug", "beneath rug", "beneath worn rug" }),
	&do_move("rug"));

    add_item(({ "candelabra", "candelabrum" }), 
        "These candelabra sit on polished brass stands which branch into "
      + "ten individual candleholders. There are five such candelabra "
      + "at various places in the room.\n");
    add_item(({ "candleholder", "candle holder" }),
        "In each candle holder sits a beeswax candle.\n");
    add_item(({ "candle", "candles" }), 
        "Each candle is made of beeswax and fairly large. One of the "
      + "candles looks rather odd.\n");
    add_item("odd candle", 
        "It seems to have been sloppily inserted into the candleholder.\n");

    add_cmd_item(({ "on chair", "on the chair" }), "stand", 
        "You briefly stand on the chair and feel tall.\n");
    add_cmd_item(({ "window", "through window" }), ({ "go", "enter", "jump" }),
        "There is nothing out there, and it is too high above the ground.\n"); 

    add_exit(MINAS_DIR + "houses/h1ncrc4", "down", 0, 1);

    FIX_EUID

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_I_SEARCH_TIME, 4);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    enable_reset(200);
}

public string
behind_drawer()
{
    write("You look behind the small drawer.\n");
    get_key(TP, 1);
    return "You put back the drawer again.\n";
}

public mixed
do_move(string str)
{
    string vb = QVB;
    if (vb == "push")
    {
        NF0("Push what?\n");    /* clupeid rubeus :-) */
    }

    switch(str)
    {
        case "rug" :
        case "up rug" :
        case "the rug" :
        case "up the rug" :
            if (!item_id("flagstone"))
	    {
                add_item(({ "flagstone", "flagstones", "tiles" }), 
                    "These are square rock tiles. One of the flagstones "
                  + "doesn't seem to fit properly.\n");
	    }
	    if (vb == "exa" ||
		vb == "look")
	    {
		return "You lift the rug and look underneath.\n" 
            	     + "Below the rug you see some flagstones.\n";
	    }
	    write("You lift the rug and look underneath.\n" 
            	+ "Below the rug you see some flagstones.\n");
            break;
        case "chest" :
        case "the chest" :
            write("You find nothing special.\n");
            break;
        case "flagstone" :
        case "the flagstone" :
        case "up flagstone" :
        case "up the flagstone" :
            write("You look beneath the flagstone.\n");
            get_key(TP, 2);
            break;
        case "seat" :
        case "the seat" :
        case "up seat" :
        case "up the seat" :
            write("You look beneath the seat.\n");
            get_key(TP, 3);
            break;
        case "boar" :
        case "the boar" :
        case "up boar" :
        case "boar head" :
        case "up boar head" :
        case "up the boar head" :
            write("You fail to pull it up.\n");
            break;
        case "odd candle" :
        case "up odd candle" :
        case "up the odd candle" :
            write("You lift up the odd candle.\n");
            get_key(TP, 0);
            write("You insert the candle in the candle holder again.\n");
            break;
	case "candle":
	    NFN0(CAP(query_verb()) + " which candle?");
	    break;
        default :
            NFN0(CAP(query_verb())+" what?");
            break;
     }
     return 1;
}

public int
do_roll(string str)
{
    switch(str)
    {
        case "up rug" :
        case "up the rug" :
            write("Below the rug you see some flagstones.\n");
            if (!item_id("flagstone"))
                add_item(({ "flagstone", "flagstones", "tiles" }), 
                    "These are square rock tiles. One of the flagstones "
                  + "doesn't seem to fit properly.\n");
            break;
        default :
            NFN0("Roll up what?");
            break;
     }
     return 1;
}

public int
do_open(string str)
{
    object  safe;

    switch(str)
    {
        case "drawer" :
            write("Which drawer?\n");
            break;
        case "drawers" :
        case "large drawers" :
            write(DRAWER_DESC + "\n");
            break;
        case "small drawer" :
            write(SMALL_DRAWER_DESC + "\n");
            break;
        case "chest" :
        case "the chest" :
            write("Inside, you find maps, covering the whole bottom.\n");
            break;
        case "flagstone" :
        case "seat" :
            write("How would you open a "+str+"?\n");
            break;
        case "safe" :
        case "wallsafe" :
            if (objectp(safe = present("safe", TO)))
                return (safe->do_default_open(str));
            NFN0("Open what?");
            break;
        default:
            NFN0("Open what?");
            break;
     }
     return 1;
}

public int
do_turn(string str)
{
    switch(str)
    {
        case "boar" :
        case "the boar" :
        case "boar head" :
            WRITE("You turn the boar head, and then pull it up.");
            get_key(TP, 4);
            break;
        default :
            NFN0(CAP(query_verb())+" what?");
            break;
     }
     return 1;
}

public int
do_smash(string str)
{
    switch(str)
    {
        case "safe" :
        case "wallsafe" :
        case "the wallsafe" :
            if (objectp(safe = present("safe", TO)))
            {
                write("Ouch! That hurt!\n");
                write("There isn't even a scratch on the wallsafe.\n");
                TP->heal_hp(-20);
                return 1;
            }
        default :
            NFN0("Smash what?");
            break;
     }
     return 1;
}

public int
do_read(string str)
{
    switch(str)
    {
        case "document" :
        case "documents" :
        case "paper" :
        case "papers" :
        case "iou" :
        case "ious" :
           write(which_document());
           break;
	case "map":
	case "maps":
	case "scroll":
	case "scrolls":
	case "volume":
	case "volumes":
	case "book":
	case "books":
	    write("Intrigued by the accumulated lore, you begin to browse, "
                + "but recollect yourself with a sigh. Reading the "
                + "contents of these shelves would take far too long.\n");
	    break;
        default :
            NFN0("Read what?");
            break;
     }
     return 1;
}

public int
get_key(object detective, int i)
{
    object key;

    if ((detective->test_bit("Gondor",
        MTIRITH_MURDER_GROUP,
        MTIRITH_MURDER_BIT)) || key_is_taken)
    {
        write("Your search reveals nothing special.\n");
        return 0;
    }

    MT_PW5_MASTER->load_me();
    if (i ==
	MT_PW5_MASTER->query_hiding_place(LOW(detective->query_real_name())))
    {
        write("You find a key in a small hiding place!\n");
        key_is_taken = 1;
        key = clone_object(MINAS_DIR + "quest/wallsafe_key.c");
        key->add_prop(MT_PW5_S_OWNER, detective->query_real_name());
        key->move(detective, 1);
        return 1;
    }
    write("Your search reveals nothing special.\n");
    return 0;
    
}

public string
which_document()
{
    string *suspects = allocate(NO_OF_SUSPECTS),
            murderer;
    int     i;

    MT_PW5_SUSPECT->load_me();

    write("There are several IOU's here with recent dates. ");
    write("You find some interesting names. Here is a list of them:\n");

    suspects = MT_PW5_SUSPECT->query_suspect_name(-1);
    murderer = MT_PW5_MASTER->query_murderer_name();

    for (i = 0; i < NO_OF_SUSPECTS; i++)   
    {
        if (murderer != suspects[i])
            write("\t" + suspects[i] + "\n");
    }

    TP->add_prop(MT_PW5_I_FOUND_MOTIVE,
	TP->query_prop(MT_PW5_I_FOUND_MOTIVE) | 1);

    return "There are some other documents, but they are of routine nature.\n";
}

public string
do_search(object detective, string str)
{
    object ledger;

    if(!str)
        NFN("Search what?");

    switch(str)
    {
        case "small drawer" :
            write("You look behind the small drawer.\n");
            get_key(TP, 1);
            return "You put back the drawer again.\n";
        case "drawer" :
        case "drawers" :
            return DRAWER_DESC + "\n" + SMALL_DRAWER_DESC + "\n";
        case "rug" :
        case "the rug" :
            if (!item_id("flagstone"))
	    {
                add_item(({ "flagstone", "flagstones", "tiles" }), 
                    "These are square rock tiles. One of the flagstones "
                  + "doesn't seem to fit properly.\n");
	    }
            return "Below the rug you see some flagstones.\n";
        case "chest" :
        case "small chest" :
            return CHEST_DESC + "\n" + LID_DESC + "\n";
        case "seat" :
            return "The seat feels somewhat loose.\n";
        case "boar" :
        case "boar head" :
            return "The boar head looks askew, "
		 + "as if it was in the wrong place.\n";
        case "flagstone" :
        case "flagstones" :
            return "One of the flagstones doesn't fit properly.\n";
        case "candles" :
            return "One of the candles looks rather odd.\n";
        case "odd candle" :
            return "It seems to have been sloppily inserted in the "
          + "candleholder. Or maybe it isn't the right size.\n";
        case "shelf" :
        case "shelves" :
        case "bookshelves" :
            if (!wallsafe_is_found)
            {
                safe = clone_object(MINAS_DIR + "quest/wallsafe");
                safe->move(TO, 1);
                ledger = clone_object(MINAS_DIR + "quest/pw5_ledger");
                ledger->move(safe, 1);
                wallsafe_is_found = 1;
            }
            return "You find a wallsafe among the bookshelves!\n";
        default :
            return "Your search reveals nothing special.\n";
            break;
     }
     NFN("You don't find any " + str + " to search.");
}

public void
reset_room()
{
    key_is_taken = 0;
    wallsafe_is_found = 0;
    if (objectp(safe))
        safe->remove_object();
}

public int
do_hide(string str)
{
    if (!strlen(str))
	return 0;

    if (!objectp(present(safe, TO)))
	return 0;

    if (!safe->id(str))
	return 0;

    write("You hide the wallsafe again behind the bookshelves.\n");
    say(QCTNAME(TP) + " hides the wallsafe behind the bookshelves.\n");

    wallsafe_is_found = 0;
    safe->remove_object();

    return 1;
}


public void
init()
{
    ::init();
    add_action(do_move,  "move");
    add_action(do_move,  "lift");
    add_action(do_move,  "pull");
    add_action(do_move,  "push");
    add_action(do_roll,  "roll");
    add_action(do_open,  "open");
    add_action(do_turn,  "turn");
    add_action(do_turn,  "screw");
    add_action(do_turn,  "twist");
    add_action(do_smash, "smash");
    add_action(do_smash, "break");
    add_action(do_read,  "read");
    add_action(do_hide,  "hide");
}


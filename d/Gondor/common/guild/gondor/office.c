/*
 *	/d/Gondor/common/guild/gondor/office.c
 *
 *	The company office of the Rangers of Gondor.
 *
 *	Modification log:
 *	19-Feb-1997, Olorin:	Changed includes to inherits.
 *	26-Jun-1998, Gnadnar:	Added a settle.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/lib/office.c";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define	GUILD_NUMBER	1
#define	SETTLE_NAME	"long settle"
#define	SETTLE_CAPACITY	12

object  board;

public void	create_office();
public void	init();
public void	leave_inv(object ob, object dest);
public string	look_at(string arg);    /* VBFC for room and chairs */
public int	plump(string arg);


/*
 * Function name:	create_office
 * Description	:	set up the room
 */
public void
create_office()
{
    string  name;

    set_short("the Office of the Council of Rangers");
    set_long(BSN(
	    "This spacious room is furnished only with a long settle "
          + "and a bulletin board. A plaque and a poster hang on the "
          + "south wall, and an open doorway leads north."));

    add_exit(RANGER_GON_DIR+"uphall", "north", check_sitting, 0);

    /* XXX doors and chair exit msg ? */
    clone_object(RANGER_DIR+"obj/cdoor1")->move(TO);

    board = clone_object(BOARD_DIR + "rog_priv_board");
    board->move(TO);

    add_chair(SETTLE_NAME,
	"[down] [in] / [on] [the] [long] 'settle'",
	SETTLE_CAPACITY, "on");

    add_item( ({ "long settle", "settle" }), &look_at(SETTLE_NAME));
    add_item( ({ "carving", "carvings", "carved back", "back", }),
	BSN("Delicate carvings of vines and flowers twine round "+
	    "the back of the settle."));
    add_item( ({ "vine", "flower", "vines", "flowers", }),
	BSN("The vines and flowers are carved in careful detail; "+
	    "they almost seem to grow from the wood."));
    add_item( ({ "blond oak", "oak", "wood" }),
	BSN("The settle is made from blond oak, carefully polished "+
	    "and beautifully carved."));
    add_item( ({ "colourful cushion", "cushion", "colourful cushions",
	"cushions", }),
	BSN("Cushions of all colours are heaped on the settle."));
    add_item( ({ "floor", "soft rushes", "rushes" }),
	BSN("Fresh rushes, soft and sweetly scented, cover the floor."));
    add_item( ({ "ceiling", "walls", "wall", }),
	BSN("The plaster walls and ceiling are quite clean."));
    add_item( ({ "plaster" }),
	BSN("The plaster is the colour of new cream."));

    add_cmd_item( ({ "colourful cushion", "cushion",
	"colourful cushions", "cushions", }),
	({ "get", "take", "pick", "steal" }),
	BSN("Please leave the cushions for other to enjoy."));
    add_cmd_item( ({ "soft rushes", "rushes" }),
	({ "smell", }),
	BSN("The rushes have the aroma of a hayfield on a sunny day."));

    set_company_number(GUILD_NUMBER);
} /* create_office */


/*
 * Function name:	init
 * Description	:	mask parent so we can call init_room_chairs()
 */
public void
init()
{
    ::init();
    add_action(plump, "plump");
    add_action(plump, "fluff");
    init_room_chairs();	/* add chair verbs */
} /* init */


/*
 * Function name:	leave_inv
 * Description	:	mask parent to be sure that departing players
 *			are removed from chair/sofa occupants
 * Arguments	:	object ob -- the departing object
 *			object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand
 * by the exit efunc check_sitting().
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */


/*
 * Function name:	look_at
 * Description	:	VBFC to describe room/settle + occupants
 * Arguments	:	string arg -- what's being looked at
 *				      null str -> it's the room
 * Returns	:	string -- the description
 */
public string
look_at(string arg)
{
    if (arg == SETTLE_NAME)
    {
	return BSN(
	    "The settle has a handsomely carved back and colourful "
	  + "cushions. It is long enough to seat several people "
	  + "very comfortably.")
	  + sitting_on_chair(SETTLE_NAME, this_player(), 0);
    }
    return "";	/* "cannot happen" */
} /* look_at */


/*
 * Function name:	plump
 * Description	:	let 'em plump the cushions
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
plump(string arg)
{
    string	vb = QVB;
    if (strlen(arg) &&
	parse_command(LOW(arg), ({}),
	    "[up] [the] [settle] 'cushion' / 'cushions' "+
	    "[on] [the] [long] [settle]"))
    {
	WRITE("You "+vb+" the cushions on the settle.");
	SAY(" "+vb+"s the cushions on the settle.");
	return 1;
    }
    NF0(CAP(vb)+" what?\n");
} /* plump */

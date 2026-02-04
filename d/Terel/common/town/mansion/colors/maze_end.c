/*
 * Dust 920812: This is the target room after the maze
 *      920904: violet hint added for zodiac quest
 */
inherit "/std/room";
// #include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/zodiac.h"
#define COLDIR TOWNDIR + "mansion/colors/"

/* the defines are just needed so the compiler doesnt complain
 * about colorpath.h (we have to reset hints as soon as one
 * enters this room
 */
#define HINTINDEX 0
#define TWOHINTS 0
#define REVERSE 0
#define HINT2INDEX 0
#define FROM 0
#define FROM2 0

/* Room-names for the 4 neighbour rooms */
#define	NORTH	"dummy"
#define	WEST	"dummy"
#define	EAST	"dummy"
#define	SOUTH	"dummy"

#include "/d/Terel/common/town/mansion/colors/colorpath.h"

/*
 * It contains a hint for the secret door
 * There are several hints spread, this is
 * hint number HINT_INDEX
 */
#define HINT_INDEX 5

/*
 * The following macros are intended to prevent lines from wrapping
 * around the screen, and avoid the wizard from having to put in explicit 
 * \n's.
 */

#define BSNN(s) break_string((s) + "\n\n",70)

/*
 * this_hint is the hint stored inthis room
 */
#define this_hint (calc_hint(5))
object box;


int
query_real_hint()
{
    return(this_hint);
}

/*
 * As soon as player leaves the room, the box is removed. used
 * as vbfc in add_exit, so it returns teh target room as string
 */
string
go_north()
{
    seteuid(getuid());
    if (box) box->remove_object();
    return(COLDIR + "violet");
}

/*
 * The box appears as soon as the player looks behind curtains (or opens it)
 */
behind_curtain(string str)
{
    seteuid(getuid());
    if (str != "behind curtain" && str != "behind curtains" &&
	str != "curtain" && str != "curtains")
	return 0;
    notify_fail("But the curtains are already open.\n");
    if (box) return 0;
    write("As you look behind the curtain, you find a box.\n");
    box = clone_object(TOWNDIR + "mansion/obj/box");
    box->move(this_object());
    return 1;
}

create_room()
{
    set_long("@@long_desc");
    set_short("violet room");

    add_item("carpet","It's a heavy carpet of violet velvet.\n");
    add_item("curtain","Those are heavy curtains of violet velvet.\n");
    add_item("curtains","Those are heavy curtains of violet velvet.\n");
    add_exit("@@go_north", "north", 0, 0);
}

string
long_desc()
{
    return(BSN("It seems you reached the end of the maze. This room " +
	"is completely in violet: the carpet is violet, and heavy, " +
	"violet curtains fall down from the ceiling. The ceiling " +
	"itself is emitting a violet light."));
}


init()
{
    ::init();
    make_new_path(); /* create a new random path */
    add_action("behind_curtain","look");
    add_action("behind_curtain","move");
    add_action("behind_curtain","open");
    add_action("behind_curtain","draw");
}

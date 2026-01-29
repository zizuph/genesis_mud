/*
 * /d/Gondor/minas/rooms/surgery.c
 *
 * This is the surgery-room of Haldira, surgeon in Minas Tirith. Here is
 * where she actually performs surgery.
 *
 * /Mercade, 6 May 1994
 *
 * Revision history:
 */

inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define WAITING_ROOM (HOH_DIR + "surgeon_waiting")

void
create_room()
{
    set_short("the surgery room of the Houses of Healing surgeon");

    set_long(BSN("This room is large. It is the surgery room of Haldira, " +
	"surgeon in the Houses of Healing. You see an operating-table and a special " +
	"chair. Several shelves are mounted to the wall. A skeleton stands " +
	"on the floor. Several closets can be seen with all kinds of " +
	"medical supplies in them."));

    add_item( ({ "closet", "closets" }),
	BSN("The closets have glass doors and in it you can see many " +
	"medical supplies, like bandage and tools, like scalpels, " +
	"scissors, etcetera. Also, you see many potions in jars."));
    add_item( ({ "tool", "tools", "scalpel", "scalpels", "bandage",
	"supplies", "medical supplies", "scissors" }),
	BSN("In the closets you see many medical supplies, like bandage " +
	"and different tools like scissors and scalpels."));
    add_item( ({ "jar", "jars", "potion", "potions" }),
	BSN("In many labeled jars, you see various potions."));
    add_item( ({ "label", "labels" }),
	BSN("The print on the jars is too fine to read."));
    add_item( ({ "table", "operating-table", "operating table" }),
	BSN("It is a large oak operating-table. On it is a white sheet. " +
	"It is large enough for an elf to lie on. "));
    add_item( ({ "sheet", "white sheet" }),
	BSN("It is a white sheet. It covers the operating table completely."));
    add_item( ({ "chair", "special chair" }),
	BSN("It is a special chair and it is for Haldira to sit on during " +
	"long surgery.\n"));
    add_item( ({ "floor", "ground", "carpet" }),
	BSN("There is a thick carpet on the floor. It is black."));
    add_item( ({ "skeleton", "deer", "bambi" }),
	BSN("You might expect the skeleton of a man or elf here, but " +
	"Haldira has the skeleton of a deer. Her husband shot it some " +
	"years ago. It is from a young deer, probably only one year old " +
	"when it was killed. The skeleton is well preserved and complete."));
    add_item( ({ "shelf", "shelves" }),
	BSN("Some shelves are nailed to the wall. On the you see many " +
	"books."));
    add_item( ({ "book", "books" }),
	BSN("There are many books on the shelves. They look rather " +
	"interesting and must contain a lot of information."));
    add_item( ({ "title", "titles" }),
	BSN("They consist of many words."));
    add_item( ({ "door" }),
	BSN("The door is sturdy, made of oak. On this side you see some " +
	"cloth, probably to quell the sound patients might make."));
    add_item( ({ "wall", "walls" }),
	BSN("The walls are wainscotted with oak panels. Some shelves with " +
	"many books are nailed to a wall."));

    add_cmd_item( ({ "door" }), ({ "open", "close" }),
	BSN("There is no reason to handle the door."));
    add_cmd_item( ({ "doors", "closet", "closets" }), ({ "open" }),
	BSN("You do not dare open the closet. Medical tools and supplies " +
	"are in them and you do not want to mess with them."));
    add_cmd_item( ({ "book", "books" }), ({ "read" }),
	BSN("You do not dare touch the books. Without touching them you " +
	"can only read the titles."));
    add_cmd_item( ({ "title", "titles" }), ({ "read" }),
	BSN("You read some titles, \"the human skin\", \"skin recovery\", " +
	"..., \"elves and dwarves\", \"halflings\", \"anatomy\" ... and " +
	"\"fairy-tales by Fatoto\"."));
    add_cmd_item( ({ "label", "labels" }), ({ "read" }),
	BSN("The print on the labels is too fine to read."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_WIZINFO,
	BSN("This room is the room in which Haldira performs surgery by " +
	"appointment of the Lady Galadriel. The player will be knocked " +
	"uncounscious and cannot move a muscle during the operation. Since " +
	"players are not welcome in this room while surgery is being " +
	"performed, I have not wasted any memory and CPU on too nice " +
	"descriptions of the surgery to others, including sublocations " +
	"of the 'victim' being on the operating table. /Mercade!"));

    /* Command 'out' used by the surgeon. Don't change for no reason. */
    add_exit(WAITING_ROOM, "out");
}

/*
 * Function called from the surgeon to determine where she is.
 */
int
query_private()
{
    return 1;
}

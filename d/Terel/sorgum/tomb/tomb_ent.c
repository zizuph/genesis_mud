/*
 * Tomb entrance
 *
 *  Modified: 3 May 2003, by Bleys
 *      - fixed many typos
 *
 */

inherit "/std/room";
     
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include "tomb.h"

/*void
reset_room()
{
    object guard;

    if (!present("guard", TO)) {
        guard = clone_object(TOMBDIR + "guard");
        guard -> move(TO);
    }
}*/

void
create_room()
{
    object door, key;
    
    set_short("Tomb entrance");
    set_long(
        "You are standing outside of a massive vault which is excavated " +
	"into the hillside.  " +
        "The vault is made of ancient granite which has been weathered " +
        "and discolored by mists and the dampness of generations. The door is " +
	"a ponderous and forboding slab of stone which hangs upon rusty " +
	"iron hinges and is fastened ajar in a queerly sinister way by " +
        "means of heavy iron chains and a padlock.\n"
    );

    add_item(({"chain", "chains"}),
	"The chains are thick and they look rather heavy and very strong.\n"
    );
    
    add_item(({"hinge", "hinges"}),
	"Although the hinges are rusty they look very strong.\n"
    );

    add_item("vault",
       "It's hard to examine the vault more closely because most of it " +
       "is excavated back into the hillside.\n"
    );

    add_prop(ROOM_I_INSIDE, 0);

    door = clone_object(TOMBDIR + "tomb_door");
    door->move(TO);
    door->set_key(TOMB_DOOR_KEY);

    /*
     * Now the key is the cottage_cellar in the heap of decayed books.
     */
    
/*    key = clone_object(TOMBDIR + "tomb_key");
    key->move(TO);
    key->set_key(TOMB_DOOR_KEY); */
     
    add_exit(TOMBDIR + "clearing", "southeast", "@@go_briars");

/*    reset_room(); */
}

go_briars()
{
    write("You push your way past the briars and get pricked by the barbs.\n");
    say(QCTNAME(TP) + " scrapes through the briars.\n");
    TP->move_living("through briars", TOMBDIR + "clearing", 1);     
    return 1;
}     


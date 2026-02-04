/*
 * Tomb entrance
 *
 *  Modified: 3 May 2003, by Bleys
 *      - fixed many typos
 *
 */
// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit MOOR_DIR +"tomb/tomb_base";
#include "../local.h"

void
create_room()
{
    object door;
    
	::create_room();
		
    set_short("Tomb entrance");
    set_long(
        "You are standing outside of a massive vault which is excavated " +
        "into the north side of the hill. " +
        "The vault is made of ancient granite which has been weathered " +
        "and discolored by mists and the dampness of generations. "+
        "The door is a ponderous and forboding slab of stone " +
	    "which hangs upon rusty iron hinges and " +
	    "is fastened ajar in a queerly sinister way by " +
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
       "is excavated back into the depths of the hillside.\n"
    );

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 0);

    door = clone_object(TOMBDIR + "tomb_door");
    door->move(TO);
    door->set_key(TOMB_DOOR_KEY);
    // The key is the cottage_cellar in the heap of decayed books.
   
    add_exit("../forest/clearing", "southeast", "@@go_briars");
}

int
go_briars()
{
    write("You push your way past the briars and get pricked "+
        "by the barbs.\n");
    say(QCTNAME(TP) + " scrapes through the briars.\n");
    TP->move_living("through briars", "/d/Terel/common/moor/forest/clearing", 1);     
    return 1;
}     


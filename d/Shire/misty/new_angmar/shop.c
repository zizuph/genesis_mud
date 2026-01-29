/*
 * Shop in Angmar's army guild
 * Milan March 1994
 * modified from:
 *  Shop in Minas Morgul
 *  Olorin, July 1993
 *  copied from:
 *  Bendar's General Store in Edoras
 *  rewritten by Olorin                   may 1993
 *  - use /lib/shop  - copied from ranger guild shop
 *  modified by Olorin                   feb 1993
 *  after ideas by Hamurabbi
 *  after the Hobbiton drug store by
 *                               Tricky, dec 1991
 * Modified by Ibun to fit into Shire code.
 */

/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */


inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"


/*
 * This shop has 3 storerooms ;)
 */


/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
void
create_room()
{

    add_prop(ROOM_I_INSIDE,1); 
    set_short("Army shop");
/*
    set_long("This was the place where Angmar's warriors use to sell " +
        "everything they had stolen from the unfortunate travelers or " +
        "the villagers they killed in their last ride. They usually " +
        "immediately spent all the money in the pub. The storeroom " +
        "is behind a massive door to the east. \n");
*/
    set_long("This was once the shop of the Army. Soldiers use to " +
        "sell their loot here and then in turn spend it on food and " +
        "drink in the pub. The shopkeeper would in turn sell the items "+
        "for an exorbitant price to anyone who wanted to buy it. Broken " +
        "shelves line the walls where the wares were displayed. A " +
        "large counter that once ran the width of the room is broken " +
        "and splintered. It lies buried under the rubble from the " +
        "walls blasted out.\n");
    
    add_item("storeroom","You can see only closed door.\n");
    add_item("door","They are very massive and able to keep anyone away "+
                  "from the storeroom.\n");

//    add_exit(NEW_ANGMAR + "store_sc", "east");
    add_exit(NEW_ANGMAR + "c1", "west");
}

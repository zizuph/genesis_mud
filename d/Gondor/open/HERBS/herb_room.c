/*
 * /d/Gondor/open/HERBS/herb_room
 *
 * An example room to show how to use the herbsearch.c file
 *
 * Olorin, May 1995
 */
inherit "/d/Gondor/common/room";		// the standard Gondor room
inherit "/d/Gondor/open/HERBS/herbsearch";	// herb search routines

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"			// standard Gondor include file
#include "/d/Gondor/lebennin/road/road.h"	// area definitions

void
create_room()
{
    set_short("a bushy field in the northeast parts of Lebennin in Gondor");
    set_long(BSN(CAP(query_short())+". Through the bushes growing here, "
      + "the main road is visible to the north and beyond it, the Rammas "
      + "Echor and the Ered Nimrais. Directly to the south, a large "
      + "mound is rising."));

    add_exit(LEB_DIR + "road/nr4","north",0,1);

    add_item(({"mountains","ered nimrais","white mountains"}), BSN(
        "These are the famed White Mountains of Gondor. Minas Tirith is built "
      + "on the side of the easternmost peak, the Mindolluin."));
    add_item(({"rammas echor","wall","rammas"}), BSN(
        "This large wall surrounding the Pelennor fields of Minas Tirith can "
      + "be seen from far off."));
    add_item("mound", BSN("This large mound fills your view to the south. "
      + "You think it is quite old."));
    add_item(({"bush","bushes"}), "These bushes are crawling with insects.\n");
    add_item(({"grass"}),
        "The grass is as green as you have ever seen green.");
 
//  this function is defined in herbsearch.c:
/*
 * Function name: set_up_herbs
 * Description:   Add herbs to the room
 * Arguments:     hfiles: Array of filenames of the herbs 
 *                places: Array of names of items (added with add_item)
 *                        that can be searched to find herbs
 *                time:   Argument for OBJ_I_SEARCH_TIME
 *                        delay used in the search function
 */
    set_up_herbs(({HERB_DIR + "ginger",
                   HERB_DIR + "athelas",
                   HERB_DIR + "caraway"}),
                   ({"bushes","bush","plain","plains","ground","grass"}),
                   3);

// herbsearch.c defines reset_room.c:
/*
 * public void
 * reset_room()
 * {
 *     this_object()->set_searched(0);
 * }
 */
// This is necessary to grow new herbs in the room in a reset.

    reset_room();
}


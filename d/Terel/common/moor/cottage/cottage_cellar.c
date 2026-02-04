// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include "../local.h"

void
create_room()
{
    set_short("cottage cellar");
    set_long("This is the cellar of the cottage. It was once a very "+
        "comfortable place, a quiet spot for someone to do a bit of "+
        "reading by the light of a fire during long winter nights. "+
        "Decay now spreads over this must-reeking room with its wormy " +
        "panelling, sagging floor, battered mantel and rickety furniture.  " +
        "Ceiling-high shelves of rotting volumes are on the far wall.\n"
    );

    add_item(({"volumes", "volume", "books", "book", "scroll", "scrolls"}), 
	"The books and scrolls were stacked with care, but suffer " +
	"from decades of disgusting decay.\n");

    add_item(({"panelling", "wormy panelling", "pine panelling"}),
    "Once-lovely pine panelling is now covered in toxic mold and "+
    "riddled with holes from beetles, worms, and termites.\n");

    add_item(({"floor", "sagging floor", "pine boards", "boards"}),
    "The floor is made of pine boards that are rotting.\n");	
	
    add_item(({"mantel", "battered mantel", "stone mantel"}),
    "It is a long rectangular piece of stone with many chips and "+
    "cracks in it. It rests above a cold grate.\n");

    add_item(({"grate", "fireplace"}),
    "The grate is cold and full of ashes. It has been decades since "+
    "anything burned in this fireplace.\n");
   
	add_item(({"furniture", "rickety furniture", "armchair", "table"}),
    "There is a moldy old armchair that looks ready to fall apart, "+
    "and a rotted table fallen beside it\n");    

    add_item(({"bookshelves", "bookshelf"}),
    "The bookshelves are ceiling-height. They look like they are "+
    "going to collapse at the slightest touch.\n");
	
	add_item("hole", "A small hole in the floor created by something "+
	"that burned VERY hot.\n");
	
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_exit("cottage_stairs", "up", 0);

    add_object("/d/Terel/common/moor/tomb/tomb_key", 1, &->set_key(TOMB_DOOR_KEY));
    add_object(OBJDIR + "book_heap", 1);
    add_object(OBJDIR + "safe", 1);
	
	enable_reset(35);  // every 4.5 hours or so.
}


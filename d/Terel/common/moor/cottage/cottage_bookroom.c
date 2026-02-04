// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

void
create_room()
{
    set_short("cottage bookroom");
    set_long(
    "You have entered a small study in the cottage. " +
	"This room is filled with ceiling-high bookshelves stocked " +
    "with dusty books and decaying scrolls. Above the doorway " +
    "is a delightful pediment " +
    "magnificently carved in an ornamental fashion with a scroll " +
    "and urn top.  Above the crowded bookshelves at intervals " +
	"are portraits.\n"	
    );

    add_prop(ROOM_I_INSIDE, 1);

    add_item(({"bookshelves", "bookshelf"}),
    "The bookshelves are ceiling-height. They look like they are "+
    "beginning to deteriorate.\n");
    add_item(({"books", "book", "scroll", "scrolls"}), 
	"The books and scrolls were stacked with care, but suffer " +
	"from abandonment or neglect.\n");

    add_item(({"pediment", "urn", "doorway"}),
    "Triangular in shape, the pediment rests above the doorway "+
    "leading east. It is magnificently carved with a scroll and "+
    "urn.\n");

    add_item(({"portrait", "portraits"}),
    "A thick layer of dust and grime has made these portraits "+
    "unrecognizable. They are of humanoids and that is all you "+
    "can tell by looking at them.\n");
	
    add_exit("cottage_in", "east", 0);
    add_exit("cottage_stairs", "down", 0);    
}

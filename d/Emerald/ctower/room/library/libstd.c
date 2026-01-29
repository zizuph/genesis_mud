inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../../ctower.h"
#include <stdproperties.h>
 
public void
create_lib()
{
}
 
public nomask void
create_ctower_room()
{
    set_short("Library");
   
    set_long("This room along with the two adjacent "+
	"rooms are part of a huge library.  Bookshelves line the walls "+
	"with thousands of books.  There appears to be magic at work "+
	"here though.  When you try to look at certain books your vision "+
	"starts to blur and you find your gaze directed towards the "+
	"books that you can read, an effective means of keeping "+
	"dangerous knowledge out of the wrong hands.\n");
   
    add_item(({"floor", "ceiling"}), "The floor and ceiling "+
	"are made of black and white marbled crystal.\n");

    create_lib();
}

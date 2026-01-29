#include "/d/City/defs.h"
inherit "/std/room.c";
#define PATH "/d/City/chaos/library/"
#include <stdproperties.h>
#include <macros.h>
#include <std.h>

void
create_room()
{
   ::create_room();
   set_short("The Back Room");
   set_long("A slight hint of cigar and pipe smoke mixes with the smell "+
      "of the fine leather that binds the many books in this room. "+
      "Shelves line every side with only the doorway leading south "+ 
"disrupting the conformity of the place.  Stacked neatly "+
"on every shelf are the books, bound in differing colors of "+
"leather.  The air shimmers as powerful magicks eternally protect the "+
"valued assests of the library.  There are several large comfortable looking "+
"chairs scattered about the well lit room and in the center "+
"is a small coffee table, with a cigar box sitting on it. "+
 
      "It looks as if this is a good place to just sit back, relax and "+ 
      "ponder the meaning of life with friends.\n");
   add_item("shelves","The shelves are filled with books written by "+
      "men with strange names.  Names like Nietzsche, Plato, Socrates, "+
"Camus, Kierkegaard, and Heidegger.  All the books are tightly "+
      "stacked together, though one book seems to be missing.\n");
   add_item("chairs","The chairs look very soft and comfortable.\n");
   add_prop(ROOM_I_LIGHT,1);
   add_item("box","This cigar box looks to be carved of ebony.  It has "+
   "two gold hinges by which it opens and a small gold catch holding it "+
   "closed.\n");
   add_prop(ROOM_I_INSIDE,1);
   add_item("books","There are so many of them, you don't know where "+
   "to start!\n");
   add_item("table","The table looks as if it were carved from a single "+
   "piece of redwood.  There are intricate designs all over it that must "+
   "have something to do with the powerful magicks in this room.\n");
   add_exit(PATH + "library","south");

}

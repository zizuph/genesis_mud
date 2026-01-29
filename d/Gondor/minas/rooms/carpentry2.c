inherit "/d/Gondor/minas/houses/citizens/house";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

//#define DOOR_ID	"MT_carpenter_n3crc1"

void
create_room()
{
    add_exit(MINAS_DIR+"rooms/carpentry","north",0,0);

    set_short("carpenter's living room");
     set_long(BSN("This is a fine living room. Furniture is placed "
      + "around the room. An exit is leading north into a workroom."));

    add_item(({"furniture", "furnitures", }), BSN(
        "You see chairs and a table in the room along with a chest "
      + "of drawers."));
    add_item("chairs","The chairs are very well made; they look like the "+ 
             "work of an craftsman.\n");
    add_item("table","This table is extremely well done; it simply must "+
             "be a very competent craftman's work.\n");
    add_item("chest of drawers","The wood of the chest of drawers is well "+
             "planed and seems to have been handled with extreme care.\n");


}



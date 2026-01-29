/*     Created by:      Sarr
 *     purpose:		
 *     Location:         
 *     Modified:        Toby, 97-09-18 (fixed a typo in the sign)
 */

#include "defs.h"
inherit STD_ROOM;
inherit LIB_DIR + "smith";

#define NUM sizeof(MONEY_TYPES)

object smith;
void reset_room();


void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
    set_short("The Smith of Drakmere");
    set_long("You are within a smokey, hot room. In the corner a "+
    "large furnace burns. All along the walls you see old, new "+
    "and broken armours and weapons.  A large anvil sits in the "+
    "center of the room. This is the smithy house of Drakmere. A "+
    "small, dusty sign hangs from the wall.\n");
    add_item("anvil","A large, iron anvil, where the smith hammers "+
    "and shapes his creations.\n");
    add_item("walls","Armours and weapons hang from them.\n");
    add_item("furnace","It burns with great intensity, making you "+
    "sweat.\n");
    config_default_trade();
    add_cmd_item("sign","read","@@sign");
    add_item("sign","It has readable words on it.\n");
    add_exit(DRAKMERE_DIR + "road07","northeast",0);
    reset_room();
}

void
reset_room()
{
    if(!smith)
    {
        smith = clone_object(DRAKMERE_NPC_DIR + "smithy");
        smith->move_living("xxx",TO);
        set_smith(smith);
    }
}

string
sign()
{
    return read_file(DRAKMERE_TEXT_DIR + "smith_sign.txt");
}

void
init()
{
   ::init();
   init_smith();
}


int *
query_coordinates()
{
    return ({65, 0, 0});
}

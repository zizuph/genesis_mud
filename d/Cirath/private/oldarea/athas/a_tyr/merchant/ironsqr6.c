/* ironsqr6: Southwest corner of Iron Square: Serpine, 7/27/95. */
 
inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/std/block.h"
 
void
create_room()
{
    set_short("southwest of iron square");
    set_long("Relatively poor in relation to the sections of "+
             "Tyr's Iron Square lying north and east, this corner "+
             "formerly was shelter to many of the minor trading houses "+
             "of the city. Unfortunately most of them were forced to "+
             "shut down by the plague that still ravages other sections "+
             "of Athas. Now only the emblem of House Ianto, hanging "+
             "over a meager entrance to the south, graces this area.\n");
 
    add_item(({"emblem", "entrance"}), "Upon a yellow field runs a "+
             "green Inix; Such is the symbol of House Ianto.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TZ_MERCHANT+"ironsqr4.c", "north", "@@block_exit@@", 1);
    add_exit(TZ_MERCHANT+"ironsqr7.c", "east", 0, 1);
    add_exit(TZ_MERCHANT+"housiant.c", "south", "@@house_block", 1);
 
}

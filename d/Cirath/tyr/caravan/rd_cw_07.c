/* rd_cw_07: Caravan Way section 7. */

inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";

void
create_room()
{
    ::create_room();
    set_short("east caravan way");
    set_long("The eastern end of Caravan Way is strangely calmer then "+
             "the rest of the road, though the crowd is even thicker. "+
             "While many have business in Iron Square to the east, they "+
             "approach the powerful merchant houses there with a caution "+
             "bordering on fear: The towering mass of the Ziggurat "+
             "just beyond does nothing to calm them. Some instead turn "+
             "towards a long, narrow brick building in an alley to the "+
             "north, passing under a wooden sign. "
            +"Others head south, approaching the sounds of animals "
            +"and men hard at work.\n");
             
    clone_object("/d/Genesis/obj/donation/column")->move(this_object(),1);
    add_item("crowd", "Most of those who approach Iron Square seem to "+
             "be traders or nobles and their guards. All sorts head west "+
             "and to the north.\n");
    add_item(({"sign", "wooden sign", "building"}), "The cracked sign has "+
             "upon it the image of a golden inix clutching a bottle.\n");

    OUTSIDE
    ADD_SUN_ITEM;
    ADD_ZIG_ITEM;

    add_exit(TYR_CARAVAN+"innlobby.c", "north", 0, 1);
    add_exit(TYR_MERCHANT+"ironsqr1.c", "east", 0, 1);
    add_exit("/d/Cirath/ships/kalad/tyr_port.c","south",0,1);
    add_exit(TYR_CARAVAN+"rd_cw_05.c", "west", 0, 1);
}

/* rd_tr_04: east end of Templar Road, Serpine-2/13/96. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";
        
void
create_room()
{
    ::create_room();
    set_short("east end of Templar Road");
    set_long("While heavily used by caravans, Templar Road still is "
            +"infected with a feeling of oppression and darkness. "
            +"Likely this is brought on by the barely audible moans "
            +"coming from the slave pits off to the west and over the "
            +"fence along the nearby brickyards. It could also be "
        +"brought on by the looming form of the Ziggurat.\n");
 
    add_item("fence", "Formed of razor sharp brambles as high as a "
            +"half-giant's head, it well serves the purpose of keeping "
            +"the slaves to the south from coming this way.\n");
    add_item(({"brickyards", "brickyard"}),
             "Your view of the brickyards is blocked by the fence.\n");
    add_item(({"caravan", "caravans"}), "Both Dune Traders and "
            +"visitors to Tyr head west to the Iron Square or east out "
            +"of the city. They don't seem eager to linger here.\n");
    add_cmd_item(({"moan", "moans", "to moans", "to moan"}), "listen",
             "The slaves project an aura of hopelessness.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TYR_SLAVE+"rd_sw_05.c", "east", 0, 1);
    add_exit(TYR_SLAVE+"rd_tr_03.c", "west", 0, 1);
}

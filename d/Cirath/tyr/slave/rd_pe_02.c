/* rd_pe_02: Middle section of Pandora's End. */
 
inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";

void
create_room()
{
        ::create_room();
    set_short("pandora's End middle");
    set_long("Winding past an ebony statue and between once oppulent but "
            +"now forgotten buildings, Pandora's End was once called "
            +"Palace Road. It earned a new name and a dark reputation "
            +"when its most important resident, High Templar Pandora, "
            +"betrayed King Kalak and was put to death. Now it only "
            +"serves as the route to the new jail of Tyr: the traitor's "
            +"former home.\n");
 
    add_item(({"buildings", "building"}), "They are dark and empty. "
            +"Apparently few wished to be associated with this road.\n");
    add_item(({"statue", "ebony statue"}), "In a chaotic mess of "
            +"imagery, the statue shows Pandora betraying her position "
            +"as High Templar: Learning sorcery, distributing dangerous "
            +"scrolls, consorting with gnomes, and even hoarding "
             +"magically acquired water. Two similar statues can be seen "
            +"gleaming in the sun to the north and south.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TYR_SLAVE+"rd_pe_03.c", "north", 0, 1);
    add_exit(TYR_SLAVE+"rd_pe_01.c", "south", 0, 1);
}

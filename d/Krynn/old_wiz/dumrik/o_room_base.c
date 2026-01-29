/* Coded 1995-05-04 01:07  by Dumrik 
*/

/*
 * This is a standard room_base file for outdoor rooms.
 * All XXX (there is four of them) should be replace with a proper name,
 * if you are doing a area like Pax Tharkas a proper name would be pax.
 * The create_XXX_room() and reset_XXX_room() should be replaced in your
 * own code.
 */
#include "/d/Krynn/common/defs.h"

inherit	OR_FILE

public void
create_outside_dragon_quest_room()
{
}

public void
reset_outside_dragon_quest_room()
{
    enable_reset(0);
}

nomask public void
create_krynn_room()
{
    create_outside_dragon_quest_room();
}

nomask public void
reset_krynn_room()
{
    reset_outside_dragon_quest_room();
}








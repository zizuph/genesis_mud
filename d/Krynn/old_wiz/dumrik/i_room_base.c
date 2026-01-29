/* Coded 1995-05-04 00.58   by Dumrik */

/*
 * This is a standard room_base file for indoor rooms.
 * All XXX (there is four of them) should be replace with a proper name,
 * if you are doing a area like Pax Tharkas a proper name would be pax.
 * The create_XXX_room() and reset_XXX_room() should be replaced in your
 * own code.
 */
#include "/d/Krynn/common/defs.h"

inherit	R_FILE

public void
create_inside_dragon_quest_room()
{
}

public void
reset_inside_dragon_quest_room()
{
    enable_reset(0);
}

nomask public void
create_krynn_room()
{
    create_inside_dragon_quest_room();
    INSIDE;
}

nomask public void
reset_krynn_room()
{
    reset_inside_dragon_quest_room();
}








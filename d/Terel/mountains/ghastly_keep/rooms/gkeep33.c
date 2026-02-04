/* /d/Terel/mountains/ghastly_keep/rooms/gkeep33.c
 *
 * The treasure room of the dragon.
 *
 * Znagsnuf
 *
 * - Language tweak complete (Gorboth)
 *
 */

#include "defs.h";

inherit GKEEP_STD_ROOM;

object chest;
int is_chest = 0;

/*
 * Function name: create_gkeep_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_gkeep_room()
{
    update_longdesc();

    set_short("Inside the treasure chamber");
    set_long("This is an ordinary room. The walls, ceiling and "
           + "floor seems naked. @@check_chest@@\n");

    add_item( ({ "wall", "floor", "ceiling" }), "There is nothing about "
               + "this room that catches your eye. Seems quite ordinary.\n");

    add_exit(GKEEP + "gkeep32",       "northeast");

    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}

string
check_chest()
{
     if (is_chest) 
          return "There is only one thing that catches "
                + "your eye - a huge treasure chest in the middle "
                + "of the room.";
     else  
          return "";
}

int
set_chest(int i)
{
    is_chest = i;
}

int
query_chest(int i)
{
    return is_chest;
}

/*
 * Function name: reset_room()
 * Description  : Resets the room
 */
void
reset_room()
{
    update_longdesc();
}

/*
 * Function name: add_treasure()
 * Description  : Resets the room
 */
void
add_treasure()
{
    if(!chest)
    {
      chest = clone_object(GKEEP_OBJ + "g_treasure_chest");
      chest->move(TO);
      is_chest = 1;
    }
}
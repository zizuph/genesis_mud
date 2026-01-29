/* /d/??/??/instances_endroom.c
 *
 * Treasureroom. Last room in the instance.
 *
 * Nerull, 15.04-15
 *
 */

inherit "std/room";
#include "dungeon_defs.h";
#include <stdproperties.h>

object tomb_chest;
object boss;

int firstspawn;


/*
 * Function name: block_player
 * Description  : If a monster is present, it will block the desired exit.
 */
public int
block_player()
{
    if (present("_tomb_monster_"))
    {
        write("Something or someone blocks you from travelling "
        +"in that direction!\n");

        return 1;
    }

    return 0;
}


/*
 * Function name: create_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_room()
{
    setuid();
    seteuid(getuid());

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_I_LIGHT, 0);

    add_npc(DUNGEON_DIR +"npc/giant_spider", TOMB_SPAWN_NUMBER + 4);
    
    firstspawn = 1;

    reset_room();
}


/*
 * Function name: reset_room
 * Description  : Resets the room/states/npc spawns.
 */
void
reset_room()
{
    if (!tomb_chest)
    {
        if ((random(10) >= 5) || (firstspawn == 1))
        {
            if (!boss)
            {
                boss = clone_object(DUNGEON_DIR + "npc/iron_golem.c");
                boss->move(this_object(), 1);
            }
            
            tomb_chest = clone_object(DUNGEON_DIR + "obj/tomb_chest.c");
            tomb_chest->move(this_object(), 1);
            
            firstspawn = 0;
        }
    }
}


/* /d/Raumdor/common/beach/bountiful/bounty_cabin.c
 *
 * Room at the ship Bountiful, Damon Skraggs hangout.
 *
 * Nerull, 2021.
 *
 */

#include <stdproperties.h>
#include "defs.h";
inherit "std/room";

int counter = 1;

void spawn_dungeon();

object deck = find_object(BEACH_DIR + "bountiful/bounty_deck");
object gangway = find_object(BEACH_DIR + "bountiful/bounty_gangway");


/*
* Function name: spawn_dungeon()
* Description  : Spawns the entire dungeon.
*/
void
spawn_dungeon()
{
    object *plays;
    object *plays2;
    object *plays3;

    plays = FILTER_PLAYERS(all_inventory(this_object()));

    plays2 = FILTER_PLAYERS(all_inventory(deck));

    plays3 = FILTER_PLAYERS(all_inventory(gangway));


    // We'll not clone any npcs if players are on the boat, camping.
    if (sizeof(plays) == 0 && sizeof(plays2) == 0 &&
    sizeof(plays3) == 0)
    {
        if (!present("_damon_skragg", this_object()))
        {
            // Cloning the boss, Damon Skragg, and populating the ship.
            clone_object(BEACH_DIR + "bountiful/npc/damon_skragg")->move(this_object(), 1);
            clone_object(BEACH_DIR + "bountiful/npc/bount_ghast1")->move(deck, 1);
            clone_object(BEACH_DIR + "bountiful/npc/bount_ghast2")->move(deck, 1);
            clone_object(BEACH_DIR + "bountiful/npc/bount_ghast3")->move(deck, 1);
            clone_object(BEACH_DIR + "bountiful/npc/bount_ghast4")->move(deck, 1);
            clone_object(BEACH_DIR + "bountiful/npc/bount_ghast5")->move(deck, 1);
            clone_object(BEACH_DIR + "bountiful/npc/bount_gangway_ghast")->move(gangway, 1);
        }

        counter = 0;
    }
}


/*
 * Function name: create_mar_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_room()
{
    ::create_room();
    
    seteuid(getuid());
    set_short("The spacious cabin of the Bountiful");

    set_long("The spacious cabin of the Bountiful is loaded with "
    +"various types of cargo crates, barrels, and other stocks that the "
    +"ship might carry for it's crew. Oddly, all of the stocks are old, "
    +"rotted, and disgusting. The stench in the cabin is almost unbearable "
    +"and the mildewed wood and rotting planks make walking "
    +"treacherous. There is a narrow crack in the wooden floor. The wind "
    +"from the sea gusts outside the "
    +"portholes and the boat rocks "
    +"heavily in the waves of the sea.\n");

    add_item( ({"crates", "cargo", "cargo crates","crate","stocks"}),
    "Rotted crates at different stages of "
    +"disarray lie in this open space. At one time likely carrying "
    +"grain, coffee, jerky, and other food stuffs, it now lies rotted "
    +"and unrecognisable.\n");
    
    add_item( ({"barrels", "barrel"}), "Holding water, rations, and "
    +"gunpowder, most of these barrels have seen better days. The "
    +"water looks more like a swamp than potable water, the rations "
    +"of fish are rotted and disgusting. The only item that is "
    +"fresh and intact are the barrels of gunpowder.\n");
    
    add_item( ({"structure", "wood", "walls", "ceiling"}), "The "
    +"wood making up the structure of this cabin is starting to "
    +"rot from the moisture of sea travel. Whomever makes up the "
    +"crew of this ship apparently does not care about it's "
    +"maintenance. Surprisingly, everything is still very sturdy as "
    +"if held together by an unnatural force.\n");
    
    add_item( ({"planks", "floor", "wooden planks", "plank"}), "rotting "
    +"planks make up the floor of this cabin. While they seem as "
    +"though they should have collapsed long ago, they are incredibly "
    +"sturdy as if some unnatural entity or force maintains their "
    +"strength.\n");
    
    add_item( ({"portholes", "porthole"}), "There are closed portholes "
    +"on the west side of the ship and on the eastern side.\n");
    
    remove_item("carvings");
    remove_item("blocks");
    remove_item("stone blocks");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_TELEPORT_FROM, 1);

    add_exit(BEACH_DIR + "bountiful/bounty_deck",   "out");

    spawn_dungeon();

    reset_room();
}


/*
 * Function name: reset_room()
 * Description  : Resets the room.
 */
void
reset_room()
{

    if (counter > 3)
    {
        spawn_dungeon();

        counter = 0;
        
        return;
    }

    counter = counter + 1;
}



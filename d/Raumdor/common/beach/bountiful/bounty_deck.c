/* /d/Raumdor/common/beach/bountiful/bounty_deck.c
 *
 * Room at the ship Bountiful.
 *
 * Nerull, 2021.
 *
 */

#include <stdproperties.h>
#include "defs.h";
inherit BEACH_ROOM;


/*
 * Function name: block_player
 * Description  : If a crew member is present, blocks entrance.
 */
public int
block_player()
{
    if (present("_deck_ghast"))
    {
        write("A crewman blocks you from entering "
        + "the cabin of the Bountiful!\n");

        return 1;
    }

    return 0;
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
        
    set_short("At the deck of the Bountiful");
    
    set_long("Standing out in the open air of the deck on the "
    +"ship the Bountiful, you can see the beach to "
    +"one side and the "
    +"open sea to the other. This frigate has "
    +"three masts with massive sails. Open deck has some of "
    +"the larger "
    +"cannons and cannon balls strapped in place and ready "
    +"for use. At one end of the deck lies the rudder and steering wheel "
    +"while at the "
    +"the other lies the bow of the ship with it's ghastly skeletal "
    +"figurehead.\n");

    add_item( ({"cannons", "cannon", "iron cannon", "iron cannons"}),
    "Cannons placed on heavy metal tracks that "
    +"allows for them to be pushed forward for use and pulled back for "
    +"loading. The cast iron design makes them incredibly heavy and it "
    +"would take a team of many to move them.\n");
       
    add_item( ({"tracks", "cannon tracks", "track", "cannon track"}),
    "Well-built iron tracks are set into the floor to "
    +"allow for the movement of the cannons both forwards and backwards.\n");
    
    add_item( ({"cannon balls", "balls", "ball", "cannon ball",
    "iron ball", "iron balls"}), "Large iron cannon balls designed to be "
    +"fired from the cannons are piled like a pyramid of death and "
    +"destruction. "
    +"Heavy canvas straps are connected to iron rings in the floor and "
    +"criss-crossed over the cannon balls to hold them in place.\n");
    
    add_item( ({"straps", "canvas straps", "strap", "canvas strap",
    "heavy canvas straps", "heavy canvas strap",
    "heavy strap", "heavy straps"}), "Heavy canvas straps are "
    +"connected to iron rings in the floor and criss-crossed over the "
    +"cannon balls to hold them in place.\n");
    
    add_item( ({"figurehead", "ghastly figurehead",
    "skeletal figurehead"}), "Carved entirely out of wood in immaculate "
    +"detail is a skeleton. His head is clean "
    +"and skeletal with huge vacant eyes as black "
    +"as the depths of the sea. His mouth is stuck in an eternal grin "
    +"daring the ocean to take him. In one hand he holds a "
    +"scythe indicating death and despair "
    +"while in the other he holds a heart representing what has been "
    +"lost and the eternity of this crews voyage\n");
    
    add_item( ({"heart", "held heart", "figurehead heart"}), "A heart, "
    +"not the anatomical heart but a typical heart, is held out in "
    +"the skeletal hand towards the sea in defiance.\n");
    
    add_item( ({"scythe", "figurehead scythe"}), "Curved blade "
    +"resting atop a long shaft used to cut wheat, or in some cases, "
    +"sever heads from torsos.\n");
    
    add_item( ({"mizzen-masts", "mizzen-mast",
    "mizzenmasts", "mizzenmast", "mast", "masts"}), "Three tall "
    +"mizzen-masts sprout from the ships deck towards the heavens. "
    +"Made of solid wood they have seen better days. Still they "
    +"seem unnaturally sturdy.\n");
    
    add_item( ({"sails", "sail", "black sails", "black sail"}), "Rolled "
    +"up sheets of black sails lie at the top of the mizzen-masts ready "
    +"to be unfurled at a moments notice to catch the wind and thrust "
    +"the ship into motion.\n");
    
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_TELEPORT_FROM, 1);
    
    remove_item("carvings");
    remove_item("blocks");
    remove_item("stone blocks");
    
    add_exit(BEACH_DIR + "bountiful/bounty_cabin",   "cabin", block_player);
    add_exit(BEACH_DIR + "bountiful/bounty_gangway",   "down");

    reset_room();
}


/*
 * Function name: reset_room()
 * Description  : Resets the room.
 */
void
reset_room()
{
}


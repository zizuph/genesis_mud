/* /d/Faerun/guilds/fire_knives/rooms/c3.c
 *
 * Connecting passageway for the cellar
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;


public int
block_check()
{
    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 0)
    {
        if (!this_player()->query_wiz_level())
        {
            write("The guard dogs slowly pace until "
            +"they stand in front of you "
            +"while growling softly, their eyes focused on yours. You decide "
            +"to reconsider your option and take a few steps backwards.\n");

            tell_room(environment(this_player()), QCTNAME(this_player()) 
            +" steps backwards from the dogs as they move in front of "
            + this_player()->query_possessive()
            +", blocking the way.\n", this_player());

            return 1;
        }
    }
      
    write("The guard dogs raise their heads to look at you, then look down "
    +"and turn around in a submissive gesture.\n");
    
    tell_room(environment(this_player()), QCTNAME(this_player())
    +" receives a furtive glance from the dogs before they lower "
    +"their head and turn around in a submissive gesture.\n", this_player());
        
    return 0;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);

    set_short("Along a cold, dank cellar");
    
    set_long("Dripping sounds of something heavier "
    +"than water reverberate across "
    +"the darkness encompassing the cell-like "
    +"passages in this cellar. Its echoes "
    +"bouncing off the clammy walls which close "
    +"in around you as if in a tunnel. "
    +"An acrid smell drifts in from the east "
    +"where a sharp turn opens up into a "
    +"rectangular room past an archway. The "
    +"darkness appears to begin dissipating "
    +"to the northwest where the route leads. A "
    +"pair of vicious guard dogs is pacing "
    +"about, guarding the entrance to the east.\n");
    
    add_item(({"tunnel", "tunnels", "cellar"}),
    "The tunnel extends to the northwest and back "
    +"to the southeast from here "
    +"ranging from dark to darker. To the east, "
    +"a sharp turn opens up into a "
    +"rectangular room past an archway.\n");
    
    add_item(({"dog", "dogs", "guard dog", "guard dogs", 
    "vicious guard dogs", "vicious dogs"}),
    "These pair of vicious wolf-like grey dogs paces about the "
    +"area, sniffing and carefully watching the movements "
    +"of any nearby creature. They appear to be guarding "
    +"the entrance to the east.\n");
    
    add_item(({"smell"}),
    "The smell is acrid, permeating all the area.\n");
   
    add_item(({"archway"}),
    "The archway covers the passage to the east "
    +"from here, as if it opened "
    +"into a new dimension of cleanliness and "
    +"comfort. At the top of it, in "
    +"the very center, is a symbol of a dagger wrathed in flames.\n");

    add_item(({"walls", "wall"}),
    "The walls emanate a coldness which has turned the little air transiting "
    +"through this tunnel into moisture due to the "
    +"lack of ventilation. Green "
    +"patches of moss are scattered around them.\n");

    add_item(({"moss"}),
    "Patches of moss have grown from small fissures in the walls.\n");

    add_item(({"fissures","fissure","crack","cracks"}),
    "Although firm and stable, the passing of time has left its mark on "
    +"the walls of this tunnel. They are far and "
    +"between, yet still present.\n");

    add_item(({"floor", "ground"}),
    "The floor of the tunnel is well-worn in and "
    +"seems to be frequented rather "
    +"than isolated from life. The patches of "
    +"moss, dirt, and pebbles bear the "
    +"form of what appear to be footsteps.\n");

    add_item(({"footstep","footsteps","dirt","pebble","pebbles"}),
    "Found on the ground and marked caked in the "
    +"dirt and moss are what appear to be "
    +"footsteps leading to the east and northwest.\n");

    add_item(({"darkness"}),
    "The darkness is all around you, swallowing the "
    +"surroundings within it, through "
    +"it seems to start to dissipate towards the northwest.\n");

    add_item(({"moisture"}),
    "The moisture accumulates from the cold emanating "
    +"from the walls and the poor "
    +"ventilation in the tunnels. Small puddles of "
    +"water are found in corners of the "
    +"passage.\n");

    add_item(({"puddle","puddles"}),
    "The puddles are formed from the condensed moisture "
    +"running down the walls.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "c2.c", "northwest");
    add_exit(FIREKNIVES_ROOMS_DIR + "g0.c", "southeast");
    add_exit(FIREKNIVES_ROOMS_DIR + "sh.c", "east", block_check);

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}

/* /d/Faerun/guilds/fire_knives/rooms/c2.c
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

    set_short("Near the stone stairway");    
    
    set_long("The darkness to the southwest recedes "
    +"against the light emanating from "
    +"above the stone stairway to the northwest. "
    +"The passage seems to descend slightly "
    +"to the southwest, as evidenced by the slow "
    +"trickle of condensed moisture "
    +"traveling in that direction. Almost imperceptible, "
    +"the base of the steps rise "
    +"from the cold, thick stone in the distance "
    +"opposite the engulfing darkness "
    +"in what seems to be a tunnel through the "
    +"cellar. A pair of vicious guard dogs is pacing "
    +"about, guarding the entrance to the east.\n");

    add_item(({"tunnel", "tunnels", "cellar"}),
    "The tunnel extends to the northwest, reaching "
    +"the base of a stone stairway "
    +"and back to the southeast from here into "
    +"the darkness deep within them.\n");
    
    add_item(({"dog", "dogs", "guard dog", "guard dogs", 
    "vicious guard dogs", "vicious dogs"}),
    "These pair of vicious wolf-like grey dogs paces about the "
    +"area, sniffing and carefully watching the movements "
    +"of any nearby creature. They appear to be guarding "
    +"the entrance to the east.\n");

    add_item(({"walls", "wall"}),
    "The walls emanate a coldness which has turned "
    +"the little air transiting "
    +"through this tunnel into moisture due to the "
    +"lack of ventilation. Green "
    +"patches of moss are scattered around them.\n");

    add_item(({"moss"}),
    "Patches of moss have grown from small fissures "
    +"in the walls.\n");
    
    add_item(({"smell"}),
    "The smell is acrid, permeating all the area.\n");

    add_item(({"fissures","fissure","crack","cracks"}),
    "Although firm and stable, the passing of time has left its mark on "
    +"the walls of this tunnel. They are far and "
    +"between, yet still present.\n");

    add_item(({"floor", "ground"}),
    "The floor of the tunnel is well-worn in and seems "
    +"to be frequented rather "
    +"than isolated from life. The patches of "
    +"moss, dirt, and pebbles bear the "
    +"form of what appear to be footsteps.\n");

    add_item(({"footstep","footsteps","dirt","pebble","pebbles"}),
    "Found on the ground and marked caked in the "
    +"dirt and moss are what appear to be "
    +"footsteps leading to the southeast and northwest.\n");

    add_item(({"darkness"}),
    "The darkness is all around you, swallowing "
    +"the surroundings to the southeast "
    +"whilst being held back by the light emenating "
    +"from the top of the stony "
    +"stairway to the northwest.\n");

    add_item(({"moisture"}),
    "The moisture accumulates from the cold emanating "
    +"from the walls and the poor "
    +"ventilation in the tunnels. Small puddles "
    +"of water are found in corners of the "
    +"passage, slightly streaming southeastwards.\n");

    add_item(({"puddle","puddles"}),
    "The puddles are formed from the condensed "
    +"moisture running down the walls.\n");

    add_item(({"steps","stairway","base"}),
    "To the northwest at the end of the tunnel the "
    +"base of a stone stairway "
    +"becomes visible. From above it, light trickles "
    +"downwards illuminating "
    +"enough to make the engulfing darkness to "
    +"the southeast recede from it.\n"
    +"The stairway appears to lead out of the cellar into the base of the "
    +"building.\n");

    add_item(({"darkness"}),
    "The darkness is all around you, swallowing the "
    +"surroundings to the southeast "
    +"whilst being held back by the light emenating "
    +"from the top of the stony "
    +"stairway to the northwest.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "c1", "northwest");
    add_exit(FIREKNIVES_ROOMS_DIR + "sm", "east", block_check);
    add_exit(FIREKNIVES_ROOMS_DIR + "c3", "southeast");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}

/* /d/Faerun/guilds/fire_knives/rooms/c1.c
 *
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("At the base of the stone stairway");
    
    set_long("From the ground rise thick and wide "
    +"steps that seem more natural "
    +"than man made. Moss and moisture cling to "
    +"the base and disappears with "
    +"each new one upwards into what seems to "
    +"be from here the base floor of the "
    +"building. To the southeast extends a tunnel "
    +"which marks the beginning of "
    +"a cold, dank cellar. An acrid smell "
    +"permeates the area, as if from deep "
    +"inside the humidity permeating the air "
    +"down here. A gentle draft pulls "
    +"a soft current from the stairs to the "
    +"southeast, disappearing into "
    +"nothingness.\n");

    add_item(({"steps","stairway","base"}),
    "From the ground rise thick and wide steps that seem more natural than "
    +"man made. Moss and moisture cling to the base and disappear with each "
    +"new one upwards into what seems to be the base floor of the building. "
    +"each step upwards is about the height of your knee, sculpted from the "
    +"rock itself. Although the first few ones are apparently slipery, they "
    +"are so well-worn from the passage of time that your feet would find a "
    +"good grasp on each one of them.\n");
    
    add_item(({"tunnel", "tunnels"}),
    "The tunnel extends to the southeast "
    +"from here, reaching into the darkness "
    +"deep within them.\n");

    add_item(({"walls", "wall"}),
    "The walls emanate a coldness which has turned the little air transiting "
    +"through this tunnel into moisture due "
    +"to the lack of ventilation. Green "
    +"patches of moss are scattered around them.\n");

    add_item(({"moss"}),
    "Patches of moss have grown from small fissures in the walls.\n");
    
    add_item(({"smell"}),
    "The smell is acrid, permeating all the area.\n");
    
    add_item(({"stairs"}),
    "The cold stone steps of the stairs lead up and out of the cellar.\n");

    add_item(({"fissures","fissure","crack","cracks"}),
    "Although firm and stable, the passing of time has left its mark on "
    +"the walls of this tunnel. They are far "
    +"and between, yet still present.\n");

    add_item(({"floor", "ground"}),
    "The floor of the tunnel is well-worn in "
    +"and seems to be frequented rather "
    +"than isolated from life. The patches of "
    +"moss, dirt, and pebbles bear the "
    +"form of what appear to be footsteps.\n");

    add_item(({"footstep","footsteps","dirt","pebble","pebbles"}),
    "Found on the ground and marked caked in "
    +"the dirt and moss are what appear to be "
    +"footsteps leading beyond to the southeast "
    +"from the base of the stairway.\n");

    add_item(({"darkness"}),
    "The darkness is kept at bay by the light "
    +"emenating from the top of the "
    +"stairs, swallowing everything beyond it to the southeast.\n");

    add_item(({"moisture"}),
    "The moisture accumulates from the cold "
    +"emanating from the walls and the poor "
    +"ventilation in the tunnels. Small puddles "
    +"of water are found in corners of the "
    +"passage, slightly streaming southeastwards.\n");

    add_item(({"puddle","puddles"}),
    "The puddles are formed from the condensed moisture "
    +"running down the walls.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "o1.c", "up");
    add_exit(FIREKNIVES_ROOMS_DIR + "c2.c", "southeast");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}

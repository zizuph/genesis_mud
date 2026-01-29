/* /d/Faerun/guilds/fire_knives/rooms/ra1.c
 *
 * 
 * Trainee rackroom
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
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Armory");
    
    set_long("This small room is organized to maximize its "
    +"capacity. Its walls "
    +"are lined with wooden racks in which weapons "
    +"and armours of all type "
    +"are stored. They are replicated on each "
    +"one of the four cardinal points "
    +"and crowned to the north with a sealed "
    +"off fireplace now serves as canvas "
    +"for various drawings of the human body "
    +"in all shapes and sizes, its vital "
    +"points marked in red ink and scrapped "
    +"in and around them by what can only "
    +"be powerful blows. Wooden planks are "
    +"placed throughout the cold stone "
    +"floor more than likely to protect the weapons "
    +"should they fall, while the "
    +"ceiling is covered in arching wooden structures "
    +"that hold the frame of "
    +"what could be used as a storage place above the racks. \n");
    
    add_item(({"room","area"}),
    "The area deafens the noise with its wooden planks covering "
    +"most of the walls and floor. It is wide enough to comfortably "
    +"equip yourself without feeling constrained, and high "
    +"enough to allow for a storage place to be "
    +"constructed above the racks on top of the wooden frame that outlines "
    +"the room.\n");

    add_item(({"wall","walls"}),
    "The walls are evened out and covered with wooden planks behind the "
    +"racks that are lined out throughout them.\n");

    add_item(({"fireplace","sealed fireplace"}),
    "Where a fireplace once stood and has sometime in the "
    +"past been sealed shut now are various drawings made "
    +"on its surface of figures of the human body, "
    +"its vital points marked by red ink.\n");

    add_item(({"canvas","ink","red ink", "drawings","drawing"}),
    "The vital points of the drawings on the wall where "
    +"the fireplace has been "
    +"sealed shut are marked in red ink, which has "
    +"been partly scrapped off along "
    +"with the chips off the wall by what can "
    +"only have been numerous powerful blows.\n");

    add_item(({"racks","wooden racks"}),
    "The wooden racks line the walls, holding various "
    +"weapons in place. Most are low "
    +"enough for all races to reach, and the ones that "
    +"aren't hold particular weapons "
    +"which would be impossible for someone of "
    +"lesser height to wield.\n");

    add_item(({"planks","wooden planks"}),
    "The wooden planks cover the floor and walls "
    +"of the room, keeping the weapons away "
    +"from the cold stone and protecting them "
    +"from any accidents that could happen.\n");

    add_item(({"floor","stone floor"}),
    "The otherwise cold, stone floor is covered "
    +"with scattered and uneven planks of "
    +"wood, mostly found around the racks.\n");

    add_item(({"ceiling"}),
    "The ceiling is covered in a dome like wooden "
    +"structure resting atop arches of "
    +"the same. The area in between seems to "
    +"be a storage place of sorts for miscellanea.\n");

    add_item(({"structures","wooden structures","arching wooden structures"}),
    "The wooden structure maximizes the space "
    +"within the room, allowing for lamps to be "
    +"hung from them and a storage place to be built atop it.\n");

    add_item(({"lamp","lamps"}),
    "Large oil lamps hang from the wooden structure "
    +"at various intervals, shedding light "
    +"to the area.\n");

    add_item(({"place","storage place","storage"}),
    "The storage place is built atop the wooden structure "
    +"right above the middle of the "
    +"the room. It serves to keep miscellanea "
    +"that wouldn't fit into the racks.\n");


    add_exit(FIREKNIVES_ROOMS_DIR + "o9", "north");
    
    room_add_object(FIREKNIVES_OBJ_DIR + "trainee_rack");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}

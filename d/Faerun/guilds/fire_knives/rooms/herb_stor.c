/* /d/Faerun/guilds/fire_knives/rooms/herb_stor.c
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
inherit "/d/Gondor/common/lib/herb_storage";

#define FIREKNIVES_HERB_SHOP	"/d/Faerun/guilds/fire_knives/rooms/herb"
#define FIREKNIVES_HERB_SAVE	"/d/Faerun/guilds/fire_knives/rooms/herb_store"


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("Near the stone stairway.");    
    
    set_long("The darkness to the southwest recedes against the light emanating from "
    +"above the stone stairway to the northwest. The passage seems to descend slightly "
    +"to the southwest, as evidenced by the slow trickle of condensed moisture "
    +"traveling in that direction. Almost imperceptible, the base of the steps rise "
    +"from the cold, thick stone in the distance opposite the engulfing darkness "
    +"in what seems to be a tunnel through the cellar.\n");

    add_item(({"tunnel", "tunnels"}),
    "The tunnel extends to the northwest, reaching the base of a stone stairway "
    +"and back to the southeast from here into the darkness deep within them.\n");

    


/* Add Actions */     

    
    add_exit(FIREKNIVES_ROOMS_DIR + "herb", "out");
    
    set_save_file(FIREKNIVES_HERB_SAVE);
    restore_object(save_file);


    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   enter_storage_inv(ob, from);
}

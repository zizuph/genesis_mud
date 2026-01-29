#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit TRAVELLERS_STD_DIR + "room_base";

#include <stdproperties.h>

void
create_traveller_room() 
{
    set_short("Outside the chateau");
    set_long("You are standing outside the chateau. It rises" +
        " high above you, with its towers and minarets reaching" +
        " to the sky. Its dark grey stone stands out starkly" +
        " against the bright sky. An archway leads into the" +
        " the chateau west.\n");

    remove_prop(ROOM_I_INSIDE);
    
    add_item(({ "arch", "archway" }),
        "It is as magnificent as the columns\n");
    
    add_exit("hall", "west");
}

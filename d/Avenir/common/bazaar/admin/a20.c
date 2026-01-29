// file name:        /d/Avenir/common/bazaar/admin/a19.c
// creator(s):       Lilith, Nov 2021
// revisions:
// purpose:
// note:
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/bazaar/admin/admin_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/bazaar/admin/admin.h"
#include "/d/Avenir/common/village/village.h"

/* Now create the room.  */
void
create_admin_room()
{
    set_short("alleyway");
    set_long("This cobbled path leads northeast toward the "+
	    "Tribunal Square. The buildings of the Kestares are "+
        "tall enough that they block the Source and cast the "+
        "pathway into deep shadow. Southwest, this street inter"+		
        "sects with the boundary road encircling the village "+
        "of Sybarus. The air is moist and fresh here, and "+
        "though you can hear the ebb and flow of voices, it "+ 
        "is mostly quiet and peaceful.\n");

    add_outside();
    add_item(({"gloom", "shadow", "building", "buildings"}),
        "The Questioning Place and the Tribunal building "+
        "are big enough to prevent the light of the Source "+
        "from penetrating the shadows. It is gloomy and dark "+
        "there, but probably safe enough.\n");
		
    add_exit(BAZ_ADMIN +"a19", "northeast",  0);
    add_exit(VILL +"street/07", "southwest",  0);   	
       
    reset_admin_room();
}

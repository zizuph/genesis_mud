#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("In a corridor in the temple");
    set_long("You are standing in a corridor inside the Temple of " +
        "Darkness. It is about 12 feet wide with the vaulted ceiling " +
        "rising 15 feet above your head. Flickering light from the torches " +
        "along the black walls are mirrored off the polished marble floor " +
        "creating disturbing movements of shadows all around you. An " +
        "archway to the northwest leads into another room and the corridor " +
        "continues both east and west.\n");

    add_exit( LVLTWO + "corr1.c", "east" );
    add_exit( LVLTWO + "corr3.c", "west" );
    add_exit( LVLTWO + "post.c", "northwest", "@@temp_ban" );
}

int
temp_ban()
{
    /* This was due to the stamp event
     */
    return 0;
    
    if (this_player()->query_wiz_level())
        return 0;

    if (this_player()->query_guild_member("Priests of Takhisis"))
        return 0;

    this_player()->catch_tell("Someone has erected some sort of barrier " +
        "here that stops your attempt to go that way.\n");
    return 1;
}

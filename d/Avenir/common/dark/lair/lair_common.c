// Common functions for rooms making worm lair.
// to be inherited by all rooms in lair.
// Made by Boriska

#include "/d/Avenir/include/worm.h"

inherit "/d/Avenir/common/map/map_room"; // mapper object handles exits
inherit "/d/Avenir/inherit/room_tell";   // room tells (tm) by Aridor.

void
create_room()
{
    ::create_room();

    add_item("floor", 
        "You cannot see the floor through the lava, but it "+
        "feels firm and smooth, worn away by countless centuries "+
        "of molten rock.\n");
    add_item(({"smoke","air"}),
        "Thick clouds of grey smoke drift around you and "+
        "your sight. The orange light from the flames reflect "+
        "off of the smoke and make it appear ominous.\n");
    add_item(({"wall","walls","tunnel"}),
        "The walls of this tunnel smoulder, occassionally sending "+
        "small curlsflames and smoke into the air. They are rough "+
        "and uneven, hewn by some unknowable force from the bowels "+
        "of the world.\n");
    add_item(({"fire","fires","flame","flames"}),
        "The fires that burn the rock around you are unbelievably "+
        "hot, a heat that would sear your lungs and kill you "+
        "instantly but for some strange force that permits you "+
        "to live, for the present.\n");
}


// notifies master_worm object about player leaving its environment,
// used to make the worm follow players around.
// Prints some messages when moving.
void
leave_inv (object ob, object to)
{
    object master_worm;
  
    ::leave_inv(ob, to);
    if (!to || !ob || !interactive(ob))
        return;
    ob->catch_msg("You make your way slowly down the smouldering "+
        "tunnel, picking your path through the lava flows and fighting "+
        "the heat which saps your strength.\n");

    if (!(master_worm = WORM_LAIR->query_master_worm()) ||
        environment(master_worm) != this_object())
        return;
  
    master_worm->notify_leave_env(ob, to);
}
  
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (objectp(ob) && interactive(ob))
        start_room_tells();
}

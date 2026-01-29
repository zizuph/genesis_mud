/* This is the dark abbey where the priests perform their worship to
 * the Dark Queen. It is private so all rites can be performed here
 * without unwanted spectators.
 *
 * I would like this to be the room which holds all the functions which
 * currently are available in the dark abbey of the old temple.
 */

#pragma strict_types

#include "/d/Ansalon/taman_busuk/neraka/temple/defs.h"

inherit TEMPLE + "std_temple.c";
inherit "/d/Ansalon/guild/new_pot/rituals/rituals";


void
create_temple_room()
{
    object altar;

    ::create_temple_room();

     set_short("In the Dark Abbey");
    set_long("This is a large circular chamber with a high vaulted ceiling. " +
        "Torches along the walls light the room and on the floor lies a " +
        "heavy red carpet. In the western side of the room stands a " +
        "statue of the Dark Queen upon a podium and at her feet is an " +
        "altar.\n");

    setuid();
    seteuid(getuid());

    altar = clone_object("/d/Ansalon/guild/new_pot/rituals/obj/altar");
    set_altar(altar);
    altar->move(this_object());
    
    load_rituals();
    
//    add_exit( DUNGONE + "corr7.c", "east" );
}

void
init()
{
    ::init();
    
    init_rituals();
}

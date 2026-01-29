/*
 * Orc camp tower
 * By Finwe, December 2007
 */

#include "defs.h"

inherit OC_TOWER_BASE;


void
create_tower_room()
{
    setuid();
    seteuid(getuid());

    reset_faerie_room();

    set_short("Top chamber of the tall tower");
    set_long(short() + ". It is larger than the rest of the tower. It is where the chief orc lives and rules the camp. Bones litter the floor and a large throne sits in the center. A ladder sits in a corner, allowing travel between the levels.\n");

    add_tower_stuff();

    add_item(({"throne"}),
        "The throne is large and dominates the chamber. It is made of solid timbers lashed together with leather. The throne is heavy looking and dark colored from countless bloodstains.\n");
    add_item(({"bloodstains"}),
        "They are dark and run down the sides of the throne. Some stains look fresh from unfortunate victims.\n");
    add_item(({"bones"}),
        "They are chewed on and scattered across the chamber. They are the grisly reminders of the orc's enemies\n");

    add_exit(OC_DIR + "undert03", "down");
}


public void
init()
{
    ::init();

}
void
reset_faerie_room()
{
    object orc, orc_lord;
    int i;

    setuid(); 
    seteuid(getuid());
    
    if (!present("_orc_lord"))
    {
        clone_object(NPC_DIR + "orc_lord")->move(TO);
    }
    
    if (!present(ORC_OFFICER_NAME))
    {
        for(i=1; i<=4; i++ )
            clone_object(NPC_DIR + "orc_officer")->move(TO);
    }
}

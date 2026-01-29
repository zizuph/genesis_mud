/* This is the Grunts training hall. The trainer who teaches skills    */
/* here will train anyone who has enough money.                        */
/* Grunts do not get any special deals here, for tax reasons.          */


inherit "/std/room";

#include <stdproperties.h>
#include "default.h"
#include "../guild.h"

/* Prototype function */
public void reset_room();

/*
 * Function name:   create_room
 * Description:     define the basics of the room  
 */
public void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    
    set_short("Grunts training hall");
    set_long("   Well, this is the nearest a cave will ever get to becoming "
	+ "a hall. This is where Grunts come to practice their fighting "
	+ "skills. The floor covers quite a large area, and judging by "
	+ "the numerous blood stains on it, is in regular use. "
	+ "You notice that this hall is suspiciously close to the Grunts "
	+ "bar to the north.\nPerhaps the arguments started in the bar get "
       + "finished out here ...\n\n");
    
    add_item(({"blood","stains"}),
	"There are many patches of blood dried on the floor. Most " +
	"are from minor scratches, but some of the others patches " +
	"are too big to be from anything less than fatal wounds.\n");
    
    add_item(({"walls","wall"}),
	"There are torches fixed on two walls of the bar. " +
	"The walls are cold, and damp to touch. It seems to be made " +
	"of the usual volcanic rock like the rest of the caves.\n");
    
    add_item(({"roof","ceiling"}),
	"The roof is made of the same rock as the walls, the familiar " +
	"volcanic rock. At least you can " +
	"be fairly sure the roof won't be falling down, as volcanic rock " +
	"is pretty tough stuff.\n");

    add_item(({"floor","ground"}),
	"The floor on which you are standing seems very firm, and is made " +
	"of volcanic rock. The blood stains add a splash of colour to " +
	"the otherwise rather dull rock.\n");

    add_item(({"torch","torches"}),
	"The torches are fixed firmly to the wall, and cannot be taken.\n");

    
    add_exit(THIS_DIR + "bar", "north", 0, 1);
    add_exit(THIS_DIR + "shop", "east", 0, 1);

    reset_room();
}


/*
 * Function name:   reset_room
 * Description:     put the Grunts trainer into the room as required  
 */
public void
reset_room()
{
    object trainer;
    
    if (!present("korfgowl"))
    {
	trainer=clone_object(GRUNTS_DIR + "npc/trainer");
        trainer->arm_me();
	trainer->move(TO);
    }
}


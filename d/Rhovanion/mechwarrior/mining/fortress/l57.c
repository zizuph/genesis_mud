
 
/* Mechwarrior, 11 Sep 1995 */
 
inherit "/d/Rhovanion/lib/room";
 
#include <stdproperties.h>
#define THIS_DIR "/d/Rhovanion/mechwarrior/mining/fortress/"
 
void
create_room()
{
   set_short("Lt. Mechwarrior's Headquarters");
   set_long("You find yourself standing before the center of " +
      "operations for Mechwarrior, Lieutenant of the Army of " +
      "Angmar.  Hearing footsteps echoing, you notice the floor " +
      "to be made of stone marble.  You also see a mahogany desk " +
      "in the center of the room with a leather chair behind it.  " +
      "An impressive painting adorns the wall behind the desk. \n\n");
 
   add_exit(THIS_DIR+"o58.c", "east");
   add_exit(THIS_DIR+"r56.c", "west");
 

   add_item(({ "painting", "oil painting" }),
        "It is a magnificient brush painting done by Lt. Mechwarrior " +
        "depicting the comradery of the soldiers drinking gayishly " +
	"at the local pub of a town they just conquered.\n");

   add_item(({"desk", "table" }),
	"A large office desk made of the finest wood around.  You " +
	"get the impression that the desk was a 'gift' from a town "+
	"that was recently sacked by the Army of Angmar.\n"); 

   add_item(({"chair", "leather chair" }),
   	"Made from the finest Corinthian leather, you realize it " +
	"must be designed for Lt. Mechwarrior to sit on.\n");

   add_item(({"paper", "orders" }),
	"Marked Confidential!  Other than that, you can't make " +
	"out the military code Lt. Mechwarrior used.\n");
 

 
}
 



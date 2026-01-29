// file name:        /d/Avenir/common/village/pale/temple/01.c
// creator(s):       Lilith & Hannah, 03/01,04/02
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/village/temple_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/village/village.h"  

/* Now create the room.  */
void
create_temple_room()
{
    set_short("Center of vaulted room, at base of spiral staircase");
    set_long("You are standing in the center of the Temple of "+
        "the Idrys, at the base of a massive staircase that spirals "+
        "upwards. The blessed light of the Source penetrates "+
        "the domed ceiling, casting a muted, golden glow "+
        "upon everything it touches. "+
        "The staircase itself is made of the "+
        "rarest building material known to all Sybaruns, wood. "+
        "With its graceful, sweeping lines, each step curves "+
        "around a twelve-sided wood column carved from the kesoit "+
        "tree. Balusters pass through the treads and up into the "+
        "handrail.\n"); 


      add_exit("07", "north", 0);
      add_exit("16", "south", 0);
      add_exit("12", "east", 0);
      add_exit("02", "west", 0);
      add_exit("21", "up", 0);

add_ground_floor();


	add_item(({"staircase", "spiral staircase", "stairs"}),
        	"Which part of the staircase do you wish to look at?\n");

      add_item(({"column", "twelve-sided column"}),
        "This column is made of the kesoit tree, its color "+
	  "variation is from mixing varnish with the sap of the "+
	  "bloodwood tree giving a reddish tint to the otherwise "+
	  "dark wood.\n");

	add_item(({"rail", "railing", "handrail"}),
        	"The railing, hand rubbed to a exquisite glossy "+
	      "finish, is made of black ebony wood.\n");

      add_item(({"stair", "tread", "treads", "step", "steps"}),
        	"The treads are attached to the center column and "+
            "each step is carefully hewn of soft bloodwood so that "+
		"any step made upon it is absorbed, thus making any step "+
            "upon them a silent affair.\n");
	      
      add_item(({"dome", "ceiling" }),
         "The dome is made up of several arches, looming high above you. "+
         "The Source pulsates as it passes through the dome reflecting "+
	   "both the staircase and the pale stone of the arches above.\n");

      add_item(({"arch", "arches" }),
         "These arches start at the corners of each vault and "+
         "come together here forming a large open dome above you.\n");



    /* Air, cobbles, source, and hedges added from the base room, 
     * put additional add_items below. 
     */

    reset_domain_room();
}

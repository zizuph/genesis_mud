/* Author: Modred 950816 */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h";

create_room()
{
    set_short("South part of the courtyard");
    set_long("You stand in the south part of the courtyard."+
     " To the south a grand marble stairway leads up to a pair"+
     " of huge bronze doors. North, you can see the iron pole"+
     " rising towards the sky, like an evil black finger and to"+
     " the nortwest and northeast the courtyard spreads out.\n");

    add_exit(RHUN_DIR + "newruins/court_w","northwest");
    add_exit(RHUN_DIR + "newruins/court_e","northeast");
    add_exit(RHUN_DIR + "newruins/court_c","north");
    add_exit(RHUN_DIR + "newruins/stairs","south");

    add_item(({"stairway", "stairs"}),"The stairs are wide, and"+
    " almost seem to be cut from a solid block of marble. Statues"+
    " line both sides of the stairway. The craftsmanship in the stair"+
    " and the statues is exquisite, far beyond the rest of the fort\n");


    add_item(({"statues"}),"The statues are all made of black polished "+
     "marble. At first glance, the beauty of the statues were overwhelming"+
     ", but as you get closer you realise that they are too lifelike!"+ 
     " No human could ever shape stone like this! The statues are kneeling"+
     " along the stairs, their elven faces contorted with horror. \n");

}

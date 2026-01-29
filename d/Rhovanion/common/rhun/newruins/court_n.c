/* Author: Modred 950904 */


inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h";

create_room()
{
    set_short("North end of the courtyard");
    set_long("You stand at the north end of an almost"+
    " circular courtyard. The walls seem to loom over you, crushing"+
    " the space around you, engulfing you in their cool shadow."+
    " You feel like an intruder here, maybe it "+
    " would be better to return to the road? To the south you see a"+
    " great pole jutting out of the center of the courtyard, and to "+
    " the southwest and southeast the courtyard spreads"+
    " out.The portal out lies to your north.");

    add_exit(RHUN_DIR + "newruins/court_e","southeast");
    add_exit(RHUN_DIR + "newruins/court_w","southwest");
    add_exit(RHUN_DIR + "newruins/court_c","south");
    add_exit(RHUN_DIR + "newruins/gates","north");
  
   add_item(({"pole","iron pole"}),"From the center of the courtyard"+
    " a great pole made of iron rises. The rust makes it look covered"+
    " in blood. \n");

    add_item(({"wall","walls"}),"The walls look even more formidable from"+
    " the inside, in fact they look like they were used to keep something"+
    " in as well as out. The carvings are not as worn here inside the fort. \n");
    
    add_item ("carvings", "The carvings inside the fort have withstood the"+
    " test of time. There are two designs that occur regularly, one wich"+
    " look like a giant eye, always looking. The other carving seem to be two"+
    " clubs crossed over a scull.\n");


}

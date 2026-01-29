/* Author: Modred 950904 */


inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h";

create_room()
{
    set_short("North end of the courtyard");
    set_long("You stand in the center of the courtyard,"+
    " looking up at an iron pole rising from the ground. Chains bolted"+
    " to the pole swing through the air as the wind moves them, and the "+
    " hoarse cry of a raven echoes through the courtyard. Although a warm"+
    " day, you cant seem to get rid of the chill spreading through your"+
    " bones. To the south, east and west the courtyard spreads"+
    " out.The portal out lies to your north.\n");

    add_exit(RHUN_DIR + "newruins/court_e","east");
    add_exit(RHUN_DIR + "newruins/court_w","west");
    add_exit(RHUN_DIR + "newruins/court_s","south");
    add_exit(RHUN_DIR + "newruins/court_n","north");

    add_item(({"pole","iron pole"}),"The iron pole is about ten metres high, "+
    " with chains hanging from the top. The iron has rusted over the years, "+
    " making the pole look like it is drenched in blood. A lone raven sits"+
    " at the top of the pole, watching you. \n");
    
    add_item ("chains", "You step closer to examine the chains, and "+
    " immediately wish you hadn't. What looked like rust is in fact dried"+
    " blood! Maybe this place isnt as deserted as you thought? You wonder"+
    " how many poor souls have been strapped to this pole to die.\n");
    add_item ("raven", " The raven watches your every move.....even when"+
    " you turn your back, you can feel his eyes in your neck. You"+
    " wonder whatever he can find to eat in this godforsaken place\n");

}

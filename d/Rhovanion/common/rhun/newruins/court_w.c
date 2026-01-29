/* Author: Modred 950816 */


inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h";

create_room()

{
    set_short("West end of the courtyard");
    set_long("You stand in the western end of an"+
    " almost circular courtyard, in front of a stone"+
    " dais. Upon the dais there is a rough stone chair"+
    " cut from a soild block of black marble. Although the"+
    " rest of the courtyard is filled with debris, the area"+
    " around the dais is almost clear, showing the stone "+
    " paving that probably  covers the whole courtyard.\n");

    add_exit(RHUN_DIR + "newruins/court_n","northeast");
    add_exit(RHUN_DIR + "newruins/court_s","southeast");
    add_exit(RHUN_DIR + "newruins/court_c","east");

    add_item(({"dais"}), "The dais is a simple stone platform"+
    " rising about one metre above the ground. Its base is covered"+
    " with the same carvings that adorn the walls. In the centre"+
    " of the dais the chair stands.\n");
    
    add_item(({"chair"}), "It is a simple stone chair, cut from a"+
    " single block of black marble. On top of the back of the chair"+
    " a large symbol is carved deep into the stone.\n");
    
    add_item(({"symbol"}), "The image of a dark red eye looks out across"+
    " the courtyard, and below the eye a bloodred shield is etched."+
    " This place must be deserted, but the symbol still chills your"+
    " blood. You notice that not a speck of dust has settled on the"+
    " symbols, or the chair for that matter.\n");
}

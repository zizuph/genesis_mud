#	pragma strict_types

#include "/d/Faerun/defs.h"
 
inherit "std/room";

object azure_wine;
 
public void
create_room()
{
    
    //0 means outdoors, and 1 means indoors for this prop
    add_prop(ROOM_I_INSIDE, 1);
    
    set_short ("Inside a small brown tent.");

    set_long("The tent is clean and maintained. Herbs hang from the beams above " +
         "you. There are crates, boxes, and sacks stacked and placed neatly " +
         "in the center of the tent. There are wide, squat barrels lining " +
         "right side.\n");
         
    add_item(({"crates"}),
         "The crates are clean. The writing on the sides tells you they are " +
         "filed with a number of different things. Mostly goods and " +
         "non-perishables.\n");
    
    add_item(({"sacks"}),
        "The sacks are full of bolts of brightly colored cloth, spidersilk, " +
        "cotton, satin, elfwyr and webcloth.\n");
    
    add_item(({"boxes"}),
        "The boxes are sealed and taped shut. They are unmarked.\n");
    
    add_item(({"beams"}),
        "Fresh herbs and flowers hang from the beams of the tent.\n");
        
    add_item(({"casks","barrels","containers"}),
         "There are casks of what seems to be wine lining the right side " +
         "of the tent. There are a few skins lying on top of the barrels. " +
         "one skin appears to be quite full.\n");
    
    add_exit("/d/Faerun/bootcamp/camp1","out");
	
    azure_wine = clone_object(OBJ + "skin");
    azure_wine->move (this_object() );
}

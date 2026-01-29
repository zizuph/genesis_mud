inherit "/d/Shire/common/lib/rom";
#include "/d/Shire/common/defs.h"

create_rom()
{
    set_short("Hillside.");
    set_long("You stand in the eastern parts of the Bree-hill. "
	    +"Here the road ends. Gazing south-eastwards you can "
	    +"see a road, which is going from Bree and further east. "
	    +"Just north of where you stand there is an open door "
	    +"leading into a rather large hole. The road continues northwest "
	    +"towards the center of Bree.\n");
	    
    add_exit(BREE_DIR + "bhill2","northwest",0,2);
    add_exit(BREE_DIR + "hobhole1","enter",0,1);
    
    add_item("hill","The Bree-hill is a small hill, with a forest covering "
    		   +"the backside of it. On the front side of the hill, there "
    		   +"is walls to protect the inhatitans of Bree.\n");
    		   
    add_item("road","The road you can see just south-east of here is bending "
    		   +"and turning in the east direction. Probably going towards "
      +"the feared and troll-haunted place, trollshaws.\n");
    		   
    add_item(({"door","open door"}),
    		    "The door is leading into a house. The house looks well kept "
    		   +"and old.\n");
    
    add_item("bree", "As you look down from the hill, in a west direction you can "
    		    +"see the rest of the village Bree. There you can find most "
    		    +"of the services you ever will need.\n");
}

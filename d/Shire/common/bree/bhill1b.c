#include "/d/Shire/common/defs.h"
inherit LIB_DIR + "rom";

create_rom()
{
    set_short("Bree hill");
    set_long("You are walking up a quite steep slope, going towards "
    	    +"up towards the 'hill'. You are surrounded by houses and "
    	    +"'holes', and from some of them you can see smoke rising. "
    	    +"From here you have a great view over the eastern parts of "
    	    +"Shire. A little further north-east the road bends eastwards "
    	    +"and follows the hill-side. Gazing south down towards Bree, "
            +" you can see the 'Prancing Pony' a famous landmark "
    	    +"in Bree.\n");
    	    
    add_exit(BREE_DIR + "bhill1", "southwest",0,2);
    add_exit(BREE_DIR + "bhill2", "east",0,1);
    
    add_item("slope","The road going up the 'hill' is paved and well kept. "
    		    +"It looks like it is used a lot.\n");
    		    
    add_item("house","There are quite lot of houses around here. They are plain "
    		    +"and do not give the idea that wealthy people live there.\n");
    		    
    add_item("holes", "The hobbits' home are dug into the ground, just as they prefer "
    		     +"to have their holes. They are mostly placed around the top of "
    		     +"the hill.\n");
    		     
    add_item("smoke","Smoke rises from many a building here. You gather that must be "
    		    +"because it is no other way of providing heat to warm up the houses "
    		    +"and cook food.\n");
    		    
    add_item("view","The view from up here is quite good. You can see up north the Deadman's "
    		   +"dike and west, the Shire.\n");
    		   
    add_item(({"prancing poney","poney","pony","prancing-poney","prancing"}),
    		"The 'Prancing poney' is a meeting place for many travellers and adventurers. "
    	       +"There they gather to tell and to listen to stories from all over Shire, and "
    	       +"sometimes they even get to hear stories from south. The beer is famous and is "
    	       +"reconed to be the best of whole middle-earth.\n");
    	       
    clone_object("/d/Shire/common/bree/obj/trees")->move(TO);

}


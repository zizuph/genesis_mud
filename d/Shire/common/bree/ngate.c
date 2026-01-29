inherit "/d/Shire/common/lib/rom";
#include "defs.h"

create_rom()
{
    set_short("By the north gate of Bree.\n");
    set_long("You are standing infront of the north gate of Bree. "
    	    +"The gates are closed due to the bad road going north "
    	    +"of here. There are no guards near here since this gate "
    	    +"is never used for traffic. From here you have a good view "
    	    +"up to Bree-hill, and you can see all the traffic passing "
    	    +"trough Bree south of here.\n");
    	    
    add_item("gate","The gates are sturdy and rather large by size. "
    		   +"It has been made by the finest oak.\n");
    		   
    add_item(({"lock","locks"}),
    		    "The locks are of a kind that is made to not be opened "
    		    +"without a key. Impossible to lockpick.\b");
    		    
    SOUTHEAST("brroad1");
}

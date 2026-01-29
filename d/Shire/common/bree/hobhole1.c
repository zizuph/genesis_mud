inherit "/d/Shire/common/lib/room";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
 
object hob;

create_room()
{
    set_short("hobbit hole");
    set_long("You are inside a small hobbit hole. Everything in here is "
    	    +"neat and tidy. It is very clean and it is easy to see that "
    	    +"the hobbit living here is fond of reading books. There is a "
    	    +"bookshelf standing against one wall, and it is filled with books. "
    	    +"On the eastern wall there is a large mirror, about the same height "
    	    +"as a tall hobbit, 4 feet. There is a big desk in the middle of "
    	    +"the room. Behind the desk there is a hobbit sitting on a chair.\n");
    	    
    add_item(({"book shelf","bookshelf","shelf"}),
    	    "The bookshelf is filled with books. It is made of pine and looks "
    	    +"sturdy.\n");
    
    add_item("books","There are lots of different books here. One book you notice "
    		    +"is one with the title 'My journeys to Gondor'. Various other "
    		    +"books are also there. There are many books about trees and gardens "
    		    +"and that is not surprising when you think of what hobbits are most "
    		    +"fond of. Gardens, plants, trees and herbs.\n");
    
    add_item("wall","The wall looks strong, compared with how it look from the outside "
    		   +"you can clearly see this cabin is much stronger then what it "
    		   +"appears to be.\n");
    		   
    add_item("desk","The desk has some drawers in it, not unusual for desk to have. "
    		   +"It looks very old, and the wood it is probably made from Oak. "	    
    	    	   +"Oak is a very common wood to make desks from.\n");
    
    add_item("drawers","Just some open drawers with nothing in them, they are empty.\n");
    
    add_item("chair","This is a wooden chair, made of pine. It is small of size, fitting "
    		    +"to the desk.\n");
    		    
    add_item("mirror","You can not see much there, only a very ugly face....weird, "
    		     +"the face reminds you of someone you have seen before....but you "
    		     +"can not quite remember who...\n");

	    
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_ATTACK,"No fighting, please!\n");
    
    add_exit(BREE_DIR +"bhill3","out",0,2);
        
    reset_room();  
}
   
reset_room()
{ 
    if (!hob)
    {
        hob = clone_object(BREE_DIR + "npc/" + "oldhobbit");
        hob->move(TO);
    }
}

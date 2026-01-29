inherit "/d/Shire/common/lib/rom";

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

object paper;

create_rom()
{
    set_short("Up on the Bree-hill.");
    set_long(
    	     "You are halfway up the top of the 'hill'. Further up placed around the top "
    	    +"of the hill, hobbits have their homes, or 'holes' as they are called. "
    	    +"There are quite a lot of houses up here, most of them placed south and "
    	    +"southeast of here. The gardens surrounding most of the houses here looks "
    	    +"well kept and tended. The hole just southeast of here is what draws your attention "
    	    +"most. It is quite big and it looks a bit different then the other "
    	    +"holes here.\n");
    	    
    add_prop(OBJ_I_SEARCH_TIME, 4);
    add_prop(OBJ_S_SEARCH_FUN, "search_tree");
    
    add_item("hill","The Bree-hill is only about 100 feet high, and has lots "
    		   +"nice gardens here. That is the work of these queer hobbits "
    		   +"who really enjoy working with gardens and trees. Where you "
    		   +"are now is only halfway up the hill.\n");
    		   
    add_item("gardens", "Most of the gardens here have hedges surrounding them. "
    		       +"The hedges is not that high, about the same height "
    		       +"as average hobbits (3 1/2 feet).\n");
    		       
    add_item(({"tree","trees"}),"There are trees in some of the gardens. They look "
    				+"very old and proud.\n");
    				
    add_item(({"house","houses"}),
    		     "There are quite a lot of houses here. Most of them look equal. But this "
    		    +"house is a bit different then the other houses. It looks like some "
    		    +"elder of the village is living there.\n");
    		    
    add_item(({"hole","hobbit hole","holes","hobbits holes"}),
     		     "The hobbits live in holes which have been dug in the ground. They "
     		    +"usually look dirty on the outside, but if you manage to come inside "
     		    +"you will most likely discover that they are very nice and cosy.\n");
 
    clone_object(BREE_DIR + "obj/trees")->move(TO);

    add_exit(BREE_DIR + "hill2", "west", 0);
    add_exit(BREE_DIR + "bhill3", "southeast", 0);
}

search_tree(object me, string arg)
{
   object paper;
   
   if(arg !="tree") return "Your search reveals nothing.";
   if (me->query_skill(SS_AWARENESS) > 20)
   {
       say(QCTNAME(me) + " finds something in the tree.\n");
       return "You find a piece of paper as you search the tree, "+
       	      "but you are not sure what it is.\n";
   
   paper = clone_object(BREE_DIR + "obj/" + "rpaper");
   paper->move(TO);
   
   }
   return "";    
}

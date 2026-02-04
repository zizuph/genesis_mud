// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, added cloning of BOD
/* from the imagination of Lord Sorgum ;)  */

// THIS IS WHERE THE BOOK OF DARKNESS WILL BE FOUND
// HIDDEN AMONGST THE BONES. clone from the Terel/unique dir

#include "/d/Terel/include/Terel.h"
inherit MOOR_DIR +"tomb/tomb_base";
inherit "/lib/unique";
#include <ss_types.h>
#include "../local.h"

public void
reset_room(void)
{
    searched = 0;
}

void
create_room()
{
		::create_room();

    set_short("In a shaft beneath the tomb");
    set_long("You have fallen somewhere deep beneath the tomb. It is "+
        "not possible to go back the way you entered. This appears "+
		"to be the bottom of a shaft and there is no way back up. "+
        "Bones crunch under you as you struggle for footing. The "+
        "stench here is overwhelming.\n");

    add_prop(OBJ_I_SEARCH_TIME, 6);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    enable_reset(200); // 45 mins
   
    add_item(({"bone", "bones", "pile of bones"}), 
	    "The bones are piled very deep here. The ones on top "+
        "appear to be rather fresh. You can see flesh glistening "+
		"on them.\n");
		
    add_item(({"shaft"}), "The shaft stretches high above.\n");		
    // The only way out is through...
    add_exit("tomb_stairs", "down", 0);    
}

public mixed
do_search(object searcher, string str)
{
   object ob;
   
    notify_fail("Your search reveals nothing but bones.\n");
    if (searched)
      return 0;

    if (searcher->query_skill(SS_AWARENESS) < 49)
      return 0;

    if (!strlen(str) || !parse_command(str, ({ }),
        " [the] [pile] [of] 'bones' / 'pile'", str))
      return 0;
  
    searched = 1; // Once per reset.
		   
 //   ob = clone_unique("/d/Terel/unique/book_of_darkness", 10, 
 //	    OBJDIR+"sack", 1, 40);
 
    if (!ob)
      return "Your search reveals nothing but bones.\n";
      
    ob->move(searcher, 1);		

    return "You find "+ ob->short() +" buried deep under a pile "+
        "of bones.\n";
}
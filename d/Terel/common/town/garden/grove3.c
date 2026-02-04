// modified by Lilith, Mar 2022:  updated desc and added items.
 
#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

#define PATH "/d/Terel/common/town/garden/"
inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

void
reset_room()
{
    set_searched(0);
}

void
create_room(){
  
   set_short("Grove");
   set_long(
      "This is a very thick part of the copse. The trees here\n" +
      "are tightly fit together, the underbrush is also very\n" +
      "thick. This spot has been allowed to grow wild.\n");

   add_item(({"tree", "trees"}),
	    "Not much light gets throught the trees here.\n");
   add_item("underbrush", "It's scrubby, and dried out but nevertheless " +
	    "it's very thick.\n");
   
   add_exit(PATH + "copse1", "east", 0);
 
   set_up_herbs( ({one_of_list(RANGER_HERBS),
                     one_of_list(MM_HERBS),
                     one_of_list(ANY_HERBS),
                  }),
              ({"ground","garden","bushes","underbrush"}), 
                   3 );
				   
    reset_room();
 
}


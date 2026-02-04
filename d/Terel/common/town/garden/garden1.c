// modified by Lilith, Mar 2022:  updated desc and items, removed "sdaf" access

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
create_room()
{
   
   set_short("Garden");
   set_long("This is a sacred garden, kept alive in this cold by\n" +
      "great devotion to its upkeep. Rows of evergreens enchant\n" +
      "this place with a life of vivid green. To the north is the\n" +
      "river, traversed by an old bridge. Going further south will\n"+
      "reveal more of this sacred place to you.\n");


     set_up_herbs( ({one_of_list(RANGER_HERBS),
                     one_of_list(MM_HERBS),
                     one_of_list(ANY_HERBS),
                  }),
                  ({"ground","garden","bushes","rows","here"}), 
                   3 );

   add_item(({"garden","sacred garden","ground"}),
       "The sacred garden looks well maintained.\n");
   add_item(({"rows", "evergreen", "evergreens", "rows of evergreens",
       "bushes", "bush"}),
       "These are rows of small evergreen bushes, kept trimmed "+
       "just-so by the fastidious gardeners.\n");
   add_item(({"bridge", "old bridge"}), "It is very old and made " +
       "of wood. It appears to be in excellent condition.\n");	  
   add_item(({"tree", "trees", "pine trees", "pines", "ancient pines", 
        "ancient pine tress", "ancient trees", "forest", "boughs"}),
    	"These ancient pine trees are all tall and straight, " +
        "with thick trunks that are perfect for building cabins "+
		"and houses. They grow thickly together and cast a deep, "+
        "mysterious shade. Their boughs are covered in snow.\n");
    add_item(({"shade", "deep shade" }), 
      "The ancient pine trees grow so thickly together that they cast a "+
      "mysteriously deep shade over the area.\n");		  
    add_item(({"snow", "ice"}), "The ice and snow never disappears in "+
        "this part of the world. Here it's damn cold unless you have warm clothes.\n");
    add_item(({"river", "water"}), "The river streams fast, otherwise " +
        "it would have been covered with an ice layer. The water is real " +
        "cold. The riverbank is overgrown with various plantlife.\n");
    add_item(({"plantlife","plants","riverbank", "soil", "muddy soil"}),
        "Various plantlife thrive in the frozen muddy soil of the riverbank.\n");	 
   
   add_exit("/d/Terel/common/town/garden/bridge", "north", 0);
   add_exit("/d/Terel/common/town/garden/lane1", "south", 0);
   add_exit(PATH + "garden2", "east", 0);
   
   reset_room();
 
}

/*  This toolsoul no longer exists, and this isn't really the appropriate
 *  way to add such things, as a mortal might be able to exploit this.
 *    -- Lilith, Mar 2022
init()
{
   ::init();
	add_action("do_sdaf","sdaf");
}
int
do_sdaf(string str)
{
	if (str=="reindeer")
	{
		this_player()->add_toulsoul("/d/Wiz/caution/extra_soul");
		this_player()->update_hooks();
}

}
*/
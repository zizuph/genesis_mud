
/*
 * Modified by Sorgum 940118
 *
 * added link to ~sorgum/tomb/meadow02
 * added herbs and terel std room  -- Tomas Dec 1999
 *
 * Lilith Dec 2021: moving area out of Sorgum's dir, updated paths
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"
#include "../local.h"

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";


#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])

void
create_room() 
{

    set_short("Moor highland");
    set_long("There is a bleak emptiness to this highland moor, covered in "+
        "frost and malevolent mists that seem to defy the howling winds. "+
	    "Heather and moss compete with shrubs for dominance in the poor, "+
		"boggy soil, but the shrubs seem to be winning. Off to the north "+
		"a craggy hill rises steeply, while to the west, a meadow of sorts "+
		"has formed. Massive megalithic rocks rise up from the ground "+
        "like monsters lying in wait.\n");
		
    add_exit("moor_hill", "north",0);
    add_exit("moor3", "south",0);
    add_exit("moor5", "east", 0);
    add_exit("../hills/meadow02", "west", 0);

    add_item(({"rocks", "megalithic rocks", "megaliths"}), 
        "There are megalithic rocks, some as small as a horse, others as big "+
        "as a house, scattered across the moors as if by a giant's hand.\n");
    add_item(({"heather", "ground", "moss"}),"The ground is covered in heather "+
       "and moss and standing water due to poor drainage.\n");
    add_item(({"trees","tree","small tree","small trees"}),
      "Several small trees dot the moorlands and line the roads.\n");
    add_item(({"hill","hills","moor", "moors"}),"Rolling hills covered in mist.\n");
    add_item(({"bushes","shrubs"}), "Bushes and shrubs " +
       "litter the area.\n");   
    add_item(("hills"),"Rolling hills.\n");
    add_item(({"mist", "mists" }), "They seem malevolent as they glide "+
       "across the moors.\n");
   set_up_herbs( ({ ONE_OF_LIST(FROST_HERBS),
                    ONE_OF_LIST(FROST_HERBS),
                    ONE_OF_LIST(FROST_HERBS),
                 }),
                 ({"bushes","shrubs", "hills"}) , 
                     3 );
 
   reset_room();
}

/*
 * Function name:
 * Description  :
 */


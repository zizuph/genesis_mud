/*
  Added herbs and new terel defs  -- Tomas Dec 1999
*/


#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

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
		"and east the elevation drops into a swampy area, thick with fog. "+
        "West is the rest of the moor, waiting in icy silence.\n");
 
   add_exit("moor4", "west",0);
   add_exit("/d/Terel/common/swamp/sw2", "east", "@@check_troll");
   add_exit("swamp", "north", 0);
   
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
    add_item(({"swamp"}), "It is too foggy to see any details from here.\n");

   set_up_herbs( ({ ONE_OF_LIST(FROST_HERBS),
                    ONE_OF_LIST(FROST_HERBS),
                    ONE_OF_LIST(FROST_HERBS),
                 }),
                 ({"bushes","shrubs", "ground"}) , 
                     3 );

   reset_room();
}

check_troll()
{
    if(this_player()->query_race_name()=="troll") return 1;
}



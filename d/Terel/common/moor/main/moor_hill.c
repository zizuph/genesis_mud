// Modifications:
// Lilith, Jan 2022
//     Updated descs and exits for migration from Sorgum's dir to the 
//     Terel/common/moor dir.

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])

#define N_TROLLS  4
#define PEBBLES   6

int pebbles = PEBBLES;


void
reset_room()
{
    pebbles = PEBBLES;
}

public void
create_room()
{
    set_short("Frosty hill");
    set_long("This frosty hill stands a bit above the rest of the hills of " +
             "the moor, providing an excellent view of the surroundings. " +
			 "You can see megalithic rocks scattered here and there in "+
             "the rugged moorland below. "+
             "Pebbles are strewn about the deep moss, bushes, and shrubs " +
             "that covers the hill. " +
             "Deep marks are impressed in the earth, like footsteps. A " +
             "mist glides about the hills, eluding all who seek it.\n");
    add_item(({"ground", "earth", "marks", "peat", "soil"}),
        "The earth on the hill is saturated and only lightly covered "+
		"with moss, so it easily shows marks left by the the steps "+
        "of creatures great and small.\n");
    add_item(("hill"),"The hill is covered in moss, small bushes and " +
       "shrubs.\n");
    add_item(({"bushes","shrubs"}),"Various sized bushes and shrubs " +
       "cover the hill.\n");
    add_item(({"rocks", "megalithic rocks", "megaliths"}), 
        "There are megalithic rocks, some as small as a horse, others as big "+
        "as a house, scattered across the moors as if by a giant's hand.\n");
    add_item(({"moor", "moorland"}), "Rugged and beautiful, with craggy "+
        "rocks and water-logged soil draped in heather and ice, this "+
        "moorland has a dreamy, surreal quality.\n");		
    add_exit("moor4", "south", 0);
    
    add_npc(MOBDIR+"troll", 4);

    set_up_herbs( ({ ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                  }),
                  ({"bushes","shrubs","hill"}) , 
                   3 );

    add_cmd_item(({"pebble","pebbles"}),
                 ({"collect","gather","get"}),"@@get_pebble");

    
    reset_room();
}


mixed
get_pebble()
{
    if (pebbles == 0) {
        return "You can't seem to find a nice pebbles.\n";
    }

    seteuid(getuid(TO));
    object pebble = clone_object(CALATHIN_DIR + "houses/obj/pebble");
    pebble->move(TP, 1);
    pebbles--;

    write("You pick up a pebble from the ground.\n");
    say(QCTNAME(TP) + " reaches down and picks up a pebble.\n");
    return 1;
}

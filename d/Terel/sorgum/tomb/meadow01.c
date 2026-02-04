inherit "/std/room";
inherit "/d/Terel/std/herbsearch.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/include/Terel.h"     
#include "/d/Terel/include/herb_arrs.h"
#include <cmdparse.h>
#include <ss_types.h>
#include <composite.h>


#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])
#define TOMBDIR "/d/Terel/sorgum/tomb/"

create_room()
{
    set_short("breezy meadow");
    set_long(
        "A huge green sea of tall grass ripples and sways under a steady " +
        "frigid breeze.  Evergreens are mounted steeply toward glistening " +
        "snow-capped peaks which tower in the distance.  Birds swoop and " +
        "spiral among the tall column-like trunks of the evergreens.\n");

    add_item(({"grass"}),"Tall grass grows through the patches of snow.\n");

    add_item(("evergreens"),"Like tall sentinels they stand along the " +
       "edges of the meadow.\n");

    add_item(({"bird", "birds"}), 
        "They fly by too fast for you to get a good look at them.  Some of " +
        "them look kind of like bats though.\n"
    );
    
    add_prop(ROOM_I_INSIDE, 0);

    set_up_herbs( ({ ONE_OF_LIST(PLAINS_HERBS),
                     ONE_OF_LIST(PLAINS_HERBS),
                     ONE_OF_LIST(FOREST_HERBS),
                  }),
                  ({"tall grass", "grass", "evergreens"}) , 
                   3 );


    add_exit(TOMBDIR + "path02", "north", 0);
    add_exit(TOMBDIR + "meadow02", "east", 0);    
    
}



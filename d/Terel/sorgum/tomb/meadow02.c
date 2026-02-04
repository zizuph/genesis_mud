#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])
#define TOMBDIR "/d/Terel/sorgum/tomb/"

init()
{
     ::init();
     add_action("do_climb", "climb");
}

create_room()
{
    set_short("tree meadow");
    set_long(
        "An immense tree stands in solitude in the middle of this broad " +
        "meadow.  The trunk is larger than a small house and its widespread " +
        "braches shadow yards of the underlying meadow.  The powerful roots " +
        "reach deep down into the heart of Terel.  In the distance scrubby " +
        "trees stand out green against the snowfields of the higher " +
        "mountains.  To the east the meadow opens up into a moor.\n" 
    );

    add_prop(ROOM_I_INSIDE, 0);

    add_item("trunk", "It's as large as a small house.\n");


    add_item(({"tree", "trees"}), 
        "It's one of the largest trees you have ever seen.\n"
    );


    add_item(({"branch", "branches"}),
        "The smaller branches are as thick as normal tree trunks.  The " +
        "larger branches reach out across the vast meadow like open arms.\n");

    add_item(({"mountain", "mountains"}), 
        "They loom in the distance.  One of them looks like it might be " +
        "a volcano.\n");

    add_item("moor", "The moor is ice coated and hauntingly beautiful.\n");

    add_item(({"snowfield", "snowfields"}), 
        "Large and white they can be seen on the crest of the distant " +
        "mountains.\n");

   set_up_herbs( ({TER_HERB + "whitehorn"}),
                 ({"tree","branch","branches","trees"}) , 
                  3 );
    
    add_exit(TOMBDIR + "meadow01", "west", 0);
    add_exit(TEREL_DIR + "common/moor/moor4", "east", 0);    
   
    reset_room();
}

do_climb(string str)
{
     notify_fail("Climb what?\n");
     if (str == "tree") {
          write("The tree is so large you can't manage to climb it.\n");
          return 1;
     }
     return 0;
}


/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * str_hld.c 
 *
 * Dwarven Stronghold
 * Tomas  -- Jan. 2000
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

inherit STDROOM;


public void
create_room()
{
    ::create_room();
    set_short("West field");
    set_long("You are standing on a rocky field which extends further north. "+
       "A cobblestone road can be seen to the east and south of here. " +
       "A large metal gate can be seen to the southwest.\n");

    add_item(({"rock","pass","cliffs","cliff","walls"}),
       "The pass looks as if it was carved out of solid rock presumably " +
       "by dwarven hands. The tall cliffs rise up on either side of the " +
       "the field and road. Covered catwalks run the length of the cliffs " +
       "on either side.\n");

    add_item(({"catwalk","catwalks"}),
       "The catwalks extend the length of the cliffs on either side of " +
       "the pass.\n");

    add_item(({"snow","debris"}),
       "The area is void of any debris or snow. The dwarves make sure " +
       "that the fields and road are clear.\n");

    add_item(({"field","fields","road","cobblestone road","cobblestones",
               "cobblestone","stone","stones"}),
       "The rocky fields make up for the floor of the pass. The dwarves " +
       "built a road out of stones fit tightly together of which runs between " +
       "the northern and southern gates.\n");

    add_exit(MOUNTAIN_DIR + "stronghld/fieldi","north",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fielde","south",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/roadd","east",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/roadc","southeast",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/roade","northeast",0,1);
    
     reset_room();

}



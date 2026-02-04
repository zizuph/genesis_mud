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
    set_short("Pass");
    set_long("The road continues north and south here. The catwalks " +
       "can be seen atop the sheer cliff walls above the rocky fields " +
       "to the west and east.\n");

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
  
    add_item(({"gates","gate","southern gate","northern gate"}),
       "The massive gates can be seen north and south of the pass.\n");

    add_exit(MOUNTAIN_DIR + "stronghld/roadc","north",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/roada","south",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fieldc","west",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fieldd","east",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fielde","northwest",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fieldf","northeast",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fielda","southwest",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fieldb","southeast",0,1);
    
     reset_room();

}



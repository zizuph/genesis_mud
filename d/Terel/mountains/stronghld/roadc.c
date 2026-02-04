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

object warrior1;
object warrior2;
object warrior3;
object warrior4;

public void
reset_room()
{

/*
    if (!warrior1) {
        warrior1=clone_object(MOUNTAIN_DIR + "stronghld/npc/lancer_leader");
        warrior1->move(this_object());
    }

    if (!warrior2) {
        warrior2=clone_object(MOUNTAIN_DIR + "stronghld/npc/dwarven_lancer");
        warrior2->move(this_object());
        warrior1->team_join(warrior2);
    }

    if (!warrior3) {
        warrior3=clone_object(MOUNTAIN_DIR + "stronghld/npc/dwarven_lancer");
        warrior3->move(this_object());
        warrior1->team_join(warrior3);
    }

    if (!warrior4) {
        warrior4=clone_object(MOUNTAIN_DIR + "stronghld/npc/dwarven_lancer");
        warrior4->move(this_object());
        warrior1->team_join(warrior4);
    }
*/
 
}



public void
create_room()
{
    ::create_room();
    set_short("Cobblestone road");
    set_long("The road continues between the gates which arenorth and " +
       "south from here. The road branches off leading west towards " +
       "a large metal gate to the west. The catwalks " +
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
  
    add_item(({"gates","gate"}),
       "A large metal gate can be seen beyond the fields to the west.\n");

    add_exit(MOUNTAIN_DIR + "stronghld/roadd","north",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/roadb","south",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fielde","west",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fieldf","east",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fieldg","northwest",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fieldh","northeast",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fieldc","southwest",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fieldd","southeast",0,1);

    add_npc(MOUNTAIN_DIR + "stronghld/npc/dwarven_lancer",4,0);
    
     reset_room();

}



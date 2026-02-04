/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 *
 * Dwarven Stronghold
 * Tomas  -- Jan. 2000
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>

inherit STDROOM;
inherit MOUNTAIN_DIR + "stronghld/catwalk";

public string exa_ngate();
object warrior1;
object warrior2;


#define DEFAULT  "/d/Terel/mountains/stronghld/"
#define GATE        ({ DEFAULT + "in_north_gate", \
                       DEFAULT + "north_gate", \
                                })


reset_room()
{
    if (!warrior1) {
        warrior1=clone_object(MOUNTAIN_DIR + "stronghld/npc/std_dwf_warrior");
        warrior1->move(this_object());
    }

    if (!warrior2) {
        warrior2=clone_object(MOUNTAIN_DIR + "stronghld/npc/std_dwf_warrior");
        warrior2->move(this_object());
    }

    if ((warrior1) && (warrior2))
        warrior1->team_join(warrior2);
}



public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("Catwalk");
     set_long("The catwalk runs along atop the northern wall continuing " +
       "east and west. From here you have an excellent view of the " +
       "fields within the stronghold. To the north is a platform " +
       "extending over the inner-gate to the main gate.\n");


    add_item(({"platform"}),"To the south is a wide platform " +
       "just above the inner-gate, extending over the entranceway " +
       "to the main gate. Heavy machinery can be seen above the " +
       "gates.\n");

    add_item(({"windless","machinery"}),
       "A huge windless sits upon an iron platform just above " +
       "the southern gates. Large strong looking chains run " +
       "through holes on either side of the windless wrapping " +
       "around giant wheels on either side of the windless. " +
       "You dont see anyone around the windless so it must " +
       "be controlled from from someplace else.\n");

    add_item(({"chains","strong looking chains",
               "counter weights","weights","large chains"}),
       "The iron chains look very strong. Each link is about " +
       "the size of a mans head. The chains extend " +
       "through holes in the platform and connect to " +
       "massive counter weights inside the gate.\n");

    add_item(({"gate","gates"}),"@@exa_ngate");

    add_exit(MOUNTAIN_DIR + "stronghld/walk20","west",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/walk18","east",0,1);

    reset_room();

}

public string
exa_ngate()
{
  object *inv, *live, room;
  int i;

  inv = ({});
  for (i = 0; i < sizeof(GATE); i++)
    if ((room = find_object(GATE[i])))
      inv += all_inventory(room);

  if (sizeof(inv)) {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if (sizeof(live))
      return "  Down on the gate you can see " +
        COMPOSITE_LIVE(live) + " standing there.\n";
  }
  return "  The gate below looks abandoned.\n";
}








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

#define DEFAULT  "/d/Terel/mountains/stronghld/"

#define ROAD        ({ DEFAULT + "roada", \
                           DEFAULT + "roadb",  \
                           DEFAULT + "roadc", \
                           DEFAULT + "roadd", \
                       DEFAULT + "roade", \
                                      })

#define FIELDS      ({ DEFAULT + "fielda", \
                       DEFAULT + "fieldb", \
                       DEFAULT + "fieldc", \
                       DEFAULT + "fieldb", \
                       DEFAULT + "fieldd", \
                       DEFAULT + "fielde", \
                       DEFAULT + "fieldf", \
                       DEFAULT + "fieldg", \
                       DEFAULT + "fieldh", \
                       DEFAULT + "fieldi", \
                       DEFAULT + "fieldj", \
                                 })


public void
create_room()
{
    ::create_room();
    INSIDE;

    set_short("Catwalk");
    set_long("You stand upon the covered stronghold catwalk. The " +
       "catwalk runs along the cliffs, over the main gates to the " +
       "otherside of the mountain From your vantage point, you can " +
       "examine everything that goes on down on the fields and road.\n");

    add_item(("catwalk"),"The catwalk surrounds the the fields and " +
       "road below. The catwalk has been covered with a slanted roof " +
       "to keep the elements out and to provide additional protection " +
       "from arrows or other nasty surprises.\n");

    add_item(({"cliffs","cliff","walls","wall"}),
       "The catwalks run atop the sheer cliffs which look extremely difficult " +
       "to climb as they have been chiseled clean of any footholds.\n");

    add_item(("road"),"@@exa_road");

    add_item(({"fields","field"}),"@@exa_fields");

    reset_room();

}


public string
exa_road()
{
  object *inv, *live, room;
  int i;

  inv = ({});
  for (i = 0; i < sizeof(ROAD); i++)
    if ((room = find_object(ROAD[i])))
      inv += all_inventory(room);

  if (sizeof(inv)) {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if (sizeof(live))
      return "  Down on the road you can see " +
        COMPOSITE_LIVE(live) + " wandering around.\n";
  }
  return "  The road below looks barren.\n";
}


public string
exa_fields()
{
  object *inv, *live, room;
  int i;

  inv = ({});
  for (i = 0; i < sizeof(FIELDS); i++)
    if ((room = find_object(FIELDS[i])))
      inv += all_inventory(room);

  if (sizeof(inv)) {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if (sizeof(live))
      return "  Down in the fields you can see " +
        COMPOSITE_LIVE(live) + " wandering around.\n";
  }
  return "  The fields below look barren.\n";
}

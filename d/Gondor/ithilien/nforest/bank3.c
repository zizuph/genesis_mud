inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

object deer;

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("shallow dell");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar");

    set_extraline("The small stream feeds a small clear lake here. The lake "
      + "lies in the broken ruins of an ancient stone basin, the carven rim "
      + "of which is almost wholly covered with mosses and rose-brambles. "
      + "At the southwestern end of the lake, the water spills ever softly "
      + "out over a stony lip. Sweet odours from herbs and flowers are in "
      + "the air everywhere.");
  add_item(({"mountains","mountain-range","mountain","ephel duath"}),
    "From here the mountains are hidden by trees and the stony ridge to the east.\n");
  add_item(({"forest","wood","woods","herbs","groves","thickets","thicket","grove"}),BS(
    "Many great trees and thick bushes are growing here, planted long ago, falling into untended age amid a riot " +
    "of careless descendants. Between the bushes and under the trees, grasses and herbs are " +
    "growing in abundance. You can make out myrtles, ginger, and irises.\n"));
  add_item(({"stream"}),BS(
    "The small stream comes running down from the east into this shallow dell. Here it enters the " +
    "lake running over the basin's rim in a small waterfall. The water is clear and fresh.\n"));
  add_item(({"flower","flowers","iris-swords","iris","lily","water-lily"}),BS(
    "Iris-swords are standing in ranks about the basin's rim, and water-lily leaves are floating " +
    "on the dark gently-rippling surface of the lake.\n"));
  add_item(({"lake","basin","pool","water"}), BS(
    "The small lake lies in the broken ruins of an ancient stone basin. A small stream running " +
    "down from the east is feeding it. Water-lily leaves are floating on the dark " +
    "gently-rippling surface of the water; but it is deep and fresh, and spills ever softly out " +
    "over a stony lip at the far end.\n"));
    
    set_drink_from( ({ "lake", "basin", "pool", }) );
  add_prop(OBJ_I_CONTAIN_WATER,-1);
  BEACH;

    set_up_herbs( ({ HERB_DIR+"clove", HERB_DIR+"ginger", HERB_DIR+"myrtle",
		     HERB_DIR+"saffron", HERB_DIR+"tarragon", HERB_DIR+"ungolestel", }),
		  ({ "forest","ground","field","flowers","forest"}), 3);

    add_exit(ITH_DIR + "nforest/sstream3", "north","@@cross_stream", 1);
    add_exit(ITH_DIR + "nforest/slake",    "south",     0, 1);
    add_exit(ITH_DIR + "nforest/bank2",    "southwest", 0, 1);

    reset_room();
}

public void
add_stuff()
{
    if (!objectp(deer))
    {
        deer = clone_object(NPC_DIR + "deer");
        deer->set_restrain_path(ITH_DIR + "nforest/");
        deer->move_living("west", TO);
    }
}

public void
reset_room()
{
    set_searched(-2);
    set_alarm(15.0 + 30.0 * rnd(), 0.0, add_stuff);
}

public int
cross_stream()
{
  write("You cross the small stream.\n");
  return 0;
}

public void
init()
{
    ::init();

    init_drink();
}
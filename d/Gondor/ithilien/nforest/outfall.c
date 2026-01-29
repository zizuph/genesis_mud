inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object  buck;

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("small lake");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cypress");

    set_extraline("You are standing at the outlet of the lake east of here. "
      + "Here the water spills over a stony lip, feeding a small stream that "
      + "runs westwards to the Anduin from here. The lake lies in the broken "
      + "ruins of an ancient stone basin, the carven rim of which is almost "
      + "wholly covered with mosses and rose-brambles. Thickets of cypresses "
      + "and dark-leaved bay-trees grow upon the steep banks above the lake.");
  add_item("rim","The rim is skillfully built up of carved stones, many long\n"+
    "years ago. Some stones have been displaced with the years, and\n"+
    "the basin looks disused.\n");
  add_item(({"mountains","mountain-range","mountain","ephel duath"}),BS(
    "From here the mountains named Ephel Duath appear as dark grey shadows beyond the stony ridge to the east. "+
    "You judge the mountains to be between 5000 to 7000 feet tall, "+
    "and you guess they are several kilometers away now.\n"));
  add_item(({"forest","wood","woods","herbs","groves","thickets","thicket","grove"}),BS(
    "Many great trees are growing here, planted long ago, falling into untended age amid a riot " +
    "of careless descendants. There are olive and bay, junipers and mints, " +
    "cedars crowing the steep banks around the lake, and many other herbs of different forms and scents. \n"));
  add_item(({"flower","flowers","water-lily","iris","lily","iris-swords"}),BS(
    "Iris-swords are standing in ranks about the basin's rim, and water-lily leaves are " +
    "floating on the dark gently-rippling surface of the water.\n"));
  add_item(({"stream"}),BS(
    "The lake is fed by a stream running down the ridge hidden by the forest to the east, while " +
    "the stream spills out over a stony lip at the southwest end of the lake.\n"));
  add_item(({"lake","basin","pool","water"}),BS("The lake to the east lies in the broken ruins of an "+
    "ancient stone basin in the dell. Mosses and brambles cover the carven "+
    "rim, and water-lilies are floating on the gently-rippling water. The "+
    "water is constantly renewed by the stream flowing into it from the "+
    "east, while it spills softly out here over a stony lip where the small stream continues westward.\n"));


  add_exit(ITH_DIR + "nforest/bank1","north",0,1);
  add_exit(ITH_DIR + "nforest/bank2","southeast","@@cross_stream",1);
  add_exit(ITH_DIR + "nforest/bank","south","@@cross_stream",1);
  add_exit(ITH_DIR + "nforest/sstream4","west",0,1);
  add_exit(ITH_DIR + "nforest/slope4","northwest",0,1);

    BEACH;
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);

    set_up_herbs( ({ HERB_DIR+"laurel", HERB_DIR+"lothore", HERB_DIR+"saffron",
                     HERB_DIR+"savory", HERB_DIR+"tyelka", HERB_DIR+"ungolestel", }),
                  ({"forest","ground","field","flowers","forest"}), 3);

    set_drink_from( ({"lake", "pool", }) );

  reset_room();
}

public void
add_stuff()
{
    if (!objectp(buck))
    {
        buck = clone_object(NPC_DIR + "buck");
        buck->set_restrain_path(ITH_DIR + "nforest/");
        buck->set_m_in("stalks into view");
        buck->move_living("west", TO);
    }
}

public void
reset_room()
{
    set_searched(-2);
    set_alarm(30.0 + rnd() * 60.0, 0.0, add_stuff);
}

public string
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


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
    set_extraline("You are standing north of a small clear lake in a shallow "
      + "dell. It lies in the broken ruins of an ancient stone basin, the "
      + "carven rim of which is almost wholly covered with mosses and "
      + "rose-brambles. Iris-swords stand in ranks about it, and water-lily "
      + "leaves are floating on its dark gently-rippling surface, but the "
      + "lake is deep and fresh, and spills ever softly over a stony lip at "
      + "the west end. A small stream pours into the lake from the east, and "
      + "thickets of cypresses and dark-leaved bay-trees grow upon the steep "
      + "banks above the lake.");
    set_up_herbs( ({ HERB_DIR+"ungolestel", HERB_DIR+"lothore", HERB_DIR+"tuo",
                     HERB_DIR+"tarragon", HERB_DIR+"saffron", HERB_DIR+"laurel",
                     HERB_DIR+"clove", HERB_DIR+"thyme", }),
                  ({ "forest","ground","field","flowers", }), 3);
    set_drink_from( ({"lake"}));

    add_item("rim", BSN("The rim is skillfully built up of carved stones, "
      + "many long years ago. Some stones have been displaced with the years, "
      + "and the basin looks disused."));
    add_item(({"mountains","mountain-range","mountain","ephel duath"}),BSN(
        "From here the mountains named Ephel Duath appear as dark grey "
      + "shadows beyond the stony ridge to the east. You judge the mountains "
      + "to be between 5000 to 7000 feet tall, and you guess they are several "
      + "kilometers away now."));
  add_item(({"forest","wood","woods","herbs","groves","thickets","thicket","grove"}),BS(
    "Many great trees are growing here, planted long ago, falling into untended age amid a riot " +
    "of careless descendants. There are olive and bay, junipers and myrtles, and thymes growing in bushes; " +
    "and mints and many other herbs of different forms and scents. \n"));
  add_item(({"flower","flowers","water-lily","iris","lily","iris-swords"}),BS(
    "Iris-swords are standing in ranks about the basin's rim, and water-lily leaves are " +
    "floating on the dark gently-rippling surface of the water.\n"));
  add_item(({"stream"}),BS(
    "The lake is fed by a stream running down the ridge hidden by the forest to the east, while " +
    "the stream spills out over a stony lip at the southwest end of the lake.\n"));
  add_item(({"lake","basin","pool","water"}),BS("The lake is in the broken ruins of an "+
    "ancient stone basin in the dell. Mosses and brambles cover the carven "+
    "rim, and water-lilies are floating on the gently-rippling water. The "+
    "water is constantly renewed by the stream flowing into it from the "+
    "east, while it spills softly out over a stony lip at the southwest end.\n"));
  add_exit(ITH_DIR + "nforest/slope2","north",0,1);
  add_exit(ITH_DIR + "nforest/slope","east",0,1);
  add_exit(ITH_DIR + "nforest/sstream3","southeast",0,1);
  add_exit(ITH_DIR + "nforest/bank1","southwest",0,1);
  add_exit(ITH_DIR + "nforest/slope3","west",0,1);
  BEACH;
  add_prop(OBJ_I_CONTAIN_WATER,1);
  reset_room();
}

public void
add_stuff()
{
    if (!objectp(buck))
    {
        buck = clone_object(NPC_DIR + "buck");
        buck->set_restrain_path(ITH_DIR + "nforest/");
        buck->move_living("down", TO);
    }
}

public void
reset_room()
{
    set_searched(-2);

    set_alarm(30.0 + 60.0 * rnd(), 0.0, add_stuff);
}

public void
init()
{
    ::init();
    init_drink();
}


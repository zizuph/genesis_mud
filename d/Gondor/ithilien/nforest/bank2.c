#pragma strict_types
inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object *rabbit = allocate(2 + random(3));

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("shallow dell");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cypress");
    set_extraline("You are standing south of a small clear lake. It "
      + "lies in the broken ruins of an ancient stone basin, the "
      + "carven rim of which is almost wholly covered with mosses and "
      + "rose-brambles. A ring scorched by fire is half hidden by recent "
      + "growth of briar and eglantine and trailing clematis. Thickets of "
      + "cypresses and dark-leaved bay-trees grow upon the steep banks above "
      + "the lake.");
    set_up_herbs( ({ HERB_DIR+"basil", HERB_DIR+"caraway", HERB_DIR+"chervil",
		     HERB_DIR+"laurel", HERB_DIR+"saffron", HERB_DIR+"tuo",
		     HERB_DIR+"tyelka", }),
		  ({ "forest", "wood", "grove", "thicket", }),  3);
    set_drink_from( ({"lake"}) );
  add_item("rim","The rim is skillfully built up of carved stones, many long\n"+
    "years ago. Some stones have been displaced with the years, and\n"+
    "the basin looks disused.\n");
  add_item(({"mountains","mountain-range","mountain","ephel duath"}),BS(
    "From here the mountains named Ephel Duath appear as dark grey shadows beyond the stony ridge to the east. "+
    "You judge the mountains to be between 5000 to 7000 feet tall, "+
    "and you guess they are several kilometers away now.\n"));
  add_item(({"forest","wood","woods","herbs","groves","thickets","thicket","grove"}),BS(
    "Many great trees are growing here, planted long ago, falling into untended age amid a riot " +
    "of careless descendants. There are olive and bay, parsleys and mints, " +
    "and many other herbs of different forms and scents.\n"));
  add_item(({"flower","flowers","water-lily","iris","lily","iris-swords"}),BS(
    "Iris-swords are standing in ranks about the basin's rim, and water-lily leaves are " +
    "floating on the dark gently-rippling surface of the water.\n"));
  add_item(({"stream"}),BS(
    "The lake is fed by a stream running down the ridge hidden by the forest to the east, while " +
    "the stream spills out over a stony lip here at the southwest end of the lake " +
    "to continue on its course towards the Anduin.\n"));
  add_item(({"lake","basin","pool","water"}),BS("The lake is in the broken ruins of an "+
    "ancient stone basin in the dell. Mosses and brambles cover the carven "+
    "rim, and water-lilies are floating on the gently-rippling water. The "+
    "water is constantly renewed by the stream flowing into it from the "+
    "east, while here it spills softly out over a stony lip.\n"));
  add_item(({"scorched ring","ring", "briar", "eglantine", "clematis"}), BS(
    "Swift growth of the wild with briar and eglantine and trailing clematis is drawing " +
    "a veil over a ring scorched with fire. In its midst, there is a pile of charred and " +
    "broken bones and skulls. The slaughter must have been rather recent, evidently orcs " +
    "held a terrible feast here.\n"));
  add_item(({"ring","campfire","stones"}),BS(
    "Stones have been laid in a ring on the ground, and a campfire "+
    "has been burned within, charring the plants that were too close. "+
    "The burned-down fire reminds you of your ever-present peril as you "+
    "travel through the lands of Ithilien, so close to Mordor. In the midst "+
    "of the ring you see a pile of charred and broken bones and skulls. " +
    "Swift growth of the wild with briar and eglantine and trailing clematis " +
    "is already drawing a veil over the place, but the slaughter must have been " +
    "rather recent. " +
    "\n"));
  add_item(({"bones","skulls","pile"}), BS(
    "There are several broken bones and skulls in a pile in the remains of the "+
    "campfire. Guessing the skulls are of humans, you realize that orcs "+
    "held a terrible feast here." +
    "\n"));
    add_exit(ITH_DIR + "nforest/bank3",   "northeast", 0, 1);
    add_exit(ITH_DIR + "nforest/slake",   "east",      0, 1);
    add_exit(ITH_DIR + "nforest/bank",    "west", 0, 1);
    add_exit(ITH_DIR + "nforest/outfall", "northwest", "@@cross_stream", 1);
    BEACH;
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    reset_room();
}

public void
clone_rabbit()
{
    int     i, s;

    for (i = 0, s = sizeof(rabbit); i < s; i++)
	if (!objectp(rabbit[i]))
        {
            rabbit[i] = clone_object(NPC_DIR + "rabbit");
            rabbit[i]->set_restrain_path(ITH_DIR + "nforest/");
	    rabbit[i]->set_m_in("hops into view");
            rabbit[i]->move_living("south", TO);
	    set_alarm(30.0 + rnd() * 60.0, 0.0, clone_rabbit);
	    return;
        }
}

public void
reset_room()
{
    set_searched(-2);

    set_alarm(30.0 + rnd() * 60.0, 0.0, clone_rabbit);
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


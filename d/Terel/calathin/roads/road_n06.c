/* silv_n_r3.c */
 
/* metaprat - 920622 */

/* Road from northern edge to centre. Connects with forest. */

/* Northern edge of Silvoria, where it intersects with the south of */
/* the forest.  Lightly inhabited here, some trees.  Descs taken    */
/* from Vader's forest, for consistency.                            */
/* Updated and changed to road_n6.c by Shinto 10-24-98 */

/* road_n6.c */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

void
reset_room()
{
     object citizen;

     if (present("citizen"))return;

     citizen=clone_object(CALATHIN_DIR + "npc/std_citizen.c");
     citizen->move(this_object());

}

public void
create_room() 
{
    set_short("Road through Silver Forest");
    set_long(
      "You are on a road through a large pine forest.  Towards the south, " +
      "you can see the tops of several buildings, just beyond a huge tree " +
      "in the distance.  Further north, the forest is much denser than it " +
      "is now, with the snowy trees glistening in the sunlight.\n" +
      "Several trees to your east and west prevent you from leaving the " +
      "road, but past them you can see glimpses of wooden houses.\n");

    add_item(({"trees", "tree"}), "They are tall and green.  Pine trees "
        + "often do well in the cold.\nThey are covered with snow in such a "
        + "way that the light reflected off\nof them gives it a silver color.\n");

    add_item( ({ "huge tree" }), "The tree looks like an ancient pine, about " +
           "100 meters tall or more.\n");

    add_item( ({ "houses", "house" }), 
        "It's hard to tell past the trees, but "+
        "the houses to the east look\nsomewhat delapidated.\n");

    add_item( ({ "buildings" }), "You can see some snowy roofs, but that's " +
      "all from this distance.\n");

    add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");

    add_item( ({ "snow" }),
      "There isn't much actual snow here, its all been trodden into the " +
      "ground by the locals.  Off the road, there are several areas " +
      "covered with icy snow.\n");

    add_item( ({ "ground", "footprint", "footprints", "trail", "road", "path"}),
      "Deeply frozen for the entire year, the ground never holds footprints. "+
      "However, the pattern of erosion from all the feet walking on it over " +
        "years, clearly shows a road leading between the north and south.\n");


    add_exit(CALATHIN_DIR + "roads/road_n07", "north", 0);
    add_exit(CALATHIN_DIR + "roads/road_n05", "south", 0);

    reset_room();
}

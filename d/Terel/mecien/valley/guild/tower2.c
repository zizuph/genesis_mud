/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/guild/"

object mon;
create_room(){

set_short("Tower");
set_long("This round chamber is draped with grey tapestries and lit\n"
    +"by a small white candle. The candle rests in a tall silver\n"
    +"candlestick that is set into the floor.\n");

add_item("tapestries", "They are simple grey tapestries.\n");
add_item("candle", "It is a small white beeswax candle.\n");
add_item("candlestick", "It is a tall spiral candlestick that has been\n"
  +"set into the floor. It stands about five feet high.\n");
add_cmd_item("candle", ({"dowse", "blow out"}), "It is not possible.\n");
add_cmd_item("candle", "light", "It is already lit.\n");

add_my_desc("A spiral set of stairs leads up and down.\n");
add_item(({"stairs", "staircase"}), 
  "The steps are a dark slate, but very strong.\n");

add_item("walls", "They are made from small round grey stones.\n");

add_exit(PATH + "tower3", "up", 0);
add_exit(PATH + "tower1", "down", 0);

seteuid(getuid());
mon = clone_object(PATH + "chante");
mon->move(this_object());

}



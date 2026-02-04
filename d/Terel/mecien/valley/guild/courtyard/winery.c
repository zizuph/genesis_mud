/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/guild/courtyard/"

create_room(){
object door, press;

set_short("Winery");
set_long(
"The smell of wine permeates everything here. Rising high, this old\n" +
"stone building is constructed inside of a rich dark wood. A huge loft is\n"
+"supported by great beams and rafters. Huge kegs and barrels are stored along\n"
+"the edge of the loft, displaying many years of work. A staircase\n"
+"leads up into the loft.\n"
);

add_item(({ "kegs", "barrels"}), 
  "Stored up in the loft, they display the work of ages.\n");
add_item("rafters", "They support the loft and roof.\n");
add_item("beams", "They support the loft and roof.\n");
add_item("staircase", "it leads up into the loft.\n");
add_item("loft", "It circles the winery, holding many kegs and "
  + "barrels.\n");
add_item("roof", "It is high above.\n");

add_exit(PATH + "loft", "up", "@@closed");

  set_noshow_obvious(1);
press=clone_object(PATH + "press");
press->move(this_object());
door=clone_object(PATH + "wd2");
door->move(this_object());

}

closed(){
write("The loft has been closed off.\n");
return 1;
}


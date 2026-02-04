inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/"

create_room(){

set_short("Lake View");
set_long(
"Stretching out through the valley, a beautiful crystal blue lake\n"
+"rests quietly against the edges of the forests. The waters seem\n"
+"calm and gentle, despite the amount of wind. Tall willows grow here\n"
+"and form a dense copse to the south. The ground here and about the lake\n"
+"is covered with small white stones. A beautiful dock stands at the\n"
+"edge of the water, to the north.\n"
);

add_item("lake", "It is a huge lake of mountain water, cold and fresh.\n");
add_item("dock", "It is of beautiful silver and white wood. It stand\n"
  + "north from here at the waters edge.\n");
add_item("stones", "They are small and white, seem to be naturally\n"
  +"accouring about the waters edges.\n");
add_item("willows", "Old drooping trees, of glorious majesty. They\n"
   +"canopy the ground with their long branches.\n");
add_exit(PATH + "lake/dock1", "north", 0);
add_exit(PATH + "copse3", "south", 0);

}


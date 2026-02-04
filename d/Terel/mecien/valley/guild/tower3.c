/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){

set_short("Tower");
set_long("A small grey table and chairs adorn this small circular\n"
   +"stone hall of the tower. A silver banner hangs from the wall\n"
   +"just over the table.\n");

add_my_desc("A spiral set of stairs leads up and down.\n");
add_item("stairs", "The steps are slate, but very strong.\n");

add_item("walls", "They are made from small round grey stones.\n");

add_item("banner", "It is a huge silver banner.  There is an image\n"+
  "on the banner, but it appears to move as you look closer.\n");
add_item("image", "You can't quite make out what the image is.\n");
add_item(({"table", "chairs", "chair", "table and chairs"}),
  "The table and chairs look remarkably like a very small dining table.\n" +
  "Only they are deviod of all items and markings.\n");
add_exit(PATH + "bt", "up", 0);
add_exit(PATH + "tower2", "down", 0);

}



inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/sf/"

create_room(){
set_short("Forest");
set_long(
"All about the trees rise up, mighty and majestic. Their leaves only\n"
+"now beginning to appear. Small flowers coat many of the vivid green\n"
+"of the trees, bringing is life in abundance. The canopy of the forest\n"
+"buzzes with activity. The forest floor is coated with early blooms and\n"
+"small shrubs that grow out of the moss.\n"
);

  add_exit(PATH + "f3", "north", 0);
  add_exit(PATH + "fe", "south", 0);

add_item("canopy", "It sparkles green with life, filled with small rodents and insects.\n");
add_item("moss", "It is a thick carpet of light green moss.\n");
add_item("blooms", "Small flowers that have sprung up in the moist ground.\n");
add_item("flowers", "Many of the trees have small flowers that are in bloom.\n");
add_item("shrubs", "There are many tiny shrubs that have just begun to grow.\n");

}


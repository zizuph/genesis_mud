inherit "/std/room";

create_room(){
set_short("Briar Patch");
set_long(
"This is a monstrous briar patch. It grows up with twisted thorns and\n"
+"hedges of wild pricking brambles, spreading out northward. It melts into\n"
+"the forest to the south.\n"
);

add_exit("/d/Terel/mecien/valley/sf/f4", "southeast", 0);

add_item("thorns", "They are sharp and dangerous.\n");
add_item("brambles", "They are thick and impassable.\n");

}

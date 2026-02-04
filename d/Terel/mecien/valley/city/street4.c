inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/city/"

create_room(){

set_short("Street");
set_long(
"Along this foggy northern street of cobblestone, a beautiful oak\n"
+"building stands, westward. Over it hang a white sign. A darker\n"
+"stone edifice stands eastward, an iron sign hangs over it, creaking\n"
+"in the wind. The street runs north, to the south the square opens out.\n"
);

add_exit(PATH + "post", "west", 0);
add_exit(PATH + "square", "south", 0);
add_exit(PATH + "street5", "north", 0);
add_exit(PATH + "armory", "east", 0);

add_item("white sign", "It is made of white stone and engraved.\n");
add_cmd_item(({"sign", "white sign"}), "read", "Postal Station\n");
add_item("iron sign", "Of wrought black iron, engraved with runic letters.\n");
add_cmd_item(({"sign", "iron sign"}), "read", "The Elnoven Armory\n");

}


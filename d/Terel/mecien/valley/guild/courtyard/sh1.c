/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/guild/courtyard/"

create_room(){

object door;

set_short("Garden");
set_long(
"Hedges of deep evergreen grow up here, wavering in the breeze\n"
+"like waves on the sea. The outer wall of the shrine encompasses\n"
+"the garden in its warding mantle, rising above the hedges to the\n"
+"south and west. A small wooden building stands here, open and\n"
+"inviting. A small patch of white flowers grow in a bed in front\n"
+"of the building.\n"
+"A small path leads through the hedges northeast.\n");

add_item(({"hedges", "evergreen", "evergreens"}), 
  "Thick hedges of holly, juniper and yew.\n");
add_item("wall", "It is an ancient stones wall. It encompasses the\n"
  + "shrine courtyard.\n");
add_item(({"building", "shed"}), "It is a small shed, made from a deep\n" +
  "rich red coloured wood.\n");
add_item("bed", "It is a small wooden box area that sits in front\n"
  + "of the shed, in which flowers grow.\n");
add_item(({"patch", "flowers", "flower"}),
"A patch of white flowersthat grow up before the shed, in a wooden\n"
+"bed prepared for them. The flowers are white and aromatic.\n");
add_cmd_item(({"flower", "flowers"}), "smell", "They smell spicy " +
                                               "and sweet.\n");

door=clone_object(PATH + "sd1");
door->move(this_object());
door->set_key(7282);

add_exit(PATH + "rg", "northeast", 0);

}



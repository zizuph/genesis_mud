/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/guild/crypt"

create_room(){
object door;

set_short("Crypt Foyer");
set_long(
  "Shadowy and haunted stone, this arched hall is the entry\n"
  +"foyer to an immense crypt. The stone is gray and black,\n"
  +"smooth and somewhat dilapidated. The vaulted ceiling has\n" 
  +"been inscribed with runes and symbols.\n"
);
  add_item("ceiling", "It is vaulted, very dark and inscrived with symbols.\n");
  add_item(({"runes", "symbols"}), "They are runes and symbols of the dead.\n");
  add_cmd_item(({"runes", "symbols"}), "read",
    "As you start to read the runes, you are suddenly filled\n" + 
    "with a dread of the dead.  You stop reading very abruptly.\n");

  add_exit(PATH + "/c1", "west", 0);

door=clone_object(PATH + "/cdoor2");
door->move(this_object());

}


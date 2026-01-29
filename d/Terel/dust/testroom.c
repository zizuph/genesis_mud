inherit "/std/workroom";

create_workroom()
{
  object board;
  set_short("Chamber of Terel");
  set_long("A place of solemnity and austere discipline. This dark\n"
    + "hall is the workplace of the wizards of Terel. The walls are\n"
    + "enormous blocks of blackened stone, they form a vaulted ceiling\n"
    + "that houses a diamond shaped skylight. The floor is set with a\n"
    + "silvery mosaic. The mosaic depicts a fiery serpent intertwined\n"
    + "with a gleaming white four-pointed star.\n");
  board=clone_object("/d/Terel/common/board");
  board->move(this_object());
  add_exit("/d/Terel/dust/door_room", "west", "@@testcall");
  add_exit("/d/Terel/dust/hint_room4", "north", 0);
  add_exit("/d/Genesis/start/human/town/church", "church", 0);
  add_exit("/d/Terel/mecien/valley/guild/guild", "mystic", 0);
  add_exit("/d/Genesis/wiz/post", "post", 0);
}

testcall()
{
    object o;
    o = clone_object("/doc/examples/obj/gem");
    return 0;
}


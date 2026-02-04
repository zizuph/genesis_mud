inherit "/std/workroom";

create_workroom()
{
  object pic1, pic2, board;
  set_short("Chamber of Terel");
  set_long("A place of solemnity and austere discipline. This dark\n"
    + "hall is the workplace of the wizards of Terel. The walls are\n"
    + "enormous blocks of blackened stone, they form a vaulted ceiling\n"
    + "that houses a diamond shaped skylight. The floor is set with a\n"
    + "silvery mosaic. The mosaic depicts a fiery serpent intertwined\n"
    + "with a gleaming white four-pointed star.\n"
    );
  board=clone_object("/d/Terel/common/board");
  board->move(this_object());
  pic1=clone_object("/d/Terel/pic_metaprat");
  pic1->move(this_object());
  pic2=clone_object("/d/Terel/pic_om");
  pic2->move(this_object());
  add_exit("/d/Genesis/start/human/town/church", "church", 0);
  add_exit("/d/Terel/mecien/valley/guild/guild", "mystic", 0);
  add_exit("/d/Genesis/wiz/post", "post", 0);
  add_exit("/d/Terel/common/domain_entr", "north", 0);
  add_exit("/d/Terel/common/ruins/rmeet", "ruins", 0);
}

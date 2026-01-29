inherit "/d/Kalad/room_std";
inherit "/d/Kalad/common/central/library/librarian";
#include "/d/Kalad/defs.h"

create_room()
{
   /* No bell in here! Too noisy! */
   INSIDE;
   set_short("Books acceptance room");
   set_long("This is where you accept books. There is a small sign "+
      "placed here, maybe it has instructions?\n");
   add_cmd_item("sign","read","To use the library you can "+
      "'add_book <bookname>' to add a book or "+
      "'toss <bookname>' to destroy a book. To "+
      "see what is in the librarians box you can "+
      "'list books'. If you would like to read a "+
      "book before approving it, use 'read <bookname>'.\n");
   
   add_item(({"sign"}),"Hey Stupid! Signs are to be read! Not examined!\n");
   
   add_exit("/d/Kalad/antharanos/workroom","antharanos",0,-1,-1);
   set_lsave("/d/Kalad/common/central/library/bookroom");
   set_lib("/d/Kalad/common/central/library/libr");
   config_librarian();
   reset_room();
   
}
reset_room()
{
}
init()
{
   ::init();
   init_lib();
   
}

inherit "/std/room.c";
inherit "/d/Roke/gresolle/open/librarian";
#include <stdproperties.h>
#include "/d/Kalad/defs.h"

create_room()
{
   set_short("Books acceptance room.");
   set_long("This is where you accept books. There is a small sign "+
            "placed here, maybe it has instructions?\n");
   add_cmd_item("sign","read","To use the library you can "+
                "'add_book <bookname>' to add a book or "+
                "'toss <bookname>' to destroy a book. To "+
                "see what is in the librarians box you can "+
                "'list books'. If you would like to read a "+
                "book before approving it, use 'read <bookname>'.\n");

   add_item("sign","I find it hard to believe you are so incredibly "+
            "stupid that you cannot even figure out that signs are "+
            "supposed to be read!!!! And they thought my add_items "+
            "are too much like a flame. <smirk>. Feel free to change "+
            "any or all of this.\n");

   add_exit("/d/Kalad/milashk/workroom2","north");
   set_lsave("/d/Kalad/common/wild/pass/guild/common/bookroom");
   set_lib("/d/Kalad/common/wild/pass/guild/common/libr");
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


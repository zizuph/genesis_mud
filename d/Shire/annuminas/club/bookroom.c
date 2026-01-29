inherit "/std/room.c";
inherit "/d/Roke/gresolle/open/librarian";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

create_room()
{
   set_short("Books acceptance room.");
   set_long("Unless you are a Shire wizard, do not even think about "+
            "touching the books in here. You notice a sign on the "+
            "wall.\n");
   add_item("sign", "Just read the dern thing, will ya?\n");
   add_cmd_item("sign", "read", "It reads:\n"
              + "Use 'add_book <bookname>' to add a book to the library.\n"
              + "Use 'toss <bookname>' to junk a book.\n"
              + "Use 'list books' to see the books that are waiting.\n"
              + "Use 'read <bookname>' to read a suggested book.\n");
    set_lsave(ANNUM_DIR+"club/bookroom");
   set_lib(ANNUM_DIR+"club/librm");
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


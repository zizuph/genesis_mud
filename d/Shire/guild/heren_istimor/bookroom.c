
#pragma save_binary

inherit "/std/room.c";
inherit "/d/Roke/gresolle/open/librarian";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "heren_istimor.h"

create_room()
{
   set_short("Books acceptance room");
   set_long("	This is where books are approved or disapproved for "+
            "the hobbit library. If you are not a Shire wizard then "+
            "keep your filthy paws off these books!\n");
 
   set_lsave(HEREN_ISTIMOR_DIR+"bookroom");
   set_lib(HEREN_ISTIMOR_DIR+"libraryroom");
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

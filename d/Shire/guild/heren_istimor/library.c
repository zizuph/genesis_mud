#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include "heren_istimor.h"

inherit SHIRE_ROOM;
inherit "/lib/library";

void
create_shire_room()
{
    set_short("A place of learning and scholarship.");
    set_long("Here, among the branches, in the many nooks and crannies "+
      "naturally made by the tree is a place where many scrolls "+
      "and small books are kept.  A leather cover covers those "+
      "places where rain is apt to seep in, but on the whole the "+
      "scrolls are left to the open air, as copies are constantly being "+
      "made by junior Heralds.  The main tree branch that led here, also "+
      "ends here.  A sign posted to the tree will "+
      "give further information.\n");

    add_item(({"branches","nooks","crannies","nook","cranny"}),
      "The branches twisting upward and every which way make many "+
      "convenient cubby-holes for putting scrolls and small books.\n");

    add_item(({"scroll","scrolls","book","small book","books"}),
      "The scrolls and books can be listed by doing: list.\n");

    add_item(({"leather cover","cover","covers","leather covers"}),
      "The leather covers protect from direct sunlight as well as "+
      "water damage.\n");

    add_item(({"branch","tree branch","main tree branch"}),
      "The strong main tree branch that leads to the main trunk "+
      "goes southeast of here back to a meeting of the ways.\n");

    add_item("sign", "It has writing which should be read, not "+
      "merely examined.  As signs go, it is a nice one.\n");
    add_cmd_item("branch", "sit on", "You sit back and relax in one "+
      "of the most comfortable chairs in the room.\n");

    set_book_directory(HEREN_ISTIMOR_DIR + "library/accepted/");
    set_book_approval_directory(HEREN_ISTIMOR_DIR + "library/waiting/");
    set_borrow_required(1);

    create_library();

    add_item("sign", library_help());
    add_cmd_item("sign","read",
      library_help());
}

void
init()
{
    ::init();
    init_library();
}

public int
library_write_access()
{
    return 1;
}

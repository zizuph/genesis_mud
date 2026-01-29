#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit DWARF_OUT;

void
reset_dwarf_room()
{
    return;
}

create_dwarf_room()
{
    set_short("The office in the brewery");
    set_long("The neat office marks the dire love for gold in dwarves. No mistakes in "+
             "establishing business is done here. Bookshelves with accounts of the brewery "+
             "lines the walls. The wellmade table is solid oak, with the loveliest decor "+
             "one could ask for. A large map shows the traderoutes, painted with solid red "+
             "marks. A few reinforced mahognychests stands in the office but noone, except "+
             "for the owner of the key to them, will ever know whats inside. The carpet here "+
             "has the feeling of luxury, beating the softness of lawn in summertime easily.\n");

    add_exit(IRON + "brew4","west",0);

    reset_dwarf_room();
}


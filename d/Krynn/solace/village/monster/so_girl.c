#include "/d/Krynn/common/defs.h"

inherit M_FILE

create_krynn_monster()
{
    set_name("girl");
    set_short("young girl");
    set_long("She looks very weak for her age.\n");
    set_race_name("human");
    set_adj("young");
    add_adj("female");
    set_knight_prestige(-1);
    set_alignment(100);

    set_gender(1);

}

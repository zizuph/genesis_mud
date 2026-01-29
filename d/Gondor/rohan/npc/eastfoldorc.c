/* This file is /d/Gondor/rohan/npc/eastfoldorc.c         */
/*                                                     */
/* This orc will attack anyone attacking a member      */
/* of his team                                         */
/* copied in parts from /doc/examples/mobiles/troll.c  */
#pragma strict_types

inherit "/d/Gondor/common/npc/std_orc";

#include "/d/Gondor/defs.h"

public void
create_monster()
{
    ::create_monster();

    set_long(BS("A most evil creature. He is big and strong, and he "
        + "looks at you with death in his eyes.\n"));

    add_chat("It's dangerous on the plains!");
    add_chat("When the rohirrim find us, we're finished!");
    add_cchat("You'll be dead soon!");
    set_random_move(5);
    set_restrain_path(({"/d/Gondor/rohan/plains/g10","/d/Gondor/rohan/plains/g11","/d/Gondor/rohan/plains/f11",
       "/d/Gondor/rohan/plains/f12","/d/Gondor/rohan/plains/e12","/d/Gondor/rohan/plains/e13",
       "/d/Gondor/rohan/plains/d13","/d/Gondor/rohan/plains/e14","/d/Gondor/rohan/plains/d14",
       "/d/Gondor/rohan/plains/c14","/d/Gondor/rohan/plains/c15","/d/Gondor/rohan/plains/d15"}));
    set_monster_home(({"/d/Gondor/rohan/plains/e14"}));
}

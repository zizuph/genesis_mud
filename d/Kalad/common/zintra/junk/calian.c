/* calian.c */

inherit "std/monster";
inherit "/d/Kalad/lib/intro";
#include <ss_types.h>
#include <stdproperties.h>
#include "../defs.h"


void
create_monster()
{
    set_name("holton");
    add_name("calian");
    set_race_name("dwarf");
    add_adj("short");
    set_adj("dispirited");
    set_long( break_string (
"This dwarf has lost his will to live.  But, with no means with which to" +
"end his life, he is waiting for starvation to take its toll.  He is" +
"shackled to the wall next to the knight.\n", 78));
    default_config_mobile(15);

    set_act_time(20);
    add_act("groan");
    add_act("cry");
    add_act("wimper");

    set_chat_time(20);
    add_chat("Please kill me...  I beg thee!");
    add_chat("They broke my medallion, then my spirit.");
    add_chat("And I thought the krougs were mean...");

    add_prop(OBJ_I_NO_ATTACK, 1);
}

string
query_title()
{
    return "the Cavalier of Calia";
}


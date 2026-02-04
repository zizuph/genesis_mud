/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/drink";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP this_player()

public void
create_drink()
{
   set_name("juice");
   set_adj("red");
   add_name(MYSTIC_JUICE);
   set_soft_amount(100 + random(25));
   add_prop(HEAP_S_UNIQUE_ID, "mystic_grape_juice");
}

public int
drink_access(object ob)
{
    if (function_exists("create_heap", ob) != "/std/drink")
        return 0;
    if (environment(ob) == TP ||
          (environment(ob)->id(MYSTIC_CHALICE) &&
           environment(environment(ob)) == TP))
        if (ob->short())
            return 1;
    return 0;
}


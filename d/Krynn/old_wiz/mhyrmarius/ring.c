/*
 * Mhyrmarius spelltossing object
 * by Myrmarius, jul 22, 1997
 */

inherit "/std/object";
inherit "/d/Krynn/rastlin/open/spells2/spellcasting.c";

#include <formulas.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/mhyrmarius/noct.c"

void create_object() 
{
    set_name("ring");
    set_adj("gnarled");
    add_adj(({"heavy","wooden"}));
    set_long("This gnarled heavy wooden ring is Mhyrmarius favourite " +
      "for testing new spells.\n");
}

void init()
{
	::init();
	add_spell("nocturnus",do_nocturnus,"Darkness");
}


#pragma save_binary

inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/sys/defs.h"
#include "herald.h"
#include <wa_types.h>

void
create_armour()
{
    set_name("robe");
    add_name("_herald_robe_");
    set_short("flawless flowing white robe");
    add_adj(({"flawless","flowing","white"}));
    set_long("This beautiful white robe is made of the finest silk "+
      "imaginable, and woven in such a way that it all seems "+
      "a whole, rather than stitched parts.  When you hold it "+
      "up to the light, some secret letters appear.\n");
    add_prop(OBJ_I_WEIGHT, 120);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP,1);

    set_default_armour(0,A_ROBE);

    add_item(({"secret letters","letters"}), "They read: 'help herald'.\n");
    add_cmd_item("letters","read","The letters read:\n"+
      "If you find yourself lost, just 'help herald'.\n");
}

void
enter_env(object ob, object from)
{
    ::enter_env(ob,from);
    if (!living(ob) || objectp(from))
	return;

    remove_name("_herald_robe_");
    if (present("_herald_robe_", ENV(TO)))
    {
	set_alarm(0.1,0.0, remove_object);
	return;
    }
    add_name("_herald_robe_");
}

public string query_recover() { return 0; }


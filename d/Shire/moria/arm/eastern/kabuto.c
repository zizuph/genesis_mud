#include "defs.h";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit BASE_ARMOUR;

CONSTRUCT_ARMOUR
{
    set_name(({"kabuto", "helmet"}));
    add_adj(({"oriental", "full", "samurai"}));
    set_short("kabuto");
    set_long("This is the basic Samurai helmet. It consists "+
	     "of metal and wood, and provides the same "+
	     "protection as a standard full helm.\n");
    set_at(A_HEAD);
}

int
query_ac()
{
    object *menpo;
    object *shikoro;
    int base_ac = 19;

    if (!living(ETO))
	return base_ac;

    menpo = filter(INV(ETO), "wears_menpo", TO);
    shikoro = filter(INV(ETO), "wears_shikoro", TO);

    if (sizeof(menpo))
	base_ac += 4;
    if (sizeof(shikoro))
	base_ac += 6;

    return base_ac;
}

int 
wears_menpo(object ob)
{
    return ob->query_worn() == ETO;
}

int
wears_shikoro(object ob)
{
    return ob->query_worn() == ETO;
}

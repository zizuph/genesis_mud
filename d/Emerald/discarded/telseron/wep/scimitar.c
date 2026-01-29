inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Emerald/defs.h"

void
create_weapon()
{
    set_name("scimitar");
    set_short("small jagged scimitar");
    add_adj( ({"small", "jagged"}) );
    set_long("This scimitar seems to be a fairly decent weapon for "+
	"harassing innocents with, although an experienced opponent "+
	"wouldn't be too concerned facing it.\n");
    set_hit(17);
    set_pen(18);
    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
}

inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("knife");
    set_short("sharp steel knife");
    add_adj( ({"sharp", "steel"}) );
    set_long("The knife seems to be an average weapon that one "+
	"might find a normal citizen carrying.\n");
    set_hit(10);
    set_pen(14);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
}

inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("shortsword");
    set_short("plain steel shortsword");
    add_adj( ({"plain", "steel"}) );
    set_long("The shortsword seems to be an average weapon that one "+
	"might find a normal citizen carrying.\n");
    set_hit(17);
    set_pen(16);
    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
}

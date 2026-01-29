inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("handaxe");
	add_name("axe");
    set_short("short-handled handaxe");
    add_adj( ({"hand", "short-handled"}) );
    set_long("The handaxe seems to be an average weapon that one "+
	"might find a dwarven traveller carrying.\n");
    set_hit(15);
    set_pen(20);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
}

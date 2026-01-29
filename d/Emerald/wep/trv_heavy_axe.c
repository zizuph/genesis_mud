inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("axe");
    set_short("heavy iron axe");
    add_adj( ({"heavy", "iron"}) );
    set_long("The axe seems to be an average weapon that one "+
	"might find a tough dwarven traveller carrying.\n");
    set_hit(20);
    set_pen(25);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
}

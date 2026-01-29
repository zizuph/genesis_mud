inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("axe");
    set_short("heavy double-bladed axe");
    add_adj(({"heavy", "double-bladed"}));
    set_long("The axe seems to be a crude uncivilized weapon. The blades "+
	"are wedges of destruction, but the shaft seems to be a little "+
	"unwieldly.\n");
    set_hit(21);
    set_pen(37);
    set_wt(W_AXE);
    set_dt(W_BLUDGEON|W_SLASH);
    set_hands(W_BOTH);
}

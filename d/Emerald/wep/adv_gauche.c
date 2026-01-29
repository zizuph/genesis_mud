inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("gauche");
    set_short("sturdy main gauche");
    add_adj( ({"sturdy", "main"}) );
    set_long("The sharp seems to be a strong fencing weapon. The blade "+
	"is light and well balanced, but it's sharper than your average "+
	"fencing foil.\n");
    set_hit(14);
    set_pen(14);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_LEFT);
}

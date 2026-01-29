inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("foil");
    set_short("sharp foil");
    add_adj("sharp");
    set_long("The sharp seems to be a strong fencing weapon. The blade "+
	"is light and well balanced, but it's sharper than your average "+
	"fencing foil.\n");
    set_hit(34);
    set_pen(20);
    set_wt(W_SWORD);
    set_dt(W_IMPALE);
    set_hands(W_RIGHT);
}

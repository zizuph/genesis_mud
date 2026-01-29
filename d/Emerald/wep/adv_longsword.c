inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("longsword");
    set_short("light longsword");
    add_adj(({"light", "chert"}));
    set_long("The longsword seems to be a strong fencing weapon. The blade "+
	"is light and well balanced, but it's not as fragile or flexible "+
	"as a fencing foil.\n");
    set_hit(32);
    set_pen(22);
    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
}

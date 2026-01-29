inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("halberd");
    set_short("shiny elvish halberd");
    add_adj( ({"shiny", "elvish"}) );
    set_long("The halberd seems to be standard issue for the elite "+
	"members of the Elvish patrol. The blade is sharp and the shaft is "+
	"very well balanced, as should be expected of a superior elvish "+
	"weapon. It seems to be very well polished, an indication of a very" +
	"well-cared for weapon.\n");
    set_hit(25);
    set_pen(39);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_BOTH);
}

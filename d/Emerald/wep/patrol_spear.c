inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("spear");
    set_short("shiny elvish spear");
    add_adj( ({"shiny", "elvish"}) );
    set_long("The spear seems to be standard issue for the standard "+
	"members of the Elvish patrol. The blade is sharpened and the "+
	"shaft is balanced, as should be expected of an elvish "+
	"weapon. It seems to be polished, an indication of a " +
	"cared for weapon.\n");
    set_hit(23);
    set_pen(18);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
}

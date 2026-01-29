inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("broadsword");
    set_short("shiny elvish broadsword");
    add_adj( ({"shiny", "elvish"}) );
    set_long("The broadsword seems to be standard issue for the average "+
	"members of the Elvish patrol. The blade is not dull and fairly "+
	"well balanced, as should be expected of an elvish weapon. It "+
	"seems to be fairly well polished, an indication of a fairly "+
	"well-cared for weapon.\n");
    set_hit(24);
    set_pen(23);
    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
}

inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("shortsword");
    set_short("shiny elvish shortsword");
    add_adj( ({"shiny", "elvish"}) );
    set_long("The broadsword seems to be standard issue for the basic "+
	"members of the Elvish patrol. The blade is not dull and decently "+
	"balanced, as could be expected of an elvish weapon. It "+
	"seems to be decently polished, an indication of a decently "+
	"cared for weapon.\n");
    set_hit(21);
    set_pen(18);
    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
}

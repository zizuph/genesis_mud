inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("helm");
    set_short("shiny elvish helm");
    add_adj(({"shiny", "elvish"}));
    set_ac(25);
    set_am( ({0,0,0}) );
    set_at(A_HEAD);
    set_long("The helm seems to be standard issue for the more senior "+
	"members of the Elvish patrol. The face is guarded by a solid, "+
	"protective tabard. It seems to be very well polished, an "+
	"indication of a very well-cared for piece of armour.\n");
}

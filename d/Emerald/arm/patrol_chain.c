inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("chainmail");
    set_short("shiny elvish chainmail");
    add_adj(({"shiny", "elvish"}));
    set_ac(27);
    set_am( ({-2,3,-1}) );
    set_at(A_TORSO);
    set_long("The chainmail seems to be standard issue for the standard  "+
	"members of the Elvish patrol. The chainmail covers the entire "+
	"torso quite well. The chain links seem to be seamlessly linked, "+
	"an indication of a very well constructed piece of armour.\n");
}

inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("coif");
    set_short("elvish chain coif");
    add_adj(({"elvish", "chain"}));
    set_ac(17);
    set_am( ({-2,3,-1}) );
    set_at(A_HEAD);
    set_long("The coif seems to be standard issue for the "+
	"members of the Elvish patrol. The head is covered by a chain "+
	"mesh, lined with padded leather. The chain appears to be seamlessly "+
	"linked, indication of a well-constructed piece of armour.\n");
}

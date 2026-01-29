inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("armour");
    set_short("plated elvish leather armour");
    add_adj(({"hardened", "plated", "leather", "elvish"}));
    set_ac(10);
    set_am( ({0,1,-1}) );
    set_at(A_TORSO);
    set_long("The leather armour seems to be standard issue for the basic "+
	"members of the Elvish patrol. The leather covers the entire "+
	"torso quite well. The leather plates seem to be properly tanned, "+
	"an indication of a properly constructed piece of armour.\n");
}

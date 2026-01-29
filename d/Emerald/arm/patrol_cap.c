inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("cap");
    set_short("elvish leather cap");
    add_adj(({"elvish", "leather"}));
    set_ac(6);
    set_am( ({0,1,-1}) );
    set_at(A_HEAD);
    set_long("The cap seems to be standard issue for the basic "+
	"members of the Elvish patrol. The head is covered by hardened "+
	"leather plates, lined with soft padded leather. The leather "+
	"appears to be adequately tanned, an indication of a "+
	"properly-constructed light piece of armour.\n");
}

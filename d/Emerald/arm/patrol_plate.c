inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("platemail");
    set_short("shiny elvish platemail");
    add_adj(({"shiny", "elvish"}));
    set_ac(33);
    set_am( ({-1,0,1}) );
    set_at(A_TORSO|A_L_ARM|A_R_ARM|A_LEGS);
    set_long("The platemail seems to be standard issue for the more senior "+
	"members of the Elvish patrol. The platemail covers the entire body "+
	"from the torso, up each arm, and down to the shins. The armour " +
	"has some gaps with a light chainmail bridging them to keep the "+
	"bulkiness from limiting the wearers motion severely. It seems to "+
	"be very well polished, an indication of a very well-cared for "+
	"piece of armour.\n");
}

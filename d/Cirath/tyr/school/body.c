/*This is the standard armour for the guards in the jail of Tyr. */

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/d/Cirath/common/defs.h"

void create_armour()
{
	set_name("mail");
    set_short("thin leather mail");
   set_long("This is the standard suit of training armour "
	+"that adepts wear while practicing.  It provides "
	+"minimal protection from damage, but the training "
	+"weapons don't do much damage.  It is made of a few "
	+"pieces of thin leather, which help to soften the "
	+"blows from the wooden and bone training weapons.\n");
    set_adj("thin");
    add_adj("leather");


	set_ac(10);
	set_at(A_BODY);

	add_prop(OBJ_I_WEIGHT, 800);
	add_prop(OBJ_I_VOLUME, 1200);
}

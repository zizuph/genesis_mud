inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/d/Cirath/common/defs.h"

void create_weapon()
{
	set_name("mace");
	set_short("wooden training mace");

   set_long("This is a mace crafted from wood.  It has "
	+"some blunt wooden spikes coming out of the head "
	+"that make it an ideal training weapon.  In a real "
	+"fight, though, it would not be that useful.\n");
	
	set_adj  ("wooden");
	set_adj  ("training");

	set_hit(10);
	set_pen(10);

	set_wt(W_CLUB);
	set_dt(W_IMPALE | W_BLUDGEON);
	set_hands(W_RIGHT);
	add_prop(OBJ_I_WEIGHT,1000);
	add_prop(OBJ_I_VOLUME,500);
}

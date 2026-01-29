inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/d/Cirath/common/defs.h"

void create_weapon()
{
	set_name("mace");
	set_short("great mace");

   set_long("A huge obsidian mace used by the captain of the "
	+"school guards, this mace looks to be very nice. "
	+"Runes etched in blood adorn the sides of it, and "
	+"the large spikes protruding from the obsidian head "
	+"look to be capable of piercing even the thickest "
	+"armours.\n");
	
	set_adj  ("great");

	set_hit(40);
	set_pen(35);

	set_wt(W_CLUB);
	set_dt(W_IMPALE | W_BLUDGEON);
  set_hands(W_ANYH);
	add_prop(OBJ_I_WEIGHT,9000);
	add_prop(OBJ_I_VOLUME,10000);
}

inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
create_armour()
{
   ::create_armour();
   set_name("chainmail");
   set_adj("supple");
   set_long("This is a finely crafted suit of chainmail. It is surprisingly "
	+"supple and light. It was crafted by the drow, and has "
	+"the characteristic high quality, and effectiveness that "
	+"the drow use on everything they make.\n");
   set_ac(35);
   set_at(A_BODY);
}

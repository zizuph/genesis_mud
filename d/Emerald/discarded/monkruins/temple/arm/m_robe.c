/* temple/arm/m_robe.c is cloned by temple/npc/monk.c,
     monk2.c and abbed.c */
inherit "/std/armour";
 
#include "/d/Emerald/defs.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
 
void
create_armour()
{
 set_name("robe");
 set_short("brown robe");
 set_long("This is a brown leather monk's robe.\n");
 set_adj("brown");
 
 add_prop(OBJ_I_VOLUME,3000);
 add_prop(OBJ_I_WEIGHT,2000);
 add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(10)+random(30));
 
 set_ac(10);
 set_am(({-6,4,0}));
 
 set_at(A_ROBE);
}

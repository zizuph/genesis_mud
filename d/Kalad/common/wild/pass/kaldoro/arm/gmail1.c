/* 
 * /d/Kalad/common/wild/pass/kaldoro/arm/gmail1.c
 * Purpose    : A standard chainmail for the guards of Kaldoro.
 * Located    : ../npc/kguard1.c and ../npc/kguard2.c
 * Created By : Rico 13.Dec.94
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour.c";

#include "/d/Kalad/defs.h"

create_armour()
{
   ::create_armour();

   set_name(({ "chainmail", "mail" }));
   set_adj("rough");

   set_short("rough mail");
   set_long("This mail armour is the usual body armour "+
	"worn by Kaldoro town guards.  It is quite beat "+
        "up and blood stained, but looks as though it "+
        "has done the work it was intended for.\n");

   set_at(TS_TORSO);

   set_ac(19);

   add_prop(OBJ_I_WEIGHT, 5000);
   add_prop(OBJ_I_VOLUME, 1300);
   add_prop(OBJ_I_VALUE, 300);
}

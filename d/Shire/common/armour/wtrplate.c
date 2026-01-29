inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include "/d/Shire/common/defs.h"

#define SAC 21
#define SAT A_TORSO
#define SAM ({1,1,-2})

void
create_armour()
{
   set_short("giant platemail");
   add_adj(({"giant","plate","troll"}));
   set_name("plate");
   add_name(({"platemail","mail"}));
   set_long("This giant platemail is of crude enough construction "+
   "to be made by trolls, and if that weren't enough, the size is "+
   "absolutely of proportions for trolls.  It is hard to tell how well "+
   "this platemail will cover you.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(251));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(36));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);

}

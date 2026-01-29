inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
 
#define SAC 17
#define SAT A_ROBE
#define SAM ({0,1,0})
#define SNAME "cloak"
#define SADJ "forest green"
#define SSHORT "forest green cloak"
#define SPSHORT "forest green cloaks"
 
create_armour()
{
 set_name(SNAME);
 set_adj(SADJ);
 add_adj(({"forest","green"}));
 set_short(SSHORT);
 set_pshort(SPSHORT);
 set_long("This "+short()+" looks like good protection "+
  "against the rain. Also it looks like it fits in well "+
  "with forests.\n"); 
 set_default_armour(SAC,SAT,SAM,0);
 add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(285));
 add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) + random(61));
 add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}
 

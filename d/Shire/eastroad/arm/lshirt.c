inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 21
#define SAT A_TORSO
#define SAM ({1,1,-2})
#define SNAME "shirt"
#define SADJ "thin"
#define SSHORT "thin leather shirt"
#define SPSHORT "thin leather shirts"

void
create_armour()
{
  set_name(SNAME);
  add_name(({"shirt","leather shirts"}));
  set_adj(SADJ);
  add_adj(({"thin","leather"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("The "+short()+" covers the wearer "+
    "and protects from the elements.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(251));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(36));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}

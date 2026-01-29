inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
 
#define SAC 23
#define SAT A_TORSO
#define SAM ({2,1,0})
#define SNAME "coat"
#define SADJ "splint"
#define SSHORT "elven splint mail"
#define SPSHORT "elven splint mail"
 
void
create_armour()
{
  set_name(SNAME);
  add_name(({"splint","splint mail"}));
  set_adj(SADJ);
  add_adj(({"elven","splint"}));

  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This is a coat of "+ short() +". It is thin "+
   "light weight and a silverish color.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(151));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(27));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}
 

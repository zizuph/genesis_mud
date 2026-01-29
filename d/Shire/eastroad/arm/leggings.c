inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 12
#define SAT A_LEGS
#define SAM ({0,1,-1})
#define SNAME "leggings"
#define SADJ "leather"
#define SSHORT "pair of leather leggings"
#define SPSHORT "pairs of leather leggings"

void
create_armour()
{
  set_name(SNAME);
  add_name(({"pair","pair of leggings"}));
  set_adj(SADJ);
  add_adj(({"leather","tall"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" is nicely stiched together from "+ 
    "well-oiled bits of strong leather.\n");
  set_default_armour(SAC,A_LEGS,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,A_LEGS)+random(101));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(11));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


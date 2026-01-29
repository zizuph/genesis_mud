#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 12
#define SAT A_TORSO
#define SAM ({1,0,-1})
#define SNAME "breastplate"
#define SADJ "hard"
#define SSHORT "hard leather breastplate"
#define SPSHORT "hard leather breastplates"

create_armour()
{
  set_name(SNAME);
  add_name(({"leather","cuir-bouili"}));
  set_adj(SADJ);
  add_adj(({"leather","cuir-bouili"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" adequately protects the chest and back of "+
    "the wearer with rigid leather that has been boiled in oil "+
    "to form cuir-bouili, a cheap and easy to make armour.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(101));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) + random(51));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
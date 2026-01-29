#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 24
#define SAT A_HEAD
#define SAM ({0,0,0})
#define SNAME "helm"
#define SADJ "tabarded"
#define SSHORT "tabarded steel helm"
#define SPSHORT "tabarded steel helms"

create_armour()
{
  set_name(SNAME);
  add_name(({"helmet","barf"}));
  set_adj(SADJ);
  add_adj(({"steel","heavy"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
set_long("This "+short()+" is extremely well crafted. It appears to be "+
    "rather ancient in design, with a broad, ridged tabard projecting "+
    "down from the front to protect the nose with sturdy steel.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(301));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(51));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
#pragma save_binary

inherit "/lib/keep";
inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 37
#define SAT A_ARMS
#define SAM ({-1,2,-1})
#define SNAME "sleeves"
#define SADJ "banded"
#define SSHORT "pair of banded armour sleeves"
#define SPSHORT "pairs of banded armour sleeves"

create_armour()
{
  set_name(SNAME);
  add_name(({"sleeve","pair"}));
  set_adj(SADJ);
  add_adj(({"pair","armour","steel"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" has overlapping steel plates that "+
    "sheath the arm from shoulder to wrist in their protective embrace. "+
    "The sleeve is carefully jointed at the elbow to ensure the "+
    "full range of motion required during combat.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) - random(101));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) + random(51));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }

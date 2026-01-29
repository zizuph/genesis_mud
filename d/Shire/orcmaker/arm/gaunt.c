#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 17
#define SAT A_ARMS
#define SAM ({-1,2,-1})
#define SNAME "bracer"
#define SADJ "ringmail"
#define SSHORT "pair of ringmail bracers"
#define SPSHORT "pairs of ringmail bracers"

create_armour()
{
  set_name(SNAME);
  add_name(({"bracers","pair"}));
  set_adj(SADJ);
  add_adj(({"pair","iron"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" has small iron rings sewn onto hard "+
    "leather plates that are strapped to the lower arm. Crafted by "+
    "orcs, they still manage to provide adequate protection.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(101));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(11));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
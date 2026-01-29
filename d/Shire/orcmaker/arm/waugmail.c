#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 30
#define SAT A_TORSO
#define SAM ({-1,1,0})
#define SNAME "hauberk"
#define SADJ "mail"
#define SSHORT "augmented mail hauberk"
#define SPSHORT "augmented mail hauberks"

create_armour()
{
  set_name(SNAME);
  add_name(({"mail","coat"}));
  set_adj(SADJ);
  add_adj(({"augmented","brass","orcish"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" is of obvious orcish craftmanship, and "+
    "it is very poorly made. Small strips of "+
    "bronze have been woven into the brass links for strength.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(101));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(101));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 23
#define SAT A_TORSO
#define SAM ({1,1,-2})
#define SNAME "mail"
#define SADJ "splint"
#define SSHORT "sturdy splint mail"
#define SPSHORT "sturdy splint mails"

create_armour()
{
  set_name(SNAME);
  add_name(({"splint","splintmail"}));
  set_adj(SADJ);
  add_adj(({"sturdy","dsa"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("The "+short()+" covers the torso of the wearer with a rigid "+
    "leather vest that has thick strips of steel riveted to it. "+
    "These vertical strips of steel provide enhanced protection.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(176));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) + random(46));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
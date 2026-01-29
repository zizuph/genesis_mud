#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 10
#define SAT A_ROBE
#define SAM ({-1,0,1})
#define SNAME "cloak"
#define SADJ "hide"
#define SSHORT "heavy hide cloak"
#define SPSHORT "heavy hide cloaks"

create_armour()
{
  set_name(SNAME);
  add_name(({"hide","barf"}));
  set_adj(SADJ);
  add_adj(({"heavy","dirty"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" is made of a thick, uncured hide that "+
    "seems to have belonged to a moose or elk at one time. "+
    "While providing some protection, it also provides a stench.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(101));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(11));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
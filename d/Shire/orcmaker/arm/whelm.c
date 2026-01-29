#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 4
#define SAT A_HEAD
#define SAM ({0,1,-1})
#define SNAME "cap"
#define SADJ "hard"
#define SSHORT "hard leather cap"
#define SPSHORT "hard leather caps"

create_armour()
{
  set_name(SNAME);
  add_name(({"helmet","helm"}));
  set_adj(SADJ);
  add_adj(({"leather","light"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" is hardly an adequate covering for "+
    "most heads, but it does manage to provide some protection. "+
    "The leather is light, but hard, and forms a rounded cone.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(21));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(11));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
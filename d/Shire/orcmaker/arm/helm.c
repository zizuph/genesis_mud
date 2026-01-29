#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 18
#define SAT A_HEAD
#define SAM ({-1,1,0})
#define SNAME "hood"
#define SADJ "mail"
#define SSHORT "double mail hood"
#define SPSHORT "double mail hoods"

create_armour()
{
  set_name(SNAME);
  add_name(({"helmet","helm"}));
  set_adj(SADJ);
  add_adj(({"iron","double"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+", worn over the head, protects "+
    "the wearer well from most blows with its superior mail design. "+
    "The mail itself seems to be forged of a high-grade iron.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(101));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) + random(21));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
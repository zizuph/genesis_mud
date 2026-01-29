#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 13
#define SAT A_TORSO
#define SAM ({0,1,-1})
#define SNAME "vest"
#define SADJ "studded"
#define SSHORT "studded leather vest"
#define SPSHORT "studded leather vests"

create_armour()
{
  set_name(SNAME);
  add_name(({"leather","barf"}));
  set_adj(SADJ);
  add_adj(({"leather","poor"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" has many bronze studs set widely "+
    "apart on a backing of poor, rotting leather.  It lacks "+
    "sleeves and the straps are almost worn through.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(66));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(31));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
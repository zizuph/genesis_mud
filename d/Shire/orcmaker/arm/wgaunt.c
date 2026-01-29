#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 8
#define SAT A_ARMS
#define SAM ({-1,-1,2})
#define SNAME "bracer"
#define SADJ "padded"
#define SSHORT "pair of padded bracers"
#define SPSHORT "pairs of padded bracers"

create_armour()
{
  set_name(SNAME);
  add_name(({"bracers","pair"}));
  set_adj(SADJ);
  add_adj(({"pair","cloth"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" protects the arm with a thick layer "+
    "of cloth.  The cloth is very rough, probably homespun, and dark "+
    "brown.  The cloth is heavily soiled, the result of years of use.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(101));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(41));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
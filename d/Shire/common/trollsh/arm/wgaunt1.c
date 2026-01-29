#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 15
#define SAT A_ARMS
#define SAM ({-1,-1,2})
#define SNAME "bracers"
#define SADJ "padded"
#define SSHORT "pair of battered bracers"
#define SPSHORT "pairs of battered bracers"

create_armour()
{
  set_name(SNAME);
  add_name(({"bracers","pair"}));
  set_adj(SADJ);
  add_adj(({"pair","battered"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" protects the arms with a thick layer "+
    "of dirty cloth. The braceres are battered from constant use.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(101));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(41));
  add_prop(OBJ_I_VOLUME,2500);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
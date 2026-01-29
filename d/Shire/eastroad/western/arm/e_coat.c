/* Just a forest green coat that Elves might wear */
 
inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
 
#define SAC 5
#define SAT A_TORSO
#define SAM ({0,0,0})
#define SNAME "coat"
#define SADJ "green"
#define SSHORT "forest green coat"
#define SPSHORT "forest green coat"
 
void
create_armour()
{
  set_name(SNAME);
  set_adj(SADJ);
  add_adj(({"green","forest"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("The "+short()+" covers the wearer "+
    "and looks as if it might blend in well with "+
    "the saroundings of a forest.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(251));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(36));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}
 

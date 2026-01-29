inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 13
#define SAT A_LEGS | A_WAIST
#define SAM ({0,1,-1})
#define SNAME "pants"
#define SADJ "canvas"
#define SSHORT "pair of canvas pants"
#define SPSHORT "pairs of canvas pants"

void
create_armour()
{
    set_name(SNAME);
    add_name(({"pair","pair of pants"}));
    set_adj(SADJ);
    add_adj(({"canvas","pair"}));
    set_short(SSHORT);
    set_pshort(SPSHORT);
    set_long("This "+short()+" is very effective against "+ 
      "briars and good at working in the field.\n");
    set_default_armour(SAC,A_LEGS,SAM,0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,A_LEGS)+random(101));
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(11));
    add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


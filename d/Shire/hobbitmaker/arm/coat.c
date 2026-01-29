inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 21
#define SAT A_TORSO
#define SAM ({1,1,-2})
#define SNAME "coat"
#define SADJ "splint"
#define SSHORT "coat of splint mail"
#define SPSHORT "coats of splint mail"

void
create_armour()
{
    set_name(SNAME);
    add_name(({"splint","splint coat"}));
    set_adj(SADJ);
    add_adj(({"iron","splint"}));
    set_short(SSHORT);
    set_pshort(SPSHORT);
    set_long("The "+short()+" covers the wearer "+
      "and protects from cuts and bruises.\n");
    set_default_armour(SAC,SAT,SAM,0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(251));
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(36));
    add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}

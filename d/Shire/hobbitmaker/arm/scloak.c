inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 15
#define SAT A_ROBE
#define SAM ({0,1,-1})
#define SNAME "cloak"
#define SADJ "leather"
#define SSHORT "smooth leather cloak"
#define SPSHORT "smooth leather cloaks"

create_armour()
{
    set_name(SNAME);
    add_name(({"leather"}));
    set_adj(SADJ);
    add_adj(({"smooth","leather"}));
    set_short(SSHORT);
    set_pshort(SPSHORT);
    set_long("This "+short()+" looks like good protection against the rain.\n"); 
    set_default_armour(SAC,SAT,SAM,0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(301));
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) + random(51));
    add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 11
#define SAT A_HEAD
#define SAM ({0,0,0})
#define SNAME "hat"
#define SADJ "fluffy"
#define SSHORT "fluffy green hat"
#define SPSHORT "fluffy green hats"

create_armour()
{
    set_name(SNAME);
    add_name(({"cap"}));
    set_adj(SADJ);
    add_adj(({"fluffy","green"}));
    set_short(SSHORT);
    set_pshort(SPSHORT);
    set_long("This "+short()+" is very colorful and bright.\n");
    set_default_armour(SAC,SAT,SAM,0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(301));
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) + random(51));
    add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}

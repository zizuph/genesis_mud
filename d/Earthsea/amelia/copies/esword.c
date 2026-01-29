inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Roke/common/defs.h"



void
create_weapon()

{
   set_name("sword");
   set_short("bastard sword");
   set_long("This is a bastard sword made from fine-forged steel. "+
               "It is basically a cross between a longsword and "+
             "a short sword.\n");
    set_adj(({"steel", "bastard"}));

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE,300);

    set_hit(24);
    set_pen(28);

        set_wt(W_SWORD);

        set_wt(W_SWORD);
        set_dt(W_SLASH | W_IMPALE);

        set_hands(W_ANYH);
}


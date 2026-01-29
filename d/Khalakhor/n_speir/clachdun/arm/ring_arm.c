#include <wa_types.h>
#include <stdproperties.h>
#include "local.h"

inherit "/d/Khalakhor/std/armour";

void
create_khalakhor_armour()
{
    set_name("_Khalakhor_mage_ring_armour");
    set_no_show();
    set_af(this_object());
    set_ac(20);
    set_at(A_MAGIC);
    set_shield_slot(({A_HEAD,A_TORSO, A_R_ARM, A_L_ARM, A_LEGS}));

    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({"enchantment", 100}));
    add_prop(OBJ_S_WIZINFO, "Check out "+OBJ_DIR+"mage_ring.c for details.\n");
}

mixed
remove(object ob)
{
    return 1;
}

mixed 
wear(object ob)
{
    return 1;
}

varargs void
remove_broken(int silent = 0)
{
    return;
}

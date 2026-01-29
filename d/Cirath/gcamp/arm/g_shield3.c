inherit "/lib/keep";
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "../defs.h"

void
create_armour()
{
        set_name("shield");
        set_adj("bone");
        add_adj("large");
        set_short("large bone shield");
        set_long("This shield looks, upon first inspection, to be "
        +"crafted from an enormous animal bone.  As you examine "
        +"it further, though, you notice that the center of the "
        +"shield actually is very high quality steel that was "
        +"probably a buckler at some point.  It has now been "
        +"converted into a better use by surrounding it with bone "
        +"so that it is larger and covers more of your body.\n");
        add_prop(OBJ_I_WEIGHT,3200);
        add_prop(OBJ_I_VOLUME,1200);
        add_prop(OBJ_I_VALUE, 3000);
        set_ac(38);
        set_at(A_SHIELD);
        set_wf(TO);
}


public int *
query_shield_slots()
{
return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}

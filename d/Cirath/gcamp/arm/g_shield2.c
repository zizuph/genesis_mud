
inherit "/lib/keep";
inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
   set_name("shield");
   set_adj("large");
   add_adj("bone");
   set_short("large bone shield");
   set_long("This shield looks, upon first inspection, to be "
   	+"crafted from an enormous animal bone.  As you examine "
   	+"it further, though, you notice that the center of the "
   	+"shield actually is very high quality steel that was "
   	+"probably a buckler at some point.  It has now been "
   	+"converted into a better use by surrounding it with bone "
   	+"so that it is larger and covers more of your body.\n");
   set_ac(36);
   set_at(A_SHIELD);
   add_prop(OBJ_I_WEIGHT,6000);
   add_prop(OBJ_I_VOLUME,3500);
   set_wf(TO);
}
public int *
query_shield_slots()
{
return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}


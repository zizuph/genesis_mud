#include "/d/Krynn/common/defs.h"
inherit "/std/weapon";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define WEAPON_HIT 22
#define WEAPON_PEN 34

void
create_weapon()
{
   set_name("tooth");
   set_pname("teeth");
   set_adj("dragon");
   set_short("dragon tooth");
   set_pshort("dragon teeth");
   set_long("This is the tooth of a mythical beast of legend, a dragon! Over a foot " +
       "in length an deadly sharp, you feel this could make a handy weapon.\n");
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(MAGIC_AM_MAGIC,({ 20, "enchantment"}));
   add_prop(MAGIC_AM_ID_INFO,({"This tooth comes from the maw of a dragon, a beast " +
       "of myth and magic. This tooth is the size of a dagger, however is incredibly " +
       "sharp. It also is extremely durable, and will not break through any mundane " +
       "means.\n",15}));
   
   set_hit(WEAPON_HIT);
   set_pen(WEAPON_PEN);
   set_wt(W_KNIFE);
   set_dt(W_IMPALE | W_SLASH);
   set_hands(W_ANYH);
   set_wf(TO);
   
   add_prop(OBJ_I_WEIGHT, 650);
   add_prop(OBJ_I_VOLUME, 500);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN));
}

varargs void
remove_broken(int silent = 0)
{
    if (calling_function() == "item_expiration_break") 
        ::remove_broken(silent);

    return;
}
 
 
int
set_dull(int du)
{
    return 0;
}

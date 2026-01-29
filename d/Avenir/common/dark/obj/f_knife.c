// Feather knife (/d/Avenir/common/dark/obj/f_knife)
// creator(s):   Grace Jun 1996
// last update:  Lilith, 20 July 1996
// last update:  Cirion 27 November 1999: fixed error with W_IMPALE || W_SLASH
// purpose:      A feather from the body of the winged wolf
// note:         This object is magical; it has a light level of +2
//               that will decay to 0 in one hour.
/*
 * Revisions:
 * 	Lucius, Aug 2017: Removed unnecessary names/pnames.
 */
inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include "/d/Avenir/common/common.h"

#define LIGHT_DELAY (3600.0) /* One hour in seconds. */

/*
 * Function name: delayed_remove_light
 * Description  : This function is called exactly LIGHT_DELAY seconds after
 *                the knife was cloned. We first add the property with the
 *                value 0 to make sure that the value is updated in the
 *                environment and then we remove the property because it is
 *                useless to keep a property 0 added.
 */
void
delayed_remove_light()
{
    add_prop(OBJ_I_LIGHT, 0);
    remove_prop(OBJ_I_LIGHT);
    if (living(ENV(TO)))
       write("The "+short()+" no longer glows from within.\n");
    set_long("This is a feather from the winged-wolf of Avenir's Under"+
       "dark.\nIt is metallic and razor-sharp, and looks like it could"+
       " be used like a knife.\n");
}

void
create_weapon()
{
    if (!IS_CLONE)
        return;

    set_name("feather");
    set_pname("feathers");
    add_name(({"knife"}));
    add_adj(({"iridescent","rainbow-hued"}));
    set_short("iridescent rainbow-hued feather");
    set_pshort("iridescent rainbow-hued feathers");
    set_long("This is a feather from the winged-wolf of Avenir's Under"+
       "dark.\nMetallic and razor-sharp, it glows from within and casts "+
       "shards\nof coloured light. It looks like it could be used like "+
       "a knife.\n");
   set_keep(1);
   set_wt(W_KNIFE);
   set_hands(W_ANYH);
   set_dt(W_SLASH | W_IMPALE);
   set_hit(20);
   set_pen(40);    // It is supposed to be 'razor-sharp'

   add_prop(OBJ_I_VOLUME, 400);
   add_prop(OBJ_I_WEIGHT, 200);  // It is a feather, so very light
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(16, 22) + 100);

   add_prop(OBJ_I_LIGHT, 2);
   add_prop(MAGIC_AM_MAGIC, ({ 75, "fire", 25, "life" }));
   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
   add_prop(MAGIC_AM_ID_INFO,({
     "This is a feather from the wolf-incarnation of the spirit-being,"+
     "Marchosias. It has about it a faint glow.\n",20,
     "The "+short()+" resonates with the magic elements of fire and "+
     "life.\n",35}));
   add_prop(OBJ_S_WIZINFO,"This "+short()+" is magical by virtue of its "+
     "glowing. It is vested with the magical properties of life and "+
     "fire. It is a feather from the body of the winged-wolf Marchosias, "+
     "(/d/Avenir/common/dark/mon/w_wolf) who lives in the Utterdark of "+
     "Avenir (/d/Avenir/common/dark/l2/n5 & 5a). He is a spirit being "+
     "of near-blinding luminescence which is caused by the feathers.\n"); 

    /* Call the alarm LIGHT_DELAY seconds after creation. */
    set_alarm(LIGHT_DELAY, 0.0, delayed_remove_light);
}

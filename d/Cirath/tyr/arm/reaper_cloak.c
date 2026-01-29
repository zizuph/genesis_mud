/*
* Created by: Luther
* Date: Jan 2002
*
* File: /d/Cirath/tyr/arm/reaper_claok.c
* Comments: 
*/
inherit "/std/armour";

#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

void
create_armour()
{    
   set_name("cloak");
   set_pname("cloaks");
   set_adj("grey");
   set_short("grey cloak");
   set_pshort("grey cloaks");
   set_long("The cloak is the dullest color of dark grey, hooded, " +
   	"and extremely long bearing lighter grey trim. The bearer of " +
   	"this cloak must be extremely powerful in the arts of arcane " +
   	"knowledge. Ancient runes envelope the trim of the cloak, " +
   	"displaying a language of mystery and knowledge. You feel " +
   	"the electricity it posseses as you grasp it in your hands...\n");
   set_ac(15);
   set_at(A_ROBE);
   add_prop(OBJ_M_NO_STEAL, "It slips out of your grasp.\n");
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
   add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO,
           ({"This armour is made of a mystical bend of cloth.", 10,
            "It has been enchanted to give better protection "
            +"as well as being super light.", 25 }));
   add_prop(OBJ_S_WIZINFO,
             "A minor magical cloak. Better AC and weight is assigned by " +
             "create_armour.\n");
}

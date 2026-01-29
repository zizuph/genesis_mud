/*
 * Elrond's shield
 * By Finwe, July 1998
 */

#pragma save_binary
 
inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>


create_armour()
{
    set_am(({0,0,0}));
    set_name("shield");
    set_adj(({"ancient", "glowing"}));
    set_short("ancient glowing elven shield");
    set_long("This ancient shield was forged ages ago by the " +
		"skilled metalworkers of the elves. It is made of mithril " +
		"and is very light yet strong. Despite its age, the shield " +
		"doesn't show any signs of battle but seems durable enough to " +
		"withstand many battles. The shield is round with a star " +
		"engraved into the center of it.\n");
    set_ac(55);
    set_at(A_SHIELD);
    set_keep(1);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(1000) + 75 + random(125));
    add_prop(OBJ_I_WEIGHT,3500);
    add_prop(OBJ_I_VOLUME,3000);
    add_prop(MAGIC_I_RES_COLD,({25,1}));

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
 
    add_prop(OBJ_S_WIZINFO,
        "This armour is worn by Elrond. The only magical ability " +
        "it has is that it burns enemies that attack the wearer.\n");
 
    add_prop(MAGIC_AM_ID_INFO,
        ({"This "+short()+" was forged by the ancient elves of " +
        "Middle-earth. A strong sense of power seems to " +
        "radiate from it.", 20}));
 
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));

}

got_hit(int hid,int ph,object att,int dt,int dam)
{
  	::got_hit(hid,ph,att,dt,dam);

	att->hit_me(random(dam),0,wearer,0);
  	att->catch_msg("You burn yourself on the elven shield!\n");
  	tell_room(ENV(TO),QCTNAME(att)+" is burned by the elven shield!\n");
}

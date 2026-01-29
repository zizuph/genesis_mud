/*
 * Elrond's helmet
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
    set_name("helmet");
    add_name("helmet");
    set_short("ancient glowing elven helmet");
    set_long("This ancient helmet was forged ages ago by elves. " +
        "Made of mithril, the helmet is light yet durable. The helmet " +
        "seems to be untouched by the ravages of battle and protects " +
        "the head from blows during battle.\n");
    set_adj("glowing");
    set_ac(55);
    set_am(({-1,1,0}));
    set_at(A_HEAD);
    set_keep(1);

    add_prop(OBJ_I_VALUE, 1000 + random(250));
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
 
    add_prop(OBJ_S_WIZINFO,
        "This armour is worn by Elrond. Armour burns attackers.\n");
 
    add_prop(MAGIC_AM_ID_INFO,
        ({"This "+short()+" was forged by the ancient elves of " +
        "Middle-earth. A strong sense of power seems to " +
        "radiate from it.", 20}));
 
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,3000);
    add_prop(MAGIC_I_RES_COLD, ({50,1}) );
}
got_hit(int hid,int ph,object att,int dt,int dam)
{
    ::got_hit(hid,ph,att,dt,dam);
    att->hit_me(random(dam)/2,0,wearer,0);
    att->catch_msg("You burn yourself on the ancient elven helmet!\n");
    wearer->catch_msg(QCTNAME(att)+" is hurt by the ancient elven helmet!\n");
  }

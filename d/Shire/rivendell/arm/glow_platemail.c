/*
 * Elrond's platemail
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
    set_name("mail");
    add_name("platemail");
    set_short("ancient glowing elven platemail");
    set_adj(({"plate","glowing","glowing plate", 
        "ancient elven glowing platemail", "ancient glowing platemail",
        "ancient platemail", "elven platemail"}));
    set_long("This platemail was forged in ages past by the " +
        "ancient elves. It is made of mithril and shows no signs " +
        "of battle. The platemail is rather light considering " +
        "what it is and even more amazing, a white fire seems to " +
        "burn within the armour.\n");

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

    set_ac(55);
    set_am(({0,0,0})); /* impale,slash,bludgeon */
    set_at(A_TORSO);
    set_keep(1);

    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(55, A_TORSO));
    add_prop(OBJ_I_VOLUME,8000);
    add_prop(OBJ_I_LIGHT,1);


}

got_hit(int hid,int ph,object att,int dt,int dam)
{
  ::got_hit(hid,ph,att,dt,dam);

  att->hit_me(random(100),0,wearer,0);
  att->catch_msg("You burn yourself on the elven platemail!\n");
  tell_room(ENV(TO),QCTNAME(att)+" is burned by the elven platemail!\n");
}

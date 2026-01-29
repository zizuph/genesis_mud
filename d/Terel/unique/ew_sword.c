/* This comment tells emacs to use c++-mode  -*- C++ -*- */
/*
 * /d/Terel/LoD/weapon/ew_sword.c
 *
 * Mergula's sword.
 *
 * Revision history:
 * Balance work by Boron 13/Aug/1996 (Added wiz_info)
 *
 * Lilith July 2008
 * -removed restriction of killer-only wielding it.
 * -updated the description.
 *
 * Petros, May 2009
 * - Updated weight and value props to default
 * - Set the wielding message correctly without the alarm
 *
 * Lilith, Feb 2022
 * - Added as a magic enhancer lvl 55 per Arman
 */

#include <wa_types.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;
inherit "/d/Genesis/specials/new/lib/spell_enhancer";
inherit "/lib/keep";

public void
create_weapon()
{
    ::create_weapon();
    

/*  Boring! Lets spice it up a little -Lilith
 *  set_short("blackened steel sword");
 *  set_long("It is a blackened steel sword. It is very sharp.\n");
 */

    set_short("sword of Mergula");
    set_long("This longsword was once wielded by the mighty Mergula, "+
        "Warlord of the Legion of Darkness. It is very long and "+
        "heavy, so much so that it requires two hands in order to "+
        "wield it. It is made of a blackened steel so dark that "+
        "only its sharpened edge catches the light, gleaming like "+
        "a ribbon of silver. Mergula uses it to enhance his "+
        "spells.\n");
    set_name("sword");
    add_name("longsword");
    set_adj("steel");
    add_adj(({"blackened", "two-handed", "mergula's", "Mergula's",
        "mergula", "Mergula"}));

    set_magic_spellpower(55);      
    set_hit(55);
    set_pen(60);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_wf(TO);
    set_hands(W_BOTH);
    set_keep(0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(query_pen(), query_wt()));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen()));
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 2200);
        
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 60, "enchantment" }) );
    add_prop(MAGIC_AM_ID_INFO,
	({"This is Mergula's famous sword.", 10 }));
    add_prop(OBJ_S_WIZINFO,
	  "This is Mergula's famous sword. It has no special abilities.\n");
}

public mixed
wield(object wep)
{
    TP->catch_msg("The " + short() + " glows faintly as you wield it.\n");
    tell_room(ENV(TP), "The " + short() + " glows faintly as " 
        + QTNAME(TP) + " wields it.\n", TP);
        
    return 1;
}

void appraise_object(int num)
{
   ::appraise_object(num);
   write(item_spellpower_desc());
}
 
string stat_object() 
{
     return ::stat_object() + stat_object_spellpower();
}

 

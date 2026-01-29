#pragma strict_types
/*
 * Modified by Ckrik 9/2003
 * increased hit to 39 and increased value.
 *
 * Modified by Ckrik 3/2004
 * Made magical to comply with new 'man weapons' guidelines
 * and added bonus to discipline.
 */
inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

public void
create_weapon()
{
    set_name("longsword");
    add_name("sword");
    set_pname("longswords");
    set_short("green steel longsword");
    set_pshort("green steel longswords");
    set_long("This is a longsword made from green steel. "+
        "It has an emblem on each side of the blade of "+
        "two crossed axes over a map of the world.\n");
    set_adj(({"green", "steel"}));
    set_keep(1);
    set_hit(39);
    set_pen(40);
    set_hands(W_ANYH);
    set_wf(this_object());
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, 1100);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, 
	     "A green steel longsword. It adds " +
	     "5 to SS_DIS when wielded. To wield, one needs " +
	     "SS_SWORD > 40, SS_WIS > 50, and SS_DEX > 50.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"This is a well balanced and finely made weapon " +
	  "that when in capable hands, instills confidence.\n", 5}));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
}

public mixed
wield(object what)
{
    object tp = this_player();

    if(tp->query_skill(SS_WEP_SWORD) > 40 &&
        tp->query_base_stat(SS_WIS) > 50 &&
        tp->query_base_stat(SS_DEX) > 50)
    {
        write("You feel confident as you wield the " + query_short() + ".\n");
        say(QCTNAME(tp) + "'s face narrows, thoughts obviously racing "+
            "through " + tp->query_possessive() + " mind.\n");
	tp->set_stat_extra(SS_DIS,
			   tp->query_stat_extra(SS_DIS) + 5);
        return 0;
    }

    tp->add_hp(-random(30) - 5);
    return "You attempt to wield the " + query_short() + ", but "+
        "feel as though you are unworthy to wield a sword such "+
        "as this.\n";
}

public mixed
unwield(object what)
{
    object tp = query_wielded();

    /* Can't use write() here for some reason Ckrik 4/2004 */
    tp->catch_tell("You feel less confident as you release your grip " +
		  "on the sword.\n");
    tp->set_stat_extra(SS_DIS,
		       tp->query_stat_extra(SS_DIS) - 5);
    return 0;
}

/* Created by Ckrik Nov 1997 for Earthsea in Genesis
 * Updated June 2003 Ckrik
 * Updated 10/2003 Ckrik to make the variable tohit work
 * Updated 07/2015 Ckrik Adjusted wield message to make the
 *    extra benefit from polearm more evident.
 */

#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>

#define WEAPON_HIT 35
#define WEAPON_PEN 55

public void
create_weapon()
{
    set_name("axe");
    add_name("__es_big_black_battleaxe__");
    set_pname("axes");
    add_name("battleaxe");
    add_pname("battleaxes");
    set_adj("blackened");
    set_adj("heavy");
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_short("blackened heavy battleaxe");
    set_pshort("blackened heavy battleaxes");
    set_long("A blackened heavy battleaxe. It is long and extremely " +
        "heavy. Just a bit longer and this axe would qualify as " +
        "a halberd. A gigantic double blade, decorated by eerie " +
        "dragon reliefs topping the long handle " +
        "makes this axe extremely lethal. It can probably hack " +
        "someone in half without any trouble.\n");
    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
    set_wf(this_object());
    set_keep(1);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN) + 1500 +
        random(500));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(WEAPON_PEN, W_AXE) +
        random(5000) + 25000);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 8);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
    add_prop(OBJ_S_WIZINFO,
        "This weapon magically exists in a flux as " +
        "both an axe and a polearm, though it seems to want " +
        "to stay as an axe. A mage tried to change the property " +
        "of this axe and failed. A person that has skill in " +
        "handling polearms will be able to control this strange " +
        "weapon better. Also, because it is made of a " +
        "special enchanted, but extremely dense, alloy, " +
        "it causes severe damage to its victims. " +
        "Its to_hit varies between 35 and 55 depending on " +
        "the polearm skill of the user.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({ "This weapon is magically enchanted.\n", 5,
        "You find that it magically exists " +
        "in a flux as both an axe and a polearm, though " +
        "it seems to want to stay as an axe.\n", 20,
        "It is made of an enchanted, but " +
        "extremely dense, alloy that allows it to " +
        "cause severe damage to its victims.\n", 35,
        "A person that has skill in handling " +
        "polearms will be able to control this strange " +
        "weapon more effectively.\n", 51 }));
}

public string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

public void
init_recover(string arg)
{
    init_wep_recover(arg);
}

public mixed
wield()
{
    object tp = this_player(), to = this_object();

    if(tp->query_stat(SS_STR) < 70)
    {
        return "You lack the strength to wield the blackened " +
            "heavy battleaxe.\n";
    }

    if(tp->query_stat(SS_INT) < 70 ||
        tp->query_stat(SS_WIS) < 90 ||
        tp->query_skill(SS_WEP_AXE) < 75)
    {
        to->move(environment(tp), 1);
        say(QCTNAME(tp) + " fumbles and drops a blackened " +
            "heavy battleaxe.\n");
        return "You try to wield the blackened heavy battleaxe, " +
            "but you can't seem handle it and drop it.\n";
    }

    if(tp->query_stat(SS_DIS) < 70)
    {
        return "The dragon relief glows bright red and you decide " +
            "it's better to not wield it.\n";
    }
    int tohit_bonus = (tp->query_skill(SS_WEP_POLEARM) -
        (tp->query_skill(SS_WEP_POLEARM) % 10)) / 5;
    if (tohit_bonus < 0)
    {
        tohit_bonus = 0;
    }
    set_hit(WEAPON_HIT + tohit_bonus);
    tp->query_combat_object()->cb_update_weapon(to);
    switch (tohit_bonus) {
    case 0:
        write("The axe feels oddly off balance and you are stumped " +
            "as to why. ");
        break;
    case 1..7:
        write("The axe feels oddly off balance and you struggle to " +
            "adjust. ");
        break;
    case 8..14:
        write("The axe feels oddly off balance to you, but you are " +
            "able to make the necessary adjustments. ");
        break;
    default:
        write("The axe feels oddly off balance to you, but your " +
            "expert knowledge of other weapons allows you to tame it. ");
        break;
    }
    write("You feel you like splitting someone in half after " +
            "wielding this axe.\n");
    say(QCTNAME(tp) + "'s eyes flare with the urge to create " +
            "carnage.\n");

    return 1;
}

public int
unwield()
{
    say(QCTNAME(query_wielded()) + " looks normal again.\n");
    set_hit(WEAPON_HIT);
    return 0;
}

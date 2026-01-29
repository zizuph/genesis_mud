/*
 * This is the broken greatsword of Duke Serl Kar-thon, the
 * Praetor-General of the Imperial Armies responsible for the
 * invasion of the Tower of High Sorcery of Daltigoth.
 *
 * This is the same weapon that appears as an illusionary weapon 
 * created as part of the Test of High Sorcery (easter egg).
 *
 * Arman Kharas, Jan 2021
 */
 
inherit "/std/weapon";

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_weapon()
{
    // The sword is broken. Potentially able to be reforged through a
    // quest.
    add_prop(OBJ_I_BROKEN, 1);

    set_name("greatsword");
    set_adj("heavy");
    add_adj("runed");
    add_name("sword");
    set_short("heavy runed greatsword");
    set_long("@@query_sword_broken");       

    set_hit(60);
    set_pen(60);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 12500);
    add_prop(OBJ_I_VOLUME, 14000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(60, 60));
    add_prop(OBJ_M_NO_SELL, 1);



    add_prop(MAGIC_AM_MAGIC,({60, "enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,({
        "The " + TO->query_short() + " appears to be magical in some way. ", 1,
        "This greatsword is an ancient relic of the Age of Dreams, rivalled " +
        "only by the greater Dragonlances! Last wielded by Duke Serl Kar-thon, " +
        "Praetor-General of the Imperial Armies of Ergoth, it was broken " +
        "through a cataclysmic magical explosion during the invasion of " +
        "the Tower of High Sorcery in Daltigoth. You detect the magic of " +
        "the blade has not dissipated, so may be reforged with the right " +
        "material and a skilled smith.\n", 45 }));
    add_prop(OBJ_S_WIZINFO,"This is a bit of an easter egg for for WoHS, " +
        "where they may have come across an illusionary version of this blade " +
        "in their Test.\n");
}

string
query_sword_broken()
{
    string str;

        str = "An incredible weapon! This greatsword has a blade over a " +
        "meter in length, covered in runes glowing a furious red. So " +
        "sharp it looks it could carve though thick steel like " +
        "parchment - a sword rivalled by nothing you have seen before. " +
        "Wicked parrying hooks protrude just above its large guard, " +
        "with a heavy steel pommel balancing the weight of the blade " +
        "at the end of comfortably long two-handed handle.";

    if(TO->query_prop(OBJ_I_BROKEN))
        str += " It looks like it has been snapped by a " +
            "cataclysmic magical force.\n";
    else
        str +="\n";

    return str;
}
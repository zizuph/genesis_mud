/* This is a magic cloak for the alchemist of Rust. 
It provides quite a bit of protection, for mages.
Made by Bishop of Calia, 5/1/99 */


inherit "/std/armour";

#include <wa_types.h>       
#include <formulas.h>      
#include <stdproperties.h>  
#include <macros.h>
#include <ss_types.h>
#include "defs.h"

int prot = 0;

void
set_protection()
{
    object wearer;
    wearer = environment(TO);

    if (wearer->query_skill(SS_SPELLCRAFT) < 49)
    {
        prot = 0;
        TO->set_ac(0);
    }
    else
    {
        prot = (wearer->query_skill(SS_SPELLCRAFT) / 2);
        TO->set_ac(prot);
    }
}

varargs int 
got_hit(int hid, int ph, object att, int dt, int dam)
{
    int red, mred;
    object wearer;
    mred = TO->query_ac();
    red  = (dam * mred / 100);
    wearer = query_worn();
    wearer->heal_hp(red);

    if (red > 0)
    {
// I'm not sure if these messages should be here. It does spam
// combat a little. At any rate, they are easily removed.

        wearer->catch_msg("The blow seems to diminish" +
            " in the folds of your cloak.\n");
        tell_room(environment(wearer), "The blow seems to" +
            " diminish in the folds of " + QTNAME(wearer) +
            "'s cloak.\n", wearer);
    }
    ::got_hit(hid, ph, att, dt, dam);
}

void
create_armour()
{
    set_name("cloak");

    set_adj("grey");
    set_adj("silver");
    set_adj("@@adj@@");

    set_long("This silver grey cloak is a superb piece of" +
        " craftsmanship. It seems to have been crafted out of a" +
        " single sheet of material, for you can find neither" +
        " stitch nor seam on it." +
        "@@cloak_descrip@@"); 

    set_ac(prot);
    set_at(A_ROBE);
    set_am(({ 0,0,0 }));
    set_wf(TO);

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 5000);
    add_prop(MAGIC_AM_MAGIC, ({	35, "enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, "This cloak is a normal, AC 0 cloak" +
        " up to the point where it is worn by someone with at" + 
        " least 50 skill in spellcraft. Then it has AC equal to" +
        " half the wearer's spellcraft, in addition all blows" +
        " that hit the cloak are reduced in damage by a percentage" +
        " equal to the cloak's AC.\n");
    add_prop(MAGIC_AM_ID_INFO, ({"A powerful enchantment has been" +
        " laid upon this cloak.", 15, "This enchanted cloak" +
        " provides special benefits for those versed in arcane lore."
        , 30, "This enchanted cloak will serve as powerful armour" +
        " for those versed in arcane lore.", 45, "This" +
        " cloak serves as powerful armour for those versed in" +
        " the arcane, and has been further enchanted to magically" +
        " cushion blows.", 75}));


}

string
adj()
{
    if(prot > 0 && query_worn() != 0)
    {
        return "flowing";
    }
    else
    {
        return "limp";
    }
}

string
cloak_descrip()
{
    object wearer;
    wearer = query_worn();
    
    if (wearer == 0)
    {
        return "\n";
    }
    else
    if (prot == 0)
    {
        return " It is hanging rather limply from your shoulders.\n";
    }
    else
    {
        return " It is flowing and swirling as if it has a life of" +
            " it's own.\n";
    }
}

mixed
wear(object ob)
{
    wearer = environment(TO);
    set_protection();

    if (prot > 0)
    {
        wearer->catch_msg("The cloak seems to come to life as you" +
            " wear it.\n");
        tell_room(environment(wearer), "The limp silver cloak" +
            " seems to come to life as " + QTNAME(wearer) +
            " wears it.\n", wearer);
    }
    else
    {
        wearer->catch_msg("You wear the limp silver cloak.\n");
        tell_room(environment(wearer), QCTNAME(wearer) + " wears" +
            " the limp silver cloak.\n", wearer);
    }
    return 1;
}

mixed
remove(object ob)
{
    wearer = query_worn();
    
    if(prot > 0)
    {
        wearer->catch_msg("The cloak goes limp again as you remove" +
            " it.\n");
        tell_room(environment(wearer), "The flowing silver cloak" +
            " goes limp again as " + QTNAME(wearer) + " removes" +
            " it.\n", wearer);
    }
    else
    {
        wearer->catch_msg("You remove the limp silver cloak.\n");
        tell_room(environment(wearer), QCTNAME(wearer) + " removes" +
            " the limp silver cloak.\n", wearer);
    }
    return 1;
}
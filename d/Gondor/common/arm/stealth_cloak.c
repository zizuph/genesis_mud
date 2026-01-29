/*
 * /d/Gondor/common/arm/stealth_cloak.c
 *
 * A cloak that increases hide and sneak skills when worn
 * following an example by Xeros
 * The description follows the cloaks from Lorien
 *
 * Xeros and Olorin, 1-nov-1993
 */
#pragma strict_types

inherit "/std/armour.c";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define ENHANCE      25   /* the value by which the skills is enhanced */
#define MIN_SKILL    50   /* the mimimun value of hide and sneak to be able to use 
                             magical properites of the armour */
#define MAX_SKILL   100   /* the maximum value of the skill that can be reached */

static  int     addhide  = 0, /* did I add the skill_extra? 0 = no */
                addsneak = 0; /* did I add the skill_extra? 0 = no */

void
create_armour()
{
    /* This armour, while providing low protection, enchances the stealth
       capabilities of the wearer, or provides some low level stealth
       abilities to those lacking them entirely */
    set_name("cloak");       
    add_name(({"robe","garment"}));
    set_pname("cloaks");
    add_pname("robes");
    add_pname("garments");
    set_adj(({"light", "fair","elven","warm","silken","grey","green","brown","dusk-silver","elvish"}));
    set_short("light cloak");
    set_long(BSN(
        "This light and fair garment is made of a light but warm silken stuff. " +
        "It is hard to say of which colour it is; " +
        "grey with the hue of twilight it seems to be; and yet " +
        "if it is moved, or set in another light, it is green as shadowed leaves, or " +
        "brown as fallowed fields by night, dusk-silver as water under the stars."));

    set_ac(5);
    set_at(A_ROBE);
    set_af(TO);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) + random(200) + 500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1500);             
    add_prop(MAGIC_AM_MAGIC,(({55,"enchantment"})));

    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_ID_INFO, ({
          "The "+short()+" seems to be mysteriously enchanted.\n", 1,
          BSN("For a skilled bearer, the cloak will aid in keeping out " +
          "of the sight of unfriendly eyes."), 30,
          BSN("If you are skilled, then this elven cloak will increase " +
          "your ability to hide yourself and to move stealthily."),50}));
    add_prop(OBJ_S_WIZINFO, "This cloak enhances the wearers sneak " +
             "and hide skills. Minimun skill requirement of 50 in each. " +
             "Adds either 25 or 100 - query_skill_level, which ever is less. " +
             "This item is not in the game yet.\n");
}

public int
wear(object arm)
{
    int     ihide   = (TP->query_base_skill(SS_HIDE) > MIN_SKILL),
            isneak  = (TP->query_base_skill(SS_SNEAK) > MIN_SKILL);

    if(!isneak && !ihide)
        return 0;
    else
    {
        if(isneak)
        {
            addsneak = MIN(ENHANCE, MAX_SKILL - TP->query_base_skill(SS_SNEAK));
            if(addsneak)
                TP->set_skill_extra(SS_SNEAK,TP->query_skill_extra(SS_SNEAK) + addsneak);
        }
        if(ihide)
        {
            addhide = MIN(ENHANCE, MAX_SKILL - TP->query_base_skill(SS_HIDE));
            if(addhide)
                TP->set_skill_extra(SS_HIDE,TP->query_skill_extra(SS_HIDE) + addhide);
        }
        if(addhide || addsneak)
            write("You wear the "+short()+".\n"+
                  BSN("The shifting colours of the cloak enable you to blend better " +
                  "into your surroundings."));
        SAY(" wears the " + short() );
    }
    return 1;
}

int remove(object arm)
{
    
    if(addsneak || addhide)
    {
        if(addsneak)
        {
            wearer->set_skill_extra(SS_SNEAK,wearer->query_skill_extra(SS_SNEAK) - addsneak);
            addsneak = 0;
        }
        if(addhide)
        {
            wearer->set_skill_extra(SS_HIDE,wearer->query_skill_extra(SS_HIDE) - addhide);
            addhide = 0;
        }
        wearer->catch_msg("You remove the "+short()+" and feel less able to hide yourself.\n");
        SAY(" removes the " + short());
        return 1;
    }
    return 0;
}

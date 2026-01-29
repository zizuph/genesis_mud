inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

/* Stealth enhancing armour written and produced by Xeros of GondorMud
debugging and some coding/testing (mainly the add skill part ;) )
courtesy of Olorin, of Genesis and GondorMud. 1 Nov 1993 */
  
#define ENHANCE      20   /* the value by which the skills is enhanced */
#define MIN_SKILL    50   /* the minimum value of hide and sneak to be able to use
                             magical properites of the armour */
#define MAX_SKILL   81 /* the max value of hdie and sneak to be able to benefit */

static  int     addhide  = 0, /* did I add the skill_extra? 0 = no */
                addsneak = 0; /* did I add the skill_extra? 0 = no */

void
create_armour()
{
    /* This armour, while providing low protection, enchances the stealth
       capabilities of the wearer, or provides some low level stealth
       abilities to those lacking them entirely */
    set_name("suit");
    set_pname("suits");
    set_short("brigandine suit");
    set_long(BSN("This painstakingly crafted suit of brigandine armour " +
        "is formed of dual plates of hard leather sandwiched with hundreds "+
        "of tiny steel plates. It would seem to provide excellent protection "+
        "against slashing attacks, but only mediocre protection against "+
    "bludgeoning or impaling attacks. Whether from the type of leather used "+
    "or how the plates are set, this suit of armour fairly ripples through "+
     "every colour known to Man, Dwarf, Hobbit, and Elf."));

    set_adj("leather");
    add_adj("shimmering");
    set_ac(27);
    set_am(({1,2,-2}));
    set_at(A_BODY);
    set_af(TO);

    add_prop(OBJ_I_VALUE, 1000+random(500));
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(MAGIC_AM_MAGIC,(({55,"enchantment"})));

    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_ID_INFO,
        ({"The suit of armour radiates magic.\n", 1,
          "It enhances stealth capabilites in those skilled enough to use it.\n", 35}));
    add_prop(OBJ_S_WIZINFO, "This suit of armour enhances a players sneak " +
             "and hide. Minimum skill requirement of 50, and adds 20 to " +
             "both skills. This item is not in the game yet.\n");
}

public int
wear(object arm)
{
    int     ihide   = (TP->query_skill(SS_HIDE) > MIN_SKILL),
            isneak  = (TP->query_skill(SS_SNEAK) > MIN_SKILL);
    int inhide = (TP->query_skill(SS_HIDE) > MIN_SKILL & TP->query_skill(SS_HIDE) < MAX_SKILL),
        insneak = (TP->query_skill(SS_SNEAK) > MIN_SKILL & TP->query_skill(SS_SNEAK) < MAX_SKILL);

    if(!insneak && !inhide) {
        WRITE("You buckle on the "+short()+" of armour. While you feel fully "+
        "protected, you don't feel that you are benefitting fully from the suit.");
        SAY(" buckles on a "+short()+" of armour.");
        }
    else
    {
        if(insneak)
        {
            TP->set_skill_extra(SS_SNEAK,TP->query_skill_extra(SS_SNEAK) + ENHANCE);
            addsneak = 1;
        }
        if(inhide)
        {
            TP->set_skill_extra(SS_HIDE,TP->query_skill_extra(SS_HIDE) + ENHANCE);
            addhide = 1;
        }
        WRITE("You buckle on the "+short()+" of armour, watching the "+        
        "shimmering hues in the material ripple in amazement.");
        SAY(" buckles on "+POSSESSIVE(TP)+" "+short()+" of armour, appearing "+
        "slightly out of focus as "+PRONOUN(TP)+" does so.");
    return 1;
    }
    return 1;
}

int remove(object arm)
{

    if(addsneak || addhide)
    {
        if(addsneak)
        {
            TP->set_skill_extra(SS_SNEAK,TP->query_skill_extra(SS_SNEAK) - ENHANCE);
            addsneak = 0;
        }
        if(addhide)
        {
            TP->set_skill_extra(SS_HIDE,TP->query_skill_extra(SS_HIDE) - ENHANCE);
            addhide = 0;
        }
        WRITE("You remove your "+short()+", wishing you did not have to "+
        "take it off your body.");
        SAY(" unbuckles "+POSSESSIVE(TP)+" "+short()+", looking pretty sad "+
        "as "+PRONOUN(TP)+" comes back into clearer focus.");
        return 1;
    }
    WRITE("You unbuckle the straps on your "+short()+" of armour.");
    SAY(" unbuckles "+POSSESSIVE(TP)+" "+short()+" of armour.");
    return 1;
}

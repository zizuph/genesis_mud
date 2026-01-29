/* 
 * File: firebane_cloak.c
 * A firebane cloak, worn by elves in Qualinesti.
 * 
 * Originally:
 * The cloak increases fire resistance by 20, and SS_HIDE by maximum 
 * value of 20. It also can be sold only to elves or half-elves.
 *
 * Blizzard, 02/2003
 *
 *
 * Note by Navarre, November 22th 2005:
 *
 * This item was one of many inappropriate items that was created.
 * It originally made only elves or half-elves able to buy it. Quite a
 * strange restriction to put on an armour.
 *
 * It also had 20 levels of hide, which I lowered to 10.
 * It also had 20 levels of fire protect, which I lowered to 10.
 * I altered the magical information about the ring, and to keep it magic
 * I have added a little amount of panic to the player as he wears it.
 */

/* Navarre July 3rd 2006, fixed typo */

 
inherit "std/armour.c";
inherit "/lib/keep";

#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

#define BONUS_SKILL  10
#define MAX_SKILL   100

int add_skill = 0; 

void
create_armour()
{
    set_name("cloak");
    set_pname("cloaks");
    set_short("earth-colored firebane cloak");
    set_pshort("earth-colored firebane cloaks");
    add_adj(({ "earth-colored", "elven", "firebane", "earth" }));
    set_ac(25);
    set_at(A_ROBE);
    set_af(TO);
    set_keep(1);
    
    set_long("This firebane cloak is treated with heat-absorbing oils " +
        "from the elathas plant. Thanks to its earth toned color, the " +
        "cloak makes the wearer almost undetectable, especially in forests. " +
        "Also, as most items of elven making, this " +
        "cloak is very light but you should not worry that it may be " +
        "pierced easily by a blade of an average quality.\n");
        
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, "This cloak enhances the wearer's hide skill. " +
        "It adds either 10 or 100 - query_skill, choosing the less value. " +
        "The cloak was treated by heat absorbing oils so it also increases " +
        "the fire resistance by 10. It can be sold only to elves and " +
        "half-elves.\n");
    add_prop(MAGIC_AM_ID_INFO, ({
        "The " + short() + " seems to be magically enhanced.\n", 1,
        "It will make the wearer blend into surrounding easier.\n", 15,
        "The cloak offers the wearer some protection against fire.\n", 30 }));
        
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25) + random(200) + 300);
}

varargs mixed
query_magic_protection(string prop, object what)
{
    if ( what == query_worn() && prop == MAGIC_I_RES_FIRE )
        return ({ 10, 1 });
    
    return ::query_magic_protection(prop, what);
}

public int
wear(object arm)
{
  /* We check if after wearing the player do not have more than sup guru
     in SS_HIDE skill. We choose the minimal value as an additional skill */
     
    if ( (MAX_SKILL - TP->query_base_skill(SS_HIDE)) > BONUS_SKILL )
        add_skill = BONUS_SKILL;
    else 
        add_skill = MAX_SKILL - TP->query_base_skill(SS_HIDE);
    
    write("You wear the " + short() + ", drawing it tightly about your " +
        "body.\n");  
    say(QCTNAME(TP) + " draws the " + short() + " tightly about " +
        POSSESSIVE(TP) + " body.\n");
    
    TP->set_skill_extra(SS_HIDE, TP->query_skill_extra(SS_HIDE) + add_skill);
    
    TP->add_magic_effect(TO);
        
    return 1;
}

int
remove(object what)
{
    wearer->remove_magic_effect(TO);
    wearer->set_skill_extra(SS_HIDE, wearer->query_skill_extra(SS_HIDE) -
        add_skill);
        
    return 0;
}

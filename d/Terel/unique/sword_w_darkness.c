/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * sword.c
 *
 * The famous darkness sword of the goblin eldar.  The idea with this sword
 * is that it should become dark when it it is wielded.
 *
 * The original code for this sword has been worked on by Commander,
 * Vader and Olorin.
 * Updated by Shinto 9-27-98
 *  -added undead check
 *  -raised hit and pen to 45
 * Updated by Lilith 5 June 2008
 *  -changed ETO to query_wielded
 * Updated by Lilith 16 Nov 2008
 *  -added darksight to wielder
 *  -added change to hit/pen when wielded by 'right' person
 * Updated by Lilith Dec 2008
 *  -updated leave_env check
 * Updated by Cotillion, Apr 2009
 *  -New darkness level.
 * Updated by Petros, May 2009
 *  -Adjusted hit/pen so non-undead use is still reasonable
 *  -Remove see-dark properties
 * Updated by Petros, December 2009
 *  - When killed with weapon wielded, this_player() is actually
 *    set to the killer, rather than the wielder. Correctly give
 *    a message for unwielding.
 * Updated by Petros, April 2010
 *  - Sword was still using "write" and writing the wrong messages.
 *    Fixed so it now calls catch_tell to query_wielded
 * Updated by Shanoga, November 2018
 *  - Sword was not using standard recovery and was re-randoming
 *    the hit/pen values on each recovery. Fixed so the initial
 *    random values are maintained through the life of the weapon.
 * Updated by Lilith, Feb 2022
 *  - made a spell enhancer lvl
 * Updated by Lilith, May 2022
 *  - forgot to update the stat_object to show the enhancer info.
 *
 */

#include <const.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

// Global variables
public int      original_pen = 42 + random(4);
public int      original_hit = 42 + random(4);
public int      max_pen = 45 + random(6);
public int      max_hit = 45 + random(6);

/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
void 
create_weapon()
{
    ::create_weapon();

    set_wf(TO);   /* Will force call of wield() and unwield() */
    set_name("longsword");
    add_name("sword");
    set_adj(({"black","obsidian"}));
    set_adj("darkness");
    set_short("obsidian longsword");
    set_pshort("obsidian longswords");
    set_long("It is made of black obsidian. This sword brings darkness " +
      "and death.\n");
    set_pname(({"longswords","obsidian longswords","swords"}));
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_S_WIZINFO, "This sword adds darkness for undead "+
        "and for those with death spells > 20. It is also a more "+
        "deadly weapon in their hands with hit-pen going from 42ish to 50. "+
        "It is cloned by the Goblin Eldar in the Terel mountains.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
        ({"The obsidian is enchanted in such a way that it will absorb light "+
        "when held. It is also a better weapon in the hands of the undead "+
        "or those with a mastery of death.\n",20}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    /* hit and pen increased and decreased in the wield and unwield */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hit(original_hit);
    set_pen(original_pen);
    set_magic_spellpower(45);
    set_hands(W_RIGHT);
    set_likely_break(0);
    set_likely_dull(0);
    set_keep();
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(max_pen, query_wt()));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(max_hit, max_pen));
    add_prop(OBJ_I_VOLUME, 1000);
}

public mixed
wield(object wep)
{
    if(this_player() != environment(this_object()))
        return 0;

    // Darkness is added whenever this sword is wielded
    add_prop(OBJ_I_LIGHT, DARKNESS_PASSIVE);
    this_player()->update_light(1);
    write("As you wield the " + short() + ", it grows cold as ice in your "
        + "hand and absorbs the light around you.\n");
    tell_room(environment(this_player()), "The light in the room is "
        + "suddenly absorbed as " + QTNAME(this_player()) + " wields "
        + "the " + short() + ".\n", this_player());
    
    if (this_player()->query_skill(SS_ELEMENT_DEATH) > 20 ||
        this_player()->query_prop(LIVE_I_UNDEAD)) 
    {
        set_hit(max_hit);
        set_pen(max_pen);
    }
    
    return 1;                   /* Do not affect rest of wield sequence */
}

public mixed
unwield(object wep)
{
    set_hit(original_hit);
    set_pen(original_pen);

    object player = query_wielded();
    if (query_prop(OBJ_I_LIGHT) == DARKNESS_PASSIVE) 
    {
        add_prop(OBJ_I_LIGHT, 0);
        query_wielded()->update_light(1);
        query_wielded()->catch_tell("The darkness surrounding the blade "
            + "disappears as you unwield it.\n");
        if (objectp(player))
        {            
            tell_room(environment(player), "The darkness surrounding "
                + "you retreats as " + QTNAME(player) + " unwields the "
                + short() + ".\n", player);
        }
            
        return 1;
    }
    
    return 0;                   /* Do not affect rest of unwield sequence */
}

/* Sometimes there is bad interaction with other items 
 * and the light does not update correctly. Lets see if 
 * changing ETO to query_wielded() corrects the problem.
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    
    if (from && living(from)) 
    {
        set_hit(original_hit);
        set_pen(original_hit);
        add_prop(OBJ_I_LIGHT, 0);
        query_wielded()->update_light(1);
        from->update_light(1);  
        to->update_light(1);   
    }
}

/*
 * Function name: query_recover
 * Description  : Sets the keep state and the hit/pen values so they
 *                are recovered properly.
 * Returns      : string - the recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover() +
        "&&" + original_hit + "&&" + original_pen + "&&" + max_hit +
        "&&" + max_pen;
}

/*
 * Function name: init_recover
 * Description  : Restores the initial hit/pen and keep values upon recovery
 * Arguments    : string - the recovery string.
 */
public void
init_recover(string arg)
{
    string *a = explode(arg, "&&");
    
    if (sizeof(a) > 1)
    {
        original_hit = atoi(a[1]);
        original_pen = atoi(a[2]);
        max_hit = atoi(a[3]);
        max_pen = atoi(a[4]);
        set_hit(original_hit);
        set_pen(original_pen);

        init_wep_recover(a[0]);
        init_keep_recover(a[0]);
    }
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



/* 
 * c_warhammer.c
 *
 *  The glistening crystal warhammer, a powerful club
 *  if you are good aligned and got decent spellcraft
 *  skill. It got a damage special attack.
 *
 * Baldacin@Genesis, Sep 2003
 *
 * 2007-07-31 - Cotillion
 * - This weapons was severly out of balance.
 *   It had a 55% chance to do an extra 130% damage on every
 *   swing. This is obviously not ok, the numbers have been adjusted.
 *   The monster guarding it is also more difficult now.
 *
 * 2007-08-08 - Navarre
 * - Replaced 'TP' to 'wielder' from the wield and unwield functions.
 *   It was causing runtimes when the the wielder quit with it.
 * 2009-09-17 - Petros
 * - Made the weapon keepable so that it won't be sold accidentally.
 * - Removed alignment restriction.
 * 2020-12-21 - Cotillion
 * - Fixed issue with recovery which didn't include standard weapon 
 *   recovery.
 */


inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";
#include "../ldefs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

#define HIT             40  /* Weapon hit value */
#define PEN             40  /* Weapon pen value */
#define SPELLCRAFT_REQ  65  /* Wield requirement, skill - spellcraft */
#define FAIL_WIELD_DMG  350 /* Damage dealth when failing to wield it */
#define SPEC_CHANCE    (random(100) < 15) /* The chance that the special hit */
#define DAMAGE_CALC(i) (((i) * 130) / 100) /* For special attack */


/*
 * Function name: create_weapon
 * Description  : Create the weapon. You must define this function to
 *                construct the weapon.
 */
public void
create_weapon()
{
    set_name("warhammer");
    add_name(({"club", "hammer", "crystal_warhammer_"}));
    set_adj(({"glistening", "crystal"}));
    set_short("glistening crystal warhammer");
    set_long("@@get_long_desc@@\n");
    
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    set_wf(TO);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen())+random(400));
    add_prop(OBJ_I_WEIGHT, 6500);
    add_prop(OBJ_I_VOLUME, 5450);
    add_prop(OBJ_M_NO_BUY, 1);

    /* Oh, yeah. It's a magical weapon */
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO, ({"This club must be enchanted.\n",10, 
      "The creator of this weapon must have enchanted it with "+
      "a very powerful spell. The origin of the spell is "+
      "unfortunately unknown.\n",20, 
      "This weapon is enchanted by a very powerful spell, making "+
      "it a very dangerous weapon. You will have to be skilled "+
      "in the art of spellcasting to wield it though.\n",40}));
    add_prop(MAGIC_AM_MAGIC, ({60, "enchantment"}));
    
    add_prop(OBJ_S_WIZINFO, "This warhammer(40/40) will require pretty high "+
      "spellcraft skill and good align, see the defines at the top of "+
      "the file for specific information.\n");

    add_item(({"magnificent pattern", "pattern"}),"The decorating gems and pearls "+
      "forms a magnificent pattern, resembling an ancient dragon.\n");
      
    set_keep(1); // make the item by default kept
    
    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(40);
}

/*
 * Function name: get_glow
 * Description  : Queries the weapons glow colour. It will return
 *                crimson red when the player is below the alignment
 *                requirement And blueish colours for good aligns.
 * Arguments    : int i - the alignment of the player to check.
 * Returns      : string - the colour of the glow.
 */
string
get_glow(int i)
{
    switch(i)
    {
        case -1200..199:
            return "crimson red";
        break;
        case 200..300:
            return "pale-blue";
        break;
        case 301..400:
            return "light-blue";
        break;
        case 401..500:
            return "dark-blue";
        break;
        default:
        break;
    }
    return "deep-blue";
}

/*
 * Function name: get_long_desc
 * Description  : Queries the long description of the warhammer.
 *                changes if the weapon is wielded or not wielded.
 * Returns      : string - the long desc of the warhammer.
 */
string
get_long_desc()
{
    /* When wielded it emits a glow */
    return "This warhammer is crafted of pure crystal with great "+
      "expertise. It is quite short for a warhammer, only about the "+
	  "length of an average mans arm. The handle has been decorated "+
	  "with gems and pearls, forming a magnificent pattern.\n"+
      (query_wielded() ? " It is emitting a "+get_glow(TP->query_alignment())+
      " glow.":"");        
}

/* 
 * Function name: wield
 * Description  : This function might be called when someone tries to wield
 *                this weapon. To have this function called, use the function
 *                set_wf().
 * Arguments    : object obj - the weapon someone tried to wield.
 * Returns      : int  0 - wield this weapon normally.
 *                     1 - wield the weapon, but print no messages.
 *                    -1 - do not wield the weapon, use default messages.
 *                string - do not wield the weapon, use this fail message.
 */

public mixed
wield(object obj)
{ 
    if (wielder->query_skill(SS_SPELLCRAFT) < SPELLCRAFT_REQ)
    {
    	/* 
    	 * The player did not have the required skill  
    	 * - Don't wield the warhammer and hurt the player a little :) 
    	 */
    	wielder->heal_hp(-FAIL_WIELD_DMG);
        say("As "+QTNAME(wielder)+" wields the "+short()+" a burning "+
          get_glow(wielder->query_alignment())+" glow emits from it, "+
          "burning "+HIM(wielder)+", forcing "+HIM(wielder)+" to unwield it "+
          "again.\n");
        return "As you wield the "+short()+" a burning "+
          get_glow(wielder->query_alignment())+" glow emits from "+
          "it, burning you, forcing you to unwield it again.\n";
    }
    else
    {
    	/* The player had the required skill
    	   - Let's wield the warhammer */
    	say("As "+QTNAME(wielder)+" wields the "+short()+" a "+
    	  get_glow(wielder->query_alignment())+ " glow emits from "+
    	  "it, warming "+HIS(wielder)+" soul.\n");
    	write("As you wield the "+short()+" a "+
    	  get_glow(wielder->query_alignment())+ " glow emits from "+
    	  "it, warming your soul.\n");
    	return 1;
    }   

}

/*
 * Function name: unwield
 * Description  : This function might be called when someone tries to unwield
 *                this weapon. To have this function called, use the function
 *                set_wf().
 * Arguments    : object obj - the weapon to stop wielding.
 * Returns      : int  0 - the weapon can be unwielded normally.
 *                     1 - unwield the weapon, but print no messages.
 *                    -1 - do not unwield the weapon, print default messages.
 *                string - do not unwield the weapon, use this fail message.
 */
public mixed
unwield(object obj)
{
    say("The "+get_glow(wielder->query_alignment())+ " glow surrounding "+
      "the "+short()+" fades away as "+QTNAME(wielder)+" unwields it.\n");
    write("The "+get_glow(wielder->query_alignment())+ " glow surrounding "+
      "the "+ short() +" fades away as you unwield it.\n");
    return 1;
}

/*
 * Function name: did_hit
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. If the weapon
 *                chooses not to handle combat messages then a default
 *                message is generated.
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                dam:   The actual damage caused by this weapon in hit points
 *                hid:   The hitlocation id
 * Returns:       True if it handled combat messages, returning a 0 will let
 *                the normal routines take over
 */
public varargs int
did_hit(int aid, string hdesc, int phurt,  object enemy,
int dt, int phit, int dam)
{
    mixed* hitres;
    object me = query_wielded();
    int damage = 1;
    string msg1, msg2, msg3;
    
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    /* If the enemy or the wielder isnt a object, bail out! */    
    if ((!objectp(enemy)) || (!objectp(me)))
         return 0;
    
    /* Here's the chance that the special hits */
    if (!SPEC_CHANCE)
	return 0;
    
    /* Lets use the original damage, but boost it a little */           
    if (dam)
        damage = DAMAGE_CALC(dam);
    
    /* Powah! This do the actual damage to the enemy */
    hitres = enemy->hit_me(damage, dt, me, aid);
    
    switch(hitres[0])
    {
        case -1..0:
            msg1 = "The "+get_glow(me->query_alignment())+" glow grows "+
              "stronger as you aim your "+short() +" towards "+
              QTPNAME(enemy)+" "+hdesc+ ", missing it by an inch.\n";
            msg2 = "The "+get_glow(me->query_alignment())+" glow grows "+
              "stronger as "+QTNAME(me)+" aims "+HIS(me)+" "+short()+
              " towards your "+hdesc+", missing it by an inch.\n";
            msg3 = "The "+get_glow(me->query_alignment())+" glow grows "+
              "stronger as "+QTNAME(me)+" aims "+HIS(me)+" "+short()+
              " towards "+QTPNAME(enemy)+" "+hdesc+ ", missing it by an inch.\n";
        break;
        case  1..8:
            msg1 = "The "+get_glow(me->query_alignment())+" glow grows "+
              "stronger as you swing your "+short() +" towards "+
              QTNAME(enemy)+", bashing "+HIS(enemy)+ " "+hdesc+
              " lightly.\n";
            msg2 = "The "+get_glow(me->query_alignment())+" glow grows "+
              "stronger as "+QTNAME(me)+" swings "+HIS(me)+" "+short()+
              " towards you, bashing your "+hdesc+" lightly.\n";
            msg3 = "The "+get_glow(me->query_alignment())+" glow grows "+
              "stronger as "+QTNAME(me)+" swings "+HIS(me)+" "+short()+
              " towards "+QTNAME(enemy)+", bashing "+HIS(enemy)+" "+hdesc+
              " lightly.\n";
        break;
        case  9..15:
            msg1 = "The "+get_glow(me->query_alignment())+" glow surrounding "+
              "the "+short() +" grow stronger as you quickly dodge "+
              QTPNAME(enemy)+" attack and rapidly counter-attack with a "+
              "blow to "+HIS(enemy)+" "+hdesc+".\n";
            msg2 = "The "+get_glow(me->query_alignment())+" glow surrounding "+
              "the "+short() +" grow stronger as "+QTNAME(me)+" quickly dodges "+
              "your attack and rapidly counter-attack with a blow to your "+hdesc+".\n";
            msg3 = "The "+get_glow(me->query_alignment())+" glow surrounding "+
              "the "+short() +" grow stronger as "+QTNAME(me)+" quickly dodges "+
              QTPNAME(enemy)+" attack and rapidly counter-attack with a "+
              "blow to "+HIS(enemy)+" "+hdesc+".\n";
        break;
        case 16..26:
            msg1 = "The " +short()+" emits a stronger "+get_glow(me->query_alignment())+
              " glow as you exploit an opening in "+QTPNAME(enemy)+" defences "+
              "and violently lambaste "+HIS(enemy)+" "+hdesc+", inflicting "+
              "a painful bruise.\n";
            msg2 = "The "+short()+" emits a stronger "+get_glow(me->query_alignment())+
              " glow as "+QTNAME(me)+" exploits an opening in your defences and "+
              "violently lambastes your "+hdesc+", inflicing a painful bruise.\n";
            msg3 = "The "+short()+" emits a stronger "+get_glow(me->query_alignment())+
              " glow as "+QTNAME(me)+" exploits an opening in "+QTPNAME(enemy)+
              " defences and violently lambastes "+HIS(enemy)+ " "+hdesc+", inflicting "+
              "a painful bruise.\n";
        break;
        case 27..45:
            msg1 = "The "+get_glow(me->query_alignment())+" glow suddenly "+
              "grow stronger as you swiftly throw yourself to the side. "+
              "Avoiding "+QTPNAME(enemy)+" attack, you brutally smash your "+
              short()+" at "+HIS(enemy)+ " "+hdesc+".\n";
            msg2 = "The "+get_glow(me->query_alignment())+" glow suddenly "+
              "grow stronger as "+QTNAME(me)+" swiftly throw "+HIM(me)+"self "+
              "to the side. Avoiding your attack, "+HE(me)+" brutally smash "+
              HIS(me)+" "+short()+" at your "+hdesc+".\n";
            msg3 = "";
        break;
        case 46..70:
            msg1 = "The "+get_glow(me->query_alignment())+" glow suddenly "+
              "grow stronger as you sidestep "+QTPNAME(enemy)+" defences "+
              "with amazing speed and badly crush "+HIS(enemy)+" "+hdesc+
              " with your "+short()+".\n";
            msg2 = "The "+get_glow(me->query_alignment())+" glow suddenly "+
              "grow stronger as "+QTNAME(me)+" sidesteps your defences "+
              "with amazing speed and badly crush your "+hdesc+" with "+
              HIS(me)+" "+short()+".\n";
            msg3 = "The "+get_glow(me->query_alignment())+" glow suddenly "+
              "grow stronger as "+QTNAME(me)+" sidesteps "+ QTPNAME(enemy) +
              " defences with amazing speed and badly crush "+HIS(enemy)+
              " "+hdesc+" with "+HIS(me)+" "+short()+".\n";
        break;
        default:
            msg1 = "The "+get_glow(me->query_alignment())+" glow grows "+
              "stronger as you notice a big opening in "+QTPNAME(enemy)+
              " defence and quickly pound your "+short()+" into "+
              HIS(enemy)+" "+hdesc+", nearly thrashing it.\n";
            msg2 = "The "+get_glow(me->query_alignment())+" glow grows "+
              "stronger as "+QTNAME(me)+" notice a big opening in your "+
              "defences and quickly pound "+HIS(me)+" "+short()+" into "+
              "your "+hdesc+", nearly thrashing it.\n";
            msg3 = "The "+get_glow(me->query_alignment())+" glow grows "+
              "stronger as "+QTNAME(me)+" notice a big opening in "+
              QTPNAME(enemy)+" defences and quickly pound "+HIS(me)+" "+
              short()+" into "+HIS(enemy)+" "+hdesc+", nearly thrashing it.\n";
    }
   
   if (interactive(me))         /* Wielder */
       me->catch_msg(msg1);     
   if (interactive(enemy))      /* Enemy */
       enemy->catch_msg(msg2);  
   me->tell_watcher(msg3);      /* Watchers */

/* Whups, the enemy died */ 
   if (enemy->query_hp() <= 0)
       enemy->do_die(me);
   
   return 1;
}

/*
 * Function:    query_recover
 * Description: Save the recover attributes.
 */
public string
query_recover()
{
    return ::query_recover() + query_keep_recover();
}

/*
 * Function:    init_recover
 * Description: Restore the item attributes during recovery
 */
public void
init_recover(string arg)
{
    ::init_recover(arg);
    init_keep_recover(arg);
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}


/* /d/Avenir/common/dark/obj/gavriels_knife.c
 *
 *  Blade of Gavriel, former Mystic Cantor, who was blinded
 *  and wanders the Underdark in a state of eternal grief
 *  over the loss of the Valley of the Ancients.
 *
 *  Magical enhancing weapon with darkvision.
 *  Approved by Arman 9 Feb 2022.
 *
 *  Created by Lilith, Feb 2022
 * 
 */
#pragma strict_types

inherit "/d/Avenir/inherit/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";
inherit "/d/Genesis/specials/new/resource";
#include <formulas.h>
#include <ss_types.h>
#include <tasks.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#define MINIM      75
#define TP         this_player()
#define COST       (get_dynamic_mana_cost(TP, TS_INT, 18, 0, 300))
#define WIELD_PROP "_numinous_wielder"

int alarm_id = 0;

public void
create_weapon()
{
    set_name("blade");
    add_name(({"_gavriels_blade", "dagger", "knife"}));
    set_adj(({ "ritual", "ancient", "mystical", "ceremonial", 
        "beautiful", "long", "numinous" }));
    set_short("numinous knife");
    set_long("This numinous knife is a thing of beauty. It is made of ancient "+
       "steel, with mystical runes written in gold along the blade. The "+
       "hilt is ivory inlaid with gold, and the pommel is inset with "+
       "sparkling amethysts. Though sharp, it looks more ceremonial than "+
       "utilitarian, as if intended for divine rather than mundane "+
       "purposes.\n");
	
	add_item(({"blade", "runes", "mystical runes", "gold runes"}),
        "The blade has runes written upon it in gold. The meaning of "+
        "the runes evades your understanding, but the connection "+
		"with the divine is apparent.\n");
	add_item(({"hilt", "ivory", "gold inlay"}), 
	    "The ivory hilt is inlaid with gold.\n");
	add_item(({"amethysts", "sparkling amethysts", "pommel", "facets"}), 
        "The facets on the emeralds affixed to the pommel of the "+
        "numinous blade are somewhat worn, but still sparkle "+
        "when they catch in the light.\n");
		
    add_prop(OBJ_I_WEIGHT,  3000); 
    add_prop(OBJ_I_VOLUME,  1000); 
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40, 40) * 2);
    add_prop(OBJ_M_NO_BUY, 1);
	
	set_magic_spellpower(40);
    set_default_weapon(38, 38, W_KNIFE, W_IMPALE| W_SLASH, W_ANYH, 0);
	set_wf(this_object());
	
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,
      ({ "Forged by a long forgotten hand\n", 10,
         "In a valley ringed in ice and snow.\n", 15,
         "In service to the gods of the land\n", 20,
         "Upon this blade do the divine bestow\n", 25,
         "Power to aid the cleric's stand\n", 30,
         "And sight to eyes that see no glow.\n", 40 }) );
	add_prop(OBJ_S_WIZINFO, 
        "This is Gavriel's blade. It is cloned by "+
        "/d/Avenir/common/dark/mon/gavriel at "+
        "/d/Avenir/common/dark/l2/add/c6\n"+
        "It grants darksight to the wielder and "+
        "It is also a lvl 40 spell enhancer. "+
        "Darkvision cost is based on dynamic mana system "+
		"cost of 18% combat aid every 5 minutes.\n");	  
}		
	
/*
 * Function:    do_mana_cost
 * Description: drains mana from the wielder every 5 minutes.
 */
void
do_mana_cost()
{
    object owner = query_wielded();
	
    if(!owner)
        return;
	
	/* If you can't pay the ongoing mana cost you can't wield it */
    if(owner->query_mana() < COST)
    {
        write("You grab your head as it suddenly pounds with purple pain!\n");
        owner->command("$unwield numinous blade");
        return;
    }
    owner->add_mana(-(COST));
	owner->catch_msg("You feel a fleeting purple pressure behind your eyes.\n");
    alarm_id = set_alarm(300.0, 0.0, do_mana_cost);
    return;
}
 

/*
 * Function     : wield
 * Description  : Wield a weapon
 * Arguments    : Object what - The weapon to wield
 * Returns      : string - error message (weapon not wielded)
 *                1 - success (weapon wielded)
 */
mixed 
wield(object what)
{
    int go;

    /* Does living have enough mana? If not, don't wield */
    if (TP->query_mana() <= COST) 
        return "You do not have the mental energy necessary to wield "+
            "it.\n";
    
    /* Lets set some stat and skill requirements to wield */
    go = TP->query_stat(SS_INT)   / 4;          /* Mortal: 100/4 = 25 */
    go += TP->query_skill(SS_WIS) / 4;          /* Mortal: 100/4 = 25 */
    go += TP->query_skill(SS_SPELLCRAFT);       /* Mortal: 0-90       */
                                                /* random < 75 fails */
    if ( (random(go) < MINIM) && (!TP->query_prop(WIELD_PROP)) )
    {
        return "You try to wield the "+ short() +", but it seems to "+
               "find you lacking in some way.\n";
    }

    /* All checks have passed, proceed with wielding */
    TP->add_mana(-COST);
    TP->catch_msg("As you wield the "+ short() +", you feel magic thrumming "+
        "through you, enhancing your vision with a faint purplish haze.\n");	
    say(QCTNAME(TP)+" blinks rapidly a few times after wielding "+
        TP->query_possessive() +" "+ short() +".\n");

    if (!TP->query_prop(WIELD_PROP))
    {
        TP->add_prop(LIVE_I_SEE_DARK, TP->query_prop(LIVE_I_SEE_DARK) + 1);
        TP->add_prop(WIELD_PROP, 1);
    }
	
    alarm_id = set_alarm(600.0, 0.0, do_mana_cost);
    return 1;
}


/*
 * Function    : remove_wield_perks
 * Description : Remove the darksight benefit
 */
int
remove_wield_perks()
{
    object owner = query_wielded();
    
    if (owner->query_prop(WIELD_PROP))
    {
        owner->remove_prop(WIELD_PROP);
        // There are other items that add and remove darkvision so
		// Let's make sure we aren't putting player in the negative
		if (owner->query_prop(LIVE_I_SEE_DARK))
		{
            owner->add_prop(LIVE_I_SEE_DARK,
                owner->query_prop(LIVE_I_SEE_DARK) - 1);
            owner->catch_msg("The purple haze fades from your sight.\n");
        }
        return 1;
    }
    return 0;
}


/* 
 * Function    : unwield
 * Description : Unwield a weapon
 * Arguments   : object wep - the weapon to unwield
 */
mixed 
unwield(object wep)
{
    object owner = query_wielded();

    if (alarm_id)
        remove_alarm(alarm_id);
	
    remove_wield_perks();

    return 0;
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

 
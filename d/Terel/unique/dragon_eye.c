/*  
 *  Dragon's eye  /d/Terel/unique/dragon_eye.c 
 *
 *  The eye of Azyphelth, an ice dragon in Terel.
 *  He lost this eye fighting Benton, Vercus, and their other brother,
 *  now dead, who was himself defeated by a circle of magic users at
 *  the tower just outside Calathin.
 *
 *  Spell enhancer for elements WATER, AIR, and DEATH.
 *  Grants darkvision and some elemental res to cold/water/air. 
 *  Uses the dynamic mana system to determine mana costs for 
 *  the darkvision at 15% combat aid every 5 mins.
 *
 * Created by: Lilith Apr/May 2022
 * Approved by: Ckrik May 2022
 *
 */

inherit "/d/Genesis/specials/new/lib/spell_enhancer";
inherit "/d/Genesis/specials/new/resource";
inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/keep";
inherit "/lib/item_expiration";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

// spell power is high, but only for 3 elements.
#define MY_SP  50
#define MY_RES 10
#define COST   (get_dynamic_mana_cost(TP, TS_INT, 15, 0, 300))
#define TP     this_player()

int alarm_id = 0;

void
create_object()
{
    set_name("eye of azyfelth");
    add_name(({"eye", "orb", "dragoneye", "::azyfelths_eye::"}));
    set_adj(({"blue", "ice-blue", "dragon", "azyfelth", "azyfelth's"}));
    set_short("ice-blue dragon eye");
    set_long("This is the eye of Azyfelth, one of the ice dragons " +
      "who dwell in the Dragon Tooth Mountains of Terel. "+ 
      "Large as a melon and just as heavy, the iris of the eye is "+
      "ice-blue in color, while the rest of the orb is purest white. "+
      "Oddly, the slitted pupil seems to adjust according to the "+
      "ambient light levels. "+
      "Lore has it that Azyfelth lost this eye when three warlock "+
      "brothers visited his ice cave a century ago."+
      "\n");

    add_item(({"iris", "blue iris", "ice-blue iris"}),
      "It is a wonderous whirl of blues of every tone and shade.\n");
    add_item(({"pupil"}), "The pupil of the dragon's eye is a long black "+
      "slit that expands and retracts on its own.\n");
    add_item(({"white of eye", "white"}), "The white part of the eye is "+
      "as smooth and pale as finest alabaster.\n");

    set_slots(W_ANYH);
    set_keep(1);
    set_item_expiration();

    set_spellpower_elements(({ 
      SS_ELEMENT_AIR, SS_ELEMENT_WATER, SS_ELEMENT_DEATH
                           	}));
    set_magic_spellpower(MY_SP);  

    // Magical items cannot be bought at a store.
    add_prop(OBJ_M_NO_BUY, 1); 			
    add_prop(MAGIC_AM_MAGIC, ({90,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({	
      "Holding Azyfelth's eye you borrow a dragon's sight:\n", 20,
      "To easily see in darkness as well as in light\n", 30,   
      "For those who meet magic it is foretold\n", 40,
      "The bearer resists water, air, and cold.\n", 50 }));

    add_prop(OBJ_S_WIZINFO, "This is the eye of an Ice Dragon. It is "+
      "cloned by Benton as one of the random items he equips with. "+
      "This is a spell enhancer level "+ MY_SP +" that grants darkvision as "+
      "well as "+ MY_RES +" levels of water, air, and cold res.\n"+
      "Darkvision cost is based on dynamic mana system "+
      "cost of 15% combat aid every 5 minutes.\n"+
      "Cloned by: /d/Terel/common/moor/monster/benton at: "+
      "/d/Terel/common/moor/tomb/gore_chamber.\n");		

    add_prop(OBJ_I_WEIGHT,  2000);
    add_prop(OBJ_I_VOLUME,  4000);
    add_prop(OBJ_I_VALUE,   2000);

}


/*
 * Function:    do_mana_cost
 * Description: drains mana from the wielder every 5 minutes.
 */
void
do_mana_cost()
{
    object owner = environment(this_object());

    if(!owner)
	return;

    if (!interactive(owner))
	return;

    /* If you can't pay the ongoing mana cost you can't hold it */
    if(owner->query_mana() < COST)
    {
	owner->catch_msg("You grab your head as it suddenly pounds "+
	  "as if pierced by ice!\n");
	owner->command("$release ::azyfelths_eye::");
	return;
    }
    /* Do dynamic mana drain */
    owner->add_mana(-(COST));
    owner->catch_msg("The hand holding "+ short() +
      " feels ice-cold for a moment.\n");
    alarm_id = set_alarm(300.0, 0.0, do_mana_cost);
    return;
}


/* Player is holding it, so lets add the nifty stuff */
public mixed
hold()
{

    this_player()->catch_msg(
      "As you hold the dragon's eye in your hand " +
      "the slit-like pupil seems to widen, and with "+
      "it your visual spectrum increases.\n");

    /* Add the dark vision */ 
    this_player()->add_prop(LIVE_I_SEE_DARK,
      (this_player()->query_prop(LIVE_I_SEE_DARK) + 1));

    /* Add a bit of magic resistance */
    this_player()->add_magic_effect(this_object());

    /* Activate the item_expiration_combat counter when it is being used. */
    add_expiration_combat_hook(this_player());

    /* Start the mana drain */
    alarm_id = set_alarm(600.0, 0.0, do_mana_cost);
    return 0;
}

/* When the player stops holding it, remove the benefits */
public mixed
release()
{
    this_player()->catch_msg(
      "As you release your hold on the dragon's eye " +
      "the slit-like pupil narrows, and the spectrum of "+
      "your vision decreases.\n");

    /* Remove the dark vision */
    this_player()->add_prop(LIVE_I_SEE_DARK,
      (this_player()->query_prop(LIVE_I_SEE_DARK) - 1));

    /* Remove the little bit of magic res */
    this_player()->remove_magic_effect(this_object());

    /* De-activate item_expiration_combat counter when not using. */
    remove_expiration_combat_hook(this_player());

    /* Remove the mana draining alarm */
    if (alarm_id)
	remove_alarm(alarm_id);

    return 0;
}


/* Add a bit of resistance to Water, Air, and Cold elements. 
 *  This is the eye of an Ice Dragon.
 */ 
varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (prop == MAGIC_I_RES_WATER || prop == MAGIC_I_RES_AIR || prop == MAGIC_I_RES_COLD)
    {
	protectee->catch_msg("The "+ short() +" in your hand "+
	  "suddenly vibrates as if resisting a magical force!\n");
	return ({ MY_RES, 1}); // additive
    }
}


/* This makes sure held items are released when leaving inventory. */
void leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

string query_recover()
{
    return MASTER + ":" + query_item_expiration_recover();
}

void init_recover(string arg)
{
    init_item_expiration_recover(arg);
}


public void set_spellpower_elements(int* element_skills)
{
    spellpower_elements = element_skills;
}


public void appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
    write(item_spellpower_desc());
}

public string stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}


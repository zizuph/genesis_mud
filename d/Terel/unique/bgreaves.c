/*
 *  Benton's greaves   /d/Terel/unique/bgreaves.c
 *  
 *  Magical alloy greaves. Good AC with fatigue reduction 
 *  (8 fatigue every 15 seconds = 32/minute)
 *  that uses the dynamic mana system to calc the mana cost.
 *
 *  Created by Lilith Apr/May 2022
 *  Approved by: 
 *
 */

inherit "/d/Genesis/specials/new/resource";
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <macros.h>
#include <ss_types.h>

#define DIS(x) (x)->query_stat(SS_DIS)
#define TO     this_object()
#define TP     this_player()

// Do 8 points of fatigue heal
#define FAT    8
#define MY_AC  45

/* Fatigue regen doesn't have a combat aid value that I'm aware of
 * but I'm going to use 20% as a basis for the dynamic mana cost
 * at 15 second intervals.
 */  
#define COST   (get_dynamic_mana_cost(TP, TS_INT, 20, 0, 15))

int alarm_id = 0;

void
create_armour()
{
    set_name(({"greaves", "pair of greaves"}));
    add_name("_bentons_greaves_");
    set_pname(({"armours","greaves","pairs of greaves"}));
    set_short("pair of metallic ice-blue greaves");
    set_pshort("pairs of metallic ice-blue greaves");
    set_long("This is a pair of greaves made of a bluish metallic "+
      "alloy that was formed in the magic fire of an ice dragon's "+
      "breath. "+
      "Runes of a corrupt and necromantic nature have been "+
      "drawn in blood along the shiny, metallic surface. "+
      "The padding appears to be of animal pelts, which offers "+
      "needed protection from the cold of northern Terel's ever"+
      "winter.\n");
    set_adj(({"magical", "shiny", "blood-runed", "runed", "alloy",
      "corrupt", "necromantic", "bluish", "benton", "bentons", 
      "benton's", "benton", "metallic", "blue"}));
    add_item(({"padding", "pelts", "animal pelts"}),
      "These greaves are so thickly padded with animal pelts that "+
      "whoever wears them will stay warm even in the Silver Forest "+
      "of northern Terel.\n");	
    add_item(({"strap", "straps" }), "These straps affix the armour "+
      "to your body without interfering with your movement.\n");		

    set_keep(1);
    set_ac(MY_AC);  
    set_at(A_LEGS);
    set_af(TO);
	
    // Magical items cannot be bought at a store.
    add_prop(OBJ_M_NO_BUY, 1); 		
    add_prop(OBJ_I_VALUE, 1500 + random (200));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 70, "transmutation" }));
    add_prop(OBJ_I_WEIGHT, 4000);  
    add_prop(OBJ_I_VOLUME, 4000);
    // For Silver Forest Cold Protection
    add_prop("_obj_cold_weather_protect", 5);
	
    add_item(({"runes", "red runes", "corrupt runes", "surface", 
      "necromantic runes", "corrupt and necromantic runes", "blood",
      "metallic surface", "shiny surface", "shiny metallic surface",
      "blood runes", "bloody runes"}),
      "Runes of a corrupt and necromantic nature have been "+
      "inscribed with blood upon the shiny metallic surface "+
      "of these greaves.\n");
    add_prop(OBJ_S_WIZINFO, "These greaves are randomly cloned to "+
      "Benton. They have AC "+ MY_AC +" and are one of the few "+
      "items in the game that restore fatigue. "+
      "Players need 75-100 DIS to wear it.\n"+	  
      "Cloned by: /d/Terel/common/moor/monster/benton at: "+
      "/d/Terel/common/moor/tomb/gore_chamber.\n");		
    add_prop(MAGIC_AM_ID_INFO,  ({ 
      "The magical flames of a dragon's breath\n", 10,
      "Transformed the metal of these greaves\n", 20,
      "Making them stronger yet light as leaves.\n", 30,
      "Runes in blood improve the vigor of the legs\n", 40, 
      "As the sacrifice of one reduces another's fatigue.\n", 60 }));		

}

/*
 * Function:    do_mana_cost
 * Description: drains mana from the wielder every 15 secs.
 *              adds fatigue instead.
 */
void
do_mana_cost()
{
    object owner = query_worn();

    if(!owner)
	return;

    /* If they don't need fatigue heal, skip mana drain */
    if (owner->query_fatigue() == owner->query_max_fatigue())
    {
    alarm_id = set_alarm(15.0, 0.0, do_mana_cost);
    return;
    }

    /* If you can't pay the ongoing mana cost you can't wear it */
    if(owner->query_mana() < COST)
    {
	owner->catch_msg("It feels like your legs have blood running "+
	  "down them underneath your greaves!\n");
	owner->command("$remove _bentons_greaves_");
	return;
    }

    /* Do dynamic mana cost */
    owner->add_mana(-(COST));
    /* Do fatigue regen */
    owner->add_fatigue(FAT);
    /* Start next round */
    alarm_id = set_alarm(15.0, 0.0, do_mana_cost);
    /* Since this happens a few times a minute, do the messaging randomly */
    if (random(20) == 0)
    owner->catch_msg("You feel a prickle of pain in your shins.\n");

    return;
}


mixed
wear(object ob)
{
    /* If an npc is wearing it, bypass the mana drain-fatigue regen effect */
    if (!interactive(TP))
	return 1;

    /* Does player have the DIS to resist the pain of wearing these? */
    if (DIS(TP) > (75 + random(25)))
    {
	TP->catch_msg("Being careful to avoid touching the bloody "+
	  "runes, you strap on your "+ short() +".\n");
	say(QCTNAME(TP) + " is careful not to touch the blood "+ 
	  "as "+ TP->query_pronoun() +" straps on "+ short() +".\n");			
	/* mana drain and fatigue regen starts 30 seconds after wearing it */
	alarm_id = set_alarm(30.0, 0.0, do_mana_cost);
	return 1;
    }
    return -1;
}

int
remove(object ob)
{
    /* If mana drain/fatigue regen alarm is running, remove it */
    if (alarm_id)
	remove_alarm(alarm_id);
    return 0;
}

void
leave_env(object to,object from)
{
    ::leave_env(to, from);

    /* If mana drain/fatigue regen alarm is running, remove it */
    if (alarm_id)
	remove_alarm(alarm_id);
}

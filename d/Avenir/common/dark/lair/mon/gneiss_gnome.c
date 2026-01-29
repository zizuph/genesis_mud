// file name: /d/Avenir/common/dark/mon/gnome.c
// creator(s): Lilith Nov 2021
// purpose:    Gnome area in the underdark for smaller players.
// note:       Stat av 35-50
//             The gneiss gnomes got trapped down on L2 
//             long ago and somehow managed to stay alive in
//             their isolation. Resources were scarce... the
//             only things they have in abundance are stone,
//             gems, metals,and fungi. They make jewelry to 
//             pass the time.  Which reminds me, I really 
//             should make that craft guild for people to
//             make jewelry from gems and coins and the metal
//             from broken weapons. 
// update(s):   

inherit "/d/Avenir/inherit/monster";
inherit "/d/Genesis/specials/npc/stat_based_specials";
#include "/d/Avenir/smis/sys/statserv.h"

#include "../dark.h"
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>


#define DEATH_LOG "/d/Avenir/log/deaths/gneissGnome"

// Global Variables
string *randadj, short_desc;

/* This is called by the darkl2p.c  placer file, not the npc */
void
equip_me()
{
    // The gneiss gnomes developed jewelry-making while isolated
    // down in the underdark. May Possibly lead to new racial or 
	// craft guild. 
	string trinket = one_of_list(({ DARK +"obj/g_earring",
	                 DARK+"obj/g_anklet", DARK+"obj/g_bracelet",
                     DARK+"obj/g_necklace"}));
	string sparkly = one_of_list(({ "/d/Genesis/gems/obj/garnet",
                     "/d/Genesis/gems/obj/spinel_red",
                     "/d/Genesis/gems/obj/star_ruby",
                     "/d/Genesis/gems/obj/fire_opal",
                     "/d/Genesis/gems/obj/agate_fire",
                     "/d/Genesis/gems/obj/beryl_red",
                     "/d/Genesis/gems/obj/bloodstone" }));
    equip(trinket);	
    equip(sparkly);	
    equip(BAZAAR +"Obj/worn/loincloth");
	
    if (random(4) == 0)
	  add_weapon(DARK +"obj/d_pickaxe");

}

string 
my_long()
{
	return "This a "+ short_desc +" that seems to be about "
	  +query_exp_title()+" in size.\n"
	  +"The gneiss gnomes take their names from the gneiss tunnels "
	  +"they live in.\nThough they have recently broken through to the "
	  +"rest of the Underdark, they have lived in isolation for "
	  +"centuries.\n"
      +"This gneiss gnome is paler, skinnier, and more muscular than "
	  +"a typical surface gnome, with a canny, almost feral look.\n";

}	  
	 
void
create_monster()
{
    int wep, gender;
    string randadj = one_of_list(({"wary","grayish","thin","slender",
      "skeletal","wiry","pale-eyed","hairless", "red-eyed",
      "pale","grim","sickly","scarred","brave","big-nosed",
      "timid", "cheerful", "simple-minded", "young", "old",
	  "lean", "elderly", "vigorous", "slow", "anxious", 
	  "artistic", "masculine", "feminine", "androgynous",
	  "child-like", "merry"}));
	  
    set_name(({"gneiss gnome", "_av_gneiss_gnome"}));
    set_race_name("gnome");
    set_adj(randadj);
    add_adj("gneiss");

    short_desc = implode(query_adjs(), " ") +" "+ query_race();
    set_short(short_desc);
	
	gender = random(3);
	if (gender == 0)
      set_gender(G_FEMALE);
    else
      set_gender(G_MALE);
	
    set_long(my_long);
    set_alignment(0);   	

    //  stat av 36 - 50
	default_config_npc(35+(random(16)));

    // fights unarmed so lets give skills based on mob size.
    set_skill(SS_AWARENESS,    40); // foil imbue thieves
    set_skill(SS_DEFENCE,      40); // reduce melee damage 	
    set_skill(SS_ACROBAT,      40); // reduce melee damage
    set_skill(SS_UNARM_COMBAT, 40);	
    set_skill(SS_BLIND_COMBAT, 40); 
    set_skill(SS_WEP_AXE,      40); // in case they get a pickaxe
	
    wep = 20 +(random(11));         // 20-30 
    set_all_attack_unarmed(wep, wep);
    set_all_hitloc_unarmed(30);     // Native AC

    // set height and weight to align with size and descs
    add_prop(CONT_I_HEIGHT, 70+(random(20)));
    add_prop(CONT_I_WEIGHT, 28000+random(5000));
    
	add_prop(LIVE_I_SEE_DARK, 1); 
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 1);
	
	set_act_time(5);
	add_act("emote sets down a small child, who dashes for a cubby.");
	add_act("emote twists a bit of metal wire around a gemstone.");
	add_act("emote munches on a mushroom.");
	add_act("emote feeds a small bat.");	
	add_act("emote adds a link to a gold chain.");
	add_act("emote scratches where it itches.");	
    add_act("emote hums a pleasant melody.");
	add_act("sigh content");
	add_act("hug gneiss gnome");
	add_act("fart");
    add_act("nudge gneiss gnome");
	add_act("love gneiss gnome");
	add_act("bounce");
	add_act("laugh gnom");
	

    set_cact_time(2);
    add_cact("emote grabs a handful of gravel and throws it at you.");
    add_cact("emote lets out a high-pitched scream that hurts your ears.");
    add_cact("emote tries to trip you up.");
    add_cact("emote slides half-way into a cubby and kicks out at you.");
    add_cact("says: We were right to fear what lies beyond this, our "+
        "gneiss gnome home.");
    add_cact("screams: Why don't you go away?");
	add_cact("wail");
    add_cact("moan pain");
	
	seteuid(getuid());

}

public int
special_attack(object victim)
{

    mixed * hitresult;
    int avg_stat, hurt;
    string how, hdesc;
    object poison;

    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
	TO->stop_fight(victim);
	return 1;
    }

    // 33% chance of a normal or special attack.
    if (random(3))
	return 0;

    // Choose power of hit based on mob stat size.
    hitresult = do_stat_based_attack(TO, victim, W_BLUDGEON);

    // The attack was evaded
    if (intp(hitresult))
	return 1;

    if (hitresult[0] <= 0)
    {
	// Handle misses.
	query_combat_object()->tell_watcher(QCTNAME(TO) + 
	  " tries to punch " + QTNAME(victim) +
	  " in the leg, but misses.\n", victim);
	victim->catch_msg(QCTNAME(TO) + " tries to punch the "
	  +"back of your knee but misses.\n");
	return 1;
    }
    // hitresult as percentage of health
    how = "unharmed";
    if (hitresult[0] > 5)
	how = "remain steady.";
    if (hitresult[0] > 10)
	how = "buckle a bit.";
    if (hitresult[0] > 25)
	how = "almost fall out from under you.";
    if (hitresult[0] > 50)
	how = "feel as though you've been stabbed in the back of the knee!";
    if (hitresult[0] > 75)
	how = "as though the have been cut out from under you!";

    query_combat_object()->tell_watcher(QCTNAME(TO) +
        " lunges for " + QTNAME(victim) + " and punches the back of "+
        victim->query_possessive() +" knee.\n", victim); 
    victim->catch_msg(QCTNAME(TO) + " lunges toward you and punches "
        +"you behind the knees!\n");
    victim->catch_msg("Your legs " + how + "\n");

    return 1;
}


/* Logging death info. */
void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    string *killers;

    if (query_hp() > 0)
	return;

    object gem;
	gem = clone_object("/d/Genesis/gems/obj/garnet");
	gem->set_heap_size(1 +random(3)); // 1 to 3 garnets
	gem->move(TO, 1);

	STATSERV_LOG_EVENT("Utterdark", "gneiss gnomes");
    
    ::do_die(killer);

}

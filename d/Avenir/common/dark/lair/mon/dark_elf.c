/*
 * Revisions:
 *
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 * Lilith May 2014: Brought npcs into current decade using stat-based
 *                  specials and skills, randomized rather than static sizing.
 *                  (Modeled after Ribos Castle tower guards)
 *                  Added gems, cloning of some Utterdark items, and healing special.
 * Lilith Jun 2014: Added clone unique of the worm's tooth knife.
 *                  added some chats, added logging of deaths.
 *                  Customized special attack to do stat-based damage.
 * Cotillion, Jun 2014: Made dark-elves wield/wear their items
 * Lilith Aug 2014: Changed stat interval to 30 from 35. Removed exp modifier.
 * Lilith Oct 2014: Added magic res. Magic users are scything through mobs. 
 *                  Will likely needd tweaking.
 * Lucius Jun 2016: Removed self-healing and mana-draining.
 * Vyasa  Nov 2016: Adapted hit msgs to not look as if they were wielding when they
 *                  weren't (broken or brawled weapons.)
 * Lucius Jun 2017: Removed the f_knife cloning, makes no sense for these to have
 * 			them. Reduced tooth_knife clones from 6 -> 3.
 * Zizuph Jun 2021: Migrated special to standard specials library.
 * Lilith Sep 2021: Added BLIND_COMBAT similar to what Maivia has. Not
 *                  sure why it wasn't there to begin with.
 */
#pragma strict_types

inherit "/std/monster";
inherit "/lib/unique";
inherit "/d/Genesis/specials/npc/stat_based_specials";

#include "../dark.h"
#include "/d/Genesis/gems/gem.h"

/* Log deaths to weekly statserv */
#include "/d/Avenir/smis/sys/statserv.h"

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 90000) ? \
(rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
(write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

#define DEATH_LOG   "/d/Avenir/log/deaths/dark_elf"

// Define the different guard types
#define MOB_0     0
#define MOB_1     1
#define MOB_2     2
#define MOB_3     3
#define MOB_4     4
#define MOB_5     5
#define MOB_6     6
#define MOB_7     7

// Global Variables
public int      Strength = 0;

/* 
 * Function:    set_mob_strength
 * Description: Called inside setup_random_mob, it indicates
 *              which elf type this is.
 */
public void
set_mob_strength(int strength)
{
    Strength = strength;
}

/*
 * Function:    get_mob_strength
 * Description: Returns the value set during the random generation.
 */
public int
get_mob_strength()
{
    return Strength;
}

/*
 * Function:    setup_random_mob
 * Description: Randomly select a type of mob to generate.
 *              They range from 50-300 stat at intervals of 30
 *              Adjective desc helps mortals figure out at a
 *				glance what size their opponents are.
 */
public void
setup_random_mob()
{
    int base_stat, mob_type;  
    string short_desc;
    
    /* The random generation type will take all the existing types
     * and try to do an equal distribution.
	 */
    object * instances = object_clones(find_object(MASTER));
    if (!sizeof(instances))
    {
        mob_type = random(8);
    }
    else
    {
        int * counts = ({ 0, 0, 0, 0, 0, 0, 0, 0 });
        foreach (object instance : instances)
        {
            int strength = instance->get_mob_strength();
            ++counts[strength];
        }
        int mincount = applyv(min, counts);
        mob_type = max(0, member_array(mincount, counts));
    }
    // Set the strength so that it can be looked up later.
    set_mob_strength(mob_type);
	
    switch (mob_type)
    {
		case MOB_0:
			add_adj(({"weak-looking", "small"}));
			break;
			
		case MOB_1:
			add_adj(({"awkward", "smallish"}));
			break;
			
		case MOB_2:
			add_adj(({"competent", "average"}));
			break;
			
		case MOB_3:
			add_adj(({"well-trained", "average"}));
			break;
			
		case MOB_4:
			add_adj(({"highly-trained", "large"}));
			break;
			
		case MOB_5:
			add_adj(({"blood-thirsty", "large"}));
			break;
			
		case MOB_6:
			add_adj(({"deadly", "huge"}));
			break;

		case MOB_7:
			add_adj(({"murderous", "huge"}));
			break;
						
    }
    
    // Set up the actual stats    
    base_stat = 50 + (mob_type * 30) + random(25);
    default_config_npc(base_stat);   
		
    short_desc = implode(query_adjs(), " ") + " dark elf";
    set_short(short_desc);
	set_name(short_desc);
}


public void
create_monster(void)
{
    setuid();
    seteuid(getuid());
	
    setup_random_mob();
    set_race_name("dark elf");
    add_name(({"elf"}));
    set_adj("dark");
    set_long("These evil creatures are the opposers of all that is light " +
      "and truth. They seek utter darkness for the world. They are dark "
      +"beings with white hair, their beauty being that of the "
      +"shadows. They are wicked, wicked beings, these elves, and not to be "
	  +"trifled with.\nThis one is a "+query_short() +" of "
      +query_exp_title() +" stature.\n");	
	
	set_default_answer("say Our leader, Maivia, answers questions. We do not.", 1);
	
    set_alignment(-100 - random(150));
	
	// Set up base ac for npc according to mob size
	set_all_hitloc_unarmed(Strength * 7);

	// Skills based on type of mob
	int skill_mod = Strength * 10;
    set_skill(SS_PARRY,		  20 + skill_mod);
    set_skill(SS_DEFENCE,	  20 + skill_mod);
    set_skill(SS_WEP_SWORD,	  20 + skill_mod);
    set_skill(SS_WEP_POLEARM, 20 + skill_mod);
    set_skill(SS_WEP_KNIFE,	  20 + skill_mod);
    set_skill(SS_2H_COMBAT,	  20 + skill_mod);
    set_skill(SS_AWARENESS,	  20 + skill_mod);
    set_skill(SS_SPELLCRAFT,  60);
	set_skill(SS_BLIND_COMBAT,75); // a bit lower than Maivia
	set_skill(SS_UNARM_COMBAT,40 + (5 *Strength));
	
	// Set up magic resistance based on mob size 
	// magic users are scything through them	
	int resistance = Strength + 2;
	add_prop(OBJ_I_RES_ACID, resistance); 
    add_prop(OBJ_I_RES_AIR, resistance); 
    add_prop(OBJ_I_RES_COLD, resistance); 
    add_prop(OBJ_I_RES_DEATH, resistance); 
    add_prop(OBJ_I_RES_EARTH, resistance); 
    add_prop(OBJ_I_RES_ELECTRICITY, resistance); 
    add_prop(OBJ_I_RES_FIRE, resistance); 
    add_prop(OBJ_I_RES_ILLUSION, resistance);  
    add_prop(OBJ_I_RES_LIFE, resistance); 
    add_prop(OBJ_I_RES_LIGHT, resistance); 
    add_prop(OBJ_I_RES_MAGIC, resistance); 
    add_prop(OBJ_I_RES_POISON, resistance); 
    add_prop(OBJ_I_RES_WATER, resistance); 
	
    add_prop(LIVE_I_SEE_DARK,   3);
    add_prop(OBJ_M_HAS_MONEY, random(1000));
	
	// set height and weight to align with size and descs
	add_prop(CONT_I_HEIGHT, TO->query_average_stat());
	add_prop(CONT_I_WEIGHT, TO->query_average_stat() * 125);
		
	// based on 15% of 5% healing + special attack + normal attack
	// Not doing exp boost, not worth the balance hassle, Lilith
    // set_exp_factor(115); 
	
	// Make beautiful as per set_long
	set_appearance_offset(-90);
    
    set_act_time(10);
    set_chat_time(20 +random(60));
    add_chat("All glory resides in darkness!");
    add_chat("We worship Shadow.");
    add_chat("Someday our people will create a great city in the Utterdark.");
    add_chat("The sun is a most foul creation.");
	add_chat("We shall destroy Sybarus one day.");
	add_chat("Shadow-elves shall fall before the glory of our leader.");
	add_chat("The ogres are the key to everything, don't you think?");
	add_chat("We took care of those Mystics, now it's time for those Shadow Warriors.");
	add_chat("We may have to push the trolls back onto the moors. It's getting crowded here.");
	add_chat("That worm sure is tough to get to, down there in the lava pits");
	add_chat("I heard there is some quest involving the imps.");
	add_chat("Those imps turn to stone you know.");
	add_chat("Good thing those foul little hobgoblins stick to their area or we'd eliminate them.");
	add_chat("Once you enter the pool, you're close to the Sun so be careful.");
	add_chat("I know the Halls of Shadow are nearby. We will find them.");
	add_chat("We plan to take the fortress on the other side of the abyss, too.");

    set_random_move(25);
    this_object()->equip_me();
}

/*
 * Function name: special_attack
 * Description:   Called from the external combat object's heart_beat
 *                routine. By redefining this, monsters can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 * Note:          By always returning 1 the mobile is unable
 *                to do an ordinary attack. 
 */
public int
special_attack(object victim)
{
	
    mixed * hitresult;
	int avg_stat, hurt;
    string how, hdesc;
	
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
	
    if (hitresult[0] < 0)
    {
        // Handle misses.
        tell_watcher(QCTNAME(TO) + " tries to slam " + QTNAME(victim) +
	    " but misses completely.\n", victim);
        victim->catch_msg(QCTNAME(TO) + " tries to slam you but misses " +
	    "completely!\n");
        return 1;
    }
    
    how = "unharmed";
    if (hitresult[0] > 0)
	how = "annoyed";
    if (hitresult[0] > 5)
	how = "some pain";
    if (hitresult[0] > 20)
	how = "a bit injured";
    if (hitresult[0] > 40)
	how = "hurt! Ouch";
    if (hitresult[0] > 60)
	how = "rather hurt, like something might be broken! "+
	    "This might be a close fight after all";
    if (hitresult[0] > 80)
	how = "as though you have been wounded internally! Yikes";

/*
     Changed the description of the hits since it looks as if 
     they were hitting with weapons even if those were broken
     by spells or disarmed by rangers.
     - Vyasa, 2016
*/
    hdesc = hitresult[1];
    tell_watcher(QCTNAME(TO) + " slaps " + QTNAME(victim) + " on the " +
	hdesc + " with the back side of his hand.\n", victim); 
    victim->catch_msg(QCTNAME(TO) + " slaps you on the " + hdesc +
	" with the back side of his hand!\n");
    victim->catch_msg("You feel " + how + ".\n");
	
    return 1;
}
				
					 
public void
equip_me(void)
{
	object gem;
	
    /* Top of the chain in the Utterdark so they carry some 
     * Of the items players might gather to accomplish things.
     * Limit number of clones on the more unique stuff.
     *
     * Since it takes 2+ to get access to kill worm, 
     * lets have his tooth out in the wild, too.
     */
    clone_unique(OBJ + "tooth_knife", 2, 0, 0, 15, 0)->move(TO);
		
    switch(random(5))
    {
    case 0:
	clone_object(OBJ +"halberd")->move(TO);
	clone_object(COM +"obj/coal")->move(TO);

	break;

    case 1:
	clone_object(OBJ +"ssword")->move(TO);
	clone_object(OBJ +"bshield")->move(TO);
	clone_unique(OBJ +"smash_tool", 6, 0, 0, 25, 0)->move(TO);
	break;

    case 2:
	clone_object(OBJ +"sabre")->move(TO);
	clone_object(OBJ +"bshield")->move(TO);
	clone_unique(OBJ +"shovel", 25, 0, 0, 25, 0)->move(TO);
	break;

    case 3:
	clone_object(OBJ +"ddagger")->move(TO);			
	clone_object(OBJ +"sabre")->move(TO);
	clone_unique(OBJ +"r_glove", 25, 0, 0, 25, 0)->move(TO);
	break;

    case 4:
	clone_object(OBJ +"ddagger")->move(TO);	
	clone_object(OBJ +"ssword")->move(TO);	
	break;
    }
		
    gem = RANDOM_GEM_BY_RARITY(GEM_ALL);
    gem->move(this_object()); 
    
    clone_object(OBJ +"chainmail")->move(TO);
    clone_object(OBJ +"war_helm")->move(TO);
    clone_object(OBJ +"cloak")->move(TO);
    clone_object(OBJ +"boots")->move(TO);

    command("$wield weapon");	
    command("$wield second weapon");	
    // Wear last so shields don't get in the way of two handed weapons.
    command("$wear all");

}

/* Logging death info. */
void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    string *killers;
	
    if (query_hp() > 0)
        return;
	
    if (!killer)
        killer = previous_object();
	
    foos -= ({ killer });
    killers = (foos)->query_name();
	
    /* Logging death for various reasons */
    SCROLLING_LOG(DEATH_LOG, "Drow ("+ TO->query_average_stat() +") by "+
	killer->query_name() +"("+ killer->query_average_stat() +") "+
	(sizeof(killers) ? "with "+ COMPOSITE_WORDS(killers) : "solo"));

    STATSERV_LOG_EVENT("Utterdark", "Dark-elf died");
    ::do_die(killer);
}

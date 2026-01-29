/*
 * /d/Faerun/orcmaker/orcmaker.c
 * Orcmaker for Faerun, based on the Shire orcmaker
 * - Finwe, November 2007
 *
 * This file will generate one of five types of orcs, EASY, MEDIUM,
 * HARD, STRONG, and TOUGH. Each one has a stat average of 50, 75,
 * 120, 175, and 225, respectively.
 *
 */
#pragma save_binary

#include "/d/Faerun/defs.h"
#include "/d/Faerun/orcmaker/orcmaker.h"
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";
inherit "/lib/unique";

// stat definitions
#define EASY_STAT   50
#define MEDIUM_STAT 75
#define HARD_STAT   120
#define STRONG_STAT 175
#define TOUGH_STAT  225
// % deviation added to stat, ie 50 would be in the range 45-55.
#define DEV         10

#define LIVE_I_KILL_ORCS  "_live_i_kill_faerun_orcs"
#define TYPE    ({"angry", "barbaric", "beastly", "bloodthirsty", "brutal", \
    "cold-blooded", "cranky", "cruel", "dangerous", "demonic", "deranged", \
    "evil", "feral", "ferocious", "fierce", "foul", "grim", "grouchy", \
    "insane", "mad", "malevolent", "mean", "murderous", "nasty", "rabid", \
    "raging", "ravening", "savage", "sinister", "terrible", "testy", \
    "wicked", "wild"})
#define PHYS    ({"big", "black-haired", "bloody", "broad", "dark-eyed", \
    "dark-skinned", "dirty", "fanged", "grey-skinned", "hairy", "large", \
    "massive", "orange-eyed", "powerful", "red-eyed", "reeking", "short", \
    "smelly", "squat", "squinty-eyed", "strong", "sturdy", "tall", \
    "towering", "ugly", "yellow-eyed", "yellow-tusked"})

// Armours
#define WEAK_ARMS   ({"ibracers"})
#define WEAK_HELM   ({"ihelm"})
#define WEAK_BODY   ({"brig"})
#define WEAK_LEGS   ({"igreaves", "lboots"})
#define BEST_ARMS   ({"sbracers"})
#define BEST_HELM   ({"shelm"})
#define BEST_BODY   ({"chainmail"})
#define BEST_LEGS   ({"sgreaves", "sboots"})
#define SHIELDS     ({"bshield", "oshield"})
#define SHIELDS2    ({"kshield", "oshield"})

// Weapons
#define WEAK_WEPS   ({"scrimasax", "broadsword", "haxe", "baxe", "sclub"})
#define GOOD_WEPS   ({"scimitar", "bastard", "waraxe", "bardiche", "smace", "flail"})
#define BEST_WEPS   ({"longsword", "falchion", "lochaber", "cleaver", "whammer", "mstar"})

#define ATTACK_STYLE    ({"charges", "rushes", "jumps", "lunges"})
#define ATTACK_BODY     ({"long claws", "tooth-filled maw"})
#define ATTACK_HOW      ({"hacks", "slashes", "cuts", "wacks", "cleaves"})
void create_orc() {}
int my_aggressive();
int set_orc_skills();
void arm_me();

// Vars for special
object stunned;  /* Player we stunned */
object gMount;
int release_id;
int iorc_type;   /* orc type value passed to the code when cloned */

void create_monster()
{
    string type, phys;
    int i;

    seteuid(getuid());

    type = ONE_OF_LIST(TYPE);
    phys = ONE_OF_LIST(PHYS);

    npc_name = FAERUN_ORC;

    add_adj(type);
    add_adj(phys);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("orc");
    add_name("orc");
    add_name(npc_name);

    set_short(type + " " + phys + " orc");
    set_pshort(type + " " + phys + " orcs");
    set_long("This is " + query_short() + ". It has long manes of bristly hair on its heads shoulders, and back. The orc has a dog-like face with sharp fangs. Its arms are long and almost reach the ground.\n");
    add_prop(NPC_I_NO_FEAR,1);
    add_prop(LIVE_I_SEE_DARK,2+random(2));
    add_prop(LIVE_I_NEVERKNOWN,1);

    set_chat_time(12+random(14));
    add_chat("You smell worse than ogre!");
    add_chat("You worthless!");
    add_chat("Hey, what you looking at?");
    add_chat("Orcses rule!");
    add_chat("Me killed lots of enemies!");

    set_act_time(14+random(20));
    add_act("flex");
    add_act("growl");
    add_act("emote snorts like a wild beast.");

    set_cchat_time(5+random(10));
    add_cchat("You no need leg, me remove it for you.");
    add_cchat("Me like beating you to dead.");
    add_cchat("You scream like pig!");
    add_cchat("Me wear your hide when you dead.");

    set_cact_time(3+random(4));
    add_cact("emote howls and charges you.");
    add_cact("enote growls dangerously at you.");
    add_cact("snarl");

    create_orc();
    set_aggressive(my_aggressive);
    arm_me();
}

int my_aggressive()
{
    string race = TP->query_race();
    // Leave the poor wizards alone.
    if (TP->query_wiz_level())
	return 0;

    // Hmmm Dinner!!
    if (race == "hobbit" || race == "elf")
	return 1;
    // Goblins are our friends
    if (race == "goblin" || race=="orc")
	return 0;
    // So are evil folk
    if (TP->query_alignment() <= -500)
	return 0;
    // Kill the rest. Free food!
    return 1;
}

void set_orc_type(int orc_type)
{
    int i;

    iorc_type = orc_type;
    switch(orc_type)
    {
        case EASY:
            add_name("easy");
            set_base_stat(0, EASY_STAT, DEV);
            set_base_stat(1, EASY_STAT, DEV);
            set_base_stat(2, EASY_STAT, DEV);
            set_base_stat(3, EASY_STAT/2, DEV);
            set_base_stat(4, EASY_STAT/2, DEV);
            set_base_stat(5, EASY_STAT, DEV);
            break;
        case MEDIUM:
            add_name("medium");
            set_base_stat(0, MEDIUM_STAT, DEV);
            set_base_stat(1, MEDIUM_STAT, DEV);
            set_base_stat(2, MEDIUM_STAT, DEV);
            set_base_stat(3, MEDIUM_STAT/2, DEV);
            set_base_stat(4, MEDIUM_STAT/2, DEV);
            set_base_stat(5, MEDIUM_STAT, DEV);
            break;
        case HARD:
            add_name("hard");
            set_base_stat(0, HARD_STAT, DEV);
            set_base_stat(1, HARD_STAT, DEV);
            set_base_stat(2, HARD_STAT, DEV);
            set_base_stat(3, HARD_STAT/2, DEV);
            set_base_stat(4, HARD_STAT/2, DEV);
            set_base_stat(5, HARD_STAT, DEV);
            break;
        case STRONG:
            add_name("strong");
            set_base_stat(0, STRONG_STAT, DEV);
            set_base_stat(1, STRONG_STAT, DEV);
            set_base_stat(2, STRONG_STAT, DEV);
            set_base_stat(3, STRONG_STAT/2, DEV);
            set_base_stat(4, STRONG_STAT/2, DEV);
            set_base_stat(5, STRONG_STAT, DEV);
            break;
        case TOUGH:
            add_name("tough");
            set_base_stat(0, TOUGH_STAT, DEV);
            set_base_stat(1, TOUGH_STAT, DEV);
            set_base_stat(2, TOUGH_STAT, DEV);
            set_base_stat(3, TOUGH_STAT/2, DEV);
            set_base_stat(4, TOUGH_STAT/2, DEV);
            set_base_stat(5, TOUGH_STAT, DEV);
            break;
        default:
            orc_type = HARD;
            set_base_stat(0, TOUGH_STAT, DEV);
            set_base_stat(1, TOUGH_STAT, DEV);
            set_base_stat(2, TOUGH_STAT, DEV);
            set_base_stat(3, TOUGH_STAT/2, DEV);
            set_base_stat(4, TOUGH_STAT/2, DEV);
            set_base_stat(5, TOUGH_STAT, DEV);
            break;
    }
    set_hp(5000);
    set_orc_skills();
}

int set_orc_skills()
{
    int     ran_num2,
    npc_stat_avg = query_average_stat(),
    mod_skills,
    com_skill,
    spe_skill,
    gen_skill;

    ran_num2 = random(6) + 5;

    set_alignment(-99 - 3 * npc_stat_avg);

    if (npc_stat_avg > 50)
    {
	mod_skills = npc_stat_avg/3 + 100;
    }
    else
    {
	mod_skills = npc_stat_avg * 2;
    }

    com_skill = mod_skills * 45 / 100;
    spe_skill = mod_skills * 50 / 100;
    gen_skill = mod_skills * 40 / 100;

    if (spe_skill > 70)
    {
	spe_skill += ran_num2 * 3;
	if (spe_skill > 100)
	    spe_skill = 100;
    }
    else if (spe_skill < 1)
	spe_skill = 1;

    if (com_skill > 60)
    {
	com_skill = com_skill + ran_num2 * 2;
	if (com_skill > 100)
	    com_skill = 100;
    }
    else if (com_skill < 1)
	com_skill = 1;

    if (gen_skill > 55)
    {
	gen_skill = gen_skill + ran_num2;
	if (gen_skill > 100)
	    gen_skill = 100;
    }
    else if( gen_skill < 1)
	gen_skill = 1;

    set_skill(SS_WEP_SWORD,spe_skill);
    set_skill(SS_WEP_CLUB,spe_skill);
    set_skill(SS_WEP_KNIFE,spe_skill);
    set_skill(SS_WEP_POLEARM,spe_skill);
    set_skill(SS_WEP_AXE,spe_skill);
    set_skill(SS_PARRY,com_skill);
    set_skill(SS_DEFENCE,com_skill);
    set_skill(SS_2H_COMBAT,com_skill);
    set_skill(SS_MOUNTED_COMBAT, com_skill);
    set_skill(SS_RIDING, gen_skill);
    set_skill(SS_SNEAK,gen_skill);
    set_skill(SS_HIDE,gen_skill);
    set_skill(SS_AWARENESS,MIN(55, gen_skill));
    set_skill(SS_ACROBAT,gen_skill);

    // Now that we have our skills set we update the weapons of the npc
    map(query_weapon(-1), update_weapon);
}

void arm_me()
{
    setuid();
    seteuid(getuid());

/* Rewrote the cloning statements to avoid armours being left in the void.
 * /Mercade, December 2014
 */
    
    switch(iorc_type)
    {
    case EASY:
        make_gems(TO, 1);
        clone_object("/d/Faerun/orcmaker/wep/" + ONE_OF_LIST(WEAK_WEPS))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(WEAK_ARMS))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(WEAK_HELM))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(WEAK_BODY))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(WEAK_LEGS))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(SHIELDS))->move(TO,1);
        break;
    case MEDIUM:
        make_gems(TO, 1);
        clone_object("/d/Faerun/orcmaker/wep/" + ONE_OF_LIST(WEAK_WEPS))->move(TO,1);
	clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(WEAK_ARMS))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(WEAK_HELM))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(WEAK_BODY))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(WEAK_LEGS))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(SHIELDS))->move(TO,1);
        break;
    case HARD:
        make_gems(TO, 1);
        clone_object("/d/Faerun/orcmaker/wep/" + ONE_OF_LIST(BEST_WEPS))->move(TO,1);
	clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(BEST_ARMS))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(BEST_HELM))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(BEST_BODY))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(BEST_LEGS))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(SHIELDS2))->move(TO,1);
        break;
    case STRONG:
        make_gems(TO, 1);
        clone_object("/d/Faerun/orcmaker/wep/" + ONE_OF_LIST(BEST_WEPS))->move(TO,1);
	clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(BEST_ARMS))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(BEST_HELM))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(BEST_BODY))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(BEST_LEGS))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(SHIELDS2))->move(TO,1);
        break;
    case TOUGH:
        make_gems(TO, 1);
        clone_object("/d/Faerun/orcmaker/wep/" + ONE_OF_LIST(BEST_WEPS))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(BEST_ARMS))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(BEST_HELM))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(BEST_BODY))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(BEST_LEGS))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(SHIELDS2))->move(TO,1);
        break;
    default:
        make_gems(TO, 1);
        clone_object("/d/Faerun/orcmaker/wep/" + ONE_OF_LIST(WEAK_WEPS))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(WEAK_ARMS))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(WEAK_HELM))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(WEAK_BODY))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(WEAK_LEGS))->move(TO,1);
        clone_object("/d/Faerun/orcmaker/arm/" + ONE_OF_LIST(SHIELDS))->move(TO,1);
        break;
    }
    command("wield weapons");
    command("wear armours");
}


/* Redefined the special attack called in the combat routine to give
 * all orcs created with this master npc maker a nice foot stomping
 * special attack, or 'stunning' move if teamed.
 * Mayhem, 11 April 1994
 */
int
special_attack(object enemy)
{
    int     delay,npc_str = query_stat(SS_STR);
    object  me = this_object();
    mixed  *hitresult;
    string  limb, how;
    string  attack_style, attack_body, attack_how;

    attack_style = ONE_OF_LIST(ATTACK_STYLE);
    attack_body = ONE_OF_LIST(ATTACK_BODY);
    attack_how = ONE_OF_LIST(ATTACK_HOW);

    if (random(5))
	return 0;
    if (objectp(gMount) && gMount == me->query_prop(LIVE_O_STEED))
    {
	    //hitresult = enemy->hit_me(npc_str * 2 + random(npc_str), W_SLASH, me, -1);
        hitresult = enemy->hit_me(npc_str + random(npc_str  / 2), W_SLASH, me, -1);
	    switch(hitresult[0])
	    {
            case -1:
            case 0:
                how = "unharmed";
                break;
            case 1..5:
                how = "a little hurt";
                break;
            case 6..10:
                how = "slightly hurt";
                break;
            case 11..25:
                how = "somewhat hurt";
                break;
            case 26..40:
                how = "injured";
                break;
            default:
                how = "badly wounded";
                break;
        }
	// The attack stuns the enemy for 1 combat round
    	enemy->add_attack_delay(1);
	// Send no msg to the npc
	    enemy->catch_tell("The "+me->query_nonmet_name()+"'s "+
	        gMount->query_nonmet_name() + " " + attack_style + ", knocking you to the "+
	        (ENV(enemy)->query_prop(ROOM_I_INSIDE) ? "floor" : "ground") +
	        "and stunning you briefly. Suddenly the "+me->query_race_name()+
	        (sizeof(me->query_weapon(-1)) ? " " + attack_how + " wildy at your prone body "+
	        "with his "+query_weapon(-1)[0]->short() : "'s "+
	        gMount->query_race_name()+" mauls you with its razor-sharp, " +
            attack_body + " ")+ " leaving you "+how+ ".\n");
	    me->tell_watcher(QCTNAME(me)+"'s "+QTNAME(gMount)+" " + attack_style + " " +
	        QTNAME(enemy)+", knocking "+HIM_HER(enemy)+" to the "+
	    (ENV(enemy)->query_prop(ROOM_I_INSIDE) ? "floor" : "ground") +
	    " stunning "+HIM_HER(enemy)+" briefly. Suddenly the " +
	    me->query_race_name()+ ((sizeof(query_weapon(-1))) ?
	    " " + attack_how + " wildly at "+QTNAME(enemy)+"'s prone body with its "+
	    query_weapon(-1)[0]->short() : "'s "+gMount->query_race_name()+
	    " mauls "+QTNAME(enemy)+" with its razor_sharp, " + attack_body + " ")+
	    "leaving "+QTNAME(enemy)+" feeling "+how+" from the attack.\n", enemy);
    	return 1;
        }

// If I am teamed and the enemy isn't held we hold him :)
//    if (sizeof(filter(me->query_team_others(), &operator(==)(environment(me)) @
//	    environment)) && !enemy->query_prop(LIVE_I_STUNNED))
//    {
//	    switch(random(4))
//        {
//            case 0:
//                limb = "arm";
//                break;
//            case 1:
//                limb = "leg";
//                break;
//            case 2:
//                limb = "head";
//                break;
//            case 3:
//                limb = "body";
//                break;
//        }
//
//    delay = 10 + random(6);  // 2-3 combat rounds.
//    enemy->add_stun();
//    me->add_stun();  // I am holding onto their legs!
//    release_id = set_alarm(itof(delay),0.0, &release(me));
//    stunned = enemy;
//
//        // Send no msgs to the npc
//    enemy->catch_msg(QCTNAME(me)+" grabs hold of your "+limb+" and "+
//        "hinders your movement.\n");
//    me->tell_watcher(QCTNAME(me)+" grabs hold of "+QCTNAME(enemy)+
//        " and attempts to keep "+HIM_HER(enemy)+
//        " from moving.\n",enemy);
//    return 1;
//    }
//    else
    {
	    hitresult = enemy->hit_me(npc_str + random(npc_str), W_BLUDGEON, me, -1);

        if (hitresult[0] > 12) /* hitresult[0] yields the % hurt. */
	        how = "with fists swinging, and pounds you terribly";
	    else if (hitresult[0] > 9)
	        how = "with fists swinging, and beats you hard";
	    else if (hitresult[0] > 6)
	        how = "and hugs you tightly. You hear bones snap";
	    else if (hitresult[0] > 4)
	        how = "and hugs you tightly, cracking bones";
	    else if (hitresult[0] > 2)
	        how = "headlong and hurts you slightly";
	    else if (hitresult[0] > 0)
	        how = "headlong and pushes you back slightly";
	    else
	        how = "headlong and bounces off you";

	// Send no msgs to the npc
	    enemy->catch_msg(QCTNAME(me)+" rushes you "+ how +".\n");
	    me->tell_watcher(QCTNAME(me)+" rushes "+QTNAME(enemy) + ".\n",enemy);

	    if(enemy->query_hp() <= 0)
	        enemy->do_die(me);
	    return 1;

    }
}

void
release(object me)
{
    if (!stunned)
	return;

    stunned->remove_stun();
    if (!me)
	return;
    me->remove_stun();
    if (present(stunned,ENV(me)))
    {
	stunned->catch_msg(QCTNAME(me) + " releases "+HIS_HER(me)+" grip on you.\n");
	tell_watcher(QCTNAME(me) +" releases "+ HIS_HER(me) +" grip on "+
	    QTNAME(stunned)+".\n", stunned);
    }
    stunned = 0;
    remove_alarm(release_id);
    release_id = 0;
}

public void
do_die(object killer)
{
    if (!TO->query_hp() <= 0)
	return;

   /* if (killer->query_alignment() < 0)
	{
		this_object()->set_exp_factor(10);
	
		killer->catch_tell("Since you are of an evil "
			+"alignment, you sense that the reward for "
			+"killing this creature is greatly diminished!\n");	
	}*/

    if (release_id)
    {
	remove_alarm(release_id);
	release_id = 0;
    }
    if (objectp(gMount))
	gMount->notify_rider_killed(killer);
    if (objectp(stunned) && objectp(TO))
	if (present(stunned, ENV(TO)))
	    stunned->catch_msg(QCTNAME(TO)+" releases "+HIS_HER(TO)+" grip on you "+
	      "as it dies.\n");

    if (stunned)
    {
	if (stunned->query_prop(LIVE_I_STUNNED))
	    stunned->remove_stun();
	stunned = 0;
    }

    return ::do_die(killer);
}

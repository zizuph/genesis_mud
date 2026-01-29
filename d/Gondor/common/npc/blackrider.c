/*
 * /d/Gondor/common/npc/blackrider.c
 * 
 * One of the nastiest dangers to be met in Gondor.
 * Killable only with Undead-slaying magical weapons.
 * By Elessar, Gondor, Genesis - 5. Nov. 1992.
 * changed black breath from add_cact to special_attack, Olorin, 19-sep-1993
 * special_attack() modifed to use resolve_task(), Olorin, 2-nov-1993
 * added resistance against magic,
 * reduced effectiveness of special attacks on nazgul,
 * added alignment bonus for hits on nazgul.
 * Olorin, 12-nov-1993
 * Increased Nazgul stats to 160 for str, dex and con
 * Increased magic resistance, except lowering it for fire, as from
 * the books...  Dunstable March 20, 1994
 *
 *	General revision, changed inheritance,
 *	Olorin, 20-Feb-1997
 *
 * Added pshort_func. Gnadnar, 9-Feb-99
 * Gwyneth, December 13, 2000:
 *     Reduced enchanted weapon breaking ability from a random
 *     number taken from the strength of the enchantment from
 *     having to be less than 5 to break the weapon to having
 *     to be less than 4 to break the weapon.
 *     Increased the damage of special attacks from 1/20th of their
 *     actual damage to 1/10th of their actual damage.
 * Serif, March 31, 2003: 
 *     Added do_mute() to disable Minstrel spells which were being
 *     used to kill the Nazgul abnormally frequently.
 * Finwe, July 27, 2005:
 *     Added TELL_ADMIN functions so domain is notified when npc is cloned
 *     and/or attacked.
 * Gorboth, December 2010:
 *     Added set_all_hitloc_unarmed() and set_all_attack_unarmed() to make
 *     him tougher and more dangerous. Also, increased combat stats by 100.
 *     The nazgul should represent one of the elite monsters in the game.
 *     The playerbase has matured to the point where he is no longer all
 *     that difficult to kill.
 * Gorboth, October 2012:
 *      Set black breath frequency to 40%. The ScoP are killing him like
 *      it is going out of style. The player Hektor suggested increasing
 *      his poison frequency as a potential way to mitigate this.
 * Gorboth, August 2018:
 *      Npcs may no longer attack the Black Rider. Morgul Mages and
 *      other clever players have been exploiting spells that force
 *      an npc to attack it to easily farm the FBB.
 * Finwe, March 2020:
 *      Added clone_unique()to weapons and armours
 * Finwe, May 2020:
 *      Commented out LIVE_O_ENEMY_CLING so players can't drag the npc around
 *      and have it killed.
 * Zizuph, Oct 2022:
 *      Migrate Rider to the current guild library.  Upgrade the mentals
 *      and use the new spells against its foes.
 * Zizuph, Oct 2022:
 *      Increase air and fire skills to 100.  Fix issue where narusse
 *      is double-flaming the flaming black broadsword.  Only its 
 *      shortsword is supposed to light up via the spell.
 *
 */
#pragma strict_types

inherit "/d/Gondor/std/monster.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage_titles.h"

#include "/d/Gondor/private/gondor_admin.h"

#define CEX if (!combat_extern) combat_reload()

#define NPC_LOG               (LOG_DIR + "npcs")
#define BLACK_BREATH_FQ_1     100   /* random(FQ_1) < FQ_2 ==> special attack  */
#define BLACK_BREATH_FQ_2      40   /* ie with FQ_1 = 100, FQ_2 = 40 ==> 40%   */
#define NAZGUL_SKILLS         ({TS_DEX, SS_SPELLCRAFT, SS_FORM_CONJURATION, SS_ELEMENT_DEATH})
#define PLAYER_SKILLS         ({TS_DEX, SS_SPELLCRAFT, SS_FORM_ABJURATION,  SS_ELEMENT_LIFE})

#define HIS(x)		(x)->query_possessive()
#define DEBUG(x)	find_player("arman")->catch_msg("[Nazgul] " + x + "\n")

#define ENABLE_BLACK_BREATH (0)
#define UNARMED_ATTACK_PROPAGATION  ([ \
    W_RIGHT:    (A_R_HAND | A_R_WRIST), \
    W_LEFT:     (A_L_HAND | A_L_WRIST), \
    W_BOTH:     (A_R_HAND | A_L_HAND | A_R_WRIST | A_L_WRIST), \
    W_FOOTR:    (A_R_FOOT | A_R_ANKLE | A_LEGS), \
    W_FOOTL:    (A_L_FOOT | A_L_ANKLE | A_LEGS), \
])

inherit "/lib/unique";

/*
 *	Prototypes:
 */
static string  emote_enemy(string str);
static string  exa_beast();
static string  exa_horse();
static string  long_func();
static string  short_func();
static string  pshort_func();
static void    hiss(string str);
public int     can_attack_nazgul();
void           add_stuff ();

/*
 *	Global variables:
 */
static int     Hooded = 1,
               Riding = 1;
static object  Last_Item;
static mapping Unarmed_Attack_Propagation = UNARMED_ATTACK_PROPAGATION;

//public int do_mute(string str);

public void
create_gondor_monster()
{
    set_name("wraith");
    set_race_name("wraith");
    set_living_name("nazgul");
    add_name( ({ "nazgul", "man", "shape", "figure", "rider",
		 "ringwraith", "shadow"})); 
    set_adj( ({ "dark-skinned", "black-robed", "red-eyed", })); 

    set_short("@@short_func@@");
    set_pshort("@@pshort_func@@");
    set_long(long_func);

    set_stats( ({ 320 + random(11), 300 + random(11), 
		  300 + random(11), 245 + random(11),
		  235 + random(11), 260 + random(11), }));

    set_learn_pref( ({ 1, 1, 1, 0, 0, 0, }) );
    set_base_stat(SS_OCCUP, query_average_stat() + random(11) - 5);
    add_subloc(MORGUL_S_SUBLOC, TO);
    set_alignment(-900);

    /* We'll make this npc have default ac due to magical nature. */
    set_all_hitloc_unarmed(100);
    set_all_attack_unarmed(50, 50); /* still deadly when unarmed */

    set_skill(SS_WEP_SWORD,  100);
    set_skill(SS_2H_COMBAT,   90);
    set_skill(SS_WEP_CLUB,   100);
    set_skill(SS_WEP_KNIFE,   50);
    set_skill(SS_PARRY,      100);
    set_skill(SS_DEFENCE,    100);
    set_skill(SS_AWARENESS,  100);
    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_FORM_ENCHANTMENT,   60);
    set_skill(SS_FORM_CONJURATION,  100);
    set_skill(SS_FORM_ABJURATION,    60);
    set_skill(SS_FORM_ILLUSION,      40);
    set_skill(SS_FORM_TRANSMUTATION, 40);
    set_skill(SS_FORM_DIVINATION,    20);
    set_skill(SS_ELEMENT_DEATH,     100);
    set_skill(SS_ELEMENT_AIR,       100);
    set_skill(SS_ELEMENT_FIRE,      100);
    set_skill(SS_ELEMENT_LIFE,       40);
    set_skill(SS_ELEMENT_EARTH,      60);
    set_skill(SS_ELEMENT_WATER,      60);
   
    add_prop(CONT_I_HEIGHT,    198);
    add_prop(CONT_I_WEIGHT,  98000);
    add_prop(LIVE_I_SEE_INVIS, 100);
    add_prop(NPC_I_NO_LOOKS,     1);
    add_prop(LIVE_I_NEVERKNOWN,  1);
    add_prop(LIVE_I_NO_CORPSE,   1);
   
    add_prop(OBJ_I_RES_MAGIC,   70);
    add_prop(OBJ_I_RES_DEATH,   70);
    add_prop(OBJ_I_RES_LIFE,    70);
    add_prop(OBJ_I_RES_LIGHT,   70);
    add_prop(OBJ_I_RES_WATER,   20);
    add_prop(OBJ_I_RES_AIR,     70);
    add_prop(OBJ_I_RES_EARTH,   40);
    add_prop(OBJ_I_RES_FIRE,    20);
    add_prop(OBJ_I_RES_COLD,    60);
    add_prop(OBJ_I_RES_POISON, 100);
    add_prop(OBJ_I_RES_ELECTRICITY, 30);

    add_prop(OBJ_M_NO_ATTACK, "@@can_attack_nazgul@@");
   
    add_item("horse", exa_horse);
    add_item("beast", exa_beast);

    set_act_time(5);
    add_act(hiss);
    add_act("battlesong");
    add_act("gaze");
    add_act("leer");
    add_act("mlaugh");
    add_act("mordor");
    add_act("mremember");
    add_act("mscoff");
    add_act("msmile");
    add_act("msniff");
    add_act("torture");

    set_cact_time(1);
    add_cact(hiss);
    add_cact("mcurse");
    add_cact("shriek");
    add_cact(&emote_enemy("damn"));
    add_cact(&emote_enemy("mcurse"));
    add_cact(&emote_enemy("mscoff"));
    add_cact(&emote_enemy("sneer"));
    add_cact(&emote_enemy("torture"));
    add_cact(&emote_enemy("wrath"));
    add_cact("mwail");

//    set_equipment( ({ WEP_DIR + "nazgul_sword", 
//		      ARM_DIR + "nazgul_plate", 
//		      ARM_DIR + "nazgul_helm", }) );

    set_alarm (0.0, 0.0, &add_stuff());

    TELL_ADMIN("Nazgul was cloned at " + ctime(time()));

}


void
add_stuff()
{
    object wep, arm1, arm2, arm3;   

    wep = clone_unique("/d/Gondor/common/wep/nazgul_sword", MAX_UNIQUE_ITEMS,
        "/d/Gondor/common/wep/nazgul_basic_sword");
    wep -> move(this_object());

    arm1 = clone_unique("/d/Gondor/common/arm/nazgul_helm", MAX_UNIQUE_ITEMS,
        "/d/Gondor/common/arm/nazgul_basic_helm");
    arm1->move(this_object());

//    arm1 = clone_object(ANN_ARM + "gauntlets");
    arm2 = clone_unique("/d/Gondor/common/arm/nazgul_plate", MAX_UNIQUE_ITEMS,
        "/d/Gondor/common/arm/nazgul_basic_plate");
    arm2 -> move(this_object());

    arm3 = clone_unique("/d/Gondor/common/arm/nazgul_gauntlets", MAX_UNIQUE_ITEMS,
        "/d/Gondor/common/arm/nazgul_basic_gauntlets");
    arm3 -> move(this_object());
   
    command("wear all");
    command("wield weapon");
    
    object mage_shadow = clone_object(MORGUL_SHADOW);
    mage_shadow->shadow_me(this_object(), GUILD_TYPE, GUILD_STYLE,
        GUILD_NAME, "");

    this_object()->set_nazgul(1);
}

public void
set_beast_type(int i)
{
    /* 0 = On foot, 1 = Black Horse, 2 = Fell Beast */
    if (i < 0)
        Riding = 0;
    else if (i > 2)
        Riding = 2;
    else
        Riding = i;
}

static string
random_hiss()
{
   switch (random(5))
   {
   case 0: 
       return "";
   case 1: 
       return "I seek Bagginss!";
   case 2: 
       return "Bagginsss is not in the Shire anymore!";
   case 3: 
       return "Bagginsss has sssomething I want!";
   case 4: 
       return "I will reward you well if you tell me where Bagginsss isss!";
   default: 
       return "";
   }
}

static void
hiss(string str)
{
    if (strlen(str)) 
	tell_room(ENV(TO),"The black rider hisses: "+str+"\n",TO);
    else 
	hiss(random_hiss());
}

public void
arm_me()
{
    object  robe;

    ::arm_me();

    robe = clone_object(MAGES_DIR + "npc/npc_robe");
    robe->check_spell_object(TO);
    robe->move(TO);
    add_cmdsoul(MORGUL_COMMAND_SOUL);
    update_hooks();
    command("wear robe");
}

static void
fear(int panic, object who)
{
    if (IS_MORGUL_MAGE(who))
        return;

    who->catch_msg(BSN("You feel fear creeping upon you as you look " +
		       "at the dark, menacing figure, and you " +
		       "struggle to control yourself!")); 
    who->add_panic(panic + MAX(0, (1000 - ABS(who->query_alignment())) / 10 ));
}

static void
test_presence()
{
    if (CAN_SEE(TO,TP))
	TP->catch_tell("You feel that the black shape is staring straight at you.\n");
}

public void
init_living()
{
    ::init_living();
    fear(60, TP);
    test_presence();
  //  add_action(do_mute, "sing");
  //  add_action(do_mute, "perform");
  //  add_action(do_mute, "play");
}

/*
 * Function name: init_attack
 * Description:   Called from init_living()
 */
public void
init_attack()
{
    if ((!monster_aggressive) || (TP->query_npc()) ||
	(query_friend_or_foe(TP) < 1)) 
        return;

    if ((monster_attack_chance == 0) || (random(100) < monster_attack_chance))
        set_alarm(2.0, 0.0, &aggressive_attack(TP));
}

public string
short_func()
{
    switch (Riding)
    {
    case 1:
	return "large black-cloaked shape riding a black horse";
    case 2:
	return "large black-cloaked shape riding a fell winged beast";
    default:
	return "large black-cloaked, hooded man on foot";
    }
}

public string
pshort_func()
{
    switch (Riding)
    {
    case 1:
	return "large black-cloaked shapes riding black horses";
    case 2:
	return "large black-cloaked shapes riding fell winged beasts";
    default:
	return "large black-cloaked, hooded men on foot";
    }
}

static string
mount_desc(int i)
{
    switch (i)
    {
    case 0:
	return "is walking on foot.";
    case 1:
	return "is riding a large black horse.";
    case 2:
	return "is riding a fell winged beast.";
    }
}

static string
long_func()
{
    string  desc;

    if (TP->query_prop(LIVE_I_SEE_INVIS))
	desc = "The tall, dark shape now stands terribly clear " +
	    "before you. In his white face burns keen and merciless " +
	    "eyes; under his mantle is a long grey robe; upon his " +
	    "grey hairs a helm of silver, and sword of steel in his " +
	    "haggard hand. The threatening man ";
    else if (Hooded)
	desc = "The black shape looks like a man, wrapped in a " +
	    "great black cloak and hood, so that only his boots " +
	    "show below. His face is shadowed and invisible, save a " +
	    "deadly gleam of eyes. The threatening shape ";
    else
	desc = "The black shape looks like a man, wrapped in a " +
	    "great black cloak, his hood flung back. A helm of " +
	    "silver he wears, but between helm and robe there is " +
	    "nothing to see, save only a deadly gleam of eyes! " +
	    "This is a Nazgul, one of Saurons most deadly " +
	    "servants. The wraith ";

    desc += mount_desc(Riding); 
    return BSN(desc);
}

static string
exa_horse()
{
    if (Riding == 1) 
	return BSN("The horse is black as night, and one of the " +
		   "largest you have seen. Its eyes gleam with a " +
		   "maddening red light, as if controlled by some " +
		   "terrifying evil."); 
    return "You find no horse.\n";
}

static string
exa_beast()
{
    if (Riding == 2) 
	return BSN("The huge fell beast is a terrifying image to " +
		   "look upon! Large bony featherless wings stretch " +
		   "out several meters to both sides, and on the " +
		   "end of a long hideous neck sits a scary head " +  
		   "as from a creature of ancient times, with a " +
		   "long beak and eyes gleaming with malice. The " +
		   "creature flaps its wings, and gives a wailing " +
		   "high-pitched screech filling you with terror!"); 
    return "You find no beast.\n";
}

static int
break_item(object it, object att)
{
    if (!objectp(att) || !objectp(it))
    return 0;
    tell_object(att, "Your " + it->query_name() +
         " breaks in many shards as it hits the menacing shape!\n");
    tell_room(ENV(TO), QCTNAME(att) + "'s " + 
    check_call(it->short()) +
        " breaks into many shards as it hits the menacing shape!\n", att);
    it->remove_broken();
    command("cackle");
    hiss("No living man may hinder me, fool!");
    return 1;
}

/*
 * Function name:   query_not_attack_me
 * Description:     The intended victim may force a fail when attacked.
 *                  If fail, the cause must produce explanatory text himself.
 * Arguments:       who: The attacker
 *                  aid: The attack id
 * Returns:         True if the attacker fails hitting us, false otherwise.
 */
public int
query_not_attack_me(object att, int att_id)
{
    object  weapon = att->query_weapon(att_id);
    mixed  *mag_arr;
    int     mid;

    if (att->query_npc())
    {
        att->run_away();
        return 1;
    }
   
    if (objectp(weapon))
    {
        Last_Item = weapon;
        if (!weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON)) 
        {
            if (!random(10))
            {
                tell_room(ENV(TO),QCTNAME(att)+"'s " +
                    weapon->query_name() +
                    " seems to have no effect against the wraith!\n",
                    att);
            }
            else 
            {
                break_item(weapon, att);
            }
            return 1;
        }
        mag_arr = weapon->query_prop(MAGIC_AM_MAGIC);
        /* added this to find source of runtime errors, Olorin, 04-may-1995 */
        if (!pointerp(mag_arr))
        {
            tell_room(ENV(TO), "The "+weapon->query_name() +
                " is broken. Please make a bug report!\n");
            log_file("npcs", file_name(weapon) +
                " has MAGIC_AM_MAGIC prop set " +
                " to an illegal value!\n");
            return 1;
        }
        if ((mid = member_array("undead-slaying", mag_arr)) > -1)
        {
            if (random(mag_arr[mid-1]) == 0)
            {
                break_item(weapon,att);
            }
            return 0;
        }
        if ((mid = member_array("enchantment", mag_arr)) > -1) 
        {
            if (random(mag_arr[mid-1]) < 4)
            {
                break_item(weapon,att);
            }
            return 0;
        }
        tell_room(ENV(TO), BSN("The magic in the " +
            check_call(weapon->short()) +
            " seems to have no effect on the wraith."));
        hiss("Your pitiful " + check_call(weapon->short()) +
            " does not worry me, mortal!");
        if (random(mag_arr[sizeof(mag_arr)-2]) < 10)
        {
            break_item(weapon,att);
        }
    }
    else
    {
        /* Ckrik 5/18/2021
         * The check for weapons completely disables unarmed attackers from
         * doing any sort of damage. As a fix, we check the relevant armour
         * slots for magical armour, mirroring the logic in weapons for
         * unarmed combatants.
         *
         * Since we're unable to map specials (i.e. attack_ids == -1)
         * we disallow unarmed special hits.
         * 
         * See #define UNARMED_ATTACK_PROPAGATION defined above for slot
         * mapping.
         */
        int slots = Unarmed_Attack_Propagation[att_id];
        object* armour_list = ({});

        // Collect all the armours from the eligible armour slots
        foreach (object armour : att->query_armour(-1))
        {
            // Skip auto load or quest objects
            if (armour->query_auto_load() || armour->query_prop(OBJ_M_NO_DROP))
            {
                continue;
            }

            foreach (int s : armour->query_slots())
            {
                if ((s & slots) != 0)
                {
                    armour_list += ({ armour });
                }    
            }
        }

        if (sizeof(armour_list) == 0)
        {
            if (!random(10) || 1)
            {
                if (att_id != -1)
                {
                    tell_room(ENV(TO), QCTNAME(att)+ "'s " + att->cr_attack_desc(att_id) +
                        " seems to have no effect against the wraith!\n", att
                    );
                }
                else
                {
                    // Text for special attacks
                    tell_room(ENV(TO), QCTNAME(att)+ "'s special attack" +
                        " seems to have no effect against the wraith!\n", att
                    );
                }
            }
            return 1;
        }

        object armour = one_of_list(armour_list);
        Last_Item = armour;
        if (!armour->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
        {
            if (!random(10) || 1)
            {
                tell_room(ENV(TO), QCTNAME(att)+ "'s " + att->cr_attack_desc(att_id) +
                    " protected by " + att->query_possessive() + " " + armour->query_name() +
                    " seems to have no effect against the wraith!\n", att
                );
            }
            else
            {
                break_item(armour, att);
            }
            return 1;
        }
        mag_arr = armour->query_prop(MAGIC_AM_MAGIC);
        if (!pointerp(mag_arr))
        {
            tell_room(ENV(TO), "The "+ armour->query_name()
                + " is broken. Please make a bug report!\n");
            log_file("npcs", file_name(armour) + " has MAGIC_AM_MAGIC prop set "
                + " to an illegal value!\n");
            return 1;
        }
        if ((mid = member_array("undead-slaying", mag_arr) || 1) > -1) {
            if (random(mag_arr[mid-1]) == 0)
            {
                break_item(armour, att);
                return 0;
            }
        }
        if ((mid = member_array("enchantment", mag_arr) || 1) > -1) 
        {
            {
                if (random(mag_arr[mid-1]) < 4)
                {
                    break_item(armour, att);
                }
                return 0;
            }
        }
        tell_room(ENV(TO), BSN("The magic in the " +
            check_call(armour->short()) +
            " seems to have no effect on the wraith."));
        hiss("Your pitiful " + check_call(armour->short()) +
            " does not worry me, mortal!");
        if (random(mag_arr[sizeof(mag_arr)-2]) < 10)
        {
           break_item(armour, att);
        }
    }
    return 1;
}

/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks we died.
 * Arguments:       killer: The enemy that caused our death.
 */
public int
do_die(object killer)
{
    if (query_hp() > 0) 
        return 0;
    if (!objectp(killer))
        killer = previous_object();
    if (IS_WEAPON_OBJECT(Last_Item))
    {
        tell_object(killer,"You swing your weapon in between helm and mantle of the Nazgul.\n");
        tell_room(ENV(TO), BSN(QCTNAME(killer) + " swings " + 
            HIS(killer) + " weapon between helm and mantle of the " +
            "dark figure."), killer);
    }
    else
    {
        tell_object(killer,"Your strike with your fist in between helm and mantle of the Nazgul.\n");
        tell_room(ENV(TO), BSN(QCTNAME(killer) + " strikes with " + 
            HIS(killer) + " fist between helm and mantle of the " +
            "dark figure."), killer);
    }
    tell_room(ENV(TO), BSN("The helm rolls to the ground with a " +
        "clang, and behold! The mantle and hauberk are empty, and " +
        "fall shapeless to the ground, torn and tumbled!") + 
    BSN("A cry goes up into the shuddering air, fading to a " + 
        "wailing passing with the wind, a voice, bodiless and " +
        "thin, dies out.")); 

    combat_extern->cb_death_occured(killer);

    this_object()->notify_death(killer);

    if (living(killer))
    {
        combat_reward(killer, 0, 1);
    }

    killer->notify_you_killed_me(TO);
    write_file(NPC_LOG, "Black Rider: Killed by " + 
        killer->query_name() + " (" + 
        killer->query_average_stat() + ") on " + ctime(time()) +
        ".\n");  
    
    if (objectp(Last_Item))
        write_file(NPC_LOG, " - possibly killed with " + Last_Item->short()+" - " +
            MASTER_OB(Last_Item)+".\n");

    move_all_to(ENV(TO));
    TO->remove_object();
    return 1;
}

static varargs string
black_breath(object victim)
{ 
    int     stat,
            strength = 100;
    object  breath;

    if (!objectp(victim))
        victim = TO->query_attack();
   
    if (!objectp(victim))
        return "";
   
    if (ENV(TO) == ENV(victim))
    {
        victim->catch_msg(QCTNAME(TO) + " hisses a cold, dark breath at you!\n"+
			  "A dreadful chill runs down your spine!\n");
        tell_room(ENV(TO),QCTNAME(TO)+" hisses at " + QTNAME(victim) +
		  " coldly.\n",victim);
        seteuid(getuid(TO));
	breath = clone_object(POISON_DIR + "black_breath");
	breath->move(victim, 1);

	if ( (stat = victim->query_stat(SS_CON)) > 100)
	{
	    strength = (stat - 100) / 2;
	    strength = 101 + strength + random(strength);
	}
	breath->set_strength(strength);
	breath->start_poison();
	write_file(LOG_DIR + "curses", victim->query_name() +
           " (" + stat + ") poisoned with Black Breath (" + 
           strength + ") by a Nazgul, " + ctime(time()) + ".\n");
    }
    return "";
}

/* Solamnian Knights are honoured by this kill. */
public int query_knight_prestige() { return 2500; }

static int filter_enemy(object x)        { return (x->query_attack() == TO); }

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
special_attack(object enemy)
{
    object  *victim = ({ });
    int      i,
             task;
   
//    add_prop(LIVE_O_ENEMY_CLING, enemy);
   
    if (ENABLE_BLACK_BREATH)
    {
   
        victim = filter(all_inventory(ENV(TO)), filter_enemy);
   
        if (sizeof(query_weapon(-1)))
        {
        	if (random(BLACK_BREATH_FQ_1) >= BLACK_BREATH_FQ_2)
	            return 0;
	        task = (TASK_DIFFICULT + TASK_ROUTINE) /2;
	        if (!random(3))
	            victim = ({ enemy });
	        else
	            if (!objectp(victim))
		    return 1;
	        victim = ({ victim[random(sizeof(victim))] });
        }
        else
        {
	    task = (TASK_SIMPLE + TASK_ROUTINE) /2;
        }

        i = sizeof(victim);
        while (i--)
        {
	    if (victim[i]->resolve_task(task, PLAYER_SKILLS, TO, NAZGUL_SKILLS) > 0)
	    {
    	    if (ENV(TO) == ENV(victim[i]))
                {
		    victim[i]->catch_msg(QCTNAME(TO)+" hisses a cold, dark breath at you!\n");
		    tell_room(ENV(TO),QCTNAME(TO)+" hisses at "+QTNAME(victim[i])+" coldly.\n",victim[i]);
		    fear(50, victim[i]);
	        }
	    }
	    else
    	    black_breath(victim[i]);
        }
        return 1;
    }
    if (objectp(enemy))
    {
        string* damage_spells;
        string* other_spells = ({});
        
        if (!present("_nazgul_broadsword", this_object()))
        {
            // Flaming black shortsword.
            other_spells += ({ "narusse" });
        }
        string name = OB_NAME(enemy);
        // Disable the weapon of the attacker.
        other_spells += ({ "naro " + name + " libo makil" });
        if (enemy->query_prop(LIVE_I_UNDEAD))
        {
            damage_spells = ({ "dramalgos", "thunaur" });
        }
        else
        {
            damage_spells = ({ "dramalgos", "thunaur", "mordru", "morthul" });
        }
        // Start spell right after the weapon is swung, to get benefit of both.
        set_alarm(0.1, 0.0, &command(one_of_list(damage_spells)));
        if (sizeof(other_spells))
        {
            set_alarm(0.1, 0.0, &command(one_of_list(other_spells)));
        }
    }
    return 0;
}

/*
 * Function name:   hit_me
 * Description:     Called to make damage on this object. The actually
 *                  made damage is returned and will be used to change
 *                  the score of the aggressor.
 * Arguments:       wcpen         - The wc-penetration
 *                  dt            - damagetype, use MAGIC_DT if ac will not
 *                                  help against this attack.
 *                  attacker      - Object hurting us
 *                  attack_id     - Special id saying what attack hit us. If 
 *                                  you have made a special attack, let the 
 *                                  id be -1
 *                  target_hitloc - Optional argument specifying a hitloc
 *                                  to damage.  If not specified or an
 *                                  invalid hitloc is given, a random
 *                                  one will be used.
 * Returns:         The hitresult as given by the external combat object.
 */
public varargs mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
    mixed   result;
    int     dam,
            ap;
   
    if ((attack_id == -1) && (dt != MAGIC_DT))
	result = ::hit_me(wcpen/10, dt, attacker, attack_id);
    else if (attack_id == 0 && dt != MAGIC_DT)
        result = ::hit_me(wcpen/10, dt, attacker, attack_id);
    else
	result = ::hit_me(wcpen, dt, attacker, attack_id);
   
    if (result[3] > 0)
    {
	ap = attacker->query_alignment();
	dam = result[3] * MAX(0, 500 - ap);
	attacker->set_alignment(ap + dam/1500);
    }
    return result;
}

/*
 * These functions taken from:
 * /d/Gondor/common/guild2/morgul_shadow.c
 *
 * The guild shadow for the Morgul Mages of Gondor
 */
string  query_guild_style_occ() { return GUILD_STYLE; }
string  query_guild_name_occ() { return GUILD_NAME; }
int     query_nazgul() { return 1; }
int     query_morgul_penalty() { return 1; }


/*
int
query_morgul_level()
{
    int     m_stat = query_stat(SS_OCCUP),
            mlevel,
            nlevels = sizeof(MORGUL_AS_MALE_TITLES);

    if (m_stat > 100)
        m_stat = 100;

    mlevel = ((m_stat * (nlevels - 1)) / 100);
    mlevel -= query_morgul_penalty();
    if (mlevel < 0)
        mlevel = 0;
    mlevel += (query_nazgul() * nlevels);
    return mlevel;
}

string
query_morgul_title()
{
    if (query_nazgul())
    {
        if (query_gender() == 1)
            return MORGUL_AS_FEMALE_NAZGUL_TITLES[query_nazgul()-1];
        else
            return MORGUL_AS_MALE_NAZGUL_TITLES[query_nazgul()-1];
    }

    if (query_gender() == 1)
        return MORGUL_AS_FEMALE_TITLES[query_morgul_level()];
    return MORGUL_AS_MALE_TITLES[query_morgul_level()];
}

string  query_guild_title_occ() { return query_morgul_title(); } 
*/

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		  me      - I
 *		  for_obj - The looker
 * Returns:	  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    int    hs,
           hl,
           mmp;
    string str;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (subloc != MORGUL_S_SUBLOC)
        return ::show_subloc(subloc, me, for_obj);

    if (for_obj == me)
	str = "You are ";
    else
	str = CAP(me->query_pronoun()) + " is ";

    switch(query_nazgul())
    {
        case 1:
            str += "one of the Nazgul of the Society of Morgul Mages.\n";
            break;
        case 2:
            str += "the Lord of the Nazgul, King of Minas Morgul.\n";
            break;
        case 0:
        default:
            str += "a Member of the Society of Morgul Mages.\n";
            break;
    }

    return str;
}

void
loot_corpse()
{
    command("get all from corpse");
    command("spit");
    command("think how the corpse isn't even worth scavenging for food.");
}

static string
emote_enemy(string str)
{
    object  pl;

    if (!objectp(pl = query_attack()))
        return "";

    command(str+" "+pl->query_real_name());

    return "";
}

void
return_nazgul_ithilien()
{
    command("emote shrieks in frustration as the trees of Fangorn close " +
        "around and block his passage deeper into the forest.");
    command("emote returns to the contested lands of Ithilien.");
    remove_prop(LIVE_O_ENEMY_CLING);
    // move_living("M", "/d/Gondor/ithilien/road/er7", 1, 0);
    remove_object();
}

/*
 * Function name: move_living
 * Description:  redefinition to prevent teleports due to LIVE_O_ENEMY_CLING
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    if (!objectp(query_prop(LIVE_O_ENEMY_CLING)))
        return ::move_living(how, to_dest, dont_follow, no_glance);

    int in_fangorn = wildmatch("/d/Gondor/fangorn/*", file_name(to_dest));

    // DEBUG("to_dest: " + file_name(to_dest) + ", in_fangorn: " +in_fangorn+ ".");

    if(in_fangorn)
    {
        log_file("npcs", "Tried to enter Fangorn following "+
            query_prop(LIVE_O_ENEMY_CLING)->query_name()+ " at " + 
            ctime(time()) + ".\n");

        return_nazgul_ithilien();

        return 0;
    }

    if (!stringp(to_dest))
        to_dest = file_name(to_dest);

    if (member_array(to_dest, ENV(TO)->query_exit_rooms()) > -1)
        return ::move_living(how, to_dest, dont_follow, no_glance);

    log_file("npcs", "MOVE ERROR: Tried to move from "+file_name(ENV(TO))
      + " to " + to_dest + ", following "+query_prop(LIVE_O_ENEMY_CLING)->query_name()
      + " at " + ctime(time()) + ".\n");

    return 7;
}

/* Function name: do_mute()
 * Description: effectively disables play, perform and sing cmds for Minstrels
 * to prevent abuse of their spells against the Nazgul
*/
/*
public int
do_mute(string str)
{
    if (TP->query_guild_name_lay() == "The August Order of Minstrels")
    {
    TP->catch_tell("Music seems impossible in the presence of this dreadful "
        + "being. You stop your song before you can even begin.\n");
    say(QCTNAME(TP)+ " seems momentarily perplexed.\n");
    return 1;
    }
    else {}
}

*/

void
attacked_by(object ob)
{
    object *arr;

    ::attacked_by(ob);
    TELL_ADMIN("[Nazgul attacked by " + ob->query_cap_name() + "("+ob->query_average_stat()+") at " + ctime(time()) + "]");
}


/*
 * Function name:        can_attack_nazgul
 * Description  :        prevent npcs from attacking the black rider
 * Returns      :        1 - can't attack, 0 - can attack
 */
public int
can_attack_nazgul()
{
    if (interactive(this_player()))
    {
        return 0;
    }

    tell_room(environment(this_object()), QCTNAME(this_player())
      + " blanches, and refuses to attack the dread figure!\n",
        this_player());

    write("You know better than to attack such a dread thing as"
      + " this!\n");

    return 1;
} /* can_attack_nazgul */

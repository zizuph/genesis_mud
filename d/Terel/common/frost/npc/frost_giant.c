/* -*- C -*- */
/* Lilith re-implemented June 2008 
 * 
 * Modifications by Petros, May 2009
 *   - Set unarmed to 100. Was originally 0.
 *   - Removed magic and poison resistance. Removed use of MAGIC_I_RES_XX
 *     as it is not supposed to be set. Resistance only checks OBJ_I_RES_XX
 *   - Reduced exp factor from 125 to 115 to account for slowness
 *   - Remove ability to see in dark as it doesn't make sense
 *   - Added cb_tohit check in special_attack and properly return 1 at end
 *     of the attack.
 *   - Added natural 50 AC to all locations
 *   - Make it so they use their weapon as much as possible.
 */
#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;
inherit "/lib/unique";

#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <macros.h>

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
#define MAX_HELP 3
#define KILL_LOG  FROST2_DIR+"log/frost_giant_log"
#define HEAL_FILE FROST2_DIR+"log/heal_log"


int no_help = 0;
int been_attacked = 0;
void call_for_help();

public void
create_monster()
{
    set_name ("gorg");
    add_name ("giant");
    set_pname ("giants");
    set_living_name ("gorg");
    set_short ("frost giant");
    set_pshort ("frost giants");
    set_long ("He is twice the height of the tallest elf you've ever seen, "+
            "and easily as big around as ten plump dwarves. His face is "+
            "vaguely human-looking with exaggeratedly large, coarse features, "+
            "and eyes are as large as a grown man's fist. His skin is very " +
	      "white, as is his very long beard. For some reason he doesn't look " +
	      "cold in his scanty clothes, even though it is freezing here.\n");
    set_adj (({"huge", "frost"}));
    set_race_name ("frost giant");
    set_gender (0);

    /* He is a giant -- big and clumsy */
    set_stats (({350, 100, 350, 150, 150, 180}));

    SET_MAX_HP;
    SET_MAX_MANA;
    set_alignment (0);
    set_skill (SS_DEFENCE,      random(10) + 85);
    set_skill (SS_AWARENESS,    100);
    set_skill (SS_WEP_CLUB, 100);
    set_skill (SS_UNARM_COMBAT, 100); 

    add_prop (LIVE_I_QUICKNESS, -100);
    add_prop (NPC_I_NO_FEAR, 1);
    add_prop (NPC_I_NO_RUN_AWAY, 1);

    // Frost giants have natural resistance to all cold
    add_prop(OBJ_I_RES_COLD,    100);

    // Frost giants are naturally vulnerable to fire
    add_prop(OBJ_I_RES_FIRE,   -100);

    set_act_time (10);
    add_act("wield weapons");
    add_act (({"spit", "grin", "emote swings his club around."}));
    
    set_chat_time (10);
    add_chat ("Beat it! Or I'll stomp the warmth out of you.");
    add_chat ("This club would pulp and splatter your head over a wide area.");
    add_chat ("These boots are made for stompin' heads!");

    set_cchat_time(4);
    add_cchat ("I'll crush your skull with my combat boots.");
    add_cchat ("You puny maggot!  You're going down.\n");
    add_cchat ("I'm going to pound your pin head with me club!");
    add_cchat ("I'll crush you like an insect!");

    set_cact_time(10);
    add_cact("@@call_for_help@@");

    // Set default AC
    set_all_hitloc_unarmed( ({ 50, 50, 50 }) );

    // Make it so they use their weapon as much as possible
    add_prop(NPC_I_NO_UNARMED, 1);
    
    // Reduced factor from 125 to 115. Giant is slow, offsetting his
    // other abilities.
    set_exp_factor(115);
    enable_intro();
    equip_me();
}

/*
 * Function name: equip_actions
 * Description:   Gear me up.
 */
public void
equip_actions()
{
    TO->command ("wear tunic");
    TO->command ("wear boots");    
    TO->command ("wield all");
}


/*
 * Function name: equip_me
 * Description:   Give me some equipment.
 */
public void
equip_me()
{
    object club, ob;
    /* 20% chance of the club being magical. Limit 5 clones. */
    club = clone_unique(FROST2_DIR + "weapon/frost_club", 5,
        FROST2_DIR + "weapon/bar_club", 1, 20);
    club->move(TO);

    ob = clone_object(FROST2_DIR + "armour/tunic");
    ob->move(TO);
    ob = clone_object(FROST2_DIR + "armour/boots");
    ob->move(TO);
   
    equip_actions();

    FIX_EUID;
    MONEY_MAKE_GC (40 + random (20)) -> move(TO);
}

void
call_for_help()
{
     object *enemies, wolf;
 
     enemies = query_my_enemies();
     command("wield all");

     if (query_hp() > query_max_hp()/2) return;
 
     if (no_help >= MAX_HELP) {
         command("whistle loudly");
         no_help++;
         return;
     }
 
     if (no_help == 0) {
         command("whistle loudly");
     } else {
         command("whistle loudly");
     }
     FIX_EUID;
     if (present("g_wolf", environment(this_object())))
         return;
     wolf = clone_object(FROST2_DIR + "npc/bigwolf");
     wolf->move_living("M", ETO);
     tell_room(ETO, QCTNAME(wolf) + " arrives.\n");
     wolf->command("growl");
     wolf->help_the_boss(TO);
     wolf->attack_someone();
     no_help++;
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
int
special_attack(object victim)
{
    object me;
    int    damage, hurt, heal; 
    mixed* hitresult;
    string how;

    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
        return 1;
    }
    
    command("wield all");
    me = this_object();

    hurt = F_PENMOD ((query_stat (SS_STR) * 4), 40 + random (query_skill (SS_WEP_CLUB)));
    
    // Check to see if we can actually hit the person first
    if (query_combat_object()->cb_tohit(-1, 100, victim) <= 0)
    {
        // Allow the round to continue normally when we miss.
        return 0;
    }
    
    hitresult = victim->hit_me (hurt, W_BLUDGEON, TO, -1);

    how = "unharmed";
    
    if (hitresult[0] > 0)
	how = "viciously trod upon";

    if (hitresult[0] > 25)
	how = "trampled underfoot";

    if (hitresult[0] > 50)
	how = "trampled brutally";

    if (hitresult[0] > 75)
	how = "crushed";

    if (hitresult[0] > 100)
	how = "crushed brutally";

    if (hitresult[0] > 300)
	how = "crushed almost to a pulp";

    tell_watcher (QCTNAME (TO) + " stomps on " + QCTNAME (victim) + "!\n",
		 victim, victim);
    tell_watcher (QCTNAME (victim) + " is " + how + ".\n", victim, victim);

    victim->catch_msg (QCTNAME (me) + " stomps on you!\n");
    victim->catch_msg ("You are " + how + ".\n");

    if ((hitresult[0] > 25) && (random (4) == 0))
	TO->command ("say How do you like that, twerp!\n");
    
    call_for_help();

    /* Lets heal me to draw out the fight. 
     * Since it goes off every 5 seconds make it a bit random. 
     */
    if (random(3)) /* fails one chance in three */
    {
        heal = (query_max_hp() / 40);
        me->heal_hp(heal);
        write_file(HEAL_FILE, ctime(time())+" "+ TO->query_name()  +
            "("+ TO->query_average_stat() +")"+
            " healed "+ heal +" points.\n");
     }
        
    return 1;
}

void
do_die(object killer)
{
    int i;
    string str;
    object *enemies;
    
    if (query_hp() > 0) return;
    command("sigh");
    enemies = query_my_enemies();
    str = killer->query_name() + "[" + killer->query_average_stat() + "]";
    for (i=0; i<sizeof(enemies); i++) {
       if (enemies[i] != killer)
           str += ", " + enemies[i]->query_name() +
           "[" + enemies[i]->query_average_stat() + "]";
      }
    write_file(KILL_LOG, str + " (" + ctime(time()) + ")\n");
    
    ::do_die(killer);
}

/* /d/Terel/mountains/ghastly_keep/npc/g_dragon.c
 *
 * Behold, this is Verath the Protective.
 *
 * He's a result of an experiment gone wrong by Sabine Scarletwound,
 * the result is that he doesn't use any magic.
 *
 *  Created by Znagsnuf.
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                 Gorboth
 *  26/04-17                   Included the player kill log            Znagsnuf 
 *  29/04-17                   Fixed a bug with special_attack         Znagsnuf
 *  02/05-17                   Lowered the resistance.                 Znagsnuf
 *  04/05-17                   Moved clone_unique from the room        Znagsnuf
 *  21/12-17                   Commented out debug statements          Lucius
 *  08/05-19                   If attack_time is 0, make dps 1         Shanoga
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";
inherit "/std/act/asking";
inherit "/lib/unique";
inherit "/d/Terel/mountains/ghastly_keep/npc/gkeep_player_kills"; 

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "../npc_stats.h"
#include <time.h>

//#define DEBUG	"znagsnuf"

#define TREASURE  (GKEEP + "gkeep33")
#define TREASURE2 (GKEEP + "gkeep34")

#define hit_locs ({" head", " back", " chest", " right foot",\
                   " left arm", " right arm", " left foot", " torso",\
                   " stomach", " right shoulder", " left shoulder"})

int attack_time, killed_time, total_time;

/*
 * Function name: create_monster()
 * Description  : Constructor, redefine this to configure your monster
 */
void create_creature()
{
    set_race_name("dragon");
    set_living_name("verath");
    set_name("verath");
    add_name("_ghastly_keep_npc");
    add_name("ghastly");

    set_adj("horrendous");
    add_adj("ghastly");

    set_short("horrendous ghastly dragon");

    set_gender(0);

    set_long("Restless cobalt eyes sit high within the creature's "
        + "scaled, horned skull, giving the creature a "
        + "disciplined-looking appearance. Several small central "
        + "horns sit atop its head, just above its short, warped "
        + "ears. Several large fan-like skin and bone structures "
        + "run down the side of each of its jaw lines. Its nose "
        + "is thick and has two short, slitted nostrils and there "
        + "are crystal growths on its chin. Rows of large teeth "
        + "poke out from the side of its mouth giving a slight "
        + "hint at the further terrors inside.\n");

    add_prop(OBJ_S_WIZINFO,"Ages ago Sabine Scarletwound found a "
        + "dragon egg on one of her adventures. She broght it home "
        + "and started conducting experiments on it. This egg "
        + "was tempered with many forms of magic, making it "
        + "resistance to those forms. This dragon is a foul "
        + "creature, but since it was growing up in captivity "
        + "it doesn't know how to use his full power. Therefor "
        + "this dragon only uses melee attacks.\n");


    add_prop(CONT_I_WEIGHT, 320000);      // 320kg
    add_prop(CONT_I_HEIGHT,    300);    // 3meters

    set_stats( ({ 400, 350, 450, 230, 230, 230 }) );

    set_hitloc_unarmed(1, 60, 15, "horned skull");
    set_hitloc_unarmed(2, 60, 10, "right wing");
    set_hitloc_unarmed(3, 60, 10, "left wing");
    set_hitloc_unarmed(4, 60, 45, "body");
    set_hitloc_unarmed(5, 60, 20, "tail");

    /*               hit/pen           %% on usage per c-round */
    set_attack_unarmed(0, 65, 65, W_SLASH,    15, "spiny left claw");
    set_attack_unarmed(1, 65, 65, W_SLASH,    15, "spiny right claw");
    set_attack_unarmed(2, 65, 65, W_BLUDGEON, 20, "massive left wing");
    set_attack_unarmed(3, 65, 65, W_BLUDGEON, 20, "massive right wing");
    set_attack_unarmed(4, 65, 65, W_BLUDGEON, 30, "macabre tail");

    set_skill(SS_DEFENCE,        100);
    set_skill(SS_AWARENESS,       90);
    set_skill(SS_UNARM_COMBAT,   100);
    set_skill(SS_BLIND_COMBAT,   100);

    add_prop(LIVE_I_NEVERKNOWN,    1);
    add_prop(LIVE_I_SEE_DARK,      1);
    add_prop(OBJ_I_RES_MAGIC,     10);
    add_prop(OBJ_I_RES_DEATH,     40);
    add_prop(OBJ_I_RES_POISON,    60);
    add_prop(OBJ_I_RES_FIRE,      40);
    add_prop(NPC_I_NO_FEAR,        1);
    add_prop(NPC_I_NO_RUN_AWAY,    1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    // Special attack.
    set_exp_factor(125);

    set_aggressive(1);
    
    // He looks hideous.
    set_appearance_offset(50);
    set_scar(7);

#ifdef DEBUG
    find_living(DEBUG)->catch_tell("ADM: Verath has returned to "
                                      + "the Ghastly Keep!\n");
#endif
}

/*
* Function name: special_attack()
* Description  : The special attack.
*/
int
special_attack(object enemy)
{
    object me = TO;

    mixed *hitresult;
    string how;
    string ohow;
    string target_loc;
    
    target_loc = one_of_list(hit_locs);

    // We'll make sure the enemy is redefined.
    enemy = me->query_attack();

    me->command("kill " + enemy->query_name());

    if (random(5))
    {
        return 0; 
    }  

    // The special.
    hitresult = enemy->hit_me(800  + random(700), W_SLASH, me, -1);

    // 25% chance to heal.. making the fight a bit longer.
    // Healing for approx 222,5hp each time.
    if (!random(4))
    {
        int heal = (query_max_hp() / 30);
        TO->heal_hp(heal);
    }

    how = " but miss";
    ohow = " but misses";

    if (hitresult[0] >= 0)

    {
        how = " fiercely gash ";
        ohow = " fiercely gashes ";
    }

    if (hitresult[0] > 10)
    {
        how = " wildly slice ";
        ohow = " wildly slices ";
    }

    if (hitresult[0] > 20)
    {
        how = " madly cut ";
        ohow = " madly cuts ";
    }

    if (hitresult[0] == -1)
    {
        me->catch_msg("You slash your claws towards " + QCTNAME(enemy)
            + " several times," + how + ".\n");

        enemy->catch_msg(QCTNAME(me)
            + " slashes " + HIS_HER + " claws in your direction," +
            ohow + ".\n");

        tell_watcher(QCTNAME(me) + " slashes " + HIS_HER + " claws "
            + "at " + QTNAME(enemy) + " several times," + ohow + "."
            + "\n", enemy);

        return 1;
    }

    if (hitresult[0] >= 0)
    {
        me->catch_msg("You slash your claws towards " + QCTNAME(enemy)
            + " several times," +
            how + enemy->query_possessive() + target_loc + ".\n");

        enemy->catch_msg(QCTNAME(me)
            + " slashes " + HIS_HER + " claws towards you," +
            ohow + "your" + target_loc + ".\n");

        tell_watcher(QCTNAME(me) + " slashes " + HIS_HER + " claws at "
            + QTNAME(enemy) + " several " +
            "times," +
            ohow + enemy->query_possessive() + target_loc + ".\n", enemy);

        if (enemy->query_hp() <= 0)
        enemy->do_die(me);

        return 1;
    }
    return 1; /*  Important! Should not have two attacks in a round. */
}

/*
 * Function name: attacked_by
 * Description  : This routine is called when we are attacked.
 * Arguments    : object attacker - the attacker.
 */
void 
attacked_by(object enemy)
{
    // Start a timer when someone attacks.
    attack_time = time();

#ifdef DEBUG
    find_living(DEBUG)->catch_tell(TO->query_name() + ": attacked by " 
                + enemy->query_cap_name()  + "("+enemy->query_average_stat()
                +") at " + ctime(time()) +"\n");
#endif

    ::attacked_by(enemy);
    
}

/*
* Function name: do_die()
* Description  : This is called when the npc is slain.
*
* This will also log who killes him, and the members of the
* team.
*
*/

public void
do_die(object killer)
{

    object *team, g_spyglass;
    int i, size, max_hp, dps_calc;
    string l_file;

    killed_time = time();
    total_time = (killed_time - attack_time);
    max_hp = this_object()->query_max_hp();
    if (total_time == 0) total_time = max_hp;

    if (!objectp(killer) || !living(killer))
        return 0;
    
    // Check if other members in the team.        
    team = killer->query_team_others();

    // See if they are in the same room.
    team = filter(team, &operator(==) (ENV(killer)) @ environment);

    // Find out the size of the team.
    size = sizeof(team);

    dps_calc = (max_hp / total_time);

    // Add timestamp, avg, and names.
    l_file = ctime(time()) + " " + CAP(killer->query_real_name()) +
    " ("+killer->query_average_stat()+ ") killed "+ CAP(TO->query_name()) +

    // Write down the teammembers also.
    (sizeof(team) ? " with assistance of:\n" : ".");
        
        for (i = 0; i < size; i++)
        {
            l_file += CAP(team[i]->query_real_name())+ " ("+
            team[i]->query_average_stat()+ ") ";
        }

    l_file += "\tTotal DPS: " + dps_calc + " ";    
    l_file += "\n";

    // Write a log file.
    write_file(VERATH_KILLED, l_file);

    // Adding treasure.
    TREASURE->add_treasure();
    TREASURE2->add_treasure();

    g_spyglass = clone_unique(GKEEP_OBJ + "g_spyglass", 8,
                                    GKEEP_OBJ + "g_stone");
    g_spyglass->move(TREASURE2);

    ::do_die(killer);
}

        

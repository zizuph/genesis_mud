/* /d/Terel/mountains/ghastly_keep/npc/g_apparition.c
 *
 * An apparition in the ghastly keep
 *
 *  Created by Znagsnuf.
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth
 *  23/04-17                   Updated the long desc.                  Znagsnuf
 *  26/04-17                   Added 33% drop chance to tear           Znagsnuf
 *  26/04-17                   Included the player kill log            Znagsnuf 
 *  26/04-17                   Removing exp_factor as requested        Znagsnuf
 *  26/04-17                   Removed the special attack              Znagsnuf 
 *  29/04-17                   Added a remove timer                    Znagsnuf 
 *  03/07-19                   Increased SS_DEFENCE from 60 to 90         Arman
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";
inherit "/d/Terel/mountains/ghastly_keep/npc/gkeep_player_kills"; 
inherit "/d/Terel/mountains/ghastly_keep/npc/npc_support";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <formulas.h>
#include <time.h>
#include "../npc_stats.h";

public varargs void arm_me();
public void remove_apparition();

/*
 * Function name: create_monster()
 * Description  : Constructor, redefine this to configure your monster
 */
void create_creature()
{
    seteuid(getuid());

    string adj1,adj2;
    adj1 = one_of_list(GKEEP_ADJ1);
    adj2 = one_of_list(GKEEP_ADJ2);

    set_race_name("apparition");
    set_name("undead");
    add_name("_ghastly_keep_npc");
    add_name("ghastly");

    set_adj(adj1);
    set_adj(adj2);
    add_adj("apparition");

    set_short(adj1 + " " + adj2 + " " +TO->query_race_name());

    set_gender(random(2));

    set_long("This " + adj1 + " " + adj2 + " apparition is no more than a "
            + "distortion of the light.\n");

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_HEIGHT, 180);

    default_config_creature(200 + random(50));

    set_hitloc_unarmed(1, 30, 15, "head");
    set_hitloc_unarmed(2, 30, 10, "right arm");
    set_hitloc_unarmed(3, 30, 10, "left arm");
    set_hitloc_unarmed(4, 30, 45, "body");
    set_hitloc_unarmed(5, 30, 20, "legs");

    set_attack_unarmed(0, 40, 40, W_SLASH, 30, "pale white fist");
    set_attack_unarmed(1, 40, 40, W_SLASH, 70, "transparent force");

    set_skill(SS_DEFENCE,         90);
    set_skill(SS_AWARENESS,       90);
    set_skill(SS_UNARM_COMBAT,   100);
    
    add_prop(LIVE_I_NEVERKNOWN,    1);
    add_prop(LIVE_I_SEE_DARK,      1);
    add_prop(LIVE_I_UNDEAD,        1);
    add_prop(LIVE_I_NO_CORPSE,     1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_aggressive(1);

    set_appearance_offset(RND_APPERANCE);

    // Give it some items.
    arm_me();

    // It will fade away in time (8mins)
    set_alarm(480.0, 0.0, &remove_apparition());
}

/*
 * Function name: arm_me()
 * Description  : Arms the NPC
 */

void
arm_me()
{
    object tear, veil;
    seteuid(getuid(TO));
    
    if(!random(3))
    {
        tear = clone_object(GKEEP_OBJ + "g_tear");
        tear->move(this_object());
    }

    veil = clone_object(GKEEP_OBJ + "g_veil");
    veil->move(TO);

    command("wear all");

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
 *//*
int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me;
    int hurt;

    me = TO;

    if(random(11) > 7) 
    {
        // Make sure that we can actually attack the target
        if (enemy->query_not_attack_me(me, -1))
        {
            return 1; // round is ended so return 1.
        }
        
        hurt = F_PENMOD(45 +(random(10)), 45 + (random(20)));

        hitresult = enemy->hit_me(hurt, MAGIC_DT, me, -1);

        how = "unharmed";
        if (hitresult[0] > 0)
            how = "overcome with pain";
        if (hitresult[0] > 20)
            how = "your body becoming numb";
        if (hitresult[0] > 50)
            how = "your mind starting to crumble";
        if (hitresult[0] > 100)
            how = "your mind becoming pulverized";

        tell_watcher(QCTNAME(me) + " stares at " + QTNAME(enemy) + ".\n", 
                     enemy);
        enemy->catch_tell(query_The_name(enemy) + " penetrates your mind!\n" +
            "You feel " + how + "!\n");

        if (enemy->query_hp() <= 0)
            enemy->do_die(me);

        return 1;
    }

    return 0;
}
*/
/*
* Function name: do_die()
* Description  : This is called when the npc is slain.
*/

public void
do_die(object killer)
{
    int k;
    int spawn = random(10);
    int rnd = random(RND_DROP);
    object apparition, stone;
    string l_file;

    // With each kill they have a bigger chance to enter the lower levels.
    if (interactive(killer))
    {
        register_gkeep_kill(killer);
    }

    // All the mobs in Ghastly Keep will have a chance to drop a green stone
    // this stone is used for the summoning ritual.
    // The reason for adding this in the death sequence is so players would
    // not be able to 'snoop' them out.
    if(rnd < DROP_CHANCE)
    {
        stone = clone_object(GKEEP_OBJ + "g_stone");
        stone->move(TO);
        tell_room(ETO, QCTNAME(TO)+ " drops " +LANG_ASHORT(stone) + ".\n", TO);

        l_file = TIME2FORMAT(time(), "dd/mm/yyyy");

        l_file += "\tStone collected by:\t" 
                  + CAP(killer->query_real_name() + "\n");

        // Write a log file.
         write_file(STONE_LOG, l_file);
    }

    // 50% chance to spawn an apparition from the Netherworld.
    if(spawn > 5)
    {
        apparition = clone_object(GKEEP_NPC + "g_apparition");
        apparition->move(ETO);
        tell_room(ETO, "The stagnant air shifts as the "
                        + apparition->short() + " appears.\n", TO);
    }

    ::do_die(killer);
}

public void
remove_apparition()
{
    if(!TO->query_attack())
    {
        tell_room(ETO, "The " + TO->query_short() + " fades out of view.\n", TO);
        TO->remove_object();
    }
}

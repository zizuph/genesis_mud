/* /d/Terel/mountains/ghastly_keep/npc/g_guardian.c
 *
 * A guardian in the ghastly keep
 *
 *  Created by Znagsnuf.
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth
 *  23/04-17                   Updated the long desc.                  Znagsnuf   
 *  26/04-17                   Added 33% drop chance to tear           Znagsnuf
 *  26/04-17                   Included the player kill log            Znagsnuf
 *  05/05-17                   Lowered resistance                      Znagsnuf 
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
#include <time.h>
#include <filter_funs.h>
#include <language.h>
#include "../npc_stats.h";

public varargs void  arm_me();

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

    set_race_name("guardian");
    set_name("undead");
    add_name("_ghastly_keep_npc");
    add_name("ghastly");

    set_adj(adj1);
    set_adj(adj2);
    add_adj("guardian");

    set_short(adj1 + " " + adj2 + " " +TO->query_race_name());

    set_gender(random(2));

    set_long("This " +adj1+ " "+adj2+ " creature has black papery looking "
           + "skin. " + CAP(HIS_HER) + " dead caved in eyes are completely "
           + "black, with small red pupils. Saliva drooling with silent "
           + "precision from " + HIS_HER + " pendulous lip. An open "
           + "dislocated jaw showing " + HIS_HER + " torn tongue and "
           + "blood-stained, razor sharp, savage teeth.\n");

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_HEIGHT, 180);
    
    set_stats( ({ 200, 190, 200, 170, 170, 200 }) );

    set_hitloc_unarmed(1, 30, 15, "head");
    set_hitloc_unarmed(2, 30, 10, "right arm");
    set_hitloc_unarmed(3, 30, 10, "left arm");
    set_hitloc_unarmed(4, 30, 45, "body");
    set_hitloc_unarmed(5, 30, 20, "legs");

    set_attack_unarmed(0, 40, 40, W_SLASH, 20, "left claw");
    set_attack_unarmed(1, 40, 40, W_SLASH, 20, "right claw");
    set_attack_unarmed(2, 40, 40, W_SLASH, 60, "stinging teeth");

    set_skill(SS_DEFENCE,         90);
    set_skill(SS_AWARENESS,       90);
    set_skill(SS_UNARM_COMBAT,    80);

    add_prop(LIVE_I_NEVERKNOWN,    1);
    add_prop(LIVE_I_UNDEAD,        1);
    add_prop(LIVE_I_NO_CORPSE,     1);
    add_prop(LIVE_I_SEE_DARK,      1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_aggressive(1);
    set_appearance_offset(RND_APPERANCE);

    // Give it some items.
    arm_me();
}

/*
 * Function name: arm_me()
 * Description  : Arms the NPC
 */

void
arm_me()
{
    object tear;
    seteuid(getuid(this_object()));

    if(!random(3))
    {
        tear = clone_object(GKEEP_OBJ + "g_tear");
        tear->move(this_object());
    }

    command("wear all");

}

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
        tell_room(ETO, QCTNAME(TO)+ " drops " +LANG_ASHORT(stone)+ ".\n", TO);

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
        tell_room(ETO, "The stagnant air shifts as "
          + LANG_ADDART(apparition->short()) + " appears.\n", TO);
    }

    ::do_die(killer);
}

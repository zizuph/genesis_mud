/*  /d/Terel/mountains/ghastly_keep/npc/g_vampire.c
 *
 *  A Vampire in the ghastly keep
 *
 *  This Vampire can have any of the legendary items from Terel.
 *  This should be a rather easy, and rewarding mob, considering
 *  the time taking to summon it.
 *
 *  The special attack is borrowed from 
 *  /d/Terel/common/moor/tcaves/npc/troll.c
 *
 *  Created by Znagsnuf.
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17             Language tweak complete                        Gorboth
 *  23/04-17             Alter how the LEG_ITEMS clones               Cotillion  
 *  26/04-17             Included the player kill log                  Znagsnuf 
 *  28/04-17             Added an item to alt. drop                    Znagsnuf
 *  05/05-17                   Lowered resistance                      Znagsnuf
 *  06/05-17                   Fixed a typo                            Znagsnuf  
 *  21/12-17                   Commented out debug statements          Lucius
 *  6 August 2021        Reduced clone_unique of LEG_ITEMS 7 to 3      Arman
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";
inherit "/lib/unique";
inherit "/d/Terel/mountains/ghastly_keep/npc/gkeep_player_kills"; 

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include "../npc_stats.h";

#define DEBUG	"arman"

#define LEG_ITEM ( ({ "/d/Terel/calathin/houses/weapon/isabre", \
                      "/d/Terel/calathin/houses/weapon/abbasi", \
                      "/d/Terel/common/frost/weapon/frost_club", \
                      "/d/Terel/unique/furrobe", \
                      "/d/Terel/unique/sword_w_darkness", \
                      "/d/Terel/last/armour/trev_bracers", \
                      "/d/Terel/unique/ew_sword", \
                      "/d/Terel/last/armour/trev_boots", \
                      "/d/Terel/mountains/redlair/weapon/dtooth" \
                 }) )

public varargs void arm_me();
string location = file_name(environment(this_player()));

/*
 * Function name: create_monster()
 * Description  : Constructor, redefine this to configure your monster
 */
void create_creature()
{
    seteuid(getuid());

    set_race_name("vampire");
    set_name("Vampire_of_Ghastly");
    add_name("_ghastly_keep_npc");
    add_name("undead");

    set_adj("pale");
    set_adj("dark-eyed");
    add_adj("vampire");

    set_short("pale dark-eyed vampire");

    set_gender(random(2));

    set_long("This " + TO->query_short() + " has skin paler than the "
            + "moon, and " + HIS_HER + " facial features are flawless. " 
            + CAP(HIS_HER) + " dark eyes match the night sky perfectly.\n");

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_HEIGHT, 180);

    default_config_creature(236 + random(58));

    set_hitloc_unarmed(1, 40, 15, "pale head");
    set_hitloc_unarmed(2, 40, 10, "pale right arm");
    set_hitloc_unarmed(3, 40, 10, "pale left arm");
    set_hitloc_unarmed(4, 40, 45, "transparent body");
    set_hitloc_unarmed(5, 40, 20, "pale legs");

    set_attack_unarmed(0, 60, 60, W_SLASH,  30, "pale white fist");
    set_attack_unarmed(1, 60, 60, W_SLASH,  30, "pale right claw");
    set_attack_unarmed(2, 60, 60, MAGIC_DT, 40, "transparent force");

    set_skill(SS_DEFENCE,       80);
    set_skill(SS_PARRY,         80);
    set_skill(SS_AWARENESS,    100);
    set_skill(SS_UNARM_COMBAT, 100);
    add_prop(LIVE_I_QUICKNESS, 150);
    add_prop(OBJ_I_RES_MAGIC,   10);
    add_prop(OBJ_I_RES_DEATH,   20);
    
    add_prop(LIVE_I_NEVERKNOWN,    1);
    add_prop(LIVE_I_SEE_DARK,      1);
    add_prop(LIVE_I_UNDEAD,        1);
    add_prop(LIVE_I_NO_CORPSE,     1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_aggressive(1);
    set_appearance_offset(RND_APPERANCE);
    set_intoxicated(TO->query_prop("_live_i_max_intox"));
    
    // Will be time consuming to summon, but rewarding.
    set_exp_factor(200);

#ifdef DEBUG
    find_living(DEBUG)->catch_tell("ADM: Vampire has been summoned in "
                                      + "the Ghastly Keep!\nLocation: "
                                      + location +"\n");;
#endif
}

/*
 * Function name: arm_me()
 * Description  : Arms the NPC
 */

void
arm_me()
{
    object tear, pouch;

    seteuid(getuid(TO));

    tear = clone_object(GKEEP_OBJ + "g_tear");
    tear->move(TO);
    pouch = clone_object(GKEEP_OBJ + "g_vamp_pouch");
    pouch->move(TO);
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
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me;
    int hurt;

    me = TO;

    if(random(11) > 6) 
    {
        // Make sure that we can actually attack the target
        if (enemy->query_not_attack_me(me, -1))
        {
            return 1; // round is ended so return 1.
        }
        
        hurt = F_PENMOD(100 +(random(50)), 100 + (random(50)));

        hitresult = enemy->hit_me(hurt, MAGIC_DT, me, -1);

        how = "unharmed";
        if (hitresult[0] > 0)
            how = "overcome with pain";
        if (hitresult[0] > 20)
            how = "your body getting numb";
        if (hitresult[0] > 50)
            how = "your mind crumbling";
        if (hitresult[0] > 100)
            how = "your mind being pulverized";

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

/*
* Function name: do_die()
* Description  : This is called when the npc is slain.
*                This Vampire will drop one random good item
*                from the Terel drop table.
*                Added that in the do_die function to prevent
*                players from 'snoop' it.
*/

public void
do_die(object killer)
{

    object *team;
    int i, size, count;
    string l_file, *item_options = LEG_ITEM;
    mixed item_path = 0;
    object item;

    while (!item && sizeof(item_options))
    {
        string file = one_of_list(item_options);
        item_options -= ({ file });
        item = clone_unique(file, 3);
    }

    if (item)
    {
        tell_room(ETO, QCTNAME(TO) + " drops " + LANG_ASHORT(item) + ".\n", TO);
        item->move(ETO);
    }

    if (!item)
    {
        item = clone_object("/d/Terel/dabaay/weapon/dshort");
        tell_room(ETO, QCTNAME(TO) + " drops " + LANG_ASHORT(item) + ".\n", TO);
        item->move(ETO);
    }

    if (!objectp(killer) || !living(killer))
        return 0;
    
    // Check if other members in the team.        
    team = killer->query_team_others();

    // See if they are in the same room.
    team = filter(team, &operator(==) (ENV(killer)) @ environment);

    // Find out the size of the team.
    size = sizeof(team);

    // Add timestamp, avg, and names.
    l_file = ctime(time()) + " " + CAP(killer->query_real_name()) +
    " (" + killer->query_average_stat() + ") killed "+ CAP(TO->query_name()) +

    // Write down the teammembers also.
    (sizeof(team) ? " with assistance of:\n" : ".");
        
        for (i = 0; i < size; i++)
        {
            l_file += CAP(team[i]->query_real_name()) + " (" +
            team[i]->query_average_stat() + ")     ";
        }
        
    l_file += "\n\tItem: " + LANG_ASHORT(item) + ".\n";

    // Write a log file.
    write_file(VAMP_KILLED, l_file);

    ::do_die(killer);
}


void
attacked_by(object ob)
{
    ::attacked_by(ob);
#ifdef DEBUG
    find_living(DEBUG)->catch_tell(TO->query_name() + ": attacked by " 
                + ob->query_cap_name()  + "("+ob->query_average_stat()
                +") at " + ctime(time()) +"\n");
#endif
}                

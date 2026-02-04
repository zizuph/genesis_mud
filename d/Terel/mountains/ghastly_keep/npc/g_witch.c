/*  /d/Terel/moutains/ghastly_keep/npc/g_witch.c
 *
 *  Behold Sabine Scarletwound.
 *
 *  Witch in the labaratory.
 *
 *  Special brew, impossible to resist.
 *
 *  Created by Znagsnuf.
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth
 *  26/04-17                   Included the player kill log            Znagsnuf
 *  26/04-17                   Fixed a bug with enemy->do_die(me);     Znagsnuf
 *  26/04-17                   Added DPS to the kill_log               Znagsnuf 
 *  02/05-17                   Lowered the resistance.                 Znagsnuf
 *  05/05-17                   Fixed a typo                            Znagsnuf 
 *  21/12-17                   Commented out debug statements          Lucius
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";
inherit "/std/act/asking";
inherit "/lib/unique";
inherit "/d/Terel/mountains/ghastly_keep/npc/gkeep_player_kills";    

//#define DEBUG	"znagsnuf"

#define hit_locs ({" head", " back", " chest", " right foot",\
                   " left arm", " right arm", " left foot", " torso",\
                   " stomach", " right shoulder", " left shoulder"})

#include "defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include "../npc_stats.h";
#include <time.h>

int attack_time, killed_time, total_time;
public void add_introduced(string name);
public void react_to_intro(object tp);
public varargs void  arm_me();
/*
 * Function name: create_monster()
 * Description  : Constructor, redefine this to configure your monster
 */
void create_creature()
{
    set_race_name("witch");
    set_living_name("sabine");
    set_title("Scarletwound, Carver of the Empty Void");
    set_name("sabine");
    add_name("_ghastly_keep_npc");
    add_name("ghastly");

    set_adj("deformed");
    add_adj("hunch-backed");

    set_short("deformed hunch-backed witch");

    set_gender(G_FEMALE);

    set_long("Her skin is as gnarled as a crooked tree, and her "
            + "hair contains just as many bugs. Her lips are large "
            + "and leathery, her nose a bumpy collection of warts, "
            + "and her eyes narrowed in such a squint that it "
            + "is impossible to tell their colour. Perhaps once "
            + "rising to almost six feet tall, quite a giant amongst the "
            + "young witches, she now is in the tidewater of "
            + "her eighth decade and has a pronounced hunch-back. "
            + "But whilst her body decayed, her mind remained sharp.\n"
            + "She has narrowed squinty eyes.\n"
            + "Her hair is curly waist-length and full of bugs.\n");

    add_prop(OBJ_S_WIZINFO,"Let me present Sabine Scarletwound, a "
        + "cunning and deceitful witch, once a respected habitant "
        + "of the Ghastly Keep, until she hatched the dragon egg "
        + "containing Verath the Protective. Sabine has now "
        + "assembled an army, as a buffer against retribution from the "
        + "former owners of the Castle, or maybe as a weapon to keep "
        + "Verath at bay, who knows? Only time will tell.\n");

    add_prop(CONT_I_WEIGHT, 61000); //61 kg
    add_prop(CONT_I_HEIGHT, 162);   //162cm

    set_stats( ({ 200, 300, 350, 250, 250, 270 }) );

    set_hitloc_unarmed(1, 40, 15, "head");
    set_hitloc_unarmed(2, 40, 10, "right arm");
    set_hitloc_unarmed(3, 40, 10, "left arm");
    set_hitloc_unarmed(4, 40, 45, "body");
    set_hitloc_unarmed(5, 40, 20, "legs");

    set_attack_unarmed(1, 60, 60, W_SLASH, 20, "crooked left fist");
    set_attack_unarmed(2, 60, 60, W_SLASH, 20, "crooked right fist");
    set_attack_unarmed(3, 60, 60, W_SLASH, 60, "long razor-sharp nails");

    set_skill(SS_DEFENCE,       70);
    set_skill(SS_AWARENESS,     90);
    set_skill(SS_UNARM_COMBAT, 100);

    add_prop(OBJ_I_RES_DEATH,   40);
    add_prop(OBJ_I_RES_POISON,  20);
    add_prop(OBJ_I_RES_FIRE,    20);
    add_prop(LIVE_I_QUICKNESS, 200);
    add_prop(LIVE_I_NEVERKNOWN,  1);
    add_prop(LIVE_I_SEE_DARK,    1);
    
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    add_leftover(GKEEP_OBJ + "g_wart", "wart", 1,"", 1, 1);

    set_act_time(15);

    add_act("emote moves uncomfortably close to you.");
    add_act("emote wanders restlessly around the room, looking for "
           + "something.");
    add_act("emote grins, flashing her yellow and black teeth.");
    add_act("say I thought you might have as well have forsaken me.");

    set_default_answer(VBFC_ME("default_answer"));

    set_aggressive(0);

    //She looks repulsive.
    set_appearance_offset(40);
    set_scar(3);

    // Special attack.
    set_exp_factor(125);
    
    // Give it some items.
    arm_me();

#ifdef DEBUG
    find_living(DEBUG)->catch_tell("ADM: Sabine has returned to "
                                      + "the Ghastly Keep!\n");
#endif
}

/*
 * Function name: query_humanoid()
 * Description  : Returns the correct humanoid status since this was
 *                created as a creature.
 * Returns      : int 1 - truly humanoid
 */
int
query_humanoid()
{
    return 1;
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
 * Function name: arm_me()
 * Description  : Arms the NPC
 */

void
arm_me()
{
    object tear, s_book, gloves, hat;
    seteuid(getuid(TO));

    gloves = clone_object(GKEEP_ARM + "gkeep_gloves");
    gloves->move(TO);

    s_book = clone_unique(GKEEP_ARM + "gkeep_spellbook", 7,
                          GKEEP_OBJ + "g_tear");
    s_book->move(TO);

    hat = clone_unique(GKEEP_ARM + "gkeep_wizhat", 7,
                       GKEEP_OBJ + "g_veil");
    hat->move(TO);

    MONEY_MAKE_PC(10+random(4))->move(TO);
    MONEY_MAKE_GC(50)->move(TO);

    command("wear all");
    command("hold spellbook");
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
        return 0;  /* Continue with the normal attacks */
    }

    // The special.
    hitresult = enemy->hit_me(500 + random(700), MAGIC_DT, me, -1);

    how = " but miss";
    ohow = " but misses";

    // 25% chance to heal.. making the fight a bit longer.
    // Healing for approx 230hp each time.
    if (!random(4))
    {
        int heal = (query_max_hp() / 20);
        TO->heal_hp(heal);
    }

    if (hitresult[0] >= 0)

    {
        how = " it fiercely explodes across ";
        ohow = " it fiercely explodes across ";
    }

    if (hitresult[0] > 10)
    {
        how = " it brutally explodes across ";
        ohow = " it brutally explodes across ";
    }

    if (hitresult[0] > 20)
    {
        how = " it violently explodes across ";
        ohow = " it violently explodes across ";
    }

    if (hitresult[0] == -1)
    {
        me->catch_msg("You throw a potion towards " + QTNAME(enemy)
            + " with both arms," + how + ".\n");

        enemy->catch_msg(QCTNAME(me)
            + " throws a potion towards you," +
            ohow + ".\n");

        tell_watcher(QCTNAME(me) + " throws a potion at " + QTNAME(enemy) +
            " with both arms," + ohow + ".\n", enemy);

        return 1;
    }

    if (hitresult[0] >= 0)
    {
        me->catch_msg("You throw a potion towards " + QTNAME(enemy)
            + " with both arms," +
            how + enemy->query_possessive() + target_loc + ".\n");

        enemy->catch_msg(QCTNAME(me)
            + " throws a potion at you with both arms," +
            ohow + "your" + target_loc + ".\n");

        tell_watcher(QCTNAME(me) + " throws a potion at "
            + QTNAME(enemy) + " with " +
            "both arms," +
            ohow + enemy->query_possessive() + target_loc + ".\n", enemy);

        if (enemy->query_hp() <= 0)
            enemy->do_die(me);

        return 1;
    }

    return 0; 
}


/*
 * Function name:        react_to_intro
 * Description  :        respond to introduction
 * Arguments    :        object tp -- the person who intro'd
 */
public void
react_to_intro(object tp)
{
    command("introduce myself to "+ tp->query_real_name());   
} /* react_to_intro */

/*
 * Function name:       add_introduced
 * Description  :       Add the name of a living who has introduced to us
 * Arguments    :       string name -- name of the introduced living
 */
public void
add_introduced(string name)
{
        set_alarm(1.5, 0.0, &react_to_intro(TP));
} /* add_introduced */


/*
 * Function name: default_answer
 * Description  : reply to questions about a task
*/

public string
default_answer()
{
    switch (random(3))
    {
    case 0:
        command("sob");
        command("say You know nothing!");
        break;
    case 1:
        command("laugh eer");
        command("say So why not join the dark side, my pretty? "
               + "Why choose to be alone in your madness?");
        break;
    case 2:
        command("shrug");
        command("say Come, let me show you the pleasure of cruelty, "
               + "the joy of power.");
        break;
    }
    return "";
} /* default_answer */

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

    object *team;
    int i, size, max_hp, dps_calc;
    string l_file;

    killed_time = time();
    total_time = (killed_time - attack_time);
    max_hp = this_object()->query_max_hp();

    if (!objectp(killer) || !living(killer))
        return 0;
    
    // Check if other members in the team.        
    team = killer->query_team_others();

    // See if they are in the same room.
    team = filter(team, &operator(==) (ENV(killer)) @ environment);

    // Find out the size of the team.
    size = sizeof(team);

    dps_calc = (max_hp / (total_time + 1));

    // Add timestamp, avg, and names.
    l_file = ctime(time()) + " " + CAP(killer->query_real_name())+
    " (" + killer->query_average_stat() + ") killed " + CAP(TO->query_name()) +

    // Write down the teammembers also.
    (sizeof(team) ? " with assistance of:\n" : ".");
        
        for (i = 0; i < size; i++)
        {
            l_file += CAP(team[i]->query_real_name())+ " ("+
            team[i]->query_average_stat()+ ")     ";
        }

    l_file += "\tTotal DPS: " + dps_calc + " ";    
    l_file += "\n";

    // Write a log file.
    write_file(SABINE_KILLED, l_file);

    // With her dying breath Sabine mumbles something to the 'killer'
    // Only the killer might find the potion

    killer->catch_msg(QCTNAME(TO) + " whispers in your ear with her final breath: "
                                   + "Search and you shall find!\n");

    tell_room(ETO, QCTNAME(TO)+ " whispers something "
                              + "to " + QTNAME(killer) + " with her dying "
                              + "breath.\n", ({TO, killer}));

    // Add the prop.
    killer->add_prop("_gkeep_can_find_potion", 1);

    ::do_die(killer);
}        

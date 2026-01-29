/*
 * The true form of Thanar.
 * MADE BY: Mirandus
 * DATE: March 13 2018
 *
 *
 * This is the Deity Thanar. He has a variety of special attacks that
 * are the same as those of the Priests within the Cathedral. They are
 * modified to be from him. As he grants them, so to does he use them.
 *
 * The on interesting feature about this NPC is that at 1/2 HP he will
 * clone a shadow version of the player attacking him that will join
 * the Fray. This makes the battle significantly harder and worthy of
 * fighting a God.
 *
 */

inherit "/d/Kalad/std/monster";
/* Mirandus: We use this to make him team properly */
inherit "/d/Kalad/std/group_cluster";
/* Mirandus: Use clone unique for any speciality items he drops */
inherit "/lib/unique";
/* Mirandus: Add a kill logger */
inherit "/d/Kalad/common/kill_logger";

#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
#include <stdproperties.h>
#include "../local.h"

#define T_I_SUMMON_THANAR "_i_summon_thanar_"
#define T_GO_SUMMON_THANAR "_go_summon_thanar_"
#define I_DID_THE_SUMMON "_i_did_the_summon_"

/* Prototypes */
public void         get_me_soul();
public void         create_monster();
public void         create_shadow();
public void         summon_guards();
public int          special_attack(object enemy);
public int          attack_object(object ob);

/*Defines for special objects*/
#define MANA_SHADOW          (GENSPECIALS + "shadows/mana_shadow")
#define SPELL_SOUL           (SPELLS + "deity_spell_soul")
#define SPELL_MANAGER_SOUL   (GENSPECIALS + "souls/spell_manager_soul")
#define SWORD                (WEP + "thanar_sword")

/* Global variables */
int soul_id;
int shadow_summon = 0;
int guard_summon = 0;

/*
 * Function name:        create_monster
 * Description  :        Creates the npc
 */
public void
create_monster()
{
    
    int i;
    
    ::create_monster();
    set_name("thanar");
    add_name("deity");
    add_name("demon");
    add_name("_thanar_npc");
    set_living_name("thanar");
    set_race_name("demonic deity");
    set_adj("omnipotent");
    add_adj("immortal");
    set_long("The true form of the Deity Thanar stands towering before you. "
    +"The rippled muscles of his human-like form bulge in anticipation of "
    +"battle. His eyes are deep and devoid of any emotion or compassion. "
    +"His body is like that of a human but there are reptilian features to "
    +"his face and eyes. There is extreme malice in the being of Thanar and "
    +"a desire to destroy all who would stand against him.\n");
   
    for(i = 0; i < 6; i++)
        set_base_stat(i, 180 + random(40));
    
    set_all_hitloc_unarmed(75);
            
    set_alignment(-1200);
    set_knight_prestige(1200);
    set_aggressive(1);
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_WEP_KNIFE,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_AWARENESS,100);
    set_skill(SS_SPELLCRAFT,100);
    set_skill(SS_FORM_ENCHANTMENT, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_FORM_TRANSMUTATION, 100);
    set_skill(SS_ELEMENT_DEATH, 100);
    set_skill(SS_ELEMENT_LIFE, 100);
    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_ELEMENT_AIR, 100);
    set_skill(SS_ELEMENT_EARTH, 100);
  
    set_cact_time(1);
    add_cact("say Heretic. You shall be struck down like a gnat!");
    add_cact("I am the lord Thanar. You cannot hope to defeat me.");
    add_cact("cackle maniac");
    add_cact("close door");
    add_cact("say Know that you face the greatest of gods!");
    add_cact("emote laughs at you in complete and utter contempt.");
    add_cact("laugh dem");
    add_cact("smirk");
    
    set_title("the Greater Power of Kalad, Creator of the Thanarians "
    +"and Patron Deity of the Holy Order of Thanar");
    
    add_speak("I will burn this world to the ground.\n");
    set_default_answer("You dare speak to me!\n");
    add_ask(({"job","quest","help","task"}),"The only quest I have to "
    +"offer you is to die.\n");
        
    add_prop(NPC_M_NO_ACCEPT_GIVE,1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_ATTACK_THIEF, 1);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_SEE_INVIS, 99);
    trig_new("%w 'attacks' %s","react_attack");
    
    /* Mirandus Add the spellcasting soul and shadow */   
    clone_object(MANA_SHADOW)->shadow_me(TO);
    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
    seteuid(getuid());
    
    /* Mirandus Add him to the team */
    set_prospective_cluster(({"_thanar_npc"}));
    
    /* Zignur XP Adjustment */
    set_exp_factor(150);  

    set_alarm(1.0,0.0,"arm_me");

}/* create_thanar_living */

/*
 * Function name: arm_me()
 * Description  : Arms the NPC
 */
void
arm_me()
{
    seteuid(getuid(this_object()));
    equip(({
        SWORD,
    }));   

}/* arm_me */

/*
* Function name: get_me_soul
* Description  : Handles the spellsoul for the npc
*/
public void
get_me_soul()
{
    add_cmdsoul(SPELL_SOUL);
    add_cmdsoul(SPELL_MANAGER_SOUL);
    add_cmdsoul(MANA_SHADOW);
    update_hooks(); 
    remove_alarm(soul_id);
}

/*
 * Function name:        react_intro
 * Description  :        the npc reacts to introductions
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        return;
    }

    command("say Now I know the gnat I will slay.");
    command("introduce me to "+this_player()->query_real_name());
    command("close door");
    return;
    
}/*react_intro*/

/*
 * Function name: add_introduced
 * Description  : Called automatically from the mudlib whenever a person
 *                introduces himself to this NPC.
 * Arguments    : string name - the name of the person being introduced.
 */
 
void
add_introduced(string name)
{
    set_alarm(1.0, 0.0, &react_intro(name));
    
}/*add_introduced*/

/*
 * Function name: special_attack
 * Description  : Handles the spell rotation for the npc
 * Arguments    : object enemy
 * Returns      : 1 or 0 
 */
int
special_attack(object enemy)
{
    int i;
    object *enemies = ({});
    object *enemy_list = ({}) ;
    object kill_enemy;
    object ob;
    
    kill_enemy = this_object()->query_attack();
    
    /* We want to always attack the enemy with the lowest health */   
    foreach(object member: this_object()->query_team_others())
    {
        if (!pointerp(enemies = filter(member->query_enemy(-1),
        &operator(<)(,0) @ &member_array(,enemy_list))))
        enemies += ({});
    
        enemy_list += enemies;
    }

    foreach(object enemy: enemy_list)
    {
        if (enemy->query_hp() < kill_enemy->query_hp())
        {
            kill_enemy = enemy;
        }    
    }
    
    if (shadow_summon == 0 && query_hp() <= (query_max_hp() / 2))
    {
        create_shadow();
        return 1;
    }
    
    if (guard_summon == 0 && query_hp() <= (query_max_hp() / 3))
    {
        summon_guards();
        return 1;
    }
    /* See if we want to cast a blind or stun*/
    if(!random(7))
    {
        if(!random(2))
        {
            command("cast tblind " + kill_enemy->query_real_name()); 
            return 1;           
        }
        else
        {
            command("cast tstun " + kill_enemy->query_real_name()); 
            return 1;   
        }
    }
       
    /* See if we want to cast damage or drain */
    if(!random(2))
    {
        command("cast tdamage " + kill_enemy->query_real_name()); 
        return 1;
    }
   
    // Cast the Drain or if they are undead, the Damage.
    if (kill_enemy->query_prop(LIVE_I_UNDEAD))
       {
         command("cast tdamage " + kill_enemy->query_real_name()); 
         return 1;
       }
       command("cast tdrain " + kill_enemy->query_real_name()); 
       return 1;     

}/* special_attack */

/*
* Function name: create_shadow
* Description  : When Thanar is at 1/2 health he summons a shadow version
*                of the biggest player to assist him.
* Arguments    : object enemy - The enemy of the NPC as set in the combat file
* Returns      : int 1 - tells the combat file that a special was cast
*/
public void
create_shadow()
{
    
    string *adj, race;
    int stat0, stat1, stat2, stat3, stat4, stat5;   
    object shadow, enemy;
    enemy = this_object()->query_attack();
    race = "shadowy " + enemy->query_race_name();
    
    seteuid(getuid(TO));
    
    stat0 = enemy->query_stat(0) + random(20);
    stat1 = enemy->query_stat(1) + random(20);
    stat2 = enemy->query_stat(2) + random(20);
    stat3 = enemy->query_stat(3) + random(20);
    stat4 = enemy->query_stat(4) + random(20);
    stat5 = enemy->query_stat(5) + random(20);
    adj = enemy->query_adj(1);
    
    

    enemy->catch_msg(QCTNAME(TO) + " stares directly at you drawing from " +
        "the shadow realm. A shadow version of yourself arises to join the "
        +"fray.\n");
    this_object()->tell_watcher(QCTNAME(this_object()) + " stares directly "
        +"at "+QCTNAME(enemy) + ". A shadow version of "+QCTNAME(enemy)+
        " arises to join the fray.\n", enemy, ({ this_object(), enemy }));

    
    shadow = clone_object(LIV + "guardian");
    shadow->set_adj(adj[0]);
    shadow->add_adj(adj[1]);
    shadow->set_race_name(race);
    shadow->set_gender(enemy->query_gender());
    shadow->set_long(enemy->long(shadow));
    shadow->set_name("shadowy " + enemy->query_race_name());
    shadow->add_name(enemy->query_race_name());
    shadow->add_name("_thanar_shadow");
    shadow->set_stats(({stat0,stat1,stat2,stat3,stat4,stat5}));
    shadow->heal_hp(10000);
    shadow->move_living("M", E(TO));
    shadow->command("$kill " + OB_NAME(enemy));
    
    shadow_summon = 1;
    return;
    
}

/*
* Function name: summon_guards
* Description  : When Thanar is at 1/3 health he summons guards to assist
*                him in combat.
* Arguments    : object enemy - The enemy of the NPC as set in the combat file
* Returns      : int 1 - tells the combat file that a special was cast
*/
public void
summon_guards()
{
    object troops, enemy;
    int i;
	enemy = this_object()->query_attack();
    
    seteuid(getuid(TO));
    command("emote erupts in black flames and cries out: Minions of the "
    +"underworld, heed my call. Come to you Lord and God and assist me in "
    +"triumphing over these Gnats!");
    for (i = 0; i < 3; i++)
    {
        troops = clone_object(LIV + "thanar_serpent");
        troops->move_living("M", E(TO));
        troops->command("$kill " + OB_NAME(enemy));
    }
    enemy->attack_object(troops);
    command("say Now you shall feel the wraith of my Serpents!");
    guard_summon = 1;
    return;
}
    

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
public int
attack_object(object ob)
{
    ::attack_object(ob);
    map(query_team_others(), &->notify_attack_on_team(this_object(), ob));
} /* attack_object */

/* Function:         query_my_enemies() : written by Mortricia
 * What's it do:     Creates an array of enemies to be used for randomizing
 */
 public varargs object *
 query_my_enemies(int how_to_sort = 0)
 {
     int i, j, swap = 0;
     object foo, *all, *enemies = ({ });
     all = all_inventory(environment(TO)) - ({ TO });
     for (i=0; i<sizeof(all); i++) {
         if (living(all[i]) && member_array(TO, all[i]->query_enemy(-1)) >= 0)
             enemies += ({ all[i] });
     }
     if (how_to_sort == 0) return enemies;
     
     for (i=0; i<sizeof(enemies)-1; i++) {
         for (j=i+1; j<sizeof(enemies); j++) {
             switch (how_to_sort) {
                 case -1:     /* Sort in decreasing stat order */
                     if (enemies[i]->query_average_stat() <
                         enemies[j]->query_average_stat()) swap = 1;
                     break;
                 case 1:      /* Sort in increasing stat order */
                     if (enemies[i]->query_average_stat() >
                         enemies[j]->query_average_stat()) swap = 1;
                     break;
                 default:
                     return enemies;
             }
             if (swap) {
                 foo = enemies[i];
                 enemies[i] = enemies[j];
                 enemies[j] = foo;
                 swap = 0;
             }
         }
     }
     return enemies;
 }/*query_my_enemies*/


/* Function:         do_die()
 * What's it do:     Initiates death in slain monster.
*/
/* Function:         do_die()
 * What's it do:     Initiates death in slain monster.
*/
 
void
do_die(object killer)
{
    
    object *enemies;
    object kill_enemy;
    int i;
    
    enemies = query_my_enemies();

    for (i=0;i<sizeof(enemies);i++)
    {
        if (enemies[i]->test_bit("Kalad", 1, 16) && 
        enemies[i]->query_prop(I_DID_THE_SUMMON))
        kill_enemy = enemies[i];
    }

    kill_enemy->catch_tell("\n\nNow that Thanar is Vanquished. You should return to the "
    +"Blacksmith for your reward.\n\n");
    kill_enemy->add_prop(T_I_SUMMON_THANAR, 1);
    kill_enemy->remove_prop(T_GO_SUMMON_THANAR);

    if (shadow_summon == 0)
    {
        write("You think you can win that easily. My minions will destroy you.\n");
        create_shadow();
    }

    if (guard_summon == 0)
    {
        summon_guards();
    }
    
    command("say You cannot kill a God. You have simply released me from this "
    +"state. Now my influence shall spread over this realm. You've only made "
    +"my hold on this world STRONGER!");
    command("emote bursts into black flames and vanishes leaving no trace.");

    ::do_die(killer);
} 
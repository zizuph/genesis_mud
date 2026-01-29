/*
 * Base file for Dunlendings, near Rohan
 * Based on Haradrim
 * Raymundo, March 2020
 *
 * Changes:
 * 
 * 2021-09-28 - Cotillion
 * - Fixed use of wrong resistance prop
 *
 * 2022-02-10 - Zizuph
 * - Removed resistances - these are provided by the special's resistance library now.
 */
 
 /* set_gems(int)   Choose a number between 0 and 3.
                    0 = no gems.
                    1 = easy (low value)
                    2 = medium (medium value)
                    3 - hard (high value)
                    
    guard_type(int) SCOUT       0
                    GUARD       1
                    CAPTAIN     2
                    ARCHER      3

*/

#pragma strict_types
#pragma save_binary

inherit "/std/act/attack";
inherit "/std/monster";
inherit "/d/Genesis/specials/npc/stat_based_specials";
inherit "/lib/unique";
#include "/d/Gondor/defs.h"
#include "defs.h"

#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <options.h>
#include <tasks.h>

#define GEMS_SET "_i_have_gems_set_manually"

/*
 * Here we define adjectives for the different types of guards.
 *
 */
 //guard
#define GUARD_ADJ ({"swarthy", "smarmy", "villianous", "agressive", "mustachioed", "tattooed"})
#define POWER_ADJ ({"powerful", "strong", "muscular", "weak", "sniveling", "snot-nosed", "average"})

#define SCOUT_ADJ ({"sneaky", "stealthy", "observant", "quiet", "furtive"})
#define SCOUT_PWR ({"lithe", "dexterous", "fast", "lean"})

#define CAPT_ADJ    ({"brave", "courageous", "commanding", "imposing", "great", "glaring"})
#define CAPT_PWR    ({"tall", "gigantic", "large-handed", "bearded", "towering"})

#define ARCHER_ADJ    ({"accurate", "sharp-eyed", "blood-thirsty", "shadowy", "sharp-nosed"})
#define ARCHER_PWR     ({"big-biceped", "thick-armed", "vicious", "hate-filled"})

#define KILLER "i_kill_dunlendings"

void create_camp_guard() {}
void set_guard(int type);
void equip_me();

string adj1;
string adj2;
string name;

int difficulty = (random(4));

int set_gems(int dif);
int guard_level;

object slayer;

void
create_monster()
{
    adj1 = ONE_OF_LIST(GUARD_ADJ);
    adj2 = ONE_OF_LIST(POWER_ADJ);
    name = "dunlending";
    set_name(name);
    add_name(({"warrior","human", "dunlending"}));
    add_name("_dunlending_warrior_");
    add_adj(adj1);
    add_adj(adj2);
    add_adj(name);
    set_alignment(-800-random(200));  
    set_race_name("human");
    set_short(adj1 + " " + adj2 + " dunlending " + name);

   set_gender(random(2));
  

   set_skill(SS_WEP_SWORD,           85 + random(10));
   set_skill(SS_WEP_POLEARM,         85 + random(10));
   set_skill(SS_WEP_AXE,             85 + random(10));
   set_skill(SS_WEP_CLUB,            85 + random(10));
   set_skill(SS_WEP_KNIFE,           85 + random(10));
   set_skill(SS_PARRY,               90 + random(5));
   set_skill(SS_DEFENCE,             90 + random(5));
   set_skill(SS_AWARENESS,           45 + random(5));
   set_skill(SS_UNARM_COMBAT,        50 + random(10));
   set_skill(SS_PROTECT_TEAM_MEMBER, 80 + random(5)); 
   set_skill(SS_BLIND_COMBAT,        50);
   
   add_prop(CONT_I_HEIGHT,   185+random(15));
   add_prop(CONT_I_WEIGHT, 80000+random(5000));
   add_prop(CONT_I_VOLUME, 75000+random(15000));    
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(NPC_I_NO_UNARMED, 1);
   
   set_restrain_path(CAMP_ROOM_DIR);
   
    create_camp_guard();
}

/* Function:    set_resistance()
 * Arguments:   res = the amount of magic resist you want
 * Description: Sets random magic element resistance for this
 *              NPC.
 */
void
set_resistance(int res)
{
    int magic_type = (random(5));
    switch(magic_type)
    {
        case 0:
        add_prop(OBJ_I_RES_DEATH, res);
        add_prop(OBJ_I_RES_MAGIC, res);
        break;
        case 1:
        add_prop(OBJ_I_RES_COLD, res);
        add_prop(OBJ_I_RES_MAGIC, res);
        break;
        case 2:
        add_prop(OBJ_I_RES_ILLUSION, res);
        add_prop(OBJ_I_RES_MAGIC, res);
        break;
        case 3:
        add_prop(OBJ_I_RES_EARTH, res);
        add_prop(OBJ_I_RES_MAGIC, res);
        break;
        case 4:
        add_prop(OBJ_I_RES_AIR, res);
        add_prop(OBJ_I_RES_MAGIC, res);
        break;
    }
}

//Sets the guard type
void
set_guard(int type)
{
    guard_level = type;
    switch(type)
    {
        case 0:
        name = "scout";
        adj1 = ONE_OF_LIST(SCOUT_ADJ);
        adj2 = ONE_OF_LIST(SCOUT_PWR);
        set_adj( ({adj1, adj2}) );
        set_short(adj1 + " " + adj2 + " dunlending " + name);
        set_name(name);
        equip_me();
        if(!TO->query_prop(GEMS_SET))
        {
            if(random(3))
            {
                set_gems(1);
            }
        }
      //  set_stats( ({160, 200, 175, 140, 140, 175}), 20);
        set_base_stat(SS_STR,             160 + random(10));
        set_base_stat(SS_CON,             200 + random(10));
        set_base_stat(SS_DEX,             175 + random(10));
        set_base_stat(SS_INT,             140 + random(10));
        set_base_stat(SS_WIS,             140 + random(10));
        set_base_stat(SS_DIS,             140 + random(10));
        //set_resistance(10);
        
        return ;
        break;
        
        case 1:
        name = "guard";
        //Default adjectives are for the guard
        set_short(adj1 + " " + adj2 + " dunlending " + name);
        set_name(name);
        add_prop(LIVE_I_SEE_DARK, 5);
        set_stats( ({170, 210, 175, 135, 135, 175}), 20);
        //set_resistance(20);
        equip_me();
            if(!TO->query_prop(GEMS_SET))
        {
            if(random(3))
            {
                set_gems(2);
            }
        }
        return ;
        break;
        
        case 2:
        name = "captain";
        adj1 = ONE_OF_LIST(CAPT_ADJ);
        adj2 = ONE_OF_LIST(CAPT_PWR);
        set_adj( ({adj1, adj2}) );
        set_short(adj1 + " " + adj2 + " dunlending " + name);
        set_name(name);
        equip_me();
        TO->add_prop(LIVE_I_SEE_DARK, 100);
        if(!TO->query_prop(GEMS_SET))
        {
            if(random(3))
            {
                set_gems(3);
            }
        }
        set_stats( ({220, 220, 220, 160, 160, 250}), 20);
        //set_resistance(30);
        return;
        break;
        
        case 3:
        name = "archer";
        adj1 = ONE_OF_LIST(ARCHER_ADJ);
        adj2 = ONE_OF_LIST(ARCHER_PWR);
        set_adj( ({adj1, adj2}) );
        set_short(adj1 + " " + adj2 + " dunlending " + name);
        set_name(name);
        add_prop(LIVE_I_SEE_DARK, 100);
        set_skill(SS_WEP_MISSILE, 85 + random(10));
        if(!TO->query_prop(GEMS_SET))
        {
            if(random(3))
            {
                set_gems(3);
            }
        }
        set_stats( ({160, 200, 200, 140, 140, 150}), 20);
        //set_resistance(20);
        equip_me();
        return;
        break;
    }
}

/* Function:    equip_me()
 * Arguments:   none
 * Description: This function controls which weapons and armours are cloned
                to the Dunlendings, along with drop rates.
 */
void
equip_me()
{
    string bracers,
            greaves,
            helm,
            body,
            faulds,
            boots,
            weapon,
            quiver,
            blung;
     blung = ("/d/Gondor/common/herbs/blung.c");       
    if(!random(3))
        {
            equip(blung);
        }
    switch(guard_level)
    {
        //Scout
        case 0:
     weapon =    (CAMP_WEP_DIR + "weapon_regular");
        bracers =   (CAMP_ARM_DIR + "d_bracers_common");
        greaves =   (CAMP_ARM_DIR + "d_greaves_common");
        body =      (CAMP_ARM_DIR + "d_chainmail_common");
        helm =      (CAMP_ARM_DIR + "d_helm_common");
        if(!random(50))
        {
        faulds =    (CAMP_ARM_DIR + "d_faulds");
        }
        equip( ({weapon, bracers, greaves, body, helm}) );
        if(strlen(faulds))
        {
            equip(faulds);
        }
        return;
        
        //Guard
        case 1:
              
              
     weapon =    (CAMP_WEP_DIR + "weapon_regular");
        if(random(10))
        {
            bracers = (CAMP_ARM_DIR + "d_bracers_common");
        }
        else
        {
            bracers = (CAMP_ARM_DIR + "d_bracers");
        }
        if(random(10))
        {
            greaves = (CAMP_ARM_DIR + "d_greaves_common");
        }
        else
        {
            greaves = (CAMP_ARM_DIR + "d_greaves");
        }
        if(random(10))
        {
            body = (CAMP_ARM_DIR + "d_chainmail_common");
        }
        else
        {
            body = (CAMP_ARM_DIR + "d_chainmail");
        }   
        if(random(10))
        {
            helm = (CAMP_ARM_DIR + "d_helm_common");
        }
        else
        {
            helm = (CAMP_ARM_DIR + "d_helm");
        }
        if(!random(50))
        {
            faulds = (CAMP_ARM_DIR + "d_faulds");
        }
        equip( ({weapon, bracers, greaves, body, helm}) );
        if(strlen(faulds))
        {
            equip(faulds);
        }
        return;
        
        //Captain
         case 2:
         object body_armour;
         object d_weapon;
        d_weapon = clone_unique(CAMP_WEP_DIR + "weapon_magic", 1, CAMP_WEP_DIR 
            + "weapon_regular");     
       
        if(random(10))
        {
            bracers = (CAMP_ARM_DIR + "d_bracers_common");
        }
        else
        {
            bracers = (CAMP_ARM_DIR + "d_bracers");
        }
        if(random(10))
        {
            greaves = (CAMP_ARM_DIR + "d_greaves_common");
        }
        else
        {
            greaves = (CAMP_ARM_DIR + "d_greaves");
        }
            body_armour = clone_unique(CAMP_ARM_DIR + "d_platemail_magic", 1,
            CAMP_ARM_DIR + "d_chainmail");
        
        if(random(10))
        {
            helm = (CAMP_ARM_DIR + "d_helm_common");
        }
        else
        {
            helm = (CAMP_ARM_DIR + "d_helm");
        }
        if(!random(50))
        {
            faulds =    (CAMP_ARM_DIR + "d_faulds");
        }
        equip( ({d_weapon, bracers, greaves, body_armour, helm}) );
        if(strlen(faulds))
        {
            equip(faulds);
        }
        return;
        
        //Archer
        case 3:
        weapon =    (CAMP_WEP_DIR + "d_bow");
        quiver =    (CAMP_WEP_DIR + "d_quiver");
        if(random(10))
        {
            bracers = (CAMP_ARM_DIR + "d_bracers_common");
        }
        else
        {
            bracers = (CAMP_ARM_DIR + "d_bracers");
        }
        if(random(10))
        {
            greaves = (CAMP_ARM_DIR + "d_greaves_common");
        }
        else
        {
            greaves = (CAMP_ARM_DIR + "d_greaves");
        }
        if(random(10))
        {
            body = (CAMP_ARM_DIR + "d_chainmail_common");
        }
        else
        {
            body = (CAMP_ARM_DIR + "d_chainmail");
        }   
        if(random(10))
        {
            helm = (CAMP_ARM_DIR + "d_helm_common");
        }
        else
        {
            helm = (CAMP_ARM_DIR + "d_helm");
        }
        if(!random(50))
        {
            faulds =    (CAMP_ARM_DIR + "d_faulds");
        }
        equip( ({weapon, bracers, greaves, body, helm, quiver}) );
        if(strlen(faulds))
        {
            equip(faulds);
        }
               
        return;
    }
        
        
        

} //End of equipment

//the next 3 functions are the types of gems that can be dropped.
string
gems_easy()
{
    string *gemseasy =
        ({"agate", "pyrite", "quartz", "amber", "aquamarine", "spinel"});
    return(ONE_OF_LIST(gemseasy));
}
string
gems_medium()
{
    string *gemsmed =
        ({"topaz", "carnelian", "garnet", "lapis", "pearl", "jade", "turquoise"});
    return(ONE_OF_LIST(gemsmed));
}

string
gems_hard()
{
    string *gemshard =
        ({"diamond", "pearl_black", "alexandrite", "moonstone", "spinel", "amber", "coral", "sapphire"});
    return(ONE_OF_LIST(gemshard));
}

/* 
 * function        set_gems()
 * arguments    dif
 * 0 = no gems, 1 easy gems, 2 med gems, 3 hard gems
 *
 */
int
set_gems(int dif)
{
    difficulty = dif;
    TO->add_prop(GEMS_SET, 1);
}

/*
 * function:     make_gems
 * description:    used to determine which gems should go in which corpse.
 */ 
string
make_gems()
{
    if(difficulty >= 4)
    {
        difficulty = 1;
    }
    switch(difficulty)
    {
        case 0:
        return"";
        
        case 1:
        return(gems_easy());
        
        case 2:
        return(gems_medium());
        
        case 3:
        return(gems_hard());
        
        default:
        return(gems_easy());
        
    }
}


void
do_die(object killer)
{
    
    setuid();
    seteuid(getuid());
    
    if(!difficulty==0)
    {
    clone_object(GEMS_DIR + make_gems())->move(TO);
    }
    killer->add_prop(KILLER, 1);
    ::do_die(killer);
}
    

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me = TO;
    object *others = enemy->query_team_others();
    object next_victim;
    int pen, success;
   
    
    if (random(3))
        return 0;

    if (sizeof(others)) //Randomly attacks someone in the team.
        {
            others += ({ enemy });
            next_victim = others[random(sizeof(others))];
   
        if(!random(5)) 
        {        
            if (present(next_victim, environment(this_object())))
                {
                    
                    command("kill " + OB_NAME(next_victim));
                    command("laugh " + OB_NAME(next_victim));
                }
        }
        } //End random attack
    
    success = this_object()->resolve_task(TASK_ROUTINE, ({TS_DIS}), enemy, ({TS_DIS}) );
        if(success <= 0)
        {
            success = 0;
        }
        pen = 200;
    switch(success) //special attack messaging
    { 
    case 0:
    how = " with little effect";
    break;
    
    case 1..15:
        how = " lightly";
        pen = 250;
        break;
        
    case 16..30:
        how = " painfully";
        pen = 400;
        break;
    
    case 31..45:
        how = " with modest success";
        pen = 500;
        break;
    
    case 46..60:
        how = " striking a painful blow";
        pen = 650;
        break;
        
    case 61..75:
        how = " striking soundly";
        pen = 700;
        break;
        
    case 76..90:
        how = " leaving deep and painful wounds";
        pen = 800;
        break;
        
    case 91..100:
        how = " with a devestating effect";
        pen = 900;
        break;
        
    default:
        how = " with great force";
        pen = 900;
    }
    
    //Deals the damage.
    hitresult = enemy->hit_me(pen, W_BLUDGEON, this_object(), -1, -1); 
    
    //Special attack message delivered.
    enemy -> catch_msg(QCTNAME(me) + " lunges at you" + how + ".\n");
    tell_watcher(QCTNAME(me) + " lunges at " + QTNAME(enemy) 
        + how +".\n", enemy);
        
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(me);
    }
    return 1;
}

//attacks the player if the player has killed dunlendings.
public int
check_enemy(object tp)
{
    if(tp->query_prop(KILLER) && CAN_SEE(TO, tp))
    {
        command("kill " + tp->query_real_name());
        command("eat moss");
        string * murder_statement = ({
            "say Die, murderer!",
            "say This one's been killin' our troops!",
            "say I'm going to bury you next to your mother.",
            "say I'll stack your corpse in that barn!",
            "say I'm going to enjoy watching you bleed.",
            "say You're not going to find me so easy to kill.",
            "say When you die, I'm going to cut your heart out.",
            "say I've killed hobbits that were tougher than you."});
        if(!random(3))
        {
        command(one_of_list(murder_statement));
        }

        return 1;
    }
    else
    {
        string *innocent_action = ({
            "peer susp",
            "glare " + tp->query_real_name(),
            "frown menac",
            "emote looks deadly.",
            "emote licks the blood off of " + HIS_HER(TO) + " weapon.",
            "emote thinks about killing trespassers."});
        
        
        string *innocent_statement =({
            "You should leave.",
            "We're already camping here.",
            "Don't make me hurt you.",
            "You're not from around here, are you?",
            "You look weak. Go enlist in Minas Morgul.",
        "We're not looking for soldiers like you."});
        if(!random(3) && CAN_SEE(TO, tp))
        {            
            command(one_of_list(innocent_action));
            command("say " + one_of_list(innocent_statement));
        }
        return 0;
    }
}

//This way the dunlending attacks the player instead of the other way around
void
execute_alarm()
{
    check_enemy(slayer);
}

public void
init_living()
{
    ::init_living();
    slayer = TP;
    set_alarm(1.0, 0.0, "execute_alarm");
}


    

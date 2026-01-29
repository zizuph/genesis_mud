/*
* /d/Kalad/common/wild/lizard_area/npc/warrior_lizard.c
*
* Standard Lizard Warrior to be supported by the Lizard Shamans.
* Coded by Mirandus, February 2nd, 202
*
* 
*/

#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
inherit "/d/Kalad/common/wild/lizard_area/npc/std_lizard";

#define NECK  ARM + "lnecklace"

/* Define some attack and hitloc id's */
#define A_L_FIST   0
#define A_R_FIST   1
#define A_L_CLAW   2
#define A_R_CLAW   3

#define H_LCLAW    0
#define H_RCLAW    1
#define H_RARM     2
#define H_LARM     3
#define H_RLEG     4
#define H_LLEG     5

#define TYPE ({"menacing","dour", "gruesome", "grim",\
    "toothsome", "leary", "menacing", "intelligent", "haughty", "refined", \
    "distraught"})
#define PHYS ({"pointy-eared", "narrow-eyed", "snake-nosed", "towering",\
    "barrel-chested", "musclebound", "lithe", "languid", "athletic", "weathered"})
#define EYES ({"blue", "green", "grey"})
#define SKIN ({"green-scaled", "blue-scaled", "grey-scaled", "red-scaled",\
 "gold-scaled", "ebony-scaled"})
#define CLAWS ({"curved claws","sharp claws","menacing claws",\
"deadly claws","savage claws","vicious claws","intimidating claws",\
"knifelike claws","razor-sharp claws","devestating claws","lethal claws",})

#define LIZARD_S_SUBLOC "_lizard_subloc_npc_"

public void create_lizard_living();

/*
 * Function name: create_lizard_living()
 * Description  : Sets all the basic properties for the npc.
 */
public
void create_lizard_living()
{
    
    determine_sex();    
    string type, phys, eyes,skin;
    int i;

    seteuid(getuid());
    type = one_of_list(TYPE);
    phys = one_of_list(PHYS);
    eyes = one_of_list(EYES);
    skin = one_of_list(SKIN);
    
    string npc_name = "saurian";
    add_adj(type);
    add_adj(phys);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name(npc_name);
    set_name(gender_race);
    add_name("saurian");
    add_name("lizard");
    add_name("lizard-man");
    add_name("_saurian_lizard_");
    set_long("Standing tall and proud, this "+type
        +" "+phys+" "+gender_race+" is devouted to an ancient faith and "
        +"protecting "+hishers+" people. "+CAPheshe+" stands attentive and"
        +"protective, interacting with others as they pass and patrolling "
        +"when need be to ensure things are safe. Occasionally, "
        +heshe+" mutters something under "+hishers+" breath, "+hishers+" "
        +eyes+" eyes constantly monitoring the situation.\n");

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_HEIGHT, 180);
    add_subloc(LIZARD_S_SUBLOC, this_object());
   
   for(i = 0; i < 6; i++)
       set_base_stat(i, 180 + random(40));
	
	add_prop(LIVE_I_SEE_DARK, 20);

    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_DEFENCE,90);
    set_skill(SS_AWARENESS,90);
    set_skill(SS_ACROBAT, 90);
    set_all_hitloc_unarmed(45);
    set_vip_importance(0);

    MONEY_MAKE_PC(random(2))->move(TO);
    MONEY_MAKE_GC(random(12))->move(TO);


   	add_prop(LIVE_I_SEE_DARK, 20);

  
    set_alignment(-100);
    set_aggressive(VBFC_ME("check_aggressive"));
    set_prospective_cluster(({"_saurian_lizard_"}));
    
    set_act_time(random(600));
    add_act("say We shall overcome.");
    add_act("say Damn Thanarian Fools.");
    add_act("say Those humans have pushed us too far.");
    add_act("emote lowers his head remembering.");
    add_act("emote shudders with rage.");
    add_act("say I am but a tool for vengence.");
    add_ask(({"about quest","quest", "quests", "task", 
            "tasks", "help"}), help_response,1);
        
        
}/* create_thanar_living */

/*
 * Function name: arm_me()
 * Description  : Arms the NPC
 */
void
arm_me()
{
    seteuid(getuid(this_object()));
    equip(({ NECK, }));   

}/* arm_me */


string show_subloc( string subloc, object me, object for_obj )
{
    
    string str, subclaws;
    subclaws = one_of_list(CLAWS);
    
    if (me->query_prop( TEMP_SUBLOC_SHOW_ONLY_THINGS ))
    {
        return "";
    }
    
    if (subloc != LIZARD_S_SUBLOC)
    {
        return ::show_subloc(subloc, me, for_obj);
    }
    if (for_obj == me)
      str = "You are ";
  
    else
	  str = capitalize(this_object()->query_possessive())+ " hands have ";
    
    return str + subclaws+".\n";;
}

/*
 * Add attacks and hitlocations:
 *     add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
 *     add_hitloc(int *ac, int prchit, string desc, int id)
 *
 * *ac == ({ ac-impale, ac-slash, ac-bludgeon })
 */
public void 
cr_configure()
{
    add_attack(40+random(20),40+random(20),W_SLASH,40,A_L_FIST);
    add_attack(40+random(20),40+random(20),W_SLASH,40,A_R_FIST);
    add_attack(40+random(20),40+random(20),W_SLASH,55,A_L_FOOT);
    add_attack(40+random(20),40+random(20),W_SLASH,55,A_R_FOOT);
    add_hitloc(({45,45,45}),5,
        "razor sharp left claw",H_LCLAW);
    add_hitloc(({45,45,45}),35,
        "razor sharp right claw",H_RCLAW);
    add_hitloc(({45,45,45}),10,
        "scaled right arm",H_RARM);
    add_hitloc(({45,45,45}),10,
        "scaled left arm",H_LARM);
    add_hitloc(({45,45,45}),20,
        "scaled right leg",H_RLEG);
    add_hitloc(({45,45,45}),20,
        "scaled left leg",H_LLEG);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_L_FIST:return "razor clawed left hand";
    case A_R_FIST:return "razor clawed right hand";
    case A_L_CLAW:return "clawed left foot";
    case A_R_CLAW:return "clawed right foot";
    }
    return "mind"; /* should never occur */
}
/*
 * Function name: special_attack()
 * Description  : Randomly triggers the special attack
 * Arguments    : Enemy = the enemy of the object
 */
int
special_attack(object enemy)
{
    object *ob;
    object *enemies;
    object kill_enemy, enemy;
    int i;
    int did_push;
    object me;
    mixed* hitresult;
    string how;
    me = this_object();
    
    enemies = query_my_enemies();
    
    if (sizeof(enemies) == 0) return 0;
    
    /* This decides if we shall do anything more... */
    if (random(2))
        return 0;
    
    enemy = me->query_attack();
    
    /*We want this to be hard. So they attack the smallest*/
    if (enemy != me->query_smallest_enemy())
    {   
         enemy = query_smallest_enemy();
         kill_enemy = enemy;
         command("kill "+kill_enemy->query_real_name());
    }
    
    int pen = query_pen_by_stat(TO->query_average_stat());
    hitresult = enemy->hit_me(query_pen_by_stat(pen) + random(600), W_SLASH, me, -1);

    switch (hitresult[3])
    {
        case 0..20:
            how = "without effect";
            break;
        case 21..50:
            how = "drawing thin red lines";
            break;
        case 51..80:
            how = "slashing the flesh";
            break;
        case 81..110:
            how = "ripping chunks of flesh";
            break;
        case 111..140:
            how = "rending flesh";
            break;
        case 141..170:
            how = "showering the area in gore";
            break;
        default:
            how = "showering the area in gore";
            break;
    }
    me -> catch_msg("You slash out at your opponent with your claws, "+how+"!\n");
    enemy->catch_msg(QCTNAME(me)+" launches towards you, claws outstretched "+how+"!\n");
    tell_watcher(QCTNAME(me)+" leaps forward towards, claws extended "+QTNAME(enemy)+" "+how+
        "!\n",enemy);
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(me);
        return 1;
    }
}/*special_attack*/


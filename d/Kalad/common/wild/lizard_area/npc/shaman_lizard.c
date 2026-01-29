/*
* /d/Kalad/common/wild/lizard_area/npc/shaman_lizard.c
* Shaman Saurian to support Warrior Saurian. Hides behind but supports.
* Created by Mirandus - February 5, 2022
*
*
 */

#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <comb_mag.h>
inherit LIV + "std_lizard";


/* The spell stuff */
#define MANA_SHADOW          (GENSPECIALS + "shadows/mana_shadow")
#define SPELL_SOUL           (SPELLS + "lizard_spell_soul")
#define SPELL_MANAGER_SOUL   (GENSPECIALS + "/souls/spell_manager_soul")

#define NECK  ARM + "lnecklace"

// Prototypes

public void         get_me_soul();
public void         create_lizard_living();
public int          no_repeat_harm_spell();
public void         summon_guards();
int                 special_attack(object enemy);
int                 soul_id;
int                 guard_summon = 0;
int                 heal_times = 0;

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

#define TYPE ({"wizened","methodical", "contemplative", "hunched",\
    "elderly", "thoughtful", "brilliant", "intelligent", "haughty", "refined", \
    "peaceful"})
#define PHYS ({"pointy-eared", "wide-eyed", "snake-nosed", "towering",\
    "thin", "frail", "lithe", "languid", "dimunitive", "weathered"})
#define EYES ({"blue", "green", "grey"})
#define SKIN ({"green-scaled", "blue-scaled", "grey-scaled", "red-scaled",\
 "gold-scaled", "ebony-scaled"})
#define CLAWS ({"curved claws","sharp claws","menacing claws",\
"deadly claws","savage claws","vicious claws","intimidating claws",\
"knifelike claws","razor-sharp claws","devestating claws","lethal claws",})

#define LIZARD_S_SUBLOC "_lizard_subloc_npc_"

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
	
    add_prop(LIVE_I_SEE_DARK, 20);

    for(i = 0; i < 6; i++)
        set_base_stat(i, 180 + random(30));

    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_DEFENCE,90);
    set_skill(SS_AWARENESS,90);
    set_skill(SS_ACROBAT, 90);
    set_vip_importance(1);
    set_all_hitloc_unarmed(45);

           
    set_skill(SS_SPELLCRAFT,100);
    set_skill(SS_FORM_ENCHANTMENT, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_FORM_TRANSMUTATION, 100);
    set_skill(SS_FORM_ABJURATION, 100);
    set_skill(SS_ELEMENT_DEATH, 100);
    set_skill(SS_ELEMENT_LIFE, 100);
    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_ELEMENT_AIR, 100);
    set_skill(SS_ELEMENT_EARTH, 100);
    
    
    set_alignment(-100);
    set_aggressive(VBFC_ME("check_aggressive"));
    set_prospective_cluster(({"_saurian_lizard_"}));

    MONEY_MAKE_PC(random(2))->move(TO);
    MONEY_MAKE_GC(random(12))->move(TO);
    
    set_act_time(random(400));
    add_act("say We shall overcome.");
    add_act("say Damn Thanarian Fools.");
    add_act("say Those humans have pushed us too far.");
    add_act("emote lowers his head remembering.");
    add_act("emote shudders with rage.");
    add_act("say I am but a tool for vengence.");
    add_ask(({"about quest","quest", "quests", "task", 
            "tasks", "help"}), help_response,1);
      
     clone_object(MANA_SHADOW)->shadow_me(TO);
     soul_id = set_alarm(0.5, 0.0, &get_me_soul());
     seteuid(getuid());
        
} /* create_lizard_living */


/*
 * Function name: arm_me()
 * Description  : Arms the NPC
 */
void
arm_me()
{
    seteuid(getuid(this_object()));
    equip( ({NECK,}));
}/*arm_me*/

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
} /* get_me_soul */


/*
* Function name: no_repeat_harm_spell
* Description  : Makes certain the harm spell is not constantly repeated.           
*/
public int
no_repeat_harm_spell()
{
    return 1;
} /* no_repeat_harm_spell */

/*
* Function name: test_friend
* Description  : Checks who is friendly in the room.
* Object : who - who is checked.
*/

int
test_friend(object who)
{
   if(who->query_name() == "_saurian_lizard_")
      return 1;
      
   return 0;
}

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
    add_attack(30+random(15),30+random(15),W_SLASH,40,A_L_FIST);
    add_attack(30+random(15),30+random(15),W_SLASH,40,A_R_FIST);
    add_attack(30+random(15),30+random(15),W_SLASH,55,A_L_CLAW);
    add_attack(30+random(15),30+random(15),W_SLASH,55,A_R_CLAW);
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
 * Function name: special_attack
 * Description  : Handles the spell rotation for the npc
 * Arguments    : object enemy
 * Returns      : 1 or 0 
 */
int
special_attack(object enemy)
{
    int i;
    int attacktype = random(1);
    object *enemies, enemy, kill_enemy, me;
	me = this_object();
 
	if (attacktype == 0 || attacktype == 1)
    {
       if(!("/d/Kalad/common/wild/lizard_area/spells/lreflect"
            ->has_spell_object(TO)))
       {
         /* Make certain they always keep resistances up. */
          command("cast lreflect");
          return 1;
       } 
    }
    
    enemies = query_my_enemies();
    
	if (sizeof(enemies) == 0) return 0;
    
    enemy = me->query_attack();
    
    /*We want this to be hard. So they attack the smallest*/
    if (enemy != me->query_smallest_enemy())
    {   
         enemy = query_smallest_enemy();
         kill_enemy = enemy;
         command("kill "+kill_enemy->query_real_name());
    }
    
    //At 1/3 HP summon some more warriors
    if (guard_summon == 0 && query_hp() <= (query_max_hp() / 3))
    {
        summon_guards();
        return 1;
    }
    
    //at 1/4 HP heal up only 3 times tho.
    if (heal_times == 3 && query_hp() <= (query_max_hp() / 4))
    {
        command("emote stops fighting and focuses inward seemingly becoming "+
        "physically restored.\n");
        this_object()->heal_hp((500) + random(250));
        heal_times == heal_times + 1;
        return 1;
    }

     /* See if we want to cast a blind*/
    if(!random(5))
    {
        command("cast lblind " + enemy->query_real_name()); 
        return 1;           
        
    }
    
    //See if we want to cast a Stun
    if (!random(5))
    {
        command("cast lstun " + enemy->query_real_name()); 
        return 1;
        
    }
} /* special_attack */

/*
* Function name: summon_guards
* Description  : When Shaman is at 1/3 health he summons guards to assist
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
    command("emote cries out a gutteral tone.");
    for (i = 0; i < random(3); i++)
    {
        troops = clone_object(LIV + "warrior_lizard");
        troops->move_living("M", E(TO));
        troops->command("$kill " + OB_NAME(enemy));
    }
    enemy->attack_object(troops);
    command("say Now you shall feel our wrath!");
    guard_summon = 1;
    return;
}
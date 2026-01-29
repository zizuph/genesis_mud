/*
 * /d/Kalad/common/guilds/new_thanar/npc/caster_priest.c
 * A caster priest meant for grinding in the Thanar Church
 * Created by Zignur 2018-01-25
 * Updated by Mirandus to include new Defs and gender based race.
 */

#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
inherit "/d/Kalad/common/guilds/new_thanar/npc/std_priest";


/* The spell stuff */
#define MANA_SHADOW          (GENSPECIALS + "shadows/mana_shadow")
#define SPELL_SOUL           (SPELLS + "thanar_spell_soul")
#define SPELL_MANAGER_SOUL   (GENSPECIALS + "guilds/souls/spell_manager_soul")
/* Global variables */
int soul_id;
#define ROBE  ARM + "probe"
#define SHIRT ARM + "pmail"
#define PANTS ARM + "pleggings"
#define NECK  ARM + "pnecklace"
#define CLUB  WEP + "pclub"

#define TYPE ({"plain","dour", "friendly", "grim",\
"stoic", "contemplative", "menacing", "intelligent", "refined", "pious", \
"distraught"})
#define PHYS ({"big-eared", "round-eyed", "button-nosed", "towering",\
"barrel-cheasted", "musclebound", "lithe", "languid", "athletic", "weathered"})
#define EYES ({"blue", "green", "brown", "hazel", "grey"})
#define SKIN ({"dark", "light", "pale", "tanned", "sun-burned", "ebony"})
#define HAIR ({"blonde", "dirty-blonde", "red", "black", "auburn", \
"white", "grey"})

// Prototypes
public void         get_me_soul();
public void create_thanar_living();
public int          no_repeat_harm_spell();
int                 special_attack(object enemy);

/*
 * Function name: create_thanar_living()
 * Description  : Sets all the basic properties for the npc.
 */
public
void create_thanar_living()
{
    
    determine_sex();
    string type, phys, eyes,skin, hair;
    int i;

    seteuid(getuid());
    type = one_of_list(TYPE);
    phys = one_of_list(PHYS);
    eyes = one_of_list(EYES);
    skin = one_of_list(SKIN);
    hair = one_of_list(HAIR);

    string npc_name = "human";

    add_adj(type);
    add_adj(phys);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name(gender_race);
    add_name(npc_name);
    add_name("_thanar_priest");
        
    set_long("Standing tall and proud in his faith, this "+type
      +" "+phys+" priest is intent on ensuring the spread and following "
      +"of "+hishers+" faith. "+CAPheshe+" tends to aspects of the church "
      +"answering questions of practitioners, cleaning when need be. "
      +"ensuring things are organized. Occasionally, "+heshe+" mutters "
      +"something under "+hishers+" breath, "+hishers+" "+eyes+" eyes "
      +"constantly monitoring the situation.\n");

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_HEIGHT, 180);

    for(i = 0; i < 6; i++)
        set_base_stat(i, 180 + random(10));

    set_hitloc_unarmed(A_HEAD, 20, 15, "head");
    set_hitloc_unarmed(A_R_ARM, 20, 10, "right arm");
    set_hitloc_unarmed(A_L_ARM, 20, 10, "left arm");
    set_hitloc_unarmed(A_BODY, 20, 45, "body");
    set_hitloc_unarmed(A_LEGS, 20, 20, "legs");

    set_skill(SS_UNARM_COMBAT,70);
    set_skill(SS_WEP_CLUB, 70);
    set_skill(SS_PARRY, 70);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_AWARENESS,90);
        
    set_skill(SS_SPELLCRAFT,100);
    set_skill(SS_FORM_ENCHANTMENT, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_FORM_TRANSMUTATION, 100);
    set_skill(SS_ELEMENT_DEATH, 100);
    set_skill(SS_ELEMENT_LIFE, 100);
    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_ELEMENT_AIR, 100);
    set_skill(SS_ELEMENT_EARTH, 100);

        
    set_prospective_cluster(({"_thanar_priest"}));
    set_act_time(random(400));
    add_act("say Humanity is the superior race.");
    add_act("say Thanar grants us clarity and wisdom.");
    add_act("say Demi-humans are an abomination.");
    add_act("emote lowers his head in prayer.");
    add_act("emote turns his head to the sky in prayer.");
    add_act("say I am but a conduit for Thanar's power.");
    add_ask(({"about quest","quest", "quests", "task", 
               "tasks", "help"}), help_response,1);
    add_ask(({"about thanar", "thanar", "religion",
               "order"}), thanar_response,1);
      
    set_alarm(1.0,0.0,"arm_me");
        
     /* Zignur Add the spellcasting soul and shadow */   
     clone_object(MANA_SHADOW)->shadow_me(TO);
     soul_id = set_alarm(0.5, 0.0, &get_me_soul());
     seteuid(getuid());
        
} /* create_thanar_living */


/*
 * Function name: arm_me()
 * Description  : Arms the NPC
 */
void
arm_me()
{
    seteuid(getuid(this_object()));
    equip( ({ ROBE,
              SHIRT,
              PANTS,
              NECK,
              CLUB,  }));
}

/* Function:         do_die()
 * What's it do:     Ordinarily initiates death in slain monster.
 * What's it do now: Destroys some to all gold and armaments with a higher
 *                   chance the bigger the player. */
 
void
do_die(object killer)
{
    command("say Thanar grant me peace and smite my foe.");
    command("emote attempts to pray through gurgling blood.");   
    ::do_die(killer);
}

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
    
  
    /* We want to always attack the enemy with the lowest health */   
    kill_enemy = this_object()->query_attack();

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
     /* See if we want to cast a blind or stun*/
    if(!random(10))
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
    
    //See if we want to cast a fireball or blind - Only if 50% or less HP
    if (query_hp() <= (query_max_hp() / 2) || !random(10))
    {
        if(!random(2))
           {
               command("cast tdamage " + kill_enemy->query_real_name()); 
               return 1;
           }
       // Cast the fireball
       command("cast tdrain " + kill_enemy->query_real_name()); 
       return 1;    
    }
} /* special_attack */

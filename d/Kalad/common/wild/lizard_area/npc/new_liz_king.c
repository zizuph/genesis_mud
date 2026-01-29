/*
* /d/Kalad/common/wild/lizard_area/npc/new_liz_king.c
*
* New Lizard King with Updated Trident
* Coded by Mirandus, February 2nd, 2022
*
* 
*/

#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
inherit LIV + "std_lizard";

/* Mirandus: Add a kill logger */
//inherit "/d/Kalad/common/kill_logger";
/* Mirandus: Use clone unique for any speciality items he drops */
inherit "/lib/unique";

/*Defines for special objects*/
#define MANA_SHADOW          (GENSPECIALS + "shadows/mana_shadow")
#define SPELL_SOUL           (SPELLS + "king_spell_soul")
#define SPELL_MANAGER_SOUL   (GENSPECIALS + "souls/spell_manager_soul")
#define TRIDENT              (WEP + "new_lmk_trident")
#define NECK                 (ARM + "lnecklace")

/* Global variables */
public void         get_me_soul();
public void         summon_guards();
public void         create_lizard_living();
int                 special_attack(object enemy);
int soul_id;
int guard_summon = 0;



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

#define TYPE ({"menacing"})
#define PHYS ({"towering"})
#define EYES ({"blue", "green", "grey"})
#define SKIN ({"green-scaled"})
#define CLAWS ({"lethal claws",})

#define LIZARD_S_SUBLOC "_lizard_subloc_npc_"

public void create_lizard_living();

/*
 * Function name: create_lizard_living()
 * Description  : Sets all the basic properties for the npc.
 */
public
void create_lizard_living()
{
    
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
    
    set_race_name(npc_name);
    set_name("Emereth Ba'Lia");
    add_name("saurian");
    add_name("lizard");
    add_name("lizard-king");
    add_name("king");
    add_name("emereth");
    add_name("_saurian_lizard_");
    set_gender(G_NEUTER);
    set_long("Standing tall and proud, this "+type
        +" "+phys+ " saurian is one above the rest of those he is "
        +"protecting. "+CAPheshe+" stand regal and powerful overseeing the"
        +"area. "+CAPheshe+" is formidable in their appearance standing  "
        +"head and shoulders above the others within these caverns. Their "
        +"muscles ripple as they shift positions. They look about with their"
        +eyes+" eyes constantly monitoring the situation.\n");

    set_title("the Saurian King. Most Honoured of the Ancients and Keeper "
    +"of Secrets");

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_HEIGHT, 180);
    add_subloc(LIZARD_S_SUBLOC, this_object());
   
   for(i = 0; i < 6; i++)
       set_base_stat(i, 180 + random(40));
	
	add_prop(LIVE_I_SEE_DARK, 20);

    set_alignment(-1200);
    
    set_aggressive(VBFC_ME("check_aggressive"));

    set_skill(SS_WEP_POLEARM,100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_ACROBAT, 100);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_AWARENESS,100);
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
    set_all_hitloc_unarmed(55);
    set_vip_importance(5);

    MONEY_MAKE_PC(random(2))->move(TO);
    MONEY_MAKE_GC(random(12))->move(TO);


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

  
    set_alignment(-100);
    set_prospective_cluster(({"_saurian_lizard_"}));
    
    set_cact_time(1);
    add_cact("say You think you can defeat me?");
    add_cact("I am more ancient than you shall ever know.");
    add_cact("cackle maniac");
    add_cact("say You've made a grave mistake.");
    add_cact("emote laughs at you in complete and utter contempt.");
    add_cact("laugh confidently");
    add_cact("smirk");
        
        
}/* create_thanar_living */

/*
 * Function name: arm_me()
 * Description  : Arms the NPC
 */
void
arm_me()
{
    seteuid(getuid(this_object()));
    equip(({ NECK, TRIDENT }));   

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
     command("say Fine. Wonderful. Let's fight.");
     command("introduce me to "+this_player()->query_real_name());
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
    add_hitloc(({55,55,55}),5,
        "razor sharp left claw",H_LCLAW);
    add_hitloc(({55,55,55}),35,
        "razor sharp right claw",H_RCLAW);
    add_hitloc(({55,55,55}),10,
        "scaled right arm",H_RARM);
    add_hitloc(({55,55,55}),10,
        "scaled left arm",H_LARM);
    add_hitloc(({55,55,55}),20,
        "scaled right leg",H_RLEG);
    add_hitloc(({55,55,55}),20,
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
    int attacktype = random(1);
    int did_push;
    object me;
    mixed* hitresult;
    string how;
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

    //At 1/3 HP summon some more warriors
    if (guard_summon == 0 && query_hp() <= (query_max_hp() / 3))
    {
        summon_guards();
        return 1;
    }
    
    int pen = query_pen_by_stat(TO->query_average_stat());
    hitresult = enemy->hit_me(query_pen_by_stat(pen) + random(750), W_SLASH, me, -1);

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

/*
* Function name: summon_guards
* Description  : When King is at 1/3 health he summons guards to assist
*                him in combat.
* Arguments    : object enemy - The enemy of the NPC as set in the combat file
* Returns      : int 1 - tells the combat file that a special was cast
*/
public void
summon_guards()
{
    object troops, stroops, enemy;
    int i;
	enemy = this_object()->query_attack();
    
    seteuid(getuid(TO));
    command("emote cries out a gutteral tone.");
    for (i = 0; i < 2; i++)
    {
        troops = clone_object(LIV + "warrior_lizard");
        troops->move_living("M", E(TO));
        troops->command("$kill " + OB_NAME(enemy));
    }
    for (i = 0; i < 1; i++)
    {
        troops = clone_object(LIV + "shaman_lizard");
        troops->move_living("M", E(TO));
        troops->command("$kill " + OB_NAME(enemy));
    }
    enemy->attack_object(troops);
    command("say Now you shall feel our wrath!");
    guard_summon = 1;
    return;
}

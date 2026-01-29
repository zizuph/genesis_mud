/*
 *  This is a giant skeleton champion, stationed outside of the 
 *  Dragon's lair. The monster is basically a group encounter, ment
 *  as an extra, possibly additional challenge to grouped people.
 *  Whenever its possible to solo, its uknown, but bouncing people
 *  will find themselves quite disappointed since the monster
 *  heals itself if the target is no longer present in the
 *  room.
 *
 *  Created by Nerull, 21-2-2009
 */

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <options.h>
#include "../defs.h";

inherit "/std/monster";

#define SKELETON_HP    30000

#define RANGER_M_NOT_DISARM     "_ranger_m_not_disarm"
#define RANGER_I_NOT_DISARM     "_ranger_i_not_disarm"

#define MORTAL_CAN_USE_THIS     "_mortal_can_use_this"


int heal_alarm;

object special_weapon;


void
fix_prop()
{
	 
	  special_weapon->remove_prop(MORTAL_CAN_USE_THIS);
	  return;
}

void
arm_me()
{   
    seteuid(getuid());  
    clone_object(DRAGON_DIR +"arm/skhelm")->move(this_object(), 1);
    clone_object(DRAGON_DIR +"arm/skbreastplate")->move(this_object(), 1);
    clone_object(DRAGON_DIR +"arm/skbracers")->move(this_object(), 1);
    clone_object(DRAGON_DIR +"arm/skgreaves")->move(this_object(), 1);
   
    
    special_weapon =  clone_object(DRAGON_DIR +"wep/special_weapon");
    special_weapon->add_prop(MORTAL_CAN_USE_THIS, 1);
    set_alarm(5.0, 0.0, &fix_prop());
    special_weapon->move(this_object(), 1);
       
    command("wear all");
    command("wield all");	
}




void
do_regenerate()
{
	  if (query_attack() == 0)
	  {             
        if (this_object()->query_hp() != SKELETON_HP)
        {
            tell_room(environment(this_object()), QCNAME(this_object())+
            " fully regenerates.\n");
            this_object()->set_hp(SKELETON_HP);
        }
	  	    			
	  }
	  	   
	  if (!present(special_weapon, this_object()))
	  {
	  	  special_weapon =  clone_object(DRAGON_DIR +
	  	  "wep/special_weapon");
        special_weapon->add_prop(MORTAL_CAN_USE_THIS, 1);
        set_alarm(5.0, 0.0, &fix_prop());
        special_weapon->move(this_object(), 1);
          
        command("wield all");	
    }
	  	   
	  return;
}


void create_monster()
{
    set_name("Champion");
    add_name("_skeleton_champion");
    add_name("champion");
    add_name("skeleton");
    set_adj("skeleton");
    set_short("giant skeleton champion");
    set_long("This is a giant rust-coloured skeleton clad in blackened " +
    "tungsten armour. It stands firmly nine feet over the " +
    "ground, watching the area closely for something. It looks " +
    "like a human skeleton, except that its much larger in both " +
    "width and height. It looks menacing and its white-glowing " +
    "eyes hints of a fanatic dedication to whatever it serves.\n");
    set_race_name("skeleton");
   
    set_base_stat(SS_STR, 170+random(40));
    set_base_stat(SS_DEX, 170+random(40));
    set_base_stat(SS_CON, 170+random(40));
    set_base_stat(SS_INT, 170+random(40));
    set_base_stat(SS_WIS, 170+random(40));
    set_base_stat(SS_DIS, 170+random(40));
   
    
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_WEP_POLEARM,100);
    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_WEP_KNIFE,100);
    set_skill(SS_WEP_AXE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_2H_COMBAT, 100);
    
    set_act_time(7);    
    set_attack_chance(100);
    add_act("emote flickers with its white-glowing eyesockets.");
    add_act("emote grinds its teeth.");
    add_act("emote paces slowly about.");
    add_act("emote stares into the sky.");
    add_act("emote glances at a small insect crawling on its skeletal " +
    "feet.");
    add_act("emote hums a melodramatic tune.");
    add_act("emote ponders what "+random(6000)+" multiplied with" +
    " "+random(5000)+" is.\n");
    add_act("emote thinks hard about E = MC^2.");
    
    


    // It may random attack different people while in combat.
    set_cact_time(3);
    add_cact("grin mal");
    add_cact("sneer");
    add_cact("shout DIE!");
    add_cact("kill elf");
    add_cact("kill dwarf");
    add_cact("kill human");
    add_cact("kill goblin");
    add_cact("kill gnome");
    add_cact("kill minotaur");
    add_cact("kill ogre");
    add_cact("kill wraith");
    add_cact("kill presence");
    add_cact("kill kender");


    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_SEE_DARK, 90);
    add_prop(LIVE_I_SEE_INVIS, 90);
    add_prop(LIVE_I_QUICKNESS, 100);


    set_gender(2);
    set_alignment(0);
    
    arm_me();  
    
    heal_alarm = set_alarm(3.0,3.0, &do_regenerate());
}

// Magical enchants have made the skeleton quite resilient
// against various forms of magic.
int
query_magic_res(string prop)
{    
    if (prop == MAGIC_I_RES_POISON ||
       prop == MAGIC_I_RES_FIRE ||
       prop == MAGIC_I_RES_LIFE ||
       prop == MAGIC_I_RES_WATER ||
       prop == MAGIC_I_RES_LIGHT ||
       prop == MAGIC_I_RES_COLD ||
       prop == MAGIC_I_RES_MAGIC ||
       prop == MAGIC_I_RES_EARTH ||
       prop == MAGIC_I_RES_AIR ||
       prop == MAGIC_I_RES_ELECTRICITY ||
       prop == MAGIC_I_RES_ILLUSION ||
       prop == MAGIC_I_RES_ACID ||
       prop == MAGIC_I_RES_DEATH)
       return 70;
    else
       return 60;    
}


int
add_prop_live_i_stunned(mixed val)
{
    return 1;
}

int
add_prop_live_as_attack_fumble(mixed val)
{
    return 1;
}

int
add_prop_live_i_attack_delay(mixed val)
{
    return 1;
}


int query_max_hp()
{ 	  
	  return SKELETON_HP; 
}


mixed 
query_option(int opt) 
{
    return (opt == OPT_UNARMED_OFF); 
}


void
do_die(object who)
{
	  remove_alarm(heal_alarm);
	  
	  special_weapon->add_prop(MORTAL_CAN_USE_THIS, 1);
	  
    ::do_die(who);
}



public void
attacked_by(object ob)
{
	  this_object()->query_team_others()->command("kill "+OB_NAME(ob));	
}

int
special_attack(object enemy)
{
    object me = this_object();

    mixed *hitresult;
    string how;

    if (random(3))
    {
        return 0; 
    }

    hitresult = enemy->hit_me(50 + random(400), W_BLUDGEON, me, -1);
    switch (hitresult[0])
    {
        case 0:
            how = "not hurt at all";
            break;
        case 1..40:
            how = "barely injured";
            break;
        case 41..80:
            how = "injured";
            break;
        case 81..600:
            how = "severly injured";
            break;            
        default:
            how = "crushed";
            break;
    }

    enemy->catch_tell(query_The_name(enemy) + " suddenly slams "+
    "into your body!\n"+"You are " + how + "!\n");

    tell_watcher(QCTNAME(me) + " suddenly slams into body of " +
    QTNAME(enemy) + "!\n" +capitalize(enemy->query_pronoun()) +
    " is " + how + "!\n", enemy);

    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_object());
    }
    
    return 1; /*  Important! Should not have two attacks in a round. */
}

public int query_panic() 
{ 
    return 0; 
} 


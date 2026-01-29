/*
 *  The High Lords councellor, in the Citadel.
 *  MADE BY: Korat
 *  DATE: Feb 14 1995
 *  Reworked by Zignur 2017-11-09
*/
/* Zignur We use this to make him team properly */
inherit "/d/Kalad/std/active_monster_base";
/* Zignur Add a kill logger */
inherit "/d/Kalad/common/kill_logger_temp";
/* Zignur  Use clone unique for his wand */
inherit "/lib/unique";


#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
#include <stdproperties.h>
#include "/sys/wa_types.h"
#include "/sys/filter_funs.h"
#include "/sys/composite.h"
#include <comb_mag.h>


/* Prototypes */
public void         get_me_soul();
public int          inguild(string word,string str);
public void         react_introduce(string person,string who);
public void         intro_the_lord(string person,string member_of);
public int          no_repeat_harm_spell();
public int          attack_object(object ob);


/* Zignur: The spell stuff */
#define MANA_SHADOW          ("/d/Genesis/specials/guilds/shadows/mana_shadow")
#define SPELL_SOUL           ("/d/Kalad/common/specials/spells/urian_spell_soul")
#define SPELL_MANAGER_SOUL   ("/d/Genesis/specials/guilds/souls/spell_manager_soul")
/* Global variables */
int soul_id;

/*
 * Function name:        create_monster
 * Description  :        Creates the npc
 */
void
create_monster()
{
   set_name("shamein");
   add_name("mage");
   add_name("_urian_npc");
   set_adj("thin");
   add_adj("sly");
   set_alignment(0);
   set_race_name("human");
   set_long("This thin human seems to be an important man to the High " +
      "Lord. You cannot see his face or hands at all, since he is " +
      "covered in a large darkened robe. All you notice from him is his " +
      "shrill, weak voice when he bends over to whisper into the High " +
      "Lords ear.\n");
   set_stats(({220,220,220,220,220,220}));
   set_skill(SS_DEFENCE,80);
   set_skill(SS_PARRY,80);
   set_skill(SS_WEP_KNIFE,100);
   set_skill(SS_AWARENESS,90);
   set_skill(SS_SPELLCRAFT,100);
   set_skill(SS_FORM_ENCHANTMENT, 100);
   set_skill(SS_FORM_CONJURATION, 100);
   set_skill(SS_FORM_DIVINATION, 100);
   set_skill(SS_FORM_ABJURATION, 100);
   set_skill(SS_FORM_ILLUSION, 100);
   set_skill(SS_FORM_TRANSMUTATION, 100);
   set_skill(SS_ELEMENT_FIRE, 100);
   set_skill(SS_ELEMENT_AIR, 100);
   
   set_act_time(5);
   add_act(({"whisper urian something devillishly...","nod . urian"}));
   add_act("whisper urian something devillishly...");
   add_act(({"whisper urian something devillishly...","bow . urian"}));
   add_act("hmm");
   
   add_prop(NPC_M_NO_ACCEPT_GIVE,1);
   add_prop(LIVE_I_SEE_DARK, 20);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(LIVE_I_ATTACK_THIEF, 1);
   trig_new("%w 'introduces' %s", "react_introduce");
   trig_new("%w 'attacks' %s","react_attack"); 
    
    /* Zignur use equip and clone_unique */
    object weapon, armour;
    seteuid(getuid(TO));
   
    weapon = clone_unique("/d/Kalad/common/central/wep/councellor_wand", 10,
                          "/d/Kalad/common/central/wep/councellor_dagger");
    weapon -> move(TO);
     
   /* Zignur Add some gear */
   equip(({
        "/d/Kalad/common/central/arm/councellor_robe",
        weapon,
        }));   
        
   command("hold wand");
   
   /* Zignur Add him to the team */
   set_prospective_cluster(({"_urian_npc"}));
   
   /* Zignur Add the spellcasting soul and shadow */   
   clone_object(MANA_SHADOW)->shadow_me(TO);
   soul_id = set_alarm(0.5, 0.0, &get_me_soul());
   seteuid(getuid());
   
   /* Zignur XP Adjustment */
   set_exp_factor(150);  

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
}

/*
 * Function name: inguild
 * Description  : Checks for the precense of a word in a string
 * Arguments    : string word, string str
 * Returns      : 1 or 0 
 */
public int 
inguild(string word,string str)
{
   string *text;
   int i;
   text = explode(str," ");
   for (i=0;i<sizeof(text);i++)
   if (text[i]==word) return 1;
   return 0;
}

/*
 * Function name: react_introduce
 * Description  : this routine reacts to intro's, and will introduce
 *                the High Lord to the players.
 * Arguments    : string person, string who
 */
public void
react_introduce(string person,string who)
{
   string *str_check;
   string gguild;
   string member_of;
   string dummy;
   string title;
   object ob;
   int i;
   if(person){
      person = lower_case(person);
      ob = present(person,environment());
      gguild=who;
      str_check = explode(who, " ");
      
      member_of="none";
      if(inguild("Army",gguild))
         {
         member_of = "a member of the Army of Angmar.";
      }
      if(inguild("Gladiator",gguild))
         {
         member_of="a Gladiator from Athas.";
      }
      if(ob->query_wiz_level())
          member_of=ob->query_title()+".";
      if(inguild("Overseer",gguild))
         {
        member_of="an Overseer of the Athasian Gladiators.";
      }
      if(inguild("Kaheda,",gguild))
         {
         member_of="a monk of the Kahedan faith.";
      }
      if(inguild("Calia",gguild))
         {
         member_of="a Calian warrior.";
      }
      if(inguild("Ranger",gguild))
         {
         member_of="a Ranger from the land of Gondor.";
      }
      if(inguild("Knight",gguild))
         {
         member_of="a Knight of Solamnia.";
      }
      if(inguild("Morgul,",gguild))
         {
         member_of="a Mage from Minas Morgul.";
      }
      if(inguild("Nazgul,",gguild))
         {
        if(inguild("Dragonarmy",gguild))
        {
            member_of="a visitor from the Dragonarmies of Krynn.";
        }

         member_of="a ring wraith, one of the nine, from "+
         "the tower of black sorcery.";
      }
      if ((str_check[0]=="himself" || str_check[0]=="herself") &&
            (sscanf(str_check[1],"as%s",dummy)))
      set_alarm(2.0,0.0,"intro_the_lord",person,member_of);
      if ((sizeof(str_check)>4) &&
            (str_check[0]=="himself") &&
         (str_check[1]=="to") &&
         (str_check[2]=="a") &&
         (str_check[3]=="noble") &&
         (str_check[4]=="terrifying"))
      set_alarm(2.0,0.0,"intro_the_lord",person,member_of);
   }
}

/*
 * Function name: intro_the_lord
 * Description  : the actual intro-doing part of the intro-function    
 * Arguments    : string person, string member_of        
 */
public void
intro_the_lord(string person,string member_of)
{
   object obj;
   object lord;
   int ran;
   if (!(lord=present("urian",environment(TO))))
      {
      command("emote announces in a low, chilling voice: "+
         "The High Lord is not present now. You may return later.");
      return;
   }
   if(obj = present(person, environment()))
      {
      if (member_of=="none") member_of="this "+obj->query_race_name()+".";
      command("emote says: My Lord, may I present "+
         C(obj->query_real_name())+", "+member_of);
      command("say "+C(obj->query_real_name())+
         ", this is our esteemed High Lord of Kabal.");
      command("introduce urian to "+obj->query_real_name());
      command("whisper "+obj->query_real_name()+
         " You may now show your respect to the Lord.");
      lord->command("offer "+obj->query_real_name());
   }
}


/*
* Function name: no_repeat_harm_spell
* Description  : Makes certain the harm spell is not constantly repeated.           
*/
public int
no_repeat_harm_spell()
{
    return 1;
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
    int     attacktype = random(1);
    int i;
    object *enemies = ({});
    object *enemy_list = ({}) ;
    object kill_enemy;
    
    if (attacktype == 0 || attacktype == 1)
    {
       if(!("/d/Kalad/common/specials/spells/shadowblink"
            ->has_spell_object(TO)))
       {
         /* Make certain he always keep shadowblink up. */
          command("cast shadowblink");
          return 1;
       }        
    
    /* We want to always attack the enemy with the lowest health */   
    object *enemies = ({}),
    *enemy_list = ({}),
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
    /* See if we want to cast a fireball or blind */
    if(!random(10))
    {
        command("cast blind " + kill_enemy->query_real_name()); 
        return 1;
    }
    
    // Cast the fireball
    command("cast fireball " + kill_enemy->query_real_name()); 
    return 1;    
    }
    
    return 0;
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


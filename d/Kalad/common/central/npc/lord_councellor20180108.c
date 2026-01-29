/*
The High Lords councellor, in the Citadel.
MADE BY: Korat
DATE: Feb 14 1995
*/

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
#include <stdproperties.h>
#include "/sys/wa_types.h"
#include "/sys/filter_funs.h"
#include "/sys/composite.h"
#include <comb_mag.h>

/* this is the room this npc will go to if he's soon dead. */
   
#define his_bedroom "/d/Kalad/common/central/citadel/cit24"

/* this is the mana each spell will draw when casted */

#define MANA_FIRE 30
#define MANA_FOG 50
#define MANA_SHIELD 50
#define MANA_CONTROL 50
#define MANA_DISSPELL 50
#define MANA_VAMPIRIC 50
#define NUMBER_OF_POTIONS 2

/* this is variables that checks if a spell is on or not */
   
int fog_is_on;
int shield_is_on;
int fire_is_on;
int done_moved;
int control_is_on;
int vampiric_is_on;
int potion;
object fog;
object dagger;


void
create_monster()
{
   set_name("shamein");
   add_name("mage");
   set_adj("thin");
   add_adj("sly");
   set_alignment(-500);
   set_knight_prestige(800);
   set_race_name("human");
   set_long("This thin human seems to be an important man to the High Lord. "+
      "You cannot see his face or hands at all, since he is covered in a "+
      "large darkened robe. All you notice from him is his shrill, weak voice "+
      "when he bends over to whisper into the High Lords ear.\n");
   set_stats(({45,110,90,160,140,140}));
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,60);
   set_skill(SS_WEP_KNIFE,100);
   set_skill(SS_AWARENESS,90);
   set_skill(SS_SPELLCRAFT,100);
   
   set_act_time(5);
   add_act(({"whisper urian something devillishly...","nod . urian"}));
   add_act("whisper urian something devillishly...");
   add_act(({"whisper urian something devillishly...","bow . urian"}));
   add_act("hmm");
   
   add_prop(NPC_M_NO_ACCEPT_GIVE,1);
   set_hitloc_unarmed(0, 50, 20, "head");
   set_hitloc_unarmed(1, 50, 80, "body");
   add_prop(LIVE_I_SEE_DARK, 20);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   trig_new("%w 'introduces' %s", "react_introduce");
   trig_new("%w 'attacks' %s","react_attack");
   fog_is_on = 0;
   shield_is_on = 0;
   fire_is_on = 0;
   done_moved = 0;
   potion = 0;
}
void
arm_me()
{
   object arm;
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/central/arm/councellor_robe");
   arm -> move(TO);
   dagger = clone_object("/d/Kalad/common/central/wep/councellor_dagger");
   dagger -> move(TO);
   MONEY_MAKE_GC(random(5)+2)->move(TO,1);
}


/* this function checks the presence of a word in a string */

inguild(string word,string str)
{
   string *text;
   int i;
   text = explode(str," ");
   for (i=0;i<sizeof(text);i++)
   if (text[i]==word) return 1;
   return 0;
}


/* this routine reacts to intro's, and will introduce */
/* the High Lord to the players. */

void
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

/* the actual intro-doing part of the intro-function. */

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


/* a function that will send messages in combat to the ones */
/* that want them */

tell_watcher(string str, object enemy)
{
   object me,*ob;
   int i;
   me = this_object();
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i=0;i<sizeof(ob);i++)
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}

/* the 'assist' function */
/* this npc will throw a fireball in the face of each attacker */
/* as a 'warm welcome' */

void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("fume");
      command("assist");
      set_alarm(1.0,0.0,"cast_fire",ob);
      command("whisper "+ob->query_the_name()+" Now you shall buurn!");
   }
}   

/* this function checks for someone attacking someone else. */
   
void
react_attack(string who,string dummy)
{
   string *str_check;
   string empty;
   object ob;
   if (who){
      who = lower_case(who);
      str_check = explode(dummy, " ");
      if ((sscanf(str_check[0],"you%s",empty)))
         {
         command("emote hisses chillingly: Fooools.");
         ob = present(who,environment(TO));
         set_alarm(1.0,0.0,"cast_fire",ob);
       }
   }
}

/* --------------------------------------------------------- */
/* the rest of the file is the combat specials of this */
/* npc. It is controlled through the 'special_attack()'. */
/* Each spell has two parts, with one 'cast_xxx' */
/* that will be called first. From that function, a */
/* 'make_xxx' will be called        */
/* that does the actual damage/spell-casting/fun? */
/* ---------------------------------------------------- */


/* this spell, 'controll', will try to take control of a */
/* players action. It will either make the player */
/* attack another player (enemy of the npc) or */
/* make the player run for its life.... */
   
cast_control(object ob, object at)
{
   if(!present(ob,environment(TO))) return;
   control_is_on = 1;
   command("emote gets some black rose leaves from his pouch.");
   command("emote throws the leaves at "+ob->query_nonmet_name()+
      " while chanting some ancient words.");
   set_alarm(6.0,0.0,"make_control",ob, at);
}

make_control(object who, object kill)
{
   if(present(who, environment(TO)))
      {
      command("whisper "+who->query_the_name()+
         " beee miiiine.");
      who->catch_msg("You feel a penetrating darkness fill your mind..\n");
      tell_watcher("The eyes of "+QTNAME(who)+
         " seems to grow black.\n", who);
      if (who->query_stat(SS_DIS) >
            (TO->query_stat(SS_DIS)+random(40)))
      {
         who->catch_msg("You manage to fight the darkness away...\n");
         tell_watcher("The eyes of "+QTNAME(who)+
            " seems to clear up again.\n",who);
         TO->command("emote screams up in dissapointment.");
         control_is_on = 0;
         return;
      }
      who->catch_msg("You fail to fight the darkness away...\n");
      TO->command("emote screams in a cruel delight!");
      TO->set_mana(TO->query_mana()-MANA_CONTROL);
      set_alarm(1.0,0.0,"result_of_casting");
      if (random(3) > 0)
         {
         who->catch_msg("A voice whispers to you: Kill !! "+
            "Kill the "+kill->query_race_name()+"!!! NOW!\n");
         who->attack_object(kill);
         who->attack_object(kill);
         set_alarm(20.0,0.0,"repeat_kill",who,kill);
         return;
      }
      else
         {
         who->catch_msg("The "+short()+" whispers to you: "+
            "Run, run for your liiifeeee!\n");
         who->command("open door");
         who->command("east");
         if (random(2)==0)
            {
            who->command("southeast");
            who->catch_msg("A voice whispers to you: Ruunnn...\n");
            who->command("south");
         }
         else
            {
            who->command("east");
            who->catch_msg("A voice whispers to you: Runnnn...\n");
            who->command("north");
         }
         who->command("panic");
         who->catch_msg("The voice seems to fade away...\n");
         who->command("puke");
         control_is_on = 0;
         who->add_panic(400);
         return;
      }
   }
   command("shout Ruuunnn fool! You cannot fight me!!");
   control_is_on = 0;
}


/* this function is an addition to the 'control' */
/* where the player is pushed to attack another player. */
/* this one does it once more */

repeat_kill(object who, object kill)
{
   if (present(who,environment(TO)))
      {
      if (present(kill, environment(who)))
         who->attack_object(kill);
   }
   control_is_on = 0;
}


/* This is the fireball-spell. Its the one that does damage */
/* while the rest does other things. Its aimed at _one_ player, */
/* and therefore pretty strong                  */

void
cast_fire(object ob)
{
   fire_is_on = 1;
   command("emote gets a red berry from his pouch.");
   command("emote eats the berry, while chanting in an ancient language.");
   command("emote points at "+ob->query_nonmet_name()+". "+
      "You think you see "+short()+"'s eyes glow with black flames.");
   set_alarm(6.0,0.0,"make_fire",ob);
}

/* this is a darkness spell. Its a fog, making it _very_ dark, since light */
/* in a fog does not really light things up */

void
cast_fog()
{
   fog_is_on = 1;
   command("emote fetches some ashes from a pouch.");
   command("emote rubs the ashes between his fingers, while chanting "+
      "some ancient words.");
   set_alarm(6.0,0.0,"make_fog");
}

/* this is a vampiric spell, that the mage uses on one of the
* guards, if present. It will draw 1000hp out of the guard,
   *  and put it in the mage, this npc.
*/

cast_vampiric(object victim)
{
   vampiric_is_on=1;
   command("emote whispers: Guard ... I need your strenght!");
   command("emote fetches a dragons tooth from his pouch.");
   victim->command("emote says: Yes, Councellor...");
   command("emote hits the guard in the neck with the tooth, while "+
      "chanting in an ancient language.");
   victim->command("emote screams up in pain.");
   set_alarm(4.0,0.0,"make_vampiric",victim);
}

make_vampiric(object victim)
{
   if (present("guard",environment()))
      {
      victim -> heal_hp(-500);
      command("emote seems to grow healthier as he drains the guard "+
         "of his lifeforce.");
      if (victim->query_hp()<=0)
         {
         victim->command("emote looks utterly devestated as his "+
            "lifeforce is sucked out.");
         victim->do_die(TO);
       }
      else
         {
         victim->command("emote looks very drained and less healthy.");
       }
      command("emote cackles evilly.");
      TO->set_mana(TO->query_mana()-MANA_VAMPIRIC);
      set_alarm(1.0,0.0,"result_of_casting");
      TO->heal_hp(500);
   }
   vampiric_is_on=0;
}


/* this is a magical shield, that the npc will only cast */
/* at the high lord when the high lord is getting */
/* some beating....                 */

cast_shield(object receiver)
{
   shield_is_on = 1;
   if(receiver->query_real_name()=="urian")
      {
      command("emote whispers chillingly: Yes, my Lord.");
      command("emote fetches a shred of steel from a pouch.");
      command("emote holds the shred above "+receiver->short()+
         ", while chanting some ancient words.");
   }
   else
      {
      command("emote fetches a shred of steel from a pouch.");
      command("emote holds the shred above his own head"+
         ", while chanting some ancient words.");
   }
   set_alarm(6.0,0.0,"make_shield", receiver);
}

make_shield(object receiver)
{
   object shield;
   float ftime;
   command("emote hand's grips hard around the shred, and you see it "+
      "starts to melt, dripping down on "+receiver->query_nonmet_name()+
      "'s head.");
   TO->set_mana(TO->query_mana()-MANA_SHIELD);
   
   /* This is nicked from the examples, and has been changed some */
   /* Halfmade by Korat */
   
    if (objectp(receiver) && NPMAGIC(receiver))
      {
      shield_is_on = 0;
      this_object()->catch_msg("Something prevents you from casting this spell.\n");
      return;
   }
   if (present("mag_shield_prot",receiver))
      {
      this_object()->catch_msg("Only one shield active at a time.\n");
      shield_is_on = 0;
      return;
   }
   seteuid(getuid(this_object()));
   shield = clone_object("/d/Kalad/common/central/obj/m_shield");
   ftime = itof(random(100)+100);
   shield->set_duration(ftime);
   shield->move(receiver);
   set_alarm(0.0,0.0,"result_of_casting");
   set_alarm(ftime,0.0,"remove_shield");
   tell_watcher(QTNAME(receiver)+" is suddenly enveloped by a glowing "+
      "forcefield!\n",receiver);
   receiver->command("wear all");
}

remove_shield()
{
   shield_is_on = 0;
}

void
make_fog()
{
   object room;
   float time;
   command("emote throws the ashes into the air. Suddenly a black "+
      "fog envelopes you.");
   TO->set_mana(TO->query_mana()-MANA_FOG);
   set_alarm(0.0,0.0,"result_of_casting");
   room = environment(TO);
   time = itof(random(40));
   fog = clone_object("/d/Kalad/common/central/obj/fog_object");
   fog -> move(room);
   set_alarm(20.0+(time),0.0,"remove_fog", room);
}

void
remove_fog(object where)
{
   if (present(fog, where))
      fog->remove_object();
   else
      command("say oops...no fog in that room :( ");
   tell_room(where,"The fog suddenly disperses.\n");
   fog_is_on = 0;
}

int
make_fire(object who)
{
   int penet;
   mixed* hitresult;
   string how;
   int say_what;
   object me;
   object ob; /* the enemy */
   me = this_object();
   ob = present(who, environment(TO));
   if(!objectp(ob))
      {
      command("emote laughs viciously as his enemy ran "+
         "away.");
      return 1;
   }
   penet= 600 + random(400);
   penet-= penet * ob->query_magic_res(MAGIC_I_RES_FIRE)/50;
   hitresult = ob->hit_me(penet, MAGIC_DT, me, -1);
   how = "not harmed";
   if (hitresult[0] >0)
      how = "slightly burned";
   if (hitresult[0] > 10)
      how = "burned";
   if (hitresult[0] > 20)
      how = "burned quite badly";
   if (hitresult[0] > 40)
      how = "burned very badly";
   if (hitresult[0] > 60)
      how = "utterly devastated";
   ob->catch_msg("You hear a rhytmic chanting and then a deadly "+
      "eruption of hellish fire shoots forth from the wizard's hands at you!\n");
   ob->catch_msg("You were "+how+" by the hellish fire!\n");
   tell_watcher(QCTNAME(ob)+" is "+how+" by the hellish fire!\n", ob);
   if (ob->query_hp() <= 0)
      ob->do_die(me);
   fire_is_on = 0;
   TO->set_mana(TO->query_mana()-MANA_FIRE);
   set_alarm(0.0,0.0,"result_of_casting");
   
   /* here I have added some emotes according to the */
   /* damage the spell did. */
   
   if (hitresult[0]<10)
      {
      switch(say_what=random(10))
      {
         case 0:
         command("emote fumes angrily as his spell did little damage."); break;
         case 1:
         command("say Next time you will buuurn!"); break;
         case 2:
         command("emote roars: You will perish! "+
            "Do not think your luck will save you!"); break;
         case 3:
         command("emote sighs deeply."); break;
         case 4..6:
         if (ob->query_race_name()=="human") break;
         command("emote fumes: You will perish, "+ob->query_race_name()+
            "! Mark my wordsss...");
         tell_room(environment(TO),"The eyes of "+short()+
            " glows of pure hatred.\n");
         break;
         default: break;
       }
   }
   if (hitresult[0]>25)
      {
      switch (say_what=random(10))
      {
         case 0:
         command("emote laughs viciously as he sees the flames "+
            "envelope "+ob->query_nonmet_name()+".");
         break;
         case 1:
         command("emote looks at "+ob->query_nonmet_name()+
            " with death in his eyes.");
         break;
         case 2:
         command("say Your death is close, "+ob->query_race_name()+"!");
         break;
         case 3:
         command("emote laughs hysterically as the flames consume "+
            "his victim.");
         break;
         case 4..6:
         if (ob->query_race_name()=="human") break;
         command("emote whispers with the voice of death: "+
            "And now you will die, "+ob->query_race_name()+
            ", like all of your kind deserves!");
         break;
         default: break;
       }
   }
   return 1;
}

/* this function is called from each spell, when the */
/* spell is finnished. It will give the players */
/* an idea of how much mana the npc has left. */

result_of_casting()
{
   string how;
   int mana_left;
   mana_left = TO->query_mana();
   switch (mana_left*100/TO->query_max_mana())
   {
      case 0..10:     how="utterly devastated";  break;
      case 11..20:    how="extremely exhausted"; break;
      case 21..30:    how="very exhausted";      break;
      case 31..40:    how="exhausted";           break;
      case 41..50:    how="extremely tired";     break;
      case 51..60:    how="very tired";          break;
      case 61..70:    how="tired";               break;
      case 71..80:    how="a little tired";      break;
      case 81..90:    how="not affected at all"; break;
      default:        how="chillingly fit";      break;
   }
   TO->catch_msg("You feel "+how+" after casting the spell.\n");
   tell_watcher("The "+short()+" looks "+how+" after "+
      "casting the spell.\n",this_object());
   if (mana_left<200)
      
   /* This npc also has some potions that he will quaff */
   /* when the mana is getting low. The potions will */
   /* add mana.  These potions are _not_ objects that  */
   /* the player can gettheir hands on.         */
   
   {
      potion=potion+1;
      if (potion>NUMBER_OF_POTIONS) return;
      TO->set_mana(mana_left+400);
      say(QCTNAME(TO)+" quaffs a potion, and suddenly looks "+
         "less exhausted!\n");
   }
}


/* the combat engine  */

public special_attack(object enemy)
{
   object me, lord, guard;
   object *enemies;
   object to_kill, to_control;
   int to_do;
   int me_hp, lord_hp;
   me = this_object();
   lord = present("urian",environment(me));
   guard = present("guard",environment(me));
   if (lord)
   {
      lord->command("assist");
      lord_hp = lord->query_hp();
   }
   me_hp = me->query_hp();
   
   /* if the npc had left the battle scene, this is done: */
      /* The npc will, if a player enters the room, either be attacked */
      /* or will attack himself. He will then */
   /* use his last powers to chant a spell that makes the spellbook */
   /* to explode. All players & npc's in the room */
   /* will be penaltied with -1000 hp.   */
   /* and this npc will die. */
   
   if (done_moved)
      {
      command("emote gets his spellbook from the table.");
      command("emote opens the book and lifts it above his head.");
      command("shout My death will be YOUURRSSS!!");
      command("emote starts to chant in an ancient language.");
      set_alarm(3.0,0.0,"do_kill_me");
      return 1;
   }
   
   /* if this npc's hp is below 500, he will leave the battle */
      
   if (me_hp < 500)
      {
      if (lord)
         lord->command("shout Shamein! Leave or they will kill you!!");
      if (!done_moved)
         {
         me->command("emote curses you all with the wrath of Thanar.");
         me->command("emote closes his eyes, wraps the black robe around "+
            "his body and chants in an ancient language.");
         TO->add_hp(1000);
         set_alarm(3.0,0.0,"leave_battle");
         return 1;
       }
   }
   
/* force the guard to close the door */
   if(objectp(guard) && random(4)>2)
   {
      TO->command("say Someone close that door! Do not let them escape their death!!");
      TO->command("close door");
   }

   /* if not more than 50 in mana left, no more spells */
      
   if (me->query_mana()<55)
      {
      set_alarm(0.0,0.0,"show_dissappointment");
      if(dagger->query_wielded() != me) command("wield dagger");
      return 0;
   }
   
   /* If less than 4000 hp's left, then maybe do a vampiric
   * spell.
   */
   
   if ((me_hp<2000) && !vampiric_is_on && random(2)==1)
      {
      if (objectp(guard))
         {
         set_alarm(0.0,0.0,"cast_vampiric",guard);
         return 1;
       }
   }
   
   /* if the lord is alive, check his hp and make a shield in case its low. */
      
   if (lord)
      {
      if (lord_hp<3000 && !shield_is_on)
         {
         lord->command("emote screams at the sly human: "+
            "I need a shield of power!");
         shield_is_on = 1;
         set_alarm(0.0,0.0,"cast_shield",lord);
         return 1;
       }
   }
   
   /* if the lord is gone, and the hp is below 3000 then add a shield */
      
   if(!lord && me_hp<2000 && !shield_is_on)
      {
      shield_is_on = 1;
      command("emote curses you all but with a glint of "+
         "cruel delight in his eyes.");
      set_alarm(0.0,0.0,"cast_shield",me);
      return 1;
   }
   
   /* this is the spell-casting machine */
   
   to_do = random(10);
   
   /* maybe a fire-spell ? */
   
   if (to_do > 5 && (fire_is_on == 0))
      {
      set_alarm(0.0,0.0,"cast_fire",enemy);
      return 1;
   }
   
   /* maybe a fog-spell ? */
   
   if ((to_do==1 || to_do==2) && fog_is_on==0)
      {
      set_alarm(0.0,0.0,"cast_fog");
      return 1;
   }
   
   /* maybe a control-spell ? */
   
   if ((to_do ==3 || to_do == 4) && !control_is_on)
      {
      enemies = ({});
      if (lord)
         {
         enemies=lord->query_enemy(-1);
       }
      else
         {
         if (sizeof(me->query_enemy(-1))>sizeof(enemies))
            enemies = me-> query_enemy(-1);
       }
      if (sizeof(enemies)==1)
         {
         return 1;
       }
      if (sizeof(enemies)==2)
         {
         to_kill = enemies[0];
         to_control = enemies[1];
         set_alarm(0.0,0.0,"cast_control",to_control,to_kill);
         return 1;
       }

    if (sizeof(enemies)>1)
    {
      to_kill = enemies[0];
      to_control = enemies[random(sizeof(enemies)-1)+1];
      set_alarm(0.0,0.0,"cast_control",to_control,to_kill);
      return 1;
    }
   }
   return 1;
}

/* This part gives an emote to the npc, showing
* his hate/etch. for the attackers. This happens when he's outof mana.
*/

show_dissappointment()
{
   switch (random(10))
   {
      case 0: command("emote cries: I have failed!");
      break;
      case 1: command("emote curses you all with the wrath of Thanar.");
      break;
      case 2: command("emote cries up aloud as his powers has dried up.");
      break;
      case 3: command("emote groans: You may win this battle, but death "+
         "shall win over you too one day!"); break;
      case 4: command("emote tries to avoid your attacks.");
      break;
      case 5: command("emote stretches his hands up into the air.");
      command("emote cries to some unseen force: Thanar! Grant me "+
         "more power to slay these pheasants!");
      break;
      default: command("emote tries to cast a spell, but is too weak.");
      break;
   }
}


/* this does the actual 'leaving of the battle' that */
/* happens when the hp is below 500 */

leave_battle()
{
   command("emote suddenly starts to melt away, leaving behind a thick "+
      "black fog that slowly drifts towards the door. Soon it is gone.");
   TO->move_living("dissapearing",his_bedroom);
   done_moved = 1;
}

/* this does the spellbook-damage, and kills this npc. */

do_kill_me()
{
   object *people;
   int i;
   command("emote suddenly stops the chanting.");
   command("emote grins with death in his eyes as his spellbook starts to "+
      "glow!");
   tell_room(environment(TO),"The spellbook explodes!\n");
   people=FILTER_LIVE(all_inventory(environment(TO)));
   for (i=0;i<sizeof(people);i++)
   {
      people[i]->set_hp(people[i]->query_hp()-1000);
      people[i]->catch_msg("You were badly damaged as the black "+
         "flames from the explosion licks around your body!\n");
      if (people[i]->query_hp()<=0) people[i]->do_die(TO);
   }
   if (TO->query_hp()>0) TO->set_hp(0);
   if (!TO->query_attack())
      {
      set_alarm(0.0,0.0,"remove_object",TO);
   }
   else
      {
      TO->do_die(TO->query_attack());
   }
}

/* this starts if this npc dies, and removes the fog if it exists */
   
do_die(object killer)
{
   if (query_hp()>0) return;
   if (fog)
      {
      tell_room(environment(fog),"The black fog suddenly disperses.\n");
      fog->remove_object();
   }
   ::do_die(killer);
}

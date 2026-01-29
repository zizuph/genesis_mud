/* Name      : /d/Gondor/harondor/room/camp/npc/chief.c
 * Purpose   : The chief of the camp.
 * Created by: Sir Toby, Gondor Domain, 2006-03.02
 *
 *   Modified: Sir Toby, Gondor Domain, 2006-07-31
 *             Sir Toby, Gondor Domain, 2006-08-14
 *                       Added support for MM talking to it.
 *             Sir Toby, Gondor Domain, 2006-08-18
 *                       Added support to recieve things
 *                       and give back if unwanted.
 *             Sir Toby, Gondor Domain, 2006-08-23
 *                       Fixed handling of being given more
 *                       then 1 pebble and how he chats.
 *             Sir Toby, Gondor Domain, 2006-08-28
 *                       He now actually responds correctly
 *                       if a player has already solved the q.
 *             Sir Toby, Gondor Domain, 2006-12-05
 *                       Added getuid stuff to the logging
 *             Eowul, 2008-10-12
 *                       Changed the haradrim race to human
 *             Eowul, 2008-10-17
 *                       Changed the non functioning trig_new to
 *                       catch_question
 */

/*
 prestige awarded in Ithilien

 object                     alignment  prestige
 Haradrim Captain (Army)   -350..-600      1200
 Haradrim Warrior (Army)   -200..-400       800
 Mordor Orc                -100..-300       575
 Mordor Orc Captain        -200..-450       800

 Camp:
 Uruk                      -200..-400       600
 Orc                       -100..-300       370
 Haradrim                  -200..-440       500
 Cook                      -250..-406       500
 
 Harondor:
 Haradrim                  -300..-500      1000

 */


inherit "/std/monster";
inherit "/d/Gondor/harondor/room/camp/npc/npc_intro";

#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <const.h>

#include "/d/Gondor/harondor/room/camp/defs.h"
#include "/d/Gondor/common/lib/logkill.c"
#include "/d/Gondor/bits.h"


void			help_friend(object ob);
public varargs int	move_living(string how, mixed to_dest,
				    int dont_follow, int no_glance);
public void		destroy_eyes();

/******************************
 * Quest related defines etc. *
 ******************************/
int check_darkness();
int chief_talking = 0;
int accept_item = 1;
int just_cloned = 1;
void accept_new_items();
void chief_talk_clear();
void update_just_cloned();
int chief_questions(string question);

#define GROUPBIT1      HARONDOR_CHIEF_GROUP
#define BIT1           HARONDOR_CHIEF_Q1
#define QUEST_REWARD   HARONDOR_CHIEF_EXP
#define PEBBLES_TGT    16
#define PEBBLES_REWARD 300  //Reward for good alignen players

#define LOGDIR "/d/Gondor/private/log/quests/"

#define WORKING_ON_Q "working_on_harondor_chief_pebbles_quest"

#define DEBUG(x) find_player("toby")->catch_msg("[DEBUG - harondor chief]: " + x + "\n")



void
create_monster()
{
   set_living_name("coul-mahlu");

   add_name("coul-mahlu");
   add_name(({"warrior","southron","man", "human", "haradrim warrior", "chief", "haradrim chief"}));
   set_pname("haradrim");
   add_pname(({"warriors", "southrons", "men", "humans", "haradrim warriors"}));
   set_race_name("human");
   /* ahn toh Pon'Fuuzah is family name, but for simplicity added in set_title */
   set_title("ahn toh Pon'Fuuzah toh Xae Balo'Korneth");
   set_adj("stocky");
   add_adj("wild-eyed");
   set_short("stocky wild-eyed male haradrim");

   set_gender(G_MALE);

   set_long("A stocky, wild-eyed male haradrim. " +
         "His deep-set, wild, almost-black eyes staring intensly at " +
         "you, practically unblinking, from under his helmet like " +
         "twin caves from within another deep cave. Well-built, tattooed " +
         "arms and stout hands tightly grip both weapon " +
         "and shield. His stance is balanced and relaxed at the same time. " +
         "He is wearing a grand stole over his shoulders made of fine wool, " +
         "decorated with bones och various sizes and feathers in bright colors.\n");

   set_alignment(-300-random(200));

   default_config_npc(170+random(10));    
   set_base_stat(SS_CON,             180 + random(10));
   set_base_stat(SS_DIS,             180 + random(10));
   set_skill(SS_WEP_SWORD,           100);
   set_skill(SS_WEP_POLEARM,          80);
   set_skill(SS_PARRY,               100);
   set_skill(SS_DEFENCE,              80);
   set_skill(SS_AWARENESS,            60);
   set_skill(SS_UNARM_COMBAT,         75);
   set_skill(SS_PROTECT_TEAM_MEMBER,  90);   
   add_prop(CONT_I_HEIGHT,   203);
   add_prop(CONT_I_WEIGHT, 89000);
   add_prop(CONT_I_VOLUME, 93000);
   
   set_chat_time(250+random(100));
   add_chat("Where are these ridiculous Dunedain? Did they all flee?");
   add_chat("What news do you bring from the north?");
   add_chat("What did I do to deserve checking on the lazy lot this far north?");
   add_chat("I whish I had something to fight, I hate this tedious waiting!");
   
   set_cchat_time(50+random(5));
   add_cchat("Take this, you maggot!");
   add_cchat("Stand still and fight, you miserable lout!"); 
   add_cchat("Let me kill you quickly, maggot, it will hardly hurt!");
   
   set_act_time(200+random(150));
   add_act("glare");
   add_act("hiss");
   add_act("grin delight");
   add_act("emote suddenly stands absolutely still staring into nothingness.");
   
   set_cact_time(50+random(50));
   add_cact("scream"); 
   add_cact("growl");
   add_cact("shout Die, you snivelling child of a troll!");

   /* If arm me for some reason fails, this will kick in and allow to recieve items for q */
   set_alarm(30.0, 0.0, &update_just_cloned());

   remove_prop(NPC_M_NO_ACCEPT_GIVE);
}


void
update_just_cloned()
{ just_cloned = 0; }

void
get_money()
{
   MONEY_MAKE_CC(140 + random(260))->move(TO);
   MONEY_MAKE_SC(50 + random(30))->move(TO);
   MONEY_MAKE_GC(20 + random(10))->move(TO);
}

void
arm_me()
{
   FIX_EUID
   
   clone_object(HAR_RM_WEP_DIR + 
        one_of_list(({"seax", "hc_scimitar"})))->move(TO);
   command("wield weapon");
   
   clone_object(HAR_RM_ARM_DIR + "bhauberk")->move(TO);
   command("wear hauberk");
   
   clone_object(HAR_RM_ARM_DIR + "luna")->move(TO);
   command("wear shield");
   
//   clone_object(HAR_RM_ARM_DIR + "helmet")->move(TO);
//   command("wear helmet");

   clone_object("/d/Gondor/ithilien/forest/harad_earring")->move(TO);
   command("wear earrings");
   
   get_money();

   set_alarm(3.0, 0.0, &update_just_cloned());
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
   object *arr;
   int i;
   
   /* work with finding leader and make a new function in npc disband_team and making 
    * this npc call it and become the leader and take charge.
    */

   ::attacked_by(ob);
   
   arr = (object *)query_team_others();
   for (i = 0; i < sizeof(arr); i++)
   arr[i]->notify_ob_attacked_me(this_object(), ob);
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
   if (query_attack())
      return;
   
   if (random(10))
      set_alarm(rnd()*5.0, 0.0, &help_friend(attacker));
}

int
query_show_list(object x)
{
    return !((x->query_no_show()) || (x->query_prop(OBJ_I_INVIS)));
}


/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
   object *loot_list;

   if (ob &&
       !query_attack() &&
       interactive(ob) &&
       ENV(ob) == ENV(TO))
   {
      loot_list = filter(all_inventory(ob), query_show_list);
      if (sizeof(loot_list))
      {
        command("say I will aid you in killing "+OBJECTIVE(ob)+", I want to have "+
	  POSSESSIVE(ob) + " " + 
	  (ONE_OF_LIST(loot_list))->short() + "!");
      }
      else
      {
        command("say I will aid you in killing "+OBJECTIVE(ob)+"!");
      }
      command("kill " + lower_case(ob->query_real_name()));
      command("spit " + lower_case(ob->query_real_name()));
   }
}


int query_knight_prestige() { return 1050; }


/*
 * Function name:	move_living
 * Description	:	mask parent so we can check new env for spying eyes
 * Arguments	:	string how -- direction of travel, etc
 *			mixed to_dest -- destination
 *			int dont_follow -- flag re group movement
 *			int no_glance -- flag re looking in new room
 * Returns	:	int -- 0 on success, non-0 on failure
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int rval;
    rval = ::move_living(how, to_dest, dont_follow, no_glance);

    if (objectp(present("eye", ENV(TO))))
    {
	set_alarm(2.0, 0.0, destroy_eyes);
    }
    return rval;
} /* move_living */

/*
 * Function name:	destroy_eyes
 * Description	:	smash any spying eyes in env
 */
public void
destroy_eyes()
{
    object	*eyes;
    int		s;

    s = sizeof(eyes = filter(all_inventory(ENV(TO)), &->id("eye")));
    if (s > 0)
    {
	command("emote smashes the glass eye" +
	    (s > 1 ? "s." : "."));
	eyes->remove_object();
    }
} /* destroy_eyes */


/****************************************************************
 ****************************************************************
 **         Here follows the quest support for the NPC         **
 ****************************************************************
 ***************************************************************/

/* Add support to try revealing anyone hidden entering environment!
   If NPC still can not see the check_hidden() will kick in.
 */


/*
 * Function name:   check_hidden
 * Description	:   Checks if a player is hidden. The NPC (chief)  
 *                  will not speak with hidden players.
 *                  Should irritate sneakers... =o)
 * Arguments	:   None
 * Returns	    :   int 1: Can not see player
 *                  int 0: Can see player
 */
int
check_hidden()
{

   if (!CAN_SEE(this_object(), this_player()))
   {   
       command("shout I can not see you. Reveal your presence or I will not " +
               "speak to you, you spittle of a desert snake!");
       command("frown");
       return 1;
    }

    return 0;
}

/*
 * Function name:   check_can_see
 * Description	:   Can the NPC see in the room?
 * Arguments	:   
 * Returns	    :   int -- 0 on success, non-0 on failure
 */
int
check_can_see()
{
   if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
   {
      command("shout Who goes there? Where are you? I can not see you, you child " +
              "of a ragged goat!");
      command("mumble irritably");

      return 1;
   }

   return check_darkness();
}

/*
 * Function name:   
 * Description	:   
 * Arguments	:   
 * Returns	    :   int -- 0 on success, non-0 on failure
 */
int
check_darkness()
{
   if(environment(this_object())->query_prop(ROOM_I_LIGHT) < 1)
   {
      command("say What is this!? I can se almost clearly though it should be dark!");
      command("say Foul magic, or other, at play here if you ask me!");
      command("frown");
      command("say I do not make deals while under influence of magic nor strong brews!");
      command("ponder");
      command("say Come back later and we shall see.");

      return 1;
   }

   return 0;   
}


void
enter_inv(object ob, object from)
{
    set_alarmv(0.1, 0.0, "enter_inventory", ({ob, from}));
    ::enter_inv(ob, from);
}

void
enter_inventory(object ob, object from)
{
    int exp_to_give, q_bit, num_pebbles;
    string quest_info;

    if(just_cloned)
       return;

    if(ob->id("Black breath"))
       return;

    /* item given to this_object() is indeed a pebble or heap of them. */

    if ( (ob->id("_harondor_pebble_chief_quest_part_I")) && (accept_item) )
    {
       /* Ok, we change this prop to 0 so the chief does not begin 
        * chatting for every pebble he recieves. We also make a call
        * that in a few seconds he will once again accept pebbles.
        */
       accept_item = 0; 
       set_alarm(2.0, 0.0, &accept_new_items());

       /* Is the player on the task at all?
        */
       if(!(from->query_prop(WORKING_ON_Q)))
       {
          command("grumble .");
          set_alarm(2.0, 0.0, &command("say Whats this???"));
          set_alarm(5.0, 0.0, &command("say Why would I even bother to keep things like this?"));
          set_alarm(7.0, 0.0, &command("frown . "));
          set_alarm(10.0, 0.0, &command("say What do you take me for? A savage?"));
          set_alarm(12.0, 0.0, &command("say Now, be off and do not disturb me any further."));
          set_alarm(17.0, 0.0, &command("give pebbles to " + lower_case(from->query_name())));
          set_alarm(17.0, 0.0, &command("drop pebbles"));
          return;
       }

       q_bit = from->test_bit("Gondor", HARONDOR_CHIEF_GROUP, HARONDOR_CHIEF_Q1);

       /* Check if the player have already done the solved task.
        */
       if (q_bit)
       {
          if(TP->query_guild_name_occ() == "Morgul Mages" || TP->query_wiz_level())
          {
             command("say My Lord, bringing me more pebbles is all very fine, but it " +
                     "will not earn you more favour or rewards.");
             command("give pebbles to " + lower_case(from->query_name()));
             command("drop pebbles");
             return;
          }

          command("say Bringing me more pebbles will not earn you more favour or rewards.");
          command("give pebbles to " + lower_case(from->query_name()));
          command("drop pebbles");
          return;
       }

       /* Now lets see if it is 16 pebbles or more... */

       num_pebbles = sizeof(filter(all_inventory(), &->id("pebble")));
       
       if(num_pebbles < PEBBLES_TGT)
       {
          command("grumble .");
         
          if(TP->query_guild_name_occ() == "Morgul Mages" || TP->query_wiz_level())
          {
             set_alarm(2.0, 0.0, &command("say Whats this?"));
             set_alarm(5.0, 0.0, &command("say Ahh, my Lord, I need more than " + num_pebbles +
                                          " as a proof of the cleanup."));
             set_alarm(8.0, 0.0, &command("say I am sorry for this inconvenience."));
             set_alarm(12.0, 0.0, &command("say I look forward to see you soon again, my Lord."));
          }
          else
          {
             set_alarm(2.0, 0.0, &command("say Whats this???"));
             set_alarm(5.0, 0.0, &command("say You call this cleaning up?"));
             set_alarm(7.0, 0.0, &command("frown . "));
             set_alarm(10.0, 0.0, &command("say Bringing me " + num_pebbles + " pitiful pebbles."));
             set_alarm(12.0, 0.0, &command("say Now, be off and do not come back with this feeble collection again."));
          }

          set_alarm(17.0, 0.0, &command("give pebbles to " + lower_case(from->query_name())));
          set_alarm(17.0, 0.0, &command("drop pebbles"));
          return;
       }

       /* Task is indeed solved.
        */
       if(TP->query_guild_name_occ() == "Morgul Mages" || TP->query_wiz_level())
       {
          command("smile .");
          set_alarm(2.0, 0.0, &command("say Oh, you have indeed cleaned the path for me, my Lord!"));
          set_alarm(5.0, 0.0, &command("say Now I only think it suitable to give you a just reward."));
          set_alarm(7.0, 0.0, &command("bow . "));
          set_alarm(10.0, 0.0, &command("say Just one moment, my Lord."));
       }
       else
       {
          command("laugh .");
          set_alarm(2.0, 0.0, &command("say Oh, you have indeed cleaned the path for me..."));
          set_alarm(5.0, 0.0, &command("say Now I gather you stick arround for a reward."));
          set_alarm(7.0, 0.0, &command("grumble . "));
          set_alarm(10.0, 0.0, &command("say Well, here you go now be off."));
       }

       set_alarm(14.0, 0.0, &tell_object(from, "The chief looks straight at you with his haughty eyes and " +
                             "makes a gesture midair and suddenly you feel slightly more experienced.\n"));
       set_alarm(12.0, 0.0, &command("say I may have use of you in the future again, remember that."));
       set_alarm(16.0, 0.0, &command("give pebbles to " + lower_case(from->query_name())));
       set_alarm(16.0, 0.0, &command("drop pebbles"));
       set_alarm(24.0, 0.0, &command("emote returns to his previous occupation."));
       
       exp_to_give = QUEST_REWARD;

       if(from->query_align() > 200)
          exp_to_give += 200;

       /* A check to not give out more exp than the player already
        * got. This is not doing any good here because of the low
        * amount of exp given out by these small tasks but just
        * in case.
        */
       if( from->query_exp() < (exp_to_give * (QUEST_FACTOR / 10)) )
           exp_to_give = (from->query_exp() / (QUEST_FACTOR / 10));
    
       /* Lets hand out the exp! */
       from->add_exp(exp_to_give, 0);
       from->set_bit(HARONDOR_CHIEF_GROUP, HARONDOR_CHIEF_Q1);
       
       /* Clear the prop working on q */
       from->remove_prop(WORKING_ON_Q);


     /* Log the quest... */
       setuid();
       seteuid(getuid());
       LOG_QUEST(from, exp_to_give, "HARONDOR_CHIEF_Q1 PEBBLES");

   }
   else if(accept_item)
   {
      accept_item = 0; 
      set_alarm(2.0, 0.0, &accept_new_items());

      command("say Bah, what do I need this for?");
      command("drop " + ob->query_short());
      command("drop pebbles");
   }
}

void accept_new_items()
{ accept_item = 1; }

int
catch_question(string question)
{
    int q_bit;

    /* Check on different darkness states... */

    if(check_can_see())
       return 1;

    if(check_hidden())
       return 1;

    if(check_darkness())
       return 1;

    
    /* Answer ordinary questions, previously added in add_ask();
     */

    if(chief_talking)
    {
       if(TP->query_guild_name_occ() == "Morgul Mages" || TP->query_wiz_level())
       {
          command("say My Lord, please do allow me to finish.");
          return 1;
       }
       else
       {
          command("say My Lady, please do allow me to finish.");
          return 1;
       }

       command("say Shut up and listen!");
       set_alarm(1.0, 0.0, &command("frown ."));
       return 1;
    }
    
    chief_talking = 1;
    set_alarm(21.0, 0.0, &chief_talk_clear()); /* A backup if all other checks fail */

    if (question == "task" || question == "quest" || question == "help")
    {
         /* The player wants a task.
          */
       q_bit = TP->test_bit("Gondor", HARONDOR_CHIEF_GROUP, HARONDOR_CHIEF_Q1);

       if(!(TP->query_guild_name_occ() == "Morgul Mages") && !TP->query_wiz_level())
       {
          /* Player already solved the task? */

          if (q_bit)
          {
              command("say You again!?");
              set_alarm(1.5, 0.0, &command("say I am busy and do not have more work for you presently."));
              set_alarm(3.5, 0.0, &command("mumble"));
              set_alarm(7.5, 0.0, &command("say Do check back in the future though."));
              set_alarm(7.5, 0.0, &chief_talk_clear());
              return 1;
          }

          /* Player already working on the task? */

          if (this_player()->query_prop(WORKING_ON_Q))
          {
              command("say First complete the darn task I gave you before maggot!");
              set_alarm(1.5, 0.0, &command("say I am busy enough without snot faces like you scurrying about."));
              set_alarm(3.5, 0.0, &command("emote mutters about those pebbles clogging the trail."));
              set_alarm(7.5, 0.0, &command("frown savage"));
              set_alarm(7.5, 0.0, &chief_talk_clear());
              return 1;
          }

          command("say Hmm.. So you seek my attention and a task... Very well, let me think.");
          set_alarm(2.5, 0.0, &command("emote appears in thought and suddenly burst into laughing loudly."));
          set_alarm(6.0, 0.0, &command("emote turns his eyes to you staring intensly from the depth of his face."));
          set_alarm(8.5, 0.0, &command("chuckle dark"));
          set_alarm(11.0, 0.0, &command("say Go clean up the trails leading to the camp..."));
          set_alarm(12.5, 0.0, &command("say Now hurry!"));
          set_alarm(15.5, 0.0, &command("emote gestures to the exit and motions you to leave."));
          set_alarm(17.0, 0.0, &command("shout Return only when you have a handful!"));
          set_alarm(17.0, 0.0, &chief_talk_clear());
      	  return 1;
       }
       else
       {
          command("emote bows his head respectfully.");

          /* Player already solved the task? */

          if (q_bit)
          {
              command("say My Lord, it is nice to have you visiting me again.");
              set_alarm(2.0, 0.0, &command("say Alas, I have no more tasks for you presently."));
              set_alarm(5.0, 0.0, &command("say Do not hesitate to check every now and then in the future now."));
              set_alarm(7.5, 0.0, &command("say May the never blinking eye bless you!"));
              set_alarm(7.5, 0.0, &chief_talk_clear());
              return 1;
          }

          /* Player already working on the task? */

          if (this_player()->query_prop(WORKING_ON_Q))
          {
              command("say You first need to complete the task you are working on.");
              set_alarm(1.5, 0.0, &command("say No disrespect intended of course."));
              set_alarm(4.5, 0.0, &command("emote mutters about those pebbles clogging the trail."));
              set_alarm(4.5, 0.0, &chief_talk_clear());
              return 1;
          }

          // if all ranks as below Of course my lord nazgul, a task etc.. then the same
          set_alarm(2.0, 0.0, &command("say Of course, my Lord."));


          set_alarm(6.0, 0.0, &command("say Yes, a task... It appears the trails leading to the camp have been " +
                           "left in a state not tolerable."));
          set_alarm(8.5, 0.0, &command("say What if enemies approach and follows the trail of pebbles laying about?"));
          set_alarm(11.0, 0.0, &command("say I need help clearing these pebbles from the trail."));
          set_alarm(13.5, 0.0, &command("say Apparently my own men can not do it!"));
          set_alarm(14.5, 0.0, &command("frown"));
          set_alarm(18.0, 0.0, &command("say Do this, return with a handful, and I shall reward you accordingly."));
          set_alarm(21.0, 0.0, &command("bow ."));
          set_alarm(21.0, 0.0, &chief_talk_clear());
       }
    }
    else
       chief_questions(question);

    TP->add_prop(WORKING_ON_Q, 1);
    return 1;
}


/* A function to clear him from status talking to use in set_alarm */
void chief_talk_clear()
{ chief_talking = 0; }


/*********************************************************************
 * All other questions except task/quest/help will be answered here. *
 *********************************************************************/

void chief_questions(string question)
{
   /* 
    * Apprentices - on barely equal level
    * Mages - my lord
    * Necromancers - respectful
    * Nazgul - Obvious...
    *
    * TP->query_morgul_level() will return the current lvl of the mage.
    *
    *    Levels  0-12 are Apprentices
    *    Levels 13-20 are Mages
    *    Levels 21-23 are Necromancers
    *    Level     24 is the Lieutenant
    *    Level   < 25 are Archmages
    *
    * TP->query_nazgul()
    *    Level 1 - Nazgul
    *    Level 2 - Lord of the Nazgul
    *
    */

   if ( (question == "minas morgul"))
   {
      command("say Ahh, Minas Morgul, is that city not something extraordinary!?");
      set_alarm(2.5, 0.0, &command("say Though I must confess the orcs can be quite rude..."));
      set_alarm(4.0, 0.0, &command("say But what to expect?"));
      set_alarm(8.0, 0.0, &command("say Be wary though! His presence is always there! Never blinking!"));
      set_alarm(9.5, 0.0, &command("laugh wild"));
      set_alarm(9.5, 0.0, &chief_talk_clear());
      return;
   }

   if ( (question == "minas tirith"))
   {
      command("say Minas Tirith you ask!? City of Gondor, hah!");
      set_alarm(3.0, 0.0, &command("say Those worms inhabiting that place should soon enough learn their place."));
      set_alarm(6.0, 0.0, &command("say They can not hide behind those walls forever you know!"));
      set_alarm(8.0, 0.0, &command("say The lidless eye is ever watching!"));
      set_alarm(9.0, 0.0, &command("laugh loud"));
      set_alarm(9.0, 0.0, &chief_talk_clear());
      return;
   }

   if ( (question == "ithilien"))
   {
      command("say Yes, yes... Ithilien, we have scouts up there.");
      set_alarm(2.5, 0.0, &command("say Made camp they have... Sending reports back, thats more slow."));
      set_alarm(4.0, 0.0, &command("say But what to expect of the one they set in charge?"));
      set_alarm(8.0, 0.0, &command("say I will deal with him another day."));
      set_alarm(9.5, 0.0, &command("smile grim"));
      set_alarm(9.5, 0.0, &chief_talk_clear());
      return;
   }

   if ( (question == "morgul vale"))
   {
      command("say Aha, interested are we... I will tell you this.");
      set_alarm(3.5, 0.0, &command("say Have you reached the Morgul Vale you are close to Him and His elite."));
      set_alarm(6.0, 0.0, &command("say You should tread lightly and not stray from roads and paths, lest " +
                                   "you seek His attention!"));
      set_alarm(8.0, 0.0, &command("say Perhaps be it so that you seek death, fool?"));
      set_alarm(9.5, 0.0, &command("chuckle grim"));
      set_alarm(10.0, 0.0, &command("say By the look of you, I would not doubt it.")); 
      set_alarm(10.0, 0.0, &chief_talk_clear());
      return;
   }
    
   if(TP->query_guild_name_occ() == "Morgul Mages" || TP->query_wiz_level())
   {
      if(!TP->query_morgul_level())
      {
         if(TP->query_gender() == G_MALE)
         {
            command("say My Lord, I would not even begin to dream that I would possess more knowledge then you " +
                    "in what you ask of me. Perhaps I may offer a task that may aid you in your travels " +
                    "throughout the realm?");  
            set_alarm(2.0, 0.0, &command("bow respect"));
            set_alarm(2.0, 0.0, &chief_talk_clear());
         }
         else
         {
            command("say My Lady, I would not even begin to dream that I would possess more knowledge then you " +
                    "in what you ask of me. Perhaps I may offer a task that may aid you in your travels " +
                    "throughout the realm?");
            set_alarm(2.0, 0.0, &command("bow respect"));
            set_alarm(2.0, 0.0, &chief_talk_clear());
         }
      }
      else if(TP->query_nazgul() == 2)
      {
         command("emote turns towards you and bow his head respectfully.");
         set_alarm(1.5, 0.0, &command("emote proceeds with putting one knee down on the ground."));
         set_alarm(3.0, 0.0, &command("emote twitches ever so slightly at the corner of the eye before starting to speak."));

         if(TP->query_gender() == G_MALE)
         {
            set_alarm(5.0, 0.0, &command("say Praise the Lord of the Nazgul!"));
            set_alarm(7.0, 0.0, &command("say  My Lord, you honour me beyond belief with you presence."));
         }
         else
         {  
            set_alarm(5.0, 0.0, &command("say Praise the Lady of the Nazgul!"));
            set_alarm(7.0, 0.0, &command("say  My Lady, you honour me beyond belief with you presence."));
         }

         set_alarm(9.0, 0.0, &command("emote bows down further over his knee."));
         set_alarm(11.0, 0.0, &command("say I would not in my wildest dreams even begin to fathom that I would " +
                    "possess more knowledge then you in that of which you ask of me."));
         set_alarm(13.0, 0.0, &command("ponder the situation quickly."));
         set_alarm(17.0, 0.0, &command("say Perhaps, turulairi, I may offer a task that may aid you in your travels " +
                    "throughout the realm?"));
         set_alarm(18.5, 0.0, &command("bow respect"));
         set_alarm(18.5, 0.0, &chief_talk_clear());
      }
      else if(TP->query_nazgul() == 1)
      {
         command("emote turns towards you and bow his head respectfully.");
         set_alarm(1.5, 0.0, &command("emote twitches ever so slightly at the corner of the eye before starting to speak."));

         if(TP->query_gender() == G_MALE)
         {
            set_alarm(2.5, 0.0, &command("say My Lord Nazgul, you honour me with you presence, but alas I would not " +
                    "even begin to fathom that I would possess more knowledge then you in what you ask of me."));
         }
         else
         {  
            set_alarm(2.5, 0.0, &command("say My Lady Nazgul, you honour me with you presence, but alas I would not " +
                    "even begin to fathom that I would possess more knowledge then you in what you ask of me."));
         }

         set_alarm(4.0, 0.0, &command("say Perhaps, ulairi, I may offer a task that may aid you in your travels " +
                    "throughout the realm?"));
         set_alarm(5.0, 0.0, &command("bow respect"));
         set_alarm(5.0, 0.0, &chief_talk_clear());
      }
      else if(TP->query_morgul_level() > 24)
      {
         command("emote turns towards you and bow his head respectfully.");

         if(TP->query_gender() == G_MALE)
         {
            set_alarm(2.0, 0.0, &command("say My Lord Archmage, I am honoured. Alas I would not even begin to fathom " +
                    "that I would possess more knowledge then you in what you ask of me."));
            set_alarm(5.5, 0.0, &command("say Perhaps, my Lord, I may offer a task that may aid you in your travels " +
                    "throughout the realm?"));
         }
         else
         {
            set_alarm(2.0, 0.0, &command("say My Lady Archmage, I am honoured. Alas I would not even begin to fathom " +
                    "that I would possess more knowledge then you in what you ask of me."));
            set_alarm(5.5, 0.0, &command("say Perhaps, my Lady, I may offer a task that may aid you in your travels " +
                                         "throughout the realm?"));
         }

         set_alarm(7.0, 0.0, &command("bow respect"));
         set_alarm(7.0, 0.0, &chief_talk_clear());
      }
      else if(TP->query_morgul_level() == 24)
      {
         command("emote bows his head respectfully.");

         if(TP->query_gender() == G_MALE)
         {
            set_alarm(2.0, 0.0, &command("say I would not even begin to fathom that I would possess more knowledge then you, Lieutenant, " +
                    "in what you ask of me."));
            set_alarm(5.5, 0.0, &command("say Perhaps, my Lord, I may offer a task that may aid you in your travels " +
                    "throughout the realm?"));
         }
         else
         {  
            set_alarm(2.0, 0.0, &command("say I would not even begin to fathom that I would possess more knowledge then you , Lieutenant, " +
                    "in what you ask of me."));
            set_alarm(5.5, 0.0, &command("say Perhaps, my Lady, I may offer a task that may aid you in your travels " +
                    "throughout the realm?"));
         }

         set_alarm(7.0, 0.0, &command("bow respect"));
         set_alarm(7.0, 0.0, &chief_talk_clear());
      }
      else if(TP->query_morgul_level() > 20)
      {
         command("emote turns his attention to you.");

         if(TP->query_gender() == G_MALE)
         {
            set_alarm(2.0, 0.0, &command("say In what you ask of me I would not even begin to fathom that I would possess more knowledge " +
                    "then someone in your position, Necromancer."));
            set_alarm(6.0, 0.0, &command("say Perhaps, my Lord, I may offer a task that may aid  " +
                    "you in your travels throughout the realm?")); 
         }
         else
         {  
            set_alarm(2.0, 0.0, &command("say In what you ask of me I would not even begin to fathom that I would possess more knowledge " +
                    "then someone in your position, Necromancer."));
            set_alarm(6.0, 0.0, &command("say Perhaps, my Lady, I may offer a task that may aid  " +
                    "you in your travels throughout the realm?"));
         }

         set_alarm(7.5, 0.0, &command("bow deep"));
         set_alarm(7.5, 0.0, &chief_talk_clear());
      }
      else if(TP->query_morgul_level() > 12)
      {
         command("emote turns his attention to you.");

         if(TP->query_gender() == G_MALE)
         {
            set_alarm(2.0, 0.0, &command("say In what you ask of me I would not even begin to fathom that I would possess more knowledge " +
                    "then you, my Lord."));
            set_alarm(4.0, 0.0, &command("emote looks at you."));
            set_alarm(8.0, 0.0, &command("say Perhaps, my Lord, I may offer a task that may aid you in your travels " +
                    "throughout the realm?"));  
         }
         else
         {  
            set_alarm(2.0, 0.0, &command("say In what you ask of me I would not even begin to fathom that I would possess more knowledge " +
                    "then you, my Lady."));
            set_alarm(4.0, 0.0, &command("emote looks at you."));
            set_alarm(8.0, 0.0, &command("say Perhaps, my Lady, I may offer a task that may aid you in your travels " +
                    "throughout the realm?")); 
         }

         set_alarm(10.0, 0.0, &command("bow ."));
         set_alarm(10.0, 0.0, &chief_talk_clear());
      }
      else
      {
         command("emote turns his haughty eyes towards you and directs his attention to you.");

         set_alarm(2.0, 0.0, &command("say Greetings to you Apprentice."));
         set_alarm(4.0, 0.0, &command("say In what you ask of me I should not possess more knowledge then you"));
         set_alarm(8.0, 0.0, &command("emote looks thoughtfully at you with his haghty eyes."));
         set_alarm(13.0, 0.0, &command("say Perhaps I may offer a task that may aid you in your travels " +
                    "throughout the realm?"));  
         set_alarm(17.0, 0.0, &command("bow briefly"));
         set_alarm(17.0, 0.0, &chief_talk_clear());
      }
            
      return;
   }

   command("frown .");   
   set_alarm(1.5, 0.0, &command("say What are you talking about? Leave if you have nothing better to do than disturb me!"));
   set_alarm(1.5, 0.0, &chief_talk_clear());

   return;
}

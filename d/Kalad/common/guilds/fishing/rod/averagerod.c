 /*****************************************************************************
*  /d/Kalad/common/guilds/fishing/rod/averagerod.c
*
*  Rod File: Average Rod
*
*  Created June 2019, Greneth        
*
 *****************************************************************************/

 /*****************************************************************************
*  Defines
 *****************************************************************************/
#define FISH_PLAYER(t, s) set_alarm(t, 0.0, &write( s ))
#define FISH_TELLR(t, s) set_alarm(t, 0.0, &say( s ))

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include "/d/Kalad/common/guilds/fishing/defs.h"
 /*****************************************************************************
*  Inherits
 *****************************************************************************/
inherit "/std/object";
inherit "/lib/holdable_item";
 
 /*****************************************************************************
*  Pragma
 *****************************************************************************/
#pragma strict_types

 /*****************************************************************************
*  Prototypes
 *****************************************************************************/
public int          cast_rod(string str);
public int          bait_hook(string str);
public int          reel_rod(string str);

 /*****************************************************************************
*  Variables
 *****************************************************************************/
public int              Casted = 0;
public int              Baited = 0;
public int              Reeling = 0;
static int              fishing_alarm;
static int              reeling_alarm;


 /*****************************************************************************
*  Function name: create_object
*  Description  : Constructor for the object
 *****************************************************************************/
public void
create_object()
{
   ::create_object();

   set_name("rod");
   set_adj("average");
   add_adj("fishing");
   set_short("average fishing rod");
   set_long("This is just an average, everyday fishing rod. It's been carved "
   + "down to a smooth stick with a normal reel, line and hook at the end. If "
   + "someone was decently skilled in fishing they could probably catch a "
	+ "good amount of fish with this rod.\n");

   set_slots(W_ANYH);

   add_prop(OBJ_M_NO_SELL, "I've got no use for this.\n");
   add_prop(OBJ_I_WEIGHT, 3000);
   add_prop(OBJ_I_VOLUME, 850);

   setuid();
   seteuid(getuid());
}

 /*****************************************************************************
*  Function name: leave_env
*  Description  : Must have when creating a holdable item, allows you to drop
 *****************************************************************************/
void
leave_env(object env, object to)
{
   ::leave_env(env, to);
   holdable_item_leave_env(env, to);
}

 /*****************************************************************************
* Function name: hold
* Description  : mask of the parent function to perform a skill check
* Returns      : string - error message (not held)
*                     1 - success (held)
 *****************************************************************************/
public mixed
hold()
{
   if(this_player()->query_skill(SS_SWIM) < 25)
   {
      say(QCTNAME(TP) + " looks confused as they fumble with the "
      + short() + ".\n");

      return "You fumble with the " + short() + ".\n";
   }

   write("You hold the " + short() + " naturally.\n");
   say(QCTNAME(TP) + " holds the " + short() + " naturally.\n");

   return 1;
}


 /***************************************************************************** 
 * Function name: release
 * Description  : mask of the parent function
 * Returns      : int  0 - held normally.
 *                     1 - releases, but print no messages.
 *                    -1 - do not release, print default messages.
 *                string - do not release, use this fail message.
 *****************************************************************************/
public mixed
release()
{
   object holder;

   if(!objectp(holder = TO->query_holder()))
   {
      return 1;
   }

   holder->catch_tell("You release your grip on the " +
      short() + ".\n");
   tell_room(environment(holder),
      QCTNAME(holder) + " releases " + HIS(holder) + " grip on the " +
      short() + ".\n", holder);

   return 1;
}

 /*****************************************************************************
*  Function name: roll_fish
*  Description  : Skill checks and algorithm for chance to catch a fish
 *****************************************************************************/
public void
roll_fish()
{

int rand_roll, neg_roll, skill_bonus, roll;

rand_roll = random(100) + 1;
neg_roll = 10;
skill_bonus = 0 + (this_player()->query_skill(SS_SWIM));

//Check for Skill Bonus

switch (skill_bonus)
{
case 1..9:
   skill_bonus = 0;
   break;
    
case 10..19:
   skill_bonus = 1;
   break;

case 20..29:
   skill_bonus = random(2) + 1;
   break;

case 30..39:
   skill_bonus = random(3) + 1;
   break;
    
case 40..49:
   skill_bonus = random(4) + 1;
   break;
    
case 50..59:
   skill_bonus = random(5) + 1;
   break;
    
case 60..69:
   skill_bonus = random(6) + 1;
   break;
    
case 70..79:
   skill_bonus = random(7) + 1;
   break;
    
case 80..89:
   skill_bonus = random(8) + 1;
   break;
    
case 90..99:
   skill_bonus = random(9) + 1;
   break;
    
case 100:
   skill_bonus = random(10) + 1;
   break;
    
default:
   skill_bonus = 0;
}

// Debug/Test
find_player("greneth")->catch_vbfc("\nRandom Roll: " + rand_roll + "\n");
find_player("greneth")->catch_vbfc("\nNegative Roll: " + neg_roll + "\n");
find_player("greneth")->catch_vbfc("\nSkill Bonus: " + skill_bonus + "\n");

// Formula for chance to catch

roll = rand_roll - neg_roll + skill_bonus;
object cfish, ucfish, rfish, vrfish, ufish;
switch (roll)
{
case 1..40:

   cfish = clone_object(F_FISH + "cfish.c");
   cfish->move(TP);
   break;

case 41..80:

   ucfish = clone_object(F_FISH + "ucfish.c");
   ucfish->move(TP);
   break;

case 81..95:

   rfish = clone_object(F_FISH + "rfish.c");
   rfish->move(TP);
   break;

case 96..99:

   vrfish = clone_object(F_FISH + "vrfish.c");
   vrfish->move(TP);
   break;

case 100:

   ufish = clone_object(F_FISH + "ufish.c");
   ufish->move(TP);
   break;

default:

   cfish = clone_object(F_FISH + "cfish.c");
   cfish->move(TP);
   }

// Debug/Test
find_player("greneth")->catch_vbfc("\nTotal Roll: " + roll + "\n");
}

 /*****************************************************************************
*  Function name: catch_rod
*  Description  : Random roll based on the rod to catch something
 *****************************************************************************/
public void
catch_rod()
{ 
    
   int chance_catch;
    
   object cjunk;
    
   chance_catch = random(100);
    
   switch (chance_catch)
   {
      case 1..45:
      write ("You reel in your line but there is nothing on it. Drats!\n");
      say(QCTNAME(this_player()) + " reels in their line but there doesn't "
      + "seem to be anything on the hook.\n");
      break;
        
      case 46..75:
      write ("You reel in your line and find a fish on it!\n");
      say(QCTNAME(this_player()) + " reels in their line and it seems like "
      + "they've caught something!\n");
      roll_fish();
      break;
        
      case 76..100:
      write ("You reel in your line and find something odd on it...\n");
      say(QCTNAME(this_player()) + " reels in their line and it seems like "
      + "they've caught something!\n");
      cjunk = clone_object(F_OBJ + "junk");
      cjunk->move(TP);
      break;
        
      default:
      write ("You reel your line up and find nothing on it. Drats!\n");
      say(QCTNAME(this_player()) + " reels in their line but there doesn't "
      + "seem to be anything on the hook.\n");
   }

   Baited = 0;
   Casted = 0;
   Reeling = 0;
}

 /*****************************************************************************
*  Function name: init
*  Description  : Adds some actions
 *****************************************************************************/
public void
init()
{
   ::init();
   add_action(cast_rod, "cast");
   add_action(bait_hook, "bait");
   add_action(reel_rod, "reel");
}

 /*****************************************************************************
*  Function name: reeling_reset
*  Description  : Resets reeling so the plyer can do so again
*  Arguments    : string str - what the player typed after the verb
*  Returns      : 1 - success, 0 - failure
 *****************************************************************************/
public void
reeling_reset()
{
   Reeling = 0;
   write ("You can <reel rod> to try again.\n");
}

 /*****************************************************************************
*  Function name: apply_paralyze
*  Description  : Applies a paralyze with reeling exception
*  Arguments    : string str - what the player typed after the verb
*  Returns      : 1 - success, 0 - failure
 *****************************************************************************/
public void
apply_paralyze()
{
   object paralyze_object;

   paralyze_object = clone_object(F_OBJ + "fparalyze.c");
   paralyze_object->move(this_player(), 1);
}

 /*****************************************************************************
*  Function name: reel_rod
*  Description  : Reels in the rod
*  Arguments    : string str - what the player typed after the verb
*  Returns      : 1 - success, 0 - failure
 *****************************************************************************/
public int
reel_rod(string str)
{
   if (!Casted)
   {
      notify_fail("You need to first cast your line.\n");
      return 0;
   }
    
   if (Reeling)
   {
      notify_fail("You shouldn't reel in so quickly.\n");
      return 0;
   }
    
   int reel_chance;
    
   object paralyze_object;
    
   paralyze_object = present("fishing_paralyze_object", this_player());
    
   reel_chance = random(100);
    
   switch (reel_chance)
   {
      case 1..30:
      write ("You slowly reel in your rod a bit but nothing bites.\n");
      say(QCTNAME(this_player()) + " reels in their line a bit.\n");
      Reeling = 1;
      reeling_alarm = set_alarm(5.0, 0.0, &reeling_reset());
      break;
        
      case 31..60:
      write ("You give a small tug before letting the line go slack "
      + "again.\n");
      say(QCTNAME(this_player()) + " gives a small tug on their line.\n");
      Reeling = 1;
      reeling_alarm = set_alarm(5.0, 0.0, &reeling_reset());
      break;
        
      case 61..80:
      write ("Your rod jerks down a bit and you yank up hard... but "
      + "you were too hasty and the fish is gone!\n");
      say(QCTNAME(this_player()) + " yanks up hard on their line but "
		+ "they were too hasty and lost the fish!\n");
      set_alarm(0.0,0.0,&paralyze_object->remove_object(this_player()));
        
      Baited = 0;
      Casted = 0;
      Reeling = 0;
      break;
        
      case 81..100:
      write ("The tip of your rod begins to dip and you notice tension "
      + "on the line. You continue to reel in up to the dock...\n");
      Reeling = 1;
      set_alarm(5.0,0.0,&paralyze_object->remove_object(this_player()));
        
      set_alarm(5.0, 0.0, "catch_rod");
      break;
        
      default:
      write ("You slowly reel in your rod a bit but nothing bites.\n");
      say(QCTNAME(this_player()) + " reels in their line a bit.\n");
      Reeling = 1;
      reeling_alarm = set_alarm(5.0, 0.0, &reeling_reset());
   }
   return 1;
}   
    
 /*****************************************************************************
*  Function name: bait_hook
*  Description  : Attaches bait to the hook
*  Arguments    : string str - what the player typed after the verb
*  Returns      : 1 - success, 0 - failure
 *****************************************************************************/
public int
bait_hook(string str)
{
   object ebait;
   object *fbait; 
    
   setuid();
   seteuid(getuid());
    
   if(!strlen(str))
   {
      notify_fail("Bait what?\n");
      return 0;
   }
   
   if (str != "earthworm")
   {
      notify_fail("Bait what exactly?\n");
      return 0;
   }     
    
   fbait = filter(all_inventory(this_player()), &->id("_fishing_bait"));
   if(!sizeof(fbait))
   {
      notify_fail("You don't seem to have any bait on you.\n");
      return 0;
   }
    
   ebait = present("_earthworm_bait", this_player());
    
   if(!objectp(ebait))
   {
      notify_fail("You don't seem to have any earthworms on you.\n");
      return 0;
   }
    
   if(Baited)
   {
      notify_fail("You already have a piece of bait on your hook\n");
      return 0;
   }
        
   ebait->remove_object();
   write("You slide your bait on the small shiny hook at the end "
   + "of your line.\n");
   say(QCTNAME(this_player()) + " slides some bait on their hook.\n");
    
   Baited = 1;

   return 1;
}

 /*****************************************************************************
*  Function name: cast_rod
*  Description  : Lets the player cast their rod
*  Arguments    : string str - what the player typed after the verb
*  Returns      : 1 - success, 0 - failure
 *****************************************************************************/
public int
cast_rod(string str)
{
   object ifheld, paralyze_object, paralyze_object2;
        
   if(!objectp(ifheld = TO->query_holder()))
   {
      notify_fail("You must be holding the rod to cast.\n");
      return 0;
   }

   if(!environment(this_player())->query_prop(LIVE_I_CAN_FISH))
   {
      notify_fail("You cannot fish here.\n");
      return 0;
   }

   if(this_player()->query_skill(SS_SWIM) < 30)
   {
      notify_fail("The " + short() + " requires more skill to use.\n");
      return 0;
   }

   if (Casted)
   {   
      notify_fail("You have already cast your line!\n");
      return 0;
   }
    
   if (!Baited)
   {
      notify_fail("You must first bait your hook!\n");
      return 0;
   }

   write("You slowly cock your arm back and then whip the "
   + this_object()->query_short()+" forward casting your line.\n");
   say(QCTNAME(this_player()) + " cocks "
   + this_player()->query_possessive() + " arm back and then whips the "
   + this_object()->query_short()+" forward casting their line.\n");;

   FISH_PLAYER(3.0,"Your line flies a ways out before dropping down into "
   + "the water.\n\nPLOP!\n\n");
    
   FISH_PLAYER(6.0,"Your line is casted you should <reel rod> to try "
   + "and catch something.\n");
    
   if (!present("_fishing_paralyze_object2_", this_player()))
   {
      paralyze_object2 = clone_object(F_OBJ + "fparalyze2.c");
      paralyze_object2->move(this_player(), 1);
   }

   set_alarm(6.0,0.0,&paralyze_object2->remove_object(this_player()));
   set_alarm(6.0, 0.0, &apply_paralyze());

   Casted = 1;

   return 1;
}

 /*****************************************************************************
*  Function name: stop_fishing
*  Description  : Stops the fishing process
 *****************************************************************************/
varargs int
stop_fishing(mixed arg)
{
   if (fishing_alarm)
   {
      remove_alarm(fishing_alarm);
      fishing_alarm = 0;
         Reeling = 0;
         Casted = 0;
         Baited = 0;
      tell_room(environment(this_player()), QCTNAME(this_player())
      + " stops fishing.\n",this_player());
        
      return 0;
      }
   if (reeling_alarm)
   {
      remove_alarm(reeling_alarm);
      reeling_alarm = 0;
         Reeling = 0;
         Casted = 0;
         Baited = 0;
      tell_room(environment(this_player()), QCTNAME(this_player())
      + " stops fishing.\n",this_player());
        
      return 0;
      }
      return 0;
}
/*
 *    A pet that will follow you and your commands, as long as
 *    you feed it.
 *                          Tricky, 16-1-93
 */

/*
 * TO DO:
 *   Skills and randomness
 *   Add types of dogs
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/attack";
inherit "/std/act/chat";
inherit "/std/act/action";

#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"

#define HE		query_pronoun()
#define HIS		query_possessive()
#define HIM		query_objective()

int total_time, hungry_time, leave_time, leave_stage, leave_chance,
    needed_skill;
string thefunction, type, match, owner_name, my_name, my_living_name;

#define ATT_TEETH    0
#define ATT_CLAWS    1 

#define HIT_HEAD     0
#define HIT_BODY     1
#define HIT_TAIL     2
#define HIT_LFPAW    3
#define HIT_RFPAW    4
#define HIT_LBPAW    5
#define HIT_RBPAW    6

/* Prototypes */
void my_heart_beat();
void set_owner(string who);
void set_my_name(string str);

void
create_creature()
{
   if (!IS_CLONE)
      return;
   set_my_name("Abacus");
   set_race_name("labrador"); 
   set_gender(G_MALE);
   set_long("@@my_long");
   set_owner("tricky");

   set_stats(({ 8, 8, 8, 17, 17, 8 }));
   set_skill(SS_UNARM_COMBAT,"@@my_ucombat");
   set_skill(SS_DEFENCE,"@@my_defence");

   set_aggressive(0);
   set_attack_chance(0);

   set_skill(SS_DEFENCE, 5);
   
   set_attack_unarmed(ATT_TEETH,  8, 8,W_IMPALE, 70, "teeth");
   set_attack_unarmed(ATT_CLAWS,  8, 8, W_SLASH, 30, "claws");

   set_hitloc_unarmed(HIT_HEAD,  ({ 2, 2, 2, 2 }), 10, "head");
   set_hitloc_unarmed(HIT_BODY,  ({ 8, 8, 8, 8 }), 40, "body");
   set_hitloc_unarmed(HIT_LFPAW, ({ 8, 8, 8, 8 }), 15, "left front paw");
   set_hitloc_unarmed(HIT_RFPAW, ({ 8, 8, 8, 8 }), 15, "right front paw");
   set_hitloc_unarmed(HIT_LBPAW, ({ 8, 8, 8, 8 }), 05, "left rear paw");
   set_hitloc_unarmed(HIT_RBPAW, ({ 8, 8, 8, 8 }), 05, "right rear paw");
   set_hitloc_unarmed(HIT_TAIL,  ({ 8, 8, 8, 8 }), 10, "tail");

   add_prop(CONT_I_WEIGHT, 67000);  /* 67 Kg  */
   add_prop(CONT_I_VOLUME, 67000);  /* 67 Ltr */
   total_time = 0;
   hungry_time = 400;
   leave_time = 200;
   leave_stage = 6;
   leave_chance = 50;
   needed_skill = 0;
   set_tell_active(1);	/* activate catch_tell() */
}


/*
 * Function name:   set_hungry_time
 * Description:     Set the time it takes for a dog to become hungry
 * Arguments:       val: That time.
 */
void
set_hungry_time(int val)
{
    hungry_time = val;
}

/*
 * Function name:   set_leave_chance
 * Description:     Set the chance that the dog will leave when trying to
 *		    escape.
 * Arguments:       val: The chance.
 */
void
set_leave_chance(int val)
{
    leave_chance = val;
}

/*
 * Function name:   set_needed_skill
 * Description:     Set the skill you need to command this animal
 * Arguments:       val: That skill
 */
void
set_needed_skill(int val)
{
    needed_skill = val;
}

/*
 * Function name:   set_leave_chance
/*
 * Function name:   query_time_since_feed
 * Description:     The time since we have last been fed.
 * Returns:         That time.
 */
int
query_time_since_feed()
{
   return total_time;
}

/*
 * Function name:   set_leave_time
 * Description:     Return the time after which the dog will leave, after
 *                  it became hungry.
 * Arguments:       val: That time.
 */
void
set_leave_time(int val)
{
    leave_time = hungry_time + val;
}

/*
 * Function name:   set_leave_stage
 * Description:     Set the hungry_stage (0-5) in which the dog is
 *		    going to attempt to run away. 0 is not at all hungry,
 *		    5 is almost starved to death. If you set 6, then the
 *		    dog will leave automatically after being starved to
 *		    death.
 * Arguments:       val: the hungry_stage
 */
void
set_leave_stage(int val)
{
    if (val > 6)
        val = 6;
    leave_stage = val;
}

/*
 * Function name:   hungry_stage
 * Description:     return the 'degree of hungriness' of the dog
 * Returns:         a number ranging from 0 (not hungry) to 5 (ravenous)
 */
int
hungry_stage()
{
   int timeslice, total;

   timeslice = ((leave_time - hungry_time) / 5);
   total = query_time_since_feed();

   if (total < hungry_time)
      return 0;
   if (total < (hungry_time + timeslice))
      return 1;
   if (total < (hungry_time + 2*timeslice))
      return 2;
   if (total < (hungry_time + 3*timeslice))
      return 3;
   if (total < (hungry_time + 4*timeslice))
      return 4;
   else
      return 5;
}

/*
 * Function name:   my_long
 * Description:     Returns the long description, dependant of the current
 *                  'degree of hungriness' of the dog.
 * Returns:         The long description.
 */
string
my_long()
{
   int hungry;
   string the_long;

   the_long = "This is " + LANG_ADDART(query_race_name()) + ". ";

   hungry = hungry_stage();
   if (hungry == 0)
      the_long += "A content look comes from " + HIS + " eyes.";
   else if (hungry == 1)
      the_long += capitalize(HE) + " looks kind of hungry to you, though.";
   else if (hungry == 2)
      the_long += capitalize(HE) + "is not at all happy without " + HIS
                + " regular meal.";
   else if (hungry == 3)
      the_long += capitalize(HE)
                + " is stark raving mad from hunger, though.";
   else if (hungry == 4)
      the_long += capitalize(HE) + " looks as if " + HE
                + " is starving to death.";
   else if (hungry == 5)
      the_long += capitalize(HE)
                + " nearly starved to death and is about to leave.";

   return break_string(the_long + "\n", 70);
}



/*
 * Function name:   my_heart_beat
 * Description:     Makes the dog grow more hungry every heartbeat,
 *		    makes him help his owner in combat.
 */
void
my_heart_beat()
{
   object tmp, owner, target;
   mixed att;

   total_time++;

     set_follow(owner); /* Test by Dunstable */
   /* Follow the owner */
   if (!present(owner_name,environment()))
   {
      if(!(owner = find_player(owner_name)))
      {
         say(QCTNAME(this_object()) + " runs away in search for " + HIS
           + " owner.\n");
         remove_object();
      }
    say(QCTNAME(this_object()) + " follows " + QCTNAME(owner)+ "\n");
//    move(environment(owner));
      say(QCTNAME(this_object()) + " walks in.\n");
   }

   /* Are we neglected for too long? */
   if (total_time > leave_time)
   {
      tell_object(owner, "Since you neglected "
        + capitalize(my_name) + " too long, " + HE + " has left you.\n");
      say(QCTNAME(this_object()) + " leaves.\n");
      remove_object();
   }

   /* Are we hungry? */
   if (total_time > hungry_time)
   {
      /* Is there food to eat? */
      if (tmp = present("doggy_meal"))
      {
         tmp->remove_object();
         say(QCTNAME(this_object()) + " eats a meal.\n");
         total_time = 0;
      }
      else
      {
         int what;

         /* Are we about to go AWOL? */
         if (hungry_stage() >= leave_stage)
         {
            if (!random(leave_chance))
            {
               command("wave");
               tell_room(environment(), QCTNAME(this_object())
                       + " runs away and is gone forever.\n");
               remove_object();
               return;
            }
         }

         /* Show our discontent */
         what = random(100);
         if(what == 1)
            command("growl"); 
         else if(what == 2)
            command("groan"); 
         else if(what == 3)
            command("sulk"); 
         else if(what == 4)
            command("tackle " + owner_name); 
      }
   }

   /* Find out with who the owner is fighting, and help him a little */
   if(att = owner->query_enemy())
   {
      /* Filter out all non-npc characters */
      if (objectp(att))
         att = ({ att });

      att = filter(att, "is_npc");

      if (sizeof(att))
         target = att[0];
      else
         target = 0;

      if (target)
      {
         if (total_time > hungry_time)
         {
            if (!random(3))
               attack_object(target);
            else
            {
               target->stop_fight(this_object());
               stop_fight(target);
            }
         }
         else
            attack_object(target);
      }
   }
}

/*
 * Function name:   heart_beat
 * Description:     Perform all heart_beat routines. Simply taken from
 *                  living/heart_beat.c, since add_heart_beat won't work.
 * Arguments:       num: Number of lost heart beats, sent as argument
 *			 If num == 0, it's a normal heart_beat
static void
heart_beat(int num)
{
    int remove_id;

    add_age(num+1);

    remove_id=set_alarm(1.0, 0.0, &restart_heart());

    decr_tmp_stats(num);
    drink_heart_beat(num);
    heal_living(num);
    my_heart_beat();

    remove_alarm(remove_id);
}
 */

int
is_npc(object obj)
{
   return obj->query_npc();
}


/*
 * Function name:   set_owner
 * Description:     Set the name of our owner
 * Arguments:       who: The name of the owner
 */
void
set_owner(string who)
{
   if (!who) return;
   owner_name = lower_case(who);
}


/*
 * Function name:   set_my_name
 * Description:     Set the name as our new name and make up a unique
 *		    ID that can be used with find_living().
 * Arguments:       str: Our new name
 */
void
set_my_name(string str)
{
   int i;
   string name;

   i = 0;
   remove_name(({my_name,"dog","pet"}));	/* Remove the old names */

   my_name = lower_case(str);
   set_name(({my_name,"dog","pet"}));		/* Set the new names */
}

/*
 * Function name:   process_command
 * Description:     Filters a given command to see if we want to execute it.
 * Arguments:       arr: An array consisting of:
 *i	            str: The commandstring to check
 *		    tp:  The person who told us to do it. 
 */
void
process_command(mixed arr)
{
   string tmp, str;
   object tp;

   str = arr[0];
   tp = arr[1];

   if (!str)
      return;

   /* Do we really want to follow orders? */
   if (tp && tp->query_skill(SS_ANI_HANDL) < needed_skill)
   {
      tp->catch_msg(capitalize(my_name) + " doesn't seem to listen to you.\n");
      return;
   }

   /* Wield a weapon? Sorry... No can do. */
   if (sscanf(str,"wield %s", tmp))
   {
      tp->catch_msg(capitalize(my_name)
          + " looks at you with a weird look and seems to grin.\n");
      tell_room(environment(), QCTNAME(this_object()) + " looks weird at "
          + QCTNAME(this_player()) + ".\n", tp);
      return;
   }
   command(str);
}

/*
 * Function name:   refuse_obey
 * Description:     Show that we are not happy with the command given by
 *		    another person than our owner
 * Arguments:       who: The person who gave the command
 */
void
refuse_obey(string who)
{
  command("spit " + who);
  command("growl");
}

/*
 * Function name:   catch_tell
 * Description:     Catches the sounds of the world outside
 * Arguments:       str: The string that is heard
 */
void
catch_tell(string str)
{
   string var1, var2;

   if (!str)
      return;

   str = lower_case(str);

   if ((sscanf(str, "%s says: " + my_name + ", %s\n", var1, var2) == 2)
      || (sscanf(str, "%s says: pet, %s\n", var1 ,var2) == 2)
      || (sscanf(str, "%s says: dog, %s\n", var1 ,var2) == 2)
      || (sscanf(str, "%s says: " + query_race_name()
                    + ", %s\n", var1, var2) == 2)
      || (sscanf(str, "%s whispers to you: %s\n", var1, var2) == 2)
      || (sscanf(str, "%s tells you: %s\n", var1, var2) == 2))
   {
      var1 = lower_case(var1);
      if(var1 == owner_name)
         set_alarm(1.0, 0.0, &process_command(), ({var2,TP}));
      else
         set_alarm(1.0, 0.0, &refuse_obey(), var1);
   }
}


/*
 * Function name:   set_total_time
 * Description:     Set the time since the last feeding time
 * Arguments:       time: Just that.
 */
void
set_total_time(int time)
{
   total_time = time;
}

int
my_ucombat()
{
   return 20;
}

int
my_defence()
{
   return 20;
}

/*
 * Function name:   
 * Description:    
 * Arguments:      
 * Returns:        
 */

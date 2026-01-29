// -*-C++-*-
// Beast's Curse	
// creator(s):      Lilith, Aug - Sept 1996
// last update:            
// purpose:         Enacts the beast's curse:
//                  I curse you with loneliness and sorrow, palsy
//                  and pain; Water will soothe you not and food
//                  will strengthen you not; and your home will
//                  not admit you to rest.
//
// note:            This object will not allow a player to reset
//                  startloc, or eat, drink, or join/lead teams.
//                  Player will also occasionally unwield weapons.
//         
//                  There is a shadow associated with this object.
// bug(s):
// to-do:

inherit "/std/object";

#include "/d/Avenir/common/common.h"
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

#define ETO           environment(this_object())
#define START         "/d/Avenir/lilith/temp/beast/doom_room"
#define SUBLOC        "beast_curse_subloc"
#define CURSE_SHADOW  "/d/Avenir/lilith/temp/beast/curse_shadow"

int curse = 0;

object curse_shadow;

void curse_mess(object who);
void curse_em(object who);

string
query_auto_load()
{
   return MASTER + ":";
}

void
create_object()
{
   set_name("curse_of_beast");
   add_name("gift");
   set_adj("beast");
   set_short("curse of the Beast");

   set_no_show();

   add_prop(OBJ_M_NO_DROP, 1);
   add_prop(OBJ_M_NO_SELL, 1);
}

/*
 * Function name: enter_env
 * Description:   This function checks to see if its environment is
 *                a living, if so, activates the curse by calling
 *                curse_em() and sets the start location to the 
 *                beast's doom room.
 */
void
enter_env(object dest, object old)
{
   ::enter_env(dest, old);
   if (living(dest)) 
    { 
       curse_em(dest);
       curse_shadow = clone_object(CURSE_SHADOW);
       curse_shadow->shadow_me(dest);
       dest->set_temp_start_location(START); 
    }
}

/*
 * Function name: leave_env
 * Description:   This function checks to see if its environment is
 *                a living, if so, deactivates the curse by removing
 *                the curse alarm and then resets the start location
 *                to default.
 */
void
leave_env(object from, object to)
{
   ::leave_env(from, to);

   if (living(from)) 
    {
      from->remove_subloc(SUBLOC);
      curse_shadow->remove_shadow();
      if (curse) remove_alarm(curse);   
      from->set_temp_start_location(START); 
    }
}

/*
 *     Set the curse into motion 
 */
void
curse_em(object who)
{
   who->add_subloc(SUBLOC, this_object());
   curse = set_alarm(75.0, itof(50+random(10)), &curse_mess(who));
}


/*
 * Function name: lift_curse
 * Description:   This function should be called to 'cure' or 'lift'
 *                the curse from players.
 */
void
lift_curse(object who)
{
    who->catch_msg("The burden of the Beast's curse has "+
         "been lifted from your soul.\n");
    who->set_temp_start_location(who->query_default_start_location()); 
    TO->remove_object();
}

void
init()
{
   ::init();
     add_action("c_start", "start");
}

/*
 *     Can't change the start place!
 */
int
c_start(string str)
{
   if (!strlen(str))
      return 0;
   write("A cackle of profound amusement sounds in your ears.\n "+
      "The voice of the Beast rings inside your head: "+
      "Until my curse is lifted, your home will not admit "+
      "you to rest! You will awaken where -I- decide.\n");
   return 1;
}
/*
 *
 *     Can't eat anything!
 *
int
c_eat(string str)
{
   if (!strlen(str))
      return 0;
   write("Though hungry, you cannot bring yourself to eat "+
      "the slightest thing. Your stomach rolls about, and "+
      "you feel the urge to vomit.\n");
   return 1;
}

 * 
 *     Can't drink or sip anything!
 *
int 
c_drink(string str)
{
   if (!strlen(str))
      return 0;
   write("Your throat is parched and dry for lack of moisture, "+
      "yet you cannot drink.\nThe voice of the Beast rings "+
      "inside your head: Water will soothe you not! Until the "+
      "curse is lifted, you are doomed to thirst.\n");   
   return 1;
}

 *
 *     Cannot join or lead a team!
 *
int
c_invite(string str)
{
   write("A triumphant voice rings inside your head: "+
      "The penalty for your blasphemy is loneliness! "+
      "I will not permit you the company of others...\n");
   return 1;
}
*/

/*
 *     Remind the player of the terms of the curse
 */
void
haunt(object who)
{
    switch(random(5))
    {
      case 0:
         who->catch_msg("A disembodied voice whispers into your ear: "+
              "I curse you with loneliness and sorrow...loneliness "+
              "and sorrow...\n"); 
         break;
      case 1:
         who->catch_msg("A disembodied voice whispers into your ear: "+
              "Water will soothe you not, and food will strengthen "+
              "you not...\n");
         break;
      case 2:
         who->catch_msg("A disembodied voice whispers into your ear: "+
              "The doors of your home will not admit you to rest...\n");
         break;

      case 3:
         who->catch_msg("A disembodied voice whispers into your ear: "+
              "I will teach you to invade my sanctuary!\n");
         break;
      case 4:
         who->catch_msg("A disembodied voice whispers into your ear: "+
              "Repent your blasphemous act, and I will lift this "+
              "curse from you.\n");
         break;
      default:
         break;
    }
}

/*    
 *     Give hints as to how the curse may be removed
 */
void
hint(object who)
{

}

/*
 *   Check to see if they've got weapons in their hands,
 *   and make them drop them if they do
 */
void
palsy(object who)
{
   if (who->query_weapon(W_BOTH)) 
     {
       who->catch_msg("Your hands tremble and shake, forcing "+
           "you to drop your weapon.");
       who->command("$drop weapon");
       return;
     }
   if (who->query_weapon(W_RIGHT)) 
     {
       who->catch_msg("The palm of your right hand begins burning "+
           "intensely!\n");
       who->command("$drop weapon");
       return;
     }
   if (who->query_weapon(W_LEFT)) 
     {
       who->catch_msg("The fingers of your left hand bend unnat"+ 
            "urally and painfully backwards!\n");
       who->command("$drop weapon");
       return;
     }
  
   who->catch_msg("You tremble and shake in a fit of palsy.\n");
   tell_room(ENV(who), QCTNAME(who) + " trembles and shakes "+
       "in a fit of palsy.\n", who);
}
/*
 *     Torment player with phantom pains
 */
void
pain(object who)
{
   tell_room(ENV(who), QCTNAME(who) + " appears to be caught in "+
        "the throes of a terrible pain!\n", who);

    switch(random(4))
    {
      case 0:
         who->catch_msg("You feel as though something is despera"+
            "tely trying to claw its way out of you!\n");
        break;
      case 1:
         who->catch_msg("What horrible pain! Your head aches as "+
            "though you had been hit with a stone.\n");
        break;
      case 2:
         who->catch_msg("There is a sudden burning in your side, "+
            "as if you had been raked with sharp claws!\n");
        break;
      case 3:
         who->catch_msg("An unseen hand seems to grip you, squee"+
            "zing so hard your bones pop and you cannot breathe!\n");
        break;
      default:
         break;
    }
}

/*    
 *     Taunt and insult the player
 */
void
taunt(object who)
{
    switch(random(5))
    {
      case 0:
         who->catch_msg("A disembodied voice whispers into your ear: "+
              "Ah, what deliciously wicked things I have planned for "+
              "you, my pet...\n");
         break;
      case 1:
         who->catch_msg("A small insect with the face of the Beast "+
              "buzzes up to you. In a tiny voice it says: You cannot "+
              "escape me.\n");
         break;
      case 2:
         who->catch_msg("A disembodied voice whispers into your ear: "+
             "You are nothing. You are less than nothing. You are "+
             "but a blemish on a troloby's arse.\n");
         break;
      case 3:
         who->catch_msg("A disembodied voice whispers into your ear: "+
              "Torment is a delightful past-time. I shall enjoy haunt"+
              "ing you for the rest of your days.\n");
         break;
      case 4:
        who->catch_msg("A disembodied voice whispers into your ear: "+
             "Shall I make you weak? Shall I strip you of you skills "+
             "and leave you a beggar in the streets?\n");
        break;
      default:
         break;
    }
}

/*
 *   Torment the player
 */
torment(object who)
{
    switch(random(5))
    {
      case 0:
         who->catch_msg("A terrible hunger claws at you.\n");
        break;
      case 1:
         who->catch_msg("Your throat is dry and burning.\n");
        break;
      case 2:
         who->catch_msg("A wave of sadness crashes over you.\n");
        break;
      case 3:
         who->catch_msg("Dread and forboding are your eternal "+
              "companions.\n");
         break;
      case 4:
         who->catch_msg("The putrid scent of death and decay fills "+
              "your nostrils.\n");
         who->command("$gag");
      default:
         break;
    }
}

/*
 *     Something to make others wonder what's going on &
 *     Remind the player that he's not alone after all 
 */
void
visit(object who)
{
    switch(random(4))
    {
      case 0:
         tell_room(ENV(who), "A huge pair of slitted eyes materialize "+
              "in the air before you.\n");
         break;
      case 1:
         who->catch_msg("An invisible hand grips your upper arm.\n"+
              "Someone whispers: Are you afraid? You should be!\n");     
         break;
      case 2:
         tell_room(ENV(who), "The ground erupts with fire! It "+
              "coalesces into a single flaming hand that reaches "+
              "for you!\n");
         break;
      case 3:
         tell_room(ENV(who), "A dark, roiling cloud glides "+
              "toward you.\nSudden, eerie laughter erupts from "+
              "the cloud, and lightning flashes.\n");
         break;
      default:
         break;
    }

}

/*   
 *     Randomly give out the curse messages
 */
void
curse_mess(object who)
{
   if (!who) return;
   
   switch (random(7))
   {
      case 0:
         haunt(who);
         break;
      case 1:
         hint(who);
         break;
      case 2:
         pain(who);
         break;
      case 3:
         palsy(who);
         break;
      case 4:
         taunt(who);
         break;
      case 5:
         torment(who); 
         break;
      case 6:
         visit(who); 
         break;
      default:
         break;
   }
}


string
show_subloc(string subloc, object carrier, object for_obj)
{
   string str;

   if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   if (for_obj == carrier)
      str = "The curse of the Beast enshrouds you, weighing "+
            "heavily upon your soul.\n";
   return str;

}

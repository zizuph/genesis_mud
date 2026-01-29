/*
 *    The hidingplace for Hin Warriors. The moment they move, it will
 *    be detected by the catch_tell(), which will make this object to
 *    throw that person back out again.
 */

inherit "/std/mobile";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"

object insider, obj, tmp_obj, tmp_inv, att_obj;
string the_enemy, insider_name;
int heard_movement;

/* Prototypes */
void my_heart_beat();

void
create_mobile()
{
   add_prop(OBJ_I_NO_GET,1);            /* Ungettable                */
   add_prop(CONT_I_VOLUME, 30000);      /* Small own volume (30 ltr) */
   add_prop(CONT_I_MAX_VOLUME, 300000); /* Big cont volume (270 ltr) */
   add_prop(CONT_I_WEIGHT, 30000);      /* Small own weight (30 Kg)  */
   add_prop(CONT_I_MAX_WEIGHT, 300000); /* Big cont weight (270 Kg)  */
   add_prop(CONT_I_TRANSP, 1);          /* You can see through it    */
   add_prop(LIVE_I_NEVERKNOWN, 1);      /* You never know this one   */
   add_prop(MAGIC_I_INVIS, 1);          /* Invisible by pure magic   */
   add_prop(OBJ_I_INVIS, 1);            /* Invisible by itself       */
   add_prop(ROOM_I_IS, 1);              /* In a way, this is a room  */
   set_name(({"hidingplace","hp"}));
   set_short("hidingplace");
   set_long("This is a hidingplace the ought to be invisible.\n");

   heard_movement = 0;
   insider_name = "";
   the_enemy = "";
   insider = 0;
}

void
init_living()
{
   if (!(this_player()->query_real_name() == insider_name))
   {
      add_action("do_enter","enter");
      return;
   }
   if(environment(this_player()) == this_object())
   {
      write("You can make yourself visible again with 'move'.\n");
      add_action("look","look");
      add_action("look","examine");
      add_action("look","exa");
      add_action("do_move","move");
      add_action("false_move","north");
      add_action("false_move","northeast");
      add_action("false_move","east");
      add_action("false_move","southeast");
      add_action("false_move","south");
      add_action("false_move","southwest");
      add_action("false_move","west");
      add_action("false_move","northwest");
      add_action("false_move","up");
      add_action("false_move","down");
   }
}

int
do_move(string str)
{
   if (str)
      return 0;
   heard_movement = 1;
   return 1;
}


int
false_move(string str)
{
   if (str) return 0;
   write("You must make a move first!\n");
   return 1;
}


/*
 * Function name:   heart_beat
 * Description:     Perform all heart_beat routines. Simply taken from
 *                  living/heart_beat.c, since add_heart_beat won't work.
 * Arguments:       num: Number of lost heart beats, sent as argument
 *			 If num == 0, it's a normal heart_beat
 */
static void
heart_beat(int num)
{
    add_age(num+1);

    call_out("restart_heart",1);

/*  Not needed for the hidingplace
    decr_tmp_stats(num);
    drink_heart_beat(num);
    heal_living(num);
*/
    my_heart_beat();

    remove_call_out("restart_heart");
}

/* TO DO: Revise everything below this line */

/*
 * Function name:   my_heart_beat
 * Description:     All kinds of things can go wrong when a player hides.
 *                  This function checks if she still is inside, if she
 *                  made a noise and if so, throws her out, and finally
 *                  removes itself.
 */
void
my_heart_beat()
{
   object enemy;

   if (insider_name != "")
   {
      if (insider = present(insider_name,this_object()))
      {
         if (heard_movement)
         {
            say(QCTNAME(insider) + " makes a movement and is visible again.\n");
            insider->move(environment());
            insider->catch_msg("You make a movement and are visible again.\n");

            /* Make the enemy (if any) attack the insider again */
            if ((the_enemy != "") && (enemy = present(the_enemy,environment())))
               enemy->attacked_by(insider);
            remove_object();
            return;
         }
      } 
      else
      {
         remove_object();
         return;
      }
   }
}

void
set_enemy(string en)
{
   the_enemy = en;
}

void
set_insider(string name)
{
   insider_name = name;
}

do_enter() {
   object tp, enemy, *ob_arr;
   int i;

   tp = this_player();
   set_insider(tp->query_real_name());
   
   if (enemy = tp->query_attack())
      set_enemy(enemy->query_real_name()); /* Remember the name of enemy */

   tp->stop_fight(ob_arr = tp->query_enemy(-1));

   if (!ob_arr)
      ob_arr = ({ });
   else if (objectp(ob_arr))
      ob_arr = ({ ob_arr });

   for (i=0; i < sizeof(ob_arr); i++)
       ob_arr[i]->stop_fight(tp);

   /* Perform tricks to move the player */
   tp->add_prop(OBJ_I_NO_GET,0);
   tp->move(this_object());
   tp->add_prop(OBJ_I_NO_GET,1);
   return 1;
}

/*
 * Idea: Make this monster look at it.
 */
int
look(string str)
{
   if (!str)
       command(query_verb());
   else
       command(query_verb() + " " + str);
   return 1;
}


void
catch_tell(string str)
{
   find_player("tricky")->catch_msg("HP: " + str);
   if(this_player() == insider)
   {
      tell_room(environment(),str);
      heard_movement = 1;
      return;
   }
   if (insider && present(insider,this_object()))
      tell_object(insider, str);
/*
   else
      remove_object();
*/
}

/*
 * Idea: What about leave_env and enter_env?
 */

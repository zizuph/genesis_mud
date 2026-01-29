inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
//  Prototypes
void half_way();
void self_destruct();
int  query_time_left();


mixed no_m_att, no_att;
int destruct_id, half_way_id;

void
create_object() {
   set_name(({"statue","statuette","statuette of nob nar"}));
   set_short("statuette of Nob Nar");
   set_pshort("statuettes of Nob Nar");
   set_long(break_string(
      "You are looking at the statuette of the Great Nob Nar, "
    + "founder of the glorious Hin Warrior Guild. An air of "
    + "peace and tranquility emanates from the statue.\n", 70));

   add_prop(OBJ_M_NO_GET,"@@my_get");
   add_prop(OBJ_S_WIZINFO,"@@wizinfo");
}

string
my_get() {
   object tp;

   tp = this_player();
   say(QCTNAME(tp) + " is struck by a lightning bolt for trying "
     + "to steal the statuette.\n",tp);

   /*
    * Do 10% damage as punishment. Bananaman, being a suicidal maniac,
    * asked for this. ;-)
    */
   tp->heal_hp(-1);
   return "You are struck by a lightning bolt when you try to get the "
        + "statuette.\n";
}

/*
 * Function name:   make_peace
 * Description:     Stop all fighting in the room and set properties
 *                  to make sure it stays peacefully.
 * Arguments:       active_time: The number of seconds the peace has to last.
 */
void
make_peace(int active_time) {
   object *ob_arr, env;
   int i;

   ob_arr = all_inventory(env = environment());
   ob_arr = filter(ob_arr,"filter_living",this_object());

   /* Make 'em all stop */
   for (i=0; i < sizeof(ob_arr); i++)
      ob_arr[i]->stop_fight(ob_arr);

   no_att = env->query_prop_settings(ROOM_I_NO_ATTACK);
   no_m_att = env->query_prop_settings(ROOM_I_NO_MAGIC_ATTACK);
   env->add_prop(ROOM_I_NO_ATTACK, 1);
   env->add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   half_way_id = set_alarm(itof((active_time*3)/4),0.0,&half_way());
   destruct_id = set_alarm(itof(active_time),0.0,&self_destruct());
}

int
filter_living(object obj)
{
   return living(obj);
}

void
half_way() {
   remove_alarm(half_way_id);
   tell_room(environment(),
      "The statue starts to show some cracks on its surface.\n");
}

int
remove_object() {
   object env;

   if (env = environment())
   {
      env->add_prop(ROOM_I_NO_ATTACK, no_att);
      env->add_prop(ROOM_I_NO_MAGIC_ATTACK, no_m_att);
      tell_room(env, break_string(
         "The statue crumbles and falls apart. The air of peace and "
       + "tranquility is gone.\n", 70));
   }
   ::remove_object();
}

void
self_destruct() {
    remove_alarm(destruct_id);
   remove_object();
}

string
wizinfo() {
   return break_string(
     "This statuette is a magic object brought about by the Hin Warrior "+
     "peace spell. It will fall apart in "+query_time_left()+
    " seconds.\n",70);
/*
      "This statuette ensures the peace in this room. It will fall apart in "
    + query_time_left() + " seconds.\n",70);
*/
}

int
query_time_left()
{
   mixed *call;

   call = get_alarm(destruct_id);
   return ftoi(call[2]);
}


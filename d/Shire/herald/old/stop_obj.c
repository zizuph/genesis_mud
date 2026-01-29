#pragma save_binary

inherit "/std/object";

#include "/d/Shire/common/defs.h"
#include "herald.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

//    Prototypes
void half_way();
void self_destruct();
int query_time_left();

int half_id, destruct_id;
int no_m_att, no_att;

void
create_object() {
   set_name("_orome_peace_");
   set_short("Orome Peace Object");
   set_long("This should never be seen.\n");

   add_prop(OBJ_M_NO_GET, 1);
   add_prop(OBJ_S_WIZINFO,"@@wizinfo");

   set_no_show();
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

   no_att = env->query_prop(ROOM_I_NO_ATTACK);
   no_m_att = env->query_prop(ROOM_I_NO_MAGIC_ATTACK);
   env->add_prop(ROOM_I_NO_ATTACK, 1);
   env->add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   half_id = set_alarm(itof((active_time*3)/4),0.0,&half_way());
   destruct_id = set_alarm(itof(active_time),0.0,&self_destruct());
}

int
filter_living(object obj)
{
   return living(obj);
}

void
half_way() {
   /*
    * This is an error; a light check should be made! If there is no
    * light, this message looks stupid.
    */
   tell_room(environment(),
   "The mood in the room seems to lift a little.\n");
}

int
remove_object() {
   object env;

   if (env = environment())
   {
      env->add_prop(ROOM_I_NO_ATTACK, no_att);
      env->add_prop(ROOM_I_NO_MAGIC_ATTACK, no_m_att);
      /*
       * This is an error; a light check should be made! If there is no
       * light, this message looks stupid.
       */
      tell_room(env, break_string(
     "The solemn mood in the room has disappeared.  The air of peace and "
       + "tranquility is gone.\n", 70));
   }
   remove_alarm(half_id);
   remove_alarm(destruct_id);
   ::remove_object();
}

void
self_destruct() {
   remove_object();
}

string
wizinfo() {
   return break_string(
      "This object ensures the peace in this room. It will fall apart in "
    + query_time_left() + " seconds.\n",70);
}

int
query_time_left()
{
   mixed *call;
 
   call = get_alarm(destruct_id);
   return ftoi(call[2]);
}

/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/monster";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define TP      this_player()
#define TO      this_object()
#define MIN_DUR 10
#define MAX_DUR 1000
#define EN environment

public void heal_npc_from_poison(object who);
public void half_way();
public void self_destruct();

static int no_m_att, no_att, aid=0;

public void
create_monster()
{
   set_name("spirit");
   set_race_name("spirit");
   add_name(({"spirit", "spirit of peace", "mystic spirit"}));
   add_name("spirit_of_peace");
   set_adj("ancient");
   set_short("spirit of peace");
   set_pshort("spirits of peace");
   set_long(
      "A spirit of peace. It stands tall and proud, bound"
    + "in a white linen robe and a wearing gold helm. It wears a pale blue"
    + "cloak that bears a white dove emblem.\n");

   add_prop(OBJ_M_NO_GET, "@@my_get");
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   
}

public string
my_get()
{
   say(QCTNAME(TP) + " falls to the ground.\n");
   if (TP->query_npc()) return "You are knocked to the ground.\n";

   TP->reduce_hit_point(10);
   if (TP->query_hp() <= 0) TP->do_die(TO);

   return "You are knocked to the ground by a blinding flash.\n";
}

public int
filter_living(object obj)
{
   if (obj == TO) return 0;
   return living(obj);
}

/*
 * Function name:   make_peace
 * Description:     Stop all fighting in the room and set properties
 *                  to make sure it stays peacefully.
 * Arguments:       active_time: The number of seconds the peace has to last.
 */
public void
make_peace(int active_time)
{
   object *ob_arr, env;
   int i;

   ob_arr = all_inventory(env = environment());
   ob_arr = filter(ob_arr, filter_living);

   /* Make 'em all stop */
   for (i=0; i<sizeof(ob_arr); i++) {
       ob_arr[i]->stop_fight(ob_arr);
       if (ob_arr[i]->query_npc())
           heal_npc_from_poison(ob_arr[i]);
   }

   no_att = env->query_prop(ROOM_I_NO_ATTACK);
   no_m_att = env->query_prop(ROOM_I_NO_MAGIC_ATTACK);
   env->add_prop(ROOM_I_NO_ATTACK, 1);
   env->add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   
   if (active_time < MIN_DUR) active_time = MIN_DUR;
   if (active_time > MAX_DUR) active_time = MAX_DUR;
   
   tell_room(EN(TO), "A sense of peace descends upon this place.\n");
   set_alarm(itof(active_time)/2.0, -1.0, half_way);
   aid = set_alarm(itof(active_time), -1.0, self_destruct);
}

public void
half_way()
{
   tell_room(environment(),
      "There is a brilliant flash of light, followed by a rushing wind.\n");
}

public void
remove_object()
{
   object env;

   if (env = environment())
   {
      env->add_prop(ROOM_I_NO_ATTACK, no_att);
      env->add_prop(ROOM_I_NO_MAGIC_ATTACK, no_m_att);
      tell_room(env, "A mystical presence departs and " +
                     "you feel a breeze from above you.\n");
   }
   ::remove_object();
}

public void
self_destruct()
{
   aid = 0;
   remove_object();
}

public string
wizinfo()
{
   int time=-1;
   mixed *call;
   
   if (aid) {
       call = get_alarm(aid);
       time = ftoi(call[2]);
   }
   
   return "This Spirit (object) keeps the Peace. It departs in " +
          time + " seconds.\n";
}

/*
 * The function heal_npc_from_poison() (called from make_peace()) is
 * here in order to prevent the mystics from first poison the npc with
 * venenare and then summon the peace spirit. 
 * Added by Mortricia
 */
public void
heal_npc_from_poison(object who)
{
   object *inv;
   int i;

   if (!(who->query_npc())) return;

   inv = all_inventory(who);
   
   for (i=0; i<sizeof(inv); i++) {
      if (function_exists("cure_poison", inv[i]) ==
	  "/std/poison_effect" && inv[i]->query_prop("mystic_poison")) {
         inv[i]->cure_poison(({"all"}), 1000);
      }
   }
}

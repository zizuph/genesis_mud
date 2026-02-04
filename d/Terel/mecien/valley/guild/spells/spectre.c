/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/monster";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define TO  this_object()
#define ETO environment(TO)

public void heal_npc_from_poison(object who);
public void half_way();
public int filter_living(object obj);

int no_m_att, no_att, aid = 0;

public void
create_monster()
{
   set_race_name("spectre");
   set_name("spectre");
   add_name(({"spirit", "spectre", "feast spirit"}));
   set_adj("dark");
   set_long("A spectral image of some dark being, whispering in the " +
      "air, like the haunting memory of some ancient time past.\n");
   set_gender(2);
   
   add_prop(OBJ_M_NO_ATTACK, "You cannot seem to harm the spectre.\n");
}

public void
make_peace(int active_time)
{
   object *ob_arr;
   int i;
   
   ob_arr = filter(all_inventory(ETO), filter_living);
   
   /* Make 'em all stop */
   for (i=0; i < sizeof(ob_arr); i++) {
      ob_arr[i]->stop_fight(ob_arr);
      if (ob_arr[i]->query_npc()) heal_npc_from_poison(ob_arr[i]);
   }
   
   no_att = ETO->query_prop(ROOM_I_NO_ATTACK);
   no_m_att = ETO->query_prop(ROOM_I_NO_MAGIC_ATTACK);
   ETO->add_prop(ROOM_I_NO_ATTACK, 1);
   ETO->add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   set_alarm(itof(active_time)/2.0, -1.0, half_way);
   aid = set_alarm(itof(active_time), -1.0, remove_object);
}

public int
filter_living(object obj)
{
   return living(obj);
}

public void
half_way()
{
   tell_room(environment(TO), "There is a brilliant flash of light, " +
             "followed by a rushing wind.\n");
}

public int
remove_object()
{
   object env;
   
   aid = 0;
   if (env = environment())
   {
      env->add_prop(ROOM_I_NO_ATTACK, no_att);
      env->add_prop(ROOM_I_NO_MAGIC_ATTACK, no_m_att);
      tell_room(env, "The spectre fades into a forming darkness " +
                "and is gone.\n");
   }
   ::remove_object();
}

string
wizinfo()
{
   mixed *a;
   int time = -1;
   
   if (aid) {
       a = get_alarm(aid);
       time = ftoi(a[2]);
   }
   return "This Spirit keeps the Peace. It departs in " +
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

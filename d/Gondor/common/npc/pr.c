/*
 * /d/Gondor/common/npc/pr.c
 *
 * A totured man, Coded by someone (likly Olorin or Elessar)
 *
 * Revision history:
 * Updated code: Boron, May 30. 1996
 */

inherit "/std/monster";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/d/Gondor/defs.h"

void
create_monster()
{
  set_name("man");
  set_race_name("human");
  set_living_name("minardel");
  set_adj("pale");
  set_adj("tortured");
  set_short("pale-looking tortured man");
  set_long("This man looks very pale and ill. You see clear marks of torture\n"+
    "and mistreatment in his face, and his wrists are sore and bloody,\n"+
    "with marks from being tied up. The man is just lying on the ground,\n"+
    "too weak to move.\n");
  set_stats(({ 5, 5, 5, 5, 5, 5 }));
  set_hp(100);
  add_prop(CONT_I_HEIGHT,197);
  add_prop(NPC_M_NO_ACCEPT_GIVE,0);
  add_prop(CONT_I_WEIGHT,80000);
}

enter_inv(obj, from)
{
  ::enter_inv(obj,from);
  if (!from) return;
  test_food(obj,from);
}

int
test_food(object obj, object pl)
{
  if (!obj) return;
  if (!function_exists("create_food",obj)) {
    set_alarm(5.0, 0.0, drop_it(obj));
    return 1;
    }
  set_alarm(5.0, 0.0, eat_it(obj));
  return 1;
}

drop_it(obj)
{
  tell_room(ENV(TO),"The pale man is too weak to hold the "+obj->query_name()+",\n"+
    "so he drops it to the ground.\n");
  TO->command("drop "+obj->query_name());
  return 1;
}

int
eat_it(obj)
{
  tell_room(ENV(TO),"The pale looking man looks hungrily at the "+obj->query_name()+".\n");
  tell_room(ENV(TO),"The man then suddenly eats the "+obj->query_name()+" almost without swallowing.\n");
  obj->remove_object();
  set_alarm(10.0, 0.0, get_better());
  return 1;
}

get_better()
{
  tell_room(ENV(TO),"The pale man looks a little better now.\n");
  return 1;
}


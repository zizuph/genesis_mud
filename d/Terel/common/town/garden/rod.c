inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#define  TP      this_player()
#define  ETP     environment(TP)
#define  NF(xx)  notify_fail(xx)
#define  FISH    "/d/Terel/common/town/garden/fish"

int bait;

public void
catchf(object ob, object where)
{
  object fish;
  
  if (!ob || environment(ob) != where) return;
  
  seteuid(getuid());
  fish = clone_object(FISH);
  fish->move(ob);
  tell_room(environment(ob), QCTNAME(ob) + " caught a fish! " +
            "It looks very tasty.\n", ob);
  ob->catch_msg("You feel a sudden move in the fishing rod and " +
                "pull the line out of the water. You have catched " +
                "a fish! You carefully remove the " + fish->short() + 
                " from the hook and put it in your pocket.\n");
  set_long("This is a sturdy fishing rod, suitable for fishing. " +
           "Unfortunately it has no bait.\n");
}

public int
do_fish(string str)
{
  mixed temp = ETP->query_prop(ROOM_I_TYPE);
  
  NF("Fish with what?\n");
  if (!str) return 0;
  
  if (str != "rod" && str != "with rod") return 0;

  if (temp != ROOM_BEACH && temp != ROOM_IN_WATER)
  {
      TP->catch_msg("You suddenly realize that this room has no water.\n");
      return 1;
  }

  if (bait) {
    NF("You have used all the bait on this rod.\n");
    return 0;
  }
  
  bait = 1;

  say(QCTNAME(TP) + " starts to fish with " + TP->query_possessive() +
      " " + short() + ".\n");
  TP->catch_msg("You begin fishing with the " + short() + ".\n");

  set_alarm(10.0, -1.0, &catchf(TP, ETP));

  return(1);
}

public void
create_weapon()
{
  set_name("rod");
  set_adj("fishing");
  set_short("fishing rod");
  set_long("This is a very sturdy fishing rod. " +
           "Maybe you should try to fish with it?\n");
  set_hit(5);
  set_pen(5);

  set_wt(W_POLEARM);
  set_dt(W_IMPALE);

  add_prop(OBJ_I_WEIGHT, 300);
  add_prop(OBJ_I_VOLUME, 88);
}

public void
init()
{
    ::init();
    add_action(do_fish,"fish");
}

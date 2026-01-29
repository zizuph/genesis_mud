/*
 * wishingwell.c
 *
 * Used in nyreese/orc_road3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Changed throw to toss, due to changes in driver. Damaris 01/2005
 * Fixed by Tapakah, 06/2021. Increased jackpot as well.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <language.h>
#include <money.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

mapping tried;
int totalsum;
int winners;
int jackpot;

void givep(int amount, object tp);
int toss(string str);
int climb(string str);
int enter(string str);

string log_file = "/d/Khalakhor/log/cadu-wishing-well.log";

void
reset_well ()
{
  winners = 0;
  jackpot = !random(10);
  tried = ([]);
}

void
create_object ()
{
  if (!IS_CLONE)
    return;

  set_short("wishing well");
  set_name("well");
  set_adj("wishing");
  set_long("This is a wishing well, or at least that's what the " +
           "sign on it claims. Perhaps you should throw some " +
           "coins in it and see for yourself.\n");

  add_item("sign", "The sign says: Ye olde wishing well.\n");
  add_cmd_item("sign", "read", "Ye olde wishing well.\n");

  add_prop(OBJ_I_NO_GET, "It's way too heavy!\n");
  add_prop(CONT_M_NO_INS, "Maybe you should try throwing it?\n");
  add_prop(CONT_I_IN, 1);

  totalsum = 0;

  reset_well();setuid(); seteuid(getuid());
}

void
init ()
{
  ::init();
  add_action(toss, "throw");
  add_action(toss, "toss");
  add_action(climb, "climb");
  add_action(enter, "enter");
}

int
climb (string s)
{
  NF("Climb what?\n");
  if (!s) return 0;

  if (!parse_command(s, TO,
                     "[in] [into] [the] [wishing] 'well'"))
    return 0;

  write("Climbing into the wishing well is not a good idea.\n");
  return 1;
}

int
enter (string s)
{
  NF("Enter what?\n");
  if (!s) return 0;

  if (s != "well" && s != "wishing well")
    return 0;

  write("Entering the wishing well is not a good idea.\n");
  return 1;
}

int
toss (string s)
{
  object ob, *obs;
  int amount;
  mixed pob;

  if (!s)
    NF0("You throw yourself around a little, but decide against it " +
        "when you almost fall into the well.");

  if (s == TP->query_real_name())
    NF0("And how do you think you could do that?");

  NF("I don't really understand you...\n");

  if (!parse_command(s, TP, "%i 'in' / 'into' [the] [wishing] 'well'", pob))
    NF0("The well doesn't seem to understand you.");

  obs = NORMAL_ACCESS(pob, 0 , 0);
  if(! sizeof(obs))
    NF0("You have no such thing to throw in the well.\n");

  ob = obs[0];

  if (living(ob))
    NF0("That is too large to fit in the well.\n");
  if (ob->query_prop(OBJ_I_NO_DROP))
    NF0("You can't part with that.\n");

  if (!ob->id("coin")) {
    write("Your " + ob->query_name() +
          " sinks to the bottom and disappears.\n" +
          "Nothing else seems to happen.\n");
    say(QCTNAME(TP) + " tosses something in the well.\n");
    ob->remove_object();
    return 1;
  }
  
  amount = ob->query_prop(OBJ_I_VALUE);

  if (!amount) {
    write("Thought that would work, did you?\n");
    say("The well kicks " + QTNAME(TP) + " in the stomach.\n");
    return 1;
  }

  write("You toss " + ob->short() + " into the well.\n");
  say(QCTNAME(TP) + " tosses some coins in the well.\n");

  ob->force_heap_split();
  ob->remove_object();

  totalsum += amount;

  set_alarm(15.0, 0.0, &givep(amount, TP));
  return 1;
}

void
givep (int amount, object tp)
{
  string name;
  string log_string;
  
  if (!tp || ENV(tp) != ENV(TO))
    return;

  name = tp->query_real_name();
  // More winners gives less chance
  if (random(5 + 5*winners) > 2) {
    if (!tried[name])
      tried[name] = 1;
    tp->catch_msg("Nothing seems to happen.\n");
    log_string = sprintf("%s (%-11s) lost %d at the wishing well (%d jackpot)\n",
                         ctime(time()), name, amount, totalsum);
    write_file(log_file, log_string);
    return;
  }
  
  if (tried[name] > 1) {
    tp->catch_msg("You feel that the well won't give you more for now.\n");
    return;
  }
  // A player only gets a jackpot on the first try
  if (!tried[name] && jackpot) {
    amount = totalsum;
    jackpot = 0;
  }
  
  winners++;
  tp->catch_msg("You feel your pockets fill with money!\n");
  log_string = sprintf("%s (%-11s) won %d at the wishing well (%d jackpot)\n",
                       ctime(time()), name, amount, totalsum);
  write_file(log_file, log_string);
  tried[name] = 2;
  if (amount < totalsum)
    amount *= 2;
  if (amount > totalsum)
    amount = totalsum;

  MONEY_MAKE_CC(amount)->move(tp);
  totalsum -= amount;
}

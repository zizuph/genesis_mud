/* created by Aridor 01/20/94 */

inherit "/std/object";

#include "../local.h"
#include <macros.h>
#define FIRST_WARNING     10800 /*3 hours*/
#define SECOND_WARNING    18000 /*5 hours*/
#define THIRD_WARNING     21600 /*6 hours*/
#define END_OF_PATIENCE   23400 /*6.5 hours*/

int amount;
int when;
object liq;

query_auto_load()
{
  return MASTER_OB(TO) + ":" + amount + " " + when;
}

create_object()
{
  set_name("Colin's lending object");
  set_no_show(1);
  set_long("Well, I'll call the liquidator once in a while " +
	   "if you don't pay your fees!");
  call_out("may_call_liquidator", 200);
}


void
init_arg(string arg)
{
    int num1, num2;

    if (sscanf(arg, "%d %d", num1, num2) == 2)
      {
	amount = num1;
	when = num2;
      }
}


initialize_the_lending_object(int much, int age)
{
  amount = much;
  when = age;
}


may_call_liquidator()
{
  int my_age = TP->query_age();
  seteuid(getuid(TO));
  if ((time() - when) > END_OF_PATIENCE)
    {
      liq = clone_object(LIV + "liquidator");
      liq->set_my_level_factor(10, E(TO));
      liq->add_prop(LIVE_O_ENEMY_CLING, E(TO));
      liq->move_living("xx",E(TP));
    }
  else if ((time() - when) > THIRD_WARNING)
    {
      liq = clone_object(LIV + "liquidator");
      liq->set_my_level_factor(5, E(TO));
      liq->move_living("xx",E(TP));
      call_out("may_call_liquidator",(when + END_OF_PATIENCE - THIRD_WARNING + 2 - my_age));
    }
  else if ((time() - when) > SECOND_WARNING)
     {
      liq = clone_object(LIV + "liquidator");
      liq->set_my_level_factor(2, E(TO));
      liq->move_living("xx",E(TP));
      call_out("may_call_liquidator",(when + THIRD_WARNING - SECOND_WARNING + 2 - my_age));
     }
  else if ((time() - when) > FIRST_WARNING)
    {
       liq = clone_object(LIV + "liquidator");
       liq->set_my_level_factor(1, E(TO));
       liq->move_living("xx",E(TP));
       call_out("may_call_liquidator",(when + SECOND_WARNING - FIRST_WARNING + 2 - my_age));
    }
  else
    {
      call_out("may_call_liquidator",(when + FIRST_WARNING + 2 - my_age));
    }
}


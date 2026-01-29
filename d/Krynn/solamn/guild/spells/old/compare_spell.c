/* the weapon/armour compare spell of the solamnian knights */

inherit "/std/spells";

#include "/d/Krynn/common/defs.h"
#include <cmdparse.h>
#include <macros.h>
#include <language.h>

void
create_spells()
{
    set_name("compare_spell");
    set_no_show();

    add_spell("compare","compare","compare <weapon/armour> with <>");
}

int
compare(string str)
{
    object *ob, ob1, ob2;
    string str1,str2;
    int i1,i2,i3,i4;
    if (!str)
      {
	  write("Compare what with what?\n");
	  return 0;
      }
    if (sscanf(str,"%s with %s",str1,str2) != 2)
      {
	  write("Compare what with what?\n");
	  return 0;
      }
    ob = FIND_STR_IN_OBJECT(str1,TP);
    if (!ob || !sizeof(ob))
      {
	  write("Compare what with what?\n");
	  return 0;
      }
    ob1 = ob[0];
    ob = FIND_STR_IN_OBJECT(str2,TP);
    ob -= ({ ob1 });
    if (!ob || !sizeof(ob))
      {
	  write("Compare what with what?\n");
	  return 0;
      }
    ob2 = ob[0];
    if (ob1->check_armour() && ob2->check_armour())
      {
	  write("CMP ARMOUR\n");
	  return 1;
      }
    if (ob1->check_weapon() && ob2->check_weapon())
      {
	  if (ob1->query_wep_type() != ob2->query_wep_type())
	    {
		write("The " + ob1->short() + " cannot be compared to the " +
		      ob2->short() + ".\n");
		return 1;
	    }
	  i1 = ob1->query_hit() + ob1->query_pen() - ob2->query_hit() -
	    ob2->query_pen() - 5 + random(11, time() % 1000);
	  i2 = ob1->query_value() - ob2->query_value() - 20 + random(41, time() % 1000);
	  i3 = ob1->query_dull() + ob1->query_corroded() - ob2->query_dull() -
	    ob2->query_corroded() - 2 + random(5, time() % 1000);
	  i4 = ob1->query_weight() - ob2->query_weight() - 300 + random(601, time() % 1000);
	  if (i1 > 10)
	    str1 = " a much better weapon than ";
	  else if (i1 > 1)
	    str1 = " a better weapon than ";
	  else if (i1 > -2)
	    str1 = " an equally good weapon as ";
	  else if (i1 > -11)
	    str1 = " a worse weapon than ";
	  else
	    str1 = " a much worse weapon than ";
	  write("The " + ob1->short() + " is" + str1 + "the " + ob2->short() + ".\n");
	  if (i2 > 800)
	    str1 = " a much more valuable weapon than ";
	  else if (i2 > 100)
	    str1 = " a more valuable weapon than ";
	  else if (i2 > -100)
	    str1 = " an equally valuable weapon as ";
	  else if (i2 > -800)
	    str1 = " a less valuable weapon than ";
	  else
	    str1 = " a much less valuable weapon than ";
	  write("The " + ob1->short() + " is" + str1 + "the " + ob2->short() + ".\n");
	  if (i3 > 10)
	    str1 = " in a much better condition than ";
	  else if (i3 > 1)
	    str1 = " in a better condition than ";
	  else if (i3 > -2)
	    str1 = " in about the same condition as ";
	  else if (i3 > -11)
	    str1 = " in a worse condition than ";
	  else
	    str1 = " in a much worse condition than ";
	  write("The " + ob1->short() + " is" + str1 + "the " + ob2->short() + ".\n");
	  if (i4 > 750)
	    str1 = " much heavier than ";
	  else if (i4 > 100)
	    str1 = " heavier than ";
	  else if (i4 > -100)
	    str1 = " as heavy as ";
	  else if (i4 > -750)
	    str1 = " lighter than ";
	  else
	    str1 = " much lighter than ";
	  write("The " + ob1->short() + " is" + str1 + "the " + ob2->short() + ".\n");
	  say(QCTNAME(TP) + " holds " + LANG_ASHORT(ob1) + " and " + LANG_ASHORT(ob2) +
	      " in front of " + OBJECTIVE(TP) + " and murmurs a few words.\n" +
	      "The weapons glow briefly.\n");
	  return 1;
      }
    write("The " + str1 + " and " + str2 + " are not comparable.\n");
    return 0;
}

/* shadow that makes a weapon blunt, or actually just a 'blank', coming
 * right out of the furnace.
 * Aridor, 10/94
 */

#include <stdproperties.h>
#include <language.h>

inherit "/std/shadow";

int reduce_pay = 0;

string
short(object for_obj)
{
    return "blunt " + shadow_who->short(for_obj);
}

string
plural_short(object for_obj)
{
    return "blunt " + shadow_who->plural_short(for_obj);
}

string
long(object for_obj)
{
    return "This is just a blank so far, right out of the furnace. It still " +
      "needs to be forged. Maybe you can find a smith to do that for you? " +
      "Eventually, it will be " + LANG_ADDART(shadow_who->short(for_obj)) +
      ".\nIt looks completely blunt.\n";
}

int
query_hit()
{
    return 1;
}

int
query_pen()
{
    return 1;
}

int *
query_pm()
{
    return ({ 0,0,0 });
}

int
query_dull()
{
    return 10;
}

int
query_value()
{
    if (shadow_who->query_prop(OBJ_I_BROKEN))
      return 0;
    else
      return 10;
}

int
is_blunt()
{
    return 1;
}

void
set_reduce_pay(int i)
{
    reduce_pay = i;
}

int
query_reduce_pay()
{
    return reduce_pay;
}

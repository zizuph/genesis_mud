#include "/d/Immortal/std/domain.h"
#include "/d/Immortal/std/money.h"

inherit "/d/Immortal/std/object";

void
create_object()
{
  set_name("money maker");
  set_short("money maker");
  set_long("Stexx's money maker. Use 'makemoney <type> <amount>' where "+
    "<type> is iron, steel, mithril, or laen.\n");
}

void
init()
{
  ::init();
  add_action("makemoney","makemoney");
}

int
makemoney(string arg)
{
string arg1;
int arg2;
object change;

  FIXEUID;

  sscanf(arg,"%s %d",arg1, arg2);
  if(strlen(arg1) && arg2 > 0)
    {
    write("trying to get change\n");

    change = MONEY_MAKE(arg2, arg1);
    if(change)
      {
      write("You got some change\n");
      change->move(this_player());
      return 1;
      }
    }
  notify_fail("makemoney <iron, steel, mithril or laen> <how much>\n");
  return 0;
}

/* Round table
 * For Gentleman's Club
 * Damaris 10/2001
 */

#include "/d/Raumdor/defs.h"

inherit "/std/object";

void
create_object()
{
    set_name("vase");
    add_name(({"roses", "red roses", "flowers", "red flowers"}));
    set_adj(({"tall", "round"}));
    set_short("tall round vase of red roses");
    set_long("A large round vase of beautiful long-stem red roses.\n");
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(CONT_I_MAX_WEIGHT, 100);
    add_prop(CONT_I_MAX_VOLUME, 100);
}

int
do_smell(string str)
{
  if(str == "")
    return 0;

  notify_fail("Smell what?\n");
  if(str != "flower" &&  str != "the flower" &&
     str != "flowers" && str != "the flowers" &&
     str != "rose" &&    str != "the rose" &&
     str != "roses" &&   str != "the roses")
    return 0;

  write("You lean over and smell the "+short()+" and "+
    "inhale deeply.  You close your eyes as you are briefly overcome "+
    "by the strong scent.\n");
  say(QCTNAME(TP)+" learns over and smells the "+short()+" and inhales "+
      "deeply, closing "+HIS(TP)+" eyes briefly.\n");

  return 1;
}
void
init()
{
  ::init();

  add_action("do_smell", "smell");
  add_action("do_smell", "sniff");
}

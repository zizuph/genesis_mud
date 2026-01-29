inherit "/std/board";

#include "/d/Roke/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#define SECRET2 ATUAN+"cape/guild/councilrm"
#define COUNCIL_MEMBER(name) ((SECRET2)->query_council_member(name))

void
create_board()
{
  set_board_name(ATUAN + "cape/guild/cboard");
  set_num_notes(30);
  set_silent(0);
  set_show_lvl(9);
  set_remove_lvl(17);
  set_remove_str("Removing notes is for high level wizards only.");
}

varargs int
check_reader()
{
  if( ((TP->query_wiz_level()) && ( TP->query_domain() == "Roke"
          || COUNCIL_MEMBER(TP->query_real_name()))) ||
            (TP->query_wiz_level() > WIZLEV_LORD) )
  {
    return 0;
  }

   if (present(this_interactive(), environment(this_object())))
    write("This board is restricted to Traveller council members "+
          "and Roke wizards.");
  return 1;
}

varargs int
check_writer()
{
  if( ((TP->query_wiz_level()) && ( TP->query_domain() == "Roke"
    || COUNCIL_MEMBER(TP->query_real_name()))) ||
      (TP->query_wiz_level() > WIZLEV_LORD) )
  {
    return 0;
  }

  if (present(this_interactive(), environment(this_object())))
    write("Only Roke wizards and Traveller council members are allowed "+
          "to manipulate this board.");
  return 1;
}

varargs int check_remove() { return check_writer(); }

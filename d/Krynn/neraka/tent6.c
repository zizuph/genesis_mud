/* A tent in Tantallon, coded by Nick */

#include <filter_funs.h>
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit TANTALLON_INSIDE;

int wake_alarm = 0;

object highlord;


reset_tantallon_room()
{
    if (!present("highlord"))
    {
      highlord = clone_object(MON + "highlord")->move_living("xx", TO);
    }
}

create_tantallon_room()
{
    set_short("big tent");
    set_long("You are in the biggest tent in Tantallon. " +
             "To your surprise the tent is rather empty. " +
             "There is only a big table and a few chairs in " +
             "here.\n");

    add_item("tent",
        "It's a large tent, the largest in Tantallon.\n");
    add_item("table",
        "It's a large, sturdy, wooden table.\n");
    add_item("chairs",
	"They are made out of the same sort of wood as the table.\n");

    add_exit(TDIR + "city11", "south", 0);

    reset_room();

    INSIDE;
}

void
update_highlord_wake_state()
{
    switch (GET_TIMEOFDAY)
    {
        case TOD_NIGHT:
	  if (highlord->is_awake())
	  {
	      highlord = highlord->go_to_sleep();
	  }
	  break;
        default:
	  if (!highlord->is_awake())
	  {
	    highlord = highlord->wake_me_up();
	  }
	  break;
    }
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (interactive(obj))
    {
      if (!wake_alarm)
      {
	wake_alarm = set_alarm(10.0, 300.0, &update_highlord_wake_state());
      }
    }
}

public void
leave_inv(object obj, object to)
{
  ::leave_inv(obj, to);
  
  if(!sizeof(FILTER_PLAYERS(all_inventory(this_object()))))
  {
    remove_alarm(wake_alarm);
    wake_alarm = 0;
  }
}

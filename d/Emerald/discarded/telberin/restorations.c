inherit "/std/room";

#include "default.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>
#include <filter_funs.h>

void kick_out(object ob);

void reset_room()
{
  object wiz;

  setuid();
  seteuid(getuid());

  if (!present("restoration_wiz") && 
      (wiz = clone_object(NPC_DIR + "wiz")))
  {
    if (calling_function() != "create_room")
    {
      tell_room(this_object(), "An elf arrives for his shift.\n");
    }

    wiz->move(this_object(), 1);
  }
}
    
void create_room()
{
  set_short("Restoration Center");
  set_long("A tiny office, barely large enough to contain the " +
      "single\ndesk which sits across from the entrance.\n");
 
  add_item("desk", "An oak desk.  The only thing on it is a " +
      "ticket dispenser with a sign attached.\n");
  add_item(({ "dispenser", "ticket dispenser" }), "An empty ticket " +
      "dispenser with a sign attached to it.\n");
  add_item("sign", "It reads, \"Please take a number.\"\n");

  add_cmd_item("sign", "read", "It reads, \"Please take a number.\"\n");
  add_cmd_item(({ "number", "a number", "ticket", "a ticket" }),
               ({ "get", "take" }), "The dispenser is empty.\n");

  add_exit(THIS_DIR + "o18", "west");

  add_prop(ROOM_I_INSIDE, 1);

  reset_room();
}

void enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if (!living(ob))
  {
    return;
  }

  if (sizeof(FILTER_LIVE(all_inventory(this_object()))) > 3)
  {
    if (IS_WIZ(ob))
    {
      ob->catch_msg("You just barely manage to squeeze yourself " +
          "into the room.\n");
      return;
    }
    
    kick_out(ob);
//    set_alarm(0.5, 0.0, &kick_out(ob));
  }
}

void kick_out(object ob)
{
  ob->catch_msg("You manage to partially squeeze into the office, " +
      "but get pushed out.  There are simply too many people in " +
      "such a small office.\n");

  tell_room(this_object(), QCTNAME(ob) + " is pushed back out of the " +
      "room before " + ob->query_possessive() + " gets all the way " +
      "through the doorway.\n", ob); 

  ob->move_living("M", THIS_DIR + "o18", 0, 1);
}

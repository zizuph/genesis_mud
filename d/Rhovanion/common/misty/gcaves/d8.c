/* goblin caves */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include <filter_funs.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define CAVE_DIR MISTY_DIR + "gcaves/"

object door;

/*
 * Prototypes
 */
void reset_room();

create_room()
{
  object prisoner;

  seteuid(getuid());

    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_INSIDE, 1);

    set_short("cell in prison");
    set_long("You are in the cell in goblin prison. it is dark with wet "+
             "walls and it stinks. Not a nice place to stay.\n");
    add_item(({"wall","walls"}),BS("The walls are natural rock except the "+
              "southern wall that was build from big blocks of rock.\n"));

    door = clone_object(CAVE_DIR + "grating_3_d");
    door->move(this_object());

    door->set_key("gcave_cell_no_3"); /* Tells the door which key fits. */

    if (!present("_misty_prisoner_"))
    {
      prisoner = clone_object(NPC_DIR + "prisoner");
      prisoner->move_living("xxx", this_object());
    }
}

void
reset_room(){
  object key, prisoner;
  string *old_lock_mess, *old_close_mess;

  seteuid(getuid());

  if(find_living("_misty_prisoner_"))
  {
    call_out("reset_room",1000);
    return;
  }
  if(sizeof(FILTER_LIVE(all_inventory(TO))))
  {
    call_out("reset_room",200);
    return;
  }
  old_lock_mess = door->query_lock_mess();
  old_close_mess = door->query_close_mess();
  door->set_lock_mess( ({"", 
          "Bunch of goblins come running in carrying some poor elf.\n"+
          "The leader goblin unlocks and opens grating and they throw "+
                   "prisoner in the cell.\n"+
          "The leader goblin shouts: Next time you try to escape I kill you "+
                   "with my own hands!!!\n"+
          "The leader closes grating, locks it, grins evilly at you and "+
                   "whole bunch runs away.\n"+
          "You feel great relief. Fortunatelly they haven't considered "+
                   "taking you as a prisoner!\n" 
                    }) );
  door->set_close_mess( ({"", ""}) );
  prisoner = clone_object(NPC_DIR + "prisoner");
  prisoner->move_living("xxx", this_object());
  key = clone_object(OBJ_DIR + "prisoner_key");
  key->move(prisoner);
  prisoner->add_prop(OBJ_I_LIGHT, 100);
  prisoner->command("close grating");
  prisoner->command("lock grating with key");
  prisoner->remove_prop(OBJ_I_LIGHT);
  key->remove_object();
  door->set_lock_mess(old_lock_mess);
  door->set_close_mess(old_close_mess);
}

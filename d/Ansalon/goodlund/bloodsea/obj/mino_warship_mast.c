/*
 * Cabin on the minotaur warship sailing the bloodsea.
 * Made by Cherek Jan 2007.
 */
 
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include <composite.h>
#include <filter_funs.h>
#include "../local.h"

inherit "/std/room.c";
inherit "/lib/unique";

#define HAT (BOBJ + "blackened_champron")
#define GEM "/d/Genesis/gems/obj/tourmaline_pink"


void set_exit(string exit_name);

object minotaur;
object hat;

void reset_room()
{
  if(!objectp(minotaur))
  {
    minotaur = clone_object(BNPC + "minotaur_sailor");
    hat = clone_unique(HAT, 5, GEM);
    hat->move(minotaur, 1);
    minotaur->command("wear all");
    minotaur->move(this_object(), 1);
  }
}

void
create_room() 
{
    set_short("Up in a mast");
    set_long("You have climed up the mast on the minotaur warship, "+
             "and reached a small platform most likely used for keeping " +
             "a lookout for enemy ships during travel.\n");
            
     add_item(({"ship", "warship"}),
                "Everything on this ship seem to have been very " +
                "carefully designed. \n");               

    add_prop(ROOM_I_INSIDE, 0);

    reset_room();
}

void set_exit(string exit_name)
{
    remove_exit("down");
    add_exit(exit_name, "down", 0, 1);
}


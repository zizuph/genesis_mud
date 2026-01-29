// file name: cell5.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note: Bicornblk
// bug(s):
// to-do:


inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"

/* Room 34 */

static object bicorna;

create_room()
{
set_short("A small cell");
set_long("You are in a large stone room what was once used "
	+"as a prison cell. The gate has long since rotted away, though, "
	+"and nothing remains but the stones and the walls.\n");

        add_prop(ROOM_I_LIGHT,1);
        IN_IN

AE(PK+"e_path7","northwest",0);

STDCELL

  reset_room();
}

reset_room()
{
  if (!bicorna)
   {
      bicorna = clone_object(PK+"mon/bicorna");
      bicorna->move_living("M", this_object());
    }
}


/*  part of the track leading up to the volcano in the land of the dinosaurs
 
    coder(s):	Deinonychus
 
    history:	DD.MM.YY	what done			who did
		27.02.93	created				Deinonychus
 
    purpose:	none
    exits:	none
 
    objects:	none
    npcs:	none
 
    quests:	none
    special:	none
 
    to do:	none
    bug:	none known
*/
 
 
inherit "/std/room";
#include "track.h"
#include <stdproperties.h>
#include <macros.h>

int rope_tied = 0;

void
create_room()
{
  set_short("Hole in the volcano");
  set_long("You're in a dark hole.\n");
  add_prop(ROOM_I_LIGHT,0);
}

void
rope_tied()
{
  if(!rope_tied)
  {
    rope_tied = 1;
    add_exit(ROOM("top"), "up", 0);
    tell_room(TO, "Somebody above lets a rope down the hole.\n");
    add_my_desc("There's a rope hanging down.\n", TO);
    return;
  }
}

void
rope_untied()
{
  if(rope_tied)
  {
    rope_tied = 0;
    remove_exit("up");
    tell_room(TO, "The rope's pulled up.\n");
    remove_my_desc(TO);
    return;
  }
}

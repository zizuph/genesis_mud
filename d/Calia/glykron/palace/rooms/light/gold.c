
/* 
   Gold room in the Crystalline palace of the Calians.

   History:
          15/5/96     check CAN_SEE for guarding       Maniac
           6/4/96     tidied up kroug handling         Maniac
           12/12/95   vandalism possibility added      Maniac
           22/9/95     Kroug raid code installed       Maniac
           8.12.94     Minor changes                   Maniac
*/


#pragma save_binary

inherit "/d/Calia/std/kroug_palace_room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include CALIAN_HEADER
#include "/d/Calia/std/vandalism.c"

object calian = 0;

int
is_calian(object ob)
{
  if (ob->query_guild_name_occ() == GUILD_NAME)
      return 1;
  else
      return 0;
}


int
guarded()
{
    object tp = this_player();

    if (objectp(calian) && present(calian, this_object()) &&
        !is_calian(tp) && CAN_SEE(calian, tp))
    {
	tp->catch_msg(QCTNAME(calian) + " won't let you by!\n");
	tell_room(this_object(), 
                   QCTNAME(calian) + " blocks " + QTNAME(tp) +
	           "'s attempt to go north.\n", ({ tp }));
	return 1;
    }

    return 0;
}


void
reset_room()
{
    if (calian)
	return;
    calian = clone_object(MONSTER("gold_calian"));
    calian->move(THIS);
    tell_room(THIS, QCTNAME(calian) + " arrives.\n");
}

void
create_room()
{
    set_short("The golden room");
    set_long(
	 "This is a small trapezoidal-shaped room whose east and west walls " +
	 "slope away from you to the north.  " +
	 "The walls, the bed, and the dresser are all lined with gold.  " +
	 "There is also a painting on the east wall.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("light_stairs"), "south", 0);
    add_exit(ROOM("light_white"), "north", "@@guarded");
    add_exit(ROOM("light_silver"), "west", 0);
    add_exit(ROOM("light_bronze"), "east", 0);

    add_item(({"wall", "walls", "east wall"}), "There is a painting on " +
            "the east wall.\n");
    add_item(({"painting", "picture"}), "It is a painting of a lady in " +
             "a golden dress. It seems to be in perfect condition.\n");
    add_item_possible_vandalism("painting", "It is a painting of a lady in " +
             "a golden dress.", ({"smear", "tear"}), 40);

    add_item("bed", "A bed lined with gold. It seems to be in perfect " +
             "condition.\n");
    add_item_possible_vandalism("bed", "A bed lined with gold.", 
                                ({"break"}), 40);
    add_item("dresser", "A dresser lined with gold. It seems to be in " +
             "perfect condition.\n");
    add_item_possible_vandalism("dresser", "A dresser lined with gold.", 
                        ({"break", "dent"}), 40);
    clone_object(OBJECT("warning_sign"))->move(THIS);
    reset_room();
}


void
init()
{
    ::init();
    init_vandalism();
}

public int
clean_up()
{
    if (calian)
        return 1;

    remove_object();
}

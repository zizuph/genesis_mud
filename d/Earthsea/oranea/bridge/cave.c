/*
*  coded by Amelia 8/2/97
*
*/

inherit "/d/Earthsea/std/room";

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
#include <ss_types.h>
#include "/sys/cmdparse.h"


int enter_waterfall(string str);
int stare_into(string str);

void
create_earthsea_room()
{

    set_short("Crystal Cave");
    set_long(break_string("The inside of this cave is like the "+
	"inside of a geode. Jagged amethyst and quartz crystals line the "+
	"ceiling and walls, sparkling like prisms in the light, "+
	"which filters in through the curtain of a waterfall on "+
	"the opposite side. The floor is hard smooth jade. A sense "+
	"of peace fills your mind, and somehow you feel that this "+
	"place is very special, a doorway between past and future. "+
	"Staring at the crystals you feel mesmerized ...\n",
	70));

    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
    add_item("waterfall",
      "The waterfall shines like a curtain across the far side "+
      "of this large cave. You see that there may be something beyond "+
      "it, since light on the other side filters through.\n");
    add_item((({"walls", "ceiling"})),
      "The walls and ceiling are like the inner side of a geode. "+
      "Quartz and amethyst crystals reflect like prisms in the "+
      "light shining through the waterfall.\n");
    add_item((({"amethyst", "quartz", "crystals"})),
      "The crystals of amethyst and quartz are light purple and "+
      "white, reflecting like prisms in the light. As you stare into "+
      "them, you get a strange sensation...\n");
    add_item((({"jade", "smooth jade", "hard jade", "floor"})),
      "You wonder who carved this floor from jade, or whether it is "+
      "some natural anomoly.\n");

    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 0);

    reset_room();
    add_exit("/d/Earthsea/oranea/rooms/oranea_path01", "out");

}


int
enter_waterfall(string str)
{

    object tp = this_player();
    object dirty;
    //for Kalad dirty object, remove when going thru waterfall also

    notify_fail("Enter what/where?\n");
    if (!str)
	return 0;

    if (str == "waterfall")
    {
	if (dirty = present("_kalad_dirty_object", tp))
	    dirty->remove_object();
	tp->catch_msg("You enter behind the curtain of the waterfall, "+
	  "and feel your soul cleansed.\n");
	tell_room(this_object(), QCTNAME(tp) + " enters behind the "+
	  "curtain of the waterfall, disappearing from view.\n", ({tp}));
	tp->move_living("M", "/d/Earthsea/oranea/bridge/cliff1", 1);
	tell_room(this_object(), QCTNAME(tp) + " enters from the "+
	  "waterfall.\n", ({tp}));
	return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(&enter_waterfall(), "enter");
    add_action(&stare_into(), "stare");
}

int
stare_into(string str)
{
    object tp = this_player();


    if (str != "into crystals" && str != "at crystals" &&
      str != "crystal" && str != "into crystal" && str != "at crystal")
	return 0;

    tp->catch_msg(
      break_string("As you stare into "+
	"the crystals, your head spins and "+
	"you see an image in your mind of a huge fiery red-scaled dragon "+
	"flying through gulfs of light and air ... "+
	"In a flash the image clears, "+
	"and another replaces it: A great palace built from many-coloured "+
	"stones, with stained-glass windows and jade pillars. In the "+
	"fraction of a second the vision clears, and you are standing "+
	"in the cave as you were before. A great sense of peace "+
	"fills your mind.\n", 70));

    return 1;
}

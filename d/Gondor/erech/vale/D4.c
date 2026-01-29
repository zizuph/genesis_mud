/*
 * D4.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit "/d/Gondor/common/lib/area_room";

inherit E_STD + "vale.c";
inherit E_QUEST + "tasker.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include TERRAIN_TYPES

/* Prototypes */
public void         create_area_room();
       void         is_climbing();
public string       do_exa();

/*
 * Function name:    create_area_room()
 * Definition   :    Creates the room.
 */
public void
create_area_room()
{
    set_short("In the vale of Erech.");
    set_areatype(AREATYPE_BARREN);
    set_area("northern");
    set_areadesc("hill");
    set_areaname("Erech");
    set_extraline("The view here is magnificent, you can allmost see the " +
	"whole vale from here. A dominant covonent black rock stands on " +
	"the top of the strange hill. A path leads northwest along the " +
	"ridge. A bit to the south and the west the sound of running " +
        "water can be heard.");

    vale_items();
    path_items();

    add_item("view", "You can see the whole vale from this point. The vale " +
	"is narrower to the north where it ends in the White Mountains, and " +
	"to the south the vale turns westwards. The vale is darkish green " +
	"telling you that there are large grass fields with occational " +
	"bushes here and there.\n");
    add_item( ({ "rock", "covenent rock" }), &do_exa());

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_exit(E_VALE + "C3.c", "northwest", 0, 2, 0);
}

public void
init()
{
    ::init();
    add_action("do_climb", "climb");
}

public string
do_exa()
{
    string know_rock = "";

    complete_task(1);

    /* if (this task is done)
    {
        know_rock = "This black rock holds a special part in Gondorian " +
	    "history. ";
    }
    */

    return "You are looking at a large black covenent rock. " + know_rock +
      "The surface seems smooth but yet while drowing your fingers across " +
      "it you can feel some waveshapen marks on it. With some luck you " +
      "think you can manage to climb it.\n";
}

public int
do_climb(string dir)
{
    if (dir)
    {
      switch(dir)
	{
	case "rock":
	case "covenent rock":
	  is_climbing();
	  return 1;
	  break;
	default:
	  write("Clib what?\n");
	  return 1;
	  break;
	}
    }
}

void
is_climbing()
{
    int climb = this_player()->query_skill(SS_CLIMB);
    int rand = random(5);

    if (climb > 15 + rand )
    {
      write("You climbs up the covenent rock.\n");
      say(QCTNAME(this_player()) + " climbs up the " +
	  "covenent rock.\n");
      complete_task(1);
      this_player()->move_living("M", E_QUEST + "rock", 1, 0);
      say(QCTNAME(this_player()) + " arriver " +
	  "climbing.\n");
    }
    else
    {
      write("You try to climb the covenent rock, but looses your grip and " +
	  "falls down again.");
      say(QCTNAME(this_player()) + " falls!!!!");
    }
}


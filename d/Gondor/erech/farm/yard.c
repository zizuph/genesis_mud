/*
 * yard.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit E_STD + "vale.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";
inherit "/lib/unique";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#include TERRAIN_TYPES

#define CHAIR_NAME   "rocking chair"
#define EXA_HOUSE    "front porch"
#define LONG_DESC    "somebody seated"

/* Global variables */
int                seated;

/* Prototypes */
public void         create_area_room();
public void         leave_inv(object ob, object dest);
public string       look_at(string arg);          /* VBFC for chair */
int                 rocking(string arg);

/*
 * Function name:    create_area_room()
 * Definition   :    Creates the room.
 */
public void
create_area_room()
{
    set_short("In the vale of Erech");
    set_areatype(AREATYPE_FARMLAND); /* Areatype, check ~Gondor/defs.h
				      * for specifications */
    set_area("central");             /* southern, central or northern */
    set_areadesc("yard");           /* jupp */
    set_grass("long");               /* grass description */
    set_areaname("Erech");           /* name of the area */
    set_extraline("A red farm house and barn dominate the view to the " +
        "north and northeast, while to the west lies a rich field.");
                                     /* set extra longdesc */
    set_vbfc_extra(look_at(LONG_DESC));
  
    vale_items();
    add_item( ({ "house", "farm house", "red house", "red farm house", }), 
	      &look_at(EXA_HOUSE));
    add_item( ({ "barn", "stable", "red barn" }), "The farm's barn also " +
        "serves as a stable. The busy sounds of many different farm animals " +
        "can be heard from inside. A red coat of paint covers the barn in " +
        "high contrast to the white painted gate in front.\n");
    add_item(({"field", "rich field", "fertile field"}), "To the west you " +
        "see a fertile field.\n");
    add_item("furrow", "You find no furrow.\n");

    add_chair(CHAIR_NAME, "[down] [in] [rocking] 'chair'", 1, "in");
    add_item("chair", &look_at(CHAIR_NAME));

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_herbs("yard");

    clone_object(E_NPC + "farmer2")->move(this_object());

    reset_room();

    add_exit(E_FARM + "house.c", "north", 0, 3, 0);
    add_exit(E_FARM + "barn.c", "northeast", 0, 3, 0);
    add_exit(E_FARM + "field.c", "west", 0, 4, 0);
    clone_object(E_OBJ + "fgate2.c")->move(this_object());
}

void
reset_room()
{
    object ob;
    
    if (!present("bucket"))
    {
	ob = clone_object(E_OBJ + "fbucket");
	ob->set_filled("water");
	ob->set_filled("water");
	ob->add_prop(OBJ_I_HIDE, 3);
	ob->move(this_object());
    }

    ob = clone_unique(E_NPC + "farmer2", 1);
    ob->move(this_object());
}

public void
init()
{
    ::init();
    init_room_chairs(); 
    add_action(rocking, "rock");
}

/*
 * Function name:    leave_inv
 * Description  :    mask parent to be sure that departing players
 *                   are removed from chair occupants
 * Arguments    :    object ob -- the departing object
 *                   object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand
 * by the exit efunc check_sitting().
 * However, if they leave by quitting, going LD, teleporting etc
 * and we don't call leave_inv_room_chairs(), then they still look
 * as if they're here.
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
}

/*
 * Function name:    look_at
 * Description  :    VBFC to describe chair + occupants
 * Arguments    :    string arg -- to change the angle of the view
 *                                 null str -. it's the room
 * Returns      :    string -- the description
 */
public string
look_at(string arg)
{
    switch ( arg )
    {
    case CHAIR_NAME:
      return "This old rocking chair has seen many years. Its seat is worn " +
          "down and its edges have faded in the sun. A crack runs down the " +
          "middle of the seat, evidence of heavy use. " + 
          sitting_on_chair(CHAIR_NAME, this_player(), 0);
    case EXA_HOUSE:
      return "This is the main house of the farm. Its walls are painted " +
        "white while the door is a bright red. The front porch has a lone " +
        "rocking chair on it. " + 
	sitting_on_chair(CHAIR_NAME, this_player(), 0) + "\n";
    case LONG_DESC:
      {
	return "An old rocking chair stands on the front porch. " + 
	  sitting_on_chair(CHAIR_NAME, this_player(), 0);
      }
    }
}

int
rocking(string arg)
{
    object    sitter;

    if (!arg)
    {
        write("Rock what?\n");
	return 1;
    }

    if (sizeof(query_occupants(CHAIR_NAME)) < 1)
      seated = 0;
    else
      seated = 1;

    if (seated == 0)
    {
	write("You rock the empty chair back and forth.\n");
	say(QCTNAME(this_player()) + " rocks the " +
	    "empty rocking chair back and forth.\n");
	return 1;
    }
    else if (seated == 1)
    {
        sitter = query_occupants(CHAIR_NAME)[0];

	if (sitter == this_player())
	{
	    write("You rock your rocking chair gently.\n");
	    say(QCTNAME(this_player()) + " rocks " +
		this_player()->query_possessive() + " rocking chair " +
		"gently.\n");
	    return 1;
	}
	else
	{
	    write("You try to rock the occupied chair, but don't manage " +
                "to move it at all.\n");
	    sitter->catch_tell(QCTNAME(sitter) + 
		" tries to rock your chair.\n");
	    tell_room(this_object(), QCTNAME(this_player()) + " tries to " +
	        "rock " +QTPNAME(sitter) + " chair.\n", ({ this_player(), 
		sitter }) );
	    return 1;
	}
    }
}

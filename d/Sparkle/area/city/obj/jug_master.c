/*
 *  /d/Sparkle/area/city/obj/jug_master.c
 *
 *  This is a simple object to keep track of the jugs assigned to players
 *  by the bartender of the Sparkle Pub for the geyser quest. I am doing
 *  it with an object, rather than a data file so that when the game resets,
 *  we are not trying to keep track of a bunch of old data, but also so that
 *  if the room resets we do not lose the data.
 *
 *  The code for the quest and the jug assignments which reference this
 *  object are at:
 *
 *      /d/Sparkle/area/city/npc/bartender.c
 *
 *  Created November 2018, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#pragma no_clone

inherit "/std/object";

/* Global Variables */
public mapping     Jug_Assignments = ([]);
public mapping     Name_Assignments = ([]);

public void        set_jug_assignments(mixed m)  { Jug_Assignments = m;  }
public void        set_name_assignments(mixed m) { Name_Assignments = m; }

public mixed       query_jug_assignments()  { return Jug_Assignments;  }
public mixed       query_name_assignments() { return Name_Assignments; }


/*
 * Function name:        create_object
 * Description  :        the constructor
 */
public void
create_object()
{
    set_name("jug_master");
    set_short("jug master object");
} /* create_object */

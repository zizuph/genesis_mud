/*
 * Genesis ShipLines Office
 *
 * Inherit this to create your own GSL Office in your domain. 
 * Simply specify the domain that the timetable should show.
 *
 * Code originally written by Tapakah. Original comments:
 *    Genesis ShipLines - Sparkle office.
 *    TAPAKAH, 10/2008
 *    To be transferred later into /d/Sparkle
 *
 * Ported by Petros, April 2009
 */

#include <std.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "gs_office.h"

inherit ROOM_OBJECT;

#ifndef LEAFLET
#define LEAFLET   (GSL_OFFICE_DIR + "leaflet")
#endif LEAFLET

// Global Variables
public string       Timetable_file;

// Prototypes
//   Interface Functions
public int          get_leaflet (string str);

//   Getters and Setters
public void         set_timetable_file(string file);
public string       query_timetable_file();

//   Customization Functions
public void         create_gsl_office();

/* 
 * Function:    create_gsl_office
 * Description: Mask this customizable creation function to add objects
 *              and descriptions to your ShipLines office. The timetable
 *              is added automatically. Simply call set_timetable_file
 *              to specify the file.
 */
public void
create_gsl_office()
{
    set_timetable_file(GSL_OFFICE_DIR + "timetable");
}

public void
init()
{
  ::init();
  add_action(get_leaflet, "get");
  add_action(get_leaflet, "take");
  add_action(get_leaflet, "pick");
  add_action(get_leaflet, "grab");
}

public nomask void
create_room () {

  ::create_room();

    setuid();
    seteuid(getuid());
    
    set_short("Inside an Office of Genesis ShipLines");
    set_long("You are inside an office of the Genesis ShipLines Company. "
        + "Currently it is a relatively small hall, albeit with a very "
        + "high ceiling. On one of the walls, you see something "
        + "bolted securely. A simple wooden desk is planted in the center "
        + "of the room.\n");
        
    add_item( ({ "desk", "wooden desk", "simple desk",
                 "simple wooden desk" }),
          "A new simple wooden desk. A heap of leaflets is piled next "
        + "to the desk.\n");
    
    add_item( ({ "heap of leaflets", "leaflets", "heap", "pile" }),
          "The leaflets look like they contain some valuable "
        + "information. You think you might be able to <grab> one.\n");
    
    add_item( ({ "wall", "walls", "bolt" }),
          "Securely fastened to the wall is what appears to be a "
        + "large timetable. You think you may be able to gather some "
        + "useful information from it.\n");
    
    add_item( ({ "ceiling" }),
          "You note that ceiling is rather high for such a small "
        + "place.\n");
    
    add_item( ({ "floor", "mud", "tracks", "mud tracks" }),
          "Besides the obvious mud tracks from the various sailors who "
        + "frequent here, you don't see much else.\n");
        
    // Call custom create function
    create_gsl_office();
    
    // Add the timetable after the custom create call to allow them to
    // specify the file.
    if (strlen(query_timetable_file()))
    {
        add_object(query_timetable_file());
    }
}

varargs public int
get_leaflet (string str)
{
    object leaflet;
    
    if (!str
        || str != "leaflet")
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (objectp(leaflet = clone_object(LEAFLET)))
    {
        leaflet->move(TP);
        write("You pick a leaflet from the heap on the desk.\n");
        tell_room(QCTNAME(TP) + " picks up a leaflet from the heap "
            + "next to the desk.\n");
    }
    
    return 1;
}

public void
set_timetable_file(string file)
{
    Timetable_file = file;
}

public string
query_timetable_file()
{
    return Timetable_file;
}

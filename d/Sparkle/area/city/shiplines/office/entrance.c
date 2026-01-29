/*
 * Genesis ShipLines - Sparkle office.
 * TAPAKAH, 10/2008
 * To be transferred later into /d/Sparkle
 */

#include <macros.h>
#include <stdproperties.h>
#include "/d/Sparkle/area/city/shiplines/lib/gs_office.h";

inherit GSL_OFFICE_BASE;

// Defines
#define EXIT_TO_PIER    "/d/Genesis/start/human/town/pier7"
#define EXIT_TO_ROOF    "/d/Genesis/start/human/town/tower_roof"

// Prototypes
public int      check_paid();

/* 
 * Function:    create_gsl_office
 * Description: Mask this customizable creation function to add objects
 *              and descriptions to your ShipLines office. The timetable
 *              is added automatically. Simply call set_timetable_file
 *              to specify the file.
 */
public void
create_gsl_office() {

  set_short("Inside the Sparkle Office of Genesis ShipLines");
  set_long("You are inside the Sparkle Office of Genesis ShipLines "
           + "Company. Currently it is a relatively small hall, albeit with "
           + "a very high ceiling. You notice some doors and windows are "
           + "still locked. A door to the west however is open, and an old "
           + "goblin is sitting next to it behind a desk. Some kind of "
           + "stairway goes up, probably to the roof. On one of the "
           + "walls, you see a timetable bolted securely. \n");
  
  add_exit(EXIT_TO_PIER, "north");
  add_exit(EXIT_TO_ROOF, "up");
  add_exit("toilet_entrance", "west", &check_paid());
  
  add_npc(GSL_OFFICE_DIR + "ticket_engineer", 1, &->equip_me());
  add_npc(GSL_OFFICE_DIR + "toilet_keeper", 1, &->equip_me());
  
  add_item(({"windows", "window"}),
           "Through the window in the south wall you can see the Pensea of " 
           + "Sparkle. The rest of the windows are closed and locked.\n");
  add_item( ({ "stairway", "stair", "stairs", "stair way",
               "steps", "staircase" }),
            "The stairs disappear out of sight to the roof the building.\n");
  add_item(({"doors", "door"}),
           "Most of the doors seem to be closed and locked. "
           + "The door in the western direction is open. An old goblin sits "
           + "behind a desk next to it.\n");
  add_item(({"box" }),
           "A simple cardboard box that is currently empty. It "+
           "is closely watched by the goblin behind the desk.\n");
  add_item( ({ "desk", "wooden desk", "simple desk",
               "simple wooden desk" }),
            "A new simple wooden desk. A large cardboard box is sitting on it, "
            +"and a heap of leaflets is piled next to the box.\n");
  
  set_timetable_file(GSL_OFFICE_DIR + "timetable");           

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_current.txt");
}

public int
check_paid() 
{
    // Right now, toilet is not yet open.    
    object toilet_keeper;
    if (objectp(toilet_keeper = present("toilet_keeper", this_object())))
    {        
        toilet_keeper->command("say Sorry, da toilit iz nut opin yet!");        
    }
    else
    {
        write("The door seems to be locked. You'll just have to "
            + "hold it until the toilet keeper returns.\n");
    }
    return 1;        
//  return TP->query_prop(PAID_FOR_TOILET_USAGE);
}

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit DWARF_IN;

#define CAIRN "/d/Ansalon/estwilde/plains/cairn_entry"

int open_door = 0;

void
reset_dwarf_room()
{
    return;
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("You stand within the ancient stone walls "+
    "of a dwarven cairn. Dust of the ages lies thick "+
    "on the floor here, undisturbed for many years. "+
    "A dark passage leads off to the west, leading deeper into "+
    "the cairn.@@portal_desc@@\n");
    add_item(({"ancient stone walls","stone walls","walls"}),
      "Ancient walls of stone rise to a low ceiling in this "+
      "cairn.\n");
    add_item(({"ceiling","low ceiling"}),
      "Just above your head is the ceiling of the cairn. It is "+
      "low, typical of dwarven design.\n");
    add_item(({"cairn","ancient dwarven cairn","dwarven cairn"}),
      "You stand within the resting place of a dwarven warrior "+
      "of the Neidar clan.\n");
    add_item(({"floor","dust"}),
      "The floor here is covered with dust. You doubt anyone has "+
      "been here for a long time.\n");
    add_item(({"passage","dark passage"}),
      "To the west, a passage leads deeper into the gloom of the "+
      "dwarven cairn you presently stand in.\n");
    add_item(({"eastern wall","door","small door"}),
      "The outline of a small door can be made out in the " +
      "eastern wall here. It looks like it would take " +
      "a bit of strength to open.\n");

    DARK;

    add_exit(ROOM + "c2","west",0);
    reset_dwarf_room();
}

int
leave_cairn()
{
    write("You step out of the gloom of the cairn and into "+
    "the fresh air of the plains of Estwilde...\n");
    return 0;
}

string
short_descr()
{
    return "within an ancient dwarven cairn";
}

/* Note : Do not call open_door from this room. Call 
 * it from ~plains/cairn_entry.c with unlock_cairn_door()
 * When closing it, do it from this room with close_door()
 */

void
open_door()
{
    if(open_door)
   return;
    tell_room(TO, "Suddenly, the portal opens to the " +
   "outside realms!\n");
    TO->add_exit(ROOM + "cairn_entry","portal","@@leave_cairn");
   open_door = 1;
}

void
close_door()
{
    if(!open_door)
   return;

    open_door = 0;
    tell_room(TO, "Suddenly, the portal closes with a " +
    "resounding 'thud'.\n");
    TO->remove_exit("portal");
    CAIRN->lock_cairn_door();
}  

int
query_open_door()
{
    return open_door;
}

string
portal_desc()
{
     if(open_door)
    return " An open portal leads out of the cairn here.";
     else
    return " The passageway seems to end here, strangely " +
     "with some sort of sense of finality.";
}

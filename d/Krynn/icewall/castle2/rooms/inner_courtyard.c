#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

object ob, fountain;

void
create_icewall_room()
{
    fountain = clone_object(OBJK + "fountain.c");
    fountain->move(TO);          

    set_short("Inner courtyard");
    set_long("@@long_descr");


    add_exit("storage1","south");
    add_exit("stable","west");
    add_exit("tunnel_gate","east");
    add_exit("courtyard_north","north");

    add_item(({"fresh snow","snow"}),"Everything here is covered " +
     "with snow, but strangely enough, the fountain produces " +
     "fresh and warm water.\n");

    add_item("castle","Situated on top of a huge rock outcropping, " +
     "Icewall Castle is a sturdy, compact fortress with smooth " +
     "ice-covered walls, and dark holes of archers' slits. " +
     "In a different age, it must have been a formidable " +
     "stronghold. Today, it loses the battle with a glacier finger " +
     "which slowly, but unstoppably consumes the castle. " +
     "The fortress consists of two buildings, a main one to the " +
     "south, and a lower, U-shaped one to the north, west, and " +
     "east. On the northeast side of the castle, the glacier already " +
     "reaches over the top of the roofed battlements, flowing inside.\n");
    add_item(({"building","buildings"}),"Which building do you wish " +
     "to examine? The main one, or the lower one?\n");
    add_item(({"main building","main structure"}),"The main " +
     "structure to the south stands on the edge of the icy cliff. " +
     "Long ago, on the upper floors of it lived the lord of the castle " +
     "with his family, while the lower floor was most likely " +
     "occupied by the servants, maids, and kitchen staff. " +
     "As most castles, the building probably has a cellar " +
     "sublevel, used for storing foods, supplies, and the " +
     "occasional prisoner.\n");
    add_item(({"lower building","lower structure"}),"The lower " +
     "U-shaped structure surrounding the courtyard makes for the " +
     "castle's compact build. Long ago, it housed the castle's garrison" +
     " The main building, located at the " +
     "edge of a cliff is inaccessible from the ground in terms " +
     "of a military siege. The lower building, with its thick " +
     "walls, serves both the role of three-way battlemants " +
     "and a difficult obstacle for invading troops, as it covers " +
     "all the flat ground on the rocky outcrop, leaving only steep " +
     "cliffs on all sides - without a ledge that could be used " +
     "as a bridgehead. The compact build of the castle also " +
     "protects it from aerial assaults, as there are no open " +
     "battlements dragons could ravage with their breaths. " +
     "Today, in the age of ice, the castle looses its battle " +
     "against a glacier, a finger of which is already two " +
     "stories high and flowing over the northeast portion of " +
     "the lower building.\n");
    add_item(({"tunnel","massive tunnel"}),"The tunnel is " +
     "blocked at the far end by a huge gate. It " +
     "appears as if the owner of the castle does not expect " +
     "any guests soon... or has enough manpower to open and " +
     "close the collosal gate as he pleases.\n");
    add_item(({"stable","stables"}),"To the west a wide, double " +
     "gate opens into the castle's stables. Both doors have been " +
     "opened wide, and blocked, allowing the winter to enter.\n");

    set_tell_time(800);

    add_tell("Water sparkles as it cascades down into the tiny " +
      "pool of the fountain.\n");
    add_tell("Fresh snow falls from the cloudy sky.\n");
    add_tell("Wind picks up quite suddenly, scattering " +
     "snow in circles around you.\n");
    add_tell("You think you have just heard a strange shriek " +
     "carried here by the everpresent freezing wind.\n");
    add_tell("Snow whirls about you, creating myriad of patterns... " +
     "There is a strange beauty in them...\n\n\n" +
     "You shiver and slap your face. It must be the cold.\n");
    add_tell("White clouds pass high over you. Its " +
     "getting colder by the minute.\n");
}

void

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string

long_descr()

{ return ("" +
   "Fresh, icy snow covers the grounds of this inner courtyard. " +
   "To the south stands the three story high main building " +
   "of the old Icewall Castle. Further to the north, and " +
   "closely to the west and east, " +
   "a two story high, U-shaped building embraces the courtyard " +
   "and connects to the main structure. A massive tunnel through the " +
   "east part of the lower building leads to the castle's gate " +
   "and drawbridge. To the west open the castle's stables, though " +
   "its highly doubtful any mundane horse could survive such harsh " +
   "climate for long. The castle itself definitely deserves a " +
   "second view, as there are not many such strongholds left on " +
   "Krynn today.\n");
  
}
             
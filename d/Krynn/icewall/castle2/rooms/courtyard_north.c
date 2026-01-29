#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"

#include <macros.h>
#include <stdproperties.h>
inherit ICEOUTROOM;




void
create_icewall_room()
{
    object door;

    set_short("North part of the inner courtyard");
    set_long("@@long_descr");


    add_exit("inner_courtyard","south");
    //add_exit("smithy","west");
    add_exit("mino_garrison","east");

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
    add_item(({"smithy","primitive smithy"}),"To the west, " +
     "someone has situated a primitive smithy. An anvil, a dim-lit " +
     "fireplace and a crooked sharpening wheel can be seen from " +
     "here.\n");
    add_item("barracks","The ironwood doorway to the barracks has " +
     "been repeatedly scratched and in places even deeply gauged " +
     "on the overhead part of the frame. You wonder what " +
     "kind of troops has been stationed there...\n");

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


     door = clone_object(OBJK + "ornatedoor");
     door->move(this_object());


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
   "A bit further to the south stands the three story high " +
   "main building of the old Icewall Castle. Closely to the north, " +
   "west and east, " +
   "a two story high, U-shaped building embraces the courtyard " +
   "and connects to the main structure. " +
   "To the west a primitive smithy used to be, and " +
   "to the east open the garrison barracks. On the north side of " +
   "the courtyard you can see sturdy ironwood doorway. " + 
   "The castle itself definitely deserves a " +
   "second view, as there are not many such strongholds left on " +
   "Krynn today.\n");
  
}
   

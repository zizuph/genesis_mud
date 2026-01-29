/* Standard plateau at the top of Mount Kyrus in Calia. 
   Template based on std_tunnel.c in Gondor.

    
   History:
           5/4/96     inherit from kr_room            Maniac
          27.3.95            created                  Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/kr_room";
#include "/sys/stdproperties.h"


/* Give palace description relative to position */
string
palace_position(int pos)
{
    switch (pos) {
        case 1: return "The palace is quite a distance away from here. " +
                       "The road runs north towards the palace and " +
                       "east down the mountain side. ";
                break;
        case 2: return "The palace is still a good hundred yards away. " +
                       "The road runs north towards the palace and " +
                       "south towards the southern mountain side. ";
                break;
        case 3: return "The palace is very close now. " +
                       "The road runs north to the palace gates " +
                       "and south towards the southern mountain side. "; 
                break;
        default: return "";
                 break;
   }
}



/*
 * This function defines the room.
 */
void
make_the_room(string extra_long, int position)
{
    if (!extra_long) extra_long = ""; 

    set_name("road");
    set_short("Crystalline road on plateau of Mount Kyrus");
    set_long(
       "You are on a plateau at the top of " +
       "Mount Kyrus. A pale mist is all about you at this high altitude, " +
       "but you can make out the glittering Palace of Caliana to your " +
       "north, at the end of the crystalline road on which you stand. " +
       "The road bisects the plateau, which is roughly elliptical in " +
       "shape, stretching " +
       "out far in all directions from here" + ((position == 1) ? 
       " except to the south where its edge is quite close. " :
       ". ") +
       "You notice that the surface " +
       "of the plateau has been skilfully levelled to a great smoothness " +
       "so that there is scarcely a bump in the road. " + 
       palace_position(position) +
       extra_long); 
          
    add_item(({"mist", "pale mist"}), "A thin pale mist is all about " +
        "you since you are now at quite a high altitude. One cannot " +
        "see far above or below from here.\n"); 

   add_item(({"palace", "crystalline palace", "palace of caliana"}),
       "The palace is fortified and very grand in appearance. Made of " +
       "crystal, it glitters in the light, giving it a somewhat magical " +
       "air.\n");
 
    add_item(({"road", "crystalline road"}), "The road surface is made " +
         "of crystal. The path on which it was based is very ancient, " +
         "perhaps thousands of years old.\n");

    add_item(({"view"}), 
        "A pale mist hangs in the air at this high altitide. " +
        "The mist is stopping you " +
        "from seeing the view of the lands below from here; " +
        "a pity as it would surely be magnificent from this " +
        "height.\n");

    add_item(({"plateau"}), "You are currently on the plateau " +
        "at the top of Mount Kyrus, which is roughly elliptical " +
        "in shape and some three hundred yards across at its longest. " +
        "The surface of the plateau appears to have " +
        "been artificially levelled, and a crystalline road " +
        "runs along it towards the Palace of Caliana, which is " +
        "to your north.\n");

    add_item(({"mountain", "mount kyrus"}), "The mountain is huge " +
        "and imposing, the most striking natural landmark in all of " +
        "Calia, whether seen up close or from a distance. Its grey, " +
        "bare rock gives it a grim, mysterious appearance.\n");

    add_prop(ROOM_I_INSIDE, 0);
}

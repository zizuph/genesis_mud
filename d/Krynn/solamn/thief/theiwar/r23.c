/* created by Aridor 04/19/94 */

#include "../local.h"

inherit LIGHTDARKROOM;

static string my_add_long = "The fact that there are no lightsources around, " +
      "and not even any means to fix a torch to the wall or the like, " +
      "lets you assume the inhabitants of this place must be able to " +
      "see in the dark.\n";

void
create_ld_room()
{
    set_short("In a cavern");
    set_long("@@my_long");
    add_item(({"footsteps","track","floor","footprints"}),"Clearly, " +
        "this place is inhabited, with denizens that walk on two " +
        "feet.\n");
    
    add_exit(THEIWAR + "r21", "southeast");
    add_exit(THEIWAR + "r26", "northeast");
    add_exit(THEIWAR + "r5", "down");
    
}


string
my_long()
{
    return "A passageway leading northeast and southeast. " +
      "You can hear loud clanking noises coming from somewhere " +
      "in the southeast. " +
      "On the western side of the passageway, a winding track appears " +
      "from down below, allowing the transport of heavy goods this way " +
      "as well. This place is quite wide and you notice it serves as a " +
      "meeting area, too. Strangely, there is no one around at the " +
      "moment, but you can see many footsteps in the debris and dust " +
      "on the floor. " + my_add_long;
}


void
make_light()
{
    tell_room(TO,"Suddenly, light floods the cavern from above.\n");
    LIGHT;
    my_add_long = "The cavern is flooded by a single beam of light entering " +
      "through a narrow hole high above you. The mines, northeast and down " +
      "from here, seem to be cast into darkness though.\n";
}

void
make_dark()
{
    ::make_dark();
    my_add_long = "The fact that there are no lightsources around, " +
      "and not even any means to fix a torch to the wall or the like, " +
      "lets you assume the inhabitants of this place must be able to " +
      "see in the dark.\n";
}

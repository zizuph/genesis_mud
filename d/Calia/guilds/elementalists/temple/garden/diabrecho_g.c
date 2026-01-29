/*
 * Garden Room of the Elemental Garden of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include <stdproperties.h>
#include "../defs.h"

inherit GARDEN_ROOM_BASE;
inherit "/d/Calia/lib/utility";

// Defines

// Prototypes

public void
create_garden_room()
{
    set_short("Sculptures inside a walled garden");
    set_long("This is a part of the walled garden surrounding the crystalline "
        + "Elemental Temple of Calia. This particular area is pretty flat "
        + "with an open lawn. Upon the lawn are large beautiful ice "
        + "sculptures. Of to the east side of the lawn is a small wooden "
        + "shed. Beside the shed there is a small well.\n\n"); 
    
    try_item( ({ "sculptures", "ice sculptures", "sculpture" }),
        "Dramatic ice sculptures in the shapes of drops of water, the "
      + "Calian waterfall, and the waves of Thalassia have been set up "
      + "on the lawn. The ice seems to be perpetually hard and it "
      + "reflects the light similarly to the crystalline Temple. As "
      + "you gaze upon them, you realize that from here, the skyline "
      + "is blurred by mist.\n");
      
    try_item( ({ "shed", "wooden shed", "small shed", "small wooden shed" }),
        "The wooden shed looks quite unremarkable. There is a small door "
      + "through which you can <enter> the shed. The shed doesn't seem "
      + "to have any windows.\n");
    
    try_item( ({ "small door", "door" }),
        "The small door provides the only visible entryway into the wooden "
      + "shed.\n");
    
    try_item( ({ "small well", "well" }),
        "A very simple well from which one can draw water from. You don't "
      + "see anything to draw the water with, however.\n");

    add_prop(OBJ_I_CONTAIN_WATER, 1); // so people can fill the watering can here.
    
    add_exit(ELEMENTALIST_GARDEN + "garden_01m", "southwest");
}

public void
init()
{
    ::init();
        
    add_action("enter_shed", "enter");
}

public int
enter_shed(string str)
{
    notify_fail("Enter what?\n");
    if (!strlen(str))
    {
        return 0;
    }
    
    if (parse_command(str, this_object(), " [small] [wooden] [garden] 'shed' "))
    {
        return move_living_special_exit(this_player(), 
            ELEMENTALIST_GARDEN + "shed", str, 
            ({ "You enter the " + str + ".\n",
               "enters the " + str + ".\n",
               "enters the " + str + ".\n" }));
    }
    
    return 0;
}

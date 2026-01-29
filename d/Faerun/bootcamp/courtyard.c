#pragma strict_types

#include "/d/Faerun/defs.h"
#define PATH "/d/Faerun/bootcamp/balcony"

#include <stdproperties.h>

inherit "/std/room";

public void
create_room()
{
    //0 means outdoors, and 1 means indoors for this prop
    remove_prop(ROOM_I_INSIDE);

    set_short("A tranquil courtyard");
    
    set_long("You walk out into an enclosed, serene courtyard. There are " +
        "many different blossoming trees and flowers planted along the " +
        "perimeter. English ivy crawls over the marble walls of the " +
        "garden. There is a statue in the center of the courtyard, resting " +
        "under a giant weeping willow.\n");

    add_item(({"trees","tree"}),
        "There are cherry trees growing near the walls of the courtyard. " +
        "Intricately placed around the statue are four dogwood trees.\n");

    add_item(({"ivy"}),
        "The ivy is cascading down the marble walls, dark green against " +
        "the white marble.\n");
    
    add_item(({"statue"}),
        "Standing in the center of the courtyard is a perfect depiction of " +
        "Amore e Psiche, or Psyche revived by Cupid's Kiss. The statue " + 
        "seems to breathe life, just as if Psyche were truly being awakened " +
        "by the kiss of her lover.\n");
        
    add_item(({"willow","weeping willow"}),
        "This giant majectic tree stands behind the lovers locked in their " +
        "eternal embrace. The tree is tall and the limbs droop down, " +
        "carressing the couple as the wind blows the branches softly " +
        "about.\n");
    
	add_item(({"lamp-post","post","lamp"}),
	    "Delicate flames can be seen inside the glass casing of the " +
		"lamp-post. It appears clean and well maintained.\n");
	
    add_exit("/d/Faerun/bootcamp/lounge", "lounge");
    add_exit("/d/Faerun/bootcamp/fronthall","hall");
    add_exit("/d/Faerun/bootcamp/balcony", "balcony", 0, 1, 1);
}

public void
hook_smelled(string str)
{
    switch(str)
    {
    case "ivy":
	write("Your nostrils are filled with a vaguely "+
	"spicy, waxy, sharp scent.\n");
	break;

    case "flowers":
	write("The scent of various flowers is in the air.\n");
	break;

    default:
	write("The scent of blossoming flowers is in the air, "+
	    "you can also make out the scent of cherries from "+
	    "amongst the trees.\n");
	break;
    }
}

void
init()
{
    ::init();
    add_action("do_enter","enter");
}

public string
do_search(object pl, string arg)
{
    if (IN_ARRAY(arg,
        ({ "lamp", 
           "post", 
           "lamp-post", 
           "lamp post",}) ) == 0)
    {
        return "Your search reveals nothing special.\n";
    }

		return "The lamp-post is tall and had six wicks housed " +
			"inside a glass casing. The lamp-post is lit.\n";

}

public int
do_enter(string str)
{
    if(!strlen(str))
    {
        notify_fail("What did you wish to enter?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
        " [in] [through] [over] [the] [tall]"
      + " [black] 'lamp-post'"))
    {
        notify_fail("Enter what? The lamp-post?\n");
        return 0;
    }

    write("The air becomes liquid and unclear and you feel transported.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " arrives\n");
    tell_room(PATH, QCTNAME(this_player()) + " arrives\n");
    this_player()->move_living("M", PATH, 1, 0);
    return 1;
}

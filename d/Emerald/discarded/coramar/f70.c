/*
 * F70.C
 * This is the entrance to the hidden shelter in the Coramar Forest.
 * The hut, through a door to the east here, is a shelter against
 * everything in the forest. None of the NPCs of the forest will
 * ever follow a player inside.
 * - Alaron Feb 17, 1998
 */

#include "coramar.h"
#include "dirheader.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>

inherit BASEFOREST;




void
create_forest()
{
    set_short("The end of a narrow path in the forest");

    set_long("   The narrow, short path comes to an abrupt halt here. The small "+
	     "trees hanging over the path seem to prevent the annoying vines from "+
             "dropping all the way to the forest floor, and the mist seems thinner "+
             "here. As a result, the view is almost clear of a small, square structure "+
             "just a few meters to the east. The lack of breeze blowing between the "+
    	     "crease not only creates a quiet, almost tranquil setting, but stops "+
             "the eerie, almost haunting noise the wind generates.\n\n");

    add_item( ({"structure", "small structure", "house", "hut","east"}),
	     "Peering east at the structure, you are instantly struck by the amount of "+
             "moss covering its surface. A few seconds later you realize why you "+
             "thought it was odd. There is moss growing on all four sides and the roof!"+
             "You then suddenly notice the familiarity of the shape. The structure before "+
             "you is a small hut. You can now make out the details of the trees strung "+
             "together for the roof and the walls. A depression in the center of the "+
             "small hut that is covered in moss could possibly be a door.\n");	


    
    reset_euid();
    clone_object(CORAMAR_OBJ+"hutdoor_out")->move(this_object(),1);
}



/*
*   by Amelia for use in the Light Forest
	This is the beginning of the Light Forest.
*/
inherit "/std/room";
#include "defs.h"
#include <stdproperties.h>
#include <macros.h>


create_room() {

	set_short("A wooded area");
	set_long("You are on a path which leads east toward a forest "+
		"of mostly oak and maple trees.  The forest seems to "+
		"emanate light.  As you breathe deep of the fresh "+
		"air, you catch the scent of wildflowers.  Birds "+
		"and other small animals appear occasionally.  "+
		"You have the feeling, the forest is full of life.\n");
	add_item((({"tree", "trees", "oak trees", "maple trees"})),
         ("The trees are older trees although not huge.\n"));
	add_item((({"forest"})),
          ("The forest seems filled with diffused sunlight.\n"));
	add_item((({"grass", "moss"})),
         ("New spring grass and soft moss carpet the path.\n"));
	add_item((({"path"})),
           ("The path is partially obscured by new grass and moss.\n"));
	add_item((({"flower","flowers","wildflower","wildflowers"})),
           ("Daisies, violets and wild roses grow in abundance along "+
            "side the path.\n"));
	add_item((({"bird", "birds","animal","animals","small animals"})),
		("Every now and then you catch a glimpse of "+
		"a sparrow, chipmunk, or squirrel.\n"));
	add_exit("/d/Calia/amelia/workroom", "workroom", 0, 0);
	add_exit((FPATH+"forest_E_3a"), "east", 0, 0);


	add_prop(ROOM_I_LIGHT, 1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 0);
}


/*
*	coder(s):		Amelia
*			coded 1/95, updated 5/95
*/
inherit "std/room";
#include "room_tell.c"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/sys/macros.h"

void
create_room()
{
     set_short("Somewhere in the light forest");
     set_long("The path is covered in moss and continues deeper into "+
              "the eastern region of the forest.  Wildflowers grow along "+
              "both sides of the path.  Sunlight filters through the bower "+
              "of leaves.  The path ahead twists and turns and is obscured "+
              "by greenery.  Further from the path on either side, the "+
              "verdant growth gets thicker with bushes, trees, and shrubs.  "+
              "Some look thorny, so perhaps it is better to stay on the path "+
		"for now.\n");

      add_tell("Sunlight feels warm on your face and makes you blink.\n");
	set_tell_time(120);
      add_tell("From somewhere nearby you can hear the cheerful sound "+
               "of frogs croaking lustily.\n");
      add_tell("A gentle, soft breeze caresses you.\n");
      add_tell("The scent of wild violets wafts up to your nose.\n");

      /* various items to examine */

      add_item((({"sunlight", "light"})), ("The light makes everything "+
                  "appear bathed in a warm glow.  It makes you feel warm "+
                  "and invigorated.\n"));
       add_item((({"moss", "path"})),
             ("Thick green moss carpets the path and cushions your steps.\n"));
       add_item((({"squuirrel"})), ("The grey squirrel appears "+
               "somewhat upset by your presence, but remains high up out "+
               "of reach.\n"));
       add_item((({"wildflower", "flower", "wildflowers", "flowers"})),
              ("You can see wild violets and daisies growing all along the "+
               "path.\n"));
       add_item((({"daisy", "daisies"})),
                ("These flowers have a golden center, with white petals "+
                 "all around.\n"));
       add_item((({"violet", "violets"})), 
                ("There are white, yellow and purple violets here.  They "+
                 "are very delicate and have a lovely scent.\n"));
       add_item((({"butterfly", "blue and gold butterfly"})),
             ("You don't know the name of this butterfly, but it is very "+
              "beautiful, as it pauses to drink nectar from the flowers.\n"));
       add_item((({"leaf", "leaves"})), 
             ("The leaves are all shades of green from the variety of "+
              "trees here.\n"));
       add_item((({"tree", "trees"})),
             ("Just off the path are maple, oak, and sassafras trees. "+
              "They are not very thick here, allowing the sunlight to filter "+
              "through their leaves.  Yet their branches form a bower "+
              "over the mossy path.\n"));
       add_item((({"bush", "bushes", "shrub", "shrubs"})),
             ("Bushes and shrubs of various kinds grow further away from "+
              "the path.\n"));
       

	add_exit((FPATH+"forest_E_3a"), "west", 0, 0);
	add_exit((FPATH+"pond1.c"), "northeast", 0, 0,);

       /*  Properties of outside room */

       add_prop(ROOM_I_LIGHT, 1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 0);
}

void
enter_inv(object ob, object from)
{
	::enter_inv(ob, from);
	if (interactive(ob))
	start_room_tells();
}


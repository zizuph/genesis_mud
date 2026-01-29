/*
*	coder(s):		Amelia
*			coded 1/95, updated 5/95, again 9/12/96
*       Modified by Bishop of Calia, 5.2.99, added exits to elemental
*       area.
*                       
*/
inherit "/d/Calia/std/room_tell_room";
#include "/sys/stdproperties.h"
#include "pond.h"
#include "/sys/macros.h"

void
create_room()
{
     set_short("Somewhere in the light forest");
     set_long("The path is covered in moss and continues deeper into "+
              "the forest. Wildflowers grow along "+
              "both sides of the path.  Sunlight filters through the bower "+
              "of leaves.  The path ahead twists, turns and forks" +
              " amid the greenery.  Further from the path on either side, the "+
              "verdant growth gets thicker with bushes, trees, and shrubs.\n");

      add_tell("Sunlight feels warm on your face and makes you blink.\n");
      set_tell_time(200);
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
       add_item("path", "The path is narrow, but you can probably" +
           " follow it without getting torn by the thorny bushes.\n");
       

	add_exit(ZIMA+"sfor2.c", "south", 0,0);
	add_exit(FPATH+"pond1.c", "northwest",0,0);
        add_exit(FPATH+"epath1.c", "northeast",0, 0);

       /*  Properties of outside room */

       add_prop(ROOM_I_LIGHT, 1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 0);
}


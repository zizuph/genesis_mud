/*******************************************************************\
| BASE_ROOM.C                                                       |
+-------------------------------------------------------------------+
| Base room module for everything in the meadows area.              |
\*******************************************************************/

/*
 * 02/07/20 Arandir	Created
 * 02/08/17 Arandir     Incorporated suggestions by Tijgen
 * 02/09/12 Arandir     Typo fixes
 * 02/09/17 Arandir     Items added
 *
 */

#include "../defs.h"

inherit DG_ROOM_BASE;

inherit DG_CLOCK_LIBS;

//-------------------------------------------------------------------

/*******************************************************************\
| Items A-F                                                         |
\*******************************************************************/

void md_item_forest_south ()
{
  add_item (({ "forest", "tree", "trees" }),
    "The forest obscures your view towards the south.\n");
}

/*******************************************************************\
| Items G-L                                                         |
\*******************************************************************/

void md_item_countryside ()
{
  add_item (({ "country", "countryside" }),
    "As you travel farther away from the sea, you near the point " +
    "where the lowlands give way to a vast mountain range which " +
    "looms over the horizon.\n");

  add_item (({ "horizon", "outline" }),
    "The jagged outline of a mountain range forms most of your horizon.\n");
}

void md_item_grass ()
{
  add_item (({ "grass", "stalks", "blossoms", "flowers", "plants", "ground" }),
    dg_embed_when_spring ("Bright green grass surrounds your feet. A few oxlips and pansies add a joyful touch to the colors that surround you.") +
    dg_embed_when_summer ("The grass around you is full of flowers. Daisies and buttercups mix with ragwort and thistle in a colorful mosaic that pleases the eye.") +
    dg_embed_when_autumn ("The plants around you are getting ready to rest after a plentiful summer. Only a few blossoms are left.") +
    dg_embed_when_winter ("Gently touching the withering grass, you can feel the strength hidden in it, eagerly awaiting coming of the next spring.") +
    "\n" +
    dg_embed_action ("stoops to take a better look at the grass."));

  add_item (({ "oxlip", "oxlips", "pansy", "pansies", "daisy", "daisies",
               "buttercup", "buttercups", "ragwort", "thistle" }),
    dg_embed_when_spring ("A colorful mixture of flowers decorates the bright green spring grass.") +
    dg_embed_when_summer ("A colorful mosaic of flowers paints intriguing patterns on the green grass.") +
    dg_embed_when_autumn ("The flowers around you sport the brownish color that marks the coming of winter.") +
    dg_embed_when_winter ("The flowers around you are resting in winter.") +
    "\n");

  add_item (({ "colors", "mosaic" }),
    dg_embed_when_spring ("Bright green is the color that prevails around you. The few flowers that peek through the grass hint at more colors to come with the summer.") +
    dg_embed_when_summer ("The flowery mosaic around you has any color you want, from the sky blue to the blood red.") +
    dg_embed_when_autumn ("The colors around you are tinted with the autumn brown.") +
    dg_embed_when_winter ("Pale shades are all that remains of the once bright colors.") +
    "\n");

  add_item (({ "feet" }),
    "You stare at your feet. They are where you would expect them. Honest." +
    "\n" +
    dg_embed_action ("stares down as if looking for something in the grass."));
}

/*******************************************************************\
| Items M-R                                                         |
\*******************************************************************/

void md_item_mountains ()
{
  add_item (({ "mountain", "mountains", "hill", "hills",
               "range", "mountain range" }),
    dg_embed_when_night (
      "Even though it is night, the jagged peaks to your north " +
      "obscure what bits of sky are visible. The images of flying " +
      "buttresses and deep gullies, which could lie anywhere in your " +
      "vicinity, assault your imagination.") +
    dg_embed_when_not_night (
      "Staring towards the distant peaks to your north, you feel " +
      "the sheer majesty of the jagged cliff faces press against " +
      "your senses.") +
    " A flicker of thought crosses your mind. Who knows, perhaps it " +
    "was this savage beauty that made the locals dub the range " +
    "Dragon Mountains, recognizing the impeccable majesty " +
    "that connects it with its namesakes.\n" +
    dg_embed_action ("stares towards the mountains."));

  // No, no and no. It was not the constant critique of the area testers
  // that made me add this particular item. It is not necessarily
  // true of the other items though ... :-)

  add_item (({ "beauty" }),
    "It is said that beauty is in the eye of the beholder. But " +
    "somehow you feel that the beauty of the mountains is " +
    "beyond the mortal critique.\n");
}

void md_item_rock_cliffs ()
{
  add_item (({ "rock", "rocks", "group of rocks" }),
    "The rocks that form the mountain side to your north are " +
    "pale and unremarkable, except for an occasional streak " +
    "of dark red that runs along some of the sharper edges.\n");
  add_item (({ "streak", "streaks" }),
    "Dark red patches cover some of the sharper edges of the rocks. " +
    "They resemble stains of dried blood, but are more likely just " +
    "marks of higher quantities of iron.\n");
  add_item (({ "blood" }),
    "You decide that the patches definitely are not blood. They " +
    "surely are ingrained too deep in the rock for that.\n");
}

/*******************************************************************\
| Items S-Z                                                         |
\*******************************************************************/

md_item_trees_cliffs ()
{
  add_item (({ "twisted tree", "twisted trees" }),
    "Twisted trees cling to life in few places on the cliffs.\n");
  add_item (({ "crevice", "crevices" }),
    "The cliff face is creased by cracks and crevices. Amazingly, " +
    "some of them hold enough soil to support trees.\n");
}

//-------------------------------------------------------------------

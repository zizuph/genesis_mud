/*******************************************************************\
| BASE_ROOM.C                                                       |
+-------------------------------------------------------------------+
| Base room module for everything in the catacomb area.             |
\*******************************************************************/

/*
 * 03/07/19 Arandir	Created
 *
 */

#include "../defs.h"

inherit DG_ROOM_BASE;

//-------------------------------------------------------------------

/*******************************************************************\
| Items A-F                                                         |
\*******************************************************************/

void cc_item_cave_inside ()
{
  add_item (({ "cave" }),
            "You are inside a large cave, lit by sunlight " +
            "streaming in through several openings along " +
            "the walls. Around you, stone columns are " +
            "arranged in concentric circles, so tall " +
            "that you cannot see to the bottom of " +
            "the cave. Narrow stone walkways that " +
            "connect the columns appear to be the only " +
            "way of moving around the cave.\n");
  add_item (({ "ceiling" }),
            "You guess the ceiling of the cave is somewhere above you.\n");
  add_item (({ "wall", "walls", "opening", "openings" }),
            "The walls of the cave are rough, with several openings " +
            "spaced regularly around its perimeter shedding light on " +
            "the cave interior.\n");
}

void cc_item_columns_outer ()
{
  add_item (({ "column", "columns", "pillar", "pillars" }),
            "The massive stone columns of smooth stone are obviously " +
            "far from a natural phenomenon, though who would have built " +
            "them and why is beyond your guess. They appear designed to " +
            "support immense loads, but stop before reaching the " +
            "ceiling of the cave. In fact, the columns are gradually " +
            "shorter towards the center of the cave.\n");
  add_item (({ "center" }),
            "Albeit far from here, the center of the cave is quite " +
            "visible, but it appears to be just another column with " +
            "nothing on it.\n");
}

void cc_item_columns_inner ()
{
  add_item (({ "column", "columns", "pillar", "pillars" }),
            "The massive stone columns of smooth stone appear built " +
            "to support immense loads. The columns are obviously " +
            "arranged to provide a good view of the center of " +
            "the cave.\n");
  add_item (({ "center" }),
            "In the center of the cave is just another stone column, " +
            "but it appears as if its top is decorated somehow.\n");
}

/*******************************************************************\
| Items G-L                                                         |
\*******************************************************************/

/*******************************************************************\
| Items M-R                                                         |
\*******************************************************************/

/*******************************************************************\
| Items S-Z                                                         |
\*******************************************************************/

void cc_item_walkways_outer ()
{
  add_item (({ "walkway", "walkways", "arch" }),
            "The narrow walkways are chiseled from a different kind " +
            "of stone than the columns, with a rough surface and " +
            "greyish in color. Here and there, you also notice " +
            "the traces of chisels used to shape the stone. " +
            "Obviously, the walkways were not built at the same " +
            "time as the columns, and maybe not even by the same " +
            "builders.\n");
  add_item (({ "pattern", "weave" }),
            "Looking at the pattern of the columns and walkways, you " +
            "see what is a complex vortex of lines pointing towards " +
            "the center of the cave.\n");
}

void cc_item_walkways_inner ()
{
  add_item (({ "walkway", "walkways", "arch" }),
            "The narrow walkways are chiseled from a greyish stone. " +
            "Spanning from column to column, they provide the only " +
            "means of moving around the cave. They seem comfortable " +
            "enough, even if a bit frightening for lack of a railing " +
            "of any kind.\n");
  add_item (({ "pattern", "weave" }),
            "Looking at the pattern of the columns and walkways, you " +
            "feel like you are standing inside a blossoming rose, the " +
            "walkways, like petals, opening to a new day.\n");
}

//-------------------------------------------------------------------


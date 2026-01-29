/*******************************************************************\
| HALL_UPPER_NORTH.C                                                |
\*******************************************************************/

/*
 * 98/06/14 Cirion	Created
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 03/03/29 Arandir     Some polishing up
 * 03/08/04 Arandir     Sunlight is now time sensitive
 * 03/12/18 Arandir     Fixed a missing space typo
 *
 */

#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("northern end of the upper hall");
  set_long  ("The floor of the northern end of this hall " +
             "is made from an iron grille, through which " +
             "the lower great hall can be seen. " +
             dg_embed_when_night ("Starlight filters ") +
             dg_embed_when_not_night ("Sunlight floods ") +
             "through the leaded-glass doors that lead " +
             "out to the northern balcony. To the east is a " +
             "dark stone stairwell, and to the west is " +
             "a small room with a desk. The high, domed " +
             "ceiling, which continues to the south, is " +
             "ringed with a narrow stone ledge, atop which " +
             "stand many small statues.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("balcony_north", "north");
  add_exit ("stair_upper", "east");
  add_exit ("hall_upper_south", "south");
  add_exit ("member_post", "west");

  dg_add_entrance ("east", "You walk out of the dark landing into the north end of a large hallway.");

  m_item_statues_former (0, 50);

  add_item (({ "grille", "iron", "floor", "ground"}),
            "The floor is made from thick iron grille-work, " +
            "allowing a view to the lower great hall below. " +
            "The grille seems very old, but sturdy. " +
            dg_embed_livings ("hall_lower_north", "Through the grille, you can see ", " down below.", "The great hall below is quiet and empty.") +
            "\n");

  add_item (({ "east", "stair", "stairwell" }),
            "The eastern doorway opens into a dark stairwell " +
            "which rises both above and below.\n");
  add_item (({ "west", "post office" }),
            "The room to the west has a feeling of silence " +
            "eminating from it.\n");

  add_item (({ "light", "sunlight", "starlight" }),
            dg_embed_when_night (
              "The starlight is soft and comforting in the " +
              "way it clings to the walls.") +
            dg_embed_when_not_night (
              "The sunlight is warm. It seems to cling to the " +
              "walls with a tenacious hold.") +
            "\n");

  add_item (({ "ceiling", "roof" }),
            "The ceiling here is the northern half of a great, " +
            "shallow dome that extends to the southern end of " +
            "the hall. The dome is smooth, made from some " +
            "white stone, and unadorned. It is beautiful in " +
            "its simplicity.\n" +
            dg_embed_action ("stares up at the dome above."));
  add_item (({ "shelf", "ledge" }),
            "Ringing the base of the dome high above, and " +
            "continuing to the south, is a very thin ledge of " +
            "stone, supported by short, thick beams of wood " +
            "that angle out from the walls. Sitting atop the " +
            "ledge are many small wooden statues.\n" +
            dg_embed_action ("looks up at the ledge ringing the dome."));
  add_item (({ "desk", "table" }),
            "The desk in the room to the west is small and made " +
            "from pine. Inset into its back are many small " +
            "cubbyholes.\n");
  add_item (({ "balcony", "north" }),
            "The balcony through the leaded glass doors to the " +
            "north looks over the front entrance to the " +
            "monastery.\n");

  add_cmd_item (
    ({ "down","floor","" }), ({ "kneel" }),
    "You kneel down on the uncomfortable grille.\n");
  add_cmd_item(
    ({ "silence", "to silence", "the silence" }),
    ({ "hear", "listen", "enjoy" }),
    "Silence makes no noise.\n" +
    dg_embed_action ("tries futily to hear something."));
  add_cmd_item (
    ({ "wall", "dome", "ledge", "up" }),
    ({ "climb", "scale" }),
    "There is no way you could climb the wall, making " +
    "you wonder how they got the statues to the ledge " +
    "in the first place.\n" +
    dg_embed_action ("scratches and scrambles against the wall in a vain attempt to climb up."));
}

//-------------------------------------------------------------------


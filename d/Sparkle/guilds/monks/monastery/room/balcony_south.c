/*******************************************************************\
| BALCONY_SOUTH.C                                                   |
\*******************************************************************/

/*
 * 98/06/14 Cirion	Created
 * 00/12/26 Manat	Fixed a typo
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 03/04/25 Arandir     Polished up and bugfixed
 * 03/08/05 Arandir     Fixed references to sunlight
 *
 */

#include "../defs.h"

inherit M_ROOM_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("southern balcony");
  set_long ("This narrow stone balcony extends over the " +
            "southern garden. The intoxicating scent of flowers " +
            "wafts upwards, " +
            dg_embed_when_night ("and the soft shades of starlight ") +
            dg_embed_when_not_night ("and the warmth of the sunlight ") +
            "on the stone ledge gives a peaceful feeling to the " +
            "place. A wrought iron railing runs at waist level " +
            "along the balcony, etched with designs of ivy leaves. " +
            "To the north, a wooden lattice door leads into " +
            "a large hall.\n");

  add_exit ("hall_upper_south", "north");

  dg_add_entrance ("north", "You walk through the doorway out onto the southern balcony.");

  add_item (({ "rail", "railing", "iron"}),
            "It is a long, thin rail of iron that simply extends " +
            "around the perimeter of the balcony in a " +
            "semicircle. It is joined into the stone walls of " +
            "the monastery. Etched delicately on its surface " +
            "are leaves of ivy, all intertwined and connected " +
            "with thin vines.\n");
  add_item (({ "etching", "ivy", "image", "vine", "vines" }),
            "The etching on the long iron rail is done with " +
            "careful, precise craftsmanship, such that even " +
            "the spines of the leaves are visible.\n");
  add_item (({ "spine", "spines" }),
            "They show the care and effort that went into the " +
            "ivy etching.\n");
  add_item (({ "door", "wood", "lattice", "lattice door", "wooden door" }),
            "The door to the north is made from thin pine slats " +
             "of wood in a lattice construction. Through it you " +
             "can see the looming upper hall of the monastery. " +
             "The slats are far enough apart to let light and " +
             "fresh air inside.\n");
  add_item (({ "garden", "down", "below", "the garden" }),
            "The garden below breathes with life. A small, " +
            "circular path travels around a large tree in the " +
            "center of the garden, and in the four corners are " +
            "stone buildings. The scent of flowers and herbs " +
            "wafts upwards from the garden, past the balcony, " +
            "and up into the sheltering sky above.\n");
  add_item (({ "hall", "great hall" }),
            "The upper hall lies to the north. Its ceiling, the " +
            "roof of the monastery, is a shallow dome of white " +
            "stone.\n");

  add_cmd_item (
    ({ "flower", "air", "flowers", "scent" }),
    ({"smell", "sniff" }),
    "You breathe in deeply the intoxicating scent of the " +
    "living flowers below.\n" +
    dg_embed_action ("breathes in the air deeply."));
  add_cmd_item (
    ({ "etching", "etchings", "ivy", "rail", "spine", "spines"}),
    ({"touch", "trace" }),
    "The etchings on the warm iron railing are done so " +
    "delicately that you can barely feel them.\n" +
    dg_embed_action ("feels the iron railing."));
  add_cmd_item (
    ({ "sun", "stars", "light", "sunlight", "starlight" }),
    ({ "feel" }),
    dg_embed_when_night ("The flickering starlight feels like the gentlest of touches upon your face. ") +
    dg_embed_when_not_night ("The sunlight is warm upon your face.") +
    "It fills you with joy and life.\n" +
    dg_embed_action ("basks in the light."));
}

//-------------------------------------------------------------------


/*
 * File:    
 * Creator: Cirion, 1998.06.14
 * Purpose: Room in the monk's guild hall
 */
#pragma strict_types
#include "defs.h"

inherit ROOMBASE;

void
create_room ()
{
    set_short("southern balcony");
    set_long("This narrow stone balcony extends over the "
        + "southern garden. The intoxicating scent of flowers "
        + "wafts upwards, and the warmth of the sunlight "
        + "on the stone ledge gives a peaceful feeling to the "
        + "place. A wrought iron railing runs at waist level "
        + "along the balcony, etched with designs of ivy leaves. "
        + "To the north, a wooden lattice door leads into "
        + "a large hall.\n");
    add_item(({"rail","railing","iron"}),
        "It is a long, thin rail of iron that simply extends "
        + "around the perimeter of the balcony in a "
        + "semi-circle. It is joined into the stone walls of "
        + "the monastery. Etched delicately on its surface "
        + "are leaves of ivy, all intertwined and connected "
        + "with thin vines.\n");
    add_item(({"etching","ivy","image","vine","vines"}),
        "The etching on the long iron rail is done with "
        + "careful, precise craftsmanship, such that even "
        + "the spines of the leaves are visible.\n");
    add_item(({"spine","spines"}),
        "They show the care and effort that went into the "
        + "ivy etching.\n");
    add_item(({"door","wood","lattice","lattice door","wooden door"}),
        "The door to the north is made from thin pine slats "
        + "of wood in a lattice construction. Through it you "
        + "can see the looming upper hall of the monastery. "
        + "The slats are far enough apart to let light and "
        + "fresh air inside.\n");
    add_item(({"garden","down","below","the garden"}),
        "The garden below breathes with life. A small, "
        + "circular path travels around a large tree in the "
        + "center of the garden, and in the four corners are "
        + "stone buildings. The scent of flowers and herbs "
        + "wafts upwards from the garden, past the balcony, "
        + "and up into the sheltering sky above.\n");
    add_item(({"north","hall","great hall","through doorway","through door"}),
        "The upper hall lies to the north. Its ceiling, the "
        + "roof of the monestary, is a shallow dome of white "
        + "stone.\n");
    add_cmd_item(({"flower","air","flowers","the air","the flowers","scent"}), ({"smell"}),
        "You breath in deeply the intoxicating scent of the "
        + "living flowers below.\n"
        + VBFC_SAY("breathes in the air deeply.\n"));
    add_cmd_item(({"etching","etchings","ivy","rail","spine","spines"}), ({"touch","feel"}),
        "They etchings on the warm iron railing are done so "
        + "delicately that you can barely feel them.\n"
        + VBFC_SAY("feels the iron railing.\n"));
    add_cmd_item(({"feel"}), ({"sun","light","sunlight"}),
        "The sunlight is warm upon your face. It fills you "
        + "with joy and life.\n"
        + VBFC_SAY("basks in the sunlight.\n"));


    WIZINFO("This balcony looks over the south garden.\n");

    // where, command
    add_exit("hall_upper_south", "north");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("north", "You walk through the doorway "
        + "out onto the sunlit balcony.\n");
}


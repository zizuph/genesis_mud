/*
 * AVULAR_ROOM.c
 * Super-Class Room Inheritance file for most of the 
 * rooms within the city of Avular.
 * - Alaron Jan 2000
 */

#include "defs.h"
#include "/d/Emerald/sys/properties.h"
#include <stdproperties.h>

inherit EMERALDROOM;

void
create_avular_room()
{
    set_short("Room in Avular.\n");
    set_em_long("A room in Avular!\n");

}

nomask void
create_emerald_room()
{
    set_region_manager(AVULAR_REGION);
    /* All the outdoor rooms in Avular are engulfed by magical darkness */
    add_prop(ROOM_I_FREE_VAMP_DVIS, 2);
    add_prop(ROOM_I_LIGHT, -2);    
    
    /* Due to the intense darkness, its pretty much a snap to hide here */
    add_prop(ROOM_I_HIDE, 2);

    add_prop(ROOM_M_NO_TELEPORT_TO, 1);

    add_prop(ROOM_S_DARK_LONG,
             "   The darkness here seems beyond that of the darkest night. The "+
             "pitch black feels so thick and dense it is almost as if you could "+
             "reach out and feel the black emptiness. You can barely see your hands before your "+
             "face, let alone anything else here.\n\n");

    add_prop(ROOM_S_DARK_MSG,
             "The seemingly supernatural darkness is too thick to");


    /* Add a couple of basic room items that will pretty much exist anywhere outside */
    
    add_item( ({"up", "sky", "moon", "sun", "air"}),
             "You crane your head back and peer upward toward where the sky should be. Instead " +
             "of the sky, your eyes see nothing but an endless expanse of blackness. The black " +
             "is far darker than the darkest night you can imagine, not even a single ray of light "+
             "can be seen penetrating the blackness.\n");

    add_item( ({"down", "ground", "grass", "soil"}),
             "The ground is hard and mostly dry. Most of the plantlife seems at best bizarre, and at "+
             "worst, eerie and dangerous. The thin, short blades of grass are completely and totally "+
             "white. It boggles your mind that any plants can grow in this area devoid of light. It "+
             "appears that many of the plants have adapted, growing with little or no color, but "+
             "growing nonetheless.\n");

    add_item( ({"plants", "plantlife", "plant"}),
             "The plants are truly bizarre. Growing in shapes and sizes never before seen, the most "+
             "noticeable difference between these and other plants is that almost all of these plants "+
             "are completely white, having grown completely in the darkness. Those plants that do "+
             "contain color are colored various shades of dark purple and blue.\n");

    add_item( ({"dark", "darkness", "suffocating darkness", "blackness"}),
             "The darkness seems to be unnaturally dark and smothering. At times it feels "+
             "as though the darkness is pushing into your very throat, unconsciously "+
             "making you gasp in the cold air. Somehow you know that even with the "+
             "brightest torch, you would not be able to see very far in this pitch.\n");

    create_avular_room();
}

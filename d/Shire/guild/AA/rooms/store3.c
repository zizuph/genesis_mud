/*
 * Milan
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "../guild.h"

inherit SHIRE_ROOM;

void
create_room()
{
    set_short("Small room");
    set_long("This is a small room just east of the armoury, it is " +
        "empty aside from a long wooden shelf on the north wall and " +
        "a large hole that has been fenced off on the southern side " +
        "of the room. The room seems to be rather hot, and the smell " +
        "of smoke lingers in the air. An opening in the western wall " +
        "leads back towards the armoury.\n");

    add_item(({"wall","walls"}),
        "The walls are made of stone here, broken only by a long wooden " +
        "shelf on the north wall.\n");
    add_item(({"floor","down"}),
        "The floor is probably made of stone, although it is hard to " +
        "see through the layer of dirt covering it.\n");
    add_item(({"ceiling","up"}),
        "There is in fact a stone ceiling up above your head. It is " +
        "profoundly uninteresting.\n");
    add_item(({"dirt","soot"}),
        "The floor actually seems to be covered in soot, probably because " +
        "of the fire that constantly burns at the bottom of the hole " +
        "nearby.\n");

    set_no_exit_msg(({"northwest","north","northeast","east"}),
        "Yup. That's a real wall, not a fake one. You will have to " +
        "try moving in another direction.\n");
    set_no_exit_msg(({"southwest","south","southeast"}),
        "Fortunately the fence stopped you before you threw yourself " +
        "into the hole and the fire that burns inside it.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_exit(AA_DIR+"rooms/store2", "west");

    clone_object("/d/Shire/guild/AA/obj/shelf")->move(TO);
    clone_object("/d/Shire/guild/AA/obj/furnace")->move(TO);
}
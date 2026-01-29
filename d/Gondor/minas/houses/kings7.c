/*
 *  /d/Gondor/minas/houses/kings7.c
 *
 *  The House of Kings: Interior Six
 *
 *  Alto, 18 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"


#define INNER_MINAS "/d/Gondor/minas"


public void
create_gondor()
{
    set_short("Inside the House of Kings");
    set_long("You are in the southernmost part of the House of Kings. "
        + "This is a wide "
        + "vaulted chamber draped in great shadows thrown upon "
        + "the shrouded walls. From here can be "
        + "dimly seen many rows of tables, carved of marble. Upon "
        + "each table lies a seemingly sleeping form, hands folded, head "
        + "pillowed upon stone. The air feels as cold as death, and "
        + "your instincts scream for you to leave this place of "
        + "death at once.\n");


    clone_object(INNER_MINAS + "/obj/king_door_in")->move(TO);

    add_item(({"building", "tomb", "hall", "halls", "chamber"}), "The "
        + "House of Kings "
        + "is made entirely of "
        + "native stone. Its sheer size is enough to intimidate even the "
        + "bravest of hearts, and its sweeping arches are so beautiful "
        + "as to leave one breathless. Most "
        + "of the interior remains shrouded with shadow.\n");
    add_item(({"stone", "native stone", "blocks"}), "Tough stone quarried from "
        + "the foothills of Mount Mindolluin. You wonder how the huge "
        + "blocks could have possibly been transported to this place.\n");
    add_item(({"arches", "arch"}), "Above you, numerous "
        + "arches climb into the shadows. The great spandrels between each "
        + "arch are decorated with painted frescos.\n");
    add_item(({"shadow", "shadows"}), "Not much can be seen through them. "
        + "That is why they are called shadows. What they conceal must "
        + "remain, for now, a mystery.\n");
    add_item(({"fresco", "frescos", "painting", "paintings"}), "The "
        + "spaces between each pair of arches have been painted in "
        + "stark relief to depict various scenes of the "
        + "history of the Kings of Gondor. Many of the paintings depict "
        + "great battles of Men or between Men and the wretched creatures "
        + "of Mordor. Others "
        + "show grim-faced men wearing a crown among various settings "
        + "in the city.\n");
    add_item(({"ceiling"}), "The ceiling of the Tomb is lost in the "
        + "shadows. It is impossible to tell how far away it is.\n");
    add_item(({"dome", "pale dome"}), "The inside of the dome in the "
        + "House of Kings is rumoured to have magnificent artwork "
        + "painted and carved into it even greater than that in the "
        + "House of Stewards. Unfortunately the shadows "
        + "preclude even the most clouded view of its secrets.\n");
    add_item(({"wall", "walls"}), "Little can be seen of the walls beyond "
        + "the shadows. Some thing or things seem to move within the darkness, "
        + "but when you look closely there is nothing to be seen.\n");
    add_item(({"marble"}), "The tables appear to be made of marble .. cold, "
        + "unyielding and eternal.\n");
    add_item(({"hands"}), "The hands of each king are folded across "
        + "the breast. So clever was the manner in which each was embalmed "
        + "that the hands retain the colour and supple texture of life.\n");
    add_item(({"tables", "rows"}), "There are many rows of tables "
        + "in this great vaulted chamber. Near at hand you can see three tables, "
        + "but to the north there appear to be many more. "
        + "Each table, except for one of those close at hand, "
        + "bears the embalmed remains of a King of Gondor.\n");
    add_item(({"pillow"}), "Each King rests upon a block of stone "
        + "sculpted into the form of a pillow. They do not look very "
        + "comfortable.\n");
    add_item(({"dead", "forms", "kings", "corpses", "bodies"}), "From "
        + "here can be seen two Kings who, although long dead, have "
        + "been embalmed such that they appear to be only sleeping. Each "
        + "rests upon a table of marble.\n");
    add_item(({"form", "king", "corpse", "body", "table"}), "Which one? "
        + "There are three tables, but only two dead kings, near at hand.\n");
    add_item(({"first table", "first form", "first king"}), "On the "
        + "first table is inscribed Ondoher, King of Gondor.\n");
    add_item(({"second table", "second form", "second king"}), "On the "
        + "second table is inscribed Earnil II, King of Gondor.\n");
    add_item(({"third table"}), "On the "
        + "third table is inscribed Earnur, King of Gondor. Unlike the "
        + "other tables, however, this one does not have the body of a "
        + "king resting upon it, but is instead empty.\n");
    add_item(({"third king"}), "The body of Earnur is not housed in the "
        + "Tomb. He was lost in Minas Morgul and no word of him was ever "
        + "heard again in Middle Earth.\n");

    /* Make it inside, dark, and impossible to hide */

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_HIDE, -1);

    clone_object(INNER_MINAS + "/npc/spectre_minardil.c")->move(TO);


    reset_room();

}   
   

    












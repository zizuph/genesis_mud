/*
 *  /d/Gondor/minas/houses/stewards7.c
 *
 *  The House of Stewards: Interior Six (Pyre of Denethor)
 *
 *  Alto, 18 April 2001
 *
 *  Updated 2019.08.13, by Shanoga:
 *    Added ROOM_I_NO_TELEPORT
 *    Adjust reset_room to have the room ready for another quester
 *      if someone somehow left (bad teleport, death, etc)
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"


#define INNER_MINAS "/d/Gondor/minas"

object spectre, door;

void
reset_room()
{
    // Remove dropped keys
    FILTER_KEY_OBJECTS(all_inventory())->remove_object();

    if (!present(spectre))
    {
        spectre = clone_object(INNER_MINAS + "/npc/spectre_hurin.c");
        spectre->move(TO);
        spectre->command("emote slowly fades in from the shadows.");
    }
    if (!sizeof(FILTER_PLAYERS(all_inventory())))
    {
        door->set_open(1);
        door->set_locked(0);
    }
    ::reset_room();
}


public void
create_gondor()
{
    set_short("Inside the House of Stewards");
    set_long("You are in the northernmost part of the House of "
        + "Stewards. This is a wide "
        + "vaulted chamber draped in great shadows thrown upon "
        + "the shrouded walls. From here can be "
        + "dimly seen many rows of tables, carved of marble. Upon "
        + "most tables there is a seemingly sleeping form, hands folded, head "
        + "pillowed upon stone. Here, however, you see a table that is "
        + "empty. The air feels as cold as death, and "
        + "your instincts scream for you to leave this place of "
        + "death at once.\n");


    door = clone_object(INNER_MINAS + "/obj/steward_door_in");
    door->move(TO);

    clone_object(INNER_MINAS + "/obj/denethor_table")->move(TO);
    clone_object(INNER_MINAS + "/obj/ecthelion_table")->move(TO);


    add_item(({"building", "tomb", "hall", "halls", "chamber"}), "The "
        + "House of Stewards "
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
        + "history of the Stewards of Gondor. Many of the paintings depict "
        + "great battles of Men or between Men and the wretched creatures "
        + "of Mordor. Others "
        + "show grim-faced men bearing a white rod among various settings "
        + "in the city.\n");
    add_item(({"ceiling"}), "The ceiling of the Tomb is lost in the "
        + "shadows. It is impossible to tell how far away it is.\n");
    add_item(({"dome", "pale dome"}), "The inside of the dome in the "
        + "House of Stewards is rumoured to have magnificent artwork "
        + "painted and carved into it. Unfortunately the shadows "
        + "preclude even the most clouded view of its secrets.\n");
    add_item(({"wall", "walls"}), "Little can be seen of the walls beyond "
        + "the shadows. Some thing or things seem to move within the darkness, "
        + "but when you look closely there is nothing to be seen.\n");
    add_item(({"marble"}), "The tables appear to be made of marble .. cold, "
        + "unyielding and eternal.\n");
    add_item(({"hands"}), "The hands of each steward are folded across "
        + "the breast. So clever was the manner in which each was embalmed "
        + "that the hands retain the colour and supple texture of life.\n");
    add_item(({"tables", "rows"}), "There are many rows of tables "
        + "in this great vaulted chamber. Near at hand you can see "
        + "only two tables, "
        + "but to the south there appear to be many more.\n");
    add_item(({"pillow"}), "Each Steward rests upon a block of stone "
        + "sculpted into the form of a pillow. They do not look very "
        + "comfortable.\n");
    add_item(({"dead", "forms", "stewards", "corpses", "bodies"}), "From "
        + "here can be seen only a single Stewards who, although long dead, has "
        + "been embalmed such that he appears to be only sleeping. He "
        + "rests upon a table of marble.\n");
    add_item(({"form", "steward", "corpse", "body"}), "Only on the first "
        + "table is there the body of a Steward. The second table is at "
        + "present empty.\n");
    add_item(({"table", "tables"}), "Which one? There are two of them.\n");
    add_item(({"first table"}), "On the "
        + "first table is inscribed Ecthelion II, Steward of Gondor.\n");
    add_item(({"second table"}), "On the "
        + "second table is inscribed Denethor II, Steward of Gondor. Unlike the "
        + "other tables, however, this one does not have the body of a "
        + "steward resting upon it, but is instead empty.\n");

    /* Make it inside, dark, and impossible to hide */

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_HIDE, -1);
    
    /* Players cannot teleport to or from this room. */
    
    add_prop(ROOM_I_NO_TELEPORT, 1);

    spectre = clone_object(INNER_MINAS + "/npc/spectre_hurin.c");
    spectre->move(TO);
    spectre->command("emote slowly fades in from the shadows.");

    reset_room();

}   
   

    












/*
 *  /d/Gondor/minas/houses/stewards2.c
 *
 *  The House of Stewards: Interior One
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

public int   check_spectre();



public void
create_gondor()
{
    set_short("Inside the House of Stewards");
    set_long("You are just inside the great arch through which one "
        + "may enter or exit the House of Stewards. This is a wide "
        + "vaulted chamber draped in great shadows thrown upon "
        + "the shrouded walls. From here can be "
        + "dimly seen many rows of tables, carved of marble. Upon "
        + "each table lies a seemingly sleeping form, hands folded, head "
        + "pillowed upon stone. The air feels as cold as death, and "
        + "your instincts scream for you to turn back now and leave "
        + "the dead in peace.\n");

    add_exit(INNER_MINAS + "/houses/stewards3", "north", 0, 0);
    add_exit(INNER_MINAS + "/houses/stewards1", "exit", check_spectre, 2, 1);

    add_item(({"porch", "expanse"}), "It is just outside the arch and "
        + "seems to be holding up some very large columns.\n");
    add_item(({"building", "tomb", "hall", "halls", "chamber"}), "The "
        + "House of Stewards "
        + "is made entirely of "
        + "native stone. Its sheer size is enough to intimidate even the "
        + "bravest of hearts, and its sweeping arches are so beautiful "
        + "as to leave one breathless. Even though you are standing "
        + "inside, most "
        + "of the interior remains shrouded with shadow.\n");
    add_item(({"stone", "native stone", "blocks"}), "Tough stone quarried from "
        + "the foothills of Mount Mindolluin. You wonder how the huge "
        + "blocks could have possibly been transported to this place.\n");
    add_item(({"arches", "arch", "exit"}), "The exit to the Tomb is framed by a "
        + "great arch. Relative to the muffled darkness inside, it seems "
        + "bright and safe on the other side. Above you, numerous "
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
    add_item(({"column", "columns"}), "From here you can only see the "
        + "two columns nearest the arch. If you want to take a closer "
        + "look, you will need to return outside. Given the unwelcome "
        + "feeling emanating from the shadows, that may not be such a "
        + "bad idea.\n");
    add_item(({"ceiling"}), "The ceiling of the Tomb is lost in the "
        + "shadows. It is impossible to tell how far away it is.\n");
    add_item(({"dome", "pale dome"}), "The inside of the dome in the "
        + "House of Stewards is rumoured to have magnificent artwork "
        + "painted and carved into it. Unfortunately the shadows "
        + "preclude even the most clouded view of its secrets.\n");
    add_item(({"street", "rath dinen"}), "Through the arch, between "
        + "the columns and down the stairs lies the Rath Dinen. It seems "
        + "a haven of safety compared to this place.\n");
    add_item(({"house of kings"}), "It stands on the other side of the "
        + "Rath Dinen and appears to be the architectural twin of the "
        + "House of Stewards.\n");
    add_item(({"flight", "stairs"}), "Only the top stair can be seen "
        + "from here.\n");
    add_item(({"statues", "men", "statue"}), "Only the statue of Hurin near the "
        + "door is visible from here. He seems to be watching you with "
        + "disapproval and anger.\n");
    add_item(({"first statue", "hurin"}), "Just outside the great arch is "
        + "the image of Hurin of Emyn-Arnen, sculpted from native stone. "
        + "Hurin was the steward of King Minardil and was the founder of "
        + "the House of Stewards. The Stewards of Gondor were ever after "
        + "chosen from his descendants. "
        + "He looks down upon you with stern reproach.\n");
    add_item(({"wall", "walls"}), "Little can be seen of the walls beyond "
        + "the shadows. Some thing or things seem to move within the darkness, "
        + "but when you look closely there is nothing to be seen.\n");
    add_item(({"marble"}), "The tables appear to be made of marble .. cold, "
        + "unyielding and eternal.\n");
    add_item(({"hands"}), "The hands of each steward are folded across "
        + "the breast. So clever was the manner in which each was embalmed "
        + "that the hands retain the colour and supple texture of life.\n");
    add_item(({"tables", "rows"}), "There are many rows of tables "
        + "in this great vaulted chamber. Near at hand you can see six tables, "
        + "but further to the north there appear to be many more. Each table "
        + "bears the embalmed remains of a Steward of Gondor.\n");
    add_item(({"pillow"}), "Each Steward rests upon a block of stone "
        + "sculpted into the form of a pillow. They do not look very "
        + "comfortable.\n");
    add_item(({"dead", "forms", "stewards", "corpses", "bodies"}), "From "
        + "here can be seen six Stewards who, although long dead, have "
        + "been embalmed such that they appear to be only sleeping. Each "
        + "rests upon a table of marble.\n");
    add_item(({"form", "steward", "corpse", "body", "table"}), "Which one? "
        + "There are six near at hand.\n");
    add_item(({"first table", "first form", "first steward"}), "On the "
        + "first table is inscribed Hurin, Steward of Gondor.\n");
    add_item(({"second table", "second form", "second steward"}), "On the "
        + "second table the inscription is too faded to read.\n");
    add_item(({"third table", "third form", "third steward"}), "On the "
        + "third table the inscription is too faded to read.\n");
    add_item(({"fourth table", "fourth form", "fourth steward"}), "On the "
        + "fourth table is inscribed Pelendur, Steward of Gondor.\n");
    add_item(({"fifth table", "fifth form", "fifth steward"}), "On the "
        + "fifth table the inscription is too faded to read.\n");
    add_item(({"sixth table", "sixth form", "sixth steward"}), "On the "
        + "sixth table is inscribed Vorondil, Steward of Gondor.\n");

    /* Make it inside, dark, and impossible to hide */

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_HIDE, -1);





    reset_room();

}   
   

public int
check_spectre()
{
    switch (TP->query_race())
    {
    case "spectre":
        return 1;
	       break;
    default:
	       write("With a sigh of relief, you leave the House of Stewards.\n");
	       return 0;
	       break;
    }
}













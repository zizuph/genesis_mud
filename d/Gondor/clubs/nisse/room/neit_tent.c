/*
 *  /d/Gondor/clubs/nisse/room/neit_tent.c
 *
 *  Neit's tent in the Nisse Ohtar camp.
 *
 *  Tigerlily & Deagol, April 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

void
create_gondor()
{
    ::create_gondor();
    
    set_short("Inside the tent");
    set_long("As you stand inside the tent and gaze around, you have the " +
        "impression that this is the home of a warrior. Light filters in " +
        "from an opening near the top and gleams off the weapons hanging " +
        "on the western wall, sharp-edged and ready for use. A large " +
        "painted shield adorns the north wall. The only other furnishings " +
        "are simple and rough with animal pelts on the floor to make a " +
        "bed and a small wooden table in the corner. A flap made from " +
        "doeskin makes the door. The tent top is supported by a tall " +
        "pine pole in the center. Despite the roughness, however, there " +
        "are a few softer decorations that make the camp more homelike.\n");

    add_item(({"opening", "hole", "top", "ceiling"}),
        "There is a hole near the top that allows light to filter in, as " +
        "well as smoke to filter out during cooler weather when the " +
        "campfire is lit.\n");
    add_item(({"weapons", "western wall"}),
        "A steel longsword, honed to a fine edge, and a black spear " +
        "decorated with bright bird plumes hang across each other on the " +
        "western wall, ready to grasp at need.\n");
    add_item(({"shield", "painted shield", "large painted shield"}),
        "Hanging on the northern wall is a large shield made from hide " +
        "stretched tight across a wooden frame. It is brightly painted "+
        "with scenes that have meaning to the person who created it.\n");
    add_item(({"painting", "scenes"}), "The brightly painted shield has " +
        "scenes that depict stories from a warrioress' life. On the top " +
        "is a picture of a young woman calling a hawk to her wrist. On the " +
        "right side is a picture of two proud women engaged in a " +
        "hand-to-hand battle with swords. On the bottom the painting shows " +
        "a brightly coloured scene of women dancing to hail the rise of " +
        "the moon. On the left a young woman with dark features is being " +
        "crowned with a helmet of feathers. Around the edge of the shield " +
        "are painted runes.\n");
    add_item(({"floor", "ground"}),
        "The floor is hard-packed earth with a few soft pelts in the " +
        "corner that appear to be used as a bed.  The center is clean " +
        "except for some dark stains that look like blood. You hope it was " +
        "from no one you knew.\n");
    add_item(({"pelts", "animal pelts", "bed"}),
        "The pelts look like soft, furry rabbit skins sewn together. This " +
        "would make a warm bed on cool nights.\n");
    add_item(({"decoration", "decorations", "softer decorations"}),
        "You can see that a woman's touch has been at work here. There are " +
        "a few soft cushions on the bed and some interesting wall " +
        "hangings. The table contains a wash bowl and pitcher that seem " +
        "out of place here since they are made of delicate porcelain.\n");
    add_item(({"pitcher", "bowl", "wash bowl"}),
        "A white porcelain wash bowl with a pitcher are standing on the " +
        "table and are obviously treasures, though well used as the bowl " +
        "is slightly chipped. The bowl has images on it of a maiden " +
        "holding a small bird. Clearly these items were not created " +
        "locally, but perhaps were purchased in the city.\n");
    add_item(({"hanging", "wall hanging", "interesting wall hanging",
        "hangings", "wall hangings"}),
        "You see an interesting wall hanging that is made from red and " +
        "blue dyed feathers, cords and colourful beads. This decoration " +
        "is called a dream catcher. A length of reed is bent into a " +
        "circle and dyed cords with beads and feathers are woven across " +
        "it like a net. It is supposed to catch sweet dreams in the net " +
        "while allowing nightmares to escape through the holes.\n");
    add_item(({"pole", "pine pole"}),
        "A lodge pine pole supports the tent in the center. It is roughly " +
        "finished and carved with runes.\n");
    add_item(({"south wall", "flap", "door"}),
        "On the south side of the tent there is a large flap that " +
        "functions like a door. It appears to be made of brown doeskin " +
        "and is soft to the touch. Right now it is raised and tied back " +
        "to allow entrance.\n");
    add_item(({"table", "wooden table", "small wooden table"}),
        "There is a small table fashioned from plain wood sitting in the " +
        "corner. On it you see a bowl and pitcher and a small black velvet " +
        "pouch.\n");
    add_item(({"pouch", "velvet pouch"}),
        "It appears to contain something, but you don't dare try to " +
        "take it.\n");
    add_item(({"furnishings"}),
        "The tent is sparsely furnished, but there are some small nice " +
        "touches that show a woman lives here.\n");
    add_item(({"cushion", "cushions"}),
        "There are some cushions made from doeskin and filled with down " +
        "lying on the bed. It makes it look quite comfortable.\n");
    add_item(({"runes"}), "The runes are indecipherable.\n");
    add_item(({"walls"}),
        "The walls of the tent are made from leather and have some " +
        "interesting hangings and decorations.\n");

    clone_object(NISSE_TRAINER)->move(TO);

    add_prop(ROOM_I_INSIDE,1);
    
    add_exit(NISSE_ROOM_DIR + "o_pool", "out", 0, 0, 0);
}

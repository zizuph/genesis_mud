/*
 *  /d/Gondor/clubs/nisse/room/estiu_tent.c
 *
 *  Estiu's tent in the Nisse Ohtar camp.
 *
 *  Tigerlily & Deagol, April 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room";

#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

/*
 *  Prototypes
 */
int	read_scroll(string str);

void
create_gondor()
{
    ::create_gondor();

    set_short("Inside the hawkmistress' tent");
    set_long("As you stand inside the tent and gaze around, you have the " +
        "impression that this is the home of a warrior. Light filters in " +
        "from an opening near the top and gleams off the weapons hanging " +
        "on the western wall, sharp-edged and ready for use. A flap made " +
        "from doeskin makes the door. The tent top is supported by a tall " +
        "pine pole in the center. While the furnishings are simple as " +
        "befits a warrior camp, there are a few more refined objects that " +
        "suggest that its owner is an educated person. A wooden rack " +
        "stands in the corner, full of scrolls, and you see a small harp " +
        "leaning against it. You see a perch standing near the bed, " +
        "letting you know who shares this tent.\n");

    add_item(({"opening", "hole", "top", "ceiling"}),
        "There is a hole near the top that allows light to filter in, as " +
        "well as smoke to filter out during cooler weather when the " +
        "campfire is lit. The opening is just about the right size for " +
        "a hawk to use as an entrance.\n");
    add_item(({"harp", "small harp"}),
        "The harp is about the length of a tall woman's forearm and is " +
        "carved from some sort of golden wood you cannot identify. It is " +
        "shiny and a little worn from much use. The strings hum a chord " +
        "in tune very slightly when a breeze strokes them.\n");
    add_item(({"perch"}),
        "The perch is about waist high and is made from rough wood. It " +
        "seems to have deep scratches made from the talons of the hawk.\n");
    add_item(({"western wall", "weapons"}),
        "A longbow made from yew and a leather quiver full of sharp-tipped " +
        "arrows hang on the wall next to a gleaming elven sword, ready to " +
        "grasp at need.\n");
    add_item(({"refined objects", "objects"}),
        "You see a wooden shelf filled with scrolls and a small harp " +
        "leaning against it.\n");
    add_item(({"floor", "ground"}),
        "The floor is clean, hard-packed earth with a few soft pelts in " +
        "the corner that appear to be used as a bed.\n");
    add_item(({"pelts", "animal pelts", "bed"}),
        "The pelts look like soft, furry rabbit skins sewn together. This " +
        "would make a warm bed on cool nights.\n");
    add_item(({"pole", "pine pole"}),
        "A lodge pine pole supports the tent in the center. It is roughly " +
        "finished and carved with runes. As it is well-worn, the runes are " +
        "indecipherable.\n");
    add_item(({"scroll", "opened scroll"}),
        "On the opened scroll you see a beautiful flowing script. You may " +
        "be able to read it.\n");
    add_item(({"rack", "wooden rack", "scrolls"}),
        "The wooden rack contains many scrolls, and you see one lying open " +
        "on the top. Beside it lies a small velvet pouch.\n");
    add_item(({"walls"}),
        "The walls of the tent are made from a soft, light-brown doeskin.\n");
    add_item(({"north wall", "flap", "door"}),
        "On the north side of the tent there is a large flap that " +
        "functions like a door. It appears to be made of brown doeskin and " +
        "is soft to the touch. Right now it is raised and tied back to " +
        "allow entrance.\n");
    add_item(({"pouch", "velvet pouch"}),
        "The pouch is made from soft black velvet. It appears to contain " +
        "something, but you do not dare try to take it.\n");
    add_item(({"furnishings"}),
        "The tent is sparsely furnished, but there are some small nice " +
        "touches that show a woman lives here.\n");
    add_item(({"cushions"}),
        "There are some cushions made from doeskin and filled with down " +
        "lying on the bed. It makes it look quite comfortable.\n");

    add_prop(ROOM_I_INSIDE,1);

    clone_object(NISSE_HAWKMISTRESS)->move(TO);

    add_exit(NISSE_ROOM_DIR + "path2", "out", 0, 0, 0);
}

/*
 *  Function name: read_scroll
 *  Description  : Reads the scroll, it gives a different view according to
 *                 the player's language skill.
 *  Arguments    : string str - as entered by the player
 *  Returns      : 0/1
 */
int
read_scroll(string str)
{
    object player = TP;

    if (str != "scroll")
    {
        notify_fail(CAP(query_verb()) + " what?\n", 0);
        return 0;
    }

    if (player->resolve_task(TASK_ROUTINE, ({TS_WIS, SS_LANGUAGE})) >= 10)
    {
        write("The words appear in your mind as you read the flowing " +
            "script:\n\n"+
            "Shadows lengthen;\n" +
            "spires fade from view.\n" +
            "Overhead the hawk of night,\n" +
            "among whirling sparks and wind-carried ashes.\n" +
            "Under the silent stars\n" +
            "a night must fall\n" +
            "that a new day may break.\n");
            return 1;
     }

    write("The handwriting is beautiful, but you lack the skill to " +
        "understand it.\n");
    return 1;
}

void
init()
{
    ::init();

    add_action(read_scroll, "read");
}

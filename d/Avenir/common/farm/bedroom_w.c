/* Creator: Ibun
 * Revised by: Lilith, June 2004
 */
#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/room";
int cloth_on_chest;  // If 0 the cloth is taken. If 1 the cloth is there to grab

void
create_room()
{
    set_short("A larger bedroom");
    set_long("This is a larger bedroom in the old manor house. "+
        "Its style is consistent with the rest of the building, "+
        "being constructed of quality materials that have been "+
        "terribly neglected. There is a patterned paper on the "+
        "walls, but it is peeling away, exposing the grayish "+
        "paint underneath. The ceiling is still mostly white, "+
        "with a few yellowed water-stains. "+
        "Beneath a thick coating of dust, you can see a "+
        "bed, a chest of drawers with a mirror on top, and a "+
        "small carpet on the floor.\n");

    add_item(({"paint", "grayish paint"}),
        "You pull back the paper a bit and examine the paint "+
        "more closely.\nIt is plain gray paint with brown "+
        "patches, probably from the glue used to apply the "+
        "wallpaper.\n");
    add_item(({"ceiling", "stains", "stain", "water-stains"}),
        "Its just a ceiling with stains on it. Not much of "+
        "interest up there.\n");
    add_item("bed","You take a step forward and sit down on " +
        "the bed. Its amazingly soft and you think you " +
        "could sleep well in it.\n");
    add_item(({"chest","chest of drawers","drawers"}),"@@desc_chest");
    add_item("mirror","You take a quick look in the mirror " +
        "and see the usual sight of yourself.\n");
    add_item("carpet","You kneel down and examine the carpet " +
        "carefully. It is a nice old rug but you decide to leave it " +
        "alone.\n");
    add_item(({"wall","walls"}),"You look at the walls and see " +
        "nothing but faded wallpaper and a small painting.\n");
    add_item(({"wallpaper", "faded wallpaper","patterned paper",
        "paper", "pattern", "patterns"}),
        "The wallpaper is so faded that you cannot "+
        "discern what the pattern on it was, only that it had "+
        "one, once.\n");
    add_item("painting","You carefully study the small painting " +
        "on the wall. Its not very well made and has also been badly " +
        "damaged. Its very hard to see what its supposed to " +
        "depict, so you decide to leave it where it hangs.\n");
    add_item(({"cloth","table cloth","red table cloth"}),"@@desc_cloth");
    add_exit("corridor1w","south");
    reset_room();
}

void
reset_room()
{
    cloth_on_chest = 1;
}

void
init()
{
    ::init();
    add_action("open_drawer", "open");
    add_action("get_cloth", "get");
    add_action("measure_bedroom","measure");
}

int
open_drawer(string str)
{
    if (strlen(str) && (str == "drawer" || str == "drawers"
        || str == "chest"))
    {
    write("You pull out one of the drawers. Its empty. " +
        "The hollow sound from the wooden chest tells you " +
        "that nothing is stored in either of the drawers.\n");
        return 1;
    }
    return 0;
}

string
desc_cloth()
{
    string text;

    if (cloth_on_chest)
        return "Its a red table cloth about a square meter or " +
            "two in size.\n";
    return "What?\n";
}

string
desc_chest()
{
    string text;

    text = "You touch the chest of drawers with your hand. Without " +
        "doubt it is of a very high quality and has withstood " +
        "the wear of exposure during the years. ";
    if (cloth_on_chest)
    {
        text += "The top of the chest is covered by a red table cloth.\n";
        return text;
    }
    text += "\n";
    return text;
}

int
query_cloth()
{
    if (cloth_on_chest)
        return cloth_on_chest;
}

int
get_cloth(string str)
{

    object cloth;

    if (cloth_on_chest)
         if ((str == "cloth") || (str == "table cloth") || (str == "red table cloth"))
         {
             cloth = clone_object(THIS_DIR + "obj/table_cloth");
             cloth->move(TP);
             cloth_on_chest = 0;
             write("You take the red cloth from the chest.\n");
             say(QCTNAME(TP) + " takes the red table cloth from the chest " +
                 "of drawers.\n");
             return 1;
         }
    return 0;
}
 
int
measure_bedroom(string str)
{
 
    if ((str) && (str == "bedroom"))
    {
        write("Its approximately 9 feet wide.\n");
        return 1;
    }
    return 0;
 
}

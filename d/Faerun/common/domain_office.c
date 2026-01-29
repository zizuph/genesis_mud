/*
 * Tower Domain Office for Faerun
 * -- Finwe, October 2006
 */
// add loose torch movements, move, twist, push, etc. It produces a click when moved.

#include <language.h>
#include "/d/Faerun/defs.h"
#include "/d/Genesis/start/human/town/tower.h"
#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>

inherit TOWER_OFFICE;
inherit "/cmd/std/command_driver";

#define NO_FIGHT_MSG    "This room is for learning and contemplation, not fighting.\n"
#define MORE(x)         this_player()->more(read_file(x, 2))
#define PROJ_DIR        "/d/Faerun/common/projects/"


void
create_tower_office()
{
    set_short("A large stone workroom");
    set_long("This is the workroom of a powerful wizard. The room is circular " +
        "and made of stone. Torches are held on the walls by iron torch stand " +
        "and cast a dull, yellow light. Smoke hangs just below the ceiling, " +
        "slowly moving around. Shelves line the walls. A large table dominates " +
        "the room. It is centered in the room. Smaller tables are scattered " +
        "around the workroom and a blood red carpet covers the floor.\n");

    add_item(({"stone", "stone blocks", "stone block"}),
        "The blocks of stone are cut from granite. They are smooth and set " +
        "together. Fine lines show where the stones have been fitted. Torch " +
        "stands are set on the walls with shelves surronding them.\n");
    add_item(({"torches"}),
        "The torches are made of long poles with some sort of substance on " +
        "the tops. They burn, filling the room with a dull, yellow light. " +
        "The torches produce a lot of smoke which hangs just below the " +
        "ceiling, coating it with black soot.\n");
    add_item(({"torch stands", "stands"}),
        "They are made of iron and are bolted onto the walls. They are round " +
        "and designed to hold torches. One looks a bit loose.\n");
    add_item(({"shelves", "shelf"}),
        "The shelves are bolted to the walls. They are finely crafted, large " +
        "and made of an ancient hardwood. The shelves are stuffed with a " +
        "wide variety of books, jars, crocks, stuffed animals, and papers.\n");
    add_item(({"books"}),
        "They are all sizes and shapes and stacked randomly on the shelves " +
        "and small tables. The books look well read. They have yellowed, " +
        "dog-eared pages and worn covers.\n");
    add_item(({"jars", "beakers"}),
        "The jars and beakers are made of glass and are of different shapes " +
        "and sizes. Some are tall and thin while others are short and squat. " +
        "Some are round and others square or oddly shaped. Some are clear " +
        "and others are colored. Some of the jars are empty and others are " +
        "full, or partially full of various liquids, bubbling gasses, and " +
        "other unidentifiable things, some of which you may have only seen " +
        "in your worst nightmares. The jars and beakers are scattered across " +
        "the shelves and small tables in a haphazard fashion.\n");
    add_item(({"crocks", "crock"}),
        "They are earthenware pots and other containers used to store " +
        "things. They are stacked haphazardly on the shelves and small " +
        "tables.\n");
    add_item(({"containers", "container"}),
        "There are jars and crocks stored on the shelves. The jars are made " +
        "of glass and the crocks are earthenware pots.\n");
    add_item(({"pots", "earthenware pots", "bowls", "bowl"}),
        "They are made from hardened clay that has been shaped into bowls " +
        "and covered pots. They are plain and stacked on the shelves and " +
        "small tables.\n");
    add_item(({"stuffed animals"}),
        "There are all kinds of animals on the shelves. There are birds and " +
        "reptiles, and they all look dusty.\n");
    add_item(({"reptiles", "stuffed reptiles"}),
        "There are stuffed snakes and lizards. They are large and are " +
        "surrounded by books and jars on the shelves.\n");
    add_item(({"stuffed snakes"}),
        "They are different colors and either coiled or stretched out. Most " +
        "are unrecognizable and likely from arid areas of Faerun.\n");
    add_item(({"stuffed lizards", "lizards"}),
        "They are different colors and look deadly. Most are unrecognizable " +
        "and probably from arid areas of Faerun.\n");
    add_item(({"stuffed birds", "birds"}),
        "They are all sizes and colors. Most are arranged perched on branches, " +
        "as they might be if they were alive. Some sit in nests, and there " +
        "is even a raven hanging upside down on a branch.\n");
    add_item(({"nests"}),
        "They are made of small branches and twigs, and sit on the shelves " +
        "and tables. Some hold stuffed birds sitting on them.\n");
    add_item(({"stuffed raven", "raven"}),
        "It is black and stuffed, and hangs upside down on a branch that is " +
        "set on a shelf. The bird looks lifelike and seems to watch your " +
        "every move.\n");
    add_item(({"twigs", "branches"}),
        "They are small and woven into nests that sit on the shelves and " +
        "small tables.\n");
    add_item(({"papers"}),
        "They are large and full of unrecognizable words that seem to shift " +
        "and flow like water on the pages as you examine them. Many are " +
        "yellowed from age and curled at the edges or have the corners folded " +
        "over. The papers are stacked on the shelves and scattered across the " +
        "small tables.\n");
    add_item(({"large table"}),
        "The large table is centered in the room. It is round and appears " +
        "to be built from one solid piece of oak. The outer border is " +
        "decorated with arcane symbols that seem to glow. A large pentagram " +
        "covers the surface. The table looks clean and is probably used for " +
        "ceremonies or other dark magics produced by the wizard.\n");
    add_item(({"symbols", "arcane symbols"}),
        "The arcane symbols are mysterious looking and different sizes. They are made of darker wood inlaid into the large table. Many of the symbols are large and look complex, and seem to be combinations of other designs. The symbols seem to glow on the surface of the tables.\n");
    add_item(({"table", "tables"}),
        "There are two sets of tables. One is a large table set in the " +
        "center of the workroom and smaller tables spread around here.\n");
    add_item(({"tables", "small tables"}),
        "They are round and scattered around the room. They look cluttered " +
        "with stacked papers.\n");
    add_item(({"dark leather", "leathers"}),
        "The leathers are skins of unknown animals. They are all different " +
        "colors and textures. Some are smooth, rough, striped, dotted, and " +
        "plain. The leathers are used to bind books and tomes, and look " +
        "well worn.\n");
    add_item(({"pages"}),
        "They are bound in the books and tomes and look well read. The pages " +
        "are worn and yellowed from age. Some have corners that have been " +
        "folded over or are curled.\n");
    add_item(({"carpet"}),
        "The carpet is round and fills the room. It is plush and blood-red " +
        "colored, with a midnight black border. A pair of finely crafted " +
        "black steel scimitars with a giant black spider behind them is " +
        "woven into the carpet. The spider's six eyes seem to sparkle and " +
        "follow you. The scimitars seem to shimmer in the dull, yellow " +
        "torch light.\n");
    add_item(({"pentagram", "large pentagram", }),
        "The pentagram is a five pointed star inlaid into the surface of " +
        "the large table. Arcane symbols encircle it. The pentagram seems " +
        "to shimmer as you move your hand over it. In the center you read:\n\n" +
        "    Commands:\n" +
        "    wizards                  - Lists the wizards of this domain.\n" +
        "    projects <domain/wizard> - The projects of the domain/wizard.\n\n");
    add_item(({"smoke", "thick smoke"}),
        "It is grey and hangs just below the ceiling. It billows and moves " +
        "around, seemingly on its own.\n");
    add_item(({"ceiling"}),
        "The ceiling is round and made of stone blocks. It is hidden from " +
        "view by thick smoke that hangs just below it.\n");
    add_item(({"soot"}),
        "The soot is black and forms round circles on the ceiling. It comes " +
        "from the torches that burn, spewing soot onto the ceiling.\n");
    

    set_project_path("/d/Faerun/common/projects/");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_ATTACK,1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK,1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_S_MAP_FILE, "domain_office.txt");

    add_tower_link("tower");
    add_exit("/d/Faerun/guilds/drow/rooms/join", "west", "@@block_room@@",1,1);
    add_exit("/d/Faerun/holidays/easter/hshop", "north", "@@block_room@@",1,1);

    room_add_object("/d/Faerun/guilds/nov/npcs/emissary");

    reset_room();

}

void
init()
{
    ::init();

    add_action("wave_pent", "move");
}


int wave_pent(string str)
{
    string text;
    switch(str)
    {
        case "hand over first point":
        case "hand first point":
        case "hand first":
        {
            write("You move your hand over the first point of the pentagram. " +
                "It blazes to life and nearly blinds you. Before your eyes " +
                "you see the following:\n\n\n");

            MORE(PROJ_DIR + "Faerun.prj");

            write("The point suddenly dims and fades back into darkness.\n");
            say (QCTNAME(TP) + " moves "+ HIS_HER(TP) + " hand over the first " +
                "point of the pentagram. It suddenly blazes to life, then " +
                "fades back into darkness.\n");
            return 1;
            break;
        }
        case "hand over second point":
        case "hand second point":
        case "hand second":
        {
            write("You move your hand over the second point of the pentagram. " +
                "It blazes to life and nearly blinds you. Before your eyes " +
                "you see the following:\n\n\n");

            MORE(PROJ_DIR + "projects.txt");
            MORE(PROJ_DIR + "Finwe.prj");
            MORE(PROJ_DIR + "Kehr.prj");
            
            write("\n\nThe point suddenly dims and fades back into darkness.\n");
            say (QCTNAME(TP) + " moves "+ HIS_HER(TP) + " hand over the second " +
                "point of the pentagram. It suddenly blazes to life, then " +
                "fades back into darkness.\n");
            return 1;
            break;
        }
        case "hand over third point":
        case "hand third point":
        case "hand third":
        {
            write("You move your hand over the third point of the pentagram. " +
                "It blazes to life and nearly blinds you. Before your eyes " +
                "you see the following:\n\n\n");

            MORE(PROJ_DIR + "opened.txt");
            
            write("The point suddenly dims and fades back into darkness.\n");
            say (QCTNAME(TP) + " moves "+ HIS_HER(TP) + " hand over the third " +
                "point of the pentagram. It suddenly blazes to life, then " +
                "fades back into darkness.\n");
            return 1;
            break;
        }
        case "hand over fourth point":
        case "hand fourth point":
        case "hand fourth":
        {
            write("You move your hand over the fourth point of the pentagram. " +
                "It blazes to life and nearly blinds you. Before your eyes " +
                "you see the following:\n\n\n");

            MORE(PROJ_DIR + "geography.txt");
            
            write("The point suddenly dims and fades back into darkness.\n");
            say (QCTNAME(TP) + " moves "+ HIS_HER(TP) + " hand over the fourth " +
                "point of the pentagram. It suddenly blazes to life, then " +
                "fades back into darkness.\n");
            return 1;
            break;
        }
        case "hand over fifth point":
        case "hand fifth point":
        case "hand fifth":
        {

            write("You move your hand over the fifth point of the pentagram. " +
                "It brightens then dims and fades back into darkness.\n");
            say (QCTNAME(TP) + " moves "+ HIS_HER(TP) + " hand over the fifth " +
                "point of the pentagram. It brightens, then fades back into darkness.\n");
            return 1;
            break;
        }
        case "loose torch":
        case "torch":
        {
            write("The loose torch moves to your right. Somewhere in the " +
                "room you hear a faint 'click'.\n");
            say(QCTNAME(TP) + " moves a loose torch to " + HIS_HER(TP) + 
                " right. Somewhere in the room you hear a faint 'click'.\n");
            return 1;
            break;
        }

        default:
        {
            write("You move your hand over the pentagram on the large table.\n");
            write("The star shimmers before your eyes.\n");
            write("The five points pulse in rhythm for a few moments then fade back into the table.\n");
            return 1;
        }
    }

}

void
reset_room()
{
    object quest_orb;
    
    if (!present("_genesis_quest_orb"))
    {
        quest_orb = clone_object(QUEST_ORB);
        quest_orb->set_orb_domain("Faerun");
        quest_orb->set_extra_line("The dark crystal orb floats above the pentagram.");
        quest_orb->move(this_object(), 1);
    }    

}

int
block_room()
{
// testers for Drow guild
    if (this_player()->query_wiz_level())
/*
        TP->query_real_name() == "xerxes" ||
        TP->query_real_name() == "calantha" ||
        TP->query_real_name() == "aizorana" ||
        TP->query_real_name() == "amberlee" ||
        TP->query_real_name() == "lestharoth" ||
        TP->query_real_name() == "deirae" 
        ) 
*/        
        return 0;

    write("You are not permitted to go there.\n");
    return 1;
}

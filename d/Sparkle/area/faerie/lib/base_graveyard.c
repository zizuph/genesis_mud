/*
 * Base orchard room for Faerie
 * Finwe, September 1999
 */
 
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
 
inherit "/std/room";
inherit S_LIB_CLOCK;
inherit COMMON_BASE;

#define MAX_NPCS 3

static object *g_npcs = allocate(MAX_NPCS);

void create_graveyard_room() {} 
void add_npcs(int i);
void reset_room();

static string aboveground = "",
              underground = "",
              add_coffins = "",
              add_ladder  = ""; 

int room_num;
int lichen_rubbed = 0;      // 0 = not rubbed, 1 = rubbed
int headstone_moved = 0;    // 0 = not pushed, 1 = pushed, 2 = none to push
// down_exit is set by the room that connects to
string down_exit;  
 
create_room()
{
    reset_room();
    add_prop(ROOM_S_MAP_FILE, "faerie_map_east.txt");
    set_short("A dismal graveyard");
//    set_long(short() + ". " +"A graveyard");
//    add_prop(ROOM_S_DARK_LONG, "A pitch black crypt.\n");

    create_graveyard_room();

}
 
init()
{
    ::init();
    add_action("rub_lichen", "rub");
}
 
void
reset_room()
{

}
 
/*
 * Basic room descriptions for graves above ground
 */
string grave_above1()
{
    return s_desc_sky_outside_sky() + "Tombstones rise from the dark, " +
    "gray fog hanging above the ground. The fog moves about even though " +
    "there is no wind here. ";
}

string grave_above2()
{
    return s_desc_sky_outside_sky() + "Many tombstones are " +
    "scattered about the rolling hills of the graveyard. They " +
    "look weather-worn and some have even started to break apart, " +
    "a testament of their age. ";
}

string grave_above3()
{
    return s_desc_sky_outside_sky() + "A thick gray fog covers " +
    "the graveyard. It churns on its own and blows past the " +
    "numerous head and tombstones sticking up from the ground. ";
}
string grave_above4()
{
    return s_desc_sky_outside_sky() + "You stand on a slight " +
    "hill overlooking a bleak landscape. Countless grave sites " +
    "are visible, some with ornate tombstones and others with " +
    "simple headstones. ";
}

string grave_above5()
{
    return s_desc_sky_outside_sky() + "A cold gray fog hangs over " +
    "the ground, adding to the feeling. Numerous headstones stick out " +
    "of the fog. ";
}

/*
 * Basic room descriptions for graves underground
 */

string grave_under1()
{
    return "The sound of water drips from the ceiling into pools on " +
    "the ground. Lichens grow on the walls and ceiling. The grave is " +
    "cold and dug out from the earth with a low ceiling. ";
}

string grave_under2()
{
    return "The grave has been dug from the earth. It is cold and musty " +
    "smelling. Lichens grow on the walls. The floor of the grave is " +
    "covered with soft dirt, and the ceiling is low. The grave is " +
    "partially collapsed. ";
}

string grave_under3()
{
    return "Lichens grow on the walls and ceiling. They are gray and " +
    "sickly looking. The grave is dark and stuffy with dirty pools of " +
    "water on the ground. The sound of dripping water echoes through " +
    "the grave. ";
}

string grave_under4()
{
    return "Moldy bones and corpses lay scattered around the grave. " +
    "Pools of water have gathered in the lower parts, and gray lichens " +
    "grow on the low ceiling and walls. ";
}

string grave_under5()
{
    return "The grave is dark and musty smelling. It is moist from " +
    "the puddles of water on the ground. Lichens grow scattered across " +
    "the ceiling and walls. ";
}

/*
 * Function name : set_add_coffins
 * Description   : adds descr of coffins in the graveyard
 */
void set_add_coffins()
{
    add_item(({"coffins", "coffin"}),
        "This is an oblong box in which a corpse is buried. It is made " +
        "of wood, but over the centuries, has rotted away. It is shattered " +
        "in two, as if whatever was buried in it broke free.\n");
}

/*
 * Function name : set_add_ladder
 * Description   : adds descr of ladder to climb between grave levels
 */
void set_add_ladder()
{
    add_item(({"holes", "ladder"}),
        "They are set irregularly into the wall. They look like they " +
        "were dug into the wall by some unfortunate soul that got stuck " +
        "in here. They appear to be some sort of a ladder as they lead " +
        "up to the ceiling to the next level.\n");

}


/*
 * Function name : set_aboveground
 * Description   : adds descr of graveyard above ground
 */
void set_aboveground()
{
    add_prop(ROOM_I_LIGHT, 1); // light

    add_item(({"path", "gravel path"}),
        "It is made of crushed gray stones. The path wanders through " +
        "the graveyard. It is bordered by tombstones and some dead trees.\n");
    add_item(({"dead trees", "trees"}),
        "They are dead and twisted. Their bare branches stretch out " +
        "like withered arms.\n");
    add_item(({"grass", "green grass", "lawn"}),
        "There isn't any here.\n"); 
    add_item(({"graves"}),
        "The graves look old and unkept, but then it's hard to tell " +
        "since they are blanketed in fog. Some have headstones on them.\n");
    add_item(({"headstone", "headstones", "tombstones", "tombstones", 
            "gravestones", "gravestone"}),
        "They stand as silent testaments to those who once lived. The " +
        "stones are old, and some have toppled over. Others are cracked, " +
        "and still some are barely visible in the fog.\n");
    add_item(({"fog", "cold fog", "cold gray fog"}),
        "The fog hangs over the ground and covers the grave sites. It " +
        "is dark and looks of death. It moves about the graveyard even " +
        "though there isn't any wind.\n");
    add_item(({"grasses", "grass"}),
        "The grasses are gray and dead looking. It grows everywhere in " +
        "the graveyard, with a path running through it.\n");
    add_item(({"ground"}),
        "The ground is cold dead looking. Gray grass covers the ground, " +
        "punctuated with tombstones and dead trees. Paths of crushed " +
        "gray stones run through the graveyard\n");
    add_item(({"gray stone", "crushed gray stone", "gray stones", 
            "crushed gray stones"}),
        "The stones are gray colored and angular is shape and size. They " +
        "form the paths that run through the graveyard.\n");
}

/*
 * Function name : set_underground
 * Description   : adds descr of graves under ground
 */
void set_underground()
{
    add_prop(ROOM_I_LIGHT, 0); // dark
    add_prop(ROOM_I_INSIDE, 1); // not outdoors!
    set_short("An underground grave");

    set_add_coffins();
    add_item(({"puddles", "puddles of water", "pools", "pools of water"}),
        "The pools are different sizes and scattered around the grave. " +
        "They have formed from dripping water, and look sickly.\n");
    add_item(({"ceiling"}),
        "The ceiling is low and made of earth. Plant roots grow through it " +
        "and gray lichens grow on it.\n");
    add_item(({"roots", "plant roots"}),
        "The plant roots grow through the ceiling and out of the walls. " +
        "Most of them are thin and branching, and hold the grave in place.\n");
    add_item(({"lichen", "lichens"}),
        "The lichens are dull, gray and spidery looking. They are fairly " +
        "large and grow on the walls and ceilings. A faint glow surrounds " +
        "some of them, as if they have been rubbed recently.\n");
    add_item(({"bones", "moldy bones"}),
        "The moldy bones are left over from decayed bodies that were " +
        "buried here. Many of them have been broken and have teeth " +
        "marks on them from vermin that gnawed on them.\n");
    add_item(({"walls"}),
        "The walls are soft having been dug out of earth. They are dark " +
        "brown with roots growing out of them. Gray lichens grow on " +
        "them and grow faintly, as if they were rubbed recently.\n");
    add_item(({"dirt", "soft dirt", "soil", "soft soil"}),
        "It is brown and soft, and full of bones and plant roots. The " +
        "soil is so soft that you can see tracks in it.\n");
    add_item(({"teeth marks"}),
        "The teeth marks are on the bones, and look like they came from " +
        "vermin that inhabit the graves.\n");
    add_item(({"glow"}),
        "The glow comes from the lichens that grow on the ceiling and " +
        "walls. It is an eerie green color.\n");
    add_item(({"claw marks", "marks"}),
        "The claw marks are long, rectangular marks in the earth. They " +
        "look like they were made by something trying to dig its way " +
        "out of the grave.\n");
    
}

/*******************************************************************************
 * Functions to turn light on in the graves. players 'rub lichen'
 ******************************************************************************/

/*
 * Function name : end_light
 * Description   : turns off light from lichen.
 */
int 
end_light()
{
    if(lichen_rubbed = 1)
    {
        if(query_prop(ROOM_I_LIGHT) <= 0)
            return 0;

        write("The eerie, green light fades, leaving the lichen dull and gray.\n");
        add_prop(ROOM_I_LIGHT, query_prop(ROOM_I_LIGHT) - 1);
        lichen_rubbed = 0;
        return 1;
    }
}

/*
 * Function name : rub_lichen
 * Description   : turns light on in room for 5 minutes when rubbed.
 */

int
rub_lichen(string str)
{

    if (str != "lichen")
    {
        notify_fail("Rub what, the lichen?\n");
        return 0;
    }

    if (lichen_rubbed == 1)
    {
        WRITE("The lichen is already glowing.\n");
        return 1;
    }

    say(QCTNAME(TP) + " rubs the lichen on the wall. It begins to glow, " +
        "casting an eerie, green light.\n");
    write("You rub the lichen on the wall. It begins to glow, casting " +
        "an eerie, green light.\n");

    lichen_rubbed = 1;
    add_prop(ROOM_I_LIGHT, query_prop(ROOM_I_LIGHT) + 1);   
    set_alarm(300.0, 0.0, "end_light");
    return 1;

}

/*
 * Routines for pushing over tombstone and going down below
 */
 
string 
headstone_descr()
{
    switch(headstone_moved)
    {
        case 0:     // not pushed or moved
        {
            return "A large tombstone is worn down and looks like it " +
            "has been pushed over many times by visitors.";
            break;
        }
        case 1:     // has been pushed over. pesky rabble rousers! :)
        {
            return "A hole where a large tombstone use to be.";
        }
    }
}

void
reset_headstones()
{
    headstone_moved = 0;
    remove_exit("down");
   tell_room(TO, "A screeching, grinding sound fills the graveyard as the large tombstone suddenly raises itself and blocks the hole.\n");
}

int 
move_headstone(string str)
{
    if (!str)
    {
        notify_fail(CAP(query_verb())+" what?\n");
        return 0;
    }

    if (str == "tombstone" || str == "headstone" || str == "gravestone")
    {
        switch(headstone_moved)
        {
            case 0: // headstone not pushed
            {
                write("You push the " + str + " with all your might. It " +
                    "moves slowly and falls over, crashing through the " +
                    "earth leaving behind a large hole.\n");
                say(QCTNAME(TP) + " pushes the " + str + " with all " + 
                    HIS_HER(TP) + " might. It falls over, crashing through " +
                    "the earth, leaving a large hole behind.\n");
                add_exit(down_exit, "down");
                add_item(({"hole", "large hole"}),
                    "This is a large hole left behind by a fallen " +
                    "tombstone. It leads down underground.\n");
                headstone_moved = 1;
                set_alarm(60.0,0.0,"reset_headstones");
                break;
            }
            case 1:
            {
                write("There are no " + str + "s to push over, only a " +
                    "hole in the ground leading down.\n");
                break;
            }

            case 2:
            {
                write("Push what?\n");
                break;
            }
        }
    }
    return 1;
}

/*
 * add npcs based on value passed from the room
 */

void
add_npcs(int i)
{
    int npcs_yn = random(5); // does this room clone npcs?
    int index, npc_count = random(MAX_NPCS);
    string which_npcs = "", restrained = "";

    setuid();
    seteuid(getuid());

    if(npcs_yn == 1 || npcs_yn == 3 || npcs_yn == 5)    // yes, we make npcs
    {
        switch(i)
        {
            case 0: // level 1, zombies
            {
                which_npcs = "zombie";
                restrained = "lvl01";
                break;
            }
            case 1: // level 2, skeletons
            {
                which_npcs = "skeleton";
                restrained = "lvl02";
                break;
            }
            case 2: // level 3, spirits
            {
                which_npcs = "spirit";
                restrained = "lvl03";
                break;
            }
            default:
            {
                which_npcs = "zombie";
                restrained = "lvl01";
                break;
            }
        }

        // lets make the npcs       
        for(index = 0; index < npc_count; index++)
        {
            if (!objectp(g_npcs[index]))
            {
                g_npcs[index] = clone_object(NPC_DIR + which_npcs);
                g_npcs[index]->set_restrain_path(GRAVEYARD_DIR + restrained);
                g_npcs[index]->set_random_move(3);
                g_npcs[index]->move(TO);
            }
        }
        
    }
}

#pragma strict_types

#include "local.h"
#include <ss_types.h>
#include <macros.h>
#include <terrain.h>
#include DEFS
#include CLOCKH

#define HERBSHERE   ({ \
        KRHERB + "poison_ivy", \
        KRHERB + "dandelion", \
        KRHERB + "wild_plum", \
        KRHERB + "raspberry", \
        KRHERB + "amanita", \
        KRHERB + "bunchberry", \
        KRHERB + "chantrelle", \
        KRHERB + "cladina", \
        KRHERB + "fdlhead", \
        KRHERB + "hazelnut", \
        KRHERB + "horsetail", \
        KRHERB + "lady_slipper", \
        KRHERB + "onoclea", \
        KRHERB + "saskatoon", \
        KRHERB + "tiger_lily", \
        KRHERB + "hawthorn", \
        KRHERB + "jewelweed", \
        KRHERB + "elidross", \
        KRHERB + "solinaith", \
        AVHERB + "carlith", \
        AVHERB + "fordinfa", \
        GOHERB + "blueberry", \
        GOHERB + "caraway", \
        GOHERB + "catnip", \
        GOHERB + "chervil", \
        GOHERB + "clove", \
        GOHERB + "coccinea", \
        GOHERB + "foxglove", \
        GOHERB + "hemlock", \
        GOHERB + "holly", \
        GOHERB + "mint", \
        GOHERB + "oregano", \
        GOHERB + "rosemary", \
        GOHERB + "sage", \
        GOHERB + "sumac", \
        SHHERB + "chives", \
        SHHERB + "huckleberry", \
        SHHERB + "parsley", \
        KHHERB + "honeysuckle", /* Permission from Damaris 2005-05-27 */ \
        EAHERB + "ginseng", \
        EAHERB + "monkshood", \
        EAHERB + "morel", \
        EAHERB + "oakmoss", \
        EAHERB + "witch_grass", \
        EAHERB + "yarrow", \
        RAHERB + "mandrake" })

inherit OR_FILE
inherit HERBSEARCHNEW

static string structure_here,
              lake_dir,
              creek_dir,
              special;

public varargs int add_exit(string place, string cmd, mixed efunc, mixed tired,
    mixed non_obvious)
{
    return ::add_exit(place, cmd, "@@move_through_forest@@", random(5), 1);
}

string get_long_desc()
{
    string desc = "A green forest surrounds you, abundant with opulent "
        + "vegetation. These woods are dense with trees, which obscure most of"
        + " the sky.";

    switch(GET_TIMEOFDAY)
    {
        case TOD_DAWN:
            desc += " Countless birds sing as the morning light trickles "
                + "through the canopy.";
            break;
        case TOD_DAY:
            desc += " The forest is spotted with sun breaks as afternoon light"
                + " penetrates the treetops.";
            break;
        case TOD_TWILIGHT:
            desc += " The forest is dim and a cool breeze stirs up the leaves,"
                + " signalling the approach of nightfall.";
            break;
        case TOD_NIGHT:
            desc += " The sounds of insects permeates the forest and the red"
                + " and white moonlight casts eerie shadows throughout the "
                + "understory.";
            break;
        default:
            break;
    }

    if(special)
        desc += special;
    else
    {
        if(lake_dir)
            desc += " The forest stops abruptly at the edge of a small lake "
                + "to the " + lake_dir + ".";
        else if(creek_dir)
            desc += " A creek lies to your " + creek_dir + ", providing a "
                + "steady supply of water to the lake downstream.";
    
        if(structure_here && this_player()->query_skill(SS_AWARENESS) >= 20)
            desc += " A small structure has been erected here.";
    }

    return desc + "\n";
}

string exa_lake()
{
    if(GET_SEASON == WINTER)
        return "The lake is fozen over and covered with snow, making it rather"
            + " uninteresting.\n";
    
    return "The lake is small and completely surrounded by trees. The water "
        + "shimmers as tiny waves follow the wind. You occasionally hear the "
        + "splash of a fish, but only turn in time to see the ripples it has "
        + "left behind.\n";
}

string exa_creek()
{
    if(GET_SEASON == WINTER)
        return "The creek is lined with ice and snow, but still manages to "
            + "flows at a turtle's pace.\n";
    
    return "The banks of the creek are steep and slippery and too far apart to"
        + " jump across. The water looks muddy and slow-going, but could be "
        + "moving quite rapidly under the surface.\n";
}

public void create_kagonesti_forest()
{
}

void create_krynn_room()
{
    set_short("A green, lush forest");
    set_long("@@get_long_desc@@");
    add_item("forest", "Thick with plant life in all directions, the forest "
        + "appears endless, and easy to get lost in.\n");
    add_item("trees", "The trees are tall and healthy, blocking much of the "
        + "sky from view.\n");
    add_item("vegetation", "Thick vegetation covers the entire area, making "
        + "passage a challenge.\n");
    add_prop(ROOM_I_HIDE, random(60));
    add_prop(ROOM_S_DARK_LONG, "A dark area in a forest.\n");
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_prop(OBJ_I_SEARCH_TIME, 4);

    for(int i = random(5); i > 0; i--)
         add_herb_file(one_of_list(HERBSHERE));

    set_terrain(TERRAIN_OUTSIDE | TERRAIN_NATURAL | TERRAIN_TEMPERATE |
        TERRAIN_SOIL | TERRAIN_TALL_PLANT | TERRAIN_SMALL_PLANT |
        TERRAIN_ROUGH | TERRAIN_SHADOWS | TERRAIN_RESIDENCE);
    OUTSIDE

    set_area_handler(STD + "kagonesti_placer");

    create_kagonesti_forest();

    if(structure_here)
    {
        add_item(({"small structure", "structure", "hut"}), "This hut-like "
            + "structure blends very well with the forest. It is supported by "
            + "several thick branches and draped with animal hide. It is "
            + "thoroughly covered with grass, twigs, and other vegetation, "
            + "making it difficult to notice in this environment. It has a "
            + "small entrance.\n");
        add_item("entrance", "You could probably use it to enter the hut.\n");
    }

    if(lake_dir)
    {
        set_short(this_object()->query_short() + ", near a lake");
        add_item("lake", "@@exa_lake@@");
    }
    else if(creek_dir)
    {
        set_short(this_object()->query_short() + ", near a creek");
        add_item(({"creek", "stream"}), "@@exa_creek");
        add_item("lake", "Though most of your view is blocked by trees, you "
            + "can make out the lake that the nearby creek feeds into.\n");
    }
}

int enter_structure(string args)
{
    if(args == "structure" || args == "hut")
    {
        if(LOAD_ERR(structure_here))
        {
            tell_room(this_object(), "There is a rift in the fabric of "
                + "time and space. Please write a bug report for this "
                + "room, and mention that " + structure_here
                + " is responsible.\n", 0, this_object());
        }
        else
            this_object()->exit_move("enter " + args,
                    find_object(structure_here));
        return 1;
    }

    return 0;
}

int do_swim(string args)
{
    if(args == "in lake" || args == "in the lake")
    {
        write("You dip your toes into the water in preparation for your swim, "
            + "but quickly decide the water is far too cold.\n");
        tell_room(this_object(), QCTNAME(this_player()) + " considers taking "
            + "a swim, but decides the water is much too cold.\n",
            this_player());
        return 1;
    }
    
    notify_fail("Swim in what?\n");

    return 0;
}

void init()
{
    ::init();
    if(structure_here)
        add_action(enter_structure, "enter");
    if(lake_dir)
        add_action(do_swim, "swim");
}

int move_through_forest()
{
    if(random(200) < 50 - this_player()->query_skill(SS_LOC_SENSE))
    {
        mixed *exits = this_object()->query_exit();
        int i = random(sizeof(exits) / 3) * 3; 

        if(LOAD_ERR(exits[i]))
        {
            tell_room(this_object(), "There is a rift in the fabric of "
                + "time and space. Please write a bug report for this "
                + "room, and mention that " + exits[i] + " is responsible.\n",
                0, this_object());
        }
        else       
            exit_move(exits[i + 1], find_object(exits[i]));
        
        return 1;
    }

    return 0;
}

public int exit_move(string exit_cmd, object dest_room)
{
    object player = this_player();
    int retval;
    string *cmd = explode(exit_cmd, " ");

    if(cmd[0] == "enter")
        retval = player->move_living("into the hut", dest_room, 1);
    else
        retval = ::exit_move(exit_cmd, dest_room);
        
    if(!retval)
        foreach(object ob : filter(all_inventory(this_object()),
            &->query_npc()))
            ob->player_left_room(player, file_name(dest_room), exit_cmd);

    return retval;
}

void set_structure_here(string loc)
{
    structure_here = loc;
}

void set_lake_dir(string dir)
{
    lake_dir = dir;
}

void set_creek_dir(string dir)
{
    creek_dir = dir;
}

void set_special(string str)
{
    special = str;
}

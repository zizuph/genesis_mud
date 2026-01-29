/* Standard room for a path through the foothills. ~mucalytic/std/hill_path */

inherit "/std/room";

#include "/sys/money.h"
#include "/sys/macros.h"
#include "../hills/defs.h"
#include "/sys/language.h"
#include "/sys/composite.h"
#include "/sys/stdproperties.h"

inherit STD + "seat";

#define DESC ({ ({ "find yourself", "are standing", "see that you are" }), \
                ({ "terribly", "wildly", "fairly" }), \
                ({ "winding", "meandering", "twisting" }), \
                ({ " hilly region", "n area of undulating hills", \
                   " rolling landscape of hills" }), \
                ({ "Small pebbles", "Round stones", "Jagged rocks" }), \
                ({ "large round", "oddly shaped", "weathered" }) })
int found;

void add_boulder();
string long_description();

void create_hill_path() { }

void create_room()
{
    create_hill_path();

    set_short("A path winding its way through the foothills");
    set_long(long_description());

    add_prop(ROOM_S_DARK_MSG, "The fog is far too thick here to");
    add_prop(ROOM_S_DARK_LONG, "@@fog_bound_description");
//  add_prop(ROOM_I_HIDE, "@@difficulty_in_hiding");
    add_prop(ROOM_I_LIGHT, "@@query_light_cond");
//  add_prop(OBJ_S_SEARCH_FUN, "search_obj");
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_item("terrain", break_string("The terrain is very hilly and there "+
        "is not an area within sight that does not run up and down cease"+
        "lessly.\n", 75));

    add_item(({"pebbles", "stones", "rocks", "small pebbles", "round stones",
        "jagged rocks"}), break_string("They dot the hills and the edges "+
        "of the path almost as frequently as the bushes and weeds do.\n", 75));

    add_item("weeds", break_string("The weeds grow everywhere. They are of "+
        "many different colours and many different shapes. Some are ugly "+
        "and some have beautiful flowers, but all of them grow in the most "+
        "inconvenient places.\n", 75));

    add_item(({"bushes", "green bushes"}), break_string("You notice nothing "+
        "really special about the bushes. They're just rather stubbly and "+
        "misshapen from the wind. Small spots of moisture dot their leaves "+
        "from the mist that sometimes rolls suddenly into this area.\n", 75));

    add_item(({"path", "overgrown path", "fairly overgrown path", "wildly "+
        "overgrown path", "terribly overgrown path"}), break_string("The "+
        "path is made of a scattering of gravelly rock and weeds. It runs "+
        "in a twisty confusing mode and seems to meander in the furthest "+
        "possible route to nowhere at all.\n", 75));

    add_item(({"grass", "green grass", "tumble of grass", "tumble of green "+
        "grass"}), break_string("The grass here grows rampant and green, "+
        "unhindered by man. It grows on the hills and if it were not for "+
        "the infrequent travellers in these parts, it would have already "+
        "have totally overgrown the path you are now travelling upon.\n", 75));

    add_item(({"hills", "foot hills", "foot-hills", "region", "hilly region",
        "undulating hills", "area of undulating hills", "landscape of hills",
        "rolling landscape of hills"}), break_string("The foot-hills roll "+
        "unremittantly and ceaslessly, dominating the terrain about you "+
        "and obscuring almost everything but the sky from your view. "+
        "Everywhere you turn is another undulating landscape covered by "+
        "rocks and grass and other foliage.\n", 75));
}

void add_boulder()
{
    set_seat_name("boulder");

    add_item(({"boulder", "large boulder", "round boulder", "large round "+
        "boulder", "oddly shaped boulder", "weathered boulder"}), "The "+
        "boulder sits by the side of the path, unmovable and solid. It is "+
        "made of the same grey stone as the gravel on the path. It looks "+
        "like an ideal place for you to 'sit' or 'rest' and with all this "+
        "trudging about around the hillside, you reckon that it might do "+
        "you some good. @@query_seated@@\n");
}

void add_money()
{
    MONEY_MAKE(2 + random(9), (random(2) ? "copper" : "silver"))->move(TO);
}

void add_birds()
{
    int i;
    object *birds;

    birds = filter(all_inventory(TO), "filter_birds", TO);

    if(!sizeof(birds))
        for(i = 0; i < (1 + random(5)); i++)
            clone_object(CREATURES + "bird")->move(TO);
}

int filter_birds(object obj)
{
    if(L(obj->query_name()) == "bird")
        return 1;
    else
        return 0;
}

int query_light_cond()
{
    return find_object(HILLS + "hill_control")->query_light_cond(file_name(TO));
}

void become_fogbound()
{
    tell_room(TO, "A bank of thick fog sweeps quitely in from the west.\n");
}

void become_clear()
{
    tell_room(TO, "The fog sweeps quietly away to the west.\n");
}

string long_description()
{
    string desc;
    int direction_count;

    desc = "You ";

    desc += DESC[0][random(3)];

    desc += " on a ";

    desc += DESC[1][random(3)];

    desc += " overgrown path ";

    desc += DESC[2][random(3)];

    desc += " through a";

    desc += DESC[3][random(3)];

    desc += ". ";

    desc += DESC[4][random(3)];

    desc += " and green bushes dot the terrain and an overgrown tumble of "+
        "green grass and weeds grow rampant around you. You notice that "+
        "the path ";

    direction_count = sizeof(query_exit_cmds());

    switch(direction_count)
    {
        case 0:
            desc += "leads nowhere. It doesn't seem to go in any direction.\n";
            break;
        case 1:
            desc += "leads to a dead end here. The only way seems to be in ";
            break;
        case 2:
            desc += "continues in ";
            break;
        case 3:
            desc += "splits in three, leading in ";
            break;
        case 4:
            desc += "becomes a crossroads here and leads in ";
            break;

        default:
            desc += "splits "+LANG_WNUM(direction_count)+" ways, leading in ";
    }

    if(direction_count)
        desc += LANG_ADDART(COMPOSITE_WORDS(query_exit_cmds()))+"erly "+
            "direction.";

    if(query_seat_name() != "none")
    {
        desc += " You notice a ";

        desc += DESC[5][random(3)];

        desc += " boulder standing nearby.";
    }

    return desc + "\n";
}

string fog_bound_description()
{
    string desc;

    desc = "You ";

    desc += DESC[0][random(3)];

    desc += " in the midst of a dense fog-bank in the middle of the "+
        "hills. You can see virtually nothing. You can feel the gravelly "+
        "texture of the path beneath your feet, but otherwise, you are "+
        "virtually blind. You can see nothing but undiscernable shapes in "+
        "the mist. You have the feeling that you are utterly lost!\n";

    return desc;
}

/*
mixed search_obj(object player, string str)
{
    int ran;
    object stone;

    ran = random(3);

    if(str != "road" && str != "cobblestoned road")
        return 0;

    if(!ran && !found)
    {
        found = 1;
        stone = clone_object(OBJECTS + "stone");

        stone->move(TO);

        tell_room(E(player), QCTNAME(player)+" finds "+
            LANG_ADDART(stone->short())+"!\n", player);

        return "You find "+LANG_ADDART(stone->short())+"!\n";
    }
    return 0;
}
*/

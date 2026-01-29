/*
 * The room base for the village Solace (outside rooms)
 */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include "../local.h";
#include <composite.h>
#include <filter_funs.h>

/* Inherit the Krynn room */
inherit OR_FILE

#define CREATE "create_solace_room"
#define RESET  "reset_solace_room"

int gPlace;
string gShort_desc, gLong_desc;

public string leaf_desc();

/* Prototypes */
public void add_bridge();
public void add_leaves();
public void add_tree_up();
public void add_tree_down();
public void add_foliage();

public void
set_place(int i)
{
    gPlace = i;
}

public void
set_short_desc(string str)
{
    gShort_desc = str;
}

public void
set_long_desc(string str)
{
    gLong_desc = str;
}

public void
short_desc()
{
    string str;

    switch (gPlace)
    {
        case MAINROAD:
            gShort_desc = "on the main road in Solace";
            add_leaves();
            add_tree_down();
        break;
        case EASTROAD:
        gShort_desc = "on the east road in Solace";
            add_tree_down();
            add_foliage();
        break;
        case WESTROAD:
        gShort_desc = "on the west road in Solace";
            add_tree_down();
        break;
    case INTERSECTION:
        gShort_desc = "at the intersection";
            add_leaves();
            add_tree_down();
        break;
    case SMALLROAD:
        gShort_desc = "on a small road";
        break;
    case NSPATH:
        gShort_desc = "on a path";
            add_leaves();
        break;
    case PLATFORM:
        gShort_desc = "on a wooden platform";
            add_leaves();
            add_tree_up();
        break;
    case BRIDGEWALK:
        add_bridge();
            add_leaves();
            add_tree_up();
        gShort_desc = "at a wooden bridge-walk high above the ground";
        break;
    case PARK:
        gShort_desc = "in the Solace park";
            add_leaves();
        break;
    case CLEARING:
        gShort_desc = "in a clearing";
        break;
    case SQUARE:
        gShort_desc = "at the Solace square";
        break;
    default:
        break;
    }
}

public string
long_desc()
{
    string desc;

    desc = "You are " + gShort_desc + ". It is " + GET_TIME_STRING + ". ";

    switch (GET_TIMEOFDAY)
    {
        case TOD_DAWN:
           desc += "The sun is rising above the horizon, highlighting " +
               "the mighty Vallenwood trees as they prepare " +
           "for a new day. ";
       break;
        case TOD_DAY:
       desc += "The sun is shining down on you, filtering through the " +
               leaf_desc() + " leaves of the Vallenwood trees. ";
       break;
        case TOD_TWILIGHT:
       desc += "The sun is sinking behind the trees, making the big " +
               "trees cast long shadows. ";
       break;
        case TOD_NIGHT:
       desc += "The pale light from the two moons makes the " +
               "trees cast strange shadows on the ground. ";
       break;
    }

    desc += check_call(gLong_desc) + " ";

    switch (GET_SEASON)
    {
        case WINTER:
            desc += "The chill of the winter is in the air, and all is pale " +
               "and frozen.";
            break;
    case SPRING:
            desc += "Spring is in the air, awakening the land from the " +
               "long winter sleep.";
        break;
        case SUMMER:
            desc += "The land is vibrant with life and color in the warm " +
               "summer.";
        break;
    case AUTUMN:
        desc += "The air grows chill, and though summer is not long " +
               "gone you know winter will be here soon.";
        break;
    }

    return desc + "\n";
}

public void
add_bridge()
{
    add_item("bridge", "@@exa_bridge@@");
}

public void
add_tree_up()
{
    add_item(({"vallenwood", "tree", "trees", "bough", "boughs", "limb", "limbs",
        "canopy", "trunk", "trunks"}),
        "Up here in the loving embrace of the Vallenwood trees, you feel secure "+
        "and protected. There is safety in the solidness of the boughs and the "+
        "gnarled thickness of the trunks. The limbs of the trees form a screen "+
        "against the elements.\n");
}

public void
add_tree_down()
{
    add_item(({"vallenwood", "tree", "trees", "trunks", "trunk"}),
        "These trees are awe-inspiring in their immensity. Their huge trunks "+
        "are wound-around with wooden stairs, and their many branches support "+
        "the floors of houses built there.\n");
}

public void
add_leaves()
{
    add_item(({"leaves", "leaf"}), "You can see that the leaves are "+ leaf_desc() +
      " at this time of the year.\n");
}

public void
add_foliage()
{
    add_item(({"foliage", "forest foliage", "brush", "shrubs"}),
        "The brush lining the road is thick and impenetrable.\n");
}

public string
exa_bridge()
{
    return "The bridge-walk is made of finest wood and stretches from tree " +
           "to tree, allowing people to walk high above the ground among " +
       "the boughs of the mighty Vallenwood trees.\n";
}

public string
leaf_desc()
{
    switch (GET_SEASON)
    {
        case WINTER:
            return "sparse, brown";
        break;
        case SPRING:
          return "pale green";
        break;
        case AUTUMN:
            return "golden";
        break;
        case SUMMER:
        return "green";
        break;
    }
}

public string
get_living(string *rooms)
{
   object *inv, *live, room;
   int i;

   inv = ({});

   i = sizeof(rooms);

   while (i--)
       if ((room = find_object(rooms[i])))
           inv += all_inventory(room);

   if (inv && sizeof(inv))
   {
       live = FILTER_LIVE(inv);
       if (sizeof(live))
           return COMPOSITE_LIVE(live);
   }
   return 0;
}

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);

    short_desc();

    set_short(gShort_desc);
    set_long("@@long_desc@@");
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}


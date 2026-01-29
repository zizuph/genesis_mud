/* 
 * The base indoor room for Thanarian Church Balcony
 * Near the Citadel in Kabal
 * Mirandus - January 31, 2018
 *
 * Update Log: -
 *
 *
 *                     Balcony of the Thanarian Cathedral                                                        
 *                                                                          
 *                       d--O--O--O--O--O--O--O--X                         
 *                       |                       |    d - Down to Cathedral             
 *                       O                       O                         
 *                       |                       |                         
 *                       O                       O                         
 *                       |                       |                         
 *                       O                       O                         
 *                       |                       |                         
 *                       O                       O                         
 *                       |                       |                         
 *                       O                       O                         
 *                       |                       |                         
 *                       d--O--O--O--O--O--O--O--d
 *
 * The High-Lord DID try to push the Thanar underground as their power
 * was growing too strong. In the end, the Avatar of Thanar returned granting
 * too much power to the Thanarian order and he was forced to reopen their
 * church in the city and allow them to return above ground.
 */
#pragma strict_types

#include "../local.h"
#include <files.h>
inherit "/std/room";
inherit STDIR + "room_tell";
inherit STDIR + "thanar_tells";

/* Definitions */
#define FLOOR\
({  \
    RDIR + "alcove_east", \
    RDIR + "alcove_west", \
    RDIR + "entrance", \
    RDIR + "inner_left1", \
    RDIR + "inner_left2", \
    RDIR + "inner_left3", \
    RDIR + "inner_mid", \
    RDIR + "inner_right1", \
    RDIR + "inner_right2", \
    RDIR + "inner_right3", \
    RDIR + "nepath1", \
    RDIR + "nepath2", \
    RDIR + "nwpath1", \
    RDIR + "nwpath2", \
    RDIR + "upper1", \
    RDIR + "upper2", \
    RDIR + "upper3", \
    RDIR + "upper4", \
    RDIR + "upper5", \
    RDIR + "upper6", \
    RDIR + "upper7", \
    RDIR + "upper8", \
    RDIR + "upper9", \
    RDIR + "upper10", \
    RDIR + "upper11", \
    RDIR + "upper12", \
    RDIR + "upper13", \
    RDIR + "upper14", \
    RDIR + "upper15", \
    RDIR + "upper16", \
    RDIR + "upper17", \
    RDIR + "upper18", \
    RDIR + "upper19", \
    RDIR + "upper20", \
    RDIR + "upper_left_path1", \
    RDIR + "upper_left_path2", \
    RDIR + "upper_left_path3", \
    RDIR + "upper_right_path1", \
    RDIR + "upper_right_path2", \
    RDIR + "upper_right_path3", \
    RDIR + "upper_mid1", \
    RDIR + "upper_mid2", \
    RDIR + "upper_mid3", \
    RDIR + "upper_mid4", \
    RDIR + "upper_mid5", \
    RDIR + "upper_mid6", \
    RDIR + "upper_mid7", \
    RDIR + "upper_mid8", \
    RDIR + "upper_mid9", \
    })

/* Prototypes */
public nomask void  create_room();
public void         create_std_thanar();
public void         add_thanar_items();

string smell_air(string str);


/*
 * This function creates the room
 */
public nomask void
create_room()
{
    add_prop(ROOM_I_LIGHT, ALWAYS_LIGHT);
    add_prop(ROOM_I_INSIDE, 1);
    create_std_thanar();
    add_thanar_items();
    set_tell_time(random(400) + 90);
    add_tell("@@get_tells@@" + "\n");
    //add_prop(ROOM_S_MAP_FILE, "/d/Kalad/open/MAP_FILES/new_thanar_church.txt");
    
    if (random(2))
    {
         //Adds the npc, the number of them and then arms them.
         add_npc(LIV +"mpriest", 2, &->arm_me());
         add_npc(LIV +"caster_priest", 2, &->arm_me());
    }
    
}
/* Function name:        create_std_thanar
 * Description  :        dummy function for inheriting rooms to mask
 */
public void
create_std_thanar()
{
    set_short("a set_short is needed here");
    set_long("A set_long is needed here.\n");
    
} 
/*
 * Function name:        add_thanar_items
 * Description  :        Adds the standard items for the road
 *
 */
public void
add_thanar_items()
{  
    
    add_item(({"walls", "wall", "the walls", "the wall"}), "Constructed from "
        + "beautifully hewn black marble, The walls have beautifully "
        + "elaborate oil lanterns attached at regular intervals providing "
        + "an adequate, if not grim, amount of light. They are adorned are "
        + "certain instances along the walls are opulent framed oil "
        + "paintings.\n");
    add_item(({"lanterns","oil lantern","lantern", "oil lanterns",
        "light", "lights", "lamps", "lamp"}),
        "Marvellously designed with flourishes of black iron these lanterns "
        + "are fed by a system of pipes that carry an endless supply of oil "
        + "automatically. A marvel of a design ensuring endless light to "
        + "cast shadows off the black marble walls.\n");
    add_item(({"ceiling", "ceilings", "beams", "thick wood", 
          "pieces of wood", "wood"}), "The ceilings of this church are "
        + "constructed from massive beams of wood culled from some unknown "
        + "place and set in support of the steel ceiling in a marvel of "
        + "ingenuity and engineering. The steel slats on the ceiling are "
        + "held together by some unknown force. The ceilings are supported "
        + "by powerfully built marble columns.\n");
    add_item(({"floor", "floors"}), "The floors are made of polished marble "
        + "tile. The black surface shows no signs of dirt or dust and appears "
        + "well tended.\n");
    add_item(({"pew", "pews", "seat", "seats", "benches", "bench"}), "Pews "
        + "are visible from most places within the church. Made of a dark "
        + "unknown wood, they shimmer in the dim light cast by the lanterns "
        + "attached to the walls. They look as though they would not be "
        + "uncomfortable, but they offer no luxury.\n");
    add_item(({"snake", "symbol", "symbol of thanar", "thanar symbol",}),
    "Visible at various locations is the symbol of small black snake. This "
    + "is the holy symbol of Thanar. It protects the pure from the wicked and "
    + "ensures that the superiority of the human race will be recognized.\n");
    add_item(({"column", "columns", "pillar", "pillars", "marble column",
    "marble columns", "marble pillar", "marble pillars"}), "The ceiling is "
     + "supported by large marble columns and pillars. They are black, "
     + "shimmering and stand tall. Engraved the length of the pillar "
     + "is a snake that winds it's way up from the floor to the ceiling.\n");
    add_item(({"sanctum", "sanctum sanctorum", "holy place", "holy space", 
    "sanctuary"}), "From where you stand you can see the sanctum, or sanctum "
    + "sanctorum. This is the most sanctified space within the Cathedral "
    + "and is only accessible to the Priests. Items of great import can "
    + "be kept there. You can see shimmering objects along with tomes "
    + "and scrolls.\n");
    add_item(({"below", "ground", "church", "down",}),"@@floor_desc");
    add_item(({"natives", "priests", "priestesses", "clergy", "members",
    "order", "members of the order", "Thanarians",}),"@@natives_desc");
    add_item(({"people", "non-natives", "outsiders", "others", "non-member"})
    ,"@@nonnatives_desc");
    add_item(({"fighting", "combat", "battle"}),"@@battle_desc");
    add_item(({"killed", "bodies", "dead"}),"@@dead_desc");
    add_item(({"shimmering items", "treasures", "tomes", "books", "tome", 
    "book", "holy tomes", "holy books", "holy tome", "holy book",
    "shimmering item", "shimmering object", "shimmering objects"}),
    "Behind the sanctum you see a variety of items shimmering and dull. "
    + "The glittering gold of crosses, coins, and jewellery along with gems "
    + "and encrusted books. Dusty tomes are stacked on shelves created from "
    + "the marble walls. Scrolls are neatly stacked within a marble scroll "
    + "store. Details can not be seen from outside the sanctum.\n");
}

int
smell_air(string str)
{
    
    notify_fail("Smell what?\n");
    if (str != "air" && str != "the air" && str != "area" 
    && str != "the area" && str != "incense"   && str != "smoke")
    return 0;
    
    else
    say(QCTNAME(this_player()) +
    " smells the area around them subtly, inhaling deeply with a calming "
    +"smile.\n");
    write("You smell the air around you and immediately feel calm from the "
    +"marvellous incense.\n");
    return 1;
}

/*
 * Function name: get_all_no_exits
 * Description: Returns an array of strings with exits for use with
 *              set_no_exit_msg()
 * Argument: Array of exits to exclude, for simplicity you can use
 *           nw instead of northwest, etc.
 */
string *
get_all_no_exits(string *exits)
{
    string *r_exits = m_values(NORMAL_EXITS);
    foreach (string exit: exits) {
        foreach (string ind, string val: NORMAL_EXITS) {
            if (exit == ind || exit == val) {
                r_exits -= ({ val });            
            }
        }
    }
    return r_exits;
}

/*
 * Function name: enter_inv()
 * Description: Starts the room tells when someone enters the rooms
 *              inventory
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}

/*
 * Function name: floor_desc()
 * Description: Returns an array of strings with people in it for use
 *              in some fun descriptions
 */
string
floor_desc()
{
    string *roomfiles;
    object *inv, *live, *corpses, *natives, room;
    int i;

    roomfiles = FLOOR;
    roomfiles -= ({ E(TP) });
    inv = ({});
    for (i = 0; i < sizeof(roomfiles); i++)
    {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
    }

    if (inv && sizeof(inv) > 0)
    {
        
    live = FILTER_LIVE(inv);
    natives = filter(live, &wildmatch(LIV + "*",) @&file_name());
    live -= ({ TP }) + natives;
    corpses = filter(inv, &operator(==)(,CORPSE_OBJECT)@ 
    &function_exists("create_container",));
    
    
    if (sizeof(natives) > 0 && sizeof(corpses) > 0)
    return ("Down within the church, you can see " + 
        LANG_NUM2WORD(sizeof(natives)) + " members of the Thanarian "
        +"Order moving around" + (sizeof(live) ? ", as well as " 
        + COMPOSITE_LIVE(live) + " not of the order" : "") 
        + ". You also see " + LANG_NUM2WORD(sizeof(corpses)) + " who " 
        + (sizeof(corpses) > 1 ? "are" : "is") + " likely dead.\n");
    else if (sizeof(natives) > 0)
    return ("Down within the church you can see " + 
        LANG_NUM2WORD(sizeof(natives)) + " members of the Thanarian "
        +"Order moving about" + (sizeof(live) ? " as well as " 
        + COMPOSITE_LIVE(live) + " not of the order" : "") + ".\n");
    }
    return ("The church below looks empty and cold.\n");
}

/*
 * Function name: natives_desc()
 * Description: Returns an array of strings with people in it for use
 *              in some fun descriptions
 */
string
natives_desc()
{
    string *roomfiles;
    object *inv, *live, *corpses, *natives, room;
    int i;

    roomfiles = FLOOR;
    roomfiles -= ({ E(TP) });
    inv = ({});
    for (i = 0; i < sizeof(roomfiles); i++)
    {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
    }

    if (inv && sizeof(inv) > 0)
    {
        
    live = FILTER_LIVE(inv);
    natives = filter(live, &wildmatch(LIV + "*",) @&file_name());
    live -= ({ TP }) + natives;
    corpses = filter(inv, &operator(==)(,CORPSE_OBJECT)@ 
    &function_exists("create_container",));
    
    
    if (sizeof(natives) > 0 && sizeof(corpses) > 0)
      return ("Down within the church, you can see " +
          LANG_NUM2WORD(sizeof(natives)) + 
          " members of the Thanarian Order moving around. "
          +"There are also "+ LANG_NUM2WORD(sizeof(corpses)) + " who "
          + (sizeof(corpses) > 1 ? "are" : "is")+" likely dead.\n");
    else if (sizeof(natives) > 0)
      return ("Down within the church you can see " +
      LANG_NUM2WORD(sizeof(natives)) + " members of the Thanarian Order "
      +"moving about.\n");
    }
    return ("The church below looks empty and cold.\n");
}
 
 /*
 * Function name: nonnatives_desc()
 * Description: Returns an array of strings with people in it for use
 *              in some fun descriptions
 */

string
nonnatives_desc()
{
    string *roomfiles;
    object *inv, *live, *corpses, *natives, room;
    int i;

    roomfiles = FLOOR;
    roomfiles -= ({ E(TP) });
    inv = ({});
    for (i = 0; i < sizeof(roomfiles); i++)
    {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
    }

    if (inv && sizeof(inv) > 0)
    {
        
    live = FILTER_LIVE(inv);
    natives = filter(live, &wildmatch(LIV + "*",) @&file_name());
    live -= ({ TP }) + natives;
    corpses = filter(inv, &operator(==)(,CORPSE_OBJECT)@ 
    &function_exists("create_container",));
    
    
    if (sizeof(live) > 0 && sizeof(corpses) > 0)
      return ("Down within the church, you can see " +
          COMPOSITE_LIVE(live) + " not of the order. There are also "
          + LANG_NUM2WORD(sizeof(corpses)) + "who" + 
          (sizeof(corpses) > 1 ? "are" : "is")+" likely dead.\n");
    
    else if (sizeof(live) > 0)
      return ("Down within the church you can see "+COMPOSITE_LIVE(live)
      +" who's an outsider to the Thanarian order.\n");
    }
    return ("You do not see anyone who does not belong.\n");
}

/*
 * Function name: battle_desc()
 * Description: Returns an array of strings with people in it for use
 *              in some fun descriptions
 */
string
battle_desc()
{
    string *roomfiles;
    object *inv, *live, *corpses, *combat, room;
    int i;

    roomfiles = FLOOR;
    roomfiles -= ({ E(TP) });
    inv = ({});
    for (i = 0; i < sizeof(roomfiles); i++)
    {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
    }

    if (inv && sizeof(inv) > 0)
    {
        
    live = FILTER_LIVE(inv);
    live -= ({ TP });
    combat = filter(live, &objectp() @ &->query_attack());
    corpses = filter(inv, &operator(==)(,CORPSE_OBJECT)@ 
    &function_exists("create_container",));
    
    
    if (sizeof(combat) > 0 && sizeof(corpses) > 0)
      return ("Down within the church, you can see " +
          COMPOSITE_LIVE(combat) + " in the heat of battle as well as "
          + LANG_NUM2WORD(sizeof(corpses)) + 
          " who have already succumb to death.\n");
    else if (sizeof(combat) > 0)
      return ("Down within the church you can see "+COMPOSITE_LIVE(combat)
      +" in the heat of battle.\n");
    }
    return ("You do not see anyone in combat below.\n");
}

/*
 * Function name: dead_desc()
 * Description: Returns an array of strings with people in it for use
 *              in some fun descriptions
 */
string
dead_desc()
{
    string *roomfiles;
    object *inv, *live, *corpses, *combat, room;
    int i;

    roomfiles = FLOOR;
    roomfiles -= ({ E(TP) });
    inv = ({});
    for (i = 0; i < sizeof(roomfiles); i++)
    {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
    }

    if (inv && sizeof(inv) > 0)
    {
        
    live = FILTER_LIVE(inv);
    live -= ({ TP });
    corpses = filter(inv, &operator(==)(,CORPSE_OBJECT)@ 
    &function_exists("create_container",));
    
    
    if (sizeof(live) > 0 && sizeof(corpses) < 0)
      return ("Down within the church, you can see that all are living.\n");
    else if (sizeof(corpses) > 0)
      return ("Down within the church you can see "+COMPOSITE_LIVE(corpses)
      + " who " + (sizeof(corpses) > 1 ? "have" : "has") + " passed to "
      + "the next life.\n");
    }
    return ("You do not see anyone dead below.\n");
}

/*
 * Function name: init()
 * Description: initializes commands
 */
public void
init()
{
    ::init();
    add_action(smell_air, "smell");
}
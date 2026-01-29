/* /d/Faerun/guilds/fire_knives/rooms/sm.c
 *
 * Smith Room, based on the MM smithy coded 
 * by Olorin, 13-Mar-1997.
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <composite.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;

#define FIREKNIVES_WEAPON   (FIREKNIVES_GUILD_DIR + "obj/fireknives_weapon")
#define FIREKNIVES_WSMITH   (FIREKNIVES_GUILD_DIR + "npc/smithy")

/*
 *      Prototypes:
 */
static string *check_stock();
static string  exa_list();
static string  exa_weapons();
public void    make_weapon(string wt);

/*
 *      Global variables:
 */
static mapping In_Stock = ([]);
static int     Make_Alarm;
static object  WSmith;

static mapping
setup_weapon_stock()
{
    int     i;
    string *wtype;

    wtype = FIREKNIVES_WEAPON->query_weapon_types();

    for (i = 0; i < sizeof(wtype); i++)
    {
        In_Stock[wtype[i]] = 1;
        add_item( ({ wtype[i] }), BSN(
            FIREKNIVES_WEAPON->query_weapon_long(wtype[i])));
    }

    return In_Stock;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("A blacksmith's shelter");
    
    set_long("Inside a small circular shelter "
    +"carved within the rock of the keep "
    +"you find the scragged walls patched with "
    +"mortar, brick and old stones, all "
    +"covered in layers of a thin, black dust "
    +"that seems part of the structure's "
    +"color rather than accumulated over time. Mounted "
    +"on the walls are flat pieces "
    +"of wood upon which tools and materials hang. On "
    +"the left side of the room "
    +"are crooked wooden tables with a myriad other "
    +"tools, while to the right is "
    +"a cubic structure made of bricks and rising towards "
    +"the ceiling, lost in its "
    +"impenetrable darkness. In the center "
    +"of the room is an anvil surrounded by "
    +"hammers and thongs of various shapes and "
    +"sizes, all apparently randomly "
    +"placed upon the dirt covered floor. A wooden table is "
    +"placed next to the anvil, which you can "
    +"<check> to see what's currently available "
    +"for purchase.\n");
    
    add_item(({"shelter","room","area"}),
    "The area seems to be carved out of the very rocks "
    +"that make up the keep, and "
    +"its reformations kept to a minimum, barely "
    +"enough to sustain the equipment "
    +"and facilities required for the labor. The "
    +"most elaborate of all constructions "
    +"is that of the cubic structure rising up on the "
    +"right side of the room. Made of "
    +"brick and mortar, with a hole in the center, it "
    +"resembles a chimney of sorts "
    +"through which the smoke escapes and ascends towards the ceiling.\n");
 
    add_item(({"wall","walls","scragged walls"}),
    "The walls are dry and covered in thin layers of black "
    +"dust, the heat dissipating "
    +"the moisture that characterizes the rest of "
    +"the area. On them are thick, flat "
    +"pieces of wood upon which tools and materials hang. \n");
 
    add_item(({"mortar","brick","stone","old stone","stones","old stones","structure","cubic "
    +"structure","chimney"}),
    "The cubic structure rises up on the right side of the room. It "
    +"is made of brick and mortar, with a whole in the center, resembling "
    +"a chimney through which the "
    +"smoke escapes and ascends towards the ceiling.\n");
 
    add_item(({"dust","black dust"}),
    "The walls are covered in thin layers of black dust. Their "
    +"thinness reflect some "
    +"sort of maintenance, though not enough to it being obvious. \n");
    
    add_item(({"table"}),
    "This is a simple wooden table next to the anvil. You can <check> it to "
    +"see what types of daggers or knives that are available for purchase.\n");
    
    add_item(({"crooked tables", "tables"}),
    "A few crooked wooden tables filled with various tools, as opposed to the "
    +"other table with the buyable weaponry.\n");
 
    add_item(({"wood","flat pieces","pieces","pieces of wood","planks"}),
    "Flat pieces of wood are embedded onto the walls, serving "
    +"as a hanging place "
    +"from which the tools dangle.\n");
    
    add_item(({"tools","materials","metals","thongs","hammers","hammer"}),
    "Blacksmiths' tools such as hammers, thongs, metals, and "
    +"other miscellanea are found "
    +"on the floor next to the tables and hanging from the "
    +"wooden planks on the wall.\n");

    add_item(({"ceiling","darkness"}),
    "The ceiling is lost in the darkness gathering around "
    +"it, and is only marked by the "
    +"rising chimney.\n");

    add_item(({"anvil"}),
    "An old, battered, single horn anvil made of forged steel "
    +"lies in the center of the "
    +"room. The large block is flattened at the top even "
    +"after the incountable amount of "
    +" times it must have been struck.\n");
    
    add_item(({"dirt","floor"}),
    "Dirt with layers of dust sprinkled on it covers the "
    +"entire stoney floor, marking "
    +"your footprints as clearly as sand would. Here "
    +"and there it seems visible that "
    +"it has been swept and cleaned, but the constant "
    +"amount of work doesn't allow "
    +"such a state to perdure.\n");
        
    setup_weapon_stock();

    add_exit(FIREKNIVES_ROOMS_DIR + "c2", "west");

    reset_faerun_room();
}


static int
add_weapon(string wt)
{
    In_Stock[wt] += 1;
    remove_item(wt);
    add_item( ({ wt }), BSN(
        FIREKNIVES_WEAPON->query_weapon_long(wt)));
}


public int
remove_weapon(string wt)
{
    if (!In_Stock[wt])
        return 0;

    In_Stock[wt] -= 1;
    remove_item(wt);
    add_item( ({ wt }), "There is no "+wt+" on display or for sale.\n");

    if (!Make_Alarm)
    {
        Make_Alarm = set_alarm(20.0, 0.0,
            &make_weapon(wt));
            
        set_alarm(20.0, 0.0, &WSmith->command("emote finishes "
        +"his work at forge and anvil and puts the new "+wt+" at the "
        +"table."));
        
        WSmith->delay_command("emote starts forging a new "+wt+".");
    }

    return 1;
}


public void
make_weapon(string wt)
{
    Make_Alarm = 0;

    //if (!objectp(WSmith) || !objectp(present(WSmith, TO)))
      //  return;

    WSmith->forge_weapon(wt);
    add_weapon(wt);

    check_stock();
}


static int
query_in_stock(string w)
{
    return In_Stock[w];
}


public string *
query_weapon_stock(int art = 0)
{
    object  lang;
    string *wep = m_indexes(In_Stock);

    if (!m_sizeof(In_Stock))
        return 0;

    wep = filter(wep, query_in_stock);

    if (art)
    {
        lang = find_object(LANG_FILE);
        wep = map(wep, &lang->add_article());
    }

    return wep;
}


static string *
check_stock()
{
    string *wep = m_indexes(In_Stock),
            nw;

    if (!m_sizeof(In_Stock))
        return 0;

    wep -= filter(wep, query_in_stock);

    if (!sizeof(wep))
        return 0;

    if (Make_Alarm || !objectp(WSmith) || !objectp(present(WSmith, TO)))
        return wep;
    else
    {
        Make_Alarm = set_alarm(20.0, 0.0,
            &make_weapon(nw = ONE_OF_LIST(wep)));
            
        set_alarm(20.0, 0.0, &WSmith->command("emote finishes "
        +"his work at forge and anvil and puts the new "+nw+" at the "
        +"table."));
            
        WSmith->delay_command("emote starts forging a new "+nw+".");
    }

    return wep;
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
    
    if (!WSmith)
    {
        WSmith = clone_object(FIREKNIVES_WSMITH);
        WSmith->move(this_object(), 1);
    }
    
    check_stock();
}


static string
exa_weapons()
{
    string  desc,
           *wstock;

    desc = "The weapon smith manufactures primary daggers and knives. "
      + "On the table of the blacksmith he "
      + "displays the weapons he has for sale. Presently you can see ";

    if (sizeof(wstock = query_weapon_stock()))
        desc += COMPOSITE_WORDS(query_weapon_stock(1));
    else
        desc += "no weapons on the table, they must all be sold out";

    desc += ".";

    return BSN(desc);
}


static string
exa_list()
{
    if (!objectp(WSmith))
    {
        write(BSN(
            "On the sign is a list of the prices for the weapons "
          + "that are for sale here. But since the weapon smith is not "
          + "here, the list is of no interest."));
    }
    else
    {
        WSmith->do_weapon_list("", 1);
    }
    return "";
}


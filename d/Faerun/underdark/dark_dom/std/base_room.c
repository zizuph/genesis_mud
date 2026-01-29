/*
 * Base room for caves of Sword mountain, leading into Underdark
 * -- Finwe, May 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_INDOORS_BASE;
inherit "/d/Faerun/std/room_tell";
inherit "/d/Faerun/std/search";
inherit "/d/Faerun/std/cmd_parse";
inherit HERB_SEARCH;

#define MAX_NPCS 3

static object *npc = allocate(MAX_NPCS);

// Added so you can add extra descriptions to the room.
static string extraline = "This is a tunnel description.";

//  Prototypes
void   set_extraline(string str) { extraline = str; }
function vbfc_extra;

void
create_tunnel()
{
}

public string
long_desc()
{
    string  desc = CAP(query_short()) + ". ";

    if (strlen(extraline))
        desc += extraline;

    if (functionp(vbfc_extra))
        desc += vbfc_extra();

    return (desc + "\n");
}


void
create_room()
{
    add_std_herbs("underdark");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1); /* dark tunnel */
    add_prop(ROOM_S_MAP_FILE, "dark_dom_map.txt");

    set_short("Somwhere in the Underdark");
    set_long(long_desc);
    set_room_tell_time(120 + random(60));
//    set_room_tell_time(5);
    add_room_tell("Scratching sounds echo from somewhere in the tunnels.");
    add_room_tell("A sound of pain echos from deep in the tunnels.");

    add_item(({"walls", "wall", "tunnel"}),
        "The walls are naturally carved from the rock. They are irregularly " +
        "shaped and rough looking, arching overhead to form a rough ceiling " +
        "above you.\n");
    add_item(({"floor", "ground"}),
        "The ground is irregular and rough looking. It looks relatively clean.\n");
    add_item(({"ceiling"}),
        "The ceiling is high above you. It is lost in the shadows.\n");
    add_item(({"rock"}),
        "The rock is dark and likely granite. It is very hard and looks " +
        "impervious. Ornate designs have been carved into the rock.\n");
    add_item(({"air"}),
      "It feels thick and stifling, surrounding everything with a black stillness.\n");
    add_item(({"darkness", "thick darkness", "black stillness"}),
        "It fills the tunnels, blocking your view and hiding anything around you.\n");

    create_tunnel();
}

/*
 * Function name : enter_inv
 * Description   : sman enter_inv for more details.  It's masked here
 *                 for room_tell support.
 */
public void
enter_inv(object ob, object from)
{
    if (sizeof(query_room_tells()))
	start_room_tells();
    ::enter_inv(ob,from);
}


string tun_desc1(string str)
{
    return "Dark stone surrounds you in all directions. The " +
        "tunnel looks dark and forbidding with a sense of uneasiness. " +
        "The weight of the mountain seems to weigh on you in this dark place. " +
        str;
}

string tun_desc2(string str)
{
    return "It seems heavy and endless, winding its way " +
        "through the dark stone of the mountain. The dark stone seems " +
        "uncut, as if the tunnel was formed naturally. A dark stillness " +
        "fills the tunnel. " + str;
}

string tun_desc3(string str)
{
    return "It cuts through the rough stone. The forbidding " +
        "tunnel is looks dark and dangerous. Darkness fills the tunnel. " +
        "An oppressive silence hangs in the air, as dense as the stone " +
        "around you. " + str;
}

string tun_desc4(string str)
{
    return "Silence and darkness fills the tunnels. The " +
        "weight of the mountain seems heavy in this forbidding place. " +
        "The dark tunnel is rough and wanders aimlessly through the " +
        "mountain. " + str;
}

string tun_desc5(string str)
{
    return "It is rough looking and looks natural, cutting through the " +
        "mountain that hangs over you. A deep darkness spreads through " +
        "the tunnel. A stillness hangs in the air. " + str;
}


/*
 * add_items to add to rooms
 */

/*
 * Function name : set_add_mountain
 * Description   : adds descr of mountains in the forest
 */
void set_add_remains()
{
    add_item(({"remains"}),
        "They are what's left of something that got lost in the tunnels. " +
        "The remains look unrecognizable, probably once a foolish human, " +
        "goblin or worse.\n");
    add_item(({"bones"}),
        "They look broken and gnawed. They are scattered around the remains.\n");
}

void set_add_stalags()
{
    add_item(({"stalactite", "stalactites"}),
        "They are icicle-shaped of mineral deposits that hang from the ceiling. They are large and look ancient, some even reaching to the ground.\n");
    add_item(({"stalagmites", "stalagmite"}),
        "They are conical shaped mineral deposits. They form from dripping water that seeps through the tunnel and falls from the ceiling. They are all sizes, some towering over you as columns.\n");
    add_item(({"deposits", "deposit", "mineral deposit",
            "mineral deposits"}),
        "They are composed of drippings from the ceiling that have been built up over time. Some hang as stalactites and others rise from the floor as stalagmites.\n");
}

void make_goblins()
{
    int index, npc_count;

    setuid();
    seteuid(getuid());

    npc_count = random(MAX_NPCS);

    if(npc_count ==0)
        npc_count = 3;

    for(index = 0; index < npc_count; index++)
    {
        if (!objectp(npc[index]))
        {
            setuid();
            seteuid(getuid());

            npc[index] = clone_object(NPC_DIR + "goblin");
            npc[index]->move(TO);
        }
    }


//	object goblin;
//    int i;
//
//    if (!present("goblin"))
//    {
//        for (i=1; i<=4; i++ )
//            goblin = clone_object(NPC_DIR + "goblin")->move(this_object());
//        tell_room(TO,"A goblin comes rushing in, preparing to fight.\n");
//    }
}


void make_svirf()
{
    int index, npc_count;

    setuid();
    seteuid(getuid());

    npc_count = random(MAX_NPCS);

    if(npc_count ==0)
        npc_count = 3;

    for(index = 0; index < npc_count; index++)
    {
        if (!objectp(npc[index]))
        {
            setuid();
            seteuid(getuid());

            npc[index] = clone_object(NPC_DIR + "svirf");
            npc[index]->move(TO);
        }
    }


//	object svirf;
//    int i;
//
//    if (!present("svirfneblin"))
//    {
//        for (i=1; i<=3; i++ )
//            svirf = clone_object(NPC_DIR + "svirf")->move(this_object());
//        tell_room(TO,"A svirfneblin rushes in, preparing to defend itself.\n");
//    }
}

void make_drow()
{
    int index, npc_count;

    setuid();
    seteuid(getuid());

    npc_count = random(MAX_NPCS);

    if(npc_count ==0)
        npc_count = 3;

    for(index = 0; index < npc_count; index++)
    {
        if (!objectp(npc[index]))
        {
            setuid();
            seteuid(getuid());

            npc[index] = clone_object(NPC_DIR + "drow_w");
            npc[index]->move(TO);
        }
    }
}

void make_illithids()
{
    int index, npc_count;


    npc_count = random(MAX_NPCS);

    if(npc_count ==0)
        npc_count = 3;

    for(index = 0; index < npc_count; index++)
    {
        if (!objectp(npc[index]))
        {
            setuid();
            seteuid(getuid());

            npc[index] = clone_object(NPC_DIR + "illithid");
            npc[index]->move(TO);
        }
    }

//	object illithid;
//    int i;
//
//    if (!present("_illithid"))
//    {
//        for (i=1; i<=4; i++ )
//            illithid = clone_object(NPC_DIR + "illithid")->move(this_object());
//    }
}

/*
 * Fix to get rid of the obnoxius 'What ?' when we try to walk in a nonexistant
 * direction. These are the default direction commands in the prefferred order.
 */
#define DEF_DIRS ({ "north", "east", "south", "west", \
    "northeast", "northwest", "southeast", "southwest", "up", "down" })

/*
 * The following two sort functions are used to sort the exits in
 * a specific, unified format.  Check the DEF_DIRS define for the
 * sorted order of the standard exits.  All other exits will be
 * added in AFTER those 10 in alphabetical order.
 * And yes, I know it looks like an ugly hack, but it DOES work. ;)
 */
static nomask int
sort_alpha(string one, string two)
{
    if (one > two)
		return 1;
    if (one < two)
		return -1;
    return 0;
}

static nomask int
resort_exits(string one, string two)
{
    int a, b;

    a = member_array(one, DEF_DIRS);
    b = member_array(two, DEF_DIRS);

    if (a >= 0 && b == -1)
		return -1;
    if (a == -1 && b >= 0 )
		return 1;
    if (a == b)
		return sort_alpha(one, two);
    if (a > b)
		return 1;
    if (a < b)
		return -1;
    return 0;
}

/* This is masked to sort the exits. */
public string *
query_obvious_exits(void)
{
    string *obv_exits = ::query_obvious_exits();

    if (obv_exits)
		obv_exits = sort_array(obv_exits, resort_exits);

    return obv_exits;
}


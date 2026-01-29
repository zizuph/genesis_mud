/*
 * Standard file for Morgul Tower
 * 
 * January 1994 by Olorin
 * 
 * Modification log:
 * Olorin, 31-Oct-1995: Put add_items from tower_defs.h into this file,
 *                      changing them into functions.
 * Olorin, 22-Apr-1997: Change to /d/Gondor/std/room.c
 * 
 * Toby, 10-Sept-2007 : Added terrain type to the Tower.
 * Eowul, 27-Juli-2013 : Make the tower always dark
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <terrain.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/time.c"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"

//	Global variables
static  object  clock = find_object(CLOCK);
static  string  extra_long,
                short_desc,
                room_type;
static  int     level;

//	Prototypes
       int     time_check(string str);
public string  long_desc();

void    set_extra_long(string x) { extra_long = x; }
void    set_level(int i)         { level = i; }
void    set_room_type(string s)  { room_type = s; }
void    set_short_desc(string s) { short_desc = s; }

void
init()
{
    ::init();
    add_action(time_check, "time");
}

int
time_check(string str)
{
    if (!IS_MORGUL_MAGE(TP))
    {
        write("For some reason you have completely lost your sense of time here.\n");
        return 1;
    }
    return check_time("");
}

int
query_is_morgul_mage(object player)
{
    return (player->query_guild_name_occ() == GUILD_NAME);
}

void
create_morgul_tower_room()
{
    set_short("In the Tower of Minas Morgul");
    set_extra_long("A room in the Tower of Dark Sorcery in Minas Morgul.\n");
    set_room_type("room");
}

nomask void
create_gondor()
{
    add_prop(ROOM_I_LIGHT, 0);

    set_terrain(TERRAIN_SHADOWS | TERRAIN_COLD | TERRAIN_ROCK | TERRAIN_HASDEAD);

    create_morgul_tower_room();

    if(level < 3)
       add_prop(ROOM_M_NO_TELEPORT, "The Dark Lord of Arda prevents your magicks " +
                                 "to work properly and you can not teleport to your " +
                                 "destination.\n");

    if (!stringp(short_desc))
    {
        short_desc = CAP(LANG_ADDART(room_type));
        switch(level)
        {
            case 0:
                short_desc += " on the ground floor of";
                break;
            case 1..5:
                short_desc += " on the "+LANG_WORD(level)+" floor of";
                break;
            case 6:
                short_desc += " at the top of";
                break;
            case 7:
                short_desc += " at the roof of";
                break;
            default:
                short_desc += " somewhere in";
                break;
        }
        short_desc += " the Tower of Black Sorcery";
    }
    set_short(short_desc);

    set_long(long_desc);

    if(level < 7)
       add_prop(ROOM_I_INSIDE, 1);
}

public string
long_desc()
{
    string  desc;

    desc = short() + ". ";

    if (stringp(extra_long))
        desc += extra_long;

    return BSN(desc);
}

varargs void
add_walls(string extra)
{
    string  desc =
        "The walls are made of black square stone blocks. The "
      + "blocks fit so well that there are hardly any seams "
      + "visible between them. The surface of the blocks has been "
      + "polished so it is very smooth and it seems to absorb light.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"wall","walls"}), BSN(desc));
}

varargs void
add_roof(string extra)
{
    string  desc =
        "The ceiling is high above your head and out of reach for "
      + "your hands. It is made from the same black stone blocks as the "
      + "walls and like them seems to absorb light.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"roof", "ceiling"}), BSN(desc));
}

varargs void
add_no_roof(string extra)
{
    string  desc =
        "The roof is so high that it is lost to view in utter darkness.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"roof","ceiling"}), BSN(desc));
}

varargs void
add_floor(string extra)
{
    string  desc = 
        "The floor is made of square black stone slabs. The surface "
      + "of the slabs has been polished so it is extremly smooth and "
      + "shows hardly any signs of wear.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"floor", "ground"}), BSN(desc));
}

varargs void
add_staircase(string extra)
{
    string  desc = 
        "The spiral staircase disappears in the floor here, leading down "
      + "to the ground level of the Tower. Upwards it soon disappears "
      + "from view, hidden in the unfathomable darkness above.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"staircase","stairs","spiral staircase","stairway"}),
        BSN(desc));
}

/*
 * Let the mages switch on the lights.
 */
public int
query_light_level()
{
//  if (IS_MORGUL_MAGE(TP))
//      return 1;
   if (sizeof(filter(all_inventory(TO), &operator(==)(GUILD_NAME) @ &->query_guild_name_occ())))
        return 1;
    return 0;
}


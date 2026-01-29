/*
 * Standard file for the cellars under the Morgul Tower
 * 
 * July 1994 by Olorin
 * 
 * Modification log:
 *
 *    2006.08.27, Fixed a typo (darknees - darkness), Toby
 *                Also removed obsolete BSN.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

public string  long_desc();

static object  clock;
static string  extra_long,
               short_desc,
               room_type = "dungeon";
static int     level = 0;

void    set_extra_long(string x) { extra_long = x; }
void    set_level(int i)         { level = i; }
void    set_room_type(string s)  { room_type = s; }
void    set_short_desc(string s) { short_desc = s; }

varargs int
time_check(string str)
{
    if (!IS_MORGUL_MAGE(TP))
    {
        write("For some reason you've completely lost your sense of time here.\n");
        return 1;
    }
    return check_time(str);
}

public void
init()
{
    ::init();
    add_action(time_check, "time");
}

int
query_is_morgul_mage(object player)
{
    return (IS_MORGUL_MAGE(player));
}

void
create_morgul_cellar_room()
{
    set_short("under the Morgul Tower");
    set_extra_long("A dark and damp cellar under the Tower of Dark " +
        "Sorcery in Minas Morgul. ");
}

nomask public void
create_gondor()
{
    add_prop(ROOM_I_LIGHT, 0);

    create_morgul_cellar_room();

    add_prop(ROOM_M_NO_TELEPORT, "The Dark Lord of Arda prevents your magicks " +
                                 "to work properly and you can not teleport to your " +
                                 "destination.\n");

    if (!stringp(short_desc))
    {
        short_desc = LANG_ADDART(room_type);
        switch(level)
        {
            case 1..5:
                short_desc += " on the "+LANG_WORD(level)+" floor below";
                break;
            default:
                short_desc += " somewhere in";
                break;
        }
        short_desc += " the Tower of Black Sorcery";
    }
    set_short(short_desc);

    set_long(long_desc);

    add_prop(ROOM_I_INSIDE, 1);
}

public string
long_desc()
{
    string  desc;

    desc = CAP(short()) + ".";

    if (stringp(extra_long))
        desc += (" " + extra_long);

    return (desc + "\n");
}

int
query_allow_escape(object enemy, object attacker)
{
    int     chance;

    if (enemy->query_npc())
        return 1;

    chance = 50 + attacker->query_stat(SS_DEX) - enemy->query_stat(SS_DEX);
    if (chance > 90)
        chance = 90;
    else if (chance < 10)
        chance = 10;
    if (random(100) < chance)
        return 0;
    return 1;
}

int
check_exit()
{
    string  dir = query_verb();
    object  tp = TP,
            attacker;

    if (objectp(attacker = tp->query_attack()))
    {
        if (!query_allow_escape(tp, attacker))
            return 1;
    }
}

int
block_npc()
{
    if (TP->query_npc())
        return 1;
    return check_exit();
}

int
block_exit()
{
    object stopper;

    if (stopper = TP->query_attack())
    {
        write(CAP(LANG_ADDART(stopper->query_nonmet_name())) +
            " stops you from going there!\n");
        return 1;
    }

    if ((stopper = present("_morgul_monster",TO)))
    {
        if (CAN_SEE(stopper,TP))
        {
            write(CAP(LANG_ADDART(stopper->query_nonmet_name())) +
              " stops you from going there!\n");
            stopper->init_attack();
            return 1;
        }
    }
    return check_exit();
}

/*
 * Function for add_item() of standard items in the cellar rooms.
 * Modified from obsolete cellar_defs.h
 *
 * Olorin, October 1995
 */
varargs void
add_floor(string extra)
{
    string  desc;

    desc = ONE_OF_LIST( ({
        "The floor is made out of large dark stone slabs.",
        "Large slabs of black stone make up the floor here.",
        "The floor is covered by large black stone slabs.",
        "The floor is made from large black cobblestones.",
        }) );

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"floor", "ground"}), desc + "\n");
}

varargs void
add_ceiling(string extra)
{
    string  desc = ONE_OF_LIST( ({
        "The vaulted ceiling is several feet above your head.",
        "The vaulted ceiling is made from large black stone blocks.",
        "The large black stone slabs of the ceiling are expertly " +
            "hewn and finely polished.",
        "Large blocks of black stone form the ceiling here. They " +
            "have been put together without any mortar and they " +
            "are held together only by their own weight.",
        "The vaulted ceiling several feet above your head " +
            "is made from large black stone blocks. The stones " +
            "fit together so closely that there are hardly any " +
            "visible joints.",
        }) );

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"ceiling", "roof"}), desc + "\n");
}

varargs void
add_walls(string extra)
{
    string  desc = ONE_OF_LIST( ({
        "The walls are made from large black stone blocks.",
        "The large stone blocks which make up the walls are smoothly " +
            "hewn and polished.",
        "The walls are made of large stone blocks which fit together " +
            "so well that there are hardly any joints visible between " +
            "them.",
        "Large stone blocks hewn from black rock, fitted together so " +
            "expertly that there are hardly any joints visible.",
        }) );

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"wall", "walls"}), desc + "\n");
}

varargs void
add_stones(string extra)
{
    string  desc = ONE_OF_LIST( ({
        "The stone blocks that make up the walls and the ceiling have " +
            "been hewn from black rock.",
        "Great blocks hewn from black rock make up the walls and the " +
            "ceiling here. They have been fitted together so smoothly " +
            "that there are hardly any joints visible between them.",
        "The walls and the ceiling are made from large black stone blocks " +
            "that have been fitted together so expertly that there are " +
            "hardly any joints visible between them.",
        }) );

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"stones", "stone blocks", "joints"}), desc + "\n");
}

varargs void
add_passage(string dir, string extra)
{
    string  desc;

    desc = "A dark tunnel is going of to the " + dir + ". All one can see "
      + "of it is a dark gaping hole.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"passage", "dark passage", "tunnel"}), desc + "\n");
}

varargs void
add_c_passage(string dir, string extra)
{
    string  desc;

    desc = "The dark tunnel is continuing to the " + dir + ". One cannot "
         + "see more than a few feet in that direction, impenetrable "
         + "darkness seems to fill the passage like a black cloud.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"passage", "dark passage", "tunnel"}), desc + "\n");
}

varargs void
add_c_passages(string dir1, string dir2, string extra)
{
    string  desc;

    desc = "The dark tunnel runs from "+dir1+" to "+dir2+". In neither "
      + "direction can one see more than a few feet, impenetrable "
      + "darkness seems to fill the passages like a black cloud.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"passages", "dark passages", "tunnel"}), desc + "\n");
}

varargs void
add_archway(string dir, string extra)
{
    string  desc;

    desc = "An archway opens in the wall to the the "+dir+". Through "
         + "the opening falls some light, and you wonder what you will "
         + "find if you pass under the arch.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"arch", "archway", "opening", "door"}), desc + "\n");
}

varargs void
add_archways(string dir1, string dir2, string extra)
{
    string  desc;

    desc = "Two arches open in the walls here. One is leading to the "
         + dir1 + ", the other to the " + dir2 + ". Through the openings "
         + "falls some light, and you wonder what you will find if you "
         + "go through the archways.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"arches", "archways", "openings", "doors"}), desc + "\n");

    add_item(({"arch", "archway", "door", "opening"}), 
        "Which archway do you mean, the one to the " + dir1 + " or the " +
        "one to the " + dir2 + "?\n");
    add_item(({dir1+"ern arch", dir1+"ern archway", dir1+"ern door",
               dir1+" arch", dir1+" archway", dir1+" door"}), 
        "An opening in the wall leading to the " + dir1 + ". Faint " +
        "light is falling through it, but you cannot make out what " +
        "fate is awaiting you beyond the archway.\n");
    add_item(({dir2+"ern arch", dir2+"ern archway", dir2+"ern door",
               dir2+" arch", dir2+" archway", dir2+" door"}), 
        "An opening in the wall leading to the " + dir2 + ". Faint " +
        "light is falling through it, but you cannot make out what " +
        "fate is awaiting you beyond the archway.\n");
}

varargs void
add_down_archway(string extra)
{
    string  desc;

    desc = "You can see the top of a flight of stairs leading down "
         + "inside the dark archway.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"arch", "archway", "opening", "hole", }), desc + "\n");
    add_item(({"stairs", "flight of stairs", }), 
        "The flight of stairs inside the dark archway is leading down "
      + "towards an even lower level of these dungeons beneath Minas "
      + "Morgul. The stone steps look worn down from centuries of "
      + "frequent use.\n");
}

varargs void
add_up_archway(string extra)
{
    string  desc;

    desc = "You can see the bottom of a flight of stairs leading "
         + "up inside the dark archway.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"arch", "archway", "opening", "hole", }), desc + "\n");

    add_item(({"stairs", "flight of stairs", }), 
        "The flight of stairs inside the dark archway is leading up "
      + "towards a higher level of these dungeons beneath Minas "
      + "Morgul. The stone steps look worn down from centuries of "
      + "frequent use.\n");
}

/*
 * Code to prevent a player sneaking somewhere.
 */
void
reveal_sneak(object tp)
{
    tp->reveal_me(1);
}

int
no_sneak()
{
    int     hurt;
    object  tp = TP;

    if (!tp->query_prop(OBJ_I_HIDE))
        return 0;

    write("As you try to sneak down the stairs, you suddenly slip and "
      + "tumble down the steps into the dungeon.\n");
    hurt = tp->query_max_hp() / 20;
    hurt *= (200 - MIN(tp->query_stat(SS_DEX), 100) 
                 - MIN(tp->query_skill(SS_ACROBAT), 100));
    hurt /= 100;
    tp->heal_hp(- hurt);

    tell_room(CELLAR_DIR + "dung_2e1",
        QCNAME(tp) + " comes tumbling down the stairs.\n");

    set_alarm(0.0, 0.0, &reveal_sneak(tp));
}


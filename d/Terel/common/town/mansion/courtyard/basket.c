inherit "/std/room";

#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define WELL "/d/Terel/common/town/mansion/crt/well"

/* LEVELS: number of levels of the well, ROOMS: pathes, first=top */
#define LEVELS 5
#define ROOMS ({ MANSION + "crt/well", \
                 MANSION + "crt/level1", \
                 MANSION + "crt/level2", \
                 MANSION + "crt/level3", \
                 MANSION + "crt/level4" })
/* SCARY: the messages the player gets when reaching the levels */
#define SCARY ({"You hear a rumble...\n", \
                "You hear a rumble...\n", \
                "You hear a rumble - you feel sick...\n", \
                "You hear a rumble - you feel sick...\n", \
                "You hear a rumble - you feel very nervous...\n" })
/* LIGHTS: at what levels there's light in the basket? */
#define LIGHTS ({1,0,0,0,0})


int level; /* current level, 0=top */
string dep_room; /* for delayed arrival messages */
string dep_dir; /* dito, function parameters */
string arr_room;
string arr_dir;

/*
 * TAS: test-and-set occupied flag; actually scans content of basket
 *      for interactive players (only one allowed)
 */
int
TAS()
{
    object *op;
    int i;

    op = deep_inventory();
    for (i=0; i<sizeof(op); i++)
        if (interactive(op[i])) return 1;
    return 0;
}

/*
 * query_load: calc sum of weights except for interactive player
 */
public int
query_load()
{
    object *op,*op2;
    int i,j,sum;

    op = all_inventory();
    sum = 0;
    for (i=0; i<sizeof(op); i++)
        if (!interactive(op[i]))
            sum += op[i]->query_prop(OBJ_I_WEIGHT);
        else
        {
            op2 = all_inventory(op[i]);
            for (j=0; j<sizeof(op2); j++)
                sum += op2[j]->query_prop(OBJ_I_WEIGHT);
        }
    return sum;
}

public string
query_desc()
{
    return "This basket obviously belongs to the " +
           "well. It's hanging on a rope that leads to the " +
           "top of the well. The basket and the rope look very old, " +
           "but they still seem able to carry some weight.\n";
}

public void
notify()
{
    tell_room(this_object(), SCARY[level]);
    dep_room->notify("leaves ", dep_dir);
    arr_room->notify("arrives from ", arr_dir);
}


/* top: up one level if possible; returns 1 on success */
int
up()
{
    if (!level) return 0;
    
    dep_room = ROOMS[level];
    dep_dir = "upwards";
    remove_exit("leave");
    level--;
    add_prop(ROOM_I_LIGHT, LIGHTS[level]);
    arr_room = ROOMS[level];
    arr_dir = "below";
    set_alarm(2.0, -1.0, notify);
    add_exit(ROOMS[level], "leave", 0);
    return 1;
}

/* down: down one level if possible; returns 1 on success */
int
down()
{
    if (level + 1 >= LEVELS) return 0;
    
    dep_room = ROOMS[level];
    dep_dir = "downwards";
    remove_exit("leave");
    level++;
    add_prop(ROOM_I_LIGHT,LIGHTS[level]);
    arr_room = ROOMS[level];
    arr_dir = "above";
    set_alarm(2.0, -1.0, notify);
    add_exit(ROOMS[level], "leave", 0);
    return 1;
}

/* query_level: returns the actual level (0=top) */
int
query_level() { return level; }

public void
create_room()
{
    set_short("well basket");
    set_long("You find yourself within a huge basket hanging on " +
             "a rope in the shaft of a very deep, dark well. The basket " +
             "offers room for one person only. Unfortunately, you don't find " +
             "any way to move the basket up or down here...\n");
    add_item("rope", "It looks like an ordinary rope, just strong enough " +
        "to carry your weight.\n");
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    level = 2;
    add_exit(ROOMS[0], "leave", 0);
}

public int
pull_rope(string str)
{
    int i;
    
    notify_fail("Pull what?\n");
    if (str != "rope") return 0;
    
    for (i=0; i<=level; i++)
        ROOMS[i]->pull_notify();
    
    write("You pull the rope...\n");
    say(QCTNAME(this_player()) + " pulls the rope.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(pull_rope, "pull");
}

/*
 * pull_notify(): notify all rooms where the rope is visible, except
 * for the top room and the given exception
 */
public void
pull_notify(int exception)
{
    int i;

    for (i=1; i<=level; i++)
        if (i != exception) ROOMS[i]->pull_notify();
    tell_room(this_object(),
        "The rope just moved - probably somebody above pulled it.\n");
}

/*
 * notify_tooheavy(): notify player that somebody tried to lift him
 */
public void
notify_tooheavy()
{
    int i;

    for (i=1; i<=level; i++)
        ROOMS[i]->notify_tooheavy();
    tell_room(this_object(),
              "The rope trembles for a second, as if somebody " +
              "tried to lift you but didn't succeed because he's too " +
              "weak.\n");
}


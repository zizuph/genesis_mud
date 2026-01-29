/* 
 * The base indoor room for the Saurian Lizard Person Guild
 * Located near the Lizard People in Kalad.
 * Mirandus - February 20, 2018
 *
 * Update Log: -
 *
 *
 * This is a racial guild that allows players to become Saurians. A race
 * of subterranian Lizard People. They will get some nice perks like
 * night-vision, boost to unarmed caid, and a slight health regen. 
 * They are also weak to fire as their ice-cold blood can
 * not adapt to extreme temperatures easily.
 *
 *
 *
 *                 Saurian Guild Hall
 *
 *    
 */
#pragma strict_types

#include "../lizards.h"
inherit "/d/Kalad/room_std";
inherit GUILD_STD + "room_tell";
inherit GUILD_STD + "lizard_tells";

/* Definitions */


/* Prototypes */
public nomask void  create_room();
public void         create_std_lizard();
public void         add_lizard_items();

/*
 * This function creates the room
 */
public nomask void
create_room()
{
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);
    create_std_lizard();
    add_lizard_items();
    set_tell_time(random(400) + 90);
    add_tell("@@get_tells@@" + "\n");
    //add_prop(ROOM_S_MAP_FILE, "");
    
}
/* Function name:        create_std_lizard
 * Description  :        dummy function for inheriting rooms to mask
 */
public void
create_std_lizard()
{
    set_short("a set_short is needed here");
    set_long("A set_long is needed here.\n");
    
} 
/*
 * Function name:        add_lizard_items
 * Description  :        Adds the standard items for the road
 *
 */
public void
add_lizard_items()
{  
    
    add_item(({"walls", "wall", "the walls", "the wall"}), "The walls "
    +"of this cavernous area are hastily hewn by clawed hands. They have "
    +"been well established and, certainly a cared for, but they bear the "
    +"marks of haste and lack of skill.\n");
    add_item(({"ceiling", "ceilings", "beams", "thick wood", 
          "pieces of wood", "wood"}), "The ceiling of the area is maintained"
          +"by rough hewn beams of wood. They act as support to the roof "
          +"so that it does not collapse down upon the area.\n");
    add_item(({"floor", "floors"}), "The floors are that of an underground "
    +"area. They are cleaner than one would expect, but still covered in "
    +"dirt and small pebbles.\n");
    add_item(({"dirt","dust","pebble","small pebbles","pebbles",
    "small pebble","bone","bit of bone"}),"Small pebbles, dirt, dust, and "
    +"the occasional bit of bone are strewn about the area.\n");
    
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

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}
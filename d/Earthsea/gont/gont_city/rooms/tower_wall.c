#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

#define GATE "/d/Earthsea/gont/gont_city/rooms/landbridge"
#define DOOR "/d/Earthsea/gont/gont_city/obj/office_out"

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Inside the city wall");
    set_long("The long hallway ends here. To the "+
        "north there is a dark stone wall with a small deepset "+
        "window in it that looks out over the north entrance "+
        "to the city. To the west is a tall solid oak door.\n");
    add_item("slits",
        "The slits in the wall serve to allow light to "+
        "enter, but nothing else (such as arrows or spears).\n");
    add_item((({"stone", "black stone", "walls", "floor",
        "granite flagstones", "flagstones"})),
        "The walls and floor are made of the same dark rock as "+
        "the city walls.\n");
    add_item((({"outside", "view", "window", "deepset window"})),
        "You look through the small window that overlooks the "+
        "dragon entrance to the city.\n" + "@@dragon_gate_desc");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("tower_hall3", "south");
    clone_object(DOOR)->move(this_object(), 1);
    call_other(GATE, "load_me");
}

/*
 * Function:    query_range_targets
 *
 * Description: Returns information about adjacent rooms
 *              that you can reach with missile weapons
 *              from this room.
 *
 * Arguments:   (object) The person that wishes to fire
 *              into an adjacent room.
 *
 * Returns:     An array with the following content. If
 *              there is more then one room accessible
 *              from this room, each room pads their
 *              values to the array.
 *
 * ({ path to remote room, 
 *    matching pattern with parse_command syntax, 
 *    description of remote room,
 *    description of this room as seen from remote room 
 *  })
 *
 * Note that upon making it possible to shoot across
 * rooms, you better make your npc:s able to respond
 * to it so they won't be sitting ducks.
 *
 */
mixed 
query_range_targets(object archer)
{
   seteuid(getuid(this_object()));
   (GATE)->load_me();
   return ({    (GATE),
                "[at] [on] [the] 'gate' / 'below'",
                "at the gate",
                "on the ground at the gate" });
}

public string
dragon_gate_desc()
{
    object *folks_outside, gate;
    (GATE)->load_me();
    gate = find_object(GATE);
    string long_desc = gate->query_long(), liv_desc = long_desc;

    if(objectp(gate))
    {
        folks_outside = FILTER_LIVE(all_inventory(gate));

        if(sizeof(folks_outside))
        {
            liv_desc += "You see ";
            liv_desc += COMPOSITE_LIVE(folks_outside);
            liv_desc += " before the gate.\n";
        }
    }

    return liv_desc;
}

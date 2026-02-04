/*
 * dungeon.c
 *
 * A generic dungeon below the Legion of Darkness quarters.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "legion_room";

#include <stdproperties.h>

#define DUNG_DIR (LOD_DIR + "dungeon/");
#define KEY_FILE (DUNG_DIR + "key_file");

int aid=0;

public mixed
opposite(mixed dir)
{
    string pass_cmd;
    
    if (stringp(dir))
        pass_cmd = dir;
    else if (pointerp(dir))
    {
        if (stringp(dir[0]))
            pass_cmd = dir[0];
        else
            return 0;
    } else
        return 0;
        
    if (pass_cmd == "w" || pass_cmd == "west")
        return ({"e", "east"});
    if (pass_cmd == "e" || pass_cmd == "east")
        return ({"w", "west"});
    if (pass_cmd == "n" || pass_cmd == "north")
        return ({"s", "south"});
    if (pass_cmd == "s" || pass_cmd == "south")
        return ({"n", "north"});
    if (pass_cmd == "u" || pass_cmd == "up")
        return ({"d", "down"});
    if (pass_cmd == "d" || pass_cmd == "down")
        return ({"u", "up"});

    return 0;
}

public varargs void
add_door_exit(mixed door_name, mixed pass_cmd, string door_desc,
              string other_room, string door_id,
              int open=1, mixed lock_name=0,
              int locked=0, int pick=50, int key=0)
{
    object door1, door2;
    
    seteuid(getuid());
    
    door1 = clone_object("/std/door");
    door2 = clone_object("/std/door");
    
    door1->set_door_id(door_id);
    door2->set_door_id(door_id);
    
    door1->set_door_name(door_name);
    door2->set_door_name(door_name);
    
    if (strlen(door_desc))
    {
        door1->set_door_desc(door_desc);
        door2->set_door_desc(door_desc);
    }
    
    door1->set_pass_command(pass_cmd);
    door2->set_pass_command(opposite(pass_cmd));
    
    door1->set_other_room(other_room);
    door2->set_other_room(file_name(this_object()));
    
    door1->set_open(open);
    door2->set_open(open);
    
    if (lock_name)
    {
        door1->set_lock_name(lock_name);
        door2->set_lock_name(lock_name);
        
        door1->set_lock_command("lock");
        door2->set_lock_command("lock");
        
        door1->set_unlock_command("unlock");
        door2->set_unlock_command("unlock");
        
        if (!open)
        {
            door1->set_locked(locked);
            door2->set_locked(locked);
        }
        else
        {
            door1->set_locked(0);
            door2->set_locked(0);
        }
        
        if (pick >= 0 && pick <= 100)
        {
            door1->set_pick(pick);
            door2->set_pick(pick);
        }
        else
        {
            door1->set_no_pick();
            door2->set_no_pick();
        }
        
        if (key)
        {
            door1->set_key(key);
            door2->set_key(key);
        }
    }
    
    door1->move(this_object());
    door2->move(other_room);
}

public void
wailing()
{
    tell_room(this_object(), "You suddenly hear some faint wailing " +
              "sounds. You are not sure if it is your imagination " +
              "that is playing a trick with you or if it is real sounds " +
              "that emerge from the cells down here.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (!ob || !living(ob) || !interactive(ob) || aid) return;
    
    aid = set_alarm(itof(50+random(21)), itof(50+random(21)), wailing);
}

public void
leave_inv(object ob, object to)
{
    object *obs;
    
    ::leave_inv(ob, to);
    
    if (!ob || !living(ob) || !interactive(ob) || !aid) return;
    
    obs = all_inventory(this_object()) - ({ ob });
    
    if (sizeof(filter(obs, interactive)))
        return;
    
    remove_alarm(aid);
    aid = 0;
}

public int
get_key_code(int cell)
{    
    return (13500 + cell);
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    
    set_short("in the dungeons");
    set_long("You are standing in a dungeon below the old mansion. " +
             "The walls are wet and the air is far from fresh.\n");

    add_item(({"floor"}), "The floor is made of stones which " +
             "have been set into place with great craftmanship.\n");

    add_item(({"wall", "walls"}), "The wet stony walls have not " +
             "been touched by human hands for many years.\n");
             
    add_prop(ROOM_I_LIGHT, 0);
}

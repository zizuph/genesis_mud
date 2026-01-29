/*
 * Basic Instance Room
 *
 * Will keep track of instances of an area and make sure the player
 * remains in the instance.
 *
 * Could should perhaps be added to clean up the instance after a certain time of inactivity.
 * Not critical on current hardware though.
 *
 * Usage - Inherit this file, all files which inherit it will be part of the same instance.
 *
 * set_instance_entrance(int val) - Set to true when a room should be an entrance / exit
 *
 * - Cotillion 2011-03-24
 */
#include <macros.h>
#include <files.h>

mapping instance_rooms = ([ ]);
int     instance_entrance = 0;

/*
 * Flag this room as an entrance / exit which will not be cloned
 */
void
set_instance_entrance(int flag)
{
    instance_entrance = flag;
}

/*
 * Return or clone the room for an instance id
 */  
object
query_instance(int id)
{
    object room;

    if (instance_entrance)
        return this_object();
    
    if (instance_rooms[id])
        return instance_rooms[id];

    room = clone_object(file_name(this_object()));
    instance_rooms[id] = room;    
    
    return room;
}

/*
 * Defines the method used to assign players to instance ids.
 * Arbitrarily complex.
 */ 
int
query_instance_id(object player)
{
    return atoi(OB_NUM(player));
}

/*
 * Basically the old room loading code.
 */
object
load_room_clone(int index)
{
    mixed room_exits = this_object()->query_exit();
    mixed droom;
    string err;
    object ob;

    droom = this_object()->check_call(room_exits[index]);
    if (objectp(droom))
    {
        return droom;
    }

    ob = find_object(droom);
    if (objectp(ob))
    {
        return ob;
    }

    if (err = LOAD_ERR(droom))
    {
        SECURITY->log_loaderr(droom, environment(this_object()),
            room_exits[index + 1], this_object(), err);
        write("Err in load:" + err + " <" + droom + ">\nPlease make a bugreport about this.\n");
        return 0;
    }
    return find_object(droom);
    
}

/*
 * This is where the work is done.
 * Override standard room loading.
 */
object
load_room(int index)
{
    string file;
    object room, instance;
    function f;

    room = load_room_clone(index);
    dump_array(room);
    
    if (!objectp(room))
        return room;
    
    file = MASTER_OB(room);

    if (instance_rooms[file])
        return instance_rooms[file];

    instance = room->query_instance(query_instance_id(this_player()));

    /* If this is an ordinary exit just let the player leave */
    if (!objectp(instance))
        return room;
    
    return instance;
}

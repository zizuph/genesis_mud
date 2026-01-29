/*
 * This is the Krynn version of the Avenir SMIS placer module.
 * We want the benifits of SMIS without having to tie everything into it.
 * 
 * This got a lot more complicated than i intended, so if you see any places
 * where there is rooms for improvements let me know.
 *
 * Thanks go to Denis for creating the original.
 *
 * Cotillion, 2003-08-19
 */

#pragma strict_types
#pragma no_clone

#include <composite.h>
#include <macros.h>

string area_name,
    base_path,
    area_path,
    unit_path,
    object_path;

mapping room_group;
mixed *units, *objects;
mapping pending_objects;

/* Prototypes */
void set_area_name(string str);
void set_base_path(string path);
static void schedule_objects();
 

/* Mask this */
public void
create_placer()
{
    set_area_name("Undefined Area");
}
               
nomask void
create()
{
    setuid();
    seteuid(getuid());
    
    objects = ({ });
    units = ({ });

    room_group = ([ ]);
    pending_objects = ([ ]);
    
    set_base_path(implode(explode(MASTER, "/")[0..-2], "/") + "/");
    create_placer();
    
    set_alarm(0.0, 1800.0, &schedule_objects());
}

void
set_area_name(string str)
{
    area_name = str;
}

void
set_base_path(string path)
{
    base_path = path;

    if (!area_path)
        area_path = path;
    if (!unit_path)
        unit_path = path;    
    if (!object_path)
        object_path = path;
}

void
set_area_path(string path)
{
    area_path = path;
}

void
set_unit_path(string path)
{
    unit_path = path;
}

void
set_object_path(string path)
{
    object_path = path;
}

string
make_absolute(string base, string path)
{
    if (wildmatch("/*", path))
        return path;

    return base + path;
}

/* 
 * Group Functions 
 */
void
add_group(string id, string *str)
{
    if (!sizeof(str))
    {
        return;
    }

    room_group[id] = str;
}

string *
query_group(string id)
{
    if (room_group[id])
        return room_group[id];
    return ({ id });
}

/*
 * Unit Functions
 */
public varargs void
add_area_unit(mixed locations, string unit, int count = 1)
{
    if (stringp(locations))
        locations = ({ locations });
    
    units += ({ ({ locations, unit, count, ({ }) }) });
}

public varargs void
add_area_object(mixed locations, string obj, int count = 1)
{
    if (stringp(locations))
        locations = ({ locations });
    
    units += ({ ({ locations, obj, count, ({ }) }) });
}


/*
 * Calculation functions
 */

/*
 * Function Name: schedule_objects
 * Description  : This is called to "place" the objects in the
 *                target rooms, it doesn't really clone anything. 
 *                It does however decide what to place in all rooms. 
 */
static void
schedule_objects()
{
    int index, size, sub_index, sub_size;
    string *rooms, room;

    size = sizeof(units);
    index = -1;

    while (++index < size)
    {
        /* Expand all aliases */
        rooms = ({ });
        sub_index = sizeof(units[index][0]);
        while (sub_index--)
            rooms += query_group(units[index][0][sub_index]);
        
        if (!units[index][2])
            sub_size = sizeof(rooms);
        else
            sub_size = units[index][2];
        
        /* Pad the array */
        while (sizeof(units[index][3]) < sub_size)
            units[index][3] += ({ 0 });
        
        sub_index = -1;
        while (++sub_index < sub_size)
        {
            /* If it's set to either a string or an object this
             * item does not need to be placed */
            if (units[index][3][sub_index])
                continue;
            
            room = make_absolute(area_path, rooms[random(sizeof(rooms))]);
            units[index][3][sub_index] = room;
        }
    }
}

void
clone_objects(object room, mixed queue)
{
    object ob;
    int count, unit_index, sub_index;

    count = min(3, sizeof(queue));

    while (count--)
    {
        unit_index = queue[0][0];
        sub_index = queue[0][1];

        ob = clone_object(make_absolute(unit_path, units[unit_index][1]));
        if (!objectp(ob))
            continue;

        units[unit_index][3][sub_index] = ob;
        
        if (living(ob))
            ob->move_living(({ "north", "west", "east", "south" })[random(4)],
                room, 1, 1);
        else
            ob->move(room, 1);

        queue = queue[1..];
    }
    
    if (sizeof(queue))
        set_alarm(rnd(), 0.0, &clone_objects(room, queue));
}

/*
 * Function Name: room_reset
 * Description  : This function should be called from the rooms in the
 *                area when they wish to be reset.
 *                It will clone any pending npcs.
 */
void
room_reset(mixed room)
{
    string file;
    mixed queue;
    int units_size, sub_size;
    
    queue = ({ });
    if (objectp(room))
        file = file_name(room);
    else
        file = room;

    units_size = sizeof(units);
    
    while (units_size--)
    {
        
        sub_size = sizeof(units[units_size][3]);
        while (sub_size--)
        {
            if (!stringp(units[units_size][3][sub_size]) ||
                units[units_size][3][sub_size] != file)
                continue;

            /* Mark that this is pending clone,
             * needed to prevent things from going wrong if another 
             * reset comes quickly. */
            units[units_size][3][sub_size] = 1;
            queue += ({ ({ units_size, sub_size }) });
        }
    }

    clone_objects(room, queue);
}

/*
 * Function Name: room_created
 */
void
room_created(mixed room)
{
    room_reset(room);
}

/*
 * It's helpful if we provide some information to wizards.
 */
string
stat_object()
{
    string ret, *idx;
    int size, index, sub_index, sub_size;
    mixed tmp;

    ret = "\n\nPlacer For: " + area_name + "\n\n";

    idx = m_indexes(room_group);
    size = sizeof(idx);

    if (size)
        ret += " Placement Groups:\n";
    while (size--)
    {
        ret += sprintf("   %13s - %s\n", 
            idx[size], COMPOSITE_WORDS(room_group[idx[size]]));
    }
    ret += "\n";
    
    size = sizeof(units);
    index = -1;

    if (size)
        ret += "  Unit Placement Orders:\n";
    
    while (++index < size)
    {
        ret += sprintf("   %s (x%d)\n    Locations: %s\n", 
            make_absolute(unit_path, units[index][1]), units[index][2], 
            COMPOSITE_WORDS(units[index][0]));
        
        sub_size = sizeof(units[index][3]);
        sub_index = -1;

        while (++sub_index < sub_size)
        {
            tmp = units[index][3][sub_index];
            if (objectp(tmp))
                ret += "      " + file_name(environment(tmp)) + " (cloned)\n";
            if (stringp(tmp))
                ret += "      " + tmp + " (pending reset)\n";
            if (intp(tmp))
                ret += "       unknown (being cloned)\n";
        }
        ret += "\n\n";
    }
    
    return ret;
}

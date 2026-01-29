inherit "/std/object";

#include <stdproperties.h>
#include "../events.h"

#define ROOM_LIST (EVENTDIR + "special_obj/room_list")
#define ROOM_SIZE 1225

string *sprinkle_rooms = ({});
string sprinkle_obj = "/d/Gondor/private/events/obj/nut.c";

public void
create_object()
{
    set_name("sprinkler");
    set_short("sprinkler");
    set_long("Object sprinkler options:\n" +
      "sprinkle [here]\t\t\tAdd or remove your current room to the array.\n" +
      "sprinkle <pathname>\t\tAdd or remove a room-path to the array.\n" + 
      "sprinkle set <pathname>\t\tChange the object to <pathname>.\n" + 
      "sprinkle list\t\t\tSee the rooms in the array and the set object.\n" +
      "sprinkle clear\t\t\tClear the array of rooms.\n" +
      "sprinkle move\t\t\tMove the set object to each room in the array.\n" +
      "sprinkle random <number>\tMove the set object to a random <number>\n" +
      "\t\t\t\tof rooms in Gondor immediately.\n");
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);

    setuid();
    seteuid(getuid());
}

public void
set_sprinkle_obj(string str)
{
    sprinkle_obj = str;
}

public int
sprinkle_random(string arg)
{
    int num, index, size;
    object obj;
    string room;

    num = atoi(arg);

    if (!intp(num) ||
      num < 1 ||
      num > 500)
    {
        write("That is not a valid range. Try 'sprinkle random " +
            "<number between 0 and 500>'.\n");
        return 1;
    }
    else
    {
        index = -1;
        while(++index < num)
        {
            room = read_file(ROOM_LIST, random(ROOM_SIZE), 1);
            /* Get rid of the \n */
            size = strlen(room);
            size -= 2;
            room = extract(room, 0, size);
            write("Room: " + room + "\n");
            obj = clone_object(sprinkle_obj);
            if (!obj->move(room, 1))
            {
                write_file(EVENTLOG + "room_move.log", room + "\n");
            }
            else
            {
                write_file(EVENTLOG + "room_fail.log", "Failed to move " +
                    "item to " + room + ".\n");
            }
        }
        return 1;
    }
}

public int
comp_rooms(string room)
{
    return (member_array(room, sprinkle_rooms)); 
}

int
sprinkle_room(string str)
{
    int index, size, num;
    object room_ob;
    string room_name, opt, arg;

    if (!strlen(str) ||
      lower_case(str) == "here")
    {
        room_name = file_name(environment(this_player())) + ".c";
        if (comp_rooms(room_name) != -1)
        {
            sprinkle_rooms -= ({ room_name });
            write(room_name + " removed.\n");
            dump_array(sprinkle_rooms);
            return 1;
        }
        sprinkle_rooms += ({ room_name });
        write(room_name + " added.\n");
        return 1;
    } 
    else if (lower_case(str) == "clear")
    {
        write("Clearing array:\n");
        dump_array(sprinkle_rooms);
        sprinkle_rooms = ({});
        return 1;
    }
    else if (lower_case(str) == "move")
    {
        write("Item moved to the following rooms:\n");
        index = -1;
        size = sizeof(sprinkle_rooms);
        while(++index < size)
        {
            room_ob = find_object(sprinkle_rooms[index]);
            room_ob->teleledningsanka();
            if (objectp(room_ob))
            {
                room_ob = find_object(sprinkle_rooms[index]);
                clone_object(sprinkle_obj)->move(room_ob, 1);
                write(sprinkle_rooms[index] + "\n");
            }
            else
            {
                write("Failed to load " + sprinkle_rooms[index] + ".\n");
            }
        }
        return 1;
    }
    else if (lower_case(str) == "list")
    {
        write("List is:\n");
        dump_array(sprinkle_rooms);
        write("Object is:\n");
        write(sprinkle_obj + "\n");
        return 1;
    }

    num = sscanf(str, "%s %s", opt, arg);
    if (lower_case(opt) == "random")
    {
        sprinkle_random(arg);
        return 1;
    }
    if (num == 2)
    {
        if (lower_case(opt) == "set")
        {
            write("Object set to " + arg + ".\n");
            set_sprinkle_obj(arg);
            return 1;
        }
        notify_fail("Invalid option.\n");
        return 0;
    }
    else if (file_size(str) <= 0)
    {
        str += ".c";
        if (file_size(str) <= 0)
        {
            notify_fail("Invalid pathname.\n");
            return 0;
        }
    }

    if (comp_rooms(str) != -1)
    {
        sprinkle_rooms -= ({ str });
        write(str + " removed.\n");
        dump_array(sprinkle_rooms);
        return 1;
    }

    sprinkle_rooms += ({ str });
    write(str + " added.\n");
    return 1;
}

public void
init()
{
    ::init();

    add_action(sprinkle_room, "sprinkle");
}

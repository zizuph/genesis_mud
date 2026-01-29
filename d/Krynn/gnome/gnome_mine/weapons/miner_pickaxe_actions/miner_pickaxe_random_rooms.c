
void
create_door(object currRoom, object instances_room, string str, string id)
{
    object door;

    door = clone_object(ROOMS_DIR + "mine_instance_actions/mine_instance_dungeon_door");

    door->configure_door(str, id);
    door->set_other_room(file_name(instances_room));
    door->move(currRoom);

    door = clone_object(ROOMS_DIR + "mine_instance_actions/mine_instance_dungeon_door");

    door->configure_door(opositeDirs[str], id);
    door->set_other_room(file_name(currRoom));
    door->move(instances_room); 
}

string *
query_room_doors(object currRoom)
{
    string * dirs = ({});
    foreach (object door: currRoom->query_doors())
    {
        dirs = dirs + door->query_pass_command();
    }

    return dirs;
}

void
recursive_room_making(string str, int boundaries, int x, int y, int z, int x_dir, int y_dir, int z_dir, object master_instance_room, int length_rooms, string type)
{
    if (length_rooms == 0) {
        return;
    }

    object instances_room = 0;

    object roomExists;
    object currRoom;

    int delta_x = 0;
    int delta_y = 0;
    int delta_z = 0;

    if (dirLocsLetters[str] == "x")
    {
        delta_x = delta_x + dirLocs[str];
    }
    else if (dirLocsLetters[str] == "y")
    {
        delta_y = delta_y + dirLocs[str];
    }
    else if (dirLocsLetters[str] == "z")
    {
        delta_z = delta_z + dirLocs[str];
    }

    roomExists = master_instance_room->query_rooms(x + delta_x, y + delta_y, z + delta_z);
    currRoom = master_instance_room->query_rooms(x, y, z);

    if (roomExists == 0)
    {
        instances_room = clone_object(ROOMS_DIR + "mine_instance");

        switch (type)
        {
            case "cave":
                instances_room->query_descr_caves(instances_room, -1);
                break;
            case "dungeon":
                instances_room->query_descr_dungeons(instances_room, -1);
                break;
        }


        if (str == "down")
        {
            currRoom->add_exit(file_name(instances_room),
                str, currRoom->block_player_down);

            currRoom->add_item(({ "rock" }),
                "A big rock.\n");

            instances_room->add_item(({ "roof" }),
                "There's a hole in the roof.\n");
        }
        else if (str == "up")
        {
            instances_room->add_exit(file_name(currRoom),
                "down", instances_room->block_player_down);

            instances_room->add_item(({ "rock" }),
                "A big rock.\n");

            currRoom->add_item(({ "roof" }),
                "There's a hole in the roof.\n");
        }
        else
        {
            if (currRoom->query_dungeon_type() == "door")
            {
                //this_player()->catch_msg("debugging.\n");
                //this_player()->catch_msg(file_name(currRoom)+str + ".\n");
                //this_player()->catch_msg("debugging string Finished.\n");
                create_door(currRoom, instances_room, str, file_name(currRoom)+str);
                //this_player()->catch_msg("debugging Finished.\n");
            }
            else
            {
                currRoom->add_exit(file_name(instances_room), str, currRoom->block_player);
                instances_room->add_exit(file_name(currRoom), opositeDirs[str], instances_room->block_player);
            }
        }

        instances_room->set_master_instance_pointer(master_instance_room);

        instances_room->set_x(x + delta_x);
        instances_room->set_y(y + delta_y);
        instances_room->set_z(z + delta_z);

        master_instance_room->set_room_loc(x + delta_x, y + delta_y, z + delta_z, instances_room);


        if (random(100) < 70)
        {
            str = dirLocs_x[x_dir];
            recursive_room_making(str, boundaries, x + delta_x, y + delta_y, z + delta_z, x_dir, y_dir, z_dir, master_instance_room, length_rooms - 1, type);            
        }

        if (random(100) < 70)
        {
            str = dirLocs_y[y_dir];
            recursive_room_making(str, boundaries, x + delta_x, y + delta_y, z + delta_z, x_dir, y_dir, z_dir, master_instance_room, length_rooms - 1, type);            
        }

        if (random(100) < 70)
        {
            str = dirLocs_z[z_dir];
            recursive_room_making(str, boundaries, x + delta_x, y + delta_y, z + delta_z, x_dir, y_dir, z_dir, master_instance_room, length_rooms - 1, type);            
        }


        if (random(100) < 20)
        {
            str = opositeDirs[dirLocs_x[x_dir]];
            recursive_room_making(str, boundaries, x + delta_x, y + delta_y, z + delta_z, x_dir, y_dir, z_dir, master_instance_room, length_rooms - 1, type);            
        }

        if (random(100) < 20)
        {
            str = opositeDirs[dirLocs_y[y_dir]];
            recursive_room_making(str, boundaries, x + delta_x, y + delta_y, z + delta_z, x_dir, y_dir, z_dir, master_instance_room, length_rooms - 1, type);            
        }

        if (random(100) < 20)
        {
            str = opositeDirs[dirLocs_z[z_dir]];
            recursive_room_making(str, boundaries, x + delta_x, y + delta_y, z + delta_z, x_dir, y_dir, z_dir, master_instance_room, length_rooms - 1, type);            
        }
    }
    else
    {
/*
        this_player()->catch_msg("debugging doors.\n");
        foreach (string dirDoor: query_room_doors(currRoom))
        {
            this_player()->catch_msg(dirDoor + ".\n");
        }
        this_player()->catch_msg(str + ".\n");
        this_player()->catch_msg(member_array(str,query_room_doors(currRoom)) + ".\n");
        this_player()->catch_msg("debugging doors Finished.\n");
*/
        if (member_array(str,currRoom->query_exit()) < 0 && member_array(str,query_room_doors(currRoom)) < 0)
        {
            if (str == "down")
            {
                currRoom->add_exit(file_name(roomExists),
                    str, currRoom->block_player_down);

                currRoom->add_item(({ "rock" }),
                    "A big rock.\n");

                roomExists->add_item(({ "roof" }),
                    "There's a hole in the roof.\n");
            }
            else if (str == "up")
            {
                // since up is not present until theres a rope, we check for the roof item.
                if (!currRoom->item_id("roof"))
                {
                    roomExists->add_exit(file_name(currRoom),
                        "down", roomExists->block_player_down);

                    roomExists->add_item(({ "rock" }),
                        "A big rock.\n");

                    currRoom->add_item(({ "roof" }),
                        "There's a hole in the roof.\n");
                }
            }
            else
            {
                //NOTICE
                //if (roomExists->query_dungeon_type() == "door")
                //can go all around and make a normal path to a "hall of doors". 
                //(doesnt matter that much if it stays this way)

                currRoom->add_exit(file_name(roomExists), str, currRoom->block_player);

                roomExists->add_exit(file_name(currRoom), opositeDirs[str], roomExists->block_player);
            }
        }
    }
}

void
make_random_rooms(object instances_room, int length_rooms, string type)
{
    int boundaries = instances_room->get_boundaries();
    int x = random(boundaries * 2) - boundaries; //check border values.
    int y = random(boundaries * 2) - boundaries; //check border values.
    int z = random(boundaries); //check border values.

    int x_dir;
    int y_dir;
    int z_dir;

    string str;

    x=1;
    y=0;
    z=0;
    type="dungeon";

    this_player()->catch_msg("debugging.\n");
    this_player()->catch_msg(type + ".\n");
    this_player()->catch_msg(boundaries + ".\n");
    this_player()->catch_msg(length_rooms + ".\n");
    this_player()->catch_msg(x + "," + y + "," + z + ".\n");

    if (x >= 0) { x_dir = -1; } else { x_dir = 1; }
    if (y >= 0) { y_dir = -1; } else { y_dir = 1; }
    if (z >= (boundaries/2)) { z_dir = -1; } else { z_dir = 1; }


    object master_instance_room = instances_room;

    instances_room = clone_object(ROOMS_DIR + "mine_instance");

    switch (type)
    {
        case "cave":
            instances_room->query_descr_caves(instances_room, -1);
            break;
        case "dungeon":
            instances_room->query_descr_dungeons(instances_room, 4);
            break;
    }

    instances_room->set_master_instance_pointer(master_instance_room);

    instances_room->set_x(x);
    instances_room->set_y(y);
    instances_room->set_z(z);

    master_instance_room->set_room_loc(x, y, z, instances_room);

    str = dirLocs_x[x_dir];
    recursive_room_making(str, boundaries, x, y, z, x_dir, y_dir, z_dir, master_instance_room, length_rooms, type);            

    if (random(100) < 50)
    {
        str = dirLocs_y[y_dir];
        recursive_room_making(str, boundaries, x, y, z, x_dir, y_dir, z_dir, master_instance_room, length_rooms, type);            
    }

    if (random(100) < 50)
    {
        str = dirLocs_z[z_dir];
        recursive_room_making(str, boundaries, x, y, z, x_dir, y_dir, z_dir, master_instance_room, length_rooms, type);            
    }
}

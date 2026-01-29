static mixed window_desc;
static mapping walls = ([]);

/*************** Doors are ugly creatures! ***********************************/
 
/*
 * Function name: add_door
 * Description:   clone a door to here and set some things.
 * Arguments:     filename - the door filename
 *                otherside - the filename of the other side
 *                pass_command - list of commands to be used
 *                    put 'north' (e.g.) first
 *                open, locked - 1 if open or locked respectively
 * Returns:       the door object
 */
public object
add_door(string filename, string otherside, mixed pass_command,
    int open = 0, int locked = 0)
{
    object door;
    reset_euid();
 
    door = clone_object(filename);
    door->set_other_room(otherside);
    if (MASTER < otherside)
        door->set_door_id(MASTER + "_to_" + otherside);
    else
        door->set_door_id(otherside + "_to_" + MASTER);
    door->set_pass_command(pass_command);
    door->set_open(open);
    door->set_locked(locked);
    door->move(this_object());
    add_door_to_exits((pointerp(pass_command) ? pass_command[0] :
        pass_command));
    return door;
}
 
/******************** Windows are lovely creatures! *************************/
 
/*
 * Function name: add_window
 * Description:   add a window to the room.
 * Arguments:     filename - window file
 *                other_room - file of other side environment
 *                direction - direction, to be used as an adj
 *                desc - description in room
 * Returns:       the window object
 */
public object
add_window(string filename, string other_room, string direction,
    mixed desc = 0)
{
    object ob;
    reset_euid();
    ob = clone_object(filename);
    ob->set_other_room(other_room);
    ob->add_adj(direction);
    ob->move(this_object());
    if (desc)
        ob->set_window_desc(desc);
    return ob;
}
 
/*
 * Function name: set_window_view
 * Description:   set what to see if looking in a window
* Arguments:     des - the description, or vbfc
 */
public void
set_window_view(mixed des)
{
    window_desc = des;
}

/*
 * Function name: query_window_view
 * Description:   tell us how it looks!
 * Returns:       a string describing the view from a window.
 */
public string
query_window_view()
{
    return check_call(window_desc);
}

public varargs void
add_wall(string direction, mixed desc, string roof_file, string other_side,
    string window_file)
{
    if (window_file)
        add_window(window_file, other_side, direction);
    walls[direction] = roof_file;
    add_item(direction + " wall", desc);
}
 
public varargs void
add_entrance(string direction, mixed desc, string roof_file, string other_side,
    string door_file, int open = 0, int locked = 0)
{
    if (door_file)
        add_door(door_file, other_side, direction, open, locked);
    if (desc)
        add_item(direction + " wall", desc);
    walls[direction] = roof_file;
}
 
public string
query_roof(string direction)
{
    return walls[direction];
}

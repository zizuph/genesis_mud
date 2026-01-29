/* Filename    : /d/Genesis/new/start/dwarf/dm/std_mountain_room.c
 * Author      : Nuf
 * Description : base room for the mountain
 */

#pragma strict_types

inherit "/std/room";

/* Prototypes */
public nomask void create_room();
public void create_mountain_room();
public string * query_nearby_rooms(string verb);

/* Function name: create_mountain_room
 * Purpose      : set up a mountain room
 * Arguments    :
 * Returns      :
 */
public void
create_mountain_room()
{
}

/* Function name: create_room
 * Purpose      : set up the room
 * Arguments    :
 * Returns      :
 */
public nomask void
create_room()
{
    ::create_room();
    create_mountain_room();
}

/* Function name: query_nearby_rooms
 * Purpose      : used to establish which rooms are nearby
 *                to give echo in those when a set of defined
 *                loud commands has taken place
 * Arguments    : the command used
 * Returns      : a list of the rooms that are nearby
 */
public string *
query_nearby_rooms(string verb)
{
    string * rooms_as_files = ({ }), * nearby_rooms = ({ });
    string sx = "", sy = "", mename = "", mesx = "", mesy = "";
    int ntemp = 0, x_axis = 0, y_axis = 0, i, mex_axis = 0, mey_axis = 0;
    int dx,dy;  
    mename = file_name(this_object());

    ntemp = strlen(mename);
    mesx = extract(mename, ntemp - 5, ntemp - 4);
    mesy = extract(mename, ntemp - 2, ntemp - 1);
    sscanf(mesx, "%d", mex_axis);
    sscanf(mesy, "%d", mey_axis);

    rooms_as_files = get_dir("/d/Genesis/new/start/dwarf/dm/*.c");
    for (i=0; i < sizeof(rooms_as_files); i++)
    {
        ntemp = strlen(rooms_as_files[i]);
        sx = extract(rooms_as_files[i], ntemp - 7, ntemp - 6);
        sy = extract(rooms_as_files[i], ntemp - 4, ntemp - 3);
        sscanf(sx, "%d", x_axis);
        sscanf(sy, "%d", y_axis);
        dx = mex_axis - x_axis;
        dy = mey_axis - y_axis;
        if ((dx < 3) && (dx > -3) && (dy < 3) && (dy > -3))
        {
            nearby_rooms += ({ rooms_as_files[i] });
        }
    }
    return nearby_rooms;
}
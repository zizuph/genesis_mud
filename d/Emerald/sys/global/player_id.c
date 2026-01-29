#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types
#pragma no_shadow

#include "/d/Emerald/sys/skills.h"

#define PLAYER_ID_SAVE_DIR ("/d/Emerald/log/player_id/")

#define PLAYER_ID_SAVE_FILE(id) \
    (PLAYER_ID_SAVE_DIR + "id_save" + \
    sprintf("%04d", ((id / MAX_FILE_SIZE + 1))))

#define PLAYER_ID_SAVE_FILE_NUMBER(filename, n) \
    ((sscanf(filename, PLAYER_ID_SAVE_DIR + "id_save%d", n) == 1) || (n = -1))

#define PLAYER_ID_SAVE_FILE_LINE_NUMBER(id) (id % MAX_FILE_SIZE)

#define MAX_FILE_SIZE 2000

public int last_new_id = 0;

static void
create()
{
    int i, n, last_file_number, line_num;
    string last_file, name, next_line, last_line, *files;

    setuid();
    seteuid(getuid());

    // Save files are split up so that it isn't necessary to read through
    // a huge file every time we initialize. There are also gamedriver
    // limits on file size.
    files = get_dir(PLAYER_ID_SAVE_DIR);
    for (i = 0; i < sizeof(files); i++)
    {
        PLAYER_ID_SAVE_FILE_NUMBER(PLAYER_ID_SAVE_DIR + files[i], n);
        if ((n != -1) && (!last_file || (n > last_file_number)))
        {
            last_file = PLAYER_ID_SAVE_DIR + files[i];
            last_file_number = n;
        }
    }

    if (!last_file)
    {
        return;
    }

    // Read to the last line of the file and get the id number from it.
    // We could just save the last id in its own file, but I think it's
    // simpler to keep the save files as simple as possible, even if it's
    // a little less efficient to process here.
    line_num = 1;
    while ((next_line = read_file(last_file, line_num++, 1)) != 0)
    {
        if (strlen(next_line))
        {
            last_line = next_line;
        }
    }

    sscanf(last_line, "%d %s", last_new_id, name);
}

/*
 * Function name: create_new_player_id
 * Description:   Assign a player id to a player who does not already
 *                have one.
 * Arguments:     (object) The player to whom the id will be assigned
 * Returns:       The id number or 0 if one could not be assigned.
 */
static int
create_new_player_id(object player)
{
    if (player->query_npc())
    {
        return 0; 
    }
    int id = last_new_id + 1;
    if (!player->set_skill(SS_PLAYER_ID, id))
    {
        return 0;
    }

    last_new_id = id;

    setuid();
    seteuid(getuid());

    write_file(PLAYER_ID_SAVE_FILE(id),
               id + " " + player->query_real_name() + "\n");

    return id;
}

/*
 * Function name: query_player_id
 * Description:   Gets a unique id number (stored as a skill) for a player.
 *                If the player has not yet been assigned an id, one will
 *                be created.
 * Arguments:     (mixed) The player (object or name) whose id we want to get.
 *                        The player must be logged in.
 * Returns:       The id number or 0 if one could not be assigned
 */
public int
query_player_id(mixed player)
{
    int id;

    if (stringp(player))
    {
        player = find_player(player);
    }

    if (!player)
    {
        return 0;
    }

    id = player->query_skill(SS_PLAYER_ID);
    if (!id)
    {
        id = create_new_player_id(player);
    }

    return id;
}

public string
query_player_name_by_id(int id)
{
    string data, file, name;
    int line_id;

    file = PLAYER_ID_SAVE_FILE(id);

    setuid();
    seteuid(getuid());

    if (file_size(file) < 1)
    {
        return 0;
    }

    data = read_file(file, PLAYER_ID_SAVE_FILE_LINE_NUMBER(id), 1);

    if (!strlen(data))
    {
        return 0;
    }

    if (sscanf(data, "%d %s\n", line_id, name) != 2)
    { 
        return 0;
    }

    // sanity check
    if (id != line_id)
    {
        return 0;
    }

    return name;
}

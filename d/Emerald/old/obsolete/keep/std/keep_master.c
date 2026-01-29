#pragma strict_types
#pragma no_clone
#pragma no_shadow

#include "../keep.h"

/*
 * Variable grid. Contains the information about the grid on the form:
 * ({ ({ ({ 1, }) , ... }), ... })
 */
mixed *grid;
static string *structures = ({});

string query_keep_save_file();
void create_keep_rooms();

static void
create_keep()
{
}

static nomask void 
create()
{
    setuid();
    seteuid(getuid());

    restore_object(query_keep_save_file());

    if (!pointerp(grid))
    {
        grid = ({});
    }

    create_keep();

    create_keep_rooms();
}

static void
create_keep_rooms()
{
}

mixed *
query_grid()
{
    return secure_var(grid);
}

string *
query_structures()
{
    return secure_var(structures);
}

/*
 * Designate a particular structure as one that can be
 * built in this keep.
 */
void
add_structure(string path)
{
    structures += ({ path });
}  
  
string
query_keep_save_file()
{
    return file_name(this_object());
}

void
save_grid()
{
    setuid();
    seteuid(getuid());

    save_object(query_keep_save_file());
}

/* 
 * init_grid(int x, int y)
 * 
 * Initialize the grid, given its dimensions
 */
void init_grid(int x, int y)
{
    grid = map(allocate(y), allocate @ &constant(x));
    save_grid();
}

/*
 * int create_structure(int x, int y, mixed type)
 *
 * Adds a structure to the grid.
 * 
 * arguments:	x - The x-coordinate in the grid.
 * 		y - The y-coordinate in the grid.
 *		type - The type of the building as defined in the keep.h 
 *                     or the path to the structure
 *
 * Returns: 	0 - failure.
 * 		1 - success.
 *		more return types?
 */
int
create_structure(int x, int y, string structure)
{
    if ((y < 0) || (y >= sizeof(grid)) ||
        (x < 0) || (x >= sizeof(grid[y])))
    {
        return 0;
    }

    if (!pointerp(grid[y][x]))
    {
        grid[y][x] = ({ structure });
    }
    else
    {
        grid[y][x] += ({ structure });
    }

    save_grid();

    return 1;
}

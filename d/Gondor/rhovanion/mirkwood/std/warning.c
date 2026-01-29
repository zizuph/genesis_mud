#include "../defs.h"

int check_for_warning() 
{
    if (MIRKWOOD_MASTER->has_received_warning(this_player(), WARNING_FOREST)) 
        return 0;

    write("You hesitate a moment to enter the dark forest, for you "
        + "are certain that great danger lies within. If you decide "
        + "to enter, you might not return, so choose wisely.\n");
    MIRKWOOD_MASTER->set_received_warning(this_player(), WARNING_FOREST);
    return 1;
}

void add_forest_entrance(string path, string direction) 
{
    this_object()->add_exit(path, direction, check_for_warning, 5, 1);
}
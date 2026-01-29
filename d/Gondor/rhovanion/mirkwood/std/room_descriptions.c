#include <macros.h>

int room_random_seed = 0;

void set_room_seed(int seed)
{
    room_random_seed = seed;
}

string get_random_message(string *messages)
{
    int index = room_random_seed ? random(sizeof(messages), room_random_seed) :
        random(sizeof(messages));
    return messages[index];
}


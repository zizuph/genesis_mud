object paralyze;

int mining_alarm;
int prospect_alarm;

mixed room_id;

int mining_fatigue = -5;

#define LAVA_MAX 100

int lava = LAVA_MAX;
int mining_speed = 1;

mapping opositeDirs = (["south": "north",
                        "north": "south",
                        "west": "east",
                        "east": "west",
                        "up": "down",
                        "down": "up"
                        ]);

mapping dirLocs =       (["south": -1,
                        "north": 1,
                        "west": -1,
                        "east": 1,
                        "up": -1,
                        "down": 1
                        ]);

mapping dirLocs_x =     ([-1: "south",
                        1: "north"
                        ]);

mapping dirLocs_y =     ([-1: "west",
                        1: "east",
                        ]);

mapping dirLocs_z =     ([-1: "up",
                        1: "down"
                        ]);

mapping dirLocsLetters = (["south": "x",
                        "north": "x",
                        "west": "y",
                        "east": "y",
                        "up": "z",
                        "down": "z"
                        ]);


int
is_terrain_minable()
{
    return environment(this_player())->terrain_includes_any(TERRAIN_ROCK);
}

int
is_lava_nearby()
{
    return environment(this_player())->terrain_includes_any(TERRAIN_MELTING);
}

void
remove_flag()
{
    environment(this_player())->remove_prop("mining_entrance");
}

void
add_flag()
{
    environment(this_player())->add_prop("mining_entrance", 1);
}

int
check_flag()
{
    return environment(this_player())->query_prop("mining_entrance");
}

int
check_mining_speed()
{
    return mining_speed;
}

public int
use_pickaxe()
{
    if (lava >= 0)
    {
        lava -= check_mining_speed();
    }
    return lava;
}

public int
check_delay_in_mining()
{
    return 21 - check_mining_speed();
}

string
ore_in_room()
{
    //server creation date/time so everyone can find the same digging spots. (but they get randomized each armagedon)
    string unique_seed = SECURITY->query_start_time();
    object tp = this_player();
    string room_id = MASTER_HASH(environment(tp));

    int room_id_ascii = string_to_int(room_id);

    //unique_seed + room ID = ore in room
    return random_ore_by_value(unique_seed + room_id_ascii);
}


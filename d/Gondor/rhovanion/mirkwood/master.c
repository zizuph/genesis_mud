#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include <stdproperties.h>

inherit "/std/room";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

void load();
void save();
void delayed_save();
void movement_skill_decay();
int query_area_limit(string area, string type);
void update_timer_for_area(string area);
mapping read_map(string filename, string prefix);

mapping last_learn_time = ([ ]);
mapping data = ([]);
int delayed_alarm = -1;
int index_alarm = -1;
string *index_pending = ({ });
string *index_done = ({ });
object index_for;
mapping alarms = ([ ]);
mapping maps = ([ ]);

#define MAX_SKILL_BY_SUCCESSFULL_MOVEMENT 90
#define MAX_SKILL_BY_FAILED_MOVEMENT 30
#define SECONDS_BETWEEN_SKILL_LEARNS 300

string describe_levels(object *nests)
{
    mapping levels = ([ ]);
    foreach(object nest : nests) {
        levels[nest->query_nest_level()]++;
    }

    return sprintf("1: %d   2: %d   3: %d   4: %d   5: %d",
        levels[1], levels[2], levels[3], levels[4], levels[5]);
}

string mirkwood_statistics()
{
    string result = "Mirkwood Control Room\n"
                  + "---------------------\n\n";

    foreach(string key, mapping areadata : data["areas"])
    {
        result += sprintf("%10s - Active nests: %d out of %d (%d rooms)\n", key, sizeof(areadata["nests"]),
            query_area_limit(key, SPIDER_LIMIT_NESTS), m_sizeof(areadata["rooms"]));
        result += sprintf("             Host nests: %d out of %d\n", sizeof(areadata["hosts"]),
            query_area_limit(key, SPIDER_LIMIT_HOSTS));
        result += sprintf("             Levels %s\n", describe_levels(areadata["nests"]));
        result += "\n";
    }

    return result;
}

void create_room() 
{
    set_short("Mirkwood Master");
    set_long(mirkwood_statistics);

    load();
    set_alarm(86400.0, 86400.0, movement_skill_decay);

    if(data["areas"]) {
        foreach(string key : m_indices(data["areas"])) {
            update_timer_for_area(key);
        }
    }

    maps = ([
        "central" : read_map(MIRKWOOD_DIR + "data/central.map", 
            MIRKWOOD_CENTRAL_FOREST_DIR),
        "south" : read_map(MIRKWOOD_DIR + "data/south.map", 
            MIRKWOOD_SOUTH_FOREST_DIR),
        "north" : read_map(MIRKWOOD_DIR + "data/north.map", 
            MIRKWOOD_NORTH_FOREST_DIR)
    ]);

    add_prop(ROOM_I_NO_CLEANUP, 1);
}

void load() 
{
    if (file_size(MASTER + ".o") > 0) {
        setuid();
        seteuid(getuid());
        data = restore_map(MASTER);
    } 
}

void save() 
{
    setuid();
    seteuid(getuid());
    save_map(data, MASTER);
}

void remove_object() 
{
    save();
    ::remove_object();
}

void trigger_delayed_save() 
{
    delayed_alarm = -1;
    save();
}

void delayed_save()
{
    if (delayed_alarm != -1) return;
    delayed_alarm = set_alarm(300.0, 0.0, trigger_delayed_save);
}

/* Mirkwood Movement */
void movement_skill_decay()
{
    if (!data["movement"]) return;
    foreach(string player : m_indices(data["movement"])) {
        int current_experience = data["movement"][player]["experience"];
        if (current_experience > 0) {
            data["movement"][player]["experience"] = current_experience - 1;
        }
    }
    save();
}

int query_guild_movement_bonus(object player)
{
    return 0;
}

void set_player_movement_by_experience_skill(object player, int skill) 
{
    string player_name = player->query_real_name();
    if (!data["movement"]) data["movement"] = ([ ]);
    if (!data["movement"][player_name]) data["movement"][player_name] = ([]);
    data["movement"][player_name]["experience"] = skill;
    save();
}

int query_movement_skill(object player) 
{
    if (player->query_npc()) return 100;

    int movement_skill = query_guild_movement_bonus(player);

    string player_name = player->query_real_name();
    if (data["movement"] && data["movement"][player_name]) {
        mixed player_data = data["movement"][player_name];

        movement_skill += player_data["experience"]
            + player_data["quest"];
    }

    return MIN(100, movement_skill);
}

private int can_learn_movement(object player) {
    string player_name = player->query_real_name();
    if (!last_learn_time[player_name]) return 1;

    int diff = time() - last_learn_time[player_name];
    return (diff > SECONDS_BETWEEN_SKILL_LEARNS);
}

void learn_movement(object player, int max_skill, int chance) 
{
    if (player->query_npc()) return;
    if (!can_learn_movement(player)) return;

    string player_name = player->query_real_name();
    if (!data["movement"]) data["movement"] = ([ ]);
    if (!data["movement"][player_name]) data["movement"][player_name] = ([]);

    int current_value = data["movement"][player_name]["experience"];
    if ((random(chance) == 0) && (random(max_skill) > current_value)) {
        last_learn_time[player_name] = time();

        current_value++;
        data["movement"][player_name]["experience"] = current_value;
        delayed_save();
    }    
}

void successfull_movement(object player)
{
    learn_movement(player, MAX_SKILL_BY_SUCCESSFULL_MOVEMENT, 2);
}

void failed_movement(object player)
{
    learn_movement(player, MAX_SKILL_BY_FAILED_MOVEMENT, 4);
}

/* Enter forest warnings */
int has_received_warning(mixed player, int warning)
{
    if (!data["warnings"]) return 0;
    string player_name = objectp(player) ? player->query_real_name() : player;
    return (data["warnings"][player_name] & warning);
}

void set_received_warning(mixed player, int warning)
{
    if (!data["warnings"]) data["warnings"] = ([ ]);
    string player_name = objectp(player) ? player->query_real_name() : player;
    data["warnings"][player_name] |= warning;
    save();
}

/* Spider room indexing */
void perform_index(string area)
{
    if (!sizeof(index_pending)) {
        index_for->catch_msg("Indexing complete, found " + m_sizeof(data["areas"][area]["rooms"])
            + " spider rooms.\n");
        remove_alarm(index_alarm);
        index_alarm = -1;
        save();
        return;
    }

    string next_room = index_pending[0];
    index_done += ({ next_room });
    index_pending -= ({ next_room });

    object room = find_object(next_room);
    if (!objectp(room)) {
        catch(next_room->teleledningsanka());
        room = find_object(next_room);
        if (!objectp(room)) {
            index_for->catch_msg("Unable to load " + next_room + "\n");
            return;
        }
    }

    int chance = room->query_spider_nest_chance();
    if (chance != 0) {
        data["areas"][area]["rooms"][next_room] = chance;
    }

    foreach(string direction, string path : room->query_mirkwood_exits()) {
        if (path[0] == '/') continue;

        string new_room = room->query_movement_base_directory() + path;
        if ((member_array(new_room, index_pending) == -1) &&
            (member_array(new_room, index_done) == -1)) {
            index_pending += ({ new_room });
        }
    }
}

mixed start_index(string area, string filename) 
{
    if (index_alarm != -1) return "Indexing already in progress";

    index_pending = ({ filename });
    index_done = ({ });
    index_for = this_player();

    if (!data["areas"]) data["areas"] = ([ ]);
    if (!data["areas"][area]) data["areas"][area] = ([ ]);
    data["areas"][area]["rooms"] = ([ ]);

    index_alarm = set_alarm(0.1, 0.1, &perform_index(area));
}

string find_area_for_room(mixed room)
{
    if (objectp(room)) room = file_name(room);
    foreach(string key, mapping areadata : data["areas"])
    {
        if (member_array(room, m_indexes(areadata["rooms"])) != -1) return key;
    }
    return 0;
}

/* Controlling spawns */
void spawn_host_nest_in_area(string area)
{
    int number_of_hosts = sizeof(data["areas"][area]["hosts"]);
    if (number_of_hosts >= query_area_limit(area, SPIDER_LIMIT_HOSTS)) return;

    string *possible_rooms = m_indices(data["areas"][area]["rooms"]);
    object *loaded_rooms = filter(map(possible_rooms, find_object), objectp);

    int excluded_rooms = 0;
    foreach(object room : loaded_rooms)
    {
        if (present(MIRKWOOD_SPIDER_NEST_ID, room))
        {
            possible_rooms -= ({ file_name(room) });
            excluded_rooms++;
        }
    }

    int total_random_count = 0;
    foreach(string room : possible_rooms) 
    {
        total_random_count += data["areas"][area]["rooms"][room];
    }

    int rand = random(total_random_count);
    foreach(string room : possible_rooms) 
    {
        int roomchance = data["areas"][area]["rooms"][room];
        if (rand < roomchance) 
        {
            object roomob = find_object(room);
            if (!objectp(roomob)) {
                catch(room->teleledningsanka());
                roomob = find_object(room);
                if (!objectp(roomob)) {
                    send_debug_message("mirkwood_spider_spawn", sprintf(
                        "Failed to load room %O for host nest", room));
                    return;
                }
            }

            setuid();
            seteuid(getuid());
            object nest = clone_object(MIRKWOOD_SPIDER_DIR + "nest");

            if (!data["areas"][area]["hosts"]) data["areas"][area]["hosts"] = ({ });
            data["areas"][area]["hosts"] += ({ nest });

            nest->move(roomob);

            send_debug_message("mirkwood_spider_spawn", 
                sprintf("Spawned host nest in %O (possible rooms %d, ignored %d)",
                room, sizeof(possible_rooms), excluded_rooms));

            return;
        } 

        rand -= roomchance; 
    }
}

void check_for_host_nests(string area)
{
    if (!data["areas"][area]["hosts"]) data["areas"][area]["hosts"] = ({ });

    data["areas"][area]["hosts"] = filter(data["areas"][area]["hosts"], objectp @ environment);
    data["areas"][area]["hosts"] = filter(data["areas"][area]["hosts"], objectp);

    int number_of_hosts = sizeof(data["areas"][area]["hosts"]);
    int missing = query_area_limit(area, SPIDER_LIMIT_HOSTS) - number_of_hosts;

    if (missing > 0)
    {
        for(int i = 0; i < missing; i++)
        {
            set_alarm(1.0, 0.0, &spawn_host_nest_in_area(area));
        }
    }
}

/* Limits */
int query_area_limit(string area, string type)
{
    if (!data["areas"]) return 0;
    if (!data["areas"][area]) return 0;
    if (!data["areas"][area]["limits"]) return 0;
    return data["areas"][area]["limits"][type];
}

void set_area_limit(string area, string type, int limit)
{
    if (!data["areas"]) data["areas"] = ([ ]);
    if (!data["areas"][area]) data["areas"][area] = ([ ]);
    if (!data["areas"][area]["limits"]) data["areas"][area]["limits"] = ([ ]);
    data["areas"][area]["limits"][type] = limit;

    check_for_host_nests(area);
    update_timer_for_area(area);
}

int query_number_of_nests_in_area(string area)
{
    if (!data["areas"]) return 0;
    if (!data["areas"][area]) return 0;
    if (!data["areas"][area]["nests"]) return 0;
    return sizeof(data["areas"][area]["nests"]);
}

/* Timers */
void update_area(string area)
{
    send_debug_message("mirkwood_spider_timer", sprintf("Timer fired for %s", area));
    m_delkey(alarms, area);

    data["areas"][area]["hosts"] = filter(data["areas"][area]["hosts"], objectp);
    check_for_host_nests(area);

    int index = 0;
    foreach(object nest : data["areas"][area]["hosts"]) 
    {
        set_alarm(itof(index) * 0.1, 0.0, &nest->update_timer());
    }

    update_timer_for_area(area);
}

void update_timer_for_area(string area)
{
    float max_nests = itof(query_area_limit(area, SPIDER_LIMIT_NESTS));
    float nest_count = itof(query_number_of_nests_in_area(area));
    float time_per_update = 60.0 
        + (log(max(1.0, 1.0 + (nest_count / max_nests))) * 900.0);

    if (member_array(area, m_indexes(alarms)) != -1) 
    {
        mixed *alarmdata = get_alarm(alarms[area]);
        if (alarmdata[2] > time_per_update)
        {
            send_debug_message("mirkwood_spider_timer", 
                sprintf("Rescheduled timer for %s", area));

            remove_alarm(alarms[area]);
            alarms[area] = set_alarm(time_per_update, 0.0, &update_area(area));
        }
    } else {
        alarms[area] = set_alarm(time_per_update, 0.0, &update_area(area));
    }
}

/* Nest registration */
void nest_added(object nest)
{
    string area = find_area_for_room(environment(nest));
    if (stringp(area)) 
    {
        send_debug_message("mirkwood_spider_spawn", 
            sprintf("%O added to area %s", nest, area));

        if (!data["areas"]) data["areas"] = ([ ]);
        if (!data["areas"][area]) data["areas"][area] = ([ ]);
        if (!data["areas"][area]["nests"]) data["areas"][area]["nests"] = ({ });

        data["areas"][area]["nests"] = filter(data["areas"][area]["nests"] 
            + ({ nest }), objectp);
        update_timer_for_area(area);
        save();
    }
}

void nest_removed(object nest)
{
    string area = find_area_for_room(environment(nest));
    if (stringp(area)) 
    {
        send_debug_message("mirkwood_spider_spawn", 
            sprintf("%O removed from area %s", nest, area));

        data["areas"][area]["nests"] -= ({ nest });
        data["areas"][area]["nests"] = filter(data["areas"][area]["nests"], objectp);
        update_timer_for_area(area);
        save();
    }
}

void remove_nests_for_area(string area) 
{
    data["areas"][area]["nests"]->remove_object();
}

/* Map functions */
mapping read_map(string filename, string prefix)
{
    setuid();
    seteuid(getuid());
    string data = read_file(filename);
    string *lines = explode(data, "\n");

    string *map = ({ });
    mapping positions = ([ ]);

    foreach(string line : lines) 
    {
        if (line[0] == '/')
        {
            string file;
            int row, col;

            if(sscanf(line, "/%s:%d,%d", file, row, col) == 3) 
            {
                positions[prefix + file] = ({ row, col });
            }
        } else {
            map += ({ line });
        }
    }

    return ([ "map" : map, "positions" : positions ]);
}

int map_cmd(string args)
{
    if (!args || !strlen(args))
    {
        notify_fail("Show map of what area?\n");
        return 0;
    }

    string *parts = explode(args, " ");
    string area = parts[0];
    string *types = (sizeof(parts) > 1) ? parts[1..] : ({ "nests" });

    if (!maps[area])
    {
        notify_fail("Unknown area " + area + ".\n");
        return 0;
    }

    mapping mapdata = maps[area];
    mixed maptext = map(mapdata["map"], &explode(, ""));

    write("Showing map of " + area + " for types " + COMPOSITE_WORDS(types) + ".\n");
    foreach(string type : types) 
    {
        foreach(string filename, int *position : mapdata["positions"])
        {
            object room = find_object(filename);
            if (!objectp(room)) continue;

            string overlay = "";
            switch(type)
            {
                case "nests": 
                {
                    object nest = present(MIRKWOOD_SPIDER_NEST_ID, room);
                    if (objectp(nest)) 
                    {
                        if (objectp(nest->query_parent_nest()))
                        {
                            overlay = "x";
                        } else {
                            overlay = "X";
                        }
                    }
                    break;
                }
                case "size":
                {
                    object nest = present(MIRKWOOD_SPIDER_NEST_ID, room);
                    if (objectp(nest)) overlay = sprintf("%d", nest->query_nest_level());
                    break;
                }
                case "maxsize":
                {
                    int size = room->query_max_spider_nest_size();
                    if (size) overlay = sprintf("%d", size);
                    break;
                }
                case "players":
                case "player":
                {
                    object *players = filter(all_inventory(room), interactive);
                    if (sizeof(players)) overlay = "P";
                    break;
                }
            }

            if (stringp(overlay) && strlen(overlay))
            {
                maptext[position[0]][position[1]] = overlay;
            }
        }
    }

    write(implode(map(maptext, &implode(, "")), "\n") + "\n");
    return 1;
}

int hosts_cmd(string args)
{
    foreach(string key : m_indices(data["areas"])) 
    {
        write("Host nests for " + key + "\n");
        foreach(object host : data["areas"][key]["hosts"]) 
        {
            write(sprintf("- %O\n", environment(host)));
        }
        write("\n");
    }
    return 1;
}

void init()
{
    ::init();
    add_action(map_cmd, "map");
    add_action(map_cmd, "mmap");
    add_action(hosts_cmd, "hosts");
}

/*
 * Library for forest movement 
 */

#include "../defs.h"
#include <macros.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h";
#include <tasks.h>
#include <ss_types.h>

int movement_difficulty = 0;
string base_directory;
mapping mirkwood_exits = ([]);
string movement_type = "forest";

mapping taken_exits = ([]);
int clear_taken_exits_alarm = -1;

void set_movement_base_directory(string directory) 
{
    base_directory = directory;
}

string query_movement_base_directory()
{
    return base_directory;
}

void set_movement_type(string type) 
{
    movement_type = type;
}

string query_movement_type() 
{
    return movement_type;
}

void set_movement_difficulty(int percentage) 
{
    movement_difficulty = MAX(0, MIN(percentage, 100));
}  

int query_movement_difficulty() 
{
    return movement_difficulty;
}

void clear_taken_exits() {

    taken_exits = ([ ]);
    clear_taken_exits_alarm = -1;
}

void store_taken_exit(string direction, string file) {
    taken_exits[direction] = file;

    if (clear_taken_exits_alarm != -1) remove_alarm(clear_taken_exits_alarm);
    clear_taken_exits_alarm = set_alarm(2.0, 0.0, clear_taken_exits);
}

private string get_filename(string direction) 
{
    string filename = mirkwood_exits[direction];
    if (filename[0] == '/') return filename;
    return base_directory + mirkwood_exits[direction];
}

private object get_room(string direction) {
    string targetfile = get_filename(direction);
    
    object target = find_object(targetfile);
    if (!objectp(target)) {
        catch(targetfile->teleledningsanka());
        target = find_object(targetfile);
    }

    return target;
}

int calculate_light_difficulty()
{
    int light_level = this_object()->query_light_level_for_living(this_player());
    switch(light_level) {
        case LIGHT_DUSKDAWN: return 90;
        case LIGHT_MIDDAY: return 80;
        case LIGHT_BRIGHT: return 70;
        case LIGHT_NIGHT:
        default:
            return 100;
    }
}

int can_player_navigate_to_direction(string direction) {
    if (this_player()->query_wiz_level()) return 1;
    if (this_player()->query_npc()) return 1;
    
    object target = get_room(direction);
    if (!objectp(target)) return 0;

    // Can never navigate when it's completely dark
    int light_difficulty = calculate_light_difficulty();
    if (light_difficulty == 100) return 0;

    int difficulty = (target->query_movement_difficulty()
        + query_movement_difficulty()) / 2;

    int player_skill_difficulty = 100 
        - MIRKWOOD_MASTER->query_movement_skill(this_player());

    float task_modifier = (itof(light_difficulty) / 100.0) *
        (itof(difficulty) / 100.0) * (itof(player_skill_difficulty) / 100.0);

    int task_difficulty = TASK_SIMPLE + ftoi(task_modifier * itof(TASK_IMPOSSIBLE - TASK_SIMPLE));

    send_debug_message("mirkwood_movement", sprintf("Player %s, light difficulty: %d, "
        + "movement difficulty: %d, skill difficulty: %d, final modifier: %f, "
        + "resulting task difficulty: %d",
        this_player()->query_real_name(), light_difficulty, difficulty,
        player_skill_difficulty, task_modifier, task_difficulty));

    return this_player()->resolve_task(task_difficulty, ({ SS_LOC_SENSE, SS_AWARENESS })) > 0;
}

mixed determine_direction_chance(string direction) {
    string *directions = ({ "north", "northeast", "east", 
                            "southeast", "south", "southwest",
                            "west", "northwest", "north",
                            "northeast", "east", "southeast",
                            "south", "southwest", "west",
                            "northwest" });

    int start = 0;
    switch(direction) {
        case "northeast": start = 1; break;
        case "east" : start = 2; break;
        case "southeast" : start = 3; break;
        case "south": start = 4; break;
        case "southwest": start = 5; break;
        case "west": start = 6; break;
        case "northwest": start = 7; break;
    }

    return ([
            directions[start]     : 100, // north
            directions[start + 1] : 100, // northeast
            directions[start + 7] : 100, // northwest
            directions[start + 2] : 75,  // west
            directions[start + 6] : 75,  // east
            directions[start + 3] : 50,  // southeast
            directions[start + 5] : 50,  // southwest
            directions[start + 4] : 25   // south
        ]);
}

string determine_random_direction(string direction) {
    object target = get_room(direction);
    if (!objectp(target)) return direction;

    string target_type = target->query_movement_type();
    
    mixed possible_exits = ({ });

    // First look for rooms within the same type
    foreach(string dir : m_indices(mirkwood_exits)) {
        object possible_room = get_room(dir);        
        if (objectp(possible_room) 
            && (possible_room->query_movement_type() == target_type)) {

            possible_exits += ({ 0, dir });
        }
    }

    // If no rooms with the same type are available, select all rooms
    if (!sizeof(possible_exits)) {
        foreach(string dir : m_indices(mirkwood_exits)) {
            object possible_room = get_room(dir);        
            if (objectp(possible_room)) {
                possible_exits += ({ 0, dir });
            }
        }
    }

    // If no other rooms are available, return the original destination
    if (!sizeof(possible_exits)) return direction;

    send_debug_message("mirkwood_movement_details", sprintf("Possible exits: %O\n",
            possible_exits));

    mixed chances = determine_direction_chance(direction);
    float light_difficulty = itof(calculate_light_difficulty()) / 100.0;
    float skill_modifier = itof(MIRKWOOD_MASTER->query_movement_skill(this_player())) / 100.0;

    send_debug_message("mirkwood_movement_details", 
        sprintf("Light modifier: %f, skill modifier: %f",
                light_difficulty, skill_modifier));

    int total_random_count = 0;
    for(int i = 0; i < sizeof(possible_exits); i = i + 2) {
        object target = get_room(possible_exits[i + 1]);

        int movement_average = ftoi(itof((target->query_movement_difficulty()
            + query_movement_difficulty()) / 2) * light_difficulty);

        possible_exits[i] = movement_average + ftoi(skill_modifier * 
                            itof(chances[possible_exits[i + 1]]));

        total_random_count += possible_exits[i];
    }

    send_debug_message("mirkwood_movement_details", sprintf("Random input: %O\n", 
                       possible_exits));

    int rand = random(total_random_count);
    for(int i = 0; i < sizeof(possible_exits); i = i + 2) {
        if (rand < possible_exits[i]) return possible_exits[i + 1];
        rand -= possible_exits[i];
    }

    return possible_exits[sizeof(possible_exits) - 1];
}

string take_mirkwood_exit(string direction) 
{
    if (taken_exits[direction]) 
    {
        send_debug_message("mirkwood_movement", "Following other player");
        return taken_exits[direction];
    }
    
    string final_direction = direction;
    if (can_player_navigate_to_direction(direction)) {
        send_debug_message("mirkwood_movement", "Player successfully navigated, "
            + "increasing skill");
        MIRKWOOD_MASTER->successfull_movement(this_player());
    } else {
        final_direction = determine_random_direction(direction);
                send_debug_message("mirkwood_movement", "Player failed to navigate, "
                    + "move to " + final_direction);
        MIRKWOOD_MASTER->failed_movement(this_player());
    }

    string destination = get_filename(final_direction);
    store_taken_exit(direction, destination);
    return destination;
}

int calculate_fatigue() {
    float skill_modifier = itof(MIRKWOOD_MASTER->query_movement_skill(this_player())) / 100.0;
    return 10 - ftoi(skill_modifier * 6.0);
}

void add_mirkwood_exits(mapping exits) 
{
    mirkwood_exits = exits;
    foreach(string exit, string path : exits) {
        this_object()->add_exit(&take_mirkwood_exit(exit), exit, 0, calculate_fatigue, 1);
    }
}

mapping query_mirkwood_exits()
{
    return mirkwood_exits;
}
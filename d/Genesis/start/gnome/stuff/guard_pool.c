#pragma save_binary

#include "../gnome.h"
#include "const.h"

mapping  guards_out;
string  *free_names;

create() {
    string *names;
    string  name_list;

    seteuid(getuid());
    name_list = read_file(GUARD_NAME_FILE);
    if (name_list) {
	names = explode(name_list, "\n");
    }
    guards_out = ([ ]);
    free_names = ({ });
    if (names && sizeof(names)) {
	filter(names, "add_guard", this_object(), sizeof(names));
    }
}

void
add_guard(string guard_data, int size) {
    /*
     * guard_data is of the form : 'name f/m'
     */
    string name, gender_char;
    if (guard_data && sscanf(guard_data, "%s %s", name, gender_char) == 2) {
	guards_out[name] = ({ gender_char == "f", 0, random(GUARD_VARIANCE) });
    } else {
	guards_out[name] = ({ 0, 0, 0 });
    }
}

object
fetch_guard(int level) {
    string name;
    object guard;
    int    index;
    mixed *guard_data;

    if (!sizeof(free_names)) {
        free_names = filter(m_indexes(guards_out), "is_dead", this_object());
        if (!sizeof(free_names)) {
            return 0;
        }
    }
    index = random(sizeof(free_names));
    name = free_names[index];
    guard_data = guards_out[name];

    guard = clone_object(GUARD_OBJECT);
    guard->set_name(name);
    guard->default_config_npc(level);
    guard->set_race_name("gnome");
    if (!guard_data[0]) {
	guard->set_gender(G_MALE);
    } else {
	guard->set_gender(G_FEMALE);
    }
    guard_data[1] = guard;

    free_names = free_names[0 .. index - 1] + free_names[index + 1 .. 1000];
    return guard;
}

status
is_dead(string who) {
    return !guards_out[who][1];
}
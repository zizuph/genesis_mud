#include <stdproperties.h>
#include "../defs.h"

inherit "/std/object";

string light_information();
int light_level;

void create_object() {
    set_name("light");
    add_name("_mirkwood_debug_light");
    
    set_adj("mirkwood");
    set_short("mirkwood light");
    set_long(light_information);
    
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    
    light_level = LIGHT_DUSKDAWN;
}

int query_mirkwood_light_level() {
    return light_level;
}

string query_light_text() {
    switch(light_level) {
        case LIGHT_NIGHT: return "night";
        case LIGHT_DUSKDAWN: return "dusk/dawn";
        case LIGHT_MIDDAY: return "midday";
        case LIGHT_BRIGHT: return "bright";
        default: return "an unknown level";
    }
}

string light_information() {
    return "This nifty device controls the light level in Mirkwood " 
        + " for the one carrying the device. Currently the light for"
        + " you is set to " + query_light_text() + ". Use 'mlight'"
        + " to control it.\n";
}

int light_cmd(string args) {
    if(!args || args == "") {
        notify_fail("MLight what? increase, decrease, night, dusk, dawn, midday, bright.\n");
        return 0;
    }
    
    switch(args) {
        case "increase": {
            light_level++;
            if(light_level > LIGHT_BRIGHT) light_level = LIGHT_BRIGHT;
            break;
        }
        case "decrease": {
            light_level--;
            if(light_level < LIGHT_NIGHT) light_level = LIGHT_NIGHT;
            break;
        }
        case "night": { light_level = LIGHT_NIGHT; break; }
        case "dawn":
        case "dusk": { light_level = LIGHT_DUSKDAWN; break; }
        case "midday": { light_level = LIGHT_MIDDAY; break; }
        case "bright": { light_level = LIGHT_BRIGHT; break; }
        default: {
            notify_fail("MLight what? increase, decrease, night, dusk, dawn, midday, bright.\n");
            return 0;
        }
    }
    
    write("You set your mirkwood light level to " + query_light_text() + ".\n");
    return 1;
}

void init() {
    ::init();
    add_action(light_cmd, "mlight");
}
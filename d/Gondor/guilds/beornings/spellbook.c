#include <macros.h>

inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting";

void create_object() {
    set_name("spellbook");
    add_name("book");
    set_short("spellbook");
    set_long("This is a spellbook containing the shapeshift spell.\n");
    
    setuid();
    seteuid(getuid());
    add_spell("/d/Genesis/newmagic/spells/shapeshift");
    add_spell("/d/Genesis/newmagic/spells/dispel");
}

void enter_env(object to, object from) {
    ::enter_env(to, from);
    add_spell_object(to);
}

void leave_env(object from, object to) {
    ::leave_env(from, to);
    remove_spell_object(from);
}

string query_auto_load() {
    return MASTER + ":";
}

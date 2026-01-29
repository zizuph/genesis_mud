#include "../gnome.h"

#pragma save_binary

inherit LIB;
inherit "std/monster";

#include "citizen.c"

create_monster() { }   /* buggy std/monster? */

void
attack_alert(string attacker) {
    if (!previous_object()->is_guard() || !query_attack()) {
        seq_new("foo"); seq_addfirst("foo", ({ "kill " + attacker }) );
    }
}

status
is_guard() { return 1; }

void
queue_setup(string *cmds, mixed dest) {
    seq_new("foo");
    seq_addfirst("foo", cmds);
    move_living("foo", dest);
}
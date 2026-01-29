#pragma save_binary
#pragma strict_types
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "guild.h"

inherit "/std/shadow";

//#include "special_armour_bonus.c"
//#include "special_defence_master.c"
//#include "special_shieldblock.c"
//#include "special_stubborn_bonus.c"
#include "special_tireless.c"
//#include
private object Shield_master_target; 

void
remove_test_neidar_shadow() {
    remove_shadow();
}


int
shadow(string str) {
    object ob = find_player(str);

    if (!ob)
        return 0;

    setuid();
    seteuid(getuid());
    object shad = clone_object("/d/Ansalon/guild/dwarf/new/test_neidar_shadow");
    return shad->shadow_me(ob);
}

public object
query_shield_master_target() {
    return Shield_master_target;
}

public void
set_shield_master_target(object target) {
    Shield_master_target = target;
}
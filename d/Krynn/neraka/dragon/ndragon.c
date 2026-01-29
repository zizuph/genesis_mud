/* The green dragon the flies between Neraka and Solace */

#include "local.h"

inherit C_FILE
inherit STD_DRAGON + "the_dragon";

#include <wa_types.h>
#include <stdproperties.h>
#include <filter_funs.h>

int place;

void
create_creature()
{
    int i;
    
    place = 0;
    set_name("cyan");
    set_living_name("cyan");
    set_long("It's a large green dragon. It just stands here, perhaps you\n" +
	     "should mount it?\n");
    set_race_name("dragon");
    set_adj("green");

    for (i = 0; i < 6; i++)
      set_base_stat(i, 130 + random(80));
    
    set_alignment(-890);
    
    set_attack_unarmed(0, 90, 90, W_IMPALE, 70, "jaws");
    set_attack_unarmed(1, 90, 90, W_BLUDGEON,  60, "wing");
    set_attack_unarmed(2, 90, 90, W_SLASH,  90, "right claw");
    
    set_hitloc_unarmed(0, 100, 20, "head");
    set_hitloc_unarmed(1, 90, 60, "body");
    set_hitloc_unarmed(2, 100, 20, "tail");
    
    ::create_creature();

    add_prop(OBJ_I_NO_ATTACK, 1);
    add_prop(OBJ_S_WIZINFO,
	     "This is the famous dragon transporting people between Solace and " +
	     "Neraka. It's not meant to be update, or killed.\n");
    add_prop(CONT_I_VOLUME, 5679000);
    add_prop(CONT_I_WEIGHT, 5784000);
}

void
init_living()
{
    init_dragon();
}

void
remove_object()
{
    seteuid(getuid(TO));
    write_file("/d/Krynn/log/dragon_remove","NERAKA: " + TP->query_name() +
	       " " + ctime(time()) + ".\n");
    ::remove_object();
}

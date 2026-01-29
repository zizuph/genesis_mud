// -*-C++-*-
// creator(s): Ibun, Aug 2007
// last update: Ibun, 2007.
// bug(s):
// to-do:

#pragma strict_types
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>
#include <state_desc.h>
#include "/d/Avenir/common/common.h"

inherit "/std/monster";
 
void equip_me();

void
create_monster()
{
    set_name("thug");
    add_name("pal");
    set_adj("stinking");
    set_race_name("port thug");
    set_long("This man in saggy clothes is one of the port " +
        "thugs common in ports like this.\n");

    set_stats(({90, 100, 100, 60, 60, 90}));
    set_alignment(-1000);

    set_skill( SS_DEFENSE, 100 );
    set_skill( SS_UNARM_COMBAT, 100 );
    set_skill( SS_AWARENESS, 70 );
    set_skill( SS_HIDE, 80 );
    set_skill( SS_PICK_POCKET, 30);
    equip_me();
}


void
equip_me()
{
    object dagger;
    int i;

    clone_object(PORT + "obj/jacket")->move(this_object(), 1);
    command("wear all");
    dagger = clone_object(PORT + "obj/uw_dagger");
    dagger->move(this_object(), 1);
    command("wield all");
}


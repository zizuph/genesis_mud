/*
 * Gully Dwarf by Teth Jan 18 97
*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include "../local.h"
inherit M_FILE

inherit "/std/act/domove";
inherit "/std/act/action";

void
create_krynn_monster()
{

    set_name("dwarf");
    set_race_name("dwarf");
    set_short("gully dwarf");
    set_long("This disgusting little creature must be a gully dwarf! " +
        "It reeks of filth and garbage, and eats the very same! It is " +
        "difficult to discern any other features behind this creature's " +
        "garbage-wrapped visage.\n");
    set_adj("gully");
    set_gender(G_FEMALE);
    add_prop(NPC_I_NO_LOOKS,1);
    set_alarm(1.0,0.0,"arm_me");
    set_m_in("rummages in");
    set_m_out("rummages");

    set_stats(({5,5,20,5,5,5}));

    set_alignment(50);
    set_knight_prestige(-2);

    set_random_move(50);
    set_restrain_path(TROOM);
    set_monster_home(TROOM + "sewer6");
   
    set_act_time(4);
    add_act("emote counts to two... no... less than two!");
    add_act("emote radiates a hideous stench.");
    add_act("emote sniffles pitifully.");
    add_act("emote rummages through the excrement looking for food.");
    add_act("emote stares at you suspiciously.");
    add_act("emote squeals: Watch out for the bone man!");
}

public void
arm_me()
{
    clone_object(TOBJ + "gully_stew")->move(TO);
}


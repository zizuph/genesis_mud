/* Mice in Kendermore, Gwyneth, June 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>

inherit AC_FILE
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/act/domove";

/* Randomly clones different colour mice. */

string *colour=({"brown", "grey", "black", "white"});

void
create_creature()
{
    string *adjecs;
    set_name("this_mouse");
    set_pname("mice");
    add_name("mouse");
    add_name("animal");
    set_race_name("mouse");
    set_adj(colour[random(4)]);
    adjecs = query_adjs();
    set_short(adjecs[0] + " mouse");
    set_pshort(adjecs[0] + " mice");
    set_gender(G_NEUTER);
    set_long("A small mouse. It's probably trying to avoid the cats.\n"); 

    set_stats(({5,5,5,5,5,5}));

    set_hp(10);
    set_alignment(0);
    set_knight_prestige(0);

    NEVERKNOWN;

    add_prop(SS_HIDE, 50);
    add_prop(SS_SNEAK, 50);
    add_prop(CONT_I_WEIGHT, 250);
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(CONT_I_VOLUME, 250);
    add_prop(OBJ_I_VOLUME, 250);
    set_attack_unarmed(2, 10, 4, W_IMPALE, 80, "teeth");
    set_hitloc_unarmed(1, 4, 80, "body");
    set_hitloc_unarmed(2, 3, 10, "head");
    set_act_time(5);
    add_act("sneak east");
    add_act("sneak west");
    add_act("sneak north");
    add_act("sneak south");

    set_random_move(20);
    set_restrain_path(KROOM);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is too small to take anything!\n");
}

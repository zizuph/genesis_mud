// file name:    bicornv.c
// creator(s):   Farlong, Ilyian 
// last update:  Lilith 27 March 1997 : removed obj_m_not_get prop,
//		 so it can get gotten added.
//		 Denis, Apr'96: fixed the volume/weight.
// purpose:      Child bicorn for park area
// note: random adjectives taken from
//       Kazz's /d/Avenir/common/outpost/mon/guard.c
//       Various valuable horns are included as leftovers in the corpse
// bug(s):
// to-do:

# pragma strict_types

# include "/d/Avenir/include/paths.h"
# include "/d/Avenir/include/deities.h"
# include <const.h>
# include <wa_types.h>
# include <stdproperties.h>

# define SHU set_hitloc_unarmed

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit "/std/act/action";

/* defines for attacks */
# define A_HORN 0
# define A_RHOOF 1
# define A_LHOOF 2
# define A_BITE 3

/* defines for hitlocs */
# define H_HEAD 0
# define H_BODY 1
# define H_LEGS 2
# define H_HORN 3

string *randadj = ({"tiny","child","innocent-looking","playful",
                    "bouncy","clumsy"});

void
create_creature()
{
    set_race_name("bicorn");
    set_gender(G_MALE);
    set_adj(randadj[random(sizeof(randadj))]);
    set_long("This is a small creature that looks a bit like a " +
             "baby horse, except it has two small blue horns " +
             "protruding from it's forehead.\n");

    set_alarm(1.0, 0.0, &set_m_in("stumbles in"));
    set_alarm(1.0, 0.0, &set_m_out("stumbles"));
    set_alignment(0);

    set_stats(({30,40,30,10,10,5}));
    set_hp(query_max_hp());
    set_restrain_path(PK);
    set_random_move(1, 0);

    set_attack_unarmed(A_HORN,5,5,W_IMPALE,50,"horns");
    set_attack_unarmed(A_RHOOF,3,5,W_BLUDGEON,20,"right hoof");
    set_attack_unarmed(A_LHOOF,3,5,W_BLUDGEON,20,"left hoof");
    set_attack_unarmed(A_BITE,3,5,W_BLUDGEON,10,"teeth");

    SHU(H_HEAD, ({7,7,7,15}),25,"head");
    SHU(H_BODY,({7,7,7,15}),25,"body");
    SHU(H_LEGS,({7,7,7,15}),25,"legs");
    SHU(H_HORN,({10,10,10,50}),25,"horns");

    set_cact_time(10);
    add_cact("cry");
    add_cact("sniff");
    add_cact("scream");

    set_act_time(20);
    add_act("emote raises his head suddenly and sniffs the air.");
    add_act("bounce");
    add_act("glare happily all");
    add_act("speer all");
    add_act("kiss bicorn");

    add_leftover(PK + "obj/blue_horn","horn",2,0,0,0);

    add_prop(LIVE_I_NEVERKNOWN, 1);

    // Lets make it acceptible offering to Salilus
    add_prop(SALILUS_OFFERING, 1); 

    remove_prop(OBJ_M_NO_GET);
    add_prop(CONT_I_WEIGHT, 7500);
    add_prop(CONT_I_VOLUME, 15000);
}

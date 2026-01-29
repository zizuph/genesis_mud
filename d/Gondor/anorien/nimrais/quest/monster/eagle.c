/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/std/creature";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/common/lib/logkill.c" 
#include "/d/Gondor/defs.h"

#define A_BEAK     0
#define A_CLAWS    1

#define H_HEAD     0
#define H_BODY     1
#define H_TAIL     2
#define H_LWING    3
#define H_RWING    4
#define H_LBPAW    5
#define H_RBPAW    6

create_creature()
{
    if (!IS_CLONE) return;
    set_name("eagle");
    set_race_name("eagle");
    set_short("eagle");
    set_long("@@long_desc");
    set_adj(({ "big" }));
    set_alignment(random(200) + 100);
    set_stats(({ 54 + random(16), 60 + random(12), 48 + random(16),
      15 + random(15), 15 + random(10), 60 + random(15) }));
    set_hp(5000);
    set_gender(0);
    set_aggressive(1);
    set_skill(SS_DEFENCE, 25 + random(20));

    set_act_time(30 + random(20));
    add_act("stare");
    add_act("@@sad_look");
}

string
sad_look()
{
    if (present("egg", ENV(TO)->query_eyrie()))
        return "emote seems to be happy.";
    return "emote looks sorrowfully at the eyrie.";
}

string
long_desc()
{
    string text;
    text = "It's a big eagle. Not one of the Great Eagles, though. ";
    if (present("egg", ENV(TO)->query_eyrie()))
        text += "It is sitting on an egg in the eyrie. ";
    else
        text += "It seems to be longing for something. ";
    return BS(text + "\n");
}

public void
cr_configure()
{
    add_attack(30, 30, W_IMPALE, 70, A_BEAK);
    add_attack(20, 20, W_SLASH,  30, A_CLAWS);

    add_hitloc(({  6,  6,  6 }), 10, "head", H_HEAD);
    add_hitloc(({ 10, 10, 10 }), 20, "body", H_BODY);
    add_hitloc(({ 10, 10, 10 }), 25, "body", H_LWING);
    add_hitloc(({ 10, 10, 10 }), 25, "body", H_RWING);
    add_hitloc(({ 10, 10, 10 }),  5, "body", H_LBPAW);
    add_hitloc(({ 10, 10, 10 }),  5, "body", H_RBPAW);
    add_hitloc(({ 10, 10, 10 }), 10, "body", H_TAIL);

}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BEAK: return "beak";
    case A_CLAWS :return "claws";
    }
    return "mind"; /* should never occur */
}

query_combat_file()
{
  return "/std/combat/cplain";
}

/* Solemnian prestige */
query_knight_prestige() { return -5;}


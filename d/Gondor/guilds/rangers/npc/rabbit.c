 /*
  * /d/Gondor/guilds/rangers/npc/rabbit.c
  * Adapted from /d/Gondor/common/npc/rabbit.c
  * Used for Ranger tasks. One must find and return the rabbit to pass.
  *
  * Gwyneth, 10/10/03
  */
inherit "/std/creature";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/combat/unarmed";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

/* Define some attack and hitloc id's (only for our own benefit) */
#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2
#define A_LHPAW 3
#define A_RHPAW 4

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

void
create_creature()
{
    set_name("rabbit");
    /* Do not remove _ranger_track_bunny name, as it's needed for tasks. */
    add_name(({"animal", "creature", "_ranger_track_bunny" }));
    set_short("fluffy brown rabbit");
    set_long("A fluffy brown rabbit with large eyes and long ears, " +
        "looking quite harmless.\n");
    set_adj( ({ "fluffy", "brown", }) );
    set_race_name("rabbit");
    set_alignment(0);
    set_stats( ({ 15, 20, 15, 10, 10, 10 }) );
    set_gender(G_MALE);
    set_skill(SS_SNEAK, 50);
    set_skill(SS_HIDE,  50);
    set_m_in("hops in");
    set_m_out("leaves hopping");
    add_prop(CONT_I_WEIGHT, 4500 + random(2501));
    add_prop(CONT_I_VOLUME, TO->query_prop(CONT_I_WEIGHT) * 75 / 100);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(RANGER_I_RABBIT, 1);
    remove_prop(OBJ_M_NO_GET);
}

/*
 * Function name: cr_configure
 * Description  : Here we add attacks and hitlocations:
 *     add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
 *     add_hitloc(int *ac, int prchit, string desc, int id)
 *     *ac == ({ ac-impale, ac-slash, ac-bludgeon })
 */
public void
cr_configure()
{
    int r = random(10) + 5;

    add_attack(r, r, W_IMPALE, 30, A_BITE);
    add_attack(r, r, W_SLASH,  20, A_LPAW);
    add_attack(r, r, W_SLASH,  20, A_RPAW);
    add_attack(r, r, W_SLASH,  15, A_LHPAW);
    add_attack(r, r, W_SLASH,  15, A_RHPAW);

    add_hitloc(({ r, r, r }), 20, "head", H_HEAD);
    add_hitloc(({ r, r, r }), 50, "body", H_BODY);
    add_hitloc(({ r, r, r }), 30, "legs", H_LEGS);
}

/*
 * Function name: cr_attack_desc
 * Description  : Give description of each attack.
 * Returns      : The attack description
 */
public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:
        return "bite";
    case A_LPAW:
        return "left paw";
    case A_RPAW:
        return "right paw";
    case A_LHPAW:
        return "left hind paw";
    case A_RHPAW:
        return "right hind paw";
    default:
        return "mind"; /* should never occur */
    }
}

string
query_combat_file()
{
    return "/std/combat/cplain";
}

object
make_corpse()
{
    object corpse;

    corpse = clone_object(OBJ_DIR + "rabbit_corpse");
    corpse->add_prop(CONT_I_MAX_WEIGHT, query_prop(CONT_I_MAX_WEIGHT));
    corpse->add_prop(CONT_I_WEIGHT,     query_prop(CONT_I_WEIGHT));
    corpse->add_prop(CONT_I_MAX_VOLUME, query_prop(CONT_I_MAX_VOLUME));
    corpse->add_prop(CONT_I_VOLUME,     query_prop(CONT_I_VOLUME));

    return corpse;
}

/* Function name: start_run
 * Description  : Used recursively to make the rabbit run until
 *                it reaches a room with only one exit going back
 *                the way it came.
 * Arguments    : string dir - the next direction to go in.
 */
public void
start_run(string dir)
{
    int i, size;
    string *cmds;
    mapping opposites;

    opposites = ([ "north" : "south", "south" : "north",
                   "east" : "west", "west" : "east",
                   "northwest" : "southeast", "up" : "down",
                   "southeast" : "northwest", "down" : "up",
                   "northeast" : "southwest", "southwest" : "northeast",
                   "downhill" : "uphill", "uphill" : "downhill" ]);

    command(dir);
    cmds = environment()->query_exit_cmds();

    /* Don't go back. */
    cmds -= ({ opposites[dir] });

    /* We've run out of places to go. */
    if (!sizeof(cmds))
        command("hide");
    else
        start_run(one_of_list(cmds));
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to))
        return;

    if (!objectp(from))
        return;

    if (!query_interactive(to))
        return;

    if (to->query_prop(RANGER_I_TASK) == TRACK_TASK)
        to->add_prop(RANGER_I_RABBIT, 1);

    return;
}

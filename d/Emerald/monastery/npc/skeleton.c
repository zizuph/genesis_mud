inherit "/d/Emerald/std/emerald_monster";
inherit "/std/act/attack";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "../defs.h"

#define RSTAT(base, ran) (base + random(ran))

static int rean;

void
create_emerald_monster()
{
    set_name("skeleton");
    set_adj("animated");
    set_race_name("skeleton");
 
    set_long("The skeletal remains of some long-dead monk, foul " +
        "magic has animated the old bones.\n");

    set_stats(({ RSTAT(50, 20), RSTAT(50, 40), RSTAT(50, 30),
                 RSTAT(5, 10),  RSTAT(5, 5),   RSTAT(10, 10) }));

    set_all_attack_unarmed(30, 30);
    set_all_hitloc_unarmed(30);

    set_aggressive(100);

    add_prop(LIVE_I_UNDEAD, 15);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_SEE_INVIS, 100);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NO_GENDER_DESC, 1);

    add_prop("_live_i_no_blood", 1);
    add_prop("_live_m_no_slash", "The skeleton has no flesh, though!\n");

    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_MAGIC, 15);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_DEATH, 70);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_FIRE,  30);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_POISON, 100);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_ELECTRICITY, 30);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_ILLUSION, 100);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_COLD, 70);

    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_DEFENSE, 60);
    set_skill(SS_AWARENESS, 50);

    set_alignment(-400);

    rean = 2 + random(4);

    /* Since the skeleton's bones will reanimate on their own, we should
     * regiter the new skeleton with the clone handler.
     */
    setuid();
    seteuid(getuid());
    (MONASTERY_DIR + "clone_handler")->register(this_object(), CH_SKELETON_ID);

    set_act_time(30);
    add_act("emote slowly turns its head, seeming to survey the area " +
        "through its empty eye sockets.");
}

public object
make_corpse()
{
    object bones;

    setuid();
    seteuid(getuid());

    bones = clone_object(MONASTERY_DIR + "obj/bones");
    bones->reanimate(rean);
    return bones;
}

public void
reanimate(int times)
{
    rean = times;
}

void
notify_death(object killer)
{
    tell_room(environment(this_object()), 
        QCTNAME(this_object()) + " collapses into a pile of bones.\n",
        this_object());

    if (living(killer))
    {
        tell_object(killer, 
            "You defeated " + query_the_name(killer) + ".\n");
        tell_room(environment(this_object()),  QCTNAME(killer) + 
            " defeated " +  query_objective() + ".\n",
           ({ this_object(), killer }));
    }
}

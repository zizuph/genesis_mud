/*
 * Construction worker
 * Damaris 03/2001
 */
#pragma strict_type

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/random.h"
#include "../defs.h"

inherit STDHUMAN;

/*
 * Function name: hook_return_intro
 * Description  : Called when someone introduces to us by the
 *                add_introduced hook in the knowledge base.
 *                Defined here only to prevent the guard from
 *                introducing himself (as he's a neverknown
 *                npc with no name.)
 * Arguments    : str - lowercase name of whoever intro'd.
 * Returns      : 1.
 */
public int
hook_return_intro(string str)
{
    return 1;
}

public string
act_1()
{
    if (environment()->query_prop(ROOM_I_INSIDE))
    {
        command("emote paces around the room restlessly.");
        return "";
    }

    command("emote paces around restlessly.");
    return "";
}

public string
act_2()
{
    object *others;

    others = filter(all_inventory(environment()), &->id("worker"));
    others -= ({TO});

    if (!sizeof(others))
    {
        command("emote looks around carefully, apparently " +
            "unformfortable about being alone.");
        return "";
    }

    command("say to " + OB_NAME(others[0]) + " I think I'm going to "+
        "head to Murah's for an ale when the shift is over, " +
        "feel like coming along?");
    others[0]->command("say If you're buying, sure.");
    others[0]->command("grin");
    return "";
}

public string
act_3()
{
    object *masters,
           *others;

    masters = filter(all_inventory(environment()),
        &->is_khalakhor_blademaster());
    others = filter(all_inventory(environment()), &->id("worker"));
    others -= ({TO});

    if (!sizeof(masters))
    {
        command("say I wonder if some day I'll be good enough " +
            "with a sword to claim the title of Blademaster.");
        if (!sizeof(others))
            return "";
        else
            others->command("laugh");
        command("grumble");
        return "";
    }

    if (sizeof(masters) == 1)
    {
        masters[0]->catch_msg(QCTNAME(TO) + " stares at " +
            "you in awe and whispers: A Blademaster!\n");
        tell_room(environment(), QCTNAME(TO) + " stares at " +
            QTNAME(masters[0]) + " in awe and whispers: " +
            "A Blademaster!\n", masters);
        return "";
    }

    masters->catch_msg(QCTNAME(TO) + " stares at you in awe and " +
        "whispers: Blademasters!\n");
    tell_room(environment(), QCTNAME(TO) + " stares at " +
        COMPOSITE_LIVE(masters) + " in awe and whispers: " +
        "Blademasters!\n", masters);
    return "";
}

/*
 * Function name: create_khalakhor_human
 * Description  : Turns this object into a worker.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_human()
{
    set_name("worker");
    add_name("_samorgan_worker");
    add_name("man");
    set_adj(RANDOM_DETAILED_ADJS(TO));
    set_long("This man appears to be one of the village " +
        "construction workers. He's not a terribly formidable sight, " +
        "but the workers of SaMorgan are skilled with their hammers.\n");

    default_config_npc(40);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_WEP_CLUB, 70);

    set_alignment(200 + random(200));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_stats(({80 + random(20),
                60 + random(5),
                60 + random(10),
                60 + random(5),
                60 + random(5),
                60 + random(10)}));
    set_random_size_descs();
    clone_object(WEP + "hammer")->move(TO);
    clone_object("/d/Khalakhor/common/arm/targe")->move(TO);
    clone_object("/d/Khalakhor/common/arm/vest_leather")->move(TO);
    clone_object("/d/Khalakhor/common/arm/belt")->move(TO);
    clone_object("/d/Khalakhor/common/kilts/kilt_macdunn")->move(TO);
    clone_object("/d/Khalakhor/common/arm/bracers_hard_leather")->move(TO);
    command("wield all");
    command("wear all");
    command("lace vest");
    set_act_time(random(10) + random(10) + random(10));
    add_act("ponder");
    add_act(VBFC_ME("act_2"));
    add_act(VBFC_ME("act_3"));
    add_act("peer");
    add_act(VBFC_ME("act_4"));
 
}


public void
come_assist_me(object victim, object attacker, string where)
{
    string *rooms,
           *cmds;
    int index;

    if (query_attack())
        return;

    if (!environment(TO))
        return;

    if (where != file_name(environment(TO)))
    {
        rooms = environment(TO)->query_exit_rooms();
        cmds = environment(TO)->query_exit_cmds();

        index = member_array(where, rooms);

        if (index < 0)
            return;
    
        command(cmds[index]);
    }
    command("kill " + OB_NAME(attacker));
}
        

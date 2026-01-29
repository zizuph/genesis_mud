/* 
*   Finwe kindly allowed copy of code from Ithilien mobs.
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/
*   Modified by Meton - 2020
*/

#pragma strict_types
#pragma save_binary

#include <ss_types.h>
#include <filter_funs.h>
#include <wa_types.h>
#include "../local.h"
#include <macros.h>
#include "/sys/money.h"
#include <files.h>
inherit "/d/Kalad/std/active_monster_base.c";

void
loot_corpse()
{
   command("get all from corpse");
}

int
notify_you_killed_me(object player)
{
    set_alarm(2.0, 0.0, loot_corpse);
    if (player->query_npc())
        return 1;
    seteuid(getuid(TO));
    log_file("evilkill", player->query_name()+" ("+player->query_average_stat()+
             ") was killed by "+ TO->query_name()+" on "+ctime(time())+
             " ("+file_name(environment(TO)) + ").\n");
    return 1;
}

/* Curtesy of Gondors Ithil_monster
*  Functions: Loot corpse
*  description: Loots items and corpses in area, breaks useless items
*               and uses better items
*
*/

private void report_break_action(object ob)
{
    tell_room(environment(this_object()),
        QCTNAME(TO) + " breaks the " + ob->short() + " with a "
            + "malicious grin.\n");

}

public void
check_shields()
{
    object *shields;

    command("wear all");

    shields = filter(all_inventory(TO), &operator(==)(ARMOUR_OBJECT) @
                     &function_exists("create_object", ));
    shields = filter(shields, &operator(==)(A_SHIELD) @
                     &->query_at());
    shields = filter(shields, not @ objectp @ &->query_worn());
    shields -= ({ 0 });
    if (!sizeof(shields))
        return;
    
    report_break_action(shields[0]);
    shields[0]->remove_broken();
    command("drop " + OB_NAME(shields[0]));

    if (sizeof(shields) > 1)
        set_alarm(5.0, 0.0, check_shields);
}

public void
check_weapons(object new, object from)
{
    int     new_type = new->query_wt(),
            new_sk = query_skill(SS_WEP_FIRST + new_type),
            old_sk;
    object *old = query_weapon(-1);

    if (!sizeof(old))
    {
        command("wield all");
        if (!objectp(new->query_wielded()))
        {
            command("remove shields");
            command("wield all");
            set_alarm(5.0, 0.0, check_shields);
        }
       
        if (!objectp(new->query_wielded()))
        {
            report_break_action(new);
            new->remove_broken();
            command("drop " + OB_NAME(new));
        }
        return;
    }
    if (member_array(new, old) >= 0)
    {
        /* already wielding the new weapon -- probably
         * as a result of a brawl "disarm" expiring
         */
    return;
    }

    old_sk = query_skill(SS_WEP_FIRST + old[0]->query_wt());
    if ( (old_sk * old[0]->query_pen() * old[0]->query_hit()) >
         (new_sk * new->query_pen() * new->query_hit()) )
        old[0] = new;
    else
    {
        command("unwield " + OB_NAME(old[0]));
        command("wield " + OB_NAME(new));
        // Did we succeed in wielding the weapon?
        if (!objectp(new->query_wielded()))
        {
            command("remove shields");
            command("wield " + OB_NAME(new));
            // Did we succeed in wielding the weapon?
            if (!objectp(new->query_wielded()))
            {
                command("wield " + OB_NAME(old[0]));
                old[0] = new;
            }
            set_alarm(5.0, 0.0, check_shields);
        }
    }

    report_break_action(old[0]);
    old[0]->remove_broken();
    command("drop " + OB_NAME(old[0]));
}

public void
check_armours(object new, object from)
{
    int     new_type = new->query_at();
    object      old, *old_shields;

    /*
     * If we can wear the new armour in addition to the already worn
     * armours, all if fine. 
     */
    command("wear all");
    if (objectp(new->query_worn()))
    {
        return;
    }

    /*
     * Is the new armour better than the old one we are wearing?
     */
    if (new_type != A_SHIELD)
    {
        old = TO->query_armour(new_type);
    }
    else
    {
        // shields are a pain:
        old_shields = filter(TO->query_armour(new_type),
                     &operator(==)(A_SHIELD) @ &->query_at());
        if (sizeof(old_shields))
        {
            old = old_shields[0];
        }
    }
    if (!objectp(old))
    {

        // This might happen if we are wielding a two handed
        // weapon, discard the new armour:
    report_break_action(new);
        new->remove_broken();
        if (objectp(new))
        {
            command("drop " + OB_NAME(new));
        }
        return;
    }
            
    if (new->query_ac() <= old->query_ac())
    {
        old = new;
    }
    else
    {
        command("remove " + OB_NAME(old));
        command("wear " + OB_NAME(new));
        // Did we succeed in wielding the armour?
        if (!objectp(new->query_worn()))
        {
            command("wear " + OB_NAME(old));
            old = new;
        }
    }

    report_break_action(old);
    old->remove_broken();
    command("drop " + OB_NAME(old));
}

public void
remove_surplus(object ob)
{
    if (!objectp(ob))   /* added to fix errs in debug log -- gnad */
        return;
    if (function_exists("create_heap", ob) == COINS_OBJECT)
    {
        command("smile greedily");
        return;
    }
    if (ob->query_prop(HEAP_I_IS))
        return;
    // We do not destroy items cloned into this room:
    if (member_array(ob, environment(TO)->query_cloned_here()) > -1)
        command("drop " + OB_NAME(ob));
    else
    {
        report_break_action(ob);
        set_alarm(0.0, 0.0, &ob->remove_object());
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from))
    {
        return;
    }

    if (ob->id("corpse"))
    {
        command("get all from corpse");
        set_alarm(2.0, 0.0, &command("drop corpse"));
        return;
    }

    if (ob->query_prop(OBJ_I_BROKEN))
    {
            // Clean up and remove broken objects that we pick up!
            set_alarm(0.0, 0.0, &ob->remove_object());
        set_alarm(5.0, 0.0, &command("drop broken things"));
        return;
    }

    if (function_exists("create_object", ob) == WEAPON_OBJECT)
    {
            set_alarm(1.0, 0.0, &check_weapons(ob, from));
        return;
    }

    if (function_exists("create_object", ob) == ARMOUR_OBJECT)
    {
        set_alarm(1.0, 0.0, &check_armours(ob, from));
        return;
    }

    if ((query_encumberance_weight() > 25) ||
        (query_encumberance_volume() > 25))
    {
        set_alarm(1.0, 0.0, &remove_surplus(ob));
    }
}
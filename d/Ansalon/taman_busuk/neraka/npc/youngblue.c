/* Ashlar, 17 Aug 97
   A young blue dragon that aids in the defence of the temple
*/

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"


inherit "/d/Krynn/std/dragon_base";
inherit "/std/act/attack";

void
create_dragon_npc()
{
    set_age("young");
    set_colour("blue");
    set_gender(0);
    set_long("This is a young dragon, but no less awesome for that fact. " +
        "His blue scales ripples as he moves with a serpentlike grace, and " +
        "his claws scratch the ground as he moves.\n");

    add_prop(CONT_I_WEIGHT, 1300000);
    add_prop(CONT_I_VOLUME, 1200000);

    set_aggressive("@@check_for_attack@@");
    ::create_dragon_npc();
}

int
check_for_attack()
{
    return TP->query_prop(NERAKA_I_ATTACKED_TEMPLE);
}

void
init_living()
{
    init_attack();
    ::init_living();
}

int
test_friend(object who)
{
    if (::test_friend(who))
        return 1;

    if (who->query_guild_name_occ() == "Priests of Takhisis")
        return 1;

    if (who->id("zombie") || who->id("_templeguard_"))
        return 1;

    return 0;
}

int
test_breath_friend(object who)
{
    int j;
    object *enemy_team;
    object t;

    if (::test_friend(who))
        return 1;

    t = query_attack();
    enemy_team = ({ });

    /* is there a better way to do this? */
    while(objectp(t))
    {
    	enemy_team |= ({ t }) + t->query_team_others();
    	t = t->query_leader();
    }
    
    // find_player("ashlar")->catch_msg("DRAGON: " + sizeof(enemy_team) + " enemies.\n");

    if (member_array(who, enemy_team) >= 0)
        return 0;
    else
        return 1;
}

int
special_attack(object enemy)
{
    int attacktype;
    mixed* hitresult;
    object me, *ob, *ob2;
    int i;

    me = this_object();

    if (forced_attacktype == 0)   /* no forced special attack this turn */
        attacktype = random(5);
    else
        attacktype = forced_attacktype;

    if (attacktype == 1)
    {
        if (forced_attacktype == 0)
        {
            /* Dragon inhales air, forced next attack to be cloud breath */

            tell_room(E(TO), QCTNAME(TO)+" rises to "+POSSESSIVE(TO)+" full "+
              "height, and you hear a sharp intake of breath as "+PRONOUN(TO)+
              " rears back "+POSSESSIVE(TO)+" head...\n", TO);
            forced_attacktype = 1;
            return 1;
        }

        tell_room(E(TO), "As "+QTNAME(TO)+"'s head descends, "+breath_weapon,
          TO);

        ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
        ob2 = ob + ({ });

        /* Remove friends from breath victims */

        for (i = 0; i < sizeof(ob2); i++)
        {
            if(test_breath_friend(ob2[i]))
                ob -= ({ ob2[i] });
        }

        for (i = 0; i < sizeof(ob); i++)
        {
            penet -= penet * ob[i]->query_magic_res(res_prop) /100;
            hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);

            how_str = how[0];
            if (hitresult[0] > 0)
                how_str = how[1];
            if (hitresult[0] > 10)
                how_str = how[2];
            if (hitresult[0] > 20)
                how_str = how[3];
            if (hitresult[0] > 40)
                how_str = how[4];
            if (hitresult[0] > 60)
                how_str = how[5];

            ob[i]->catch_msg("You are "+how_str+" by the dragon breath!\n");
            tell_watcher(QCTNAME(ob[i]) + " is "+how_str+" by the dragon "+
              "breath!\n", ob[i]);

            if (ob[i]->query_hp() <= 0)
                ob[i]->do_die(me);
        }
        forced_attacktype = 0;
        return 1;
    }

    return 0;
}

int
second_life(object killer)
{
    setuid();
    seteuid(getuid());
    A_KILL_LOG("pot/npckills","Young Blue",killer);
    return 0;
}




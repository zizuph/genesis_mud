inherit "/std/object";
#include "defs.h"
#include <wa_types.h>

#define D(x) find_living("cirion")->catch_tell(x)

varargs int create_fight(string test_type = "strike",
    string guild_type = "occupational", int count = 30);

void
create_object()
{
    set_name("tester");
    set_short("monk tester");
    set_long("Type: test <strike/plexus> <occupational/layman> <number hits>\n"
        + "to get statistics on special attacks.\n");
}

int
do_test(string str)
{
    string type = "strike", guild = "occupational";
    int count = 30;

    if(strlen(str))
        sscanf(str, "%s %s %d", type, guild, count);

    notify_fail("Error in parameters.\n");
    return create_fight(type, guild, count);
}

void
init()
{
    ::init();

    add_action(do_test, "test");
}

varargs int
create_fight(string test_type = "strike", string guild_type = "occupational", int perc = 100, int count = 30)
{

    object monk_npc, enemy, where, shadow, who, ob;
    string guild_style, guild_name, str = "";
    int i, result, hit_percent, total_hits, total_pen, average_pen, stime;
    mixed arr;
    int *m_skills;

    who = this_player();
    where = environment(this_player());

    m_skills = m_indices(MONK_SKILL_CONFIG_MAPPING);

    //dump_mapping(MONK_SKILL_CONFIG_MAPPING);
    //dump_array(m_skills);

    guild_style = "fighter";
    guild_name = "monks";

    reset_euid();

    present("__testmonk" + guild_type, where)->remove_object();
    present("__testenemy", where)->remove_object();

    if(!(monk_npc = present("__testmonk" + guild_type, where)))
    {
        monk_npc = clone_object("/std/monster");
        monk_npc->set_name("monk");
        monk_npc->add_name("__testmonk" + guild_type);
        monk_npc->set_short("oreana monk");
        monk_npc->set_stats(({((100 * perc) / 100),
            ((100 * perc) / 100),
            ((100 * perc) / 100),
            ((100 * perc) / 100),
            ((100 * perc) / 100),
            ((100 * perc) / 100),
            ((100 * perc) / 100),
            ((100 * perc) / 100)
                })); // all stats are 100
        monk_npc->add_prop(LIVE_I_NEVERKNOWN, 1);

        for(i=0;i<25;i++)
            monk_npc->set_skill(i, ((100 * perc) / 100)); // all combat skills are 100


        shadow = clone_object("/d/Genesis/guilds/monks/shadow/"+guild_type+"_shadow");

        if((result = shadow->shadow_me(monk_npc, guild_type, guild_style, guild_name)) != 1)
            find_living("cirion")->catch_tell("Error setting up shadow.\n");
        else
        {
            monk_npc->init_occ_shadow();
            monk_npc->init_lay_shadow();
            monk_npc->move(where, 1);
        }

        if(guild_type == "occupational")
        {
            for(i=0;i<sizeof(m_skills);i++)
                monk_npc->set_skill(m_skills[i], MONK_SKILL_CONFIG_MAPPING[m_skills[i]][0][0] * perc / 100);
        }
        else
        {

            for(i=0;i<sizeof(m_skills);i++)
            {
                monk_npc->set_skill(m_skills[i], MONK_SKILL_CONFIG_MAPPING[m_skills[i]][1][0] * perc / 100);
                D("Setting " + m_skills[i] + ": " +  MONK_SKILL_CONFIG_MAPPING[m_skills[i]][1][0] + "\n");
            }
        }


    }

    if(!(enemy = present("__testenemy", where)))
    {
        enemy = clone_object("/std/monster");
        enemy->set_name("monster");
        enemy->add_name("__testenemy");
        enemy->set_short("big mean monster");
        enemy->set_stats(({100,100,100,100,100,100,100,100,100})); // all stats are 100
        enemy->add_prop(LIVE_I_NEVERKNOWN, 1);

        for(i=0;i<25;i++)
            enemy->set_skill(i, 100); // all combat skills are 100

        enemy->move(where, 1);

        // give the moster some decent armour
        ob = clone_object("/std/armour");
        ob->set_short("leather body armour");
        ob->set_at(A_BODY);
        ob->set_ac(20);
        ob->move(enemy, 1);

        ob = clone_object("/std/armour");
        ob->set_short("pair of leather greaves");
        ob->set_at(A_LEGS);
        ob->set_ac(20);
        ob->move(enemy, 1);

        ob = clone_object("/std/armour");
        ob->set_short("leather helmet");
        ob->set_at(A_HEAD);
        ob->set_ac(20);
        ob->move(enemy, 1);

        enemy->command("wear all");
    }

    // make them atack each other
    monk_npc->attack_object(enemy);
    enemy->attack_object(monk_npc);

    // test strike
    if(test_type == "strike")
    {    
        for(i = 0; i < count; i++)
        {
            monk_npc->heal_hp(1000000);
            enemy->heal_hp(1000000);
            monk_npc->add_fatigue(1000000);
            enemy->add_fatigue(1000000);

            arr = monk_npc->do_strike(enemy, -1, 1);
            str += sprintf("hit: %-5d pen: %-5d delay: %-5d seconds\n", arr[0], arr[1], arr[2]);
            total_hits += arr[0];
            if(arr[0] > 0)
                total_pen += arr[1];

        }

        str += "Average hits: " + (total_hits * 100 / count) + "%\n";

        if(total_hits != 0)
            str += "Average pen:  " + (total_pen / total_hits) + "\n";

    }
    else // else plexus
    {    
        for(i = 0; i < count; i++)
        {
            stime = 0;

            monk_npc->heal_hp(1000000);
            enemy->heal_hp(1000000);
            monk_npc->add_fatigue(1000000);
            enemy->add_fatigue(1000000);

            arr = monk_npc->do_plexus(enemy, 1);

            stime = arr[1];
            if(stime < 0)
                stime = 0;

            str += sprintf("hit: %-5d stun: %-5d delay: %-5d seconds\n", arr[0], stime, arr[2]);
            total_hits += arr[0];
            if(arr[0] > 0)
                total_pen += stime;

        }


        str += "Average hits: " + (total_hits * 100 / count) + "%\n";

        if(total_hits != 0)
            str += "Average stun time:  " + (total_pen / total_hits) + "\n";
    }

    // make them atack each other
    monk_npc->stop_fight(enemy);
    enemy->stop_fight(monk_npc);


    who->catch_tell(str);

    return 1;
}


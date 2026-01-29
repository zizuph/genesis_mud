inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <filter_funs.h>
#include <stdproperties.h>

#define ORIGINAL_SOURCE "black_reaver_armour"

#define DO_DAMAGE(x) if (random(poisonee->query_stat(SS_CON)) <= strength) x
#define LOG(x) \
    setuid(); \
    seteuid(getuid()); \
    log_file("reaver_disease", ctime(time())[4..15] + " " + \
    poisonee->query_name() + " " + x + ".\n")
                
static int incubating = 0;
static mapping infection_map = ([]);

void
create_poison_effect()
{
    add_name("reaver_disease");
    set_interval(120);
    set_poison_type("disease");
}

void
timeout()
{
    ::timeout();
}

void
start_poison()
{
    set_silent(2);
    ::start_poison();
    set_silent(1);
}

void
end_incubation()
{
    incubating = 0;
    tell_object(poisonee, "You are starting to feel sick.\n");
}

void
incubate_disease()
{
    set_alarm(rnd() * 500.0 + 200.0,0.0, end_incubation);
    incubating = 1;
}

public void
clean_infection_map()
{
    mixed *indices = m_indices(infection_map);
    int i, j, cutoff, *times;

    for (i = 0; i < sizeof(indices); i++)
    {
        if (!objectp(indices[i]) || 
            !pointerp(times = infection_map[indices[i]]))
	{
            infection_map = m_delete(infection_map, indices[i]);
	}
        else
	{
            cutoff = time() - 60 * 30;
            for (j = 0; j < sizeof(times); j++)
	    {
                if (times[j] > cutoff)
		{
                    times = times[j..];
		}
	    }

            if (!sizeof(times))
	    {
                infection_map = m_delete(infection_map, indices[i]);
	    }
            else
	    {
                infection_map[indices[i]] = times;
	    }
	}
    }
}

public void
spread_disease(object who)
{
    object disease;

    setuid();
    seteuid(getuid());

    disease = clone_object(MASTER);
    if (!(disease->infect(who, poisonee)))
    {
        disease->remove_object();
    }
}

public void
try_to_infect(object who)
{
    if (!pointerp(infection_map[who]))
    {
        infection_map[who] = ({ time() });
        return;
    }

    if (sizeof(infection_map[who]) > 8)
    {
        spread_disease(who);
        infection_map = m_delete(infection_map, who);
        return;
    }
        
    infection_map[who] += ({ time() });
}

int
special_damage(int *dam, int i)
{
    clean_infection_map();
    for_each(FILTER_LIVE(all_inventory(environment(poisonee)) - 
        ({ poisonee })), try_to_infect);

    if (incubating)
    {
        return i + 7;
    }

    set_this_player(find_player("shiva"));
    dump_array(dam);

    if (random(3) && (poisonee->query_appearance() > 0))
    {
        poisonee->set_appearance(poisonee->query_appearance() - 1);
    }

    i++;
    DO_DAMAGE(poisonee->add_fatigue(-random(dam[i])));
    i++;
    DO_DAMAGE(poisonee->heal_hp(-random(dam[i])));
    i++;
    DO_DAMAGE(poisonee->add_mana(-random(dam[i])));
    i++;
    DO_DAMAGE(poisonee->add_tmp_stat(SS_STR, -dam[i],
        ftoi(p_time * rnd())));
    i++;
    DO_DAMAGE(poisonee->add_tmp_stat(SS_DEX, -dam[i],
        ftoi(p_time * rnd())));
    i++;
    DO_DAMAGE(poisonee->add_tmp_stat(SS_CON, -dam[i],
        ftoi(p_time * rnd())));

    poisonee->catch_tell("A wave of pain hits you, and you barely " +
        "resist the urge to cry out in agony.\n");

    dump_array(i);

    return ++i;
}

int
racial_resistance(object who)
{
    int res = who->query_prop(LIVE_I_UNDEAD);
    return who->query_prop(LIVE_I_UNDEAD) +
        ([ "elf"    : 80,
           "dwarf"  : 90,
           "human"  : 40,
           "goblin" : 20,
	   "gnome"  : 30,
           "hobbit" : 40,
        ])[who->query_race()];
}

varargs int
infect(object who, object src)
{
    if (present("reaver_disease", who))
    {
        return 0;
    }

    if (!src->id(ORIGINAL_SOURCE) && (who->query_average_stat() < 30))
    {
        return 0;
    }
 
    if (who->query_wiz_level())
    {
        return 0;
    }

    /* People who had it once this reboot won't get it again. */
    if (who->query_prop("_live_i_contracted_reaver_disease"))
    {
        return 0;
    }

    if (who->resolve_task(TASK_FORMIDABLE,
        ({ TS_CON, &racial_resistance(who) })) > 0)
    {
        if (!who->query_npc())
	{
            LOG(" resisted");
	}

        return 0;
    }

    move(who, 1);

    if (src->id(ORIGINAL_SOURCE))
    {
        /* The disease is especiall nasty for those who contract it
         * from the original source.
         */
    	set_time(3200 + random(1800));
    	set_damage(({ POISON_USER_DEF, 
    		      40 + random(10),
    		      100 + random(50),
   		      30 + random(30),
                      3,
                      3,
                      3, }));

        set_strength(80 + random(20));
    }
    else
    {
    	set_time(1300 + random(1800));
    	set_damage(({ POISON_USER_DEF, 
    		      20 + random(20),
    		      40 + random(50),
   		      20 + random(30),
                      1,
                      1,
                      1, }));

        set_strength(50 + random(20));
    }

    incubating = 1;
    start_poison();

    if (who->query_prop(LIVE_I_UNDEAD))
    {
        LOG(" is an immune carrier");
        return 1;
    }

    if (who->query_npc())
    {
        return 1;
    }

    LOG("is infected");

    incubate_disease();

    return 1;
}

public void
kill_player()
{
    LOG("died");
    ::kill_player();
}

void
remove_object()
{
    poisonee->add_prop("_live_i_contracted_reaver_disease");
    ::remove_object();
}

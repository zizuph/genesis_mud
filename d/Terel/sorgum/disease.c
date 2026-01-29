/*
 * virus object
 */
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

static void set_infect_percent(int p);
static void set_damage(int d);
static void set_time(int t, int i);
static void set_target_msgs(string *tar_msgs);
static void set_other_msgs(string *other_msgs);

static int     infect_percent, damage, lasts, interval;
static string  *tar_msgs, *other_msgs;
static mapping all_players;

public void
create_disease()
{
    /* how much percent to infect others */
    set_infect_percent(5); 
    /* how much damage all in all after disease is over */
    set_damage(300);
    /* how long will it last and how long is one interval,
       damage is distributed among this time */
    set_time(100, 10);          
    /* all messages to target while ill (no prefix) */
    set_target_msgs(({
	"You begin to feel a little bit sick.\n",
	"Your skin gets hotter and hotter.\n",
	"It seems you have been sickened, it's a kind of fever.\n",
	"But now the fever seems leave.\n",
	"You feel much better.\n"
	}));
    /* all messages to other people while ill (prefix will be targets name) */
    set_other_msgs(({
	" looks a little bit ill.\n",
	" gets a red face, like blushing.\n",
	" seems to fight with fever.\n",
	"'s fever seems to leave.\n",
	" looks healthy again.\n"
	}));
}

public nomask void
create()
{
    create_disease();
    all_players = ([ ]);
}

/*
 * Function name: set_damage(int d)
 * Description:   set the damage inflicted by disease
 * Arguments:     d - the damage
 * Returns:       nothing
 */
static void
set_damage(int d)
{
    damage = d;
}

/*
 * Function name: set_infect_percent(int p)
 * Description:   how much percent that other will get infected?
 * Arguments:     p - the percent
 * Returns:       nothing
 */
static void
set_infect_percent(int p)
{
    infect_percent = p;
}

/*
 * Function name: set_time(int t, int i)
 * Description:   how long does disease lasts
 * Arguments:     t - time
 *                i = interval
 * Returns:       nothing
 */
static void
set_time(int t, int i)
{
    lasts = t;
    interval = i;
}

/*
 * Function name: set_target_msgs(string *s)
 * Description:   all messages printed to target while he/she is ill
 * Arguments:     s - a string array with messages
 * Returns:       nothing
 */
static void
set_target_msgs(string *s)
{
    tar_msgs = s;
}

/*
 * Function name: set_other_msgs(string *o)
 * Description:   all messages printed to others while target is ill
 * Arguments:     o - a string array with messages (targets name will be
 *                    the prefix automatically
 * Returns:       nothing
 */
static void
set_other_msgs(string *o)
{
    other_msgs = o;
}

/*
 * Function name: stop_epidemic(object player)
 * Description:   called to remove a virus (never rename the function)
 * Arguments:     player - the player who is now healed
 * Returns:       1 if sucessful
 */
public int
stop_epidemic(object player)
{
    if (!all_players[player])
	return 0;
    
    player->catch_msg("You feel healthy again.\n");
    all_players[player] = 0;
    player->add_prop("_"+MASTER, time() + 120); /* immunity 2 minutes */
    return 1;
}

/*
 * Function name: add_player(object p)
 * Description:   makes a player ill if he's not
 * Arguments:     p - the player
 * Returns:       1 if successful, 0 if he cannot become ill (again?)
 */
public int
add_player(object p)
{
    if (!p || p->query_ghost() || all_players[p] ||
	p->query_prop("_"+MASTER) > time())
	return 0;
    all_players[p] = 1;
    set_alarmv(itof(interval), -1.0, "do_disease", ({ p, 0, 0, 0 }));
    return 1;
}

/*
 * Function name: query_player_ill(object p)
 * Description:   check if player is ill
 * Arguments:     p - the player
 * Returns:       1 if player is ill, 0 else
 */
public int
query_player_ill(object p)
{
    return all_players[p];
}

/*
 * Function name: extra_effect(object p, int c)
 * Description:   could produce an extra effect
 * Arguments:     p - player
 *                c - intervall counter
 * Returns:       nothing
 */
public void
extra_effect(object p, int c)
{
}

/*
 * Function name: infection(object p)
 * Description:   infect others around ill player
 * Arguments:     p - the ill player
 * Returns:       nothing
 */
static void
infection(object p)
{
    int    i, sz;
    object c, *all;
    
    all = all_inventory(environment(p)) - ({ p });
    
    for (i=0, sz=sizeof(all); i<sz; i++)
	if ((c = all[i]) && living(c) && random(100) < infect_percent)
	    set_alarmv(0.0, -1.0, "add_player", ({c}));
}

/*
 * Function name: do_disease(mixed arg)
 * Description:   handle the disease
 * Arguments:     arg - ({ the ill player-object, the counter,
 *                         tar_msg count, other_msg count })
 * Returns:       nothing
 */
static void
do_disease(mixed arg)
{
    int    i, c, m, n;
    object p;
    
    p = arg[0];
    if (!p || !living(p) || p->query_ghost())
    {
	all_players[p] = 0;
	return;
    }

    if (!all_players[p])
	return;
    
    c = arg[1];
    m = arg[2];
    n = arg[3];
    
    if (m >= 0)
    {
	m -= lasts / sizeof(tar_msgs);
	p->catch_msg(tar_msgs[interval * sizeof(tar_msgs) * c / lasts]);
    }
    if (n >= 0)
    {
	n -= lasts / sizeof(other_msgs);
	tell_room(environment(p), QCTNAME(p) +
		  other_msgs[interval * sizeof(other_msgs) * c / lasts], p);
    }
    m += interval;
    n += interval;

    extra_effect(p, c);
    
    if (p->query_ghost() ||
	p->check_death(damage * interval / lasts, this_object(), 0) == 1)
    {
	/* dead */
	all_players[p] = 0;
	return;
    }
    
    if (infect_percent > 0) infection(p);
    
    c++;
    if (c * interval >= lasts)
    {
	all_players[p] = 0;
	return;
    }
    set_alarmv(itof(interval), -1.0, "do_disease", ({ p, c, m, n }));
}

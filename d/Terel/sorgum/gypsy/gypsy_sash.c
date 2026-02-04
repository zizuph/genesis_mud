/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * gypsy_sash.c
 *
 * Gypsy guild object
 */

#include "/d/Terel/include/Terel.h"
inherit "/std/armour";

#include "/d/Terel/sorgum/gypsy/gypsy_defs.h"

#include "/sys/wa_types.h"
#include "/sys/ss_types.h"

int inited;

varargs void
initialize(object player, string str)
{
    object room;
    
    inited = 1;

    /*
     * Destroy the sash if it is held by a non-guild member.
     */
    
    if (player->query_guild_name_occ() != GUILD_NAME) {
	room = ETO;
	while (!room->query_prop(ROOM_I_IS))
	    room = ENV(room);
	player->catch_msg("The " + query_short() + " disintegrates!\n");
	set_alarm(0.0, 0.0, "remove_object");
	return;
    }

    player->add_cmdsoul(GUILD_SOUL);
    player->update_hooks();
}

/*
 * Function name: query_value
 * Description:   What's the value of this armour
 */
public int
query_value()
{
    return 0;
}

/*
 * Function name: create_armour
 * Description:   Reset the armour
 */
public void
create_armour()
{
    set_name("sash");
    set_short("fancy shash");
    set_adj(({"black"}));
    set_long("Its a fancy sash.\n");

    set_af(TO);    
    set_ac(1);
    set_at(A_WAIST);

    FIX_EUID;
}


public int
query_gypsy_rank()
{
    object player;

    player = ETO;

    if (MEMBER(player))
        return player->query_gypsy_rank();
    else
        return 0;
}

/*
 * Function name: query_auto_load
 * Description:   Make this object autoloading
 * Returns:       The filename of this object and other data
 */

public string
query_auto_load()
{
    return MASTER + ":" + "#gr#" + query_gypsy_rank() + "#";
}

mixed
wear(object ob)
{
    if (ob != TO)
        return -1;

    if (MEMBER(TP)) {
        write("You wear the " + query_short() + " around your waist.\n" +
              "The power of the gypsy gods coarses through you.\n");
        
        say(QCTNAME(TP) + " wears " + LANG_ASHORT(TO) + ".\n");
        return 1;
    }
    else {
        return "You lose!\n";
    }
    
}

void
init_arg(string str)
{
    if (!inited)
        set_alarm(0.0, 0.0, "initialize", TP, str);
}

void
init()
{
    ::init();
    add_action("join", "join");
        
}

string
query_recover()
{
    return 0;
}


/*
 * shadow join from /cmd/live/social.c
 */

public int
join(string name)
{
    object leader;
    object *potential_team;
    int i;
    int gypsies = 0;

    TP->catch_msg("obj join called in you!\n");

    if (!name) 
        return 0;

    if (TP->query_leader())
    {
 	write("You already have a leader!\n");
	return 1;
    }

    if (!this_player()->query_met(name))
    {
	write("You don't know anyone called '" + capitalize(name) + "'.\n");
	return 1;
    }

    leader = present(name, environment(this_player()));

    if (!leader || !leader->check_seen(this_player()))
    {
	write("You don't see " + capitalize(name) + " here.\n");
	return 1;
    }

    /*
     * Can not have a leader with too low DIS
     */
    if (leader->query_stat(SS_DIS) + 10 < this_player()->query_stat(SS_DIS) &&
		!this_player()->query_wiz_level())
    {
	write("You do not have enough faith in " + 
	      LANG_POSS(leader->short()) + " discipline.\n");
	return 1;
    }

    if (MEMBER(leader) == 0) {
	potential_team = leader->query_team();
	
	for (i = 0; i < sizeof(potential_team); i++)
	    if (MEMBER(potential_team[i]))
		++gypsies;

        write("Nay, there are not enough of your kind in that team.\n");
	if ((sizeof(potential_team) - gypsies) > gypsies) 
	    return 1;
    }

    if (leader->team_join(this_player()))
    {
	write("Your leader is now: " + leader->short() + ".\n");
	say(QCTNAME(this_player()) + " joined the team of " +
		QTNAME(leader) + ".\n", ({ leader, this_player() }));
	leader->catch_msg(this_player()->query_The_name(leader) +
	    " joined your team.\n");
	return 1;
    }
    else
    {
	write(leader->short() +
	      " has not invited you as a team member.\n");
	return 1;
    }
}

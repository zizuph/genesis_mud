#pragma strict_types;

#include "defs.h"

inherit PARTY_BASE;

#include <composite.h>

// Prototypes
string query_party_for();
string query_hosts();
string query_guests();
void lock_party();
void end_party();
object * add_guild_members(string guild);


int costumes, free_food, Party_id, party_ready, party_happening;
string reason, *for_whom = ({}), *hosts = ({}), *guests = ({});
private mapping guilds = ([]);

string *party_rooms = ({PARTY_DIR + "entrance",
  PARTY_DIR+"podium",PARTY_DIR+"post",PARTY_DIR+"dinner",
  PARTY_DIR+"field", PARTY_DIR+"costume_shop", 
  PARTY_DIR+"bank"});

void
make_log(string type,string text)
{
    setuid(); seteuid(getuid());
    write_file(PARTY_LOG + type, ctime(time()) + " " + text);
}

void
create_party_room()
{
    set_short("The MASTER party room");
    set_long("This room takes care all all the party upkeep "+
      "from who started the party to who it is for, and keeps track "+
      "of logs etc..\n");
    guilds = restore_map(MAP_FILE);
    add_prop(ROOM_I_NO_CLEANUP,1);
}

int
query_costumes()
{
    return costumes;
}

int
query_free_food()
{
    return free_food;
}

int
query_is_host(string name)
{
    name = CAP(name);
    if (member_array(name,hosts) != -1)
	return 1;
    else
	return 0;
}

int
query_is_guest_of_honour(string name)
{
    name = CAP(name);
    if (member_array(name,for_whom) != -1)
	return 1;
    else
	return 0;
}

string
query_hosts()
{
    return COMPOSITE_WORDS(map(hosts, capitalize));
}

mixed
query_party_for()
{
    if (!sizeof(for_whom))
	return 0;
    return COMPOSITE_WORDS(map(for_whom, capitalize));
}

string
query_reason()
{
    return reason;
}

string 
query_guests()
{
    return COMPOSITE_WORDS(map(guests, capitalize));
}

string
query_invited()
{
    string *invited = hosts + for_whom + guests;

    invited = map(invited, capitalize);
    return COMPOSITE_WORDS(invited);
}

int
query_is_party()
{
    return party_happening;
}

mapping
query_guilds()
{
    return guilds;
}

void
add_guest(mixed name)
{
    if (party_ready)
    {
	write("No more changes can be made to this party.\n");
	return;
    }
    if (stringp(name))
	name = ({name});
    guests += name;
}

void
add_host(mixed name)
{
    if (party_ready)
    {
	write("No more changes can be made to this party.\n");
	return;
    }
    if (stringp(name))
	name = ({name});
    hosts += name;
}

void
add_guest_of_honour(mixed name)
{
    if (party_ready)
    {
	write("No more changes can be made to this party.\n");
	return;
    }
    if (stringp(name))
	name = ({name});

    for_whom += name;
}

void
set_reason(string str)
{
    if (party_ready)
    {
	write("No more changes are allowed to this party.\n");
	return;
    }
    reason = str;
}

void
set_costumes()
{
    if (party_ready)
    {
	write("No more changes are allowed to this party.\n");
	return;
    }
    costumes = 1;
}

void
set_free_food()
{
    if (party_ready)
    {
	write("No more changes are allowed to this party.\n");
	return;
    }
    free_food = 1;
}

void
lock_party()   //  No more changes to this party.
{
    party_ready = 1;
}

void
tell_party_rooms(string str,string where,object *no_tell)
{
    object room;
    int i;
    for (i = 0;i < sizeof(party_rooms);i++)
    {
	room = find_object(party_rooms[i]);
	switch (where)
	{
	case "inside":
	    if (room->query_prop(ROOM_I_INSIDE))
		tell_room(room, str + "\n",no_tell);
	    break;
	case "outside":
	    if (!room->query_prop(ROOM_I_INSIDE))
		tell_room(room, str + "\n",no_tell);
	    break;
	default:
	    tell_room(room, str + "\n",no_tell);
	    break;
	}
    }
}

void
reset_party()
{
    reason = "";
    for_whom = ({});
    hosts = ({});
    guests = ({});
    party_ready = 0;
    party_happening = 0;
    costumes = 0;
    free_food = 0;
    // Unload some rooms.
    find_object(PARTY_DIR + "entrance")->remove_object();
}

int
check_party_ready()
{
    if (party_happening)
	return 0;
    if (!sizeof(hosts))
	return 0;
    if (!sizeof(guests))
	return 0;
    if (!strlen(reason) || !stringp(reason))
	return 0;

    party_ready = 1;
    return 1;
}

void
start_party(object player)
{
    string *invited;
    int i;
    object *people, *matches, guest;

    if (!party_ready)
	return;

    invited = guests + hosts + for_whom;
    people = users();
    matches = ({});
    if (member_array("all",invited) != -1)
    {
	//  We invite Everyone!!
	matches = people;
    }
    if (member_array("wizards",invited) != -1)
    {
	//  Invite all the wizards and only the wizards
	matches = filter(people, &->query_wiz_level());
    }
    if (!sizeof(matches))
    {
	for (i = 0;i < sizeof(invited); i++)
	{
	    if (guilds[invited[i]])
	    {
		matches += add_guild_members(invited[i]);
	    }
	    else
	    {
		if (guest = find_player(invited[i]))
		{
		    matches += ({guest});
		}
	    }
	}
    }
    if (!sizeof(matches))
    {
	make_log("error","Was unable to find anyone to invite to the party!\n");
	return;
    }
    i = -1;
    while (++i < sizeof(matches))
    {
	if (!present("_shire_party_invite_",matches[i]))
	{
	    setuid(); seteuid(getuid());
	    clone_object(INVITATION)->move(matches[i], 1);
	}
    }
    party_happening = 1;
    Party_id = set_alarm(10800.0, 0.0, &end_party());
    make_log("party","A party hosted by "+query_hosts()+" was started to "+
      "celebrate "+(sizeof(for_whom) ? query_party_for() + "'s " 
	: "") + reason+".\n\n");
    (PARTY_DIR + "field")->load_me();
}

public void
end_party()
{
    int i;
    object *players;

    players = users();
    //  Remove everyone from all the party rooms.
    i = -1;
    while (++i < sizeof(players))
    {
	if (ENV(players[i])->query_shire_party_room())
	{
	    players[i]->catch_msg("The party has come to an end, and you are "+
	      "sent back to where you were before the party started.\n");
	    if (players[i]->query_prop(LIVE_O_ROOM_BEFORE_PARTY))
		players[i]->move_living("X",
		  players[i]->query_prop(LIVE_O_ROOM_BEFORE_PARTY));
	    else
		players[i]->move_living("X",
		  players[i]->query_default_start_location());
	}
    }

    if (TI)
    {
	make_log("party",CAP(TI->query_real_name())+" ended the party to "+
	  "celebrate "+(sizeof(for_whom) ? query_party_for() + "'s " 
	    : "") +reason+".\n\n");
	remove_alarm(Party_id);
    }
    else
	make_log("party","Time ran out on "+query_hosts()+
	  " party for "+query_party_for()+"'s "+reason+".\n\n");
    reset_party();
}

object *
add_guild_members(string short)
{
    object *members = ({});
    object *people = users();

    if (guilds[short][MAP_OCC])
	members += filter(people, &operator(==) (guilds[short][MAP_NAME]) @ 
	  &->query_guild_name_occ());
    if (guilds[short][MAP_LAY])
	members += filter(people, &operator(==) (guilds[short][MAP_NAME]) @
	  &->query_guild_name_lay());
    if (guilds[short][MAP_RACE])
	members += filter(people, &operator(==) (guilds[short][MAP_NAME]) @
	  &->query_guild_name_race());

    return members;
}


void
add_guild(string short, string guild_name, int occ, int lay, int race)
{  

    if (!stringp(short))
	return;
    if (!stringp(guild_name))
	return;
    if (occ + lay + race == 0)
	return;

    TI->catch_msg("Adding "+guild_name+" to the mapping.\n");
    short = lower_case(short);
    guilds[short] = ({guild_name,occ,lay,race});
    save_map(guilds, MAP_FILE);
}

void
remove_guild(string short)
{
    if (!stringp(short))
	return;

    if (!guilds[short])
	return;

    TI->catch_msg("Removing "+guilds[short][MAP_NAME]+" from mapping.\n");
    guilds = m_delete(guilds, short);
    save_map(guilds, MAP_FILE);
}

int
valid_guild_short(string short)
{
    if (guilds[short])
	return 1;

    return 0;
}

void
dump_guilds()
{
    dump_mapping(guilds);
    write("\nTo delete a guild 'Call "+PARTY_MASTER+" remove_guild "+
      "<mapping index>' \n");
}

/* Stralle @ Genesis 001002
 *
 * The admin object for the PoT
 */

#pragma strict_types
#pragma save_binary
#pragma no_clone
#pragma no_inherit

inherit "/std/room";
inherit "/d/Ansalon/guild/new_pot/lib/rank";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "admin.h"
#include <macros.h>
#include <files.h>
#include <alignment.h>
#include <std.h>
#include "../guild.h"

static mapping gGuildlist = ([ ]);
static mapping gPilgrims = ([ ]);
static string *gCouncil = ({ 0, 0, 0, 0, 0 });
static mapping gDelegated = ([ ]);
static mapping gHerbaccess = ([ ]);
static int gTime;

#define MAX_LEADER_IDLE 1900800     
            // 22 days * 60sec * 60min * 24 hours = 1900800 secs (22 days)
/* Prototypes
 */
int query_days_in_guild(string name);
int remove_priest(string name);
int remove_pilgrim(string name);
int remove_council_member(string name, string seat);
string * query_guild_council();
int query_council_absent(string name);
int remove_delegated(string name, string seat);
int add_council_member(string name, string seat);
int query_guild_level(string name);
int remove_herbaccess(string name);
string * set_herbaccess(string name, string *restrictions);
void unset_leader_absent();
void remove_idle_leader();
/*
 */

/* Function name: log
 * Description:   Make a logentry in a standardised format.
 * Arguments:     mixed pl - objectpointer or string to the player
 *                string logfile - the filename, not the pathname
 *                string mess - the log entry
 */
void
log(mixed pl, string logfile, string mess)
{
    string tm = ctime(time()), str, logpath = "/d/Ansalon/log/new_pot/";
    
    if (stringp(pl) && find_player(pl))
        pl = find_player(pl);

    setuid();
    seteuid(getuid());

    /* The council logfile may be read by mortals. Therefore we restrict
     * the contents of it
     */
    if (logfile != "council")
    {
        str = sprintf("%-17s: %-13s  age: (%3d) days: (%3d) " +
        "avg: (%3d)\n", tm[8..9] + "-" + tm[4..6] + "-" + tm[20..23] +
            " " + tm[11..15],
        (objectp(pl) ? capitalize(pl->query_real_name()) : capitalize(pl)),
        (objectp(pl) ? (pl->query_age() * 2) / 86400 : -1),
        (objectp(pl) ? query_days_in_guild(pl->query_real_name()) :
            query_days_in_guild(pl)),
        (objectp(pl) ? pl->query_average_stat() : -1));
    }
    else
    {
        str = sprintf("%-17s: %-13s\n", tm[8..9] + "-" + tm[4..6] + "-" +
         tm[20..23] + " " + tm[11..15],
         (objectp(pl) ? capitalize(pl->query_real_name()) : capitalize(pl)));
        logpath = GUILDDIR + "doc/library/book/";
        logfile = "reportsfromthecouncil";

        /* 600 * 80 characters per line equal 48000 bytes */
        str += "\t" + mess + "\n" + read_file(logpath + logfile, 1, 600);
        rm(logpath + logfile);
        write_file(logpath + logfile, str);

        find_object(GUILD_LIB)->add_council_book_if_not_present();
        return;
    }

    if (file_size(logpath + logfile) > 50000)
    {
        rename(logpath + logfile, logpath + logfile + ".old");
    }

    write_file(logpath + logfile, str + "\t" + mess + "\n");
}

/* Function name: clean_up_vars
 * Description:   Checks whether or not we have purged players in
 *                our variables. The name derives from the fact that
 *                the function name clean_up is reserved in Ansalon
 *                rooms.
 */
void
clean_up_vars()
{
    string *arr = m_indices(gGuildlist), *council_titles = COUNCIL_TITLES;
    int x, size, i = -1;
    
    for (x = 0, size = sizeof(arr) ; x < size ; x++)
    {
        if (!SECURITY->exist_player(arr[x]))
        {
            log(arr[x], "purged", "Has been purged and removed from " +
                "gGuildlist.");
            remove_priest(arr[x]);
        }

        /* Council members can only be idle a set number of days
         * that may be prolonged by a command until they are kicked
         * from the council
         */
        if ((member_array(arr[x], query_guild_council()) >= 0) &&
            (gGuildlist[arr[x]][M_LAST] + 86400 * COUNCIL_IDLE +
                query_council_absent(arr[x])) < time())
        {
            while (++i < 5)
            {
                remove_council_member(arr[x], council_titles[i]);
                remove_delegated(arr[x], council_titles[i]);
            }
            
            log(arr[x], "council", "Had not been seen since " +
                ctime(gGuildlist[arr[x]][M_LAST]));
        }
    }

    for (x = 0, arr = m_indices(gPilgrims), size = sizeof(arr) ; x < size ;
        x++)
    {
        if (gPilgrims[arr[x]] < time())
        {
            log(arr[x], "pilgrims", "Exceeded time and was removed.");
            remove_pilgrim(arr[x]);
        }
    }
}

/* Function name: restore_vars
 * Description:   Reads the saved variables
 */
void
restore_vars()
{
    mapping smap;
    
    setuid();
    seteuid(getuid());

    smap = restore_map(MASTER);
    
    if (m_sizeof(smap))
    {
        gTime = smap["time"];
        gGuildlist = smap["guildlist"];
        gPilgrims = smap["pilgrims"];
        gCouncil = smap["council"];
        gDelegated = smap["delegated"];
        gHerbaccess = smap["herbaccess"];
    }

    clean_up_vars();
}

/* Function name: save_vars
 * Description:   Saves the vars to disk
 */
void
save_vars()
{
    mapping smap;
    
    setuid();
    seteuid(getuid());

    smap = ([ "time" : gTime,
              "guildlist" : gGuildlist,
              "pilgrims" : gPilgrims,
              "council" : gCouncil,
              "delegated" : gDelegated,
              "herbaccess" : gHerbaccess ]);
    
    save_map(smap, MASTER);
}

void
one_time()
{
    int x, y;
    string *arr = ({ "diri", "zagar" });
    
    save_vars();
    dump_array(gGuildlist["diri"]);

    for (x = 0 ; x < 2 ; x++)
    {
        for (y = 0 ; y < sizeof(gGuildlist[arr[x]][M_LOCS]) ; y++)
        {
            if (!pointerp(gGuildlist[arr[x]][M_LOCS][y]))
            {
                gGuildlist[arr[x]][M_LOCS] = exclude_array(gGuildlist[arr[x]][M_LOCS], y, y);
                y--;
                continue;
            }
        }
    }

    dump_array(gGuildlist["diri"]);
#ifdef 0
    restore_vars();
#else
    save_vars();
#endif
}

/* Function name: query_guild_list
 * Description:   Returns an array of the members by name we have
 * Returns:       string * - the membernames
 */
string *
query_guild_list()
{
    return m_indices(gGuildlist);
}

/* Function name: query_days_in_guild
 * Description:   Returns the number of days the member by name have
 *                been member.
 * Arguments:     string name - the membername
 * Returns:       int - the number of days or -1 if not member.
 */
int
query_days_in_guild(string name)
{
    int isn_real, days;
    object pl;
    
    if (!gGuildlist[name])
        return -1;
    
    if (!(pl = find_player(name)))
    {
        pl = SECURITY->finger_player(name);
        isn_real = 1;
    }

    days = ((pl->query_age() * 2) - (gGuildlist[name][M_AGE])) /
        86400;

    /* Clean up after ourselves */
    if (isn_real)
        pl->remove_object();

    return (days <= 0 ? 1 : days);
}

void
set_age(string name, int t)
{
    gGuildlist[name][M_AGE] = t;

    save_vars();
}

int
query_days_in_level(string name)
{
    int isn_real, days;
    object pl;
    
    if (!gGuildlist[name])
        return -1;
    
    if (!(pl = find_player(name)))
    {
        pl = SECURITY->finger_player(name);
        isn_real = 1;
    }

    if (sizeof(gGuildlist[name]) <= M_GAGE)
        return -1;
        
    if (!gGuildlist[name][M_GAGE])
        gGuildlist[name][M_GAGE] = pl->query_age() * 2;

    days = ((pl->query_age() * 2) - (gGuildlist[name][M_GAGE])) /
        86400;

    /* Clean up after ourselves */
    if (isn_real)
        pl->remove_object();

    return (days <= 0 ? 0 : days);
}

void
set_level_age(string name, int t)
{
    gGuildlist[name][M_GAGE] = t;
    
    save_vars();
}

/* Function name: set_leader
 * Description:   Tries to set the leader of the guild. An alias for
 *                add_council_member(name, "leader"). See that function
 *                description for return values.
 * Arguments:     string name - the one we want as leader
 * Returns:       See add_council_member
 */
int
set_leader(string name)
{
    int r;
    
    r = add_council_member(name, "leader");
    if (r == 1)
        unset_leader_absent();
    
    return r;
}

/* Function name: query_guild_leader
 * Description:   Returns the name of the leader or an empty string.
 * Returns:       string - the leader or an empty string
 */
string
query_guild_leader()
{
    return query_guild_council()[0];
}

/* Function name: add_pilgrim
 * Description:   Adds a player to the list of pilgrims
 * Arguments:     string name - the name to add as pilgrim
 * Returns:       int - 1, success or 0 failure.
 */
int
add_pilgrim(string name)
{
    if (gPilgrims[name])
        return 0;
     
    /* time() + two weeks */
    gPilgrims[name] = time() + 86400 * 7 * 2;
    log(name, "pilgrims", "Added as pilgrim");
    save_vars();
    
    return 1;
}

/* Function name: query_pilgrim
 * Description:   Returns whether or not a certain player is a pilgrim
 * Arguments:     string name - the player to check against
 * Returns:       int - 1, is a pilgrim or 0 is not a pilgrim
 */
int
query_pilgrim(string name)
{
    return !(!(gPilgrims[name]));
}

/* Function name: query_pilgrims
 * Description:   Returns the names of all pilgrims
 * Returns:       string * - the names
 */
string *
query_pilgrims()
{
    return m_indices(gPilgrims);
}

/* Function name: query_pilgrimage
 * Description:   Returns the time a pilgrimage is due for a player
 * Arguments:     string name - the pilgrim
 * Returns:       int - the time in seconds since 700101
 */
int
query_pilgrimage(string name)
{
    return gPilgrims[name];
}

/* Function name: extend_pilgrimage
 * Description:   Updates the expiration time for the player by setting
 *                a new time for expiration.
 * Arguments:     string name - the pilgrim
 *                int date    - the new expiration time in unix epoch time
 *                              format
 * Returns:       int - 1, updated or 0 no such pilgrim
 */
int
extend_pilgrimage(string name, int date)
{
    if (!gPilgrims[name])
        return 0;
    
    gPilgrims[name] = date;
    log(name, "pilgrims", "Pilgrimage extended to " + ctime(date));
    save_vars();
    
    return 1;
}

/* Function name: remove_pilgrim
 * Description:   Removes a pilgrim from the list of pilgrims
 * Arguments:     string name - the pilgrim to remove
 * Returns:       int - 1, removed or 0 no such pilgrim
 */
int
remove_pilgrim(string name)
{
    if (!gPilgrims[name])
        return 0;

    gPilgrims = m_delete(gPilgrims, name);
    if (!gPilgrims)
        gPilgrims = ([ ]);
    log(name, "pilgrims", "Removed as pilgrim");
    save_vars();

    return 1;
}

/* Function name: query_promoted
 * Description:   Returns the new PS_GUILD_LEVEL we have been pro/de-moted to
 * Arguments:     string name - the member
 * Returns:       int - 0, not promoted
 *                     -1, not a member
 *                     >0, the new PS_GUILD_LEVEL pro/de-moted to
 */
int
query_promoted(string name)
{
    if (!gGuildlist[name])
        return -1;
    
    if (!gGuildlist[name][M_PROMO])
        return 0;

    return gGuildlist[name][M_PROMO];
}

/* Function name: set_promoted
 * Description:   Pro/De-motes a member of the guild by setting the new
 *                PS_GUILD_LEVEL he may reach instantly after praying.
 * Arguments:     string name - the member
 *                int gs      - the new PS_GUILD_LEVEL
 */
int
set_promoted(string name, int gs)
{
    if (!gGuildlist[name])
        return -1;
    
    gGuildlist[name][M_PROMO] = gs;
    save_vars();
    
    return 1;
}

/* Function name: clear_promotions
 * Description:   An alias for set_promoted(name, 0) to reset the
 *                promotion status of the player, called after raising
 *                in rank.
 * Arguments:     string name - the member
 */
void
clear_promotions(string name)
{
    set_promoted(name, 0);
}

/* Function name: query_delegated
 * Description:   Returns the time for when a delegation ends for
 *                a specific councilmember and seat
 * Arguments:     string name - the councilmember
 *                string seat - the councilseat
 * Returns:       int - 0, no such seat
 *                     -1, no such delegation
 *                     >0, the time for the delegation ends
 */
int
query_delegated(string name, string seat)
{
    int i;

    if (!gDelegated[name])
        return -1;
    
    if ((i = member_array(seat, gDelegated[name])) >= 0)
        return gDelegated[name][i + 1];

    return 0;
}

/* Function name: remove_delegated
 * Description:   Removes a delegation for a specfic councilmember
 *                and seat
 * Arguments:     string name - the councilmember
 *                string seat - the councilseat
 *  Returns:      int - -1, not delegated
 *                      -2, not a seat delegated
 *                       1, properly removed
 */
int
remove_delegated(string name, string seat)
{
    int i;
    
    if (!gDelegated[name])
        return -1;
    
    if ((i = member_array(seat, gDelegated[name])) < 0)
        return -2;

    gDelegated[name] = exclude_array(gDelegated[name], i, i + 1);
    
    if (!sizeof(gDelegated[name]))
        gDelegated = m_delete(gDelegated, name);

    if (!gDelegated)
        gDelegated = ([ ]);
    
    save_vars();
    
    return 1;
}

/* Function name: set_delegated
 * Description:   Delegates councilcommands to another councilmember
 * Arguments:     string whom  - the councilmember
 *                string seat  - the councilseat
 *                int duration - when the delegation is set to end
 * Returns:       int - -1, no member of the council
 *                      -2, no such councilseat
 *                      -3, already delegated
 *                       1, now delegated
 */
int
set_delegated(string whom, string seat, int duration)
{
    if (member_array(whom, query_guild_council()) < 0)
        return -1;

    if (member_array(seat, COUNCIL_TITLES) < 0)
        return -2;

    if (query_delegated(whom, seat) == 1)
        return -3;

    if (sizeof(gDelegated[whom]))
        gDelegated[whom] += ({ seat, duration });
    else
        gDelegated[whom] = ({ seat, duration });

    save_vars();

    return 1;
}

/* Function name: set_council_absent
 * Description:   Sets a council member as being absent.
 * Arguments:     string name - the councilmember
 *                int absent  - the unix epoch time for when he intends to
 *                              come back
 * Returns:       int - 1, always
 */
int
set_council_absent(string name, int absent)
{
    gGuildlist[name][M_ABSENCE] = absent;
    save_vars();

    return 1;
}

/* Function name: query_council_absent
 * Description:   Returns how much longer in unix epoch time a councilmember
 *                have said he is going to be returning
 * Arguments:     string name - the councilmember
 * Returns:       int - 0, time passed or not set.
 *                     >0, unix epoch time for when he is to return
 */
int
query_council_absent(string name)
{
    return (gGuildlist[name][M_ABSENCE] - time() < 0 ? 0 :
        gGuildlist[name][M_ABSENCE] - time());
}

/* Function name: query_guild_council
 * Description:   Returns an array of the current council if any.
 * Returns:       string * - the council or an empty array if none
 */
string *
query_guild_council()
{
    return gCouncil; // Milan - we return only set council
                     // Stralle - no we do not, it is vital for its functionality
}

/* Function name: add_council_member
 * Description:   Adds a player to the council. There must be sufficiant
 *                number of seats left and (s)he must be a high priest
 * Arguments:     string name - the player who wishes to be on the council
 *                string seat - what position the player wants.
 *                              COUNCIL_TITLES[x] in guild.h
 * Returns:       int - -1, not a member
 *                      -2, not high level enough
 *                      -3, no such councilseat.
 *                      -4, already taken. First demote the councilmember.
 *                       1, added to the council
 */
int
add_council_member(string name, string seat)
{
    int i;
    object pl;
    
#ifdef 0
    /* If we ever change the size of the council this must be called */
    if ((i = (COUNCIL_SEATS - sizeof(gCouncil))) > 0)
        gCouncil += allocate(i);
#endif

    if (!gGuildlist[name])
        return -1;

    if ((query_guild_level(name) / 50) < GUILD_LEVEL_HIGH_PRIEST)
        return -2;

    /* Leader can only be set by set_leader() */
    if ((i = member_array(seat, COUNCIL_TITLES)) < 0)
        return -3;

    if (stringp(gCouncil[i]))
        return -4;

    gCouncil[i] = name;

    save_vars();

    log(name, "admin", "Added to council as " + seat);

    if ((pl = find_player(name)))
        clone_object(GUILDDIR + "obj/council/" + COUNCIL_TITLES[i])->move(pl);
    
    return 1;
}

/* Function name: remove_council_member
 * Description:   Removes a member from the council
 * Arguments:     string name - the name of the councilmember
 *                string seat - the seat that the councilmember holds
 * Returns:       int - 1, now removed
 *                     -1, not on the council to begin with.
 *                     -2, not a seat of the council
 */
int
remove_council_member(string name, string seat)
{
    int i;
    object pl;

    if ((i = member_array(seat, COUNCIL_TITLES)) < 0)
        return -2;
    
    if (gCouncil[i] != name)
        return -1;

    gCouncil[i] = 0;
    
    save_vars();

    log(name, "admin", "Removed from council as " + seat);
    
    if ((pl = find_player(name)))
    {
        present(seat + "_council_object", pl)->remove_object();
    }

    return 1;
}

/* Function name: query_council_seat
 * Description:   Queries whom has a certain council seat if any.
 * Arguments:     string seat - the seat defined by COUNCIL_TITLES[x]
 * Returns:       int    - 0, no such council seat.
 *                string - empty string, council seat not taken.
 *                         the name of the one who sits on the council seat
 */
string
query_council_seat(string seat)
{
    int i;

    if ((i = member_array(seat, COUNCIL_TITLES)) < 0)
        return 0;
    
    return (stringp(gCouncil[i]) ? gCouncil[i] : "");
}

int
sort_guild_list_ranking(string a, string b)
{
    return query_guild_level(b) - query_guild_level(a);
}

int
query_leader_absent()
{
    return gTime;
}

void
set_leader_absent()
{
    gTime = time();
    save_vars();
}

void
unset_leader_absent()
{
    gTime = 0;
    save_vars();
}

int
query_leadership_claimable(string name)
{
    int x, size;
    string *arr;

    if (!query_leader_absent())
        return -1;

    arr = sort_array(query_guild_list(), sort_guild_list_ranking);
    for (x = 0, size = sizeof(arr) ; x < size ; x++)
    {
        if (arr[x] == name && time() -
            (query_leader_absent() + (x * 86400 * 2)) >= 0)
            return 1;
    }

    return 0;
}
            
/* Function name: update_last_entered
 * Description:   Gets called from init_priest(), i.e. whenever a member
 *                logs on. Here to update the last time entered info
 *                and also see to it that members are to be added to
 *                the various variables
 * Arguments:     string name - the membername
 */
static void
update_last_entered(string name)
{
    int t;

#ifdef 0
    /* In a transession phase we automagically fill in the missing
     * info for our current members
     */
    if (!gGuildlist[name])
    {
        gGuildlist[name] = allocate(M_CURSIZE);

        /* This will be wrong for those members we already have */
        gGuildlist[name][M_AGE] = find_player(name)->query_age() * 2;
        gGuildlist[name][M_LAST] = time();
    }
    else
    {
#endif
        /* Also check if our arraysize has changed, if so pad it
         */
        if ((t = (M_CURSIZE - sizeof(gGuildlist[name]))) > 0)
            gGuildlist[name] += allocate(t);
        
        gGuildlist[name][M_LAST] = time();
#ifdef 0
    }
#endif

    if (!query_guild_leader() && !query_leader_absent())
        set_leader_absent();

    save_vars();
}

/* Function name: add_priest
 * Description:   Called when we let someone join. Adds the initiate
 *                to the variables we have. This is the only thing we
 *                will do. Guildshadows, souls, etc needs to handled
 *                elsewhere.
 * Arguments:     object p - the initiate
 *                object i - the sponsor if any.
 */
varargs void
add_priest(object p, object i)
{
    string name = p->query_real_name();

    if (pointerp(gGuildlist[name]))
        return;

    gGuildlist[name] = allocate(M_CURSIZE);

    if (objectp(i))
        gGuildlist[name][M_SPONSOR] = i->query_real_name();
    
    gGuildlist[name][M_AGE] = p->query_age() * 2;
    gGuildlist[name][M_LAST] = time();

#ifdef ADMIN_LOGS_ON_ITS_OWN
    if (objectp(i))
    {
        log(p, "join", "Joined, initiated by " +
            capitalize(i->query_real_name()));
    }
    else
    {
        log(p, "join", "Joined, initiated by noone");
    }
#endif

    remove_pilgrim(p->query_real_name());
    set_herbaccess(p->query_real_name(), ({ "buying", "listing", "identifying" }));

    save_vars();
}    

/* Function name: remove_priest
 * Description:   Called when we leave the guild somehow. Removes the
 *                priest in question from our variables. This is the
 *                only thing we will do. Removing guildshadows, souls,
 *                etc will have to be handled elsewhere.
 * Arguments:     string name - the name of the priest about to leave.
 * Returns:       int - 1, removed successfully
 *                     -1, not a priest to begin with.
 */
int
remove_priest(string name)
{
    int i = -1;
    string *council_titles;

    if (!gGuildlist[name])
        return -1;

    /* Check if we are on the council, if so remove ourselves from the
     * council
     */
    if (member_array(name, gCouncil) >= 0)
    {
        council_titles = COUNCIL_TITLES;
        /* We may hold several council positions
         */
        while (++i < 5)
        {
            remove_council_member(name, council_titles[i]);
            remove_delegated(name, council_titles[i]);
        }
    }
    
    /* We might have herb restrictions
     */
    remove_herbaccess(name);
    /* And finally removes ourselves from the guildlist
     */
    gGuildlist = m_delete(gGuildlist, name);

    save_vars();

#ifdef ADMIN_LOGS_ON_ITS_OWN
    log(name, "join", "Left the guild");
#endif
    
    return 1;
}

/* Function name: query_priest_sponsor
 * Description:   Returns what sponsor a priest has if any.
 * Arguments:     string name - the priest whom we want to know the sponsor
 * Returns:       int    - -1, not a member
 *                string - the sponsor or if none, an empty string.
 */
mixed
query_priest_sponsor(string name)
{
    if (!gGuildlist[name])
        return -1;
    
    return (stringp(gGuildlist[name][M_SPONSOR]) ?
        gGuildlist[name][M_SPONSOR] : "");
}

/* Function name: set_guild_level
 * Description:   Sets the guild level of a player (PS_GUILD_LEVEL) to
 *                allow for queries when the player is not logged on.
 *                We cannot use /secure/finger_player for this as it does
 *                not support skills
 * Arguments:     string name - the priest
 *                int lev     - the lev to set to
 * Returns:       int, -1 - no such priest
 *                      1 - successfully set
 */
int
set_guild_level(string name, int lev)
{
    if (!gGuildlist[name])
        return -1;
    
    gGuildlist[name][M_GLEV] = lev;
    save_vars();
    
    return 1;
}

/* Function name: query_guild_level
 * Description:   Returns the last set guild level for a player. See
 *                set_guild_level for a more explanatory description.
 * Arguments:     string name - the priest
 * Returns:       int, -1 - no such priest
 *                    >=0 - the previously set guild level
 */
int
query_guild_level(string name)
{
    if (!gGuildlist[name])
        return -1;

    return gGuildlist[name][M_GLEV];
}

/* Function name: remove_herbaccess
 * Description:   Remove all access given/taken away from the player
 * Arguments:     string name - the player to remove access
 * Returns:       int - 1, removed or 0, not given access
 */
int
remove_herbaccess(string name)
{
    if (!gHerbaccess[name])
        return 0;
    
    gHerbaccess = m_delete(gHerbaccess, name);
    if (!gHerbaccess)
        gHerbaccess = ([ ]);
        
    save_vars();
    
    return 1;
}

/* Function name: set_herbaccess
 * Description:   Toggles access to the herbshop for various players.
 *                Access given to non-members will be positive.
 *                Access given to members will be negative.
 * Arguments:     string name          - the player
 *                string *restrictions - an array of any or none of
 *                                       "buying", "selling", "listing" or
 *                                       "identifying"
 * Returns:       string * - the new toggled access.
 */
string *
set_herbaccess(string name, string *restrictions)
{
    string *restr = ({ });

    if (!SECURITY->exist_player(name))
        return 0;

    if (!gHerbaccess[name])
        gHerbaccess[name] = ({ });

    /* Toggles the various states */
    if ((member_array("buying", restrictions) >= 0) &&
        (member_array("buying", gHerbaccess[name]) < 0) ||
        (member_array("buying", restrictions) < 0) &&
        (member_array("buying", gHerbaccess[name]) >= 0))
        restr += ({ "buying" });
    if ((member_array("selling", restrictions) >= 0) &&
        (member_array("selling", gHerbaccess[name]) < 0) ||
        (member_array("selling", restrictions) < 0) &&
        (member_array("selling", gHerbaccess[name]) >= 0))
        restr += ({ "selling" });
    if ((member_array("listing", restrictions) >= 0) &&
        (member_array("listing", gHerbaccess[name]) < 0) ||
        (member_array("listing", restrictions) < 0) &&
        (member_array("listing", gHerbaccess[name]) >= 0))
        restr += ({ "listing" });
    if ((member_array("identifying", restrictions) >= 0) &&
        (member_array("identifying", gHerbaccess[name]) < 0) ||
        (member_array("identifying", restrictions) < 0) &&
        (member_array("identifying", gHerbaccess[name]) >= 0))
        restr += ({ "identifying" });

    gHerbaccess[name] = restr;
    save_vars();
    
    /* Remove the mapping index if all restrictions were taken away.
     */
    if (!sizeof(restr))
        remove_herbaccess(name);

    return gHerbaccess[name];
}

/* Function name: query_herbaccess
 * Description:   Returns the set state of the access for the player.
 *                See set_herbaccess for details.
 * Arguments:     string name - the player
 * Returns:       string * - The access
 */
string *
query_herbaccess(string name)
{
    return gHerbaccess[name];
}

/* Function name: query_herbaccess_list
 * Description:   Will return a sorted array of all accesses given in the
 *                form of ({ "name1", ({ "access1", "access2" }) }), ...
 * Returns:       mixed * - the array.
 */
mixed *
query_herbaccess_list()
{
    string *names = sort_array(m_indices(gHerbaccess));
    int x, size;
    mixed *arr = ({ });
    
    for (x = 0, size = sizeof(names) ; x < size ; x++)
        arr += ({ names[x], gHerbaccess[names[x]] });

    return arr;
}

/* Function name: set_priest_punishment
 * Description:   Sets the punishments the priest has. This uses bitwise
 *                numbers as defined by admin.h
 * Arguments:     string name - the priest to set the punishment for
 *                int pun     - the punishment
 * Returns:       int - 1, successfully set
 *                     -1, no such member
 */
int
set_priest_punishment(string name, int pun)
{
    if (!gGuildlist[name])
        return -1;

    gGuildlist[name][M_PUN] = pun;

    save_vars();
    
    log(name, "admin", "Punishment set: " + pun);

    return 1;
}

/* Function name: add_priest_punishment
 * Description:   Adds a punishment for a priest. This uses bitwise
 *                numbers as defined by admin.h
 * Arguments:     string name - the name of the priest
 *                int pun     - the punishment to add
 * Returns:       int - 1, successfully added
 *                     -1, no such member
 */
int
add_priest_punishment(string name, int pun)
{
    if (!gGuildlist[name])
        return -1;
    
    gGuildlist[name][M_PUN] |= pun;
    
    save_vars();

    log(name, "admin", "Punishment added: " + pun);
    
    return 1;
}

/* Function name: remove_priest_punishment
 * Description:   Removes a punishment from the priest. This uses bitwise
 *                numbers as defined by admin.h
 * Arguments:     string name - the name of the priest
 *                int pun     - the punishment to remove
 * Returns:       int - 1, successfully removed
 *                     -1, no such member
 */
int
remove_priest_punishment(string name, int pun)
{
    if (!gGuildlist[name])
        return -1;

    gGuildlist[name][M_PUN] &= ~(pun);

    save_vars();

    log(name, "admin", "Punishment removed: " + pun);
    
    return 1;
}

/* Function name: query_priest_has_punishment
 * Description:   Checks if the priest has a certain punishment type.
 *                This uses bitwise numbers as defined by admin.h
 * Arguments:     string name - the name of the priest
 *                int pun     - the punishment to check for
 * Returns:       int - 0, doesn't have the punishment
 *                      1, has the punishment
 *                     -1, no such member
 */
int
query_priest_has_punishment(string name, int pun)
{
    if (!gGuildlist[name])
        return -1;
    
   return !(!(gGuildlist[name][M_PUN] & pun));
}

/* Function name: query_priest_punishments
 * Description:   Returns all punishments the priest has which then can
 *                be queried individually with the & operator. This uses
 *                bitwise numbers as defined by admin.h
 * Arguments:     string name - the name of the priest
 * Returns:       int - -1, not a member to begin with
 *                     >=0, the punishments added or if 0, no punishments
 */
int
query_priest_punishments(string name)
{
    if (!gGuildlist[name])
        return -1;
    
    return (gGuildlist[name][M_PUN]);
}

/* Function name: set_priest_quest
 * Description:   Sets the quests the priest has. This uses bitwise
 *                numbers as defined by admin.h
 * Arguments:     string name - the priest to set the quest for
 *                int quest   - the quest
 * Returns:       int - 1, successfully set
 *                     -1, no such member
 */
int
set_priest_quest(string name, int quest)
{
    if (!gGuildlist[name])
        return -1;

    gGuildlist[name][M_QUEST] = quest;

    save_vars();
    
    log(name, "admin", "Quest set: " + quest);

    return 1;
}

/* Function name: add_priest_quest
 * Description:   Adds a quest for a priest. This uses bitwise
 *                numbers as defined by admin.h
 * Arguments:     string name - the name of the priest
 *                int quest   - the quest to add
 * Returns:       int - 1, successfully added
 *                     -1, no such member
 */
int
add_priest_quest(string name, int quest)
{
    if (!gGuildlist[name])
        return -1;
    
    gGuildlist[name][M_QUEST] |= quest;
    
    save_vars();

    log(name, "admin", "Quest added: " + quest);
    
    return 1;
}

/* Function name: remove_priest_quest
 * Description:   Removes a quest from the priest. This uses bitwise
 *                numbers as defined by admin.h
 * Arguments:     string name - the name of the priest
 *                int quest   - the quest to remove
 * Returns:       int - 1, successfully removed
 *                     -1, no such member
 */
int
remove_priest_quest(string name, int quest)
{
    if (!gGuildlist[name])
        return -1;

    gGuildlist[name][M_QUEST] &= ~(quest);

    save_vars();

    log(name, "admin", "Quest removed: " + quest);
    
    return 1;
}

/* Function name: query_priest_has_quest
 * Description:   Checks if the priest has a certain quest type.
 *                This uses bitwise numbers as defined by admin.h
 * Arguments:     string name - the name of the priest
 *                int quest   - the quest to check for
 * Returns:       int - 0, doesn't have the quest
 *                      1, has the quest
 *                     -1, no such member
 */
int
query_priest_has_quest(string name, int quest)
{
    if (!gGuildlist[name])
        return -1;

    if (sizeof(gGuildlist[name]) < M_CURSIZE)
        return 0;
    
   return !(!(gGuildlist[name][M_QUEST] & quest));
}

/* Function name: query_priest_quests
 * Description:   Returns all quests the priest has which then can
 *                be queried individually with the & operator. This uses
 *                bitwise numbers as defined by admin.h
 * Arguments:     string name - the name of the priest
 * Returns:       int - -1, not a member to begin with
 *                     >=0, the quests added or if 0, no quests
 */
int
query_priest_quests(string name)
{
    if (!gGuildlist[name])
        return -1;
    
    return (gGuildlist[name][M_QUEST]);
}

#define PLANESWALK_LOCS 3

int
query_planeswalk_slots(string name)
{
    int x;

    if (!gGuildlist[name])
        return -1;

    /* Need to deduce the guildage at the time the spell was recieved
     * Utilising the special hidden guildstat could be another approach
     */
    return PLANESWALK_LOCS + (find_player(name)->exp_to_stat(
       find_player(name)->query_skill(PS_SKILL_POINTS)) / 25);
}
    
int
set_planeswalk_loc(string name, string room, string loc)
{
    int x, oldest;
    
    if (!gGuildlist[name])
        return -1;
    
    if (file_size(room + ".c") < 0)
        return -2;
    
    if (!loc)
        return -3;
    
    if (!pointerp(gGuildlist[name][M_LOCS]))
        gGuildlist[name][M_LOCS] = ({ });
//        allocate(query_planeswalk_slots(name));

    if (sizeof(gGuildlist[name][M_LOCS]) >= query_planeswalk_slots(name))
        return -4;

#ifdef 0
    for (x = 0, oldest = 0 ; x < query_planeswalk_slots(name) ; x++)
    {
        if (sizeof(gGuildlist[name][M_LOCS]) &&
            sizeof(gGuildlist[name][M_LOCS][x]) &&
            !sizeof(gGuildlist[name][M_LOCS][(x + 1) % query_planeswalk_slots(name)]))
            oldest = (x + 1) % query_planeswalk_slots(name);

        if (sizeof(gGuildlist[name][M_LOCS]) &&
            sizeof(gGuildlist[name][M_LOCS][x]) &&
            sizeof(gGuildlist[name][M_LOCS][(x + 1) % query_planeswalk_slots(name)]) &&
            gGuildlist[name][M_LOCS][x % query_planeswalk_slots(name)][3] <
            gGuildlist[name][M_LOCS][(x + 1) % query_planeswalk_slots(name)][3])
            oldest = x;
    }
    
    gGuildlist[name][M_LOCS][oldest] = ({ room, room->query_short(),
        lower_case(loc), time() });
#else
    gGuildlist[name][M_LOCS] +=
        ({ ({ room, room->query_short(), lower_case(loc), time() }) });
#endif
    save_vars();

    return 1;
}

mixed
query_planeswalk_loc(string name, string loc)
{
    int x;
    
    if (!gGuildlist[name])
        return -1;
    
    for (x = 0 ; x < query_planeswalk_slots(name) &&
        x < sizeof(gGuildlist[name][M_LOCS]) ; x++)
    {
#ifdef 0
        if (sizeof(gGuildlist[name][M_LOCS]) &&
            sizeof(gGuildlist[name][M_LOCS][x]))
#endif
            if (lower_case(gGuildlist[name][M_LOCS][x][2]) == loc)
                return gGuildlist[name][M_LOCS][x][0];
    }
    
    return 0;
}

int
remove_planeswalk_loc(string name, string loc)
{
    object tp;
    int x;
    
    if (!gGuildlist[name])
        return -1;
    
    if (!query_planeswalk_loc(name, loc))
        return -2;

    for (x = 0 ; x < query_planeswalk_slots(name) &&
        x < sizeof(gGuildlist[name][M_LOCS]) ; x++)
    {
        find_player("stralle")->catch_tell("#pot#admin: x: " + x + "\n");
#ifdef 0
        if (sizeof(gGuildlist[name][M_LOCS]) &&
            sizeof(gGuildlist[name][M_LOCS][x]))
#endif
            if (lower_case(gGuildlist[name][M_LOCS][x][2]) == loc)
            {
                gGuildlist[name][M_LOCS] = exclude_array(gGuildlist[name][M_LOCS], x, x);
                break;
            }
    }

    save_vars();
    return 1;    
}

mapping
query_planeswalk_locations(string name)
{
    mapping smap = ([]);
    int x;
    
    if (!gGuildlist[name])
        return 0;

    for (x = 0 ; x < query_planeswalk_slots(name) &&
        x < sizeof(gGuildlist[name][M_LOCS]) ; x++)
    {
#ifdef 0
        if (sizeof(gGuildlist[name][M_LOCS]) &&
            sizeof(gGuildlist[name][M_LOCS][x]))
#endif
            smap[gGuildlist[name][M_LOCS][x][2]] = ({
                gGuildlist[name][M_LOCS][x][0],
                gGuildlist[name][M_LOCS][x][1],
                gGuildlist[name][M_LOCS][x][3] });
    }

    return smap;
}    

/* Function name: query_may_join
 * Description:   Checks whether or not a player may join our guild.
 * Arguments:     object pl - the player who wishes to join.
 * Returns:       string - reason as to why not (s)he may not join
 *                int - 0, success.
 */
mixed
query_may_join(object pl)
{
    if (MEMBER(pl))
        return "already a member";
    
    if (pl->query_alignment() >= ALIGN_SINISTER)
        return "not following the path of evil";

    if (pl->query_guild_name_lay() || pl->query_guild_name_occ())
        return "torn between loyalties";
    
#ifdef RACES_BLOCK
    if (member_array(pl->query_race_name(), RACES_BLOCK) >= 0)
        return "of an inferior race";
#endif

    return 0;
}

/* Function name: init_priest
 * Description:   Called whenever a member logs on.
 * Arguments:     object pl - the member who logs on.
 */
void
init_priest(object pl)
{
    int i;
    object ob;
    string *arr = COUNCIL_TITLES;

    /* update_last_entered() calls save_vars() */
    update_last_entered(pl->query_real_name());

    /* A priest may hold any or all of the council positions */
    for (i = 0 ; i < 5 ; i++)
    {
        if ((stringp(query_guild_council()[i]) &&
            query_guild_council()[i] == pl->query_real_name()) ||
            query_delegated(pl->query_real_name(), arr[i]) > time())
        {
            setuid();
            seteuid(getuid());

            ob = clone_object(GUILDDIR + "obj/council/" + arr[i]);
            if (ob->move(pl))
                ob->move(pl, 1);
        }
    }

    if (query_guild_leader() == pl->query_real_name())
    {
        set_alarm(0.1, 0.0, &(pl)->catch_tell("Being the leader of " +
            "the priesthood you shall be known as such and may always " +
            "ask Terwed about your true title.\n"));
        pl->add_prop(POT_SPECIAL_TITLE, TITLES_COUNCIL["leader"][
            (pl->query_gender() == G_FEMALE ? 1 : 0)][0]);
    }
}

/*
 * Functions for the room itself here on
 */

string
print_quests(string name)
{
    string s="";

    s += (query_priest_has_quest(name, Q_ANTECHAMBERS) == 1 ? "1" : " ");
    s += (query_priest_has_quest(name, Q_KALAMAN) == 1 ? "2" : " ");
    s += (query_priest_has_quest(name, Q_VERMINAARD) == 1 ? "3" : " ");
    
    return s;
}

/* 
 * Function: check_replace_leader
 * Description: Try to become the leader if the spot is open
 */
int
check_replace_leader(mixed who)
{
    if (objectp(who)) {
        who = who->query_real_name();
    }
    string s;

    remove_idle_leader();

    //Still have a leader
    if (strlen(s = query_guild_leader()))
        return 0;

    if (1 == set_leader(who))
    {
        return 1;
    }

    return 0;
}

/*
 * Function : remove_idle_leader
 * Description: Remove a leader that hasn't logged in for X days
 */
void
remove_idle_leader()
{
    //Check if any King has logged in within 22 days
    // 60sec * 60min * 24 hours * 22 days = 1900800 secs
    int t = time() - MAX_LEADER_IDLE;

    string lead = query_guild_leader();

    if (!strlen(lead))
        return;

    if (find_player(lead))
        return;

    int j = file_time(PLAYER_FILE(lead) + ".o");

    if (j < t) {
        remove_council_member(lead, "leader");
        //remove_council_member calls save_vars(), no need to do it here
    }    
}

/* Function name: do_list
 * Description:   The function for the list members command
 * Arguments:     string str - the argument
 * Returns:       int - 1/0, success or failure
 */
int
do_list(string str)
{
    int x, size;
    string *arr;
    object pl;
    
    if (!str || str != "members")
    {
        notify_fail("List what?\n");
        return 0;
    }
    
    str = sprintf("%-11s %-8s %-8s %-6s %-6s %-5s %-8s %-6s\n",
        "Name", "Guildage", "Levelage", "Due in", "Online", "Level", "Standing", "Quests");
    str += "----------- -------- -------- ------ ------ ----- -------- ------\n";

    for (x = 0, arr = query_guild_list(), size = sizeof(arr) ;
         x < size ; x++)
    {
        str += sprintf("%-11s %3d days %3d days  %3d   %|6s  %2d.%1d %8s %-6s\n",
            capitalize(arr[x]), query_days_in_guild(arr[x]),
            query_days_in_level(arr[x]),
            "/d/Ansalon/guild/new_pot/lib/rank"->due_in(arr[x]),
            ((pl = find_player(arr[x])) ? "Yes" : "No"),
            query_guild_level(arr[x]) / 10,
            query_guild_level(arr[x]) % 10,
            (objectp(pl) ? "" + pl->query_skill(PS_STANDING) : "n/a"),
            print_quests(arr[x]));
    }
    
    write(str);

    return 1;
}

int
do_nstat(string arg)
{
    object *arr;
    int x, y, size, size2;
    string *loc, str;

    if (arg)
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    for (x = 0, str = "", arr = users(), size = sizeof(arr) ; x < size ; x++)
    {
        if (!environment(arr[x]) ||
            !wildmatch("/d/Ansalon/taman_busuk/neraka/*",
            file_name(environment(arr[x]))))
            continue;
        
        loc = explode(file_name(environment(arr[x])), "/");
        size2 = sizeof(loc);
        
        str += sprintf("%-13s : %s\n",
            capitalize(arr[x]->query_real_name()),
            implode(loc[5 .. size2 - 1], "/"));
    }

    if (strlen(str))
        write(str);
    else
        write("No-one in Neraka.\n");

    return 1;
}
/* Function name: create_room
 * Description:   The create function
 */
void
create_room()
{
    set_short("PoT admin room");
    set_long("This is the PoT admin room where you currently can " +
        "do the following:\n" +
        "  list members\n" +
        "  nstat\n");

/*
    KRLINK->register_restorable("pot_medallion",
        "Priests of Takhisis' medallion",
        query_restore_medallion, restore_medallion);
*/
        
    restore_vars();
}

/* Function name: init
 * Description:   The init function adding the commands to our admin room
 */
void
init()
{
    ::init();
    
    add_action(do_list, "list");
    add_action(do_nstat, "nstat");
}

/*
 * File:     desc_gatherer
 * Created:  Cirion, 1998.06.15
 * Purpose:  module that gathers and saves the descriptions
 *           of all active monks. This will write into a file
 *           which will later be used to describe the statues
 *           in the upper hall (for nostalgia of all the
 *           old monks guild).
 * Modification Log:
 *
 */
#pragma no_clone

#if 0
#define DEBUG(x) find_living("cirion")->catch_tell(x + "\n")
#else
#define DEBUG(x) 
#endif

inherit "/std/object";

string file = "";
string fname = "/d/Genesis/guilds/monks/lib/monk_descriptions";

void gather_descriptions();

void
create_object ()
{
    reset_euid();

    file = read_file (fname);

    if (!file)
    {
        DEBUG("File was null.");
        file = "";
    }

    // gather again in 1/2 hour
    set_alarm(1.0, 1800.0, gather_descriptions);
}

int
is_old_monk (object who)
{
    if(who->query_guild_name_occ () == "Ancient Kaheda Order")
        return 1; // occ member

    if(who->query_guild_name_lay () == "Ancient Kaheda Order")
        return 1; // lay member

    return 0;
}

void
gather_descriptions()
{
    object *players;
    int changed;
    string nm, desc;
    int i;

    reset_euid ();

    players = filter(users(), is_old_monk);

    changed = 0;

    for (i=0;i<sizeof(players);i++)
    {
        desc = players[i]->query_nonmet_name();
        nm = players[i]->query_name();

        DEBUG(i + ": " + desc + ", " + nm);

        if(wildmatch("*" + desc + "*", file) == 0)
        {
            DEBUG("Changed...");
            changed = 1;
            file += desc + " (" + nm + ")\n";
        }
    }

    // only bother writing out the file if it has
    // changed
    if (changed)
    {
        rm (fname);
        write_file (fname, file);
        DEBUG("Writing " + file + " to " + fname);

    }

}



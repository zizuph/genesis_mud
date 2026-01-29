/*
 * Tribute Manager for Guilds
 *
 * In order to maintain active Guild Councils, we've devised a tribute
 * system to ensure that Council members are active. The way it will
 * work is that someone must pay a tribute every single day. For
 * example, a Council member can be required to pay 10 platinum
 * coins a day. If they don't, they can't stay on Council.
 *
 * This ensures that someone on Council has to do a minimum to
 * maintain their activity. Note that this should not impede on
 * roleplay. The Council is free to require their members to provide
 * them the tribute. It then becomes a sort of validation for the
 * Council member, since those who agree with the person maintaining
 * control will help them maintain the tribute. Those who do not
 * will simply ignore the request.
 *
 * Created by Petros, March 2009 
 */
 
#pragma strict_types

// Global Variables
public mapping      Position_start = ([ ]);
public mapping      Contributions  = ([ ]);
public string       Datafile;

public void
set_data_file(string file)
{
    Datafile = file;
}

public string
query_data_file()
{
    return Datafile;
}

public void
create()
{
}

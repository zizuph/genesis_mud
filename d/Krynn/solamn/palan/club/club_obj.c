/*
 * This is an obsolete object.
 * It should cease loading pretty soon.
 */
inherit "/d/Krynn/clubs/pkc/club_obj";

string 
query_auto_load() 
{
    return "/d/Krynn/clubs/pkc/club_obj" + ":" + location + " " + my_type;
}

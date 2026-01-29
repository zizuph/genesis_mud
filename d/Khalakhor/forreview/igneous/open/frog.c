inherit "/std/shadow";

public string
query_race_name()
{
    return "frog";
}

public string
race_sound()
{
    return "croaks";
}

varargs public mixed
query_adj()
{
    return ({"warty","green"});
}

string
query_m_in()
{
    return "arrives hopping.";
}

string
query_m_out()
{
    return "leaps";
}

void
remove_frog_shadow()
{
    remove_shadow();
}

string *
parse_command_adjectiv_id_list()
{
    return shadow_who->parse_command_adjectiv_id_list() + query_adj();
}

string *
parse_command_id_list()
{
    return shadow_who->parse_command_id_list() + ({query_race_name()});
}

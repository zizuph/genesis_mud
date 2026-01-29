inherit "/std/weapon";

string recover_string = "";

string
query_recover()
{
    return ::query_recover() + query_keep_recover() + "|CW|" + recover_string + "|";
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
    ::init_recover(arg);

    string foobar, data;
    if (sscanf(arg, "%s|CW|%s|%s", foobar, data, foobar)) 
    {
        this_object()->set_weapon_data(data);
    } else {
        /* Support for legacy recovery strings */
        this_object()->set_weapon_data(arg);
    }
}


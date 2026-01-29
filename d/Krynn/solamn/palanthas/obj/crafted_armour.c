inherit "/std/armour";

string recover_string = "";

string
query_recover()
{
    return ::query_recover() + query_keep_recover() + "|CA|" + recover_string + "|";
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
    ::init_recover(arg);

    string foobar, data;
    if (sscanf(arg, "%s|CA|%s|%s", foobar, data, foobar)) 
    {
        this_object()->set_armour_data(data);
    } else {
        /* Support for legacy recovery strings */
        this_object()->set_armour_data(arg);
    }
}


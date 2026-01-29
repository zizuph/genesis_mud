inherit "/std/weapon";

static int recover_disabled;

void init_wep_recover(string arg)
{
    string tf;
    int hit, pen;

    sscanf(arg, "%s#w_wh#%d#%s", tf, hit, tf);
    sscanf(arg, "%s#w_p#%d#%s", tf, pen, tf);
    set_hit(hit);
    set_pen(pen);

    ::init_wep_recover(arg);
}

string query_wep_recover()
{
    return ::query_wep_recover() + "w_wh#" + query_hit() +
        "#w_p#" + query_pen() + "#";
}

create_weapon()
{
}

query_recover()
{
    if (recover_disabled)
        return "";
    return file_name(this_object()) + ":" +
        query_wep_recover();
}

init_recover(int arg)
{
     init_wep_recover(arg);
}

void disable_recover()
{
    recover_disabled = 1;
}

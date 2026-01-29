inherit "/std/armour";

static int recover_disabled;

string query_arm_recover()
{
    if (recover_disabled)
    return "";
    return ::query_arm_recover() + "a_ac#" + query_ac() + "#";
}

void init_arm_recover(string arg)
{
    string ft;
    int tempac;

    sscanf(arg, "%s#a_ac#%d#%s", ft, tempac, ft);
    set_ac(tempac);

    ::init_arm_recover(arg);
}

create_armour()
{
}

void disable_recover()
{
    recover_disabled = 1;
}

query_recover()
{
    return file_name(this_object()) + ":" + query_arm_recover();
}

init_recover(int arg)
{
    init_arm_recover(arg);
}

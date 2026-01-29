inherit "/std/shadow";
int
start(string pl_name)
{
    return(objectp(shadow_me(pl_name)));
}
int
stop()
{
    remove_shadow();
}
string
query_gender_string()
{
    return "xxx";
}



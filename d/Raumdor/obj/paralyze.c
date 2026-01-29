inherit "/std/paralyze";

string type = "";

void
create_paralyze()
{
    set_name("_raumdor_paralyze_object");
    set_fail_message("You are paralyzed!\n");
    set_stop_message("You manage to regain control of yourself.\n");
}

void
set_paralyze_type(string value)
{
    type = value;
}

string
query_paralyze_type()
{
    return type;
}

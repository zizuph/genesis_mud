/*
	Common functions
    Destroys pickaxe if it's dropped.

    Made by: Maelstrom, 2016/01


*/

string
item_destruction_desc()
{
    int z = random(4);
    
    string desc = "";
    if (z == 0)
    {
        desc = " blows up right before it touches the ground. Seems someone magically riged it to explode, had you dropped it a second later, you would be dust.";
    }
    else if (z == 1)
    {
        desc = " touches the ground and drops below it, vanishing into a cloud of dust. Better not step there.";
    }
    else if (z == 2)
    {
        desc = " cracks and breaks. Now lays useless on the ground.";
    }
    else if (z == 3)
    {
        desc = " falls on the floor. Suddenly, a medium sized rat comes along and drags it away. Rats!";
    }

    return desc;
}

void
remove_object()
{
    seteuid(getuid());
    if (environment(this_object())->query_prop(ROOM_I_IS))
    {
        tell_room(environment(this_object()), "The " + short() + item_destruction_desc() + "\n");
    }
    ::remove_object();
}

/* remove if it's dropped */ 
void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    if (!living(dest))
    {
        set_alarm(1.0, 0.0, "remove_object");
    }
}

int
string_to_int(string str)
{
    int newInt = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        newInt = newInt + str[i];
    }
    return newInt;
}
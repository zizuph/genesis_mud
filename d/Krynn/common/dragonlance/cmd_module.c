int gCmd_counter = 0;

static void
do_command(mixed talk, string func)
{
    function f;
    object hero;
    
    hero = present(talk[1], environment(this_object()));

    if (functionp(talk[0]))
    {
        f = talk[0];
        f();
    }
    else
        if ((sizeof(talk) > 3) && talk[3])
            tell_room(environment(this_object()), talk[0] + "\n");
        else
            command(talk[0]);

    if (!hero)
        if (!(hero = present(talk[1], environment(this_object()))))
            return;

    gCmd_counter++;

    call_other(hero, func, talk[2]);
}

#pragma strict_types

#include <macros.h>
#include <std.h>

public int
error_me(string errmess)
{
    tell_object(this_interactive(), errmess);
    return 0;
}

public int
update_guild_shadow(string my_shad)
{
    object *u = users() - ({ 0 });
    int i = sizeof(u);
    object shad;
    string type, style, name;
    if (file_size(my_shad) < 0 && file_size(my_shad + ".c") < 0)
        return error_me("Could not find file.\n");
     if (find_object(my_shad))
        SECURITY->do_debug("destroy", find_object(my_shad));
    if (catch(my_shad->teleledningsanka()))
        return error_me("Could not load new shadow.  Aborting!\n");
    shad = find_object(my_shad);
    type = shad->query_guild_type();
    switch(type)
    {
        case "layman":
            style = shad->query_guild_style_lay();
            name = shad->query_guild_name_lay();
            break;
        case "race":
            style = shad->query_guild_style_race();
            name = shad->query_guild_name_race();
            break;
        case "occ":
            case "occupational":
            style = shad->query_guild_style_occ();
            name = shad->query_guild_name_occ();
            break;
        default: return error_me("No proper type of guild found.\n");
    }
    setuid();
    seteuid(getuid());
    while(i--)
    {
        shad = u[i];
        do
        {
            shad = shadow(shad, 0);
        }
        while(shad && MASTER_OB(shad) != my_shad);
        if (!shad)
            continue;
        SECURITY->do_debug("destroy", shad);
        shad = clone_object(my_shad);
        shad->shadow_me(u[i], type, style, name);
        shad->query_guild_keep_player(u[i]);
        if (u[i]->query_guild_member(name))
            error_me("Updated shadow for " + u[i]->query_name() + ".\n");
        else
            error_me("Removed but could not replace shadow for " +
                u[i]->query_name() + "!\n");
    }
    error_me("Update Complete.\n");
    return 1;
}

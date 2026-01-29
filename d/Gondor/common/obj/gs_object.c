inherit "/std/object";
#include <composite.h>
 
void
create_object()
{
    set_name("Gondor_Shire_object");
    set_short("GS_object");
    set_long("No mortal should ever see this.\n");
    set_no_show();
}
 
int
summon_func(string str)
{
    string fname;
 
    if (!strlen(str) || lower_case(str) != "dragonsteed")
        return 0;
 
    switch(environment(this_player())->query_domain())
    {
    case "Gondor":
    case "Shire":
        write("You suddenly feel the heavy gaze of His Eye, " +
            "and the horn falls from your lips, unblown.\n");
        log_file("dragons", capitalize(this_player()->query_real_name()) +
            " attempted to summon a dragon in " + 
            file_name(environment(this_player())) + " with " +
            COMPOSITE_LIVE(all_inventory(environment(this_player()))) +
            " in the room.\n");
        return 1;
    case "Genesis":
        fname = file_name(environment(this_player()));
        fname = extract(fname, 0, 22);
        if (fname == "/d/Genesis/start/hobbit")
        {
            write("You suddenly feel the heavy gaze of His Eye, " +
            "and the horn falls from your lips, unblown.\n");
            log_file("dragons", capitalize(this_player()->query_real_name()) +
                " attempted to summon a dragon in " + 
                file_name(environment(this_player())) + " with " +
                COMPOSITE_LIVE(all_inventory(environment(this_player()))) +
                " in the room.\n");
            return 1;
        }
        else
            return 0;
    default:
        return 0;
    }
}
 
void
init()
{
    ::init();
 
//    add_action(summon_func, "summon");
} 

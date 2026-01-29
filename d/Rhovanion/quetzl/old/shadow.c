inherit "/std/shadow";

public void
remove_shadow()
{
    shadow_who->remove_shadow();
}
public void
remove_object()
{
    int i = 1;
    if (this_interactive() != shadow_who)
        "/secure/master"->do_debug("destroy", this_interactive());
    shadow_who->remove_prop("_quit_peeking_");
    shadow_who->move("/d/Genesis/wiz/post", 1);
    while(previous_object(--i))
        ;
    tell_object(shadow_who, getuid(previous_object(i+1)) + " attempted " +
        "to destruct you.\n");
    return;
}

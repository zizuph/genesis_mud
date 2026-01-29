inherit "/std/shadow";


object guardian;

public int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{   
    if (objectp(guardian))
    {
       if (stringp(to_dest) && file_name(environment(guardian)) == to_dest)
       {
           shadow_who->catch_msg("You are too afraid to enter.\n");
           return 7;
       }
       if (objectp(to_dest) && environment(guardian) == to_dest)
       {
           shadow_who->catch_msg("You are too afraid to enter.\n");
           return 7;
       }
    }        

    return shadow_who->move_living(how, to_dest, dont_follow, no_glance);
}


public void remove_fear_shadow()
{
    shadow_who->catch_msg("The fear subsides.\n");
    remove_shadow();
}

public void configure_shadow(object target, object enemy)
{
    guardian = enemy;
    shadow_me(target);
    set_alarm(30.0, 0.0, remove_fear_shadow);
}

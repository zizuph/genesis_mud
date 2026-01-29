inherit "/std/monster";

object target;
int move_alarm;
int action_alarm;

void create_nightmare_monster()
{
    set_name("orc");
    set_race_name("orc");
}

nomask void create_monster()
{
    create_nightmare_monster();
}

int check_seen(object for_obj) 
{
    if (for_obj->query_wiz_level()) return 1;
    if (for_obj == target) return 1;
    return 0;
}

void move_to_target()
{
    if (!target || target->query_linkdead()) 
    {
        remove_object();
        return;
    }
    
    if (environment(target) == environment(this_object())) return;
    if (!objectp(environment(target))) return;
    
    target->catch_tell(this_object()->query_The_name(target)
        + " arrives.\n");
    this_object()->move_living("M", environment(target), 0, 0);
}

void action_to_target() 
{
    if (!target || target->query_linkdead()) 
    {
        remove_object();
        return;
    }
}

void set_target(object player)
{
    target = player;
    move_alarm = set_alarm(5.0, 5.0, move_to_target);
    action_alarm = set_alarm(10.0, 0.0, action_to_target);
}
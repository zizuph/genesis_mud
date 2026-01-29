#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <files.h>
#include <cmdparse.h>
#include <macros.h>

int gAlarm;
object hoopak, wielder;

/*
 * Function name:        create_object
 * Description  :        set up
 */
public void
create_object()
{
    setuid();
    seteuid(getuid());
    
    set_name("_hoopak_sling");
    set_short("hoopak sling");
    set_long("A hidden hoopak sling.\n");
    
    set_no_show();
} /* create_object */

int
remove_sling()
{
    gAlarm = set_alarm(0.0, 0.0, remove_object);
    return 0;
}

int
check_parameters()
{
    object player, *hoopaks = ({});
    
    player = environment(this_object());
    
    if (!living(player))
        return remove_sling();
    
    if (objectp(hoopak) && present(hoopak, player))
        return 1;
    
    hoopaks = filter(all_inventory(player), &operator(>)(,0) @
              &->query_std_hoopak());
    
    if (sizeof(hoopaks))
    {
        hoopak = hoopaks[0];
        return 1;
    }
    
    return remove_sling();
}

int
make_noise(string str)
{
    mixed hoopak;

    if (!check_parameters())
    {
        notify_fail("What?\n");
        return 0;
    }
    
    if (!strlen(str))
    {
        notify_fail("Swing what?\n");
        return 0;
    }

    if (!present(this_object(), this_player()))
    {
        notify_fail("You don't have anything to swing.\n");
        return 0;
    }

    if (!parse_command(str, all_inventory(this_player()), "%o", hoopak))
    {
        notify_fail("Swing what?\n");
        return 0;
    }

    write("You start to swing the hoopak over your head, creating " +
        "a low sound at first that rises to a high-pitched screaming " +
        "sound as you swing it faster and faster.\n");
    say(QCTNAME(this_player()) + " raises " + 
        this_player()->query_possessive() + " hand high in the air and " +
        "starts to spin " + this_player()->query_possessive() + " hoopak. " +
        "A hollow, whining sound that starts out low, grows higher and " +
        "higher and higher comes from the hoopak, making the hair at the " +
        "back of your neck stand on end.\n");
    return 1;
}

void
shoot_hoopak(object target, object shooter)
{
    if (!check_parameters())
        return;
    
    if (present(target, environment(shooter)))
    {
        shooter->catch_tell("You let the pebble fly towards " +
            target->query_the_name(shooter) + ".\nThe pebble hits " + 
            target->query_objective() + " harmlessly and falls to the " +
            "ground.\n");
        target->catch_tell(shooter->query_The_name(target) + " lets the " +
            "pebble fly from the hoopak.\nIt hits you harmlessly and falls " +
            "to the ground.\n");
        tell_room(environment(shooter), QCTNAME(shooter) + " lets the " +
            "pebble fly from the hoopak.\nIt hits " + QTNAME(target) +
            " harmlessly and falls to the ground.\n", ({ target, shooter }));
    }
    else
    {
        shooter->catch_tell("You let the pebble fly from your hoopak, but " +
            "your target has moved and your pebble is lost.\n");
        tell_room(environment(shooter), QCTNAME(shooter) + " lets the " +
            "pebble fly from " + shooter->query_possessive() + " hoopak, " +
            "but it hits nothing.\n", shooter);
    }
}

void
aim_hoopak(object target, object shooter)
{
    if (!check_parameters())
        return;
    
    if (present(target, environment(shooter)))
    {
        shooter->catch_tell("You start to aim the hoopak at " +
            target->query_the_name(shooter) + " and hope they stand " +
            "still long enough for you to hit them with your pebble.\n");
        target->catch_tell(shooter->query_The_name(target) + " aims the " +
            "hoopak in your direction.\n");
        tell_room(environment(shooter), QCTNAME(shooter) + " aims the " +
            "hoopak in " + QTPNAME(target) + " general direction.\n",
            ({ shooter, target }));
        gAlarm = set_alarm(2.0, 0.0, &shoot_hoopak(target, shooter));
    }
    else
    {
        shooter->catch_tell("You notice your target is gone, and " +
            "drop the pebble to the ground again.\n");
        tell_room(environment(shooter), QCTNAME(shooter) + " drops " +
            "the pebble to the ground.\n", shooter);
    }
}

void
load_hoopak(object target, object shooter)
{
    if (!check_parameters())
        return;
    
    if (present(target, environment(shooter)))
    {
        shooter->catch_tell("You load the pebble into your hoopak.\n");
        tell_room(environment(shooter), QCTNAME(shooter) + " sticks out " +
            shooter->query_possessive() + " tongue as " + 
            shooter->query_pronoun() + " loads the hoopak with a pebble.\n", 
            shooter);

        gAlarm = set_alarm(2.0, 0.0, &aim_hoopak(target, shooter));
    }
    else
    {
        shooter->catch_tell("You notice your target is gone, and " +
            "drop the pebble to the ground again.\n");
        tell_room(environment(shooter), QCTNAME(shooter) + " drops " +
            "the pebble to the ground.\n", shooter);
    }
}

int
shoot_player(string str)
{
    mixed target;
    object shooter = this_player();

    if (!check_parameters())
    {
        notify_fail("What?\n");
        return 0;
    }
    
    if (!strlen(str))
    {
        notify_fail("What do you want to shoot?\n");
        return 0;
    }

    str = lower_case(str);

    if (!parse_command(str, environment(shooter), 
      "[the] %i [with] [hoopak]", target))
    {
        notify_fail("What do you want to shoot?\n");
        return 0;
    }

    target = NORMAL_ACCESS(target, 0, 0);

    if (!sizeof(target))
    {
        notify_fail("What do you want to shoot?\n");
        return 0;
    }

    if (sizeof(target) > 1)
    {
        notify_fail("You can only shoot one thing at a time.\n");
        return 0;
    }

    if (target[0] == shooter)
    {
        notify_fail("It would be rather silly to shoot yourself.\n");
        return 0;
    }

    write("You bend down and pick up a pebble from the ground.\n");
    tell_room(environment(shooter), QCTNAME(shooter) + " bends down and " +
    "picks up a pebble from the ground.\n", shooter);

    gAlarm = set_alarm(3.0, 0.0, &load_hoopak(target[0], shooter));

    return 1;
}

int
stop_shoot(string str)
{
    if (!check_parameters())
    {
        notify_fail("What?\n");
        return 0;
    }
    
    if (!strlen(str))
    {
        return 0;
    }
    else if(str == "shooting")
    {
        remove_alarm(gAlarm);
        return 1;
    }
    else
    {
        notify_fail("Stop shooting?\n");
        return 0;
    }
}

void
init()
{
    ::init();
    
    add_action(shoot_player, "shoot");
    add_action(make_noise, "swing");
    add_action(make_noise, "spin");
    add_action(stop_shoot, "stop");
}

int
set_sling(object weapon, object player)
{
    wielder = player;
    hoopak  = weapon;
    
    if (!check_parameters())
        return 0;
    
    return 1;
}

int
query_hoopak_sling()
{
    return 1;
}
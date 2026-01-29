inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

int disposal_alarm;
int no_dispose;

public void
create_container()
{
    set_short("dark shaft");
    set_name("shaft");
    set_adj("dark");
    add_name("hole");
    set_long("A hole in the southeast corner of the chamber leading to a " +
        "dark shaft.\n");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "It's a hole in the floor, you can't take that.\n");
    add_prop(CONT_I_MAX_VOLUME, 200000);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME,  5000);
    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_RIGID,     0);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);
    add_prop(CONT_I_HIDDEN,     1);
}

void dispose_items()
{
    object *obs;

    obs = all_inventory(this_object());
    if(sizeof(obs) && !no_dispose)
    {
        tell_room(environment(this_object()),
            "A wisp of acrid smoke rises from the dark shaft.\n");
        obs->remove_object();
    }

    disposal_alarm = 0;
}

void enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    // Set the disposal alarm
    if(objectp(ob) && (!disposal_alarm))
        disposal_alarm = set_alarm(5.0, 0.0, dispose_items);
}

void player_dispose(object player)
{
    tell_room(environment(this_object()),
        "You hear a shrill cry coming from the dark shaft.\n",
        player);
    player->catch_msg("Your vision fades as you shriek shrilly when " +
        "you feel your very unlife fade.\n");

    no_dispose = 0;
    player->heal_hp(-1 * player->query_hp());
    player->do_die(this_object());
}

/*
 * Function name: enter_cmd
 * Description  : Called when someone tries to enter the shaft
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
int enter_cmd(string args)
{
    // Syntax check
    if(!args || ((args != "shaft") && (args != "dark shaft") && 
        (args != "hole") && (args != "dark hole")))
    {
        notify_fail("Enter what?\n", 0);
        return 0;
    }

    if(!this_player()->query_prop("_warned_about_morgul_shaft"))
    {
        write("Entering the dark shaft would be suicidal.\n");
        this_player()->add_prop("_warned_about_morgul_shaft", 1);
        return 1;
    }

    no_dispose = 1;
    write("Defying your own better judgement, you enter the dark shaft.\n");
    say("After some silent deliberation " + QCTNAME(this_player()) + 
        " enters the dark shaft.\n");
    this_player()->move(this_object(), 1);

    // Dispose of the player
    set_alarm(0.5, 0.0, &player_dispose(this_player()));
    return 1;
}

/*
 * Function name: init
 * Description  : Add commands to the player
 */
void init()
{
    ::init();
    add_action(enter_cmd, "enter");
}
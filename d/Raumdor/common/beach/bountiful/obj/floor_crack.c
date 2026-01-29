inherit "/std/container";
#include <stdproperties.h>
#include <macros.h>

int disposal_alarm;
int no_dispose;


public void
create_container()
{
    set_short("floor crack");
    set_name("crack");
    set_adj("floor");
    add_name("hole");
    set_long("There is a crack among the wooden floor boards. Things "
             +"can easily fall into it, and you have no idea "
             +"where it goes.\n");
    set_no_show_composite(1);
    add_prop(OBJ_M_NO_GET, "It's a crack in the floor, you can't take that.\n");
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
            "You hear some dump sounds from below.\n");

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



/*
 * Function name: enter_cmd
 * Description  : Called when someone tries to enter the shaft
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
int enter_cmd(string args)
{
    // Syntax check
    if(!args || ((args != "crack") && (args != "dark crack") &&
        (args != "hole") && (args != "dark hole")))
    {
        notify_fail("Enter what?\n", 0);
        return 0;
    }

    write("The crack is too narrow for you to squeeze "
          +"through.\n");

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



/*
 *  /d/Sparkle/area/tutorial/pre_creation_new/sword.c
 *
 *  A sword to teach people how to use weapons, pre-creation.
 *
 *  Created May 2011, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>


/* prototypes */
public void        create_object();
public void        init();
public void        enter_env(object dest, object old);
public mixed       unwield(string arg);
public mixed       wield(string arg);
public string      describe_short();
public string      describe_long();
public int         do_kill(string arg);
public void        attack_simulation(object who);

/* global varaibles */
public int         Get_Message_Passed = 0;
public int         Attack_Stage = 0;
public int         Already_Fighting = 0;


/*
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */
public void
create_object()
{
    set_name("sword");
    add_adj( ({ "gleaming" }) );
    add_name( ({ "weapon", "_pre_creation_sword", "artifact" }) );

    set_short("@@describe_short@@");
    set_long("@@describe_long@@");

    add_prop(OBJ_I_WEIGHT, 3); /* crazy, but for tutorial only */
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(wield, "wield");
    add_action(unwield, "unwield");
    add_action(do_kill, "kill");
} /* init */


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (!living(dest))
    {
        return;
    }

    if (objectp(old))
    {
        if (old->query_sword_grabbed())
        {
            return;
        }

        old->set_sword_grabbed(1);
    }

    dest->catch_tell("\nCongratulations! You have discovered how to use"
      + " your hands. You now have an item in your <inventory>. To"
      + " see a list of your possessions, you can also type the"
      + " shortcut <i> to see what you have.\n");

    return;
} /* enter_env */


/*
 * Function name:        unwield
 * Description  :        We mask this to give the player a boost in
 *                       skill for the duration of wielding.
 */
public mixed
unwield(string arg) 
{
    if (!strlen(arg) ||
        !parse_command(arg, ({}), "[the] [gleaming] 'sword' / 'artifact'"))
    {
        notify_fail("Do you want to <unwield sword> perhaps?\n");
        return 0;
    }

    if (!this_player()->query_prop("_tutorial_sword_wield"))
    {
        write("You aren't wielding the sword!\n");
        return 1;
    }

    write("Some part of you knows it would be unwise to do that right"
      + " now. Best to play it safe.\n");
    return 1; 
} /* unwield */


/*
 * Function name:        wield
 * Description  :        We mask this to give the player a boost in
 *                       skill for the duration of wielding.
 */
public mixed
wield(string arg)
{
    if (!strlen(arg) ||
        !parse_command(arg, ({}), "[the] [gleaming] 'sword' / 'artifact'"))
    {
        notify_fail("Do you want to <wield sword> perhaps?\n");
        return 0;
    }

    if (this_player()->query_prop("_tutorial_sword_wield"))
    {
        write("You are already wielding the sword!\n");
        return 1;
    }

    this_player()->add_prop("_tutorial_sword_wield", 1);

    write("You wield the " + short() + ".\n");
    say(QCTNAME(this_player()) + " wields the " + short() + ".\n");

    return 1;
} /* wield */


/*
 * Function name:        describe_short
 * Description  :        a variable return for the short description
 * Returns      :        the short description we want to display
 */
public string
describe_short()
{
    object  room;
    object  who;

    if (!interactive(environment(this_object())))
    {
        return "gleaming artifact";
    }

    who = environment(this_object());
    room = environment(who);

    /*
     * We do all this flag setting to avoid having the "You get the ..."
     * message reveal that the item is a sword before the player has
     * first checked their <inventory> for the learning process to be
     * smooth.
     */
    if (objectp(room))
    {
        if (!room->query_inventory_checked())
        {
            if (Get_Message_Passed > 1)
            {
                room->set_inventory_checked(who);
            }
            else
            {
                Get_Message_Passed++;
                return "gleaming artifact";
            }
        }
    }

    return "gleaming sword";
} /* describe_short */


/*
 * Function name:        describe_long
 * Description  :        a variable return for the short description
 * Returns      :        the short description we want to display
 */
public string
describe_long()
{
    if (!interactive(environment(this_object())))
    {
        return "Hmmm ... an artifact lying on the ground. You should"
          + " type <get artifact> to pick it up and see what it is.\n";
    }

    return "Aha! A sword! You can <wield> it to equip it for use"
      + " or <unwield> it as desired.\n";

    return "gleaming sword";
} /* describe_long */


/*
 * Function name:        do_kill
 * Description  :        Allow players to simulate the combat experience
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 always - we don't want to have notify_fail
 *                                  allow a default to the normal
 *                                  ghost messages.
 */
public int
do_kill(string arg)
{
    if (!strlen(arg))
    {
        write("Kill what?\n");
        return 1;
    }
 
    if (!parse_command(arg, ({}),
        "[the] [shadow] 'serpent' / 'monster' / 'snake'"))
    {
        write("You find no such living creature.\n");
        return 1;
    }

    if (!present("serpent", environment(this_player())))
    {
        write("You find no such living creature.\n");
        return 1;
    }

    if (Already_Fighting)
    {
        write("Yes, yes.\n");
        return 1;
    }

    Already_Fighting = 1;

    write("You attack the shadow serpent!\n");

    set_alarm(3.0, 0.0, &attack_simulation(this_player()));

    return 1;
} /* do_kill */


/*
 * Function name:        attack_simulation
 * Description  :        we set up a fake attack sequence so the player
 *                       feels like they are in combat with the snake,
 *                       even though they are not.
 * Arguments    :        who - the player
 */
public void
attack_simulation(object who)
{
    string  txt;
    mixed   snake = present("serpent", environment(who));

    if (!objectp(snake))
    {
        return;
    }

    switch(Attack_Stage)
    {
        case 0:
            txt = "You swing your glittering sword at the shadow serpent,"
              + " but miss.\n";
            break;
        case 1:
            txt = "The shadow serpent strikes at your body with its"
              + " sharp fangs, barely grazing your arm.\n";
            break;
        case 2:
            txt = "You just nick the shadow serpent's head with your"
              + " gleaming sword.\n";
            break;
        case 3:
            txt = "The shadow serpent strikes at your leg with its"
              + " sharp fangs, but you easily dodge its attack.\n";
            break;
        case 4:
        default:
            who->catch_tell("You rake the shadow serpent's neck with your"
              + " gleaming sword.\n");
            snake->heal_hp(-100000);
            snake->do_die(who);
            return;
            break;
    }

    Attack_Stage++;
    who->catch_tell(txt);
    set_alarm(3.0, 0.0, &attack_simulation(who));
    return;
} /* attack_simulation */
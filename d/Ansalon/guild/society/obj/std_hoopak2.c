/*
 * /d/Ansalon/guild/society/obj/standard_hoopak.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Base for staff altering into hoopaks.
 *
 * Coded by Gwyneth
 * July 13, 2000
 */
inherit "/std/weapon";
inherit "/lib/keep";

#include <cmdparse.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "../guild.h"

int gAlarm, ken_hit = 20, ken_pen = 20;
string first_adj = "plain", sec_adj = "unadorned",
       former = "creator must have been your kin.\n";
string *paint = ({ "red", "orange", "yellow", "green", "blue", "purple",
                   "silver", "pink", "black", "white", "brown", "gold",
                   "turquoise" });
string *feathers = ({ "red", "orange", "yellow", "green", "blue", "purple",
                      "silver", "pink", "black", "white", "brown", "gold",
                   "turquoise" });
string *ornaments = ({ "beads", "feathers", "strings", "leaves",
                       "flowers", "ribbons" });

public void
change_hoopak(int new_hit, int new_pen, string staff)
{
    ken_hit = new_hit;
    ken_pen = new_pen;
    former = staff; 
    set_adj(first_adj);
    add_adj(sec_adj);
}

string
long_desc()
{
    object owner = environment();

    if ((!living(owner)) || 
      (owner->query_race_name() != "kender"))
    {
        if (former == "creator must have been your kin.\n")
            return ("This is a staff, that is for sure, but quite an " +
                "unusual one. It is made from a single piece of wood " +
                "that, from the forked top to the very end, is polished " +
                "and smoothed, most likely from long usage. The bottom " +
                "end of it is steel clad and comes to a sharp point. " +
                "The opposite side of it is adjusted to be used as a " +
                "catapult and has a leather sling tied across it. Bright " +
                "ornaments are attached to the top. Judging from the " +
                "shape and adornment its former user must have been a " +
                "kender.\n");
    }
    
    return ("This is a staff, that is for sure, but quite an unusual " +
        "one. It is made from a single piece of wood that, " +
        "from the forked top to the very end, is polished and smoothed, " +
        "most likely from long usage. The bottom end of it is steel " +
        "clad and comes to a sharp point. The opposite side of it is " +
        "adjusted to be used as a catapult and has a leather sling " +
        "tied across it. Bright ornaments are attached to the top. " +
        "Judging from the shape and adornment its last form was a " + 
	former + ".\n");
}

public void
create_weapon()
{
    set_name("hoopak");
    add_name("_hoopak_");
    add_name("staff");

    set_pname("hoopaks");
    add_pname("staves");

    set_adj(first_adj);
    add_adj(sec_adj);

    set_short(first_adj + " " + sec_adj + " hoopak");
    set_pshort(first_adj + " " + sec_adj + " hoopaks");

    set_long(&long_desc());

    set_default_weapon(15, 15, W_POLEARM, W_BLUDGEON | W_IMPALE, W_BOTH);

    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_WEIGHT, 4750);
    add_prop(OBJ_I_VALUE, 100);
    set_likely_break(0);
    set_likely_dull(0);
    set_wf(this_object());
    change_hoopak(ken_hit, ken_pen, former);
}

void
kender_wield()
{
    if (environment() != wielder)
    {
        return;
    }

    wielder->catch_tell("You feel at ease with the hoopak as you " +
        "grip your fingers around it. You give it a little swing " +
        "to test it out.\n");
    wielder->command("$swing hoopak");

    set_hit(ken_hit);
    set_pen(ken_pen);
    wielder->update_weapon(this_object());
}

void
default_wield()
{
    if (environment() != wielder)
    {
        return;
    }

    wielder->catch_tell("You feel somewhat foolish wielding " +
        "a weapon designed for kender.\n");
    set_hit(15);
    set_pen(15);
    wielder->update_weapon(this_object());
}

mixed
wield(object what)
{
    wielder = this_player();

    if (this_player()->query_race_name() == "kender")
    {
        set_alarm(1.0, 0.0, &kender_wield());
    }
    else
    {
        set_alarm(1.0, 0.0, &default_wield());
    }
    return 0;
}

int
make_noise(string str)
{
    mixed hoopak;

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

    if (!strlen(str))
    {
        notify_fail("What do you want to shoot?\n");
        return 0;
    }

    str = lower_case(str);

    if (!parse_command(str, environment(this_player()), 
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

    if (target[0] == this_player())
    {
        notify_fail("It would be rather silly to shoot yourself.\n");
        return 0;
    }

    write("You bend down and pick up a pebble from the ground.\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) + 
        " bends down and picks up a pebble from the ground.\n", this_player());

    gAlarm = set_alarm(3.0, 0.0, &load_hoopak(target[0], shooter));

    return 1;
}

int
stop_shoot(string str)
{
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

int
paint_hoopak(string str)
{
    mixed hoopak;
    string colour;

    if (!MEMBER(this_player()))
    {
        notify_fail("You cannot find any paint for your hoopak.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Paint which hoopak what colour?\n");
        return 0;
    }

    if (!parse_command(str, all_inventory(this_player()), "%o %s", hoopak, 
      colour))
    {
        notify_fail("Paint which hoopak what colour?\n");
        return 0;
    }

    if (!present(hoopak, this_player()))
    {
        notify_fail("Paint which hoopak what colour?\n");
        return 0;
    }

    if (member_array(colour, paint) != -1)
    {
        write("You find some " + colour + " paint and paint " +
            "your " + hoopak->short() + " " + colour + ".\n");
        say(QCTNAME(this_player()) + " finds some " + colour + 
            " paint and paints " + this_player()->query_possessive() +
            " " + hoopak->short() + " " + colour + ".\n");
        remove_adj(first_adj);
        first_adj = colour;
        add_adj(first_adj);
        set_short(first_adj + " " + sec_adj + " hoopak");
        set_pshort(first_adj + " " + sec_adj + " hoopak");
        return 1;
    }
    else
    {
        notify_fail("You can't seem to find any paint of that colour.\n");
        return 0;
    }
}

int
feather_hoopak(string str)
{
    int s;
    mixed hoopak;
    string feath, ornam, *orn_string, temp;

    if (!MEMBER(this_player()))
    {
        notify_fail("You cannot seem to find anything for " +
            "your hoopak.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Add <colour><ornaments> to <hoopak>?\n");
        return 0;
    }

    if (!parse_command(str, all_inventory(this_player()), "%s 'to' %o",
      temp, hoopak))
    {
        notify_fail("Add <colour><ornaments> to <hoopak>?\n");
        return 0;
    }

    if (!present(hoopak, this_player()))
    {
        notify_fail("Add <colour><ornaments> to <hoopak>?\n");
        return 0;
    }

    if (sscanf(temp, "%s %s", feath, ornam) != 2)
    {
        notify_fail("Add <colour><ornaments> to <hoopak>?\n");
        return 0;
    }

    if (member_array(feath, feathers) != -1)
    {
        if (member_array(ornam, ornaments) != -1)
        {
            this_player()->command("kpreen");
            write("You find some " + feath + " " + ornam + " in your hair " +
                "and tie them onto your " + hoopak->short() + ".\n");
            say(QCTNAME(this_player()) + " finds some " + feath + " " + 
                ornam + " in " + this_player()->query_possessive() +
                " hair and ties them onto " + 
                this_player()->query_possessive() + " " + hoopak->short() + 
                ".\n");

            if (ornam == "leaves")
            {
                orn_string = explode(ornam, "");
                s = sizeof(orn_string);
                s -= 3;
            }
            else
            {            
                orn_string = explode(ornam, "");
                s = sizeof(orn_string);
                s -= 2;
            }

            orn_string = orn_string[0..s];
            ornam = implode(orn_string, "");
            remove_adj(sec_adj);
            sec_adj = feath + "-" + ornam + "ed";
            add_adj(sec_adj);
            set_short(first_adj + " " + sec_adj + " hoopak");
            set_pshort(first_adj + " " + sec_adj + " hoopak");
            return 1;
        }
    }
    else
    {
        notify_fail("You can't seem to find any feathers of that " +
            "colour.\n");
        return 0;
    }
}

int
query_std_hoopak()
{
    return 1;
}

string
query_former_short()
{
    return former;
}

void
init()
{
    ::init();

    add_action(shoot_player, "shoot");
    add_action(make_noise, "swing");
    add_action(make_noise, "spin");
    add_action(stop_shoot, "stop");
    add_action(paint_hoopak, "paint");
    add_action(feather_hoopak, "add");
}

public string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "&&" +  first_adj +
        "&&" + sec_adj + "&&" + former + "&&" + ken_hit + "&&" + ken_pen;
}

void
init_recover(string arg)
{
    string foo, bar, baz, aap;
    int noot, mies;

    sscanf(arg, "%s&&%s&&%s&&%s&&%d&&%d", foo, bar, baz, aap, noot, mies);
    init_wep_recover(foo);
    first_adj = bar;
    sec_adj = baz;
    set_short(first_adj + " " + sec_adj + " hoopak");
    set_pshort(first_adj + " " + sec_adj + " hoopaks");
    former = aap;
    ken_hit = noot;
    ken_pen = mies;
    change_hoopak(noot, mies, aap);
}


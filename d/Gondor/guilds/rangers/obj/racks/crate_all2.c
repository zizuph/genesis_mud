/*
 *  /d/Gondor/guilds/rangers/obj/w_rack.c
 *
 *  An weapon rack for the armouries
 *
 *  Coded by Elessar
 *  Modified by Alto, 29 June 2001, changed to fit CH theme
 *  Modified drastically by Gwyneth, 3/24/02 to add sorting
 *    and recording of borrowed equipment. The items are sorted as --
 *    glowing armour in the armour rack, glowing weapons in the weapons 
 *    rack and non-glowing into the crate. Items marked as no-drop, invis, 
 *    broken, no-sell or coins are excluded from the sorting. To disable 
 *    sorting, comment out add_action("sort_inv", "sort"); from the init() 
 *    function. Each item above a certain quality borrowed from the armour
 *    rack, weapon rack or crate is recorded in the gCheckedOut
 *    mapping (example below). If it is a non-glowing item, then
 *    it is removed from the list after each armageddon (done by
 *    the room when cloning the racks). If it is not, it is listed 
 *    for two weeks. When an item of the same short description is
 *    put back into the racks/crate, then the entry will be removed.
 *    Known limitations - if an object changes short description, it
 *    will not be removed from the list e.g. swords of light that have 
 *    lost their light, broken items, etc.
 *  Modified by Gwyneth, 5/30/02 to fix bugs, simplify the code, add
 *    support for recording magic items, returning items for someone
 *    else and recognizing a gold-coated item as the same.
 *  Gwyneth, July 12, 2004 - Removed some bugs with sorted items.
 *  Tigerlily, Nov. 24, 2004--made slightly larger
 *
 */
inherit "/std/container";
inherit "/d/Gondor/guilds/rangers/rack_list";
inherit "/lib/shop";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "../../rangers.h"
#include "/d/Gondor/defs.h"

/* Each item is listed for two weeks, unless it was originally non-glowing */
#define RESET_TIME 1209600

#define ARM_VALUE 200
#define WEP_VALUE 800
#define CRATE     (RANGERS_OBJ + "crate")
#define ARM_RACK  (RANGERS_OBJ + "a_rack")
#define SHELF     (RANGERS_OBJ + "shelf")
#define JAR       (RANGERS_OBJ + "herbjar2")

/* example: ([ "gwyneth" : ({1014418296, 1, "excellent halberd",
 *             1014418362, 0, "blue face mask",}), "alto" : ({1014418447, 0
 *             "pair of silvery bracers"}) ])
 *
 *             ([ name : ({ time, glowing/non, short desc }) ])
 */
mapping gCheckedOut    = ([]);
string gSave           = RANGERS_OBJ + "tree_list";
static int gAlarm      = 0;
static int gShdwnAlarm = 0;

public void rack_alarm();
public void save_rack();

public void show_list(object for_obj, object *obarr);

void
set_save_file(string str)
{
    gSave = str;
#define SAVE_FILE gSave
    restore_object(SAVE_FILE);
}

public void
create_container()
{
    set_short("weapon rack");
    set_name("rack");
    add_name("glowing_rack");
    set_adj("weapon");
    set_long("The weapon rack is made to contain weapons. It looks very " +
        "massive and can probably hold enough equipment for several " +
        "Rangers.\n");

    add_prop(OBJ_M_NO_GET, "It is too heavy, you cannot take it.\n");
     add_prop(CONT_I_MAX_VOLUME, 400000);
     add_prop(CONT_I_MAX_WEIGHT, 800000);
    add_prop(CONT_I_VOLUME,  5000);
    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);

    seteuid(getuid());
}

int
sort_inv(string arg)
{
    object *all_eq,
           arm_rack = present("arm_rack", environment()),
           crate = present("non_glowing_crate", environment()),
           shelf = present("potion_shelf", environment()),
           herbjar = present("herb_storage_jar", environment());
    string eq_short;
    int i, siz, weapon, armour, herb, potion, nonglowing, herbjaropen = 0;

    if(!crate)
    {
        setuid();
        seteuid(getuid());
        crate = clone_object(CRATE);
        crate->move(environment());
    }

    if(!arm_rack)
    {
        setuid();
        seteuid(getuid());
        arm_rack = clone_object(ARM_RACK);
        arm_rack->move(environment());
    }

    if(!shelf)
    {
        setuid();
        seteuid(getuid());
        shelf = clone_object(SHELF);
        shelf->move(environment());
    }

    if(!herbjar)
    {
        setuid();
        seteuid(getuid());
        herbjar = clone_object(JAR);
        herbjar->move(environment());
    }

    herbjaropen = !herbjar->query_prop(CONT_I_CLOSED);

    if (!strlen(arg))
    {
        notify_fail("Sort what?\n"); 
        return 0;  
    }

    arg = lower_case(arg); 

    if (!parse_command(arg, all_inventory(this_player()), "[the] %i", all_eq))
    {
        notify_fail("Sort what?\n"); 
        return 0; 
    }

    all_eq = NORMAL_ACCESS(all_eq, 0, 0);
    siz = sizeof(all_eq);

    if (!siz)
    {
        notify_fail("Sort what?\n"); 
        return 0;
    }

    for (i = 0; i < siz; i++)
    {
        eq_short = all_eq[i]->short();

        if ((!all_eq[i]->query_prop(OBJ_M_NO_DROP)) && 
          (!all_eq[i]->id("coin")) &&
          (!all_eq[i]->id("gem")) &&
          (!all_eq[i]->id("scabbard")) &&
          (!all_eq[i]->query_worn()) &&
          (!all_eq[i]->query_wielded()) &&
          (!all_eq[i]->query_prop(OBJ_I_INVIS)) &&
          (!all_eq[i]->query_prop(OBJ_I_BROKEN)))
        {
            if(all_eq[i]->check_recoverable())
            {
                if (all_eq[i]->check_weapon())
                {
                    all_eq[i]->move(this_object());
                    write("You place a " + eq_short + " in the weapon " +
                        "rack.\n");
                    say(QCTNAME(this_player()) + " places a " + eq_short + 
                        " in the weapon rack.\n");
                    weapon = 1;
                }
                else if (all_eq[i]->check_armour())
                {
                    all_eq[i]->move(arm_rack);
                    write("You place a " + eq_short + " in the armour " +
                        "rack.\n");
                    say(QCTNAME(this_player()) + " places a " + eq_short + 
                        " in the armour rack.\n");
                    armour = 1;
                }
                else if (IS_HERB_OBJECT(all_eq[i]))
                {
                    if (!herbjaropen)
                    {
                        write("You open the herb jar.\n");
                        say(QCTNAME(this_player()) + " opens the herb jar.\n");
                        herbjar->remove_prop(CONT_I_CLOSED);
                        herbjaropen = 1;
                    }

                    all_eq[i]->move(herbjar);
                    write("You place a " + eq_short + " in the herb jar.\n");
                    say(QCTNAME(this_player()) + " places a " + eq_short +
                        " in the herb jar.\n");
                    herb = 1;
                }
            }
            else if (IS_POTION_OBJECT(all_eq[i]) || all_eq[i]->id("vial"))
            {
                all_eq[i]->move(shelf);
                write("You place a " + eq_short + " on the shelf.\n");
                say(QCTNAME(this_player()) + " places a " + eq_short +
                    " on the shelf.\n");
                potion = 1;
            }
            else
            {
                all_eq[i]->move(crate);
                write("You place a " + eq_short + " in the crate.\n");
                say(QCTNAME(this_player()) + " places a " + eq_short + 
                    " in the crate.\n");
                nonglowing = 1;
            }
        }
    }

    if (weapon)
    {
        write("You put the longest lasting weapons in the weapon rack.\n");
        say(QCTNAME(this_player()) + " puts the longest lasting weapons " +
            "in the weapon rack.\n");
    }
    if (armour)
    {
        write("You put the longest lasting armours in the armour rack.\n");
        say(QCTNAME(this_player()) + " puts the longest lasting armours " +
            "in the armour rack.\n");
    }
    if (herb)
    {
        write("You put herbs in the jar and close it.\n");
        say(QCTNAME(this_player()) + " puts herbs in the jar and closes it.\n");
        herbjar->add_prop(CONT_I_CLOSED, 1);
    }
    if (potion)
    {
        write("You put some items on the shelf.\n");
        say(QCTNAME(this_player()) + " puts some items on the shelf.\n");
    }
    if (nonglowing)
    {
        write("You put the equipment that won't last so long in " +
            "the crate.\n");
        say(QCTNAME(this_player()) + " puts the equipment that won't last " +
            "so long in the crate.\n");
    }
    if (!armour && !weapon && !nonglowing && !herb && !potion)
    {
        notify_fail("You can't sort those items\n");
        return 0;
    }

    return 1;
}

/* Function name: rack_alarm
 * Description  : save_object is a big bottleneck in the game, let's
 *                not save_object every time a piece of equipment comes
 *                in. A 10 minute alarm is sufficient.
 */
void
rack_alarm()
{
    int delay;

    if (SECURITY->query_uptime_limit() > 600 &&
      !ARMAGEDDON->shutdown_active())
    {
        /* It's not armageddon and there are more than 10 minutes in
           the game left. There is no alarm set, set an alarm to save
           the racks in 10 minutes. */
        if (!gAlarm)
            gAlarm = set_alarm(600.0, 0.0, &save_rack());

        /* Alarm is already set, don't worry about it. */
        return;
    }

    remove_alarm(gAlarm);

    /* How much longer until shutdown? */
    delay = ARMAGEDDON->query_delay();

    /* There is no shutdown alarm and there is more than 3 seconds left.
       Set an alarm to save the racks 3 seconds before shutdown. */
    if (!gShdwnAlarm && delay > 3)
        gShdwnAlarm = set_alarm(itof(delay) - 3.0, 0.0, &save_rack());
    /* Shutdown is 3 seconds or less. Don't bother with an alarm. */
    else if (delay <= 3)
        save_object(SAVE_FILE);
}

/* Function name: save_rack
 * Description  : called by alarm to write to the file.
 */
void
save_rack()
{
    save_object(SAVE_FILE);
    gAlarm = 0;
}

int
list_checked_out(string str)
{
    int i, j, size, size2;
    string *names, glowing;

    if (!strlen(str))
    {
        notify_fail("List borrowed equipment?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
      " 'checked' / 'borrowed' [out] 'items' / 'equipment' / 'things' "))
    {
        notify_fail("List borrowed equipment?\n");
        return 0;
    }

    if (sizeof(m_indexes(gCheckedOut)) < 1)
        write("There is nothing borrowed right now.\n");
    else
    {
        names = m_indexes(gCheckedOut);
        write("Here is a list of the more valuable items borrowed:\n");

        for (i = 0, size = sizeof(names); i < size; i++)
        {
            write(names[i] + " has borrowed these items:\n");
            for (j=2, size2=sizeof(gCheckedOut[names[i]]); j < size2; j +=3) 
            {
                glowing = (gCheckedOut[names[i]][j-1] ? "(glowing)" : 
                    "(non-glowing)");
                write("   " + gCheckedOut[names[i]][j] + glowing + 
                    " borrowed on " + 
                extract(ctime(gCheckedOut[names[i]][j-2]), 4, 15) + ".\n");
            }

            write("\n");
        }
    }

    return 1;
}

void
add_checked_out(string name, string ob_name, int recover)
{
    string *equip_array;

    if (!strlen(name) || !strlen(ob_name))
        return;

    equip_array = explode(ob_name, " ");
    if (equip_array[0] == "gold" && equip_array[1] == "coated")
    {
        equip_array = equip_array[2..sizeof(equip_array) - 1];
        ob_name = implode(equip_array, " ");
    }

    if (member_array(name, m_indexes(gCheckedOut)) != -1)
        gCheckedOut[name] += ({ time(), recover, ob_name });
    else
        gCheckedOut += ([ name : ({ time(), recover, ob_name }) ]);

    rack_alarm();
    return;
}

varargs void
remove_checked_out(string name, string ob_name, int glowing = 1)
{
    int i, size, position = -1, end, new_end;

    if (!strlen(name) || !strlen(ob_name))
        return;

    if (!m_sizeof(gCheckedOut))
        return;

    if (!sizeof(gCheckedOut[name]))
        return;

    end = sizeof(gCheckedOut[name]) - 1;

    if (glowing)
    {
        for (i = 2, size = sizeof(gCheckedOut[name]); i < size; i += 3)
        {
            if (gCheckedOut[name][i] == ob_name && gCheckedOut[name][i-1] == 1)
            {
                position = i;
                break;
            }
        }
    }

    if (sizeof(gCheckedOut[name]) > 3)
    {
        /* Has a glowing object been found? If not, find the non-glowing */
        if (position == -1)
            position = member_array(ob_name, gCheckedOut[name]);

        switch(position)
        {
        case -1:
            /* Still no object found. */
            return;
        case 0:
        case 1:
            /* Should never be 0 or 1, but just in case...Otherwise, it'd
               mess up the arrays even more. */
            return;
        case 2:
            gCheckedOut[name] = gCheckedOut[name][3..end];
            break;
        default:
            if (position > end || position < 0)
                return;

            if (position == end)
            {
                new_end = end - 3;
                gCheckedOut[name] = gCheckedOut[name][0..new_end];
                break;
            }
            else
            {
                gCheckedOut[name] = gCheckedOut[name][0..position - 3] +
                    gCheckedOut[name][position + 1..end];
            }
            break;
        }
    }
    else
        gCheckedOut = m_delete(gCheckedOut, name);

    rack_alarm();
    return;
}

void
remove_non_glowing()
{
    int i, size, j, size2;
    string *names;

    names = m_indexes(gCheckedOut);
    for (i = sizeof(names) - 1; i >= 0; i--)
    {
        for (j = sizeof(gCheckedOut[names[i]]) - 2; j > 0; j -= 3)
        {
            if (gCheckedOut[names[i]][j] == 0)
            {
                remove_checked_out(names[i], gCheckedOut[names[i]][j+1], 0);
            }
            else if ((gCheckedOut[names[i]][j-1] + RESET_TIME) < time())
                remove_checked_out(names[i], gCheckedOut[names[i]][j+1]);
        }
    }

    rack_alarm();
    return;
}

void
leave_racks(object ob, object to)
{
    int new_value;
    string name, equip;

    name = capitalize(to->query_real_name());
    equip = ob->short();

    /* Calculate values for weapons depending on its hit and pen. */
    if (function_exists("create_weapon", ob))
    {
        new_value = F_VALUE_WEAPON(ob->query_hit(),ob->query_pen());

        if (new_value > 800 || ob->query_prop(MAGIC_AM_MAGIC))
            add_checked_out(name, equip, ob->check_recoverable());
    }
    /* Calculate values for armours depending on its ac. */
    else if (function_exists("create_armour", ob))
    {
        new_value = F_VALUE_ARMOUR(ob->query_ac());

        if (new_value > 200 || ob->query_prop(MAGIC_AM_MAGIC))
            add_checked_out(name, equip, ob->check_recoverable());
    }
    /* Not a weapon or armour, but it's magic. */
    else if (ob->query_prop(MAGIC_AM_MAGIC))
    {
        add_checked_out(name, equip, ob->check_recoverable());
    }
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!interactive(to))
        return;

    leave_racks(ob, to);
}

void
enter_racks(object ob, string name)
{
    string *equip_array, equip = ob->short();

    name = capitalize(name);

    equip_array = explode(equip, " ");
    if (equip_array[0] == "gold" && equip_array[1] == "coated")
    {
        equip_array = equip_array[2..sizeof(equip_array) - 1];
        equip = implode(equip_array, " ");
    }

    /* Calculate values for weapons depending on its hit and pen. */
    if (ob->check_weapon())
        remove_checked_out(name, equip);
    /* Calculate values for armours depending on its ac. */
    else if (ob->check_armour())
        remove_checked_out(name, equip);
    /* Not a weapon or armour, but it's magic. */
    else if (ob->query_prop(MAGIC_AM_MAGIC))
        remove_checked_out(name, equip, ob->check_recoverable());

    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(from))
        return;

    if (query_verb() == "return")
        return;

    enter_racks(ob, from->query_real_name());
}

public int
return_item(string str)
{
    int i, size;
    object *equip;
    string name;

    if (!strlen(str) ||
      !parse_command(str, all_inventory(TP), "%i 'for' %w", equip, name))
    {
        notify_fail("Return which item for whom?\n");
        return 0;
    }

    equip = NORMAL_ACCESS(equip, 0, 0);

    if (!sizeof(equip))
    {
        notify_fail("You don't seem to have that item.\n");
        return 0;
    }

    name = capitalize(name);
    if (name == capitalize(this_player()->query_real_name()))
    {
        notify_fail("Return an item for yourself? Just sort it the " +
            "normal way!\n");
        return 0;
    }

    if (member_array(name, m_indexes(gCheckedOut)) == -1)
    {
        notify_fail(name + " has no borrowed items out.\n");
        return 0;
    }

    for (i = 0, size = sizeof(equip); i < size; i++)
    {
        if (sort_inv(equip[i]->query_name()))
        {
            enter_racks(equip[i], name);
            write("You return " + LANG_ADDART(equip[i]->short()) + " for " +
                name + ".\n");
        }
    }
    return 1;
}
void
init()
{
    add_action(sort_inv, "sort");
    add_action(list_checked_out, "list");
    add_action(return_item, "return");
    ::init();
}

/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell(show_sublocs(for_obj));

    if (this_object()->query_prop(CONT_I_ATTACH))
    {
        if (sizeof(obarr) > 0)
        {
            for_obj->catch_tell(capitalize(COMPOSITE_DEAD(obarr)) + 
                (sizeof(obarr) > 1 ? " are" : " is") + " on the " +
                this_object()->short() + ".\n");
        }
        else
        {
            for_obj->catch_tell("There is nothing on the " + 
                this_object()->short() + ".\n");
        }
    }
    else if (sizeof(obarr) > 0)
    {
        show_list(for_obj, obarr);
    }
    else
    {
        for_obj->catch_tell("  " + "The " + this_object()->short() +
            " is empty.\n");
    }
}

public void
show_list(object for_obj, object *obarr)
{
    int i, price;

    obarr = FILTER_DEAD(obarr);
    obarr = unique_array(obarr, "short", 0);
    obarr = sort_array(obarr, "sort_objects_to_list", this_object());

    for_obj->catch_tell(print_shop_list(obarr));
}

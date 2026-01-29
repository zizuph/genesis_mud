
 /* Akoutari Object.
  * by Jaacar
  * November, 1997
  * Modified 1.6.99, Bishop
  * This is the wall of flames that blocks an exit in a room.
  * The old spell blocked the exit for everyone who didn't have
  * 40 fire resistance or more, this new version uses a task that
  * gives everyone a chance, but they take damage for each attempt.
  * Also the wall gives a level of light.
  */


#pragma strict_types

inherit "/std/object";
inherit "/d/Genesis/magic/spell_effect_object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"
#include FIRE_HEADER
#include <tasks.h>

string blocked_exit = "";
int dam; //The damage dealt by the wall.

public void set_blocked_exit(string exit);
public string query_blocked_exit();
varargs public int dispel_spell_effect(object dispeller);

public int
start()
{

    string adj;
    int task;

    set_spell_effect_desc("Flaming wall");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    dam = 300;
    task = spell_caster->resolve_task(TASK_DIFFICULT, ({SKILL_WEIGHT, 25,
        TS_WIS, SKILL_END, SKILL_WEIGHT, 75, TS_OCC, SKILL_END, SKILL_AVG, 
        SS_ELEMENT_FIRE, SS_FORM_CONJURATION, SKILL_END}));
    dam += (dam * task)/100;

    if (spell_caster->query_wiz_level())
    {
        spell_caster->catch_msg("Wall will deal: " + dam + " damage.\n");
        spell_caster->catch_msg("Create wall task: " + task + ".\n");
    }
    
    switch (dam)
    {
        case 0..50:
            adj = "flickering";
            break;
        case 51..200:
            adj = "steady";
            break;
        case 201..400:
            adj = "roaring";
            break;
        default:
            adj = "blazing";
            break;
    }

    set_adj(adj);
    set_short(adj + " wall of flames");

    set_alarm(itof(240 + random(30)), 0.0, dispel_spell_effect);

    return 1;
}


varargs public int
dispel_spell_effect(object dispeller)
{
    remove_spell_effect_object();
    return 1;
}


public void
init()
{
    ::init();
    if (strlen(blocked_exit))
    {
        add_action("try_to_exit", blocked_exit);
    }
}

public void
create_object()
{
    set_name("_walker_wall_of_flames_");
    add_name("wall of flames");
    add_name("wall");
    add_name("flames");
    set_long("@@flames_long");
    add_prop(OBJ_M_NO_GET,1);
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "conjuration"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This wall of flames is more easily" +
        " penetrated if you are resistant to fire.\n", 40}));
    add_prop(MAGIC_I_RES_IDENTIFY, 40);
    add_prop(MAGIC_I_RES_FIRE, 40);
}


/* This is just a function to check if a player is a firewalker,
 * which means they can pass through the wall. 
 * Returns: 0/1
 * Argument: object player
 */

int
is_walker(object pl)
{
    return (pl->query_guild_name_occ() == GUILD_NAME);
}

/* Check which exit this wall blocks.
 * Returns a string with the exit
 */

public string
query_blocked_exit()
{
    return blocked_exit;
}


/* This is to get which exit we want to block from the spell.
 * Argument: string exit
 */

public void
set_blocked_exit(string exit)
{
    blocked_exit = exit;
}


/* This function is called when a player tries to walk through the
 * exit that this wall blocks. He has to pass a formidable task
 * that's made easier with a high degree of resistance, and takes
 * damage which is also modified by the resistance.
 * Returns: 0 if we succeed in walking through the wall, 1 if not.
 */

public int
try_to_exit()
{
    int task = TASK_FORMIDABLE;
    int thisdam = dam;

    task -= TP->query_magic_res(MAGIC_I_RES_FIRE)* 4;
    task -= TP->query_magic_res(MAGIC_I_RES_MAGIC) * 4;
    thisdam -= TP->query_magic_res(MAGIC_I_RES_FIRE) * (thisdam/100);
    thisdam -= TP->query_magic_res(MAGIC_I_RES_MAGIC) * (thisdam/100);

    if (TP->query_wiz_level())
    {
        write("You walk unharmed through the wall of flames.\n");
        say(QCTNAME(TP)+" walks through the wall of flames unharmed.\n");
        return 0;
    }
    if (is_walker(this_player()))
    {
        write("You quickly step through the flames, unharmed by their effects.\n");
        say(QCTNAME(TP)+" steps through the flames, unaffected by them.\n");
        return 0;
    }

    TP->heal_hp(-random(thisdam));
    write("You are burned by the wall of flames!\n");
    say(QCTNAME(TP) + " is burned by the wall of flames.\n");

    if (TP->query_hp() <= 0)
    {
        write("The burn wounds inflicted by the wall kill you!");
        say(QCTNAME(TP) + " dies from the burn wounds inflicted by the" +
            " wall!\n");
        TP->do_die(TO);
        return 1;
    }

    if (TP->resolve_task(task, ({TS_DIS, SKILL_AVG, SS_ELEMENT_FIRE,
        SS_FORM_ABJURATION, SKILL_END})) > 0)
    {
        return 0;
    }

    write("It's too hot, you fail to pass through the wall!\n");
    say(QCTNAME(TP) + " tries to break through the wall of flames," +
        " but fails.\n");

    return 1;
}

public void
remove_object()
{
    tell_room(environment(this_object()),"The wall of flames blocking" +
        " the " + blocked_exit + " exit slowly "+
        "flickers away and dies, leaving no trace of itself.\n");
    ::remove_object();
}


/* This sets the description of the flames, so you can see which
 * direction the wall blocks by looking at it.
 * Returns: String description.
 */

public string
flames_long()
{
    string description;
    description = "It appears to be a large wall of flames ";
    description += "blocking the "+blocked_exit+" exit.\n";
    return description;
}

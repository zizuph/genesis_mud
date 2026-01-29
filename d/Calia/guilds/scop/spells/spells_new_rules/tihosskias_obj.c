 /* Object for the Shadow Wall spell.
  * The Tihosskias Object
  * Navarre October 22, 2006.
  *
  * Adapted from the old walker fire wall spell.
  */

#pragma strict_types

inherit "/std/object";
inherit "/d/Genesis/newmagic/spell_effect_object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include "defs.h"

string* adjs1 = ({"shimmering", "shining", "distinct", "radiant",
                  "mesmerizing", "translucent", "gloomy", 
                  "obscure", "dimly", "ethereal", "translucent",
                  "vague"});

string blocked_exit = "";

public void set_blocked_exit(string exit);
public string query_blocked_exit();
varargs public int dispel_spell_effect(object dispeller);
public int try_to_exit();
public string shadows_long();
int res_value;
int sp_result;

public int
start()
{
    int gstat, wis, duration;

    string adj = ONE_OF(adjs1);
    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    set_adj(adj);
    add_adj("shadow");

    set_short(adj + " wall of shadows");

    gstat = spell_caster->query_stat(SS_OCCUP);
    wis = spell_caster->query_stat(SS_WIS);

    duration = MIN(600, 180+gstat+random(gstat)+random(wis));
    set_alarm(itof(duration), 0.0, dispel_spell_effect);

    return 1;
}


varargs public int
dispel_spell_effect(object dispeller)
{
    spell_caster->catch_msg("You feel your "+short()+" disperse.\n");
    remove_spell_effect_object();
    return 1;
}


public void
init()
{
    ::init();
    add_action(try_to_exit, blocked_exit, 1);
}

public void
create_object()
{
    set_name("_SCOP_shadow_wall");
    add_name("shadow wall");
    add_name("wall");
    add_name("shadows");
    set_long(shadows_long);
    add_prop(OBJ_M_NO_GET,1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "conjuration"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This shadow wall is " +
                                 "created to affect any " +
                                 "undeads passing through " +
                                 "it.\n", 40}));
    add_prop(MAGIC_I_RES_IDENTIFY, 40);
    add_prop(MAGIC_I_RES_MAGIC, 40);
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


public void
set_res_value(int value)
{
    res_value = value;
}

public void
set_sp_result(int value)
{
  sp_result = value;
}

/* This function is called when a player tries to walk through the
 * exit that this wall blocks. He has to pass a formidable task
 * that's made easier with a high degree of resistance, and is
 * drained, which is also modified by the resistance.
 * Returns: 0 if we succeed in walking through the wall, 
 *          1 if not (currently we always succeed).
 */
public int
try_to_exit()
{
    object drain_obj;
    int amount, delay;

    int task = TASK_FORMIDABLE;
    task -= TP->query_magic_res(MAGIC_I_RES_MAGIC) * 6;

    if (!TP->query_prop(LIVE_I_UNDEAD))
    {
        if(TP->query_alignment() < -300)
        {
            write("As you pass through the "+short()+", it is as if " +
                  "someone is looking directly into your soul " +
                  "taking good measures at your previous "+
                  "actions.\n");
            write("You feel slight panic creaping over you.\n");
            say(QCTNAME(TP)+" walks through the wall of shadows.\n");

            if (TP->resolve_task(task, ({TS_DIS, SKILL_AVG, SS_SPELLCRAFT,
                                         SS_FORM_ABJURATION, SKILL_END})) < 0)
            {
                TP->add_panic(50+random(50));            
            }
        }
        return 0;
    }

    if (TP->query_wiz_level())
    {
        write("As a wizard you do not feel any effects of passing " +
              "through this wall.\n");
        say(QCTNAME(TP)+" walks through the wall of shadows unharmed.\n");
        return 0;
    }

    if (present("_scop_shadow_wall_drain_object", TP) || 
        TP->resolve_task(task, ({TS_DIS, SKILL_AVG, SS_SPELLCRAFT,
                                 SS_FORM_ABJURATION, SKILL_END})) > 0)
    {
        write("You walk through the shadow wall unharmed.\n");
        say(QCTNAME(TP)+" walks through the wall of shadows unharmed.\n");
        return 0;
    }

    // Setting cap so hp taken is at most 820 hp, and thats for a 300 avg player.
    amount = TP->query_stat(SS_CON)/5;
    amount = amount/4 + random(amount/4) + random(amount/4) + random(amount/4);
    amount = MAX(20, amount);
    amount = MIN(40,amount);
    delay = amount * 20 / 40;

    spell_caster->catch_tell("You feel that a Soulless creature is trying to " +
                             "pass through your "+short()+", you focus your " +
                             "mental concentration on maintaining the wall.\n"); 

    // I base my value of delay on 1 second delay per 40 damage taken.
    // 1 second in pen calculation would yield about 46.67 but we are
    // willing to take a little higher penalty.
    // You take approximately 20 damage per 1 stat con drained.
    spell_caster->add_prop(SCOP_CAST_TIME, time());
    spell_caster->add_prop(SCOP_SPELL_DELAY, delay);
    spell_caster->add_attack_delay(delay/2);

    drain_obj = clone_object(SPIRIT_SPELLS + "tihosskias_drain_obj");
    drain_obj->set_amount(amount);
    drain_obj->move(TP, 1);
    drain_obj->start();

    write("As you move through the "+short()+" tendrils from the " +
          "shadows reach out for you. The tendrils tries to pull " +
          "you into the shadows beyond which lies the celestial " +
          "realm of utmost beauty. Visions haunt you and a deep " +
          "pain within your soulless body cause you to stagger as "+
          "you manage to pull yourself loose and manage to pass.\n");
    write("You feel drained from this endeavour.\n");
    say("As "+QTNAME(TP) + " attempts to pass through the "+short()+
        " tendrils from the shadows reach out for "+HIM(TP) +
        ". With what appears to be a strenuous effort "+QTNAME(TP)+
        " manages to struggle "+HIM(TP)+"self free and moves through the " +
        short()+".\n");
    return 0;
}

public void
remove_object()
{
    tell_room(environment(this_object()),"The "+short()+" blocking" +
        " the " + blocked_exit + " exit blinks out of existence!\n");
    ::remove_object();
}


/* This sets the description of the wall, so you can see which
 * direction the wall blocks by looking at it.
 * Returns: String description.
 */
public string
shadows_long()
{
    string description = "Before you a mesh of a "+short()+" pervades the "+
                          blocked_exit+". It seems to exist in " +
                         "a constant conflux of interchangable lights and " +
                         "shadows. Now and again long twisting tendrils "+
                         "reach out from the shadows. This "+short() +
                         " covers the passage going "+blocked_exit+".\n";
    if(TP->query_prop(LIVE_I_UNDEAD) || TP->query_alignment() < -300)
    {
        description += "Something about this " + short() +
                       " seems threatening to you.\n";
    }
    else
    {
        description += "You sense no threat from this shadow.\n";
    }
    return description;
}

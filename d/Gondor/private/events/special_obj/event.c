/*
 * /d/Gondor/events/special_obj/event_master.c
 *
 * Gives commands to run an event to a wizard. Ability to preset
 * variables such as multiple groups kept track of by the leader's
 * name, experience, additional leader experience, multiple tells,
 * multiple echos. Options will include preseting, seeing the
 * location of each group member, tell, group tell, echo, group
 * echo, reward, group reward, silent reward, silent group reward,
 * display the presets, clear the presets, query the team setup of
 * group members and withdraw and place an event npc.
 *
 * Originally coded by Gwyneth on October 2, 2000
 */

inherit "/std/object";

#include <const.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

/* Global vars */
int general = 0, combat = 0, quest = 0, ex_gen = 0,
    ex_com, ex_qst;
mapping group = ([]), tell = ([]), echo = ([]);
string arg, temp;

/* Prototypes */
private int preset_extra(string str);
private int preset_tell(string str);

public void
create_object()    
{
    set_name("ball");
    add_name("event_master");
    add_name("master");

    set_adj("crystal");
    add_adj("event");

    set_short("crystal ball");

    set_long("Pure magic, meant for the mighty wizards in the sky, " +
        "this crystal ball can be used for running events. " +
        "The words, 'event help' have been etched into the " +
        "handle.\n");
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);

    setuid();
    seteuid(getuid());
}


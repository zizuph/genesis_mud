
/*
   This is the object for fire spells in the Elemental Worshippers
   guild.

   Coded by Jaacar

   Modifications by Maniac 27/9/96.

   Revised by Bishop, June 2000.
*/


#pragma save_binary

#include "defs.h"

inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting.c";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include "defs.h"

#define WAND_SUBLOC "wbelt"

int count = 0;
int worn = 0;

int wear(string str);
int remove(string str);
int dest_tool();
string show_subloc(string subloc, object on, object for_obj);


string
query_auto_load()
{
    return MASTER + ":" + count;
}


int
remove(string str)
{
    object this, tp;
    this = this_object();
    tp = this_player();
    if (!present(this,tp))
    {
        notify_fail("You don't have the wand!\n");
        return 0;
    }
    if (!worn)
    {
        notify_fail("You don't have the wand on your belt!\n");
        return 0;
    }
    tp->remove_subloc(WAND_SUBLOC);
    worn = 0;
    write("You remove the copper wand from your belt.\n");
    say(QCTNAME(tp)+" removes a copper wand from "+tp->query_possessive()+" belt.\n");
    set_no_show_composite(0);
    return 1;
}


string
show_subloc(string subloc, object on, object for_obj)
{
    string data;
    if (subloc == WAND_SUBLOC)
    {
        if (for_obj != on)
            data = capitalize(on->query_pronoun())+ " has a copper wand "+
                "hanging from "+on->query_possessive()+" belt.\n";
        else
            data = "You have a copper wand hanging from your belt.\n";
        return data;
    }
}


int
wear(string str)
{
    object this,tp;
    this = this_object();
    tp = this_player();
    if (!present(this,tp))
    {
        notify_fail("You don't have the wand!\n");
        return 0;
    }
    if (worn)
    {
        notify_fail("You already have the wand hanging from your belt!\n");
        return 0;
    }
    tp->add_subloc(WAND_SUBLOC,this);
    worn = 1;
    write("You hang the copper wand from your belt.\n");
    say(QCTNAME(tp)+" hangs a copper wand from "+tp->query_possessive()+" belt.\n");
    this->set_no_show_composite(1);
    return 1;
}


int
dest_tool()
{
    object e;

    e = environment(this_object());

    if (interactive(e))
        e->catch_msg("The Fire Wand shatters into thousands of " +
                     "tiny pieces.\n");
    else
        tell_room(e, "The Fire Wand shatters into thousands of " +
                     "tiny pieces.\n");

    remove_object();
    return 1;
}


void
init_arg(string arg)
{
    if (!(this_player()->is_worship()))
    {
        count = atoi(arg) + 1;
        if (count >= 50)
            set_alarm(5.0,0.0, dest_tool);
    }
}


void
create_object()
{
    set_name("wand");
    add_name("worshipper_wand");
    set_short("copper fire wand");
    set_long("This is the Fire Wand. It is a smoothly carved "+
        "wooden shaft that is two feet in length, sheathed in copper, "+
        "and has strange runes carved along it.\n");

    add_prop(OBJ_M_NO_INS, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
}


void
enter_env(object env, object from)
{ 
   ::enter_env(env, from);
    add_spell_object(env);
}


void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}


init()
{
    ::init();
    add_action(wear,"whang");
    add_action(remove,"wremove");
}

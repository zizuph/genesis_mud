
/* 
   This is the object for air spells in the Elemental Worshippers
   guild.  
   
   Coded by Jaacar

   Modifications by Maniac 27/9/96. 
*/ 

#pragma save_binary


inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include "defs.h"
#include WORSHIP_HEADER

#define DAGGER_SUBLOC "belt"

int count = 0;
int worn = 0;
object tellspell;

int
is_worship(object living)
{
    return living->query_guild_name_lay() == GUILD_NAME;
}

int
is_worn()
{
    return worn;
}

string
query_auto_load()
{
    return MASTER + ":" + count;
}

int
unsheathe(string str)
{
    object this, tp;
    this = this_object();
    tp = this_player();
    if (!present(this, tp))
    {
        notify_fail("You don't have the dagger to unsheathe!\n");
        return 0;
    }
    if (!worn)
    {
        notify_fail("You don't have it sheathed!\n");
        return 0;
    }
    tp->remove_subloc(DAGGER_SUBLOC);
    worn=0;
    write("You unsheathe the dagger from your belt.\n");
    say(QCTNAME(tp)+" removes a silver dagger from "+tp->query_possessive()+" belt.\n");
    set_no_show_composite(0);
    return 1;
}

string
show_subloc(string subloc, object on, object for_obj)
{
    string data;
    if (subloc == DAGGER_SUBLOC)
    {
        if (for_obj != on)
            data = capitalize(on->query_pronoun()) + " has a silver dagger "+
                "sheathed in "+on->query_possessive()+" belt.\n";
        else
            data = "You have a silver dagger sheathed in your belt.\n";
        return data;
    }
}

int
sheathe(string str)
{
    object this, tp;
    this = this_object();
    tp = this_player();
    if (!present(this, tp))
    {
        notify_fail("You don't have the dagger to sheathe!\n");
        return 0;
    }
    if (worn)
    {
        notify_fail("You already have the dagger sheathed!\n");
        return 0;
    }
    tp->add_subloc(DAGGER_SUBLOC,this);
    worn=1;
    write("You sheathe the dagger in your belt.\n");
    say(QCTNAME(tp)+" sheathes a dagger in "+tp->query_possessive()+" belt.\n");
    this->set_no_show_composite(1);
    return 1;
}


int
dest_tool()
{
    object e;

    e = environment(this_object()); 

    if (interactive(e)) 
        e->catch_msg("The Air Dagger shatters into thousands of " +
                     "tiny pieces.\n");
    else
        tell_room(e, "The Air Dagger shatters into thousands of " +
                     "tiny pieces.\n");

    remove_object();
    return 1;
}


/* We don't let non-worshippers keep hold of these for long. */ 
void
init_arg(string arg)
{
    if (!is_worship(this_player()))
    {
        count = atoi(arg) + 1;
        if (count >= 50) 
            set_alarm(5.0, 0.0, dest_tool);
    }
}

void
try_to_activate()
{
    if (is_worship(environment(TO)))
    {
        if (!objectp(tellspell))
        {
            setuid();
            seteuid(getuid());
            tellspell = clone_object("/d/Calia/newworshippers/spells/t_anemos.c");
            add_spell(tellspell);
        }
        
        if (environment(TO)->query_skill(SS_CARVED) & AIR_FLAG)
        {
            remove_spell("/d/Calia/newworshippers/spells/t_stous.c");
            add_spell("/d/Calia/newworshippers/spells/t_stous.c");
            
            if (environment(TO)->query_skill(SS_PATRON_ELEMENTAL) & AIR_FLAG)
            {
                remove_spell("/d/Calia/newworshippers/spells/t_evimero.c");
                add_spell("/d/Calia/newworshippers/spells/t_evimero.c");
            }
        }
    }
}

void
create_object()
{
    set_name("dagger");
    add_name("worshipper_dagger");
    add_name(I_CAN_CAST);
    add_name(WORSHIPPER_OBJECT_ID);
    set_short("silver air dagger");
    set_long("This is the Air Dagger.  It is coated in silver, "+
        "about one foot in length, and has a brightly polished "+
        "hilt carved with strange runes.  "+
        VBFC_ME("dagg_long") + "\n");
    add_prop(OBJ_M_NO_INS, 1); 
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_STEAL,1);
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

public void
remove_object()
{
    cleanup_spells();
    ::remove_object();
}

string
dagg_long()
{
    object tp = this_player(); 

    string long_desc;
    if (tp->query_skill(SS_CARVED) & AIR_FLAG)
        {
            long_desc = "The runes read: Aeria, "+
                capitalize(tp->query_real_name())+
                ", Egsousia.  You also see the words 'wsheathe' and 'wunsheathe'.  ";
        }
    else
        {
            long_desc = "The runes read: Aeria, "+
                capitalize(tp->query_real_name())+
                ".  You also see the words 'wsheathe' and 'wunsheathe'.  ";
        }
    return long_desc;
}

int
wield(string str)
{
    NF("It would be disrespectful to use one of the Elemental Tools in "+
        "combat!\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(wield,"wield");
    add_action(sheathe,"wsheathe");
    add_action(unsheathe,"wunsheathe");
    try_to_activate();
}


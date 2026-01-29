/*
 * The scroll used to learn new spells for SoHM
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "/d/Krynn/guilds/sohm/defs.h"

void
create_object()
{
    set_name("scroll");
    add_adj(({"basic", "dark"}));
    set_long("Scroll for new spell. 'whedabra', or gloom...\n");

    add_prop(OBJ_I_WEIGHT,50);
}

void
remove_scroll()
{
    write("As you finish scribing the spell, the runes on the scroll begin glowing furiously and it " +
          "combusts!\n");
    say("As " +QTNAME(this_player()) + " completes scribing, the runes on the scroll begin to " +
        "glow furiously, and the scroll combusts!\n");

    this_object()->remove_object();
}


int
study_cmd(string str)
{
    if (!stringp(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if(this_player()->query_guild_name_occ() != GUILD_NAME) 
    {
        notify_fail("You are unable to decypher the magical writing " +
        "on the scroll.\n");
        return 0;
    }  

    if(str != "scroll")
    {
        notify_fail("Study what?\n");
        return 0;
    }

    if(!this_player()->query_prop("_sohm_read_magic_active")) 
    {
        notify_fail("You are not mentally focused enough to decypher the magical " +
        "writing on the scroll. Perhaps try again after preparing yourself " +
        "to read magic?\n");
        return 0;
    } 

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"whedabra"))
    {
        notify_fail("This scroll seems to have the spell gloom " +
            "scribed on it. This spell you already know.\n");
        return 0;
    }
     
    write("You begin to carefully study the scroll. You scribe the " +
        "gloom spell in to your spellbook!\n");
    say(QCTNAME(this_player()) + " begins copying the scroll in to " +
        this_player()->query_possessive() + " spellbook.\n");
    
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"whedabra");

    set_alarm(2.0,0.0,"remove_scroll");
    


    return 1;

}

void
init()
{
    ::init();
    add_action(study_cmd, "study");
    add_action(study_cmd, "read");
}

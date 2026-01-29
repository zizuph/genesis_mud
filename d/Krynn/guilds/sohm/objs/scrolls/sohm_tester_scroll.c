/*
 * The scroll used to learn new spells for SoHM
 *
 * Adds a comprehensive range of spells to the caster... should not be
 * given to mortals!
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
    add_adj(({"basic", "green"}));
    set_long("Scroll for all SoHM spells\n");

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

    if(this_player()->query_guild_name_occ() != "School of High Magic" &&
      this_player()->query_guild_name_occ() != "Wizards of High Sorcery")
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


    write("You begin to carefully study the scroll. You scribe the " +
      "xxx spell in to your spellbook!\n");
    say(QCTNAME(this_player()) + " begins copying the scroll in to " +
      this_player()->query_possessive() + " spellbook.\n");

    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"trothweyog");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"trothshochraos");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"trothgul");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"trothuvelucal");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"trothdraconis");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"trothixen");

    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"apianak");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"arcanfethos");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"arcanisvaes");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"bakmadaingis");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"chikohk");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"edarmolik");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"ehtahhewa");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"ehtahxiekiv");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"hewavers");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"ickrakarcanis");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"ixenner");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"kadenadon");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"levexlaraek");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"reelojawa");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"ricindenthanus");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"ripeidronik");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"riyitchikohk");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"shirak");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"shochraos");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"suacovisp");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"talkarpas");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"ukrisrivek");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"uvelucavaes");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"viraxregpos");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"vistoma");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"whedabra");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"xarzithnar");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"zhinpersvek");

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


/* 
 * This is the herb clerk for the guild hall. 
 *   
 * Coded by Jaacar July 30th, 2003.
 */ 

#pragma save_binary
#pragma strict_types

inherit "/std/monster";
inherit "/d/Calia/std/remember";
inherit "/d/Calia/std/intro";
inherit "/lib/guild_support";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include <language.h>

#include "defs.h"
#include SPIRIT_HEADER

public string
herbs_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Herbs are "+
        "a gift born of Lady Gu, and like all things, they have a "+
        "deeply powerful spiritual energy.\n");
    return "";
}

public string
energy_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: You can "+
        "harness the spiritual energy of an herb through the ritual "+
        "chamber and use of your gifts.\n");
    return "";
}

public string
gu_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Before I "+
        "was Chosen, I humbly served Lady Gu in caring for the earth.\n");
    TO->command("sweyes");
    return "";
}


public string
psuchae_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Blessed be "+
        "Psuchae, the Ruler of Spirit and Shadow.\n");
    return "";
}

void
create_monster()
{
    set_name("Jardeth");
    add_name("jardeth");
    set_title("the Master Herbalist of Psuchae");
    set_adj(({"ancient","white-robed"}));
    set_race_name("elf");
    set_stats(({100,100,100,100,100,100}));
    set_alignment(1200);
    set_base_stat(SS_OCCUP, 119);
    set_skill(SS_DEFENCE,100);
    set_intro_delay(1);
    set_act_time(60);
    add_act("emote absentmindedly brushes a bit of the soil "+
        "from the front of his robes.");
    add_act("emote frowns slightly and squints as he makes out a "+
        "label for one of his herb pouches.");
    add_prop(NPC_M_NO_ACCEPT_GIVE,1);
    add_prop(LIVE_I_ALWAYSKNOWN,1);

    clone_object("/d/Calia/guilds/scop/specials/spiritshadow")->shadow_me(TO,
        "occupational", "cleric", "Spirit Circle of Psuchae", "");
    clone_object("/d/Calia/guilds/scop/specials/spiritlayshadow")->shadow_me(TO,
        "layman", "cleric", "Spirit Circle of Psuchae", "");
    clone_object("/d/Calia/guilds/scop/objects/holy_symbol")->move(TO);

    set_skill(SS_PATRON_ELEMENTAL,EARTH_FLAG);
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"herb","herbs"}),&herbs_answer());
    add_ask(({"energy","spiritual energy"}),&energy_answer());
    add_ask(({"stones","earth","gu","lady gu"}),&gu_answer());
    add_ask(({"psuchae"}),&psuchae_answer());
}

public string
default_answer()
{
    command("emote telepathically says to you: I do not know of what "+
        "you speak.");
    return "";
}


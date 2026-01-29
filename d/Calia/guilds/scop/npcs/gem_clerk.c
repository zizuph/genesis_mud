
/* 
 * This is the gem clerk for the guild hall. 
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

#include "defs.h"
#include SPIRIT_HEADER

public string
gems_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Born of "+
        "fire deep in the bowels of the earth, gems are an untapped "+
        "resource of tremendous spiritual power.\n");
    return "";
}

public string
power_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Though "+
        "it may sound unreal, gems are formed by an unfathomable "+
        "liquid fire! The memory of this feat remains imprinted on "+
        "the gem's residual energy, which can be harnessed in the service "+
        "of Psuchae.\n");
    return "";
}

public string
pyros_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Before "+
        "Psuchae embraced me, my passions burned with great fury in my "+
        "service to Lord Pyros. His blessing remains remains upon my "+
        "spirit still.\n");
    TO->command("sweyes");
    return "";
}

public string
psuchae_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Exalted be "+
        "Psuchae, the Ruler of Spirit and Shadow.\n");
    return "";
}

public string
library_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: As the "+
        "most studious founder, I did indeed write many books for the "+
        "temple library to prepare the way for those who would follow. "+
        "Once the First Matriarch was Chosen, I was granted retirement, "+
        "and began to manage the Temple's gemstores.\n");
    return "";
}

public string
matriarch_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Anahita "+
        "is the First Matriarch of the Spirit Circle.\n");
    return "";
}

void
create_monster()
{
    set_name("Arial");
    add_name("arial");
    set_title("the Master Lapidarist of Psuchae");
    set_adj(({"beautiful","white-robed"}));
    set_race_name("elf");
    set_gender(G_FEMALE);

    set_stats(({100,100,100,100,100,100}));
    set_alignment(0);
    set_skill(SS_DEFENCE,100);
    set_base_stat(SS_OCCUP, 105);

    add_prop(LIVE_I_ALWAYSKNOWN,1);

    clone_object("/d/Calia/guilds/scop/specials/spiritshadow")->shadow_me(TO,
        "occupational", "cleric", "Spirit Circle of Psuchae", "");
    clone_object("/d/Calia/guilds/scop/specials/spiritlayshadow")->shadow_me(TO,
        "layman", "cleric", "Spirit Circle of Psuchae", "");
    clone_object("/d/Calia/guilds/scop/objects/holy_symbol")->move(TO);

    set_skill(SS_PATRON_ELEMENTAL,FIRE_FLAG);
    set_alignment(1100);
    set_intro_delay(1);
    set_act_time(60);
    add_act("emote gazes at the tapestry on the wall.");
    add_act("emote polishes her gemstones and you can't help but "+
        "notice her hands are yet stained with the ink she devoted "+
        "to writing the books in the library.");
    add_act("emote breathes deeply as a fresh breeze wafts in from the "+
        "garden.");
    add_act("emote telepathically says: It is not for me to reveal the "+
        "spiritual properties of gems. It is something you must discover "+
        "for yourself.");
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"gem","gems","gemstone","gemstones"}),&gems_answer());
    add_ask(({"power","spiritual power"}),&power_answer());
    add_ask(({"flames","fire","pyros","lord pyros"}),&pyros_answer());
    add_ask(({"psuchae"}),&psuchae_answer());
    add_ask(({"library","book","books"}),&library_answer());
    add_ask(({"matriarch","first matriarch"}),&matriarch_answer());
}

public string
default_answer()
{
    command("emote telepathically says to you: I do not know of what "+
        "you speak.");
    return "";
}
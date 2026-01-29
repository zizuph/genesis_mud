
/* 
 * This is the caterer for the guild hall. 
 *   
 * Coded by Jaacar July 30th, 2003.
*/ 

#include <ss_types.h>
#include <macros.h> 
#include <stdproperties.h>
#include "defs.h"
#include SPIRIT_HEADER

inherit "/std/monster";
inherit "/d/Calia/std/remember";
inherit "/d/Calia/std/intro";
inherit "/lib/guild_support";

public string
food_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Many "+
        "think cooking is a whimsical persuit, but sustinance "+
        "of the body is just as important as sustinance of the spirit.\n");
    return "";
}

public string
spirit_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: While we "+
        "are servants of spirit, we are still bound by our physical body. "+
        "Without a nourished body, we cannot thrive in this reality.\n");
    return "";
}

public string
diabrecho_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Though I "+
        "now serve Psuchae, the depths of Diabrecho's insights still "+
        "inspire my soul.\n");
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
insight_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: While the "+
        "Clergy can offer some insights to guide you along your spiritual "+
        "path, ulitmately the journey is one you walk with Psuchae "+
        "beside you. I have found the garden to be a place of serenity "+
        "for contemplation.\n");
    return "";
}

void
create_monster()
{
    set_name("Tiashe"); 
    add_name("caterer");
    add_name("tiashe");
    add_name("Tiashe Laodarahel");

    set_adj(({"smiling", "robed"}));  
   
    set_race_name("elf");
    set_gender(G_FEMALE);
    set_title("the Master Caterer of Psuchae");

    set_long("This is the elven caterer of the temple. She "+
        "is wearing a long white robe that covers most of "+
        "her body.\n"); 

    default_config_npc(150);

    clone_object("/d/Calia/guilds/scop/specials/spiritshadow")->shadow_me(TO,
        "occupational", "cleric", "Spirit Circle of Psuchae", "");
    clone_object("/d/Calia/guilds/scop/specials/spiritlayshadow")->shadow_me(TO,
        "layman", "cleric", "Spirit Circle of Psuchae", "");
    clone_object("/d/Calia/guilds/scop/objects/holy_symbol")->move(TO);

    set_skill(SS_UNARM_COMBAT, 50); 
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PATRON_ELEMENTAL,WATER_FLAG);
    set_alignment(1100);

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_ALWAYSKNOWN,1);
    add_prop(CONT_I_WEIGHT, 65000); 
    add_prop(CONT_I_VOLUME, 65000); 
    set_intro_delay(1);
    set_act_time(60);
    add_act("emote smiles softly as she cleans one of the tables.");
    add_act("emote prepares a meal with a graceful motion.");
    add_act("emote peers surreptitiously around, then tastes a small bit of "+
        "cookie dough from her mixing bowl.");
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"food"}),&food_answer());
    add_ask(({"spirit"}),&spirit_answer());
    add_ask(({"diabrecho","lord diabrecho","waves","water"}),&diabrecho_answer());
    add_ask(({"psuchae"}),&psuchae_answer());
    add_ask(({"insight","insights"}),&insight_answer());
}

public string
default_answer()
{
    command("emote telepathically says to you: I do not know of what "+
        "you speak.");
    return "";
}


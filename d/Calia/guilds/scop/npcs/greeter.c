
/* 
 * This is the greeter NPC for the guild hall. 
 *   
 * Coded by Jaacar August 27th, 2003.
 * 
 * Changelog: 
 *   Baldacin, Feb 25 2004.
 *        Made the greeter 'alwaysknown' to members by
 *        adding it to the introduced list of the member
 *        players when they enter the room, through init_living.
 *  Added 'donations' and 'joining' as responses - Jaacar, May 2016
*/ 

#include <ss_types.h>
#include <macros.h> 
#include <stdproperties.h>
#include <cmdparse.h>
#include "defs.h"
#include SPIRIT_HEADER

inherit "/std/monster"; 
inherit "/d/Calia/std/intro";
inherit "/lib/guild_support";

#define DROPROOM "/d/Calia/guilds/scop/temple/storage_chamber"
#define DONATION_LOG "spirit_circle/donation_log"

public string
job_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: My "+
        "job is to answer the questions of those who come to this "+
        "holy temple.\n");
    return "";
}

public string
temple_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: This "+
        "is the holy temple of Psuchae. Those who are members of the "+
        "Spirit Circle reside here.\n");
    return "";
}

public string
sc_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: The "+
        "Spirit Circle consists of people who follow the teachings "+
        "of Psuchae.\n");
    return "";
}

public string
member_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: I "+
        "cannot divulge the identities of the members. I am sorry.\n");
    return "";
}

public string
join_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: One "+
        "does not choose to serve in the Spirit Circle of Psuchae. "+
        "All who dwell here are chosen by Psuchae.\n");
    return "";
}

public string
apply_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: I "+
        "am sorry. Psuchae does not take applications. If you are "+
        "to follow the path, Psuchae will select you and you will "+
        "be contacted.\n");
    return "";
}

public string
psuchae_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: "+
        "Psuchae is the ruler of Spirit and Shadow.\n");
    return "";
}

public string
elementals_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: "+
        "The Elemental Worshippers can be found elsewhere in these "+
        "realms.\n");
    return "";
}

public string
shadow_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: "+
        "The Shadow is a true reflection of ones Soul.\n");
    return "";
}

public string
spirit_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: "+
        "Spirit is the quickening of creation.\n");
    return "";
}

public string
wedding_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Very "+
        "soon we shall be performing wedding ceremonies here.\n");
    return "";
}

public string
donation_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: You "+
        "can donate items to the Spirit Circle if you wish. Simply "+
        "notify me which item you wish to donate. (donate <item>)\n");
    return "";
}


public string
question_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Ah! "+
        "A question I do not get asked very many times. I can tell "+
        "you about Spirit, Shadow, Elementals, Psuchae, applying, "+
        "joining, members, Spirit Circle, holy temple, donations, "+
        "and position.\n");
    return "";
}

public void
create_monster()
{
    set_name("Sehis");
    add_name("elf");
    add_name("greeter");
    add_name("sehis");
    
    set_adj(({"smiling", "white-robed"}));  
   
    set_race_name("elf");
    set_gender(G_FEMALE);
    
    set_long("This white-robed elf is smiling gently at you. She "+
        "seems very quiet. Looking into her eyes seem to bring "+
        "peace to your heart.\n"); 

    set_stats(({100,100,100,100,100,100}));
    set_alignment(1200); 

    set_skill(SS_UNARM_COMBAT, 50); 
    set_skill(SS_DEFENCE, 50);
    set_base_stat(SS_OCCUP, 70);

    set_intro_delay(1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_WEIGHT, 65000); 
    add_prop(CONT_I_VOLUME, 65000);

    clone_object("/d/Calia/guilds/scop/specials/spiritshadow")->shadow_me(TO,
        "occupational", "cleric", "Spirit Circle of Psuchae", "");
    clone_object("/d/Calia/guilds/scop/specials/spiritlayshadow")->shadow_me(TO,
        "layman", "cleric", "Spirit Circle of Psuchae", "");
    clone_object("/d/Calia/guilds/scop/objects/holy_symbol")->move(TO);

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"job","position"}),&job_answer());
    add_ask(({"temple","holy temple"}),&temple_answer());
    add_ask(({"spirit circle","circle"}),&sc_answer());
    add_ask(({"member","members"}),&member_answer());
    add_ask(({"join","joining"}),&join_answer());
    add_ask(({"apply","application","applying"}),&apply_answer());
    add_ask(({"psuchae"}),&psuchae_answer());
    add_ask(({"elements","elementals"}),&elementals_answer());
    add_ask(({"shadow","shadows"}),&shadow_answer());
    add_ask(({"spirit","spirits"}),&spirit_answer());
    add_ask(({"wedding","weddings","marriage"}),&wedding_answer());
    add_ask(({"donate","donation","donating","donations"}),&donation_answer());
    add_ask(({"question","questions"}),&question_answer());
}

public string
default_answer()
{
    command("emote telepathically says to you: I do not know of what "+
        "you speak.");
    return "";
}

/* 
 * Function:     do_donate 
 * Description:  Donate an item to the cadet racks. 
 * Original code by Maniac for Cadets
 *
 */

int 
do_donate(string str) 
{ 
    object *oblist, donation; 
    string sh; 
    int v; 

    if (!stringp(str) || !strlen(str) || 
        !sizeof(oblist = FIND_STR_IN_ARR(str, all_inventory(TP)))) 
    { 
        NF("Donate what to the Spirit Circle?\n"); 
        return 0; 
    } 

    if (sizeof(oblist) > 1) 
    { 
        NF("You may only donate one item at once to " + 
            "the Spirit Circle.\n"); 
        return 0; 
    } 

    donation = oblist[0]; 
    sh = LANG_ASHORT(donation); 
    write("You offer " + sh + " as a donation to " + 
          "the Spirit Circle.\n"); 
    say(QCTNAME(TP) + " offers " + sh + 
        " as a donation to the Spirit Circle.\n"); 

    if (IS_COINS_OBJECT(donation)) 
    { 
        v = donation->query_prop(OBJ_I_VALUE); 
        if (v > 500) 
            command("$emote smiles thankfully"); 
        else if (v > 1000) 
            command("$emote smiles appreciatively"); 
        else if (v > 4000) 
            command("$emote smiles very appreciatively"); 

        write(TO->query_The_name(TP)+" telepathically says to you: "+
            "Very generous of you, but there is no fund to add that "+
            "to currently.\n"); 
        return 1; 
    } 

    if (living(donation)) 
    { 
        command("boggle"); 
        write(TO->query_The_name(TP)+" telepathically says to you: "+
            "Thanks for the thought but we don't accept " + 
            "live animals!\n"); 
        return 1; 
    } 

    if (donation->query_prop(OBJ_I_BROKEN)) 
    { 
        command("chuckle"); 
        write(TO->query_The_name(TP)+" telepathically says to you: "+
            "Good of you to think of us, but " + 
            "that " + donation->query_name() + " doesn't " + 
            "look much use at the moment.\n"); 
        return 1; 
    } 

    if (donation->query_keep()) 
    { 
        write(TO->query_The_name(TP)+" telepathically says to you: "+
            "Are you sure you want to " + 
            "donate " + LANG_THESHORT(donation) + 
            "? If so, please unkeep the "+LANG_THESHORT(donation) + 
            " and try again.\n"); 
        return 1; 
    }

    if (donation->query_prop(OBJ_M_NO_DROP))
    {
        write(TO->query_The_name(TP)+" telepathically says to you: "+
            "You cannot seem to release " + LANG_THESHORT(donation) +".\n"); 
        return 1;
    }

    if (donation->query_prop(OBJ_M_NO_GIVE))
    {
        write(TO->query_The_name(TP)+" telepathically says to you: "+
            "You cannot seem to release " + LANG_THESHORT(donation) +".\n"); 
        return 1;
    }

    DROPROOM->teleledningsanka(); // load the room if it's not already loaded.
    donation->move(DROPROOM,1);
    
    sh = LANG_THESHORT(donation); 

    tell_room(DROPROOM,capitalize(LANG_ASHORT(donation))+" suddenly "+
        "appears on the ground.\n");
    tell_room(environment(this_object()),QCTNAME(this_object()) + 
        " puts " + sh + " into a magical bag.\n"); 
    command("$thank " + OB_NAME(TP));
    log_file(DONATION_LOG, ctime(time())+" "+capitalize(LANG_ASHORT(donation))+
        " was donated by "+TP->query_name() +".\n",-1);
    return 1; 
} 

void
init_living()
{   
	if (TP->query_guild_name_occ() == SPIRIT_GUILD_NAME)
		TP->add_introduced(query_real_name());

    add_action(do_donate,"donate");
	::init_living();
}

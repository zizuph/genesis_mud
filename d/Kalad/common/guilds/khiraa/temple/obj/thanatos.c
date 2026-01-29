/* 
 * /d/Kalad/common/guilds/khiraa/temple/obj/thanatos.c
 * Purpose    : This is a guild npc in chrage of killing those who join the guild.
 * Located    : ~khiraa/temple/rooms/temple_join
 * Created By : Sarr 16.Apr.97
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

#pragma save_binary
#pragma strict_types

void
create_monster() 
{
    ::create_monster();
    set_name("thanatos");
    set_race_name("human");
    set_adj("ghostly");
    add_adj("eyeless");
    set_long("This robbed human is so pale, you can almost see through "+
    "him. His face is gaunt and skeletal, and he is missing eyes. His "+
    "black robe hangs on a skeletal frame. A slight grin plays on his "+
    "ghastly face.\n");
    set_stats(({100,110,150,150,150,150}));
    set_skill(SS_DEFENCE,100);
    add_prop(LIVE_I_NO_GENDER_DESC,1);
    add_prop(NPC_I_NO_FEAR,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_UNDEAD,150);
    set_title("the Bloody Hand, High Death Priest of the Khiraa");
    set_alignment(-1200);
    add_speak("Ah...you came to join us...how nice. Perhaps you "+
    "should read the book first.\n");
}

string
query_gender_string()
{
    return "undead";
}

void
arm_me()
{
    object wep;
    object arm;
    seteuid(getuid());
    wep = clone_object(KHIRAA_DIR(temple/obj/cer_dagger));
    wep->move(TO);
    arm = clone_object(RAUM(arm/dmrobe));
    arm->move(TO);
    arm = clone_object(DK_DIR(obj/dk_medallion));
    arm->move(TO);
    command("wear all");
    command("wield all");
}

string
query_guild_name_occ()
{
    return "DK of Khiraa";
}
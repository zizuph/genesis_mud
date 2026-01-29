/* 
 * /d/Kalad/common/guilds/khiraa/temple/obj/xantios.c
 * Purpose    : A guild npc
 * Located    : ~khiraa/rooms/temple/t8
 * Created By : Sarr 16.Mar.97
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
    set_name("xantios");
    set_race_name("elf");
    set_adj("glowing-eyed");
    add_adj("skeletal");
    set_long("You gaze upon a skeletal figure of what appears to have "+
    "once been an elf. Its eye sockets are filled with pin-point red "+
    "glowing embers. An evil grin spreads across his face. Through "+
    "its tattered robes, you can make out a skeletal figure. A "+   
    "bony hand clutches a staff.\n");
    set_stats(({100,110,150,150,150,150}));
    set_skill(SS_DEFENCE,100);
    add_prop(LIVE_I_NO_GENDER_DESC,1);
    add_prop(NPC_I_NO_FEAR,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_SEE_DARK,50);
    add_prop(LIVE_I_UNDEAD,150);
    set_title("the Forgotten King, Greater Necromancer of the Khiraa");
    set_alignment(-1200);
    add_speak("Greetings, foolish one, to the Temple of the Khiraa.\n");
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
    wep = clone_object(RAUM(wep/wstaff));
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
/* 
 * /d/Kalad/common/guilds/khiraa/temple/obj/urgana.c
 * Purpose    : This npc gives out the entrance quest
 * Located    : ~khiraa/temple/rooms/temple_main
 * Created By : Sarr 20.Apr.97
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
    set_name("urgana");
    add_name("lich");
    set_race_name("human");
    set_adj("silver-haired");
    add_adj("ethereal");
    set_short("silver-haired ethereal human");
    set_long("You see a ghostly figure before, wrapped in black "+
    "robes. Her hair pours out of her robe in a pure silver waterfall. "+
    "She wears a black grim-skulled medallion.\n");
    set_gender(1);
    set_stats(({100,110,150,150,150,150}));
    set_skill(SS_DEFENCE,100);
    add_prop(LIVE_I_NO_GENDER_DESC,1);
    add_prop(NPC_I_NO_FEAR,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_SEE_DARK,50);
    add_prop(LIVE_I_UNDEAD,180);
    set_title("the Raven's Song, Mistress of the Grave");
    set_alignment(-1200);
    add_speak("Greetings, foolish one, to the Temple of the Khiraa.\n");
    set_default_answer("The "+short()+" glares at you.\n");
    add_ask("khiraa","The "+short()+" hisses: Ah, yes...the Khiraa. "+
    "That is where you are. The temple of the Khiraa. I am a High "+
    "priestess of Him, he whos name is unspeakable. You, living "+
    "mortal, should leave before it's too late....unless, you seek "+
    "to serve Him. As all will eventually, in one way or another! "+
    "Service to Him, is a great honor.\n");
    add_ask(({"service","serve","join"}),"The "+short()+" hisess: ahh.."+
    ".so you want to serve Him. Well, He must accept your service. I "+
    "have a small task that will determine if you are fit.\n");
    add_ask("task","The "+short()+" hisses: The task, yes. Well, "+
    "go forth to the bloody sacrifice chamber here, and there you "+
    "will find an item of interesting nature. Take that item to the "+
    "skeleton of blood in that foul city of light, and do what it "+
    "says. If He gives you His divine permission, then you may "+
    "go forth to the north. Until then, begone!\n");
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

int
special_attack(object enemy)
{
    object poi;
    if(random(8))
        return 0;
    tell_room(E(TO),QCTNAME(TO)+" points her finger at "+
    QTNAME(enemy)+" and utters strange words.\n",enemy);
    tell_object(enemy,"The "+query_the_name(enemy)+" points her finger at "+
    "you and utters strange words.\n");
    seteuid(getuid());
    poi = clone_object(LP_DIR(obj/disease));    
    poi->set_strength(90);
    poi->set_time(4000);
    poi->move(enemy);
    poi->start_poison();
    return 1;
}

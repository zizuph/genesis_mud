/* 
 * /d/Kalad/common/guilds/khiraa/temple/obj/olaus.c
 * Purpose    : Guild npc.
 * Located    : ~khiraa/rooms/temple/t6
 * Created By : Sarr 28.Mar.97
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
    set_name("olaus");
    set_race_name("human");
    set_adj("gloomy");
    add_adj("sinister");
    set_long("A dark and tall figure cloaked in black robes. A foul "+
    "smell eminates off him, and you realize its the stech of total "+
    "evil mixed in with death and decay. Dark black eyes peer at "+
    "you from behind a hood. In its pale bony hand, he holds a book "+
    "and staff.\n");
    set_stats(({140,160,180,250,200,150}));
    set_skill(SS_DEFENCE,100);
    add_prop(LIVE_I_NO_GENDER_DESC,1);
    add_prop(NPC_I_NO_FEAR,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(LIVE_I_SEE_DARK,50);
    add_prop(LIVE_I_UNDEAD,150);
    set_title("Magnus, the Hellish, Chosen One of Him");
    set_alignment(-1200);
    add_speak("Greetings, foolish one, to the Temple of the Khiraa.\n");
    add_ask("book","Olaus Magnus says: "+
    "I would like to find my old, ancient book known as the "+
    "Necronomicon. It was taken from me by a powerful necromancer of "+
    "another world, known as Zeelek. What has become of it, I know "+
    "not.\n");
    add_ask("zeelek","Zeelek was a necromancer of Kara-moon. He was "+
    "a master of transmutation. He created horrible creatures. In "+
    "fact, I belive the beast lord that dwells in the forgotten ruins "+
    "in the plains was one of his creations.\n");
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

void
thank(object ob,object from)
{
    command("say Thank you, "+from->query_name()+", may He look "+
    "favorably on you.");
    ob->remove_object();
}

void
enter_inv(object what, object from)
{
    ::enter_inv(what,from);
    if(MASTER_OB(what) == RAUM(obj/necro_book))
    {
        set_alarm(3.0,0.0,&thank(what,from));
    }
}
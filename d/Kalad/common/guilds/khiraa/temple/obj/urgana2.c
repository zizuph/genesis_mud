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
    set_name("ghost");
    set_race_name("ghost");
    set_adj("white");
    add_adj("transparent");
    set_short("white transparent ghost");
    set_long("You see a ghostly female figure before you, her white " +
    " transparent hair flows gently, like a silver waterfall.\n");
    set_gender(1);
    set_stats(({200,210,250,150,150,150}));
    set_skill(SS_DEFENCE,100);
    add_prop(NPC_I_NO_FEAR,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_SEE_DARK,50);
    add_prop(LIVE_I_UNDEAD,180);
    add_prop(LIVE_I_NEVERKNOWN,1);
    //set_title("the Raven's Song, Mistress of the Grave");
    set_alignment(-200);
    add_speak("Greetingss...visitor.\n");
    set_default_answer("The "+short()+" glares at you.\n");
    add_ask("khiraa","The "+short()+" whispers: Ah, yes...the Khiraa.." +
    "..The servants of the Nameless One once belonged to this now abandoned " +
    "temple. Khiraa have relocated to a different place, and this temple " +
    "serves noone except arcanists and seekers of the uknown.\n");
    add_ask(({"service","serve","join"}),"The "+short()+" whispers: ahh.."+
    ".so you want to serve Him. Well, He must accept your service. I "+
    "have a small task that will determine if you are fit. However, " +
    "even if you are deemed fit to serve Him after doing the task, it " +
    "will not happen until Khiraa announces their arrival from the Nether.\n");
    add_ask("task","The "+short()+" whispers: The task, yes. Well, "+
    "go forth to the bloody sacrifice chamber here, and there you "+
    "will find an item of interesting nature. Take that item to the "+
    "skeleton of blood in that foul city of light, and do what it "+
    "says...\n");
}


int
special_attack(object enemy)
{
    object poi;
    if(random(5))
        return 0;
    tell_room(E(TO),QCTNAME(TO)+" points her finger at "+
    QTNAME(enemy)+" and utters strange words.\n",enemy);
    tell_object(enemy,"The "+query_the_name(enemy)+" points her finger at "+
    "you and utters strange words.\n");
    seteuid(getuid());
    poi = clone_object(LP_DIR(obj/disease));    
    poi->set_strength(190);
    poi->set_time(4000);
    poi->move(enemy);
    poi->start_poison();
    return 1;
}

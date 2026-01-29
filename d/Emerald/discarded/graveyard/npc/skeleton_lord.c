inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
 
#include "/d/Emerald/defs.h"
 
 
void
create_monster()
{
 
    if(!IS_CLONE)
        return;
 
    set_name("lord");
    set_race_name("skeleton");
    set_short("skeleton lord");
    set_long( "A skeleton of what was once a mighty warrior,"+
        " now doomed to wander these darkened tunnels.\n" );
 
    set_stats(({80,80,80,50,50,90}));
    set_hp(1920);
    set_all_hitloc_unarmed(20);
 
    set_skill(SS_DEFENCE,70);
    set_skill(SS_PARRY,60);
    set_skill(SS_WEP_SWORD,70);
    set_skill(SS_BLIND_COMBAT,80);
    set_skill(SS_AWARENESS,50);
    set_alignment(-600);
 
    add_prop(LIVE_I_NO_CORPSE,1);
 
    set_chat_time(10);
    add_chat("Leave now, before I kill you.");
 
    seq_new("do_things");
    seq_addfirst("do_things",("@@arm_me"));
}
 
 
arm_me()
{
    object wep,arm;
 
    seteuid(getuid(this_object()));
 
    wep=clone_object(GRAVEYARD_DIR + "wep/evil_sword");
    wep->move(this_object());
 
    arm=clone_object(GRAVEYARD_DIR + "arm/skshield");
    arm->move(this_object());
 
    arm=clone_object(GRAVEYARD_DIR + "arm/skringmail");
    arm->move(this_object());
 
    arm=clone_object(GRAVEYARD_DIR + "arm/skhelmet");
    arm->move(this_object());
 
    command("wield all");
    command("wear all");
}

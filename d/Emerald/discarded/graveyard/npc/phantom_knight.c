inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
 
#include "/d/Emerald/defs.h"
 
 
void
create_monster()
{
 
    if(!IS_CLONE)
        return;
 
    set_name("phantom");
    set_race_name("knight");
    set_short("phantom knight");
    set_adj("phantom");
    set_long( "A somewhat insubstantial looking figure, with cold"+
        " evil eyes. You feel an urge to flee from this being.\n" );
 
    set_stats(({100,100,100,100,100,100}));
    set_hp(2800);
    set_all_hitloc_unarmed(30);
 
    set_skill(SS_DEFENCE,70);
    set_skill(SS_PARRY,60);
    set_skill(SS_WEP_SWORD,70);
    set_skill(SS_BLIND_COMBAT,80);
    set_skill(SS_AWARENESS,80);
 
    seq_new("do_things");
    seq_addfirst("do_things",("@@arm_me"));
}
 
 
arm_me()
{
    object wep,arm;
 
    seteuid(getuid());
 
    wep=clone_object(GRAVEYARD_DIR + "wep/phantom_blade");
    wep->move(this_object());
 
    arm=clone_object(GRAVEYARD_DIR + "arm/phantom_plate");
    arm->move(this_object());
 
    command("wield all");
    command("wear all");
}

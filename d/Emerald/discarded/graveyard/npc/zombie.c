inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/std/act/add_things";
 
#include "/d/Emerald/defs.h"
 
 
 
void
create_monster()
{
 
    if(!IS_CLONE)
        return;
    set_name("zombie");
    set_race_name("zombie");
    set_adj("rotting");
    set_long( "A partially decomposed human, covered in "+
        "rotting skin.\n" );
 
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_UNDEAD,35);
 
    set_stats(({40,40,40,20,20,50}));
    set_hp(10000);
 
    set_skill(SS_DEFENCE,25);
    set_skill(SS_WEP_CLUB,30);
 
 
    set_act_time(10);
    add_act("grin");
    add_act("glare all");
 
    seq_new("do_things");
    seq_addfirst("do_things","@@arm_me");
}
 
 
arm_me()
{
    object arm,wep;
 
    seteuid(getuid(this_object()));
 
    wep=clone_object(GRAVEYARD_DIR + "wep/bone");
    wep->move(this_object());
    command("wield all");
 
    arm=clone_object(GRAVEYARD_DIR + "arm/cloth");
    wep->move(this_object());
    command("wear all");
}

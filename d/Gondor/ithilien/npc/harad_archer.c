#include "/d/Gondor/defs.h"
#include <ss_types.h>

inherit ITH_DIR + "npc/haradstd";
inherit LIB_DIR + "protection";

public void
create_monster()
{
    ::create_monster();
    set_base_stat(SS_DEX,     95 + random(10));
    set_skill(SS_WEP_MISSILE, 85 + random(10));
    set_skill(SS_PARRY,       35 + random(5));
    set_skill(SS_DEFENCE,     90 + random(5));
    set_exp_factor(110);
}

void
arm_me()
{
    object arrows, quiver;
    
    setuid();
    seteuid(getuid());
       
    clone_object(WEP_DIR + "haradscim")->move(TO, 1);
    
    clone_object(WEP_DIR + "longbow")->move(TO, 1);
    command("wield longbow");
    command("secondary wield sword");
    
    quiver = clone_object(OBJ_DIR + "greatquiver");
    quiver->move(TO, 1);
    command("wear quiver");
    
    arrows = clone_object(WEP_DIR + "long_black_arrow");
    arrows->move(quiver, 1);    
    arrows->set_heap_size(50);
    
    clone_object(ARM_DIR + "haradcloak")->move(TO, 1);
    command("wear cloak");
    
    clone_object(ARM_DIR + "haradshield")->move(TO, 1);
    command("wear shield");
    
    clone_object(ARM_DIR + "corslet")->move(TO);
    command("wear corslet");
    
    clone_object(ITH_DIR + "forest/harad_earring")->move(TO);
    command("wear earrings");
}








#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <poison_types.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/dargaard/local.h"
#include "../local.h"

inherit AM_FILE

void
create_krynn_monster()
{
    set_name("Trell");
    set_title("the Atrocious Guardian of the Death Knights of Krynn");
    set_race_name("wraith");
    add_name("trell");
    set_adj("black-cloaked");
    add_adj("translucent");
    set_gender("G_MALE");
    set_long("Dressed in a shredded black cloak, this translucent "+
             "being stands here to protect the inner sanction of "+
             "Dargaard Keep. You feel that attempting to get past him "+
             "might be a mistake, unless you have the emblem of "+
             "Dargaard Keep.\n");

    set_stats(({190, 220, 300, 100, 120, 200}));
    set_all_hitloc_unarmed(60);
    set_alignment(-1200);
    set_introduce(1);   

    change_prop(LIVE_I_QUICKNESS, 200);
    change_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_HEIGHT, 2100);
    add_prop(CONT_I_VOLUME, 2200); 
    add_prop("_ranger_m_not_disarm",1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_SEE_INVIS, 1);


    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_UNARM_COMBAT, 120);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
}

void
attacked_by(object ob)
{
    object stun;

    ob->catch_msg(QCTNAME(TO) + 
           " spins "+HIS(TO)+ " sleek bone-handled scythe around in a low circle.\n"+
           "The weapon strikes your legs and you fall to the ground.\n");

    tell_room(E(TO), QCTNAME(TO) + " spins " +HIS(TO)+ " sleek bone-handled scythe "+
              "around in a low circle.\n"+
              "The weapon strikes " +QTNAME(ob)+ " legs and " +HE(ob)+ " falls "+
              "to the ground.\n",({ob, TO}));
 
    if(!P("Serion_stun", ob))
        clone_object("/d/Ansalon/balifor/port_balifor/obj/serion_stun")->move(ob);

    ::attacked_by(ob);   
}

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
public void
attack_object(object ob)
{
    object stun;

    ob->catch_msg(QCTNAME(TO) + 
           " spins "+HIS(TO)+ " sleek bone-handled scythe around in a low circle.\n"+
           "The weapon strikes your legs and you fall to the ground.\n");

    tell_room(E(TO), QCTNAME(TO) + " spins " +HIS(TO)+ " sleek bone-handled scythe "+
              "around in a low circle.\n"+
              "The weapon strikes " +QTNAME(ob)+ " legs and " +HE(ob)+ " falls "+
              "to the ground.\n",({ob, TO}));
 
    if(!P("Serion_stun", ob))
        clone_object("/d/Ansalon/balifor/port_balifor/obj/serion_stun")->move(ob);

    ::attacked_by(ob);   
}


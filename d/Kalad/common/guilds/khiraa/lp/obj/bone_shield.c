/* 
 * /d/Kalad/common/guilds/khiraa/lp/obj/bone_shield.c
 * Purpose    : This is the shield that is made by the lich spell 'lbone'. It is magical, and adds protection to all body parts.
 * Located    : Conjured by the spell 'lbone'
 * Created By : Sarr 12.Apr.97
 * Modified By: Sarr 18.Jun.98 (recode)
 */ 

#include <wa_types.h>
#include "/d/Kalad/common/guilds/khiraa/magic.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"

inherit "/d/Kalad/std/armour.c";
inherit SPELL_EFFECT_OBJECT;

/* by Sarr*/

/* For the spell 'bone shield' of the lichs */

void
set_remove_time(int i)
{
    set_alarm(itof(i),0.0,"remove_object");
}

void
remove_object()
{
    tell_object(E(TO),"The "+short()+" suddenly vanishes!\n");

    if(query_worn())
    {
        tell_object(query_worn(),"The cage of bones around you "+
        "dissapear.\n");
        tell_room(E(query_worn()),"The cage of bones around "+
        QTNAME(query_worn())+" dissapear.\n",query_worn());
    }
    ::remove_object();
}


void
create_armour()
{
    ::create_armour();
    set_name("shield");
    set_short("bone shield");
    set_adj("bone");
    set_long("A skull-shaped bone shield.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    set_ac(25);
    set_at(A_MAGIC);
    set_shield_slot(({A_HEAD,A_TORSO,A_L_ARM,A_R_ARM,A_LEGS,}));
    set_no_show();
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_M_NO_DROP,"It is magical, you must wait till it "+
    "wears off to be rid of it.\n");
    set_af(TO);
}

int
wear(object arm)
{
    write("A cage of bones suddenly "+
    "appear around you!\n");
    say("A cage of bones suddenly appears around "+QTNAME(TP)+"!\n");
    TP->add_magic_effect(TO);
    return 1;
}

int
remove(object arm)
{
    set_this_player(query_worn());
    write("The cage of bones around you dissapear.\n");
    say("The cage of bones around "+QTNAME(TP)+" suddenly dissapear.\n");
    TP->remove_magic_effect(TO);
    return 1;
}

void
start()
{
    if(move(spell_target))
    {
        tell_object(spell_target,"But you were not able to carry it, so it "+
        "vanishes.\n");
        remove_object();
    }
    set_this_player(spell_target);
    command_wear();
}

public int
dispel_spell_effect(object ob)
{
    tell_object(spell_target,"Your bone shield is dispeled by "+
    ob->query_the_name(spell_target)+"!\n");
    tell_object(ob,"You dispel the bone shield around "+
    spell_target->query_the_name(ob)+"!\n");
    remove_object();
    return 1;
}

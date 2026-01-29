/* 
 * /d/Kalad/common/guilds/khiraa/dk/obj/glowing_sh.c
 * Purpose    : This is the shadow that is cloned through the spells 
 * kblade and karmour. It adds the short 'glowing' to it without distrubing
 * weapons with vbfc shorts.
 * Located    : From the spells karmour and kblade
 * Created By : Sarr 14.May.97
 * Modified By: 
 */ 

#pragma save_binary
#pragma strict_types

#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"
#include "/d/Kalad/common/guilds/khiraa/magic.h"

inherit "/std/shadow";
inherit SPELL_EFFECT_OBJECT;

int gPen;
int gAc;

string
short()
{
    return "glowing "+shadow_who->short();
}


void
remove_it()
{
    if(gPen != -1)
    {
        shadow_who->set_pen(shadow_who->query_pen() - gPen);
        shadow_who->set_hit(shadow_who->query_hit() - gAc);
        if(shadow_who->query_wielded())
            shadow_who->update_weapon(shadow_who);
    }
    else
    {
        shadow_who->set_ac(shadow_who->query_ac() - gAc);
        if(shadow_who->query_worn())
            shadow_who->update_armour(shadow_who);
    }
}

void
remove_glowing_shadow()
{
    if(living(E(shadow_who)))
    {
        tell_room(E(E(shadow_who)),QCTNAME(E(shadow_who))+"'s "+
        short()+" suddenly stops glowing.\n",E(shadow_who));
        tell_object(E(shadow_who),"Your "+short()+" stops glowing.\n");
    }
    remove_it();
    remove_shadow();
}

void
start()
{
    shadow_me(spell_target);    
}

void
set_remove_time(int pen, int ac, float time)
{
    gPen = pen;
    gAc = ac;
    if(pen != -1)
    {
        shadow_who->set_pen(shadow_who->query_pen() + pen);
        shadow_who->set_hit(shadow_who->query_hit() + ac);
    }
    else
    {
        shadow_who->set_ac(shadow_who->query_ac() + ac);
    }
    set_alarm(time,0.0,&remove_glowing_shadow());
}

int
query_glowing_shadow()
{
    return 1;
}

public int
dispel_spell_effect(object dispeler)
{
    tell_object(dispeler,"You dispel the magic around the "+shadow_who->short()+"!\n");
    tell_room(E(dispeler),QCTNAME(dispeler)+" dispels the magic around the "+
    shadow_who->short()+"!\n",dispeler);
    remove_glowing_shadow();
    return 1;
}

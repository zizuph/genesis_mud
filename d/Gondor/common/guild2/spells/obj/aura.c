/* 
 *	This is a magic aura, protecting the wearer from blows.
 */
#pragma strict_types

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
 
#define MAGIC_STR 20
 
int     remove_shield();

static int    a_end;

void
create_armour()
{
    set_name(({"aura", "aura of death", }));
    add_name("_morgul_aura");
    add_name("deathaura");
    set_adj("death");
    set_short("aura of death");
    set_long("A magical aura of the forces of death that surround and "+
      "protect your body.\n");
    add_prop(OBJ_I_VALUE,    0);
    add_prop(OBJ_I_VOLUME,   0);
    add_prop(OBJ_I_WEIGHT,   0);
    add_prop(OBJ_I_INVIS,   20);
    add_prop(OBJ_I_NO_DROP,  1);
    add_prop(MAGIC_I_RES_MAGIC, 100);
    add_prop(MAGIC_I_RES_DEATH, 100);
    add_prop(MAGIC_I_RES_LIFE,  100);
    add_prop(MAGIC_I_RES_COLD,   50);
    add_prop(MAGIC_I_RES_FIRE,   50);
    add_prop(OBJ_I_RES_MAGIC,   100);
    add_prop(OBJ_I_RES_DEATH,   100);
    add_prop(OBJ_I_RES_LIFE,    100);
    add_prop(OBJ_I_RES_COLD,     50);
    add_prop(OBJ_I_RES_FIRE,     50);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, "@@wizinfo@@");
    add_prop(MAGIC_AM_MAGIC, ({ MAGIC_STR, "abjuration" }) );
    add_prop(MAGIC_AM_ID_INFO, ({
	"The aura will protect your entire body.\n", 0}) );
 
    set_default_armour(15+random(11), A_MAGIC);

    set_likely_cond(0);
    set_likely_break(0);
}
 
int
query_time()
{
    return ftoi(get_alarm(a_end)[2]);
}

string
wizinfo()
{
    return "The spellobject for the 'ringurth' spell of the Morgul Mages.\n"
      + "A magical armour of armour class "+query_ac()+".\n"
      + "Magic form: abjuration, strength: " + MAGIC_STR + ".\n"
      + "Magic resistance: MAGIC_I_RES_MAGIC: 40, additive,\n"
      + "                  MAGIC_I_RES_DEATH: 40, additive,\n"
      + "                  MAGIC_I_RES_LIFE:  70, non-additive,\n"
      + "                  MAGIC_I_RES_COLD:  50, non-additive,\n"
      + "                  MAGIC_I_RES_FIRE:  50, non-additive.\n"
      + "The armour will expire in " +query_time()+ " seconds.\n";
}

void
set_duration(int dur)
{
    if (!a_end)
        a_end = set_alarm(itof(dur), 0.0, remove_shield);
}
 
int
remove_shield()
{
    if (!worn || !objectp(wearer))
        return 0;
    worn = 0;
 
    wearer->remove_arm(TO);
    wearer->remove_magic_effect(TO);
    tell_object(wearer,"The chill of death departs silently, "+
      "leaving you feeling less protected.\n");
    tell_room(ENV(wearer),"Warmth creeps back into your bones as "+
      "the chill of death departs.\n",wearer);
    remove_object();
    return 1;
}
 
void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (!objectp(dest) || !living(dest))
        return;

    wearer = dest;
    worn = 1;
    tell_object(dest, "You entreat the Dark Lord to protect you from "
      + "harm, and the chill of death surrounds you in response.\n");
    tell_room(environment(dest), "The chill of death surrounds "
      + QTNAME(dest)+" and settles into your bones.\n",dest);
    wearer->wear_arm(TO);
    wearer->add_magic_effect(TO);
}
 
void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    set_alarm(0.0, 0.0, remove_shield);
}
 
int *
query_shield_slots()
{
    return ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS });
}
 
int
dispel_magic(int magic)
{
    if (magic > MAGIC_STR)
    {
        set_alarm(1.0, 0.0, remove_shield);
        return 1;
    }
    return 0;
}
 
/*
  *  A magical aura cannot break, but where other armours break,
  *  this one will just disappear.
  */
varargs void
remove_broken(int silent = 0)
{
    set_alarm(0.0, 0.0, remove_shield);
}

mixed
query_magic_protection(string prop, object who = previous_object())
{
    object  player = ENV(TO);

    if (who == player)
    {
        switch (prop)
        {
        case MAGIC_I_RES_MAGIC:   return ({40, 1});
        case MAGIC_I_RES_DEATH:   return ({40, 1});
        case MAGIC_I_RES_LIFE:    return ({70, 0});
        case MAGIC_I_RES_COLD:    return ({50, 0});
        case MAGIC_I_RES_FIRE:    return ({50, 0});
        }
    }

    return ::query_magic_protection(prop, who);
}

string query_recover() { return 0; }


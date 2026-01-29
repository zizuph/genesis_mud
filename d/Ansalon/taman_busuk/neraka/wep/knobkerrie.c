inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Ansalon/common/defs.h"

#define HIT 22
#define PEN 16

create_weapon()
{
    set_name("knobkerry");
    set_short("knobkerry");
    add_name("club");
    set_long("The knobkerry is a short wooden club with a knobbed head.\n");
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN)+random(30)-15);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 2500);
}

int
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    object me = environment(this_object());
    string s;

    if (hdesc != "head")
	return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);

    switch(phurt)
    {
    case -1:
    case -2:
	return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
    case 0..15:
	s = ", softly";
	break;
    case 16..31:
	s = "";
	break;
    case 32..50:
	s = ", hard";
	break;
    case 51..70:
	s = ", very hard";
	break;
    case 71..87:
	s = ", with a vengeance";
	break;
    case 88..99:
	s = ", so hard the weapon almost breaks";
	break;
    default:
	s = ", dealing a fatal blow";
    }
    me->catch_msg("Gripping your knobkerry hard, you clout " +
      QTNAME(enemy) + " about the head" + s + ".\n");
    enemy->catch_msg("Gripping " + POSSESSIVE(me) + " knobkerry hard, " +
      QTNAME(me) + " clouts you about the head" + s + ".\n");
    me->tell_watcher("Gripping " + POSSESSIVE(me) + " knobkerry hard, " +
      QTNAME(me)+ " clouts " +QTNAME(enemy)+ " about the head" + s + ".\n", enemy);

    ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
    return 1;
}

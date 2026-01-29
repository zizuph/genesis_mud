/* -*- Mode: C -*-
 *
 * obj/wep/mage-dagger.c
 *
 * Skippern 20(c)02
 *
 * This is a dagger which the mage uses, if he cant find his quarterstaff.
 * This should have some side effects, but not anything large.
 *
 * I have tried to make the special damage be weakened if the victim have
 * magical resistance.
 */
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define HIT 25
#define PEN 30

/* Global variables */
static int   Charge, Fire, Ice;

/* Prototypes */
       int   charged();
       int   charge_me(string arg);
       int   fire_me(string arg);
       int   freeze_me(string arg);

/* Code */
void
create_weapon()
{
    set_name("dagger");
    set_short("black dagger");
    set_pshort("black daggers");
    set_adj("black");
    set_long(&long());

    set_may_not_recover();

    set_hit(HIT);
    set_pen(PEN);

    set_wt(W_KNIFE);
    set_dt(W_IMPALE|W_SLASH);

    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(40) - 20 );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD) +
	     random(70) - 45 );
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_I_LIGHT, &charged());
    add_prop(MAGIC_AM_MAGIC, ({ 22, "enchantment" }));
    add_prop(OBJ_I_HAS_FIRE, 10);
    add_prop(OBJ_I_RES_ACID, 10);
    add_prop(OBJ_I_RES_COLD, 5);
    add_prop(OBJ_I_RES_ELECTRICITY, 10);
    add_prop(OBJ_I_RES_WATER, 10);
    add_prop(OBJ_I_RES_FIRE, 10);
    add_prop(OBJ_S_WIZINFO, "This is a magical dagger to be found on the " +
	     "mage in Dol Amroth when he is not holding his quarterstaff. " +
	     "The dagger have a special ability who is dependent on " +
	     "charges. Call query_charges() in the dagger to see how many " +
	     "charges are left. You can <charge>, <fire> and <freeze> the dagger.\n");
    add_prop(OBJ_M_NO_BUY, "A voice tells you: Don't sell my dagger. Return " +
	     "it to me instead.\n");
    add_prop(OBJ_M_NO_SELL, "A voice tells you: Don't sell my dagger. " +
	     "Return it to me instead.\n");
    add_prop(MAGIC_AM_ID_INFO, ({ "This dagger have some special abilities. " +
				      "It can be charged to use them.\n", 25,
				  "This dagger have some special abilities. " +
				      "It can be charged to use them. It " +
				      "can deliver fire or cold damage.\n", 50,
				  "This dagger have some special abilities. " +
				      "It can be charged to use them. It " +
				      "can deliver fire or cold damage. " +
				      "It can hold as many as 10 charges.\n", 
				      70 }) );

    Charge = 2;
    Ice = 0;
    Fire = 0;
}

void
init()
{
    ::init();
    add_action(charge_me, "charge");
    add_action(fire_me, "fire");
    add_action(freeze_me, "freeze");
}

int
charged()
{
    if (Charge == 0)
	return 0;
    if (Charge && Fire)
	return 2;
    return 1;
}

string
long()
{
    string r;

    r = "This is a black dagger.";

    if (Charge)
	r += " A faint blue light can be seen " +
	    "along its edge.";

    if (Fire && query_wielded())
	r += " A flame rushes along the blade.";
    else if (Ice && query_wielded())
	r += " The hilt feels cold.";

    r += "\n";
    return r;
}

void
charge_dagger()
{
    if (Charge > 9)
	return;

    Charge++;
}

void start_ice() 
{
    Ice = 1; 
}
void 
stop_ice() 
{ 
    Ice = 0; 
}

void 
start_fire() 
{
    Fire = 1; 
}
void stop_fire()  
{    
    Fire = 0; 
}

void
unwield(object dagger)
{
    if (Fire == 1)
	stop_fire();
    if (Ice == 1)
	stop_ice();
}

int 
charge_me(string arg)
{
    object tp = query_wielded();
    int    max_hp, Cost_hp;

    if (arg != "dagger")
	return 0;

    if (Fire)
        stop_fire();
    if (Ice)
        stop_ice();

    if (!objectp(tp))
    {
	notify_fail("You have to wield the dagger to do that.\n");
	return 0;
    }

    max_hp = tp->query_max_hp();
    Cost_hp = max_hp / 10;

    if (tp->query_hp() < Cost_hp)
    {
	write("You feel a sever pain in your hand as the dagger tries to " +
	      "charge itself.\n");
	say(QCTNAME(tp)+" winces in pain.\n");
	tp->set_hp(1);
	return 1;
    }

    if (Charge > 9)
    {
	notify_fail("You fail to charge this dagger any more.\n");
	return 0;
    }

    write("You scream out in pain as the "+short()+" draws power from " +
	  "your blood and charges itself.\n");
    say(QCTNAME(tp) + " screams out in pain.\n");
    tp->heal_hp(-Cost_hp);

    charge_dagger();

    return 1;
}

int
fire_me(string arg)
{
    object tp = query_wielded();

    if (arg != "dagger")
	return 0;

    if (!objectp(tp))
    {
        notify_fail("You have to wield the dagger to do that.\n");
        return 0;
    }

    if (Ice)
    {
	write("The cold feeling on the hilt of the "+short()+" disappears.\n");
	stop_ice();
    }

    if (Charge == 0 && !Fire)
    {
        write("There are no more charges in the dagger.\n");
        return 1;
    }

    if (Fire)
    {
	write("The flames retard from the blade of the "+short()+".\n");
	stop_fire();
	return 1;
    }
    else
    {
	write("A flame shoots forth and engulfs the blade of your "+short()+
	      ".\n");
	start_fire();
	if (wielder->query_name() != "halvgorn_the_mage")
	    Charge--;
	return 1;
    }
}

int
freeze_me(string arg)
{
    object tp = query_wielded();

    if (arg != "dagger")
	return 0;

    if (!objectp(tp))
    {
        notify_fail("You have to wield the dagger to do that.\n");
        return 0;
    }

    if (Fire)
    {
        write("The flames retard from the blade of the "+short()+".\n");
	stop_fire();
    }

    if (Charge == 0 && !Ice)
    {
	write("There are no more charges in the dagger.\n");
	return 1;
    }

    if (!Ice)
    {
        write("A chill runs down your spine as the hilt of your "+short()+
	      " gets cold.\n");
	start_ice();
        if (wielder->query_name() != "halvgorn_the_mage")
	    Charge--;
	return 1;
    }
    else
    {
	write("The cold feeling on the hilt of the "+short()+" disappears.\n");
	stop_ice();
	return 1;
    }
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    string w_msg, e_msg, o_msg;
    int    xdam, f_res, c_res, m_res, res = 0;
    object wielder = query_wielded();

    if (dt == W_BLUDGEON) return 0;

    if (dam < 10)
	return 0;

    f_res = enemy->query_magic_res(MAGIC_I_RES_FIRE);
    if (enemy->query_magic_res(OBJ_I_RES_FIRE) > f_res)
	f_res = enemy->query_magic_res(OBJ_I_RES_FIRE);
    c_res = enemy->query_magic_res(MAGIC_I_RES_COLD);
    if (enemy->query_magic_res(OBJ_I_RES_COLD) > c_res)
	c_res = enemy->query_magic_res(OBJ_I_RES_COLD);
    m_res = enemy->query_magic_res(MAGIC_I_RES_MAGIC);
    if (enemy->query_magic_res(OBJ_I_RES_MAGIC) > m_res)
	m_res = enemy->query_magic_res(OBJ_I_RES_MAGIC);

    if (Fire)
    {
	xdam = dam / 10;

	if (f_res > 1 && m_res > 1)
	    res = ftoi((1.0 - (1.0 -(itof(f_res)/100.0))*
			(1.0-itof(m_res)/100.0)) * 100.0);
	else if (f_res > 1)
	    res = f_res;
	else if (m_res > 1)
	    res = m_res;

	xdam = ftoi(itof(xdam) - (itof(xdam) * (itof(res) / 100.0)));

	if (xdam < 1)
	    return 0;

	if (dt == W_IMPALE)
	{
	    o_msg = "Smoke appears from a wound on " + QTPNAME(enemy) +
                " "+ hdesc + ".\n";
            w_msg = "Smoke appears from a wound on " + 
		enemy->query_the_possessive_name(wielder)+" "+ hdesc + ".\n";
	    e_msg = "You feel a burning heat from " + 
		wielder->query_the_possessive_name(enemy)+" stab wound.\n";
	}
	if (dt == W_SLASH)
	{
            w_msg = "You notice smoke coming from the mark you left on " +
		enemy->query_the_possessive_name(wielder)+" skin.\n";
            e_msg = "You feel a burning pain as the "+short()+" leaves " +
		"a mark on your skin.\n";
	    o_msg = "Smoke appears from a wound on " + QTPNAME(enemy) +
		" "+ hdesc + ".\n";
	}

	enemy->heal_hp(-xdam);
    }
    else if (Ice)
    {
	xdam = dam / 10;

        if (c_res > 1 && m_res > 1)
            res = ftoi((1.0 - (1.0-(itof(c_res)/100.0))*
			(1.0-itof(m_res)/100.0)) * 100.0);
        else if (c_res > 1)
            res = c_res;
        else if (m_res > 1)
            res = m_res;

        xdam = ftoi(itof(xdam) - (itof(xdam) * (itof(res) / 100.0)));

	if (xdam < 1)
	    return 0;

        if (dt == W_IMPALE)
        {
            e_msg = "It feels like a spine of ice is stabbed into your " +
		hdesc + ".\n";
	    o_msg = "A faint blue mist appears around " +QTPNAME(wielder)+
		" "+short()+" as "+wielder->query_pronoun()+" stabs "+
		QTPNAME(enemy)+" "+hdesc+".\n";
	    w_msg = "A faint blue mist appears around your " + short() +
		"as you stab " + enemy->query_the_possessive_name(wielder) +
		" " + hdesc + ".\n";
        }
        if (dt == W_SLASH)
        {
//	    w_msg = "You cut "+enemy->query_the_name(wielder)+" with your " +
//		short()+".\n";
            e_msg = "You feel cold as if you where cut by an ice dagger.\n";
//	    o_msg = QCTPNAME(enemy) + " " + hdesc + "is cut by " + 
//		QTPNAME(wielder) + " " + short() + ".\n";
        }

      	enemy->heal_hp(-xdam);
    }

    if (Fire || Ice)
    {
	if (strlen(w_msg))
	    wielder->catch_tell(w_msg);
	if (strlen(e_msg))
	    enemy->catch_tell(e_msg);
	if (strlen(o_msg))
	    wielder->tell_watcher(o_msg, enemy);
    
	if (wielder->query_name() != "halvgorn_the_mage")
	    Charge--;
    }
    if (!Charge)
    {
	if (Fire) stop_fire();
	if (Ice) stop_ice();
	write("The powers in your "+short()+" fades as you have used the " +
	      "last charge.\n");
    }

    return 0;
}

int query_charges() { return Charge; }

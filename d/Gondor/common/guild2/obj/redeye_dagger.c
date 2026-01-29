/*
 *	/d/Gondor/common/guild2/obj/redeye_dagger.c
 *
 *	A dagger for the naming ceremony
 *
 *	Olorin, November 1995
 * 
 * Palmer April 23, 2006
 * Added fixes to let wizards wield
 *
 */
#pragma strict_types

inherit "/std/weapon.c";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define HE(x)	(x)->query_pronoun()

void
create_weapon()
{
    set_name("dagger");
    add_name(({"_Red_Eye_Dagger", "knife", }));
    set_adj(({"sharp", "ceremonial", "steel", }));
    set_short("ceremonial dagger");
    set_long(BSN("The dagger is intricately ornamented, clearly not "
      + "destined for daily or casual use. The blade is wrought from "
      + "steel. The hilt is decorated with the picture of an eye "
      + "red as blood."));

    set_default_weapon(5, 5, W_KNIFE, W_SLASH|W_IMPALE, W_ANYH, TO);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 100, "conjuration" }));
    add_prop(MAGIC_AM_ID_INFO, ({ "This ceremonial dagger is a tool of the "
      + "highest servants of the Dark Lord.\n", 1,
        "Unauthorized use will be punished!\n", 10, }));
    add_prop(OBJ_S_WIZINFO, "A ceremonial dagger for use in the ceremony "
      + "in which an apprentice in the Society of Morgul Mages is promoted "
      + "to full mage. Outside the ceremony, the use is minimal, and no "
      + "magic effects are effective, besides a protection against "
      + "unauthorized use.\n");
}

mixed
wield(object wep)
{
    if (TP->query_wiz_level() || TP->query_nazgul())
    {
        write("As you wield the dagger, you feel the glare of the "
          + "Red Eye resting upon you.\n");
        return 1;
    }

    TP->heal_hp(- (TP->query_max_hp() / 2) - 100);
    return "As you try to wield the "+short()+" you feel something "
      + "terrible watching you.\n"
      + "The "+short()+" starts to glow and disappears.\n"
      + "You are hurt!\n";
}

public int
do_cut(string str)
{
    int     i;
    object  tp = TP,
           *victim,
            eye;

    if (member_array(TO, tp->query_weapon(-1)) < 0)
        return 0;

    NFN("Cut what?");
    if (!strlen(str))
        return 0;

    str = LOW(str);

    NFN("Cut what from what?");
    if (!parse_command(str, ENV(tp),
        " [the] 'eyes' 'from' / 'of' [the] [head] [skull] [of] %l [out] ",
        victim))
        return 0;

    victim = NORMAL_ACCESS(victim, 0, 0) - ({ 0 });
    if (!sizeof(victim))
        return 0;

    
    if (!TP->query_wiz_level() && !victim[0]->query_prop("_Morgul_remove_eyes"))
    {
        write("The Dark Lord does not give you the power to use this "
          + short() + " in this way on " + victim[0]->query_the_name(TP) + "!\n");
        return 1;
    }

    write("Using the "+short()+", you cut the eyes of "
      + victim[0]->query_the_name(tp) + " out.\n");
    victim[0]->catch_msg("With "+LANG_ADDART(short())+", "
      + QTNAME(tp) + " draws nearer to you while you are unable to move.\n"
      + "You see the "+short()+" approach your eyes, and then darkness "
      + "falls!\n"
      + "A fiery pain spreads from your now empty eyesockets through "
      + "your whole body.\n"
      + "You wish you could die!\n");
    tell_room(ENV(TP), QCTNAME(TP) + " approaches " + QTNAME(victim[0])
      + ", wielding " + LANG_ADDART(short()) + ".\n"
      + "Then, suddenly, with two quick cuts, " + HE(TP) + " cuts out "
      + "the eyes of "+QTNAME(victim[0])+" out of their sockets.\n"
      + QCTNAME(victim[0]) + " groans in pain.\n", ({ TP, victim[0] }) );

    victim[0]->heal_hp( - (victim[0]->query_hp() - 1) );
    victim[0]->add_prop(LIVE_I_SEE_DARK, -999);
    victim[0]->remove_prop("_Morgul_remove_eyes");

    FIX_EUID

    for (i = 0; i < 2; i++)
    {
        eye = clone_object("/std/leftover");
        eye->leftover_init("eye", victim[0]->query_race_name());
        eye->set_decay_time(120);
        eye->set_long("This is the bloody eye eye of " + LANG_ADDART(victim[0]->query_race_name()) + ".\n");
        if (eye->move(TP))
            if (eye->move(TO))
                eye->move(TO, 1);
    }
    return 1;
}

void
init()
{
    ::init();

    add_action(do_cut, "cut");
}


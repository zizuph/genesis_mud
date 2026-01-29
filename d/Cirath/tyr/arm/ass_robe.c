/* 
 *	/d/Gondor/common/guild2/mage_robe.c
 *
 *	The robe of the Mogul Mages
 *	modified from the ranger ring
 *
 *	Olorin, 05-jan-1994
 *
 *	Copyright (c) 1996, 1997 by Christian Markus (Olorin)
 *
 *	Modification log:
 */
#pragma save_binary
#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "lib/morgul_defs.h"

#define HIS(x)	(x)->query_possessive()

/*
 *      Global variables:
 */
static  object  Shadow;

public int     query_value() { return 0; }

/*
 * Function name: create_armour
 * Description:   Creator.
 */
public void
create_armour()
{
    set_name(({"robe","cloak"}));
    add_name(({"morgul_guild_object", "token", "guild token", 
                   "mage token","morgul token"}));
    set_adj(({"large", "black", "hooded"}));
    set_short("black hooded robe");
    set_long("This is a large black robe, with a wide hood.\n");
    add_item(({"hood", "wide hood", }), BSN("When worn over the head "
        + "the wide hood of the robe will hide the features of the "
        + "person wearing the robe."));
    set_ac(1);
    set_af(TO);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,     0);
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME,  650);
    add_prop(OBJ_I_NO_DROP,   1);

    FIX_EUID;
}

/*
 * Function name: query_auto_load
 * Description:   Makes this object autoloadable.
 * Returns:       the autoload string
 */
public string
query_auto_load()
{
    return MASTER + ":";
}

/*
 * Function name: check_spell_object
 * Description:   load the spell object
 */
private void
check_spell_object(object player)
{
    if ((ENV(TO) == player) &&
        (!objectp(present("Morgul_Spell_Object", player))))  
        clone_object(GUILD_DIR + "spells/morgul_spells")->move(player, 1); 
}

/*
 * Function name: remove
 * Description:	  the remove function for the robe
 * Argument:      ob - object pointer to the robe
 * Returns:       int  0 - No effect, the armour can be removed
 *                     1 - It can be removed but no text should be
 *                         printed (it was done in the function)
 *                    -1 - It can not be removed, default failmsg will
 *                         be written 
 *                string - It cannot be removed, 'string' is the fail
 *                         message to print 
 */
public mixed
remove(object ob)
{
    if (ob != TO)
        return -1;

    if (TP->query_hooded())
        Shadow->remove_shadow();

    return 0;
}

/*
 * Function name: wear
 * Description  : This function might be called when someone tries to wear
 *                this armour. To have it called, use set_af().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */
public mixed
wear(object ob)
{
    object  tp = TP;

    if (ob != TO)
        return -1;

    if (tp->query_guild_name_occ() == GUILD_NAME || tp->query_real_name() == "gibreel")
    {
        write("You wear the "+query_short()+" around your body.\n"+
              "You feel the dark power of Black Sorcery flowing through you.\n");
        say(QCTNAME(tp)+" wears "+LANG_ASHORT(TO)+".\n");
        check_spell_object(tp);
        present("Morgul_Spell_Object", tp)->update_morgul_spells();
        return 1;
    }
    tp->heal_hp(-(tp->query_max_hp()/20));
    set_alarm(0.0, 0.0, remove_object);
    return "When you try to wear the " + query_short() +
        ", it bursts out in flames and disappears.\n"; 
}

/* 
 * Function name: init_arg
 * Description  : Called when autoloading.
 * Arguments    : string arg - the auto-load argument.
 */
public varargs void 
init_arg(string str)
{
    object  tp = TP;

    if (tp->query_guild_name_occ() != GUILD_NAME)
    {
        write("The "+query_short()+" bursts out in flames and disappears!\n");
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    // Give them the spell object
    set_alarm(1.0, 0.0, &check_spell_object(tp));
}

/*
 * Function name: query_recover
 * Description:	  no recovery, since the robe autoloads
 * Returns:       0
 */
public string query_recover() { return 0; }

/*
 * Function name: leave_env
 * Description:   remove the hood shadow if the robe leaves its
 *                environment 
 * Arguments:     from - old environment, to - new environment
 */
public void
leave_env(object from, object to)
{
    if (objectp(from) && from->query_hooded())
    {
        Shadow->remove_shadow();
    }

    ::leave_env(from, to);
}

/*
 *Function name: do_hood
 *Description:   wear the hood
 *Argument:      command verb argument
 *Returns:       1/0
 */
public int
do_hood(string str)
{
    string  vb = query_verb(),
            pron;

    if (vb == "hood")
        pron = "whom";
    else
        pron = "what";

    NFN(CAP(vb)+" "+pron+"?");
    if (!strlen(str))
        return 0;

    if ((vb == "hood") && ((str != "me") && (LOW(str) !=
        ENV(TO)->query_real_name()))) 
        return 0;

    if ((vb == "wear") && (str != "hood"))
        return 0;

    if (ENV(TO) != TP)
    {
        NFN("You do not have the robe!");
        return 0;
    }

    if (query_worn() != TP)
    {
        NFN("You do not wear your robe!");
        return 0;
    }

    if (TP->query_hooded())
    {
        NFN("You are already wearing your hood!");
        return 0;
    }

    write("You pull the hood of your robe over your head, concealing your features.\n");
    say(QCTNAME(TP)+" pulls the hood of "+HIS(TP)+" robe over "
      + HIS(TP) + " head, concealing " + HIS(TP) + " features.\n");

    Shadow = clone_object(GUILD_DIR + "obj/hood_shadow");
    Shadow->shadow_me(TP);
    return 1;
}

/*
 * Function name: do_reveal
 * Description:   remove the hood
 * Argument:      str - argument
 *                silent - write no message if 1
 * Returns:       1/0
 */
public int
do_reveal(string str, int silent = 0)
{
    string  vb = query_verb(),
            pron;

    switch (vb)
    {
    case "unhood":
    case "reveal":
        pron = "whom";
        break;
    case "mreveal":
        vb = "remove";
    case "remove":
        pron = "what";
        break;
    }

    NFN(CAP(vb)+ " "+pron+"?");
    if (!strlen(str))
        return 0;

    switch (vb)
    {
    case "unhood":
        if (str == "me")
            break;
        if (LOW(str) == ENV(TO)->query_real_name())
            break;
        NFN("You can only remove your own hood!");
        return 0;
        break;
    case "reveal":
        if (str == "me")
            break;
        if (LOW(str) == ENV(TO)->query_real_name())
            break;
        return 0;
        break;
    case "remove":
        if (str != "hood")
            return 0;
        break;
    }

    if (ENV(TO) != TP)
    {
        NFN("You do not have the robe!");
        return 0;
    }

    if (!TP->query_hooded())
    {
        NFN("You are not wearing your hood!");
        return 0;
    }

    if (!silent)
    {
        write("You remove the hood and reveal your face again.\n");
        say(QCTNAME(TP)+" removes "+HIS(TP)+" hood.\n");
    }

    Shadow->remove_hood_shadow();
    return 1;
}

public void
init()
{
    ::init();

    add_action(do_hood,   "hood");
    add_action(do_hood,   "wear");
    add_action(do_reveal, "reveal");
    add_action(do_reveal, "unhood");
    add_action(do_reveal, "remove");
}


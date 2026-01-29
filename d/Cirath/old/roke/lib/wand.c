/*
 * wand.c
 * FIXA
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*******************************************************************

  Gresolle's magic wand construction kit. 930624

  set_long
  set_short        - set descriptions for unidentified wands

  set_id_long
  set_id_short     - set descriptions for identified wands

  set_ident_limit  - set how hard it is to identify wand
                     identification depends on player's
		     SS_SPELLCRAFT + wisdom.

  create_wand      - create the wand

  set_charges      - set amount of charges in the wand

  set_charge_value - set the value of each charge

  set_zap_verb     - set the verb to use to zap the wand (default is 'zap')

  query_zap_verb   - returns the previously set zap verb

  set_fail_msg     - the message given to player when out of charges.
                     Default is 'The wand says poof.'

  set_wand_effect  - set the effect of the wand. This is simply a
                     mixed variable used for many purposes.

  set_wand_param   - set the parameter to the wand functions. This
                     is another mixed variable used for many purposes.

  set_wand_type    - select the type of the wand. This can be one
                     of WAND_SPECIAL, WAND_HEAL, WAND_SPELL or WAND_POOF.

		     WAND_SPECIAL - the zapping code calls the function
		     special_effect in the wand which gets the zapped
		     object as argument.

		     WAND_HEAL - heal the target. The target gets healed
		     averagely 'wandeffect' hp for each zap. (Set the
		     wandeffect with set_wand_effect.) 

		     WAND_MANA - as WAND_HEAL, but with mana.

		     WAND_STAT - add a tmp stat to the target. The
		     'wand effect' should be set to an array
		     containing ({stat,ds,dt}) (see doc on add_tmp_stat)

		     WAND_SPELL - load a 'spell file' and exec it with
		     the zapped persons name as argument.

		     The path to the spell file is set with
		     set_wand_effect, the function to call should be set 
		     with set_wand_param.
  
		     WAND_POOF - make the wand behave like if it is
		     out of charges.

		     Those values are declared in /d/Roke/gresolle/wand.h

  identify_me      - this is a way to permanently identify the
                     wand.

  zapping syntax
  ~~~~~~~~~~~~~~

  You should be able to: zap wand
                         zap wand at/on <someone>
			 zap wand of baba
			 zap wand of baba at/on <someone>

  (The zap wand of baba ... is really on the form of
  zap <objectname> of <adjective>)

  If you don't specify who to zap at/on, the wand assumes it is you.

  The wand calls the function 'notify_been_zapped' with itself as
  argument in the object being zapped, if you're not using
  wand type WAND_SPELL.

********************************************************************/

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>

#include "wand.h"

/*
 * defines (some default values)
 */

#define WEIGHT  100
#define VOLUME  100
#define VERB    "zap"

#define FAILMSG "The wand says poof.\n"

#define TP this_player()
#define TO this_object()

#define NF(x) notify_fail(x)

void set_ident_limit(int i);

/*
 * globals
 */

int charges, chargevalue, wandtype;
string zapverb, failmsg;
mixed wandeffect, wandparam;

string idshort, idlong;
string unidshort, unidlong;

int ident_limit, identified;


/* Prototypes */
void set_charges(int charg);

/* 
 * Function : enter_env
 * Descript : update wand identify status
 */
public void
enter_env(object dest, object old)
{
    if (!living(dest))
    {
        identified = 0;
        return;
    }

    if ((dest->query_skill(SS_SPELLCRAFT) + dest->query_stat(SS_WIS)) >
        (2 * ident_limit))
        identified = 1;
    else
        identified = 0;
}

/*
 * Function name: stat_object
 * Description:   Called when someone tries to stat the wand
 * Returns:       A string to write
 */
public string
stat_object()
{
    string str;

    str =::stat_object();

    str += "Charges     : " + charges + "\n";
    str += "Charge value: " + chargevalue + "\n";
    str += "Zap verb    : " + zapverb + "\n";
    str += "Unid-long   : " + unidlong + "\n";
    str += "Unid-short  : " + unidshort + "\n";
    str += "Id-long     : " + idlong + "\n";
    str += "Id-short    : " + idshort + "\n";
    str += "Wand type   : ";

    switch (wandtype)
    {
    case WAND_POOF:
        str += "WAND_POOF\n";
        break;
    case WAND_HEAL:
        str += "WAND_HEAL\n";
        break;
    case WAND_SPECIAL:
        str += "WAND_SPECIAL\n";
        break;
    case WAND_SPELL:
        str += "WAND_SPELL\n";
        break;
    case WAND_MANA:
        str += "WAND_MANA\n";
        break;
    case WAND_STAT:
        str += "WAND_STAT\n";
    }

    str += "Wand effect : " + wandeffect + "\n";
    str += "Wand param  : " + wandparam + "\n";
    str += "Fail msg    : " + failmsg + "\n";
    str += "Ident. lim. : " + ident_limit + "\n";

    return str;
}

/**************************************

  recovery functions

***************************************/
string
query_recover()
{
    string name;
    int i;
    sscanf(file_name(this_object()), "%s#%d", name, i);

    return name + ":" + charges;
}

void
init_recover(string s)
{
    set_charges(atoi(s));
}
/***************************************/

/* Function : set_long
 * Descript : set long description for unid'd wand
 */
void
set_long(string s)
{
    unidlong = s;
}
/* Function : set_short
 * Descript : set short description for unid'd wand
 */
void
set_short(string s)
{
    unidshort = s;
}

/* Function : set_id_short
 * Descript : set short description for id:d wand
 */
public void
set_id_short(string s)
{
    idshort = s;
    set_ident_limit(ident_limit);
}

/* Function : set_id_long
 * Descript : set long description for id:d wand
 */
public void
set_id_long(string s)
{
    idlong = s;
}

/* Function : set_ident_limit
 * Descript : set how hard it is to identify wand
 *            this value is used together with WIS & SPELLCRAFT
 *            to determine if player recognizes wand immediately
 */
public void
set_ident_limit(int i)
{
    ident_limit = i;
    add_prop(MAGIC_AM_ID_INFO, ({"stick", 0,
                                   "wand", i / 2,
                                   idshort, i}));
    add_prop(MAGIC_AM_MAGIC, ({i, "enchantment"}));
}

/* Function : set_wand_param
 * Descript : function in spell file etc
 */
public void
set_wand_param(mixed param)
{
    wandparam = param;
}

/*
 * Function : set_wand_effect
 * Descript : various params, spell file name, wand strength etc
 */
public void
set_wand_effect(mixed eff)
{
    wandeffect = eff;
}

/*
 * Function : set_wand_type
 * Descript : set the wand type (see wand.h)
 */
public void
set_wand_type(int type)
{
    wandtype = type;
}

/*
 * Function : set_fail_msg
 * Descript : set message displayed when wand is out of power 
 */
public void
set_fail_msg(string msg)
{
    failmsg = msg;
}

/*
 * Function : set_charges
 * Descript : set number of charges in the wand
 */
public void
set_charges(int charg)
{
    charges = charg;
}

/*
 * Function : set_charge_value
 * Descript : sets wand value/charge
 */

public void
set_charge_value(int value)
{
    chargevalue = value;
}

/*
 * Function : set_zap_verb
 * Descript : set the verb used to zap the wand
 *            default is - 'zap'
 */
public void
set_zap_verb(string verb)
{
    zapverb = verb;
}

/* 
 * Function : query_zap_verb
 * Descript : returns the zap verb 
 */
public string
query_zap_verb()
{
    return zapverb;
}

/*
 * Function : snok
 * Descript : calculate wand value
 */
public int
snok()
{
    return charges * chargevalue + chargevalue / 2;
}

/* 
 * Function : mylong
 * Descript : returns the long desc of the wand, depending on
 *            if the wand has been id'd or not
 */
public string
mylong()
{
    if (identified)
        return idlong;
    else
        return unidlong;
}

/*
 * Function : myshort
 * Descript : returns the short desc of the the wand, depending on
 *            if the wand is id'd or not
 */
public string
myshort()
{
    if (identified)
        return idshort;
    else
        return unidshort;
}

/*
 * Function : create_wand
 * Descript : create the wand
 *            mask this with your own function
 */
public void
create_wand()
{
}

/*
 * Function : create_object
 * Descript : well, if you don't know that...
 */
public nomask void
create_object()
{
    ::set_long("@@mylong");
    ::set_short("@@myshort");

    add_prop(OBJ_I_WEIGHT, WEIGHT);
    add_prop(OBJ_I_VOLUME, VOLUME);

    set_zap_verb(VERB);

    set_fail_msg(FAILMSG);

    set_wand_type(WAND_POOF);

    /* VERY IMPORTANT! DO NOT REDEFINE OBJ_I_VALUE!!! */

    add_prop(OBJ_I_VALUE, "@@snok");

    create_wand();
}

/* Function : init
 * Descript : add cmd's to player
 */
void
init()
{
    ::init();

    add_action("wave", "wave");
    add_action("zap", zapverb);
}

int
wave(string s)
{
    notify_fail("Wave what?\n");
    if (!id(s))
        return 0;

    TP->catch_msg("You wave your " + short () +
                  " in the air, but nothing happens.\n");
    say(QCTNAME(TP) + " waves a little in the air with some kind of " +
        query_name() + ".\n");
    return 1;
}

/* Function: identify_me
 * Descript: this function should be called by someone who wants
 *           to identify the wand permanently. (That is, a npc 
 *           wandidentify-shop or something.)
 * Returns : 1 if success, 0 else
 */
public int
identify_me()
{
    int i;

    i = TP->query_skill(SS_SPELLCRAFT) + TP->query_stat(SS_WIS);

    i = i / 2;

    if (random(i) < ident_limit)
    {
        /* success */

        ::set_long(idlong);
        ::set_short(idshort);
        return 1;
    }
    else
        return 0;
}

/*
 * Function : special_effect
 * Descript : defines any special wand effects
 */
public int
special_effect(object target)
{
    notify_fail(failmsg);
    return 0;
}

/*
 * Function : zap
 * Descript : find a wand and zap it
 */
int
zap(string s)
{
    object *wand, *target;
    string gunk, wn, wa;

    NF("You can't do that here.\n");
    if (environment(TP)->query_prop(ROOM_M_NO_MAGIC))
        return 0;

    notify_fail(zapverb + " what?\n");

    if (!s)
        return 0;

    if (!parse_command(s, environment(TO), "%s 'at' / 'on' %w", wn, gunk))
    {
        wn = s;
        s = s + " at me";
        gunk = "me";
    }

    wand = CMDPARSE_ONE_ITEM(wn, "check_wand", "check_wand");

    if (!sizeof(wand))
    {
        /* let's try with 'wand of babababa' */

        /* sigh */

        if (!parse_command(s, environment(TO), "%w 'of' %w 'at' / 'on' %w",
                           wa, wn, gunk))
            return 0;
        else
        {
            wn = wn + " " + wa;

            wand = CMDPARSE_ONE_ITEM(wn, "check_wand", "check_wand");

            if (!sizeof(wand))
                return 0;
        }
    }

    if (gunk == "me" || gunk == "")
        gunk = TP->query_real_name();

    return wand[0]->zappa(gunk);

}

/*
 * Function : check_wand
 * Descript : is it a usable wand?
 */
public int
check_wand(object ob)
{
    if (function_exists("zappa", ob) && ob->query_zap_verb() == zapverb &&
        present(ob, TP))
        return 1;
    return 0;
}

/* Function : make_tmp_stat
 * Descript : add a tmp stat to the target
 */
void
make_tmp_stat(object ob, int stat, int str, int dur)
{
    /* borrowed from herb_support */

    if (str > 0)
    {
        ob->add_tmp_stat(stat, random(str) + str / 2, random(str) + str / 2);
        if (stat == SS_STR)
            ob->catch_msg("You feel strengthened.\n");
        else if (stat == SS_DEX)
            ob->catch_msg("You feel more dexterious.\n");
        else if (stat == SS_CON)
            ob->catch_msg("You feel healthier.\n");
        else if (stat == SS_INT)
            ob->catch_msg("You feel brighter.\n");
        else if (stat == SS_WIS)
            ob->catch_msg("You feel wiser.\n");
        else if (stat == SS_DIS)
            ob->catch_msg("You feel more secure.\n");
        else
            write("You feel more clever.\n");
    }
    else if (str < 0)
    {
        ob->add_tmp_stat(stat, random(str) + str / 2, random(str) + str / 2);
        if (stat == SS_STR)
            ob->catch_msg("You feel weakened.\n");
        else if (stat == SS_DEX)
            ob->catch_msg("You feel slower.\n");
        else if (stat == SS_CON)
            ob->catch_msg("You feel less healthy.\n");
        else if (stat == SS_INT)
            ob->catch_msg("You feel stupider.\n");
        else if (stat == SS_WIS)
            ob->catch_msg("You feel less wise.\n");
        else if (stat == SS_DIS)
            ob->catch_msg("You feel more insecure.\n");
        else
            write("You feel less clever.\n");
    }
    else
        ob->catch_msg("You feel no effect.\n");
}

/* 
 * Function : zappa
 * Descript : perform the actual zapping
 */
public int
zappa(string s)
{
    object *target, ob;
    string gunk;

    if (!charges)
    {
        notify_fail(failmsg);
        return 0;
    }

    charges--;

    if (wandtype == WAND_SPELL)
    {

        TP->catch_msg("You " + zapverb + " the " + query_name() + " on " +
                      ((s == TP->query_real_name())? "yourself" : s) + ".\n");

        gunk = call_other(wandeffect, wandparam, s);

        if (gunk)
            TP->catch_msg(gunk + "\n");

        return 1;
    }

    if (!parse_command(s, environment(TP), "%s %l", gunk, target))
        ob = TP;
    else
        ob = target[1];

    notify_fail("You can't see " + QCTNAME(ob) + " here.\n");
    if (!CAN_SEE(TP, ob) && ob != TP)
        return 0;

    TP->catch_msg("You " + zapverb + " " + short () + " at " +
                  ((ob == TP) ? "yourself" : QCTNAME(ob)) + ".\n");
    say(QCTNAME(TP) + " " + zapverb + "s " + short () + " at " +
          ((ob == TP) ? TP->query_objective() + "self" : QCTNAME(ob)) +
        ".\n",
          (
              {
              TP, ob
              }
        ));
    if (TP != ob)
        ob->catch_msg(QCTNAME(TP) + " " + zapverb + "s " + short () +
                      " at you.\n");

    /* check the zapeffects here */

    /* tell the object that it has been zapped. this function was
       mostly added if you want a 'secret' function with a npc
       but still use the wand as normally */

    ob->notify_been_zapped(this_object());

    switch (wandtype)
    {
    case WAND_POOF:
        notify_fail(failmsg);
        return 0;
    case WAND_HEAL:
        ob->heal_hp(random(wandeffect) + wandeffect / 2);
        if (wandeffect >= 0)
            ob->catch_msg("You feel better.\n");
        else
        {
            ob->catch_msg("You feel bad.\n");
            ob->attack_object(TP);
        }
        return 1;
    case WAND_MANA:
        ob->add_mana(random(wandeffect) + wandeffect / 2);
        if (wandeffect >= 0)
            ob->catch_msg("Your mental powers increased.\n");
        else
            ob->catch_msg("You feel drained of mental powers.\n");
        return 1;

    case WAND_STAT:
        make_tmp_stat(ob, wandeffect[0], wandeffect[1], wandeffect[2]);
        return 1;

    case WAND_SPECIAL:
        return special_effect(ob);

    }
}

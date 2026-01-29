// Recode of Gresolle's wand code.


inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include "/d/Faerun/std/obj/wand.h"

#define WEIGHT  100
#define VOLUME  100
#define VERB    "zap"

#define FAILMSG "The wand says poof.\n"

#define TP this_player()
#define TO this_object()

#define NF(x) notify_fail(x)

// Global vars

int wandValue, chargeValue, wandType, charges, wandStat, wandChange, wandTime;
string zapVerb, failMsg;
mixed wandParam;

string idShort,idLong;
string unidShort,unidLong;

int identLimit = 0;
int identified = 0;

/*
 * Function : enter_env
 * Descript : update wand identify status
 */
public void enter_env(object dest,object old)
{
    ::enter_env(dest,old);
    // checks if user is an NPC. If so, do not identify wand
    if(!living(dest))
    {
	    identified = 0;
	    return;
    }

    // checks that user's spellcract skill and WIS is high enough to ID  wand
    if((dest->query_skill(SS_SPELLCRAFT) + dest->query_stat(SS_WIS)) > (2 * identLimit))
        identified = 1;
    else
        identified = 0;
}

/*
 * Function name: stat_object
 * Description:   Called when someone tries to stat the wand
 * Returns:       A string to write
 */
public string stat_object()
{
    string str;

    str=::stat_object();

    str += "Charges         : " + charges + "\n";
    str += "Charge value    : " + chargeValue + "\n";
    str += "Zap verb        : " + zapVerb + "\n";
    str += "Unid-long       : " + unidLong + "\n";
    str += "Unid-short      : " + unidShort + "\n";
    str += "Id-long         : " + idLong + "\n";
    str += "Id-short        : " + idShort + "\n";
    str += "Wand type       : ";

    switch(wandType)
    {
        case WAND_EMPTY:
            str += "WAND_EMPTY\n";
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
/*
        case WAND_MANA:
            str += "WAND_MANA\n";
            break;
*/
        case WAND_STAT:
            str += "WAND_STAT\n";
    }

//    str += "Wand effect     : " + wandEffect + "\n";
    str += "Wand param      : " + wandParam + "\n";
    str += "Fail msg        : " + failMsg + "\n";
    str += "Identify limit  : " + identLimit + "\n";

    return str;
}

/*
 * Recovery Functions
 */
query_recover()
{
    string name;
    int i;
    sscanf(file_name(this_object()),"%s#%d", name, i);

    return name + ":" + charges;
}

init_recover(string s)
{
    set_charges(atoi(s));
}

/*******************************/
/*
 * Function : set_ident_limit
 * Descript : set how hard it is to identify wand.
 *            this value is used together with WIS & SPELLCRAFT
 *            to determine if player recognizes wand immediately
 */
public void set_ident_limit(int limit)
{
    identLimit = limit;

    add_prop(MAGIC_AM_ID_INFO,({"stick", 0,
	        "wand", limit/2,
		    idShort, limit}));
    add_prop(MAGIC_AM_MAGIC,({limit, "enchantment"}));
}
/*
 * Function : set_long
 * Descript : set long description for unid'd wand
 */
set_long(string str)
{
    unidLong = str;
}

/*
 * Function : set_short
 * Descript : set short description for unid'd wand
 */
set_short(string str)
{
    unidShort = str;
}

/*
 * Function : set_id_short
 * Descript : set short description for id:d wand
 */
public void set_id_short(string str)
{
    idShort = str;
    set_ident_limit(identLimit);
}

/*
 * Function : set_wand_param
 * Descript : function in spell file etc
 */
public void set_wand_param(mixed param)
{
    wandParam = param;
}
/*
 * Function : set_effect_stat
 * Descript : sets the stat being affected
 */
public void set_effect_stat(int eff)
{
    // wandeffect[0]
    wandStat = eff;
}

/*
 * Function : set_effect_change
 * Descript : sets how much the stat is changed by
 */

public void set_effect_change(int eff)
{
    // wandeffect[1]
    wandChange = eff;
}
/*
 * Function : set_effect_time
 * Descript : sets how how long in heartbeats the effect lasts
 */

public void set_effect_time(int eff)
{
    // wandeffect[2]
    wandTime = eff;
}


/*
 * Function : set_wand_type
 * Descript : set the wand type (see wand.h)
 */
public void set_wand_type(int type)
{
    wandType = type;
}

/*
 * Function : set_fail_msg
 * Descript : set message displayed when wand is out of power
 */
public void set_fail_msg(string msg)
{
    failMsg = msg;
}

/*
 * Function : set_charges
 * Descript : set number of charges in the wand
 */
public void set_charges(int charge)
{
    charges = charge;
}

/*
 * Function : set_charge_value
 * Descript : sets wand value/charge
 */

public void set_charge_value(int value)
{
    chargeValue = value;
}

/*
 * Function : set_zap_verb
 * Descript : set the verb used to activate the wand
 *            default is - 'zap'
 */
public void set_zap_verb(string verb)
{
    zapVerb = verb;
}

/*
 * Function : calc_wand_value
 * Descript : calculate wand value
 */
public int calc_wand_value()
{
    return (charges * chargeValue) + (chargeValue / 2);
}

/*
 * Function : my_long
 * Descript : returns the long desc of the wand, depending on
 *            if the wand has been id'd or not
 */
public string my_long()
{
    if(identified)
        return idLong;
    else
        return unidLong;
}

/*
 * Function : my_short
 * Descript : returns the short desc of the the wand, depending on
 *            if the wand is id'd or not
 */
public string my_short()
{
    if(identified)
        return idShort;
    else
        return unidShort;
}


/* Function : init
 * Descript : add cmd's to player
 */
init()
{
    ::init();

    add_action("wave","wave");
    add_action("zap",zapVerb);
}

/*
 * Descript: Aleternate way of activating wand
 * Returns : 1 if success, 0 not successful
 */
wave(string str)
{
    NF("Wave what?\n");

    if(!id(str))
        return 0;

    TP->catch_msg("You wave your "+short()+" in the air, but nothing happens.\n");
    say(QCTNAME(TP)+" waves a " + query_name() + "in the air.\n");
    return 1;
}

/*
 *Function: identify_me
 * Descript: this function should be called by someone who wants
 *           to identify the wand permanently. (That is, a npc
 *           wandidentify-shop or something.)
 * Returns : 1 if success, 0 else
 */
public int identify_me()
{
    int i;

    i = TP->query_skill(SS_SPELLCRAFT) + TP->query_stat(SS_WIS);
    i = i / 2;

    if(random(i)<identLimit)
    {
      // success
        ::set_long(idLong);
        ::set_short(idShort);
        return 1;
    }
    else

    return 0;
}

/*
 * Function : special_effect
 * Descript : defines any special wand effects
 */
public int special_effect(object target)
{
    NF(failMsg);
    return 0;
}

/*
 * Function : zap
 * Descript : find a wand and zap it
 */
zap(string str)
{
    object *wand,*target;
    string gunk,wn,wa;

    NF("You can't do that here.\n");
    if(environment(TP)->query_prop(ROOM_M_NO_MAGIC))
        return 0;

    NF(zapVerb + " what?\n");

    if(!str)
        return 0;

    if(!parse_command(str,environment(TO),"%s 'at' / 'on' %w",wn,gunk))
    {
      wn = str;
      str = str + " at me";
      gunk = "me";
    }

    wand = CMDPARSE_ONE_ITEM(wn,"check_wand","check_wand");

    if(!sizeof(wand))
    {
      // let's try with 'wand of babababa'

        if(!parse_command(str,environment(TO),"%w 'of' %w 'at' / 'on' %w",wa,wn,gunk))
	        return 0;
        else
	    {
	        wn = wn + " " + wa;
	        wand = CMDPARSE_ONE_ITEM(wn,"check_wand","check_wand");

	        if(!sizeof(wand))
	            return 0;
	    }
    }

    if(gunk == "me" || gunk == "")
        gunk = TP->query_real_name();

    return wand[0]->zap_wand(gunk);
}

/*
 * Function : check_wand
 * Descript : is it a usable wand?
 */
public int check_wand(object ob)
{
    if(function_exists("zap_wand",ob) && ob->query_zap_verb() == zapVerb && present(ob,TP))
        return 1;
  return 0;
}

/* Function : make_tmp_stat
 * Descript : add a tmp stat to the target
 */
make_tmp_stat(object ob,int stat,int str,int dur)
{
    if (str > 0)
    {
        ob->add_tmp_stat(stat, random(str) + str / 2,random(dur) + dur / 2);
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
        else write("You feel more clever.\n");
    }
    else if(str < 0)
    {
        ob->add_tmp_stat(stat, random(str) + str / 2,random(dur) + dur / 2);
        if (stat == SS_STR) ob->catch_msg("You feel weakened.\n");
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
        else write("You feel less clever.\n");
    }
    else
        ob->catch_msg("You feel no effect.\n");
}

/*
 * Function : zap_wand
 * Descript : perform the actual zapping
 */
public int zap_wand(string s)
{
    object *target,ob;
    string gunk;

    if(!charges)
    {
        NF(failMsg);
        return 0;
    }

    charges--;

    if(wandType == WAND_SPELL)
    {
        TP->catch_msg("You "+zapVerb+" the "+query_name()+" on " +
            ((s == TP->query_real_name())?"yourself":s) + ".\n");
        gunk = call_other(wandStat,wandParam);

        if(gunk)
	        TP->catch_msg(gunk+"\n");
        return 1;
    }

    if(!parse_command(s,environment(TP),"%s %l",gunk,target))
        ob = TP;
    else
        ob = target[1];

    NF("You can't see " + QCTNAME(ob) + " here.\n");
    if(!CAN_SEE(TP,ob) && ob!=TP)
        return 0;

    TP->catch_msg("You " + zapVerb + " " + short() + " at " +
		((ob==TP)?"yourself":QCTNAME(ob)) + ".\n");
    say(QCTNAME(TP) + " " + zapVerb + "s " + short() + " at " +
        ((ob==TP)?TP->query_objective() + "self":QCTNAME(ob)) + ".\n",
        ({TP,ob}));
    if(TP!=ob)
        ob->catch_msg(QCTNAME(TP) + " " + zapVerb + "s "+short() + " at you.\n");

  /* check the zapeffects here */

  /* tell the object that it has been zapped. this function was
     mostly added if you want a 'secret' function with a npc
     but still use the wand as normally */

    ob->notify_been_zapped(TO);

    switch(wandType)
    {
        case WAND_EMPTY:
            NF(failMsg);
            return 0;
        case WAND_HEAL:
            ob->heal_hp(random(chargeValue)+chargeValue/2);
            if(chargeValue>=0)
	            ob->catch_msg("You feel better.\n");
            else
	        {
	            ob->catch_msg("You feel bad.\n");
	            ob->attack_object(TP);
	        }
            return 1;
/*
        case WAND_MANA:
            ob->add_mana(random(chargeValue) + chargeValue / 2);
            if(chargeValue>=0)
	            ob->catch_msg("Your mental powers increased.\n");
            else
	            ob->catch_msg("You feel drained of mental powers.\n");
            return 1;
*/
        case WAND_STAT:
            make_tmp_stat(ob,wandStat, wandChange, wandTime);
            return 1;
        case WAND_SPECIAL:
            return special_effect(ob);

    }
}

/*
 * Function : create_wand
 * Descript : create the wand
 *            mask this with your own function
 */
public void create_wand()
{
}

/*
 * Function : create_object
 * Descript : well, if you don't know that...
 */
public nomask void create_object()
{
    ::set_long("@@mylong");
    ::set_short("@@myshort");

    add_prop(OBJ_I_WEIGHT,WEIGHT);
    add_prop(OBJ_I_VOLUME,VOLUME);

    set_zap_verb(VERB);

    set_fail_msg(FAILMSG);

    set_wand_type(WAND_EMPTY);

    // VERY IMPORTANT! DO NOT REDEFINE OBJ_I_VALUE!!!
    add_prop(OBJ_I_VALUE,"@@calc_wand_value");

    create_wand();
}

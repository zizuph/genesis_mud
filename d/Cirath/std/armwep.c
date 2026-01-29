/*
 *  Coded by: Yrgol 
 *  date: 2/2 - 02
 *  file: /w/yrgol/test/armwep.c
 *  Comment: Well Milashk wanted to have a weapon that could be
 *  both a weapon and a shield. So I went and made this.
 *  copied most of it from the original inherits from weapons and armours
 *  but many modifications made, and functions removed.
 *
 *  Most of the problems came when I noticed that if you wielded the
 *  weapon you couldn't wear in. But if you wore it first it would say
 *  "you wear the WEAPON" but not at a place. So you had to remove and
 *  wear it again. therefor there are many different calls doing the same
 *  shit.
 *
 *
 *  This code has many flaws, or most of them removed. But it still has
 *  functions that aren't needed, but if I need to remake it I find it
 *  to be easier to keep them. They won't affect much.
 *
 *  This is mostly a combination of the weapons and arms files, but I had
 *  to look deep into the object and wearable_item files aswell. To find the
 *  root commands, and well master them.
 *
 *  Suggestions? You want to make a spiked harnesk for you new guild that
 *  should be a weapon aswell as an armour? well then, I bet we could colaborate.
 *  just mail (the god himself,) Yrgol. =)
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include <cmdparse.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>

void update_prop_settings();
varargs void remove_broken(int silent = 0);

static int      wep_hit,        /* Weapon to hit */
                wep_pen,        /* Weapon penetration */
                wep_wt,         /* Weapon type */
                wep_dt,         /* Damage type */
                wep_hands,      /* How many hands the weapon takes */
                wielded,        /* Wielded or not */
                wielded_in_hand,/* Wielded in which hand */
                *m_pen,         /* Modifiers for the wep_pen */
                hits,           /* No of hits the weapon have made */
                dull,           /* How dull the weapon has become */
                corroded,       /* Corrotion on the weapon */
                repair_dull,    /* How much dullness we have repaired */
                repair_corr,    /* How much corrosion we have repaired */
                likely_corr,    /* How likely will this weapon corrode */
                likely_break,   /* How likely will this weapon break? */
                likely_dull,    /* How likely will it be dulled by battle? */
                max_value,      /* Value of weapon at prime condition */
                arm_ac,         /* Armour class */
                *arm_mods,      /* Armour modifiers */
                arm_shield,     /* Bodypart(s) protected by shield */
                condition,      /* How correded/worn down the armour has been*/
                likely_cond,    /* Likely cond of armour will worsen */
                repair;         /* How much of this has been repaired */
string  wep_condition_desc();
static object   wielder,        /* Who is holding it */
                wield_func;     /* Object that defines extra wield/unwield */
static private int      will_not_recover;       /* True if it won't recover */

nomask mixed wield_me();
public mixed remove_me();
nomask mixed unwield_me();
public mixed s_remove_me();

public string
wear_how(int location)
{
    string how, pos;

    if (!wearer)
    {
        pos = "the";
    }
    else if (this_player() == wearer)
    {
        pos = "your";
    }
    else
    {
        pos = wearer->query_possessive();
    }

    switch (location)
    {
        case A_CHEST:
            how = " on " + pos + " chest"; break;
        case A_TORSO:
            how = " over " + pos + " shoulders"; break;
        case A_HEAD:
            how = " on " + pos + " head"; break;
        case A_LEGS:
            how = " on " + pos + " legs"; break;
        case W_RIGHT:
        case A_R_ARM:
            how = " on " + pos + " right arm"; break;
        case W_LEFT:
        case A_L_ARM:
            how = " on " + pos + " left arm"; break;
        case A_ANY_ARM:
            how = " on " + pos + " arm of choice"; break;
        case A_FEET:
            how = " on " + pos + " feet"; break;
        case A_ROBE:
            how = " around " + pos + " body"; break;
        case A_NECK:
            how = " around " + pos + " neck"; break;
        case A_WAIST:
            how = " around " + pos + " waist"; break;
        case A_R_FINGER:
            how = " on " + pos + " right ring finger"; break;
        case A_L_FINGER:
            how = " on " + pos + " left ring finger"; break;
        case A_ANY_FINGER:
            how = " on " + pos + " ring finger of choice"; break;
        case A_HANDS:
            how = " on both hands"; break;
        case A_R_HAND:
            how = " on " + pos + " right hand"; break;
        case A_L_HAND:
            how = " on " + pos + " left hand"; break;
        case A_ANY_HAND:
            how = " on " + pos + " hand of choice"; break;
        case A_R_FOOT:
            how = " on " + pos + " right foot"; break;
        case A_L_FOOT:
            how = " on " + pos + " left foot"; break;
        case A_ANY_FOOT:
            how = " on " + pos + " foot of choice"; break;
        case A_ARMS:
            how = " on both arms"; break;
        case A_BACK:
            how = " on " + pos + " back"; break;
        case A_WRISTS:
            how = " on " + pos + " wrists"; break;
        case A_L_WRIST:
            how = " on " + pos + " left wrist"; break;
        case A_R_WRIST:
            how = " on " + pos + " right wrist"; break;
        case A_ANY_WRIST:
            how = " on " + pos + " wrist of choice"; break;
        case A_ANKLES:
            how = " on " + pos + " ankles"; break;
        case A_L_ANKLE:
            how = " on " + pos + " left ankle"; break;
        case A_R_ANKLE:
            how = " on " + pos + " right ankle"; break;
        case A_ANY_ANKLE:
            how = " on " + pos + " ankle of choice"; break;
        case A_EARS:
            how = " on " + pos + " ears"; break;
        case A_L_EAR:
            how = " on " + pos + " left ear"; break;
        case A_R_EAR:
            how = " on " + pos + " right ear"; break;
        case A_HIPS:
            how = " on " + pos + " hips"; break;
        case A_L_HIP:
            how = " on " + pos + " left hip"; break;
        case A_R_HIP:
            how = " on " + pos + " right hip"; break;
        case A_ANY_HIP:
            how = " on " + pos + " hip of choice"; break;
        case A_SHOULDERS:
            how = " on " + pos + " shoulders"; break;
        case A_L_SHOULDER:
            how = " on " + pos + " left shoulder"; break;
        case A_R_SHOULDER:
            how = " on " + pos + " right shoulder"; break;
        case A_ANY_SHOULDER:
            how = " on " + pos + " shoulder of choice"; break;
        case A_BROW:
            how = " on " + pos + " brow"; break;
        case A_EYES:
            how = " over " + pos + " eyes"; break;
        default: 
            how = "";
    }

    return how;
}

public mixed
s_wear_me()
{
    string what, how, error_msg;
    mixed wfail;
    int *slots, i;

    what = this_object()->short();
    if (worn)
    {
        return "You already wear the " + what + ".\n";
    }

    if (this_object()->query_prop(OBJ_I_BROKEN))
    {
        return "You can't wear broken items.\n";
    }

    worn_on_part = ABS(arm_at);
    slots = query_slots(0);
    wearer = this_player();

    error_msg = "";

    while (i < sizeof(slots))
    {
        if (stringp(wfail = check_slot(slots[i])))
	{
            if (arm_at >= 0)
	    {
                return wfail;
	    }

            error_msg += wfail;
	}
        else
	{
            if (arm_at < 0)
	    {
                worn_on_part = slots[i];
                break;
	    }
	}
        
        if ((++i == sizeof(slots)) && strlen(error_msg))
	{
            return error_msg;
	}
    }

    if (stringp(wfail = do_wear_item()))
    {
        return wfail;
    }

    /*
     * A wear function in another object.
     */
    if (!wear_func || !(wfail = wear_func->wear(this_object())))
    {
        how = wear_how(worn_on_part);
//        write("You wear the " + what + how + ".\n");
//        say(QCTNAME(this_player()) + " wears the " + what + ".\n");
    }

    /*
     * If the wearfunc returned a value < 0 then we can not wear the armour
     */
    if (intp(wfail) && wfail >= 0)
    {
        this_object()->set_adj("worn");
        worn = 1;
        return 1;
    } 

    do_remove_item();

    this_object()->remove_adj("worn");
    wearer = 0;
    worn = 0;

    if (stringp(wfail))
    {
        return wfail;
    }

    return "You cannot wear the " + 
        this_object()->short(this_player()) + ".\n";
}

public mixed
wear_me()
{
    string what, how, error_msg;
    mixed wfail;
    int *slots, i;

    what = this_object()->short();
    if (worn)
    {
        return "You already wear the " + what + ".\n";
    }

    if (this_object()->query_prop(OBJ_I_BROKEN))
    {
        return "You can't wear broken items.\n";
    }

    worn_on_part = ABS(arm_at);
    slots = query_slots(0);
    wearer = this_player();

    error_msg = "";

    while (i < sizeof(slots))
    {
        if (stringp(wfail = check_slot(slots[i])))
	{
            if (arm_at >= 0)
	    {
                return wfail;
	    }

            error_msg += wfail;
	}
        else
	{
            if (arm_at < 0)
	    {
                worn_on_part = slots[i];
                break;
	    }
	}
        
        if ((++i == sizeof(slots)) && strlen(error_msg))
	{
            return error_msg;
	}
    }

    if (stringp(wfail = do_wear_item()))
    {
        return wfail;
    }

    /*
     * A wear function in another object.
     */
    if (!wear_func || !(wfail = wear_func->wear(this_object())))
    {
        how = wear_how(worn_on_part);
        write("You wear the " + what + how + ".\n");
        say(QCTNAME(this_player()) + " wears the " + what + ".\n"); 
    }

    /*
     * If the wearfunc returned a value < 0 then we can not wear the armour
     */
    if (intp(wfail) && wfail >= 0)
    {
        this_object()->set_adj("worn");
        worn = 1;
        return 1;
    } 

    do_remove_item();

    this_object()->remove_adj("worn");
    wearer = 0;
    worn = 0;

    if (stringp(wfail))
    {
        return wfail;
    }

    return "You cannot wear the " + 
        this_object()->short(this_player()) + ".\n";
}

public mixed
command_wear()
{
    return "Perhaps wield this weapon?\n";
}

public mixed
s_remove_me()
{
    mixed wret;

    if (!worn || !wearer)
    {
        return 0;
    }

    /*
     * A remove function in another object.
     */
    if (!wear_func || !(wret = wear_func->remove(this_object())))
    {
        if (CAN_SEE(this_player(), this_object()))
        {
//            write("You remove the " + this_object()->short() + ".\n");
        }
        else
        {
//           write("You remove something.\n");
        }
     
//        say(QCTNAME(this_player()) + " removes " +
//            this_player()->query_possessive() + " " +
//            QSHORT(this_object()) + ".\n");
    }

    if (intp(wret) && (wret >= 0))
    {
        do_remove_item();
        this_object()->remove_adj("worn");
        wearer = 0;
        worn = 0;

        return 1;
    }

    return (stringp(wret) ? wret : "");
}

public mixed
remove_me()
{
    mixed wret;

    if (!worn || !wearer)
    {
        return 0;
    }

    /*
     * A remove function in another object.
     */
    if (!wear_func || !(wret = wear_func->remove(this_object())))
    {
        if (CAN_SEE(this_player(), this_object()))
        {
            write("You remove the " + this_object()->short() + ".\n");
        }
        else
        {
           write("You remove something.\n");
        }
     
        say(QCTNAME(this_player()) + " removes " +
            this_player()->query_possessive() + " " +
            QSHORT(this_object()) + ".\n");
    }

    if (intp(wret) && (wret >= 0))
    {
        do_remove_item();
        this_object()->remove_adj("worn");
        wearer = 0;
        worn = 0;

        return 1;
    }

    return (stringp(wret) ? wret : "");
}

public mixed
command_remove()
{
    return "Perhaps unwield this?\n";
}


static mixed
do_wear_item()
{
    return wearer->wear_arm(this_object());
}

static void
do_remove_item()
{
    wearer->remove_arm(this_object());
}

static mixed
check_slot(int slot)
{
    object tool;

    if (tool = this_player()->query_tool(slot))
    {
        return "The " + tool->short() + " is in the way.\n";
    }

    return ::check_slot(slot);
}

void
set_ac(int class)
{
    if (query_lock())
    {
        return;
    }

    arm_ac = class;
}


varargs int
query_ac(int hid)
{
    return arm_ac - condition + repair;
}

void
set_at(int type)
{
    set_slots(type);
}

int
query_at()
{
    return query_slots_setting();
}

void
set_am(int *list)
{
    if (query_lock())
        return;                 /* All changes have been locked out */

    if (F_LEGAL_AM(list))
        arm_mods = list;
}

int *
query_am(int hid)
{
    return arm_mods + ({});
}

void
set_af(object obj)
{
    set_wf(obj);
}

object
query_af()
{
    return query_wf();
}

nomask int
check_armour()
{
    return 1;
}

public varargs void
set_default_armour(int ac, int at, int *am, object af)
{
    if (ac) set_ac(ac); 
    else set_ac(1);

    if (at) set_at(at);
    else set_at(A_BODY);
    
    if (am) set_am(am);
    else set_am(A_NAKED_MOD);

    if (af) set_af(af);
}

public void
set_shield_slot(mixed hids)
{
    arm_shield = hids;
}

public nomask int *
query_protects();

public int *
query_shield_slots()
{
    int *ss;

    ss = check_call(arm_shield);
    if (ss) return ss;
    if (worn_on_part & W_LEFT) return ({ A_L_ARM });
    if (worn_on_part & W_RIGHT) return ({ A_R_ARM });
    if (query_prop(OBJ_I_IS_MAGIC_ARMOUR)) return query_protects();
    return ({ });
}

public nomask int *
query_protects()
{
    int abit, *hids, *chid;
    /*
       Table of armour slots <-> Hitlocations

             TORSO HEAD LEGS R_ARM L_ARM ROBE SHIELD

    TORSO      X      
    HEAD            X
    LEGS                 X
    R_ARM                      X
    L_ARM                            X
    ROBE       X         X                
    SHIELD                     X     X                          
    MAGIC      X    X    X     X     X 

        Max ac is 100 for all hitlocations. If the sum of the ac for a
        given hitlocation is > 100 then it is set to 100.
    */
    for (hids = ({}), abit = 1; abit <= worn_on_part; abit *= 2)
    {
        if (worn_on_part & abit)
        {
            switch (abit)
            {
                case A_CHEST:
                    chid = ({ A_TORSO });    
                    break;
                case A_HEAD:    
                case A_LEGS:
                case A_R_ARM:
                case A_L_ARM:
                    chid = ({ abit });
                    break;
                case A_ROBE:  
                    chid = ({ A_TORSO, A_LEGS });
                    break;
                case W_LEFT:
                case W_RIGHT:
                    chid = query_shield_slots();
                    break;
                default:
                    chid = ({});
            }

            hids = (hids - chid) + chid;
        }
    }

    return hids;
}
 
public void
create_weapon()
{
}

public nomask void
create_object()
{
    set_slots(F_ARMOUR_DEFAULT_AT);
    wep_wt = F_WEAPON_DEFAULT_WT;
    wep_dt = F_WEAPON_DEFAULT_DT;
    arm_mods = allocate(W_NO_DT);
    likely_dull = 10;
    likely_corr = 10;
    likely_break = 10;
    set_layers(6);
    set_looseness(2);
    wep_hands = F_WEAPON_DEFAULT_HANDS;
    set_name("weapon");
    worn = 0;
    wielded = 0;
    add_prop(OBJ_I_VALUE, "@@query_value");
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 200);
    m_pen = ({ 0, 0, 0 });

    will_not_recover = (random(100) < PERCENTAGE_OF_RECOVERY_LOST);

    create_weapon();

    update_prop_settings();
}
public void
reset_weapon()
{
}

public nomask void
reset_object()
{
    reset_weapon();
}

public varargs string
short(object for_obj)
{
    if (query_prop(OBJ_I_BROKEN))
    {
        return "broken " + ::short(for_obj);
    }

    return ::short(for_obj);
}

public varargs string
plural_short(object for_obj)
{
    string str = ::plural_short(for_obj);

    /* We make this additional check for stringp(str) because if no plural
     * short has been set, we shoudln't alter it. The plural short will
     * be generated if no plural short has been set.
     */
    if (query_prop(OBJ_I_BROKEN) && stringp(str))
    {
        return "broken " + str;
    }

    return str;
}

public varargs string
long(object for_obj)
{
    return ::long(for_obj) + break_string(wep_condition_desc(), 75);
}

nomask mixed
wield_me()
{
    int wret, skill, pen;
    string penuse, wfail;
    if (wielded)
        return "You already wield the " + short() + ".\n";
    else if (this_player() != environment(this_object()))
        return "You must carry the " + short() + " to be able to wield it.\n";
    else if (query_prop(OBJ_I_BROKEN))
        return "The " + short() + " is broken and not wieldable.\n";

    wielder = this_player();

    /* 
     * Check for a hand to wield the weapon in.
     */
    wielded_in_hand = wep_hands;
    if (wep_hands != W_ANYH)
    {
        if (wielder->query_tool(W_BOTH) && wep_hands < W_FOOTR)
        {
            return "Your hands seem busy with other things.\n";
        }

        /* 
         * Anything in the specified hand
         */
        if (wielder->query_tool(wep_hands))
        {
            return "The " + wielder->query_tool(wep_hands)->short() +
                " is in the way.\n";
        }
    
        if ((wep_hands == W_BOTH) &&
            (wielder->query_tool(W_RIGHT) || wielder->query_tool(W_LEFT)))
        {
            return "You need both hands to wield it.\n";
        }
    }
    else if (!wielder->query_tool(W_BOTH) && 
             !wielder->query_tool(W_RIGHT))
    {
        wielded_in_hand = W_RIGHT;
    }
    else if (!wielder->query_tool(W_BOTH) && 
             !wielder->query_tool(W_LEFT))
    {
        wielded_in_hand = W_LEFT;
    }
    else
    {
        return "You have no hand left to wield that weapon.\n";
    }

    if (stringp(wfail = wielder->wield(this_object())))
    {
        return wfail;
    }

    wret = 0;
    if ((!wield_func) || (!(wret=wield_func->wield(this_object()))))
    {
//        if (wielded_in_hand == W_BOTH)
//            write("You wield the " + short() + " in both your hands.\n");
//        else if (wielded_in_hand < W_FOOTR)
//            write("You wield the " + short() + " in your " +
//                  (wielded_in_hand == W_RIGHT ? "right" : "left") + 
//                  " hand.\n");
//        else
//            write("You wield the " + short() + " on your " +
//                  (wielded_in_hand == W_FOOTR ? "right" : "left") + 
//                  " foot.\n");

//        say(QCTNAME(this_player()) + " wields " + 
//            this_player()->query_possessive() + " " +
//            QSHORT(this_object()) + ".\n");
    }
    if (intp(wret) && wret >= 0)
    {
        wielded = 1;
        set_adj("wielded");
        return 1;
    }

    if (stringp(wfail = wielder->unwield(this_object())))
    {
        /* This is serious and almost fatal, please panic! */
        wielded = 1;
        set_adj("wielded");
        return 1;
    }
    if (stringp(wret))
        return wret;
    else 
        return "You cant wield the " + short() + "\n";
}

mixed
command_wield()
{
    mixed wield_msg;
    s_wear_me();
    wield_msg=wield_me();
    s_remove_me();
    if(wield_msg == 1)   // Have to check if the item already is wielded or not
       wear_me();        // would have been easier if it would wear as it should in
    else  		 // the first place.. but well well..
       s_wear_me();

    return wield_msg;//1;//wield_me();
}


nomask mixed
unwield_me()
{
    mixed wret;
    if (!wielded || !wielder)
    {
        return 0;
    }

    wret = 0;
    if ((!wield_func) || (!(wret = wield_func->unwield(this_object()))))
    {
//        if (check_seen(this_player()))
//            write("You stop wielding the " + short() + ".\n");
//        else
//            write("You stop wielding something.\n");
//        say(QCTNAME(this_player()) + " stops wielding " +
//            this_player()->query_possessive() + " " +
//            QSHORT(this_object()) + ".\n");
    }
    if (intp(wret) && (wret >= 0))
    {
        wielder->unwield(this_object());
        wielded = 0;
        remove_adj("wielded");
        wielded_in_hand = wep_hands;
        return 1;
    }
    return (stringp(wret) ? wret : "");
}

mixed
command_unwield()
{
    remove_me();
    return unwield_me();
}

void
leave_env(object from, object dest)                            // Milashk, this is where
{							       // destruct and drop things are handled.
    ::leave_env(from, dest);

    if (!wielded)
        return;

    if ((!wield_func ||
         !wield_func->unwield(this_object())) &&
        wielder)
    {
//        tell_object(wielder, "You stop wearing the " + short() + ".\n");
    }

    
//    wielder->unwield(this_object());
//    remove_adj("wielded");
//    wielded = 0;
    remove_me();
    unwield_me();								
}

void
set_hit(int class)
{
    if (query_lock())
    {
        return;
    }

    wep_hit = class;
}
int query_hit() { return wep_hit; }
void
set_pen(int class)
{
    if (query_lock())
        return;                 /* All changes has been locked out */

    wep_pen = class;
}
int query_pen() { return wep_pen; }
void
set_pm(int *list)
{
    if (query_lock())
        return;

    if (F_LEGAL_AM(list))
        m_pen = list;
}
int *query_pm() { return m_pen + ({}); }
int *
query_modified_pen()
{
    int *m_pent, i, du, co, pen;

    du = dull - repair_dull;
    co = corroded - repair_corr;
    pen = this_object()->query_pen();

    m_pent = allocate(W_NO_DT);

    for (i = 0; i < W_NO_DT; i++)
    {
        if (!pointerp(m_pen))
            m_pent[i] = pen;
        else if (i >= sizeof(m_pen))
            m_pent[i] = pen + (i ? m_pen[0] : 0);
        else
            m_pent[i] = pen + m_pen[i];
    }

    return ({ m_pent[0] - 2 * (du + co) / 3, m_pent[1] - du - co,
                m_pent[2] - (du + co) / 3 });
}
void
set_wt(int type)
{
    int *likely;

    if (query_lock())
        return;                 /* All changes has been locked out */

    if (type >= 0 && type < W_NO_T)
    {
        wep_wt = type;
        likely = W_DRAWBACKS[type];
        likely_dull = likely[0];
        likely_corr = likely[1];
        likely_break = likely[2];
    }
}
int query_wt() { return wep_wt; }
void
set_dt(int type)
{
    if (query_lock())
        return;                 /* All changes has been locked out */

    if (F_LEGAL_DT(type))
        wep_dt = type;
}
int query_dt() { return wep_dt; }
void
set_hands(int which)
{
    if (query_lock())
        return;                 /* All changes has been locked out */

    if (F_LEGAL_HANDS(which))
        wep_hands = which;
}
int query_hands() { return wep_hands; }
int query_attack_id() { return wielded_in_hand; }
int *
query_slots()
{
    int abit, *hids;

    for (hids = ({}), abit = 2; abit <= wielded_in_hand; abit *= 2)
    {
        if (wielded_in_hand & abit)
        {
            hids = hids + ({ abit });
        }
    }
    return hids;
}
/*int *
query_protects()
{
    switch (wielded_in_hand)
    {
        case W_LEFT:
            return ({ A_L_ARM });
        case W_RIGHT:
            return ({ A_R_ARM });
        case W_BOTH:
            return ({ A_L_ARM, A_R_ARM });
        case W_FOOTR:
            return ({ A_R_FOOT });
        case W_FOOTL:
            return ({ A_L_FOOT });
        default:
            return ({ });
    }
}*/

void
set_wf(object obj)
{
    if (query_lock())
        return;                 /* All changes has been locked out */

    wield_func = obj;
}
#if 0
public mixed
wield(object obj)
{
    return 0;
}
public mixed
unwield(object obj)
{
    return 0;
}
#endif
int
set_corroded(int corr)
{
    if (corr > corroded)
    {
        corroded = corr;
        if (F_WEAPON_BREAK(dull - repair_dull, corroded - repair_corr,
                        likely_break))
            set_alarm(0.1, 0.0, &remove_broken(0));
        if (wielded && wielder)
            wielder->update_weapon(this_object());
        return 1;
    }
    return 0;
}
int query_corroded()
{
    return corroded;
}
void set_likely_corr(int i) { likely_corr = i; }
int query_likely_corr() { return likely_corr; }
int
set_dull(int du)
{
    if (du > dull)
    {
        dull = du;
        if (F_WEAPON_BREAK(dull - repair_dull, corroded - repair_corr,
                        likely_break))
            set_alarm(0.1, 0.0, &remove_broken(0));
        if (wielded && wielder)
            wielder->update_weapon(this_object());
        return 1;
    }
    return 0;
}
int query_dull() { return dull; }
void set_likely_dull(int i) { likely_dull = i; }
int query_likely_dull() { return likely_dull; }
void set_likely_break(int i) { likely_break = i; }
int query_likely_break() { return likely_break; }
varargs void
remove_broken(int silent = 0)
{
    if (!wielded || !wielder)
    {
        add_prop(OBJ_I_BROKEN, 1);
        return;
    }

    if (objectp(wield_func))
    {
        wield_func->unwield(this_object());
    }
    if (!silent)
    {
        tell_object(wielder, "The " + short(wielder) + " breaks!!!\n");
        tell_room(environment(wielder), "The " + QSHORT(this_object()) +
            " wielded by " + QTNAME(wielder) + " breaks!!!\n", wielder);
    }

    wielder->unwield(this_object());
    remove_adj("wielded");
    add_prop(OBJ_I_BROKEN, 1);
    wielded = 0;
}
int
set_repair_dull(int rep)
{
    if (rep > repair_dull && F_LEGAL_WEAPON_REPAIR_DULL(rep, dull))
    {
        repair_dull = rep;
        if (wielded && wielder)
            wielder->update_weapon(this_object());
        return 1;
    }
    return 0;
}
int query_repair_dull() { return repair_dull; }
int
set_repair_corr(int rep)
{
    if (rep > repair_corr && F_LEGAL_WEAPON_REPAIR_CORR(rep, corroded))
    {
        repair_corr = rep;
        if (wielded && wielder)
            wielder->update_weapon(this_object());
        return 1;
    }
    return 0;
}
int query_repair_corr() { return repair_corr; }
public void
set_weapon_hits(int new_hits) { hits = new_hits; }
public int
query_weapon_hits() { return hits; }
int
add_prop_obj_i_value(mixed val)
{
    if (!max_value)
    {
        max_value = 10;
        return 0;
    }

    if (intp(val) && val)
        max_value = val;

    return 1;
}
int
query_value()
{
    if (query_prop(OBJ_I_BROKEN))
        return 0;

    return max_value *
        F_WEAPON_VALUE_REDUCE(dull - repair_dull, corroded - repair_corr) /
100;
}
object query_wf() { return wield_func; }
int try_hit(object target) { return 1; }
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{
    hits++;

    if (F_WEAPON_CONDITION_DULL(hits, wep_pen, likely_dull))
    {
        hits = 0;
        set_dull(query_dull() + 1);
    }

    return 0;
}
nomask int
check_weapon()
{
    return 1;
}
varargs void
set_default_weapon(int hit, int pen, int wt, int dt, int hands, object obj)
{
    /* Sets the weapon "to hit" value.
    */
    if (hit) set_hit(hit);
    else set_hit(5);

    /* Sets the weapon penetration value.
    */
    if (pen) set_pen(pen);
    else set_pen(10);
   /* Set the weapon type.
    */
    if (hit) set_wt(wt);
    else set_wt(W_FIRST);

    /* Set the damage type.
    */
    if (hit) set_dt(dt);
    else set_dt(W_IMPALE | W_SLASH);

    /* Set the hand(s) used to wield the weapon.
    */
    if (hands) set_hands(hands);
    else set_hands(W_NONE);
    
    /* Sets the name of the object that contains the function
       to call for extra defined wield() and unwield()
       functions.
    */
    if (obj) set_wf(obj);
}
public nomask string 
query_wield_desc(string p)
{
    string str;

    if (check_seen(this_player()))
        str = LANG_ADDART(short(this_player()));
    else
        str = "something";

    switch(wielded_in_hand)
    {
    case W_RIGHT:return str + " in " + p + " right hand";
    case W_LEFT: return str + " in " + p + " left hand";
    case W_BOTH: return str + " in both hands";
    case W_FOOTR:return str + " on " + p + " right foot";
    case W_FOOTL:return str + " on " + p + " left foot";
    }
    return str;
}
nomask void
update_prop_settings()
{
    if (query_prop(OBJ_I_VALUE) < F_VALUE_WEAPON(wep_hit, wep_pen) &&
            !query_prop(OBJ_I_IS_MAGIC_WEAPON))
        add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(wep_hit, wep_pen));
 
    if (F_WEIGHT_FAULT_WEAPON(query_prop(OBJ_I_WEIGHT), wep_pen, wep_wt) &&
            !query_prop(OBJ_I_IS_MAGIC_WEAPON))
        add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(wep_pen, wep_wt));
}

object
query_wielded()
{
    if (wielded) return wielder;
}

/*public nomask int *
query_am() { return ({ -3, 2, 1}); }*/

/*public nomask int
query_ac()
{
    if (wielder)
        return wielder->query_skill(SS_PARRY) * wep_hit / 500 +
                wep_hit / 2;
    else
        return wep_hit / 2;
}*/

string
stat_object()
{
    string str;

    str = ::stat_object();

    str += "Hit: " + wep_hit + "\t\tPen: " + wep_pen + "\t\tAC:" + arm_ac + "\n";  // Added so it shows the AC

    str += "Type: " + wep_wt + "\n";
    str += "Hands: " + wep_hands + "\n";
    return str;
}

string
wep_condition_desc()
{
    string hand, hand2;

    if (query_prop(OBJ_I_BROKEN))

        return "It is broken.\n";

    switch (corroded - repair_corr)
    {
        case 0:
            hand = ""; break;
        case 1:
            hand = "You find some rust marks on it!\n"; break;
        case 2:
            hand = "You can spot some rust on it!\n"; break;
        case 3:
            hand = "The weapon is full of rust!\n"; break;
        case 4:
        case 5:
            hand = "It looks like it have been bathing in acid!!\n"; break;
        default:
            hand = "It looks like it is falling apart from corrosion.\n";
break;

    }

    switch (dull - repair_dull)
    {
        case 0:
            hand2 = "in prime condition"; break;
        case 1:
            hand2 = "in a fine condition"; break;
        case 2:
            hand2 = "a little touched by battle"; break;
        case 3:
            hand2 = "scarred by battle"; break;
        case 4:
        case 5:
            hand2 = "very scarred by battle"; break;
        case 6:
        case 7:
        case 8:
            hand2 = "in big need of a smith"; break;
        default:
            hand2 = "going to break any second"; break;
    }

    return hand + "It looks like it is " + hand2 + ".\n";
}

string
weapon_type()
{
    if (wep_wt >= W_NO_T)
    {
        return "weapon";
    }

    return W_NAMES[wep_wt];
}
string
wep_usage_desc()
{
    string hand;

    switch (wep_hands)
    {
        case W_RIGHT:
            hand = "in the right hand"; break;
        case W_LEFT:
            hand = "in the left hand"; break;
        case W_BOTH:
            hand = "in both hands"; break;
        case W_FOOTR:
            hand = "on the right foot"; break;
        case W_FOOTL:
            hand = "on the left foot"; break;
        case W_ANYH:
            hand = "in any hand"; break;
        default:
            hand = "by some strange creature"; break;
    }

    return ("The " + weapon_type() + " is made to be wielded " + hand + ".\n");
}

void
appraise_object(int num)
{
    ::appraise_object(num);

    write(wep_usage_desc());
}


nomask int
may_not_recover()
{
    return will_not_recover;
}

nomask void
may_recover()
{
    will_not_recover = 0;
}

nomask void
set_may_not_recover()
{
    will_not_recover = 1;
}

string
query_wep_recover()
{
    return ("#WEP#" + hits + "#" + dull + "#" + corroded + "#" +
        repair_dull + "#" + repair_corr + "#" + query_prop(OBJ_I_BROKEN) +
        "#");
}
void
init_wep_recover(string arg)
{
    string foobar;
    int    broken;

    sscanf(arg, "%s#WEP#%d#%d#%d#%d#%d#%d#%s", foobar,
        hits, dull, corroded, repair_dull, repair_corr, broken, foobar);

    if (broken != 0)
    {
        add_prop(OBJ_I_BROKEN, broken);
    }
}
public string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}
public void
init_recover(string arg)
{
    init_wep_recover(arg);
}


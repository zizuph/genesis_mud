/*
 * /d/Gondor/common/obj/oilflask.c
 *
 * This is a flask of oil that can be used to re-fill the oil-lamp that goes
 * with it.
 *
 * Original idea and coding by Lord Elessar Telcontar
 * Recoded for use with /std/torch.c by
 *
 * /Mercade, 30 October 1993
 *
 * Revision history:
 * -  4 Sep 1996, Olorin: Modified to use /lib/keep.
 *                        Modified to use functions for VBFC.
 * - 31 Oct 2005, Finwe:  Modified so when empty, flask decays. 
 *                        Based on /std/torch which falls apart when empty.
 * - 24 May 2006, Palmer: add_name("_flask_of_oil_") for standardization
 *
 */
#pragma strict_types

inherit "/std/object.c";
inherit "/lib/keep.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#define DECAY_TIME (300.0)

static  int Decay_Alarm;        /* Alarm used when the flask decays */

/*
 * prototype
 */
static  int Decay_Alarm;        /* Alarm used when the flask decays */
int compute_value();
int compute_weight();
string short_description();
string pshort_description();
string long_description();
int compute_volume();
void set_amount(int i);

/*
 * Global variables
 */
int max_amount; /* the maximum contents of the flask */
int oil_amount; /* the current contents of the flask */

void
create_object()
{
    set_name("oil");
    add_adj(({"flask","of"}));
    add_adj("oil");
    add_name("flask");
    add_name("oil-flask");
    add_name("lamp-oil");
    add_name("_gondorian_flask_with_oil_");
    add_name("_flask_of_oil_");

    set_pname("flasks");
    add_pname("oil-flasks");

    add_adj("lamp");

    set_short(short_description);
    set_pshort(pshort_description);
    set_long(long_description);

    set_amount(4000);

    add_prop(OBJ_I_VALUE,  compute_value);
    add_prop(OBJ_I_WEIGHT, compute_weight);
    add_prop(OBJ_I_VOLUME, compute_volume);
}

/*
 * Function name: decay_item
 * Description  : This function is called with a delay to destruct the
 *                empty flask. 
 */
void
decay_item()
{
    object env = environment();
    string tmp = short();

    if (living(env))
    {
	tell_object(env, "The remains of the " + tmp + " fall apart.\n");
	tell_room(environment(env), "The remains of the " + tmp + " that " +
	    QTNAME(env) + " is holding fall apart.\n", env);
    }
    else if (env->query_prop(ROOM_I_IS))
    {
	tell_room(env, "The remains of the " + tmp + " fall apart.\n");
    }

    remove_object();
}

string
short_description()
{
    if (!oil_amount)
    {
        return "empty oil-flask";
    }

    return "flask of oil";
}

string
pshort_description()
{
    if (!oil_amount)
    {
        return "empty oil-flasks";
    }

    return "flasks of oil";
}

string
long_description()
{
    string long_desc = "It is an oil-flask, made of leather. It was " +
        "designed to contain lamp-oil for an oil-lamp. ";

    if (!oil_amount)
    {
        long_desc += "The flask is empty. ";
    }
    else
    {
        long_desc += "The flask contains some oil. ";
    }

    if (query_keep())
    {
        long_desc += "Presently, you do not want to sell the flask.";
    }
    else
    {
        long_desc += "If you do not want to sell the flask, just decide to " +
            "<keep flask>.";
    }

    return BSN(long_desc);
}

void
set_amount(int i)
{
    if (i <= 0)
    {
        add_adj("empty");
    }
    else
    {
        remove_adj("empty");
    }

    oil_amount = i;
    max_amount = i;
}

int
query_amount()
{
    return oil_amount;
}

void
remove_oil(int i)
{
    oil_amount -= i;

    if (oil_amount <= 0)
    {
        oil_amount = 0;
        add_adj("empty");
        Decay_Alarm = set_alarm(DECAY_TIME, 0.0, decay_item);
    }
}

int
compute_weight()
{
    /* 300 for the flask and 2 gram per 6 ml oil */
    return (300 + (2 * oil_amount / 6));
}

int
compute_volume()
{
    /* the flask is not rigid */
    /* 100 for the flask and the amount of oil */
    return (100 + oil_amount);
}

int
compute_value()
{
    /* 40 for the flask and 1 cc per 30 ml oil */
    return (40 + (oil_amount / 30));
}

void
appraise_object(int num)
{
    int perc = ((oil_amount * 100) / max_amount);
    int skill;
    int seed;
    string extra_desc = "is empty.";

    ::appraise_object(num);

    if (!num)
    {
	skill = (int)TP->query_skill(SS_APPR_OBJ);
    }
    else
    {
	skill = num;
    }

    sscanf(OB_NUM(this_object()), "%d", seed);
    skill = random((1000 / (skill + 1)), seed);
    perc = cut_sig_fig(perc + (skill % 2 ? -skill % 70 : skill) * perc / 100);

    switch (perc)
    {
        case  0:
            break;
        case  1..20:
            extra_desc = "hardly contains any lamp-oil.";
            break;
        case 21..40:
            extra_desc = "filled with lamp-oil for about one-third.";
            break;
        case 41..60:
            extra_desc = "is about half-full of lamp-oil.";
            break;
        case 61..80:
            extra_desc = "filled with lamp-oil for about two-thirds.";
            break;
        case 81..99:
            extra_desc = "is almost completely filled with lamp-oil.";
            break;
        default:
            extra_desc = "is completely filled with lamp-oil.";
            break;
    }
    write (BSN("You appraise that it " + extra_desc));
}

/*
 * Recovery stuff
 */
string
query_recover()
{
    return MASTER + ":" +
        "#o_a#" + oil_amount +
        "#m_a#" + max_amount +
        query_keep_recover();
}

void
init_recover(string arg)
{
    string foobar, tmp;

    sscanf(arg, "%s#o_a#%d#%s", foobar, oil_amount, foobar);
    sscanf(arg, "%s#m_a#%d#%s", foobar, max_amount, foobar);

    init_keep_recover(arg);
}

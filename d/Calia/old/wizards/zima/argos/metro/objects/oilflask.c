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
 * 11/18/95 Copied/Recoded to work with Argosian and Gondoran Lamps
 *          Sold EMPTY in the Argos glass works
 *          (zima/argos/metro/rooms/glasswrk.c)
 *          May be filled with oil in the press (with argosian olives)
 *          press=(zima/argos/metro/rooms/press.c)
 *          olive grove = (zima/argos/swterr/rooms/ogroveX.c)
 *          olives = (zima/argos/swterr/objects/olives.c)
 *
 */
 
inherit "/std/object";
 
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"
 
/*
 * prototype
 */
void set_amount(int i);
 
/*
 * Global variables
 */
int max_amount=4000; /* the maximum contents of the flask */
int oil_amount; /* the current contents of the flask */
 
void
create_object()
{
    set_name("oil");
    add_adj(({"glass","flask","of"}));
    add_adj("oil");
    add_name("flask");
    add_name("oil-flask");
    add_name("lamp-oil");
    add_name("_gondorian_flask_with_oil_");
    add_name("_argosian_flask_");
 
    set_pname("flasks");
    add_pname("oil-flasks");
 
    add_adj("lamp");
 
    set_short("@@short_description");
    set_pshort("@@pshort_description");
    set_long("@@long_description");
 
    set_amount(4000);
 
    add_prop(OBJ_I_VALUE,  "@@compute_value");
    add_prop(OBJ_I_WEIGHT, "@@compute_weight");
    add_prop(OBJ_I_VOLUME, "@@compute_volume");
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
    string long_desc = "It is an oil-flask, made of glass. It was " +
        "designed to contain lamp-oil for an oil-lamp. ";
 
    if (!oil_amount)
    {
        long_desc += "The flask is empty. ";
    }
    else
    {
        long_desc += "The flask contains some oil. ";
    }
 
    if (query_prop(OBJ_M_NO_SELL))
    {
        long_desc += "The flask is not sellable.";
    }
    else
    {
        long_desc += "Do 'keep flask' if you do not want to sell it.";
    }
 
    return BSN(long_desc);
}
 
void
init()
{
    ::init();
 
    add_action("do_keep", "keep");
}
 
int
do_keep(string str)
{
    if (!strlen(str))
        NFN0("Keep what?");
        if((!(parse_command(str, TP, " [the] [glass] [flask] [of] [lamp] " +
        " 'oil' / 'lamp-oil' "))) &&
       (!(parse_command(str, TP, " [the] 'flask' "))))
    {
        NFN0(CAP(query_verb()) + " what?");
    }
 
    if (ENV(TO) != TP)
    {
        NFN0("You do not have the " + short() + " in your inventory.");
    }
 
    if(TO->query_prop(OBJ_M_NO_SELL))
    {
        remove_prop(OBJ_M_NO_SELL);
        write("You can sell the flask again now. \n");
    }
    else
    {
        add_prop(OBJ_M_NO_SELL,"The flask is not sellable!\n");
        write(BSN("The flask is now not sellable. Do 'keep flask' again "+
            "to be able to sell it."));
    }
 
    return 1;
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
}
 
int
query_max_amount()
{
   return max_amount;
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
    /* the glass flask IS rigid - differs from Gondoran */
    return (150 + max_amount);
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
 
    if (perc >= 100)
        extra_desc = "is completely filled with lamp-oil.";
    else if (perc > 80)
        extra_desc = "is almost completely filled with lamp-oil.";
    else if (perc > 60)
        extra_desc = "filled with lamp-oil for about two-thirds.";
    else if (perc > 40)
        extra_desc = "is about half-full of lamp-oil.";
    else if (perc > 20)
        extra_desc = "filled with lamp-oil for about one-third.";
    else if (perc > 0)
        extra_desc = "hardly contains any lamp-oil.";
 
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
        "#o_k#" + ((query_prop(OBJ_M_NO_SELL)) ? "1" : "0") + "#";
}
 
void
init_recover(string arg)
{
    string foobar, tmp;
 
    sscanf(arg, "%s#o_a#%d#%s", foobar, oil_amount, foobar);
    sscanf(arg, "%s#m_a#%d#%s", foobar, max_amount, foobar);
    sscanf(arg, "%s#o_k#%d#%s", foobar, tmp, foobar);
    if(tmp)
    {
        add_prop(OBJ_M_NO_SELL,"The flask can't be sold!\n");
    }
}

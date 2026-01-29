/*
 * /d/Gondor/rohan/farm/farm/camp/arm/d_platemail_magic.c
 *   Originally a brooch coded by
 * Varian - 2016
 *
 * - Modified with help from Arman to save random factors
 *   Varian - April 2020
 *
 * - Shamelessly stolen for Dunlendings
 *
 *      The idea here is that the platemail is resistant to one
 *      type of magic, and that that resistance changes each
 *      time it's cloned. However, the resistance should recover
 *      when the player logs in with the platemail. The colors
 *      correspond to resistances.
 *   Raymundo, spring 2020
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <files.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include <ss_types.h>

#define ARM ({"platemail"})
#define ADJ2 ({"blackened"})
/* Below are the possible magic resistances. This armour will be
 * resistant to ONE of the types of magic.
 */
#define RES ({"MAGIC_I_RES_ACID", "MAGIC_I_RES_AIR","MAGIC_I_RES_EARTH", "MAGIC_I_RES_ELECTRICTY", "MAGIC_I_RES_ILLUSION", "MAGIC_I_RES_WATER"})
string adj, adj2, arm, res;
string wizinfo();
string magic_info();

/*
 * Function name:   set_armour_data
 * Descrption:      A function which returns the magical resistance and
 *                  first adjective for the armour.
 * Arguments:       none
 * Returns:         The description and magic resistance of the armour.
 */
 
void
set_armour_data()
{
   if(!strlen(adj2))
    {
        adj2 = one_of_list(ADJ2);
        arm = one_of_list(ARM);
        res = one_of_list(RES);
    }
    //This way the color of the armour matches the resistance
    if(!strlen(adj)) 
    {
        switch(res)
        {
            case "MAGIC_I_RES_ACID":
                adj = "yellow";
                break;

            case "MAGIC_I_RES_AIR":
                adj= "swirling";
                break;

            case "MAGIC_I_RES_EARTH":
                adj = "granite-grey";
                break;

            case "MAGIC_I_RES_ELECTRICTY":
                adj = "gold";
                break;

            case "MAGIC_I_RES_ILLUSION":
                adj = "opaque";
                break;

            case "MAGIC_I_RES_WATER":
                adj = "dark-blue";
                break;

            default:
                adj = "unspecified";
                break;
        }

    }

    set_name(arm);
    add_name("armour");
    add_name("mail");
    add_name("platemail");
    add_adj("plate");
    set_short(adj + " " + adj2 + " " + arm);
    set_adj(adj);
    add_adj(adj2);
    set_long("This " + arm + " is crafted in an ancient and rare style. "
        + "It consists of thick plates of " + adj2 + " metal "
        + "that are made to cover "
        + "both your chest and back. As you look closely, you see runes "
        + "engraved in the side.\n");
    add_item( ({"rune", "runes"}), "@@exa_runes@@");
    add_cmd_item( ({"rune", "runes"}), "read", "@@do_read@@");
    set_at(A_BODY);
    set_ac(50);

    add_prop(OBJ_I_VALUE, (1728*5));

    add_prop( OBJ_M_NO_BUY, 1 );
    add_prop( OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(query_ac(), A_BODY) 
        + random(200) );
    add_prop( OBJ_I_VOLUME, query_prop( OBJ_I_WEIGHT )/ 6 );
    add_prop( OBJ_S_WIZINFO, wizinfo );
    add_prop( OBJ_I_IS_MAGIC_ARMOUR, 1 );
    add_prop( MAGIC_AM_MAGIC, ({ 10, "enchantment" }) );
    add_prop( MAGIC_AM_ID_INFO, magic_info);

}

string
magic_info()
{
    return("You notice small runes on the "
        + arm + " which seem to indicate that "
        + "this armour protects you from magic. "
        + "Judging by the shape of the runes, you'd guess the "
        + query_short() + " was made by dwarves. This "
        + "is an ancient armour of extremely high quality.\n");
}

string
wizinfo()
{
    return("This " + arm + " is extremely good armour. Also, it adds "
        + "20 " + res + " to the wearer.\n");
}

string
exa_runes()
{
    string runes = "These runes look like they were etched by "
        + "dwarves.";
    if(TP->query_skill(SS_LANGUAGE) < 50)
    {
        return ("With your skills with languages, you can only understand a "
            + "little bit about the runes. " + runes + "\n");
    }
    runes += " You recognize that one of the runes reads 'protection'.";
    if(TP->query_skill(SS_LANGUAGE) < 70)
    {
        return ("Your skill with languages enables you to understand "
            + "some of what the runes mean. " + runes + "\n");
    }
    return (runes + " Also, you can make out the rune for 'magic'.\n");
}

int
do_read()
{
    write(exa_runes());
    return 1;
}

void
create_armour()
{
    set_armour_data();
    set_wf(TO);
}

mixed
wear(object ob)
{
    environment(ob)->add_prop(res, (environment(ob)->query_prop(res) + 20));
    write("As you wear the " + arm + " you feel more resistant.\n");
    say(QCTNAME(environment(ob)) + " looks resistant to whatever comes "
        + HIS_HER(environment(ob)) + " way as " + HE_SHE(environment(ob))
        + " wears the " + query_short() + ".\n");
    return 1;
}

mixed
remove(object ob)
{
    query_worn()->add_prop(res, query_worn()->query_prop(res) -20);
    write("As you remove the " + arm + " you feel less resistant.\n");
    say(QCTNAME(query_worn()) + " looks less prepared to handle the "
        + "stresses of life as " + HE_SHE(query_worn()) + " removes the "
        + query_short() + ".\n");
    return 1;
}


void
init_recover(string arg)
{
    string *a = explode(arg,"&&");

    if (sizeof(a) >= 5)
    {
        adj = a[1];
        adj2 = a[2];
        arm = a[3];
        res = a[4];
    }

    init_arm_recover(arg);
    set_armour_data();
}

string
query_recover()
{
    return ::query_recover() + "&&" + adj + "&&" + adj2 + "&&" + arm + "&&" + res;
}
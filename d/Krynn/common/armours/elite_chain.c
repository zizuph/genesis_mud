/* File name  : elite_chain.c
 * Description: Unique armour worn by the most elite draconians.
 *              It will increase one of the wearer's stats.
 *
 * Blizzard, 15.07.2003
 */

/* Navarre Feb 2007, changed to use F_WEIGHT and F_VALUE */
/* Navarre June 2008, Lowering resist value from 75 to 25. */
 
inherit "std/armour.c";
inherit "/lib/keep";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

#define           BONUS_STAT      10
#define           ARMOUR_INFO     query_info()

object            wearer;
private string    color = "uncolored";

public string     query_color();
public string     query_effect();
public string     query_info();

public string
long_description()
{
    return "This perfectly crafted chain mail is a standard armour of " +
        "the dragonarmy elite fighters. It is made of interlocking steel " +
        "rings and padded with a layer of fabric to prevent chafing and to " +
        "lessen the impact of blows. The vital places of the wearer's body " +
        "are also shielded by " + query_color() + " metal plates, what " +
        "increases the protective quality of this armour. In addition to " +
        "being beautifully made, it empowers the owner with an aura of " +
        "respect and " + query_effect() + ", what makes it the object of " +
        "every soldier's lust.\n";
}

void
create_armour()
{
    set_name(({ "mail", "chainmail" }));
    set_short("scale-plated chain mail");
    add_adj(({ "chain", "plated", "scales", "scale-plated", query_color() }));

    set_long(long_description);
    
    add_item(({ "rings", "metal rings", "steel rings", "links" }),
        "Hundreds or even thousands of small metal rings have been used to " +
        "make this armour, thus this fine mesh suit feels more like cloth " +
        "than armour, yet many a killing blow has been turned aside by its " +
        "links.\n");
    add_item(({ "link", "ring", "metal ring", "metal link" }),
        "This metal ring looks exactly like thousands of the other ones " +
        "making this armour.\n");
    add_item(({ "plates", "metal plates", "scales", "scale-plates", "plate" }),
        "The chain mail has been reinforced by metal scale-plates to " +
        "protect the vital parts of the wearer's body.\n");
    add_item(({ "fabric", "padding", "layer" }),
        "The armour is padded with a layer of fabric to prevent chafing " +
        "and to lessen the impact of blows.\n");
        
    set_keep(1);
    set_af(TO);
    set_ac(43);
    set_am( ({-2, 4, -2}) );
    set_at(A_BODY);
    
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, "This is the elite draconian armour, worn " +
        "only by the most skilled members of the dragonarmy. It will " +
        "increase the wearer's stat; which one - it depends on the " +
        "color of the army (blue - SS_DEX, red - SS_DIS, black - SS_STR, " +
        "white - SS_INT, green - SS_CON, and by default SS_WIS). " +
        "It requires at least 50 in average stat to be worn. It also " +
        "greatly increases resistance against magical healing, setting " +
        "non-additive MAGIC_I_RES_LIFE at 25.\n");
    add_prop(MAGIC_AM_ID_INFO, ({
        "This armour has been magically enchanted and it will make " +
        "the wearer to feel more self-confident, but only experienced " +
        "people may wear it since it is used by the elite forces of the " +
        "dragonarmy.\n", 10,
        "Once donned, the chain mail grants its powers to the wearer, " +
        "increasing one of his stats.\n", 35,
        "However, the armour will make the wearer more resistant to " +
        "any forms of life magic, so he is invulnerable to powers of " +
        "the false Gods' followers.\n", 70 }) );
    add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment" }) );

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT,  F_WEIGHT_DEFAULT_ARMOUR(43, A_BODY));
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(43));
}

public void
set_color(string new_color)
{
    color = new_color;  // I do not change adjectives, since it still will be
                        // the same armour. Colors are used oly to set the
                        // extra stat bonus.
}

public string
query_color()
{
    if ( color != "uncolored" )
        return color;
    else
        return "dark";
}

/* Function name: query_info
 * Description  : It returns the information for the person who
 *                uses ifentify spell on this armour.
 */
public string 
query_info()
{
    switch ( query_color() )
    {
        case "blue":
            return "more agile";
        break;
        case "black":
            return "stronger";
        break;
        case "green":
            return "healthier";
        break;
        case "white":
            return "more intelligent";
        break;
        case "red":
            return "fiercer";
        break;
        default:
            return "wiser";
        break;
    }
}

/* Function name: query_effect
 * Description  : It returns the information about the effect this
 *                armour provides to its wearer.
 */
public string
query_effect()
{
    string my_color = query_color();
    
    if ( my_color == "black" || my_color == "green" )
        return "power";
    else if ( my_color == "white" || my_color == "red" )
        return "fear";
    else
        return "authority";
}

/* Function name: set_bonus_stat
 * Description  : It decides what stat the armour will increase.
 */
public void
set_bonus_stat(object who)
{
    switch ( query_color() )
    {
        case "red":
            who->set_stat_extra(SS_DIS, 
                who->query_stat_extra(SS_DIS) + BONUS_STAT);
        break;
        case "blue":
            who->set_stat_extra(SS_DEX,
                who->query_stat_extra(SS_DEX) + BONUS_STAT);
        break;
        case "white":
            who->set_stat_extra(SS_INT,
                who->query_stat_extra(SS_INT) + BONUS_STAT);
        break;
        case "black":
            who->set_stat_extra(SS_STR,
                who->query_stat_extra(SS_STR) + BONUS_STAT);
        break;
        case "green":
            who->set_stat_extra(SS_CON,
                who->query_stat_extra(SS_CON) + BONUS_STAT);
        break;
        default:
            who->set_stat_extra(SS_WIS,
                who->query_stat_extra(SS_WIS) + BONUS_STAT);
        break;
    }
}

/* Function name: remove_bonus_stat
 * Description  : Removes the bonus stat from the person who has been
 *                wearing this armour.
 */
public void
remove_bonus_stat(object who)
{
    switch ( query_color() )
    {
        case "red":
            who->set_stat_extra(SS_DIS, 
                who->query_stat_extra(SS_DIS) - BONUS_STAT);
        break;
        case "blue":
            who->set_stat_extra(SS_DEX,
                who->query_stat_extra(SS_DEX) - BONUS_STAT);
        break;
        case "white":
            who->set_stat_extra(SS_INT,
                who->query_stat_extra(SS_INT) - BONUS_STAT);
        break;
        case "black":
            who->set_stat_extra(SS_STR,
                who->query_stat_extra(SS_STR) - BONUS_STAT);
        break;
        case "green":
            who->set_stat_extra(SS_CON,
                who->query_stat_extra(SS_CON) - BONUS_STAT);
        break;
        default:
            who->set_stat_extra(SS_WIS,
                who->query_stat_extra(SS_WIS) - BONUS_STAT);
        break;
    }

}

public string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + color;
}

public void
init_recover(string arg)
{
    string *a = explode(arg, "&&");
    set_color(a[1]);
    init_arm_recover(a[0]);
}

varargs mixed
query_magic_protection(string prop, object what)
{
    if ( what == query_worn() && prop == MAGIC_I_RES_LIFE )
        return ({ 25, 0 });
    
    return ::query_magic_protection(prop, what);
}

public mixed
wear(object what)
{
    wearer = TP;
    
    if ( wearer->query_average_stat() < 50 )
    {
        say(QCTNAME(TP) + " attempts to wear the " + what->short() +
            ", but it doesn't seem to fit " + OBJECTIVE(TP) + ".\n");
        return "You try to wear the " + what->short() + ", but you " +
            "do not seem to be worthy of it.\n";
    }
                
    wearer->catch_msg("As you wear " + short() + " a feeling of " +
        "self-confidence sweeps over you.\n");
    say(QCTNAME(wearer) + " seems to become more self-confident as " + 
        HE(wearer) + " wears the " + short() + ".\n");
    
    set_bonus_stat(wearer);    
    wearer->add_magic_effect(TO);
    
    return 1;
}    

public mixed
remove(object what)
{
    set_this_player(query_worn());

    remove_bonus_stat(query_worn());
    TP->remove_magic_effect(TO);

    if ( TP->query_npc() )
        return 0;
        
    TP->catch_msg("You remove the " + short() + " and the feeling of " +
        "self-confidence leaves you.\n");
    say("As " + QTNAME(TP) + " removes the " + short() + ", " + HE(TP) + 
        " seems to become less self-confident.\n");

    return 1;
}

        

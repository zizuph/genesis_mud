/*
 * File: fullplate.c
 *
 * Full plate armour, created for the dragonarmy Highlords.
 * Created for Verminaard and Kitiara, but possible use for other
 * Highlords too.
 *
 * Blizzard, 12.07.2003
 */

/* Navarre Feb 2007, changed to use F_DEFAULT_WEIGHT and F_VALUE */
/* Navarre August 2009, commented out the punishment in LIVE_I_QUICKNESS
 *                      other armours now exist that are better than this
 *                      one, easier to get and without the punishment.
 *                      Also now that LIVE_I_QUICKNESS influence special
 *                      attacks, its too harsh a punishment.
 *
 * Navarre October 2010, Removed race restrictions as we are trying to remove
 *                       such restrictions globally.
 *
 * Navarre September 2013, After discussion with AoB (Petros), we agreed to
 *                         remove the death resist from the armour. It was not
 *                         thematic and something Blizzard added previously.
 *                         In Krynn the dragons do Fire, Lightning, Poison,
 *                         Acid, and Ice. Not Death and not Life.
 *
 * Carnak September 2016, Moved magic properties below create_fullplate to fix
 *                        an issue with magic identification showing the wrong
 *                        resistance.
 */                        
inherit "std/armour.c";
inherit "/lib/keep";

#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

private string   color = "uncolored";
object           wearer;
int              alarm_id, steal_alarm;
int              steal_mana_time = 0;

public string    color_protection();
public string    query_color();

public void
create_fullplate()
{

}

void
create_armour()
{
    set_name(({ "armour", "mail", "suit", "fullplate" }));
    set_short("deep-blue full plate armour");
    add_adj(({ "deep-blue", "blue", "full", "plate" }));
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_long("This plate mail is the best armour a warrior can wear, both " +
        "in appearance and protection. The perfectly fitted interlocking " +
        "plates are specially angled to deflect blows, and the entire suit " +
        "is carefully adorned with rich engraving and embossed detail. " +
        "Being constructed especially for the dragonarmy Highlords, it is " +
        "comprised of a dark blue alloy and offers protection from all but " +
        "the most determined attacks. The aura of powerful magic radiates " +
        "from this armour.\n");

    add_item(({ "plate", "plates" }),
        "Perfectly fitted and interlocking metal plates are covering the " +
        "vital areas of the wearer.\n");
    add_item(({ "engraving", "decorations", "decoration", "detail" }),
        "This armour has been not only perfectly crafted, but also " +
        "carefully decorated. On the main plate, protecting the chest, " +
        "a picture of the almost alive dragon head has been engraved. " +
        "It seems to gleam with a dim @@query_color@@ light. The " +
        "pauldrons meant to protect each of the wearer's shoulders are " +
        "stylized for dragon scales. This makes the armour look quite " +
        "spectacularly.\n");
    add_item(({ "picture", "head", "dragon head", "main plate" }),
                "A picture of a dragon head has been engraved on " +
                "the chest plate.\n");
    add_item(({ "scales", "scale", "pauldron", "pauldrons" }),
        "Each pauldron has been stylized to look like a big dragon scale.\n");
    add_item(({ "straps", "strap" }),
        "The straps can be used to adjust the plates of the " + short() +
        " upon wearing. They also help to keep the individual plates " +
        "together.\n");

    set_ac(53);
    set_at(A_BODY | A_ARMS | A_LEGS);
    set_af(TO);
    set_keep(1);

    add_prop(OBJ_I_COLORABLE, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(53, A_BODY|A_LEGS|A_ARMS));
    add_prop(OBJ_I_VOLUME, 30000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(53));
    
    create_fullplate();
    
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, "This armour has been created especially " +
        "for Highlords and enchanted so it protects the wearer against " +
        "magic attacks (depending on the colour of the army, blue - " +
        "electricity, green - poison, black - acid, white - cold, " +
        "red - death and fire). This will happen at the cost of mana. " +
        "Since it is the best quality and complate armour it provides " +
        "excellent protections. People who are not strong " +
        "enough (SS_STR < 80) may not wear this armour.\n");
    add_prop(MAGIC_AM_ID_INFO, ({
        "This armour has been magically enchanted and it will protect " +
        "the wearer against " + color_protection() + ".\n", 15,
        "However, this will happen at the cost of the wearer's mana.\n", 60}));
    add_prop(MAGIC_AM_MAGIC, ({ 100, "enchantment" }) );
}

public void
set_color(string new_color)
{
    color = new_color;  // I do not change adjectives, since it still will be
                        // the same armour. Colors are used to estimate the
                        // resistance only.
}

public string
query_color()
{
    if (color != "uncolored")
    {
        return color;
    }
    else
    {
        return "multicolored";
    }
}

public string
color_protection()
{
    switch ( query_color() )
    {
        case "red":
            return "fire";
        case "blue":
            return "electricity";
        case "white":
            return "cold";
        case "black":
            return "acid";
        case "green":
            return "poison";
        default:
            return "fire";
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


public int
ready_to_steal()
{
    // Want to assure we don't steal repeatedly
    return (steal_mana_time + 15 < time());
}

/* Function name: steal_mana
 * Description  : Removes 25 mana if ready_to_steal allows it
 *                called from the magic protection.
 */
public void
steal_mana()
{
    if (!ready_to_steal())
    {
        return;
    }

    query_worn()->add_mana(-25);
    steal_mana_time = time();

}

public mixed
query_magic_protection(string prop, object what)
{
    if ( what == query_worn() )
    {
        if ( query_worn()->query_mana() < 25 )
	{
            return ::query_magic_protection(prop, what);
	}

        switch ( query_color() )
        {
            case "red":
                if ( prop == MAGIC_I_RES_FIRE )
                {
                    steal_mana();
                    return ({ 35, 1 });
                }

            break;
            case "blue":
                if ( prop == MAGIC_I_RES_ELECTRICITY )
                {
                    steal_mana();
                    return ({ 35, 1 });
                }

            break;
            case "white":
                if ( prop == MAGIC_I_RES_COLD )
                {
                    steal_mana();
                    return ({ 35, 1 });
                }

            break;
            case "green":
                if ( prop == MAGIC_I_RES_POISON )
                {
                    steal_mana();
                    return ({ 35, 1 });
                }

            break;
            case "black":
                if ( prop == MAGIC_I_RES_ACID )
                {
                    steal_mana();
                    return ({ 35, 1 });
                }

            break;
            default:
                if ( prop == MAGIC_I_RES_FIRE )
                {
                    steal_mana();
                    return ({ 35, 1 });
                }

            break;
        }
    }
    else
    {
        return ::query_magic_protection(prop, what);
    }
}

public void
wear_message()
{
    write("Finally, you managed to wear the armour and even if it limits " +
          "your movements a bit, you feel comfortable and well protected.\n");
    say("Finally, " + QTNAME(wearer) + " manages to wear the " +
        short() + " completely.\n");
}

public mixed
wear(object what)
{
    wearer = TP;

    if ( wearer->query_stat(SS_STR) < 80 )
    {
        say(QCTNAME(TP) + " struggles in attempt to wear the " + short() +
            ", but " + HE(TP) + " does not seem to be able to use it.\n");
        return "You try to wear the " + short() + ", but you " +
               "do not seem to be able to use it.\n";
    }

    wearer->catch_msg("You slowly don the " + short() + " carefully " +
        "adjusting the straps, that keep the metal plates together.\n");
    say(QCTNAME(wearer) + " slowly dons the " + short() + " carefully " +
        "adjusting the straps, that keep the metal plates together.\n");
    wearer->add_magic_effect(TO);

    if ( !wearer->query_npc() )    
        alarm_id = set_alarm(5.0, 0.0, &wear_message());

    return 1;
}

public mixed
remove(object what)
{
    set_this_player(query_worn());

    if (alarm_id)
    {
        remove_alarm(alarm_id);
    }

    TP->remove_magic_effect(TO);

    if (TP->query_npc())
    {
        return 0;
    }
        
    TP->catch_msg("You slip out of your " + short() + ".\n");
    say(QCTNAME(TP) + " slips out of " + HIS(TP) + " " + short() + ".\n");
    return 1;
}


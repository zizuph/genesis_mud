/* /d/Gondor/guilds/rangers/obj/numenor_sword.c
 *
 *  Tigerlily, 2004-10-10
 *  A sword for the warg cave
 *  Has some magical properties in the hands of a ranger
 *  Only rangers may wield it, as it is a special heirloom
 *  for the guild.  One can only obtain this sword by assisting
 *  an apprentice to finish the last task of Lossefalme and
 *  gain the token to apply to a company, hence, the access
 *  to this sword is limited only to those occasions where
 *  a team of two rangers completes this task.
 *  The warg must be killed to obtain it.
 *  Borrowed to some extent from the famous nazgul_sword.
 *  (although not nearly as powerful of course ;)
 */

inherit "/std/weapon";
inherit "/d/Genesis/magic/resist";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

int try_to_burn(object enemy, int dam);
int read_script(string str);

void
create_weapon()
{
    set_name("sword");
    add_name("longsword");
    add_name("lightbringer");
    add_name("Lightbringer");
    set_adj(({ "ancient", "numenorean", "Numenorean" }));
    set_short("ancient numenorean longsword");
    set_long("A heavy longsword forged in the style of ancient " +
        "Numenor. The hilt is made of burnished gold with a slight " +
        "patina that reveals its great age and lineage. The blade is made " +
        "from cold steel that yet appears warm and bright, as if it " +
        "contained its own source of heat. A flowing script " +
        "is inlaid along each side of the blade in mithril runes.\n");

    set_likely_break(10);

     set_default_weapon(48, 55, W_SWORD, W_SLASH | W_IMPALE, W_ANYH, TO);
    /* Designate this as a magic weapon */
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_I_RES_MAGIC, 50);
    add_prop(OBJ_I_RES_FIRE,  50);
    add_prop(OBJ_I_RES_AIR,   50);
    add_item(({"runes", "script", "flowing script"}), "The script flows " +
        "in glowing mithril along each side of the blade. You may be " +
        "able to decipher it.\n");

    /* Allow for identification of the magical properties */
    add_prop(MAGIC_AM_ID_INFO, ({ "The sword has magic imbued within. ", 20,
        "In the hands of a Ranger of Westerness the magic will unleach! ", 40,
        "The runes on the blade can be deciphered and it will only reach " +
        "its full potetial in the hands of a full Ranger. ", 60,
        "\n", 0,}));
    /* Indicate the level and type of magic */
    add_prop(MAGIC_AM_MAGIC, ({ 20, "abjuration" }));

    /* Let wizards know what the sword does */
    add_prop(OBJ_S_WIZINFO, "This sword does additional damage " +
        "in the hands of a ranger.\n");

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 2800);
    add_prop(OBJ_I_WEIGHT, 9500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(45, 55) + 1000);
}

/*
 * special hit
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{

    object attacker = query_wielded();

    /* did_hit() is called even when the weapon misses, so we need
     * to check if phurt < 0 before we do any special damage.  If
     * phurt < 0, then it was a missed attack. If it's less than
     * 5, give standard messages. Only rangers can access the
     * special attacks.
     */
    if (phurt < 5 || !(RANGERS_FULL_MEMBER(attacker)))
    {
        return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }


    switch(phurt)
    {        
        case 5..9:
            attacker->catch_msg("The ancient numenorean longsword lightly " +
                "slices " + "the " + hdesc + " of " + QTNAME(enemy) + 
                ", as you deftly spin out of reach.\n");
            enemy->catch_msg("The ancient numenorean longsword of " + 
                QTNAME(attacker) + " lightly slices your " + hdesc + 
                ", while your opponent spins deftly out of reach.\n");
            attacker->tell_watcher(QCTNAME(attacker) + 
                " lightly slices the " +
                hdesc + " of " + QTNAME(enemy) + " with the ancient " +
                "numenorean longsword and spins deftly out of reach.\n",
                enemy);
            break;

        case 10..19:
            attacker->catch_msg("The ancient numenorean longsword just " +
                "grazes the " + hdesc + " of " + QTNAME(enemy) + 
                " as it flashes brightly through " +
                "the air.\n");
            enemy->catch_msg("The ancient numenorean longsword of " + 
                QTNAME(attacker) + " just grazes your " + hdesc + 
                ", as it flashes brightly through the air.\n");
            attacker->tell_watcher(QCTNAME(attacker) + " grazes the " +
                hdesc + " of " + QTNAME(enemy) + " with the ancient " +
                "longsword as it flashes brightly " +
                "through the air.\n", enemy);
            break;
        case 20..29:
            attacker->catch_msg("Lunging the ancient numenorean " +
                "longsword " + "at "+ QTNAME(enemy)+ ", you jab " + 
                POSSESSIVE(enemy) + " " + 
                hdesc + " with great force.\n");
            enemy->catch_msg("Lunging the ancient numenorean longsword " +
                "at you, " + QTNAME(attacker) + " jabs your " + hdesc + 
                " with  " + "great force.\n");
            attacker->tell_watcher("Lunging the ancient numenorean " +
                "longsword at " + QTNAME(enemy) + ", " + QTNAME(attacker) + 
                " jabs " + POSSESSIVE(attacker) + " enemy's " + 
                hdesc + " with great " + "force.\n",enemy);
            break;
        case 30..39:
            attacker->catch_msg("Swinging the ancient numenorean longsword at "+
                QTNAME(enemy)+ ", you hurt " + POSSESSIVE(enemy) + " " + 
                hdesc + " with a burst of white flame.\n");
            enemy->catch_msg("Swinging the ancient numenorean longsword " +
                "at you, " + QTNAME(attacker) + " hurts your " + hdesc + 
                ", with a burst of white flame.\n");
            attacker->tell_watcher("Swinging the ancient numenorean longsword " +
                "at " + QTNAME(enemy) + ", " + QTNAME(attacker) + " hurts " + 
                POSSESSIVE(attacker) + " enemy's " + hdesc + " with a burst " +
                "of white flame.\n",enemy);
            break;
        case 40..49:
            attacker->catch_msg("With a strong slash you hurt "+QTNAME(enemy) +
                "'s " + hdesc + " rather badly, piercing deeply with the " +
                "ancient numenorean longsword.\n");
            enemy->catch_msg("With a strong slash, " + QTNAME(attacker) + " hurts " +
                "your " + hdesc + " rather badly, piercing deeply with the " +
                "ancient numenorean longsword.\n");
            attacker->tell_watcher("With a strong slash, " + QTNAME(attacker) + 
                " hurts " + QTNAME(enemy) + "'s " + hdesc + " rather badly, " +
                "piercing deeply with the ancient numenorean longsword.\n",enemy);
            break;
        case 50..59:
            attacker->catch_msg("Your mighty ancient blade causes great pain " +
                "as it hits " + QTNAME(enemy) + " in the " + hdesc + ", white " +
                "fire engulfing the wound.\n");
            enemy->catch_msg("You feel great pain as " + QTNAME(attacker) + 
                " hits your " + hdesc + " with "+ POSSESSIVE(attacker) +
                "ancient numenorean longsword, and you are engulfed " +
                "by white fire!\n");
            attacker->tell_watcher(QCTNAME(attacker) + " hurts " + QTNAME(enemy) + 
                " very badly with the ancient numenorean longsword, white fire " +
                "engulfing " + POSSESSIVE(attacker)+" enemy's " + hdesc + 
                "!\n", enemy);
            break;
        case 60..69:
            attacker->catch_msg("The ancient numenorean longsword rends " +
                "your enemy's " + hdesc + " asunder with a sickening sound.\n");
            enemy->catch_msg("The ancient numenorean longsword of " +
                QTNAME(attacker) + " rends your " + hdesc + " asunder " +
                "with a sickening sound!\n");
            attacker->tell_watcher("The ancient numenorean longsword " +
                "rends the " + hdesc + " of "+QTNAME(enemy)+ " asunder " +
                "with a sickening sound.\n", enemy);
            break;
        case 70..79:
            attacker->catch_msg("Blood is splattered all around as you wreak " +
                "havoc upon the " + hdesc + " of " + QTNAME(enemy) + " with " +
                "your ancient numenorean longsword. A bright light flashes from the " +
                "tip of the blade!\n");
            enemy->catch_msg("Blood splatters all around as the ancient " +
                "longsword of " + QTNAME(attacker)+" wreaks havoc upon your " +
                hdesc + ". A bright light flashes from the tip of the blade.\n");
            attacker->tell_watcher("Blood splatters all around as " + 
                QTNAME(attacker) + " wreaks havoc on " + QTNAME(enemy) + 
                "'s " + hdesc + ". A bright light flashes from the tip of " +
                "the ancient numenorean longsword!\n",enemy);
            break;
        default:
            attacker->catch_msg("Your ancient numenorean longsword nearly cuts off the " +
                hdesc + " of "+QTNAME(enemy)+" as you slash with all your " +
                "might!\n");
            enemy->catch_msg("Your " + hdesc + " is nearly cut off as " + 
                QTNAME(attacker) + " swings " + POSSESSIVE(attacker) + 
                " ancient numenorean longsword at you with great force!\n");
            attacker->tell_watcher(QCTNAME(enemy) + "'s " + hdesc + 
                " is nearly cut off as the ancient numenorean longsword of " + 
                QTNAME(attacker) + " hits with great force!\n",enemy);
            break;
      }

    /* Kill the target, if appropriate */
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(attacker);
        return 1;
    }
    if (random(8) == 0)
    {
        try_to_burn(enemy, dam/3);
    }
    return 1;
}
int
try_to_burn(object enemy, int dam)
{
    object wielder = query_wielded();
    int    res     = enemy->query_magic_res(MAGIC_I_RES_FIRE);
    dam = dam - (res*dam/100);

    if (dam < 1) 
    {
        enemy->catch_msg("The plume of white flame surrounding the " +
            "ancient numenorean longsword does not harm you.\n");
    return 1;
    }

    enemy->heal_hp(-dam);
    enemy->catch_tell("White fire leaps from the ancient numenorean " +
        "longsword to burn you!\n");
    wielder->catch_tell("You smell burnt flesh as a plume of white flame " +
        "leaps from the ancient sword, burning your opponent!\n");
    wielder->tell_watcher("You smell burnt flesh as a plume of white flame " +
        "leaps from the tip of the ancient numenorean longsword and " +
        "burns " + QTNAME(enemy) + ".\n", enemy);
    return 1;
}

public mixed
wield(object wep)
{
    object tp = this_player();
    //only rangers get magical effect
    if (!IS_RANGER(tp))
    {
        return 0;
    }
    if (APPRENTICE_MEMBER(tp))
    {
        write("You feel that this blade may yield a more " +
            "powerful effect against the Enemy in the " +
            "the hands of a more skilled Ranger.\n");
        return 0;
    }
    if (ENV(TO) == tp)
        tp->add_magic_effect(TO);
    add_prop(OBJ_I_LIGHT, 2);
    write("The hilt of the sword fits perfectly in your hands, and you " +
        "feel the glowing light of the ancient numenorean longsword flow up " +
        "through your arms.\n");
    say(QCTNAME(tp) + " wields the ancient numenorean longsword, and a soft " +
        "warm light seems to glow from it.\n");
    return 1;
}

public mixed
unwield(object wep)
{
    object  tp = TO->query_wielded();
    if (!IS_RANGER(tp))
    {
        return 0;
    }
    if (APPRENTICE_MEMBER(tp))
    {
        return 0;
    }
    add_prop(OBJ_I_LIGHT, 0);
    tp->catch_msg("As you release your grip on the ancient " +
        "longsword, the glowing warmth subsides.\n");
    tp->remove_magic_effect(TO);
    tp->update_light();
    tell_room(ENV(tp), "As "+QTNAME(tp)+" unwields the ancient numenorean longsword, "
      + "it becomes once again an ordinary steel blade.\n", tp);
    return;
}

int
read_script(string str)
{
    object tp = this_player();

    if (!strlen(str))
    {
        notify_fail("Decipher runes?\n");
        return 0;
    }
    if (IS_RANGER(tp))
    {
        write("A script glows on the sides of " +
            "the sword in mithril runes. The language is ancient " +
            "Numenorean: Uri-yat Zagar. You decipher it as: " +
            "'Lightbringer, or, Sword of the Sun and Moon.'\n");
        return 1;
    }
    write("A beautiful script glows on the sides of " +
        "the sword in mithril runes, but you are unable to make " +
        "out the meaning.\n");
    return 1;
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    from->update_light();
    to->update_light();
}
void
init()
{
    ::init();
    add_action(&read_script(), "decipher");
    return;
}

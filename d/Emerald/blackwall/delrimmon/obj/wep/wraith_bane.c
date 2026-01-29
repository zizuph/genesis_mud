/*
 *  /d/Emerald/blackwall/delrimmon/obj/wep/wraith_bane.c
 *
 *  This weapon is wielded by Ugluk:
 *      /d/Emerald/blackwall/delrimmon/npc/ugluk.c
 *  It is a powerful weapon, created by Saruman to make sure that
 *  the nazgul do not interfere with his plans. It is a weapon
 *  of undead-slaying.
 *
 *  Copied and modified with permission from Elessar's:
 *      /d/Gondor/elessar/orc_slayer.c
 *
 *  Copyright (c) July 1997, Cooper Sherry (Gorboth)
 *
 *  2017-08-28 - Cotillion
 *  - Fixed runtime in check_undead_present
 *  - Will now dull, except when fighting undeads
 *
 *  Cotillion - 2020-10-04
 *  - Fixed type confusion in read runes command
 */
#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep";

#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

// Definitions
#define  HERE_MSG  ({  ("vibrates violently in your hand!"),\
                       ("wrenches to and fro in your hand!"),\
                       ("grows more and more difficult to hold!"),\
                       ("dips and sways about, pulling your arm with it!"),\
                    })
#define  NEAR_MSG  ({  ("vibrates slightly in your hand."),\
                       ("darts softly to and fro in your grip."),\
                       ("grows slightly difficult to hold well."),\
                       ("sways a bit, pulling at your arm."),\
                    })
#define  TPH_MSG   ({  ("struggles desperately to control the blackened"\
                      + " mithril scimitar!"),\
                       ("grips the blackened mithril scimitar tightly,"\
                      + " as it darts violently about."),\
                       ("attempts to steady the blackened mithril"\
                      + " scimitar, which is vibrating violently."),\
                       ("is nearly unable to control the blackened"\
                      + " mithril scimitar, which darts wildly"\
                      + " of its own accord!"),\
                    })

// Global Variables
static int     Count,
               Vib_alarm;

// Prototypes
public varargs void check_for_enemies();
public int          check_undead_present(mixed roomstr);
int                 exa_runes(string str);
public string       long_func();
private string      rune_description();
public int          undead_near(object room);
public int          undead_present(object room);

public void
create_weapon()
{
    set_name("sword");
    add_name( ({"weapon","scimitar"}) );
    set_adj( ({"blackened","mithril"}) );

    set_short("blackened mithril scimitar");
    set_long(long_func);

    add_item(({"rune","runes"}), rune_description);
    add_item(({"crosspiece","crosspieces","emblem"}), BSN(
        "The crosspiece of the blackened mithril scimitar bears at its"
      + " center a circular ornament embossed with the symbol of a"
      + " white hand against a black field."));

    // the last argument sets the object that defines the wield/unwield
    // functions:
    set_default_weapon(40, 40, W_SWORD, W_SLASH, W_RIGHT, TO);

    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(OBJ_S_WIZINFO, BSN(
        "This sword is magically enhanced to slay undead opponents."
      + " It is wielded by /d/Emerald/blackwall/delrimmon/npc/ugluk.c."
      + " It will vibrate violently depending on whether or not"
      + " undead opponents are nearby."));
    add_prop(MAGIC_AM_MAGIC,({ 50, "enchantment" }));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO, ({
        "An aura of evil magic radiates from the scimitar!\n",1,
        "This weapon can sense the presence of undead creatures.\n",10,
        "This weapon is called 'Wraith Bane', and will deliver"
      + " terrible destruction upon the undead!\n",20,
        "It was created by Saruman in the furnaces beneath"
      + " Orthanc, that he might vie for power against the minions"
      + " of Sauron in Mordor.\n",50 }));

    add_prop(OBJ_I_WEIGHT, 12500);
    add_prop(OBJ_I_VOLUME,  5800);
    // A magical weapon should either have a higher value, or you
    // should set OBJ_I_NO_BUY so it cannot be bought from shops.
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(40,40) + random(200) - 100);

    set_wf(TO);
    set_keep();
}

public int
check_undead_present(mixed roomstr)
{
    object *liv,
            room;

    if (!roomstr)
        return 0;

    seteuid(getuid(TO));

    //catch(roomstr->short());
    if (stringp(roomstr))
    {
        if (file_size(roomstr + ".c") <= 0)
            return 0;
        catch(roomstr->short());
        if (!objectp(find_object(roomstr)))
            return 0;

        room = find_object(roomstr);
    }
    else
    {
        room = roomstr;
    }

    if (!objectp(room))
        return 0;

    /*
     * The FILTER_LIVE() might be superfluous if for all
     * non-living objects LIVE_I_UNDEAD is not set.
     * To prevent possible errors if a weapon or another
     * dead object has this prop set, we filter the livings
     * first.
     *
     * Note that query_undead() is defined only in the
     * shadow of the Society of Morgul Mages and that the
     * generic check is the check for the prop LIVE_I_UNDEAD.
     */
    liv = FILTER_LIVE(all_inventory(room));
    // For testing purposes, we remove wizards:
    liv = filter(liv, not @ &->query_wiz_level());
    return sizeof(filter(liv, &->query_prop(LIVE_I_UNDEAD)));
}

public int
undead_near(object room)
{
    int     n,
            undead_found;
    string *exit_rooms;

    if (!objectp(room))
        return 0;

    if (room->query_prop(ROOM_I_IS))
        ;
    else if (ENV(TO) != room)
        return 0;
    else
        room = ENV(room);

    exit_rooms = room->query_exit_rooms();

    n = sizeof(exit_rooms);
    while (n--)
        undead_found += check_undead_present(exit_rooms[n]);

    return undead_found;
}

public int
undead_present(object room)
{
    if (!objectp(room))
        return 0;

    if (room->query_prop(ROOM_I_IS))
        ;
    else if (ENV(TO) != room)
        return 0;
    else
        room = ENV(room);

    return check_undead_present(room);
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy,
        int dt, int phit, int dam)
{
    if (!objectp(enemy) || !(enemy->query_prop(LIVE_I_UNDEAD)))
        return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (phurt == -1 || phurt == -2) // -2 Could be split into a parry message.
    {
        query_wielded()->catch_msg("The " +short()+ " slashes"
          + " violently through open air.\n");
        enemy->catch_msg("You deftly duck as "+QTNAME(query_wielded())
          + " swings " +query_wielded()->query_possessive() + short()
          + " at you!\n");
    }
    else if (phurt == 0) // This means hit, but weapon bounces off the armour.
    {
        query_wielded()->catch_msg("Your " +short()+ " just barely misses "+
            QTNAME(enemy)+"!\n");
        enemy->catch_msg("You are just barely able to dodge the "
      + short() + " of " +QTNAME(query_wielded())+ " as it slashes violently"
      + " in front of you!\n");
    }
    else
    {
        enemy->heal_hp(-dam); /* The sword does double damage on the undead */

        query_wielded()->catch_msg("Your " +short()+ " slashes violently into"
          + " the undead flesh of " +QTNAME(enemy)+ "!\n");
        enemy->catch_msg("You shriek as the " +short()+ " slashes"
          + " violently through your flesh!\n");
	tell_room(environment(enemy), QCTNAME(enemy)+" shrieks in dismay as the "
			+ short() + " cuts deeply!\n",({enemy,query_wielded()}));
    }
    return 1;
}

public string
long_func()
{
    string  txt =
          "This weapon looks positively evil. A long and cruelly curved"
        + " blade of mithril extends from the weapon's simple crosspiece."
        + " Some foul process has corrupted the natural gleam of the"
        + " silver, leaving its rune-carved surface with a blackened"
        + " hue.";

    if (undead_present(ENV(TO)))
        txt += " The " +short()+ " is vibrating violently!";
    else if (undead_near(ENV(TO)))
        txt += " The " +short()+ " is vibrating slightly.";

    return BSN(txt);
}

public varargs void
check_for_enemies()
{
    object  wielder;

    if ( !objectp( wielder = query_wielded() ) )
        return;

    // This is the easiest way to randomize the interval
    // between messages a little.
    if (random(Count))
        return;
    if (Count <= 12)
        Count += random(2);

    /*
     * What happens if the player is carrying but not
     * wielding the weapon?
     */
    if (undead_present(ENV(TO)))
    {
        if (objectp(wielder))
        {
            wielder->catch_msg("The " + short()
              + " " + ONE_OF_LIST(HERE_MSG) + "\n");
            say(QCTNAME(wielder) + " " + ONE_OF_LIST(TPH_MSG) + "\n");
        }

        else if (ENV(TO)->query_prop(ROOM_I_IS))
        {
            say("The " +short()+ " vibrates violently!\n");
        }
    }

    else if (undead_near(ENV(TO)))
    {
      // Better use different messages chosen randomly.
      // It is boring to see the same message spamming
      // your screen over and over.
        if (objectp(wielder))
        {
            wielder->catch_tell("The " + short()
              + " " + ONE_OF_LIST(NEAR_MSG) + "\n");
            say(QCTNAME(wielder)+"'s " +short()+
                " vibrates slightly.\n", wielder);
        }

        else if (ENV(TO)->query_prop(ROOM_I_IS))
        {
            say("The " +short()+ " vibrates slightly.\n");
        }
    }

    /*
     * You could switch the alarm on and off when the weapon
     * is wielded and unwielded.
     * Right now, the alarm is running all the time, even if
     * the weapon is in the store room of a shop or in
     * a backpack or a scabbard.
     * Moreover, either this function is called by Vib_alarm,
     * then this call is not necessary, or it is not called,
     * then this call won't set the alarm up.
     * So remove this, and set the alarm up from enter_env().
    if (!Vib_alarm || !sizeof(get_alarm(Vib_alarm)))
        Vib_alarm = set_alarm(0.0, 10.0, &check_for_enemies());
     */
}

public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    /*
     * If the object is cloned or destroyed, stop here:
     */
    if (!objectp(dest) || !objectp(old))
        return;

    /*
     * A possible way to set up the alarm:
     * Only when in the inventory of a living (but
     * fix check_for_enemies):
    if (!living(dest)) // could also be interactive(dest)
    {
        remove_alarm(Vib_alarm);
        Vib_alarm = 0;
        return;
    }

    if (!Vib_alarm || !sizeof(get_alarm(Vib_alarm)))
        Vib_alarm = set_alarm(5.0, 10.0, check_for_enemies);
     */
}

/*
 * Function name: wield
 * Description  : This function might be called when someone tries to wield
 *                this weapon. To have this function called, use the function
 *                set_wf().
 * Arguments    : object obj - the weapon someone tried to wield.
 * Returns      : int  0 - wield this weapon normally.
 *                     1 - wield the weapon, but print no messages.
 *                    -1 - do not wield the weapon, use default messages.
 *                string - do not wield the weapon, use this fail message.
 */
public mixed
wield(object obj)
{
    // Perhaps add some wield check here.
    if (TP->query_prop(LIVE_I_UNDEAD) && !TP->query_wiz_level())
        return "The " + short() +
            " is vibrating so violently that you are unable to wield it.\n";

    if (!Vib_alarm || !sizeof(get_alarm(Vib_alarm)))
    {
        Count = 0;
        Vib_alarm = set_alarm(2.0, 5.0, check_for_enemies);
    }

    if (undead_present(ENV(TP)))
        write("As you wield the " + short() + " it begins to vibrate"
            + " violently.\n");
    else if (undead_near(ENV(TP)))
        write("As you wield the " + short() + " it begins to vibrate"
            + " slightly.\n");
    return 0;
}

/*
 * Function name: unwield
 * Description  : This function might be called when someone tries to unwield
 *                this weapon. To have this function called, use the function
 *                set_wf().
 * Arguments    : object obj - the weapon to stop wielding.
 * Returns      : int  0 - the weapon can be unwielded normally.
 *                     1 - unwield the weapon, but print no messages.
 *                    -1 - do not unwield the weapon, print default messages.
 *                string - do not unwield the weapon, use this fail message.
 */
public mixed
unwield(object obj)
{
    remove_alarm(Vib_alarm);
    Vib_alarm = 0;

    return 0;
}

string
rune_description()
{
    string rune_txt = "Runes have been cunningly etched into the"
                    + " blackened metal of this scimitar";

    if (TP->query_skill(SS_LANGUAGE) > 45)
    {
        rune_txt += ", spelling the Quenya word 'Umbartulairi'";
    }

    if (TP->query_skill(SS_LANGUAGE) > 75)
    {
        rune_txt += ", which means 'Wraith-bane'";
    }

    return BSN(rune_txt + ".");
}

int
exa_runes(string str)
{
    if (!strlen(str))
        NFN0("Read what?");

    if (str != "rune" && str != "runes")
        NFN0("What do you want to read?");

    write("You study the runes on the sword carefully.\n"
             + rune_description());

    return 1;
}

void
init()
{
    ::init();
    add_action(exa_runes, "read");
}

/*
 * /d/Gondor/mordor/obj/wep/whip.c
 *
 * This is a whip. Currently it is defined as a /std/object for I don't see
 * which type of weapon to define it. The problem is that you cannot force
 * anyone to use a hand to wield it until I've patched the combat system, so
 * this will be the solution for now :-(
 *
 * /Mercade, 26 September 1993
 *
 * Revision history:
 *     Sept-9-97, Gorboth
 *       Changed set_long() and add_item( ({"sturdy handle", "handle" }) )
 *       to make the English more clear and correct.
 */

inherit "/std/object";

#include "/d/Gondor/defs.h"
#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>

#define TIME_BETWEEN_WHIPS   15.0 /* float */
#define MAXIMUM_WHIP_DAMAGE  50
#define MAXIMUM_WHIP_LASHES 100
#define INITIAL_VALUE       300
#define LASH_COST             2

/*
 * Global variables
 */
int can_not_whip_again = 0; /* You have to wait before you can whip again */
int total_whip_lashes = 0;  /* The whip will wear out if you use it       */
int alarm_id = 0;           /* the id given from set_alarm                */

/*
 * To create the whip
 */
void
create_object()
{
    set_name("whip");
    set_pname("whips");
    add_adj("strong");
    add_adj("orkish");
    add_adj("leather");
    add_adj("long");

    set_short("long leather whip");
    set_pshort("long leather whips");
    set_long(BSN("This is a long leather whip with a sturdy handle and short "
      + "strips of leather on the far end for extra whipping power. It is " +
        "an excellent tool for managing slaves and prisoners, or for " +
        "simply torturing them. A skilled user will have no trouble " +
        "coming up with at least a dozen other uses."));

    add_item( ({ "sturdy handle", "handle" }),
        BSN("The handle is made of a very sturdy type of leather, rolled " +
        "tightly to provide an excellent grip."));
    add_item( ({ "strips", "short strips", "strips of leather", "far end",
        "leather strips", "short strips of leather" }),
        BSN("The short strips of leather on the far end of the whip are " +
        "added for extra lashing power. Feeling the harsh strokes, a " +
        "reluctant slave or prisoner will get that extra bit of " +
        "encouragement to stay in line."));

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, INITIAL_VALUE);
}

/*
 * Allows someone to use the whip
 */
void
init()
{
    ::init();

    add_action("do_whip", "whip");
}

/*
 * Count the number of lashes made with the whip.
 */
void
whiplash()
{
    can_not_whip_again = 1;
    total_whip_lashes += 1;
    add_prop(OBJ_I_VALUE, (query_prop(OBJ_I_VALUE) - LASH_COST));
    alarm_id = set_alarm(TIME_BETWEEN_WHIPS, 0.0, "can_whip_again");
}

/*
 * Tell all people in the room about the whiplash.
 */
tell_spectators(object tp, object victim)
{
    object *inventory = FILTER_LIVE(all_inventory(environment(tp)));
    int i;

    for (i = 0; i < sizeof(inventory); i++)
    {
        if ((inventory[i] != tp) && (inventory[i] != victim))
        {
            inventory[i]->catch_msg(BSN(tp->query_The_name(inventory[i]) +
                " swings " + POSSESSIVE(tp) + " whip towards " +
                victim->query_the_name(inventory[i]) + " and lashes " +
                OBJECTIVE(victim) + " with it, hurting " + OBJECTIVE(victim) +
                " severely."));
        }
    }
}

/*
 * The parser to get the victim.. .Copied from the standard soul and slightly
 * adjusted to my needs.
 */
object
get_victim(string str)
{
    object *oblist, *tmplist;
    int    i;

    tmplist = ({});
    if (!CAN_SEE_IN_ROOM(this_player()))
        return 0;

    if (!parse_command(str, environment(this_player()), "%l", oblist))
        return 0;
 
    oblist = NORMAL_ACCESS(oblist, 0, 0);

    if (!sizeof(oblist))
        return 0;

    for (i = 0; i < sizeof(oblist); i++)
    {
        if (objectp(oblist[i]) && living(oblist[i]) &&
                (this_player() != oblist[i]) &&
                CAN_SEE(this_player(), oblist[i]))
            tmplist = tmplist + ({ oblist[i] });
    }

    return (sizeof(tmplist) ? tmplist[0] : 0 );
}

/*
 * Whip someone or something or nothing
 */
int
do_whip(string str)
{
    object tp = TP;
    object victim;

    if (ENV(TO) != tp)
    {
        NFN0("You will have to pick up the whip before you can use it.");
    }

    if (can_not_whip_again)
    {
        NFN0("You have to rest your arm before you can whip again.");
    }

    if (total_whip_lashes > MAXIMUM_WHIP_LASHES)
    {
        NFN0("You have used your whip too many times. It won't crack again.");
    }

    if (!strlen(str))
    {
        write(BSN("You lash your whip with a loud crack!"));
        SAY(" lashes " + POSSESSIVE(tp) + " whip with a loud crack!");
        whiplash();
        return 1;
    }

    if (str == "enemy")
    {
        victim = tp->query_attack();
    }
    else
    {
        victim = get_victim(lower_case(str));
    }

    if (!objectp(victim))
    {
        NFN0("No such living found.");
    }

    write(BSN("You swing your whip towards " + victim->query_the_name(tp) +
        " and lash " + OBJECTIVE(victim) + " with it, hurting " +
        OBJECTIVE(victim) + " severely."));
    victim->CATCH_MSG(" swings " + POSSESSIVE(tp) + " whip towards you and " +
        "lashes you with it, hurting you severely.", tp);
    tell_spectators(tp, victim);
    victim->heal_hp(-(random(MAXIMUM_WHIP_DAMAGE) + 1));
    if (victim->query_hp() <= 0)
    {
        victim->do_die(tp);
    }

    /* it will initiate combat on an npc */
    if (victim->query_npc() &&
        !objectp(victim->query_attack()))
    {
        FIX_EUID;

        victim->attacked_by(tp);
        victim->command("kill " + tp->query_real_name());
    }

    whiplash();
    return 1;
}

/*
 * Called to be able to whip again after some time.
 */
void
can_whip_again()
{
    can_not_whip_again = 0;
}

/*
 * If you give the whip to someone or drop it again, it can be instantly used
 * by the new owner. If people use this feature to get a quick recovery of
 * the whip, I might remove this function later.
 */
leave_inv(object from, object to)
{
    ::leave_inv(from, to);

    remove_alarm(alarm_id);
    can_whip_again();
}

/*
 * If you stat the whip you get the total number of done lashes.
 */
string stat_object()
{
    return (::stat_object() + "Total whiplashes: " + total_whip_lashes + "\n");
}

/*
 * Recovery stuff
 */
string
query_recover()
{
    return MASTER + ":#lashes#" + total_whip_lashes + "#";
}

void
init_recover(string arg)
{
    string foobar;

    sscanf(arg, "%s#lashes#%d#%s", foobar, total_whip_lashes, foobar);
    add_prop(OBJ_I_VALUE, (INITIAL_VALUE - (total_whip_lashes * LASH_COST)));
}

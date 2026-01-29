/*
 * magic_ring.c
 *
 * This ring is a magic object found only by players who have
 * just completed the Seer and the Lord Quest. It's a one-shot
 * magic power. When used, it casts a 'pseudo-spell' that inflicts
 * damage on any undeads in the room, and is destroyed in the
 * process.
 *
 * Khail - Feb 12/96
 */
#pragma strict_types

#include "defs.h"

#define AC     1

#define MANA   500
#define DAMAGE 1000

inherit "/std/armour";

public int do_invoke(string str);

/*
 * Function name: create_armour
 * Description  : Turns this object into the ring as armour.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_armour()
{
    set_name("ring");
    add_name("jewelry");
    set_adj("silver");
    add_adj("serpentine");
    set_short("silver serpentine ring"); 
    set_pshort("silver serpentine rings"); 
    set_long("This silvery ring is a strange shape, appearing to " +
        "be a long serpent which has coiled about itself several " +
        "times, but is otherwise unadorned.\n");

    set_ac(AC);
    set_at(A_R_FINGER);
    set_af(TO);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_STEAL, 1);

    add_prop(MAGIC_AM_MAGIC, ({ 20, "transmutation" }));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, "This ring is part of a 'treasure' found " +
        "after completion of the 'Seer and the Lord Quest' in " +
        "Eldoral. It has nothing to do with the quest itself, it's " +
        "just a little something extra thrown in, and once it's " +
        "been used once, it's gone, period. _Never_ supply a " +
        "replacement to a player who says he/she lost it, as it " +
        "doesn't log when it's been used, and the player could " +
        "have used it and wants a freebie.\n");

    add_prop(MAGIC_AM_ID_INFO, ({
        "You sense the ring will somehow aid the wearer in " +
            "his or her time of greatest need.\n", 15,
        "This ring will come to the wearer's defense when its " +
            "name is invoked.\n", 30,
        "As you study the ring, a strange, hissing voice echoes " +
            "in your mind: Lyzdrall.\n", 45, 
        "You extend your senses deep into the ring, and the " +
            "hissing voice echoes again: Undead, how I loathe them, " +
            "fall beneath my fangs, they will!\n",60}));        
            
    remove_item_expiration();
}

/*
 * Function name: init (MASK)
 * Description  : Called when objects meet one another. Used 
 *                here to add the 'invoke' command to players
 *                who have the ring.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    ::init();
    add_action(do_invoke, "invoke");
}

/*
 * Function name: do_invoke
 * Description  : Allows players to attempt to invoke the power
 *                of the ring.
 * Arguments    : str - Argument players passed with the command
 *                      verb.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
public int
do_invoke(string str)
{
    int i;
    object *arr;

  /* Fail if no argument. */
    if (!str || !strlen(str))
        return 0;

  /* Fail if this player isn't wearing the ring. */
    if (!query_worn() || query_worn() != TP)
        return 0;

  /* Fail if the player did not  'invoke lyzdraal' */
    if (lower_case(str) != "lyzdrall")
        return 0;

  /* Fail if the player doesn't have the mana required. */
    if (TP->query_mana() < MANA)
    {
        notify_fail("You invoke Lyzdrall, but have not the " +
            "strength to summon it.\n");
        return 0;
    }

  /* Success, take mana, deliver messages. */
    TP->add_mana(-MANA);

    write("The ring suddenly pulses with a bright light, almost " +
        "painful to look at. It's hard to be sure, but you think " +
        "you can see the image of a brilliant serpent lashing about " +
        "from within the light!\n");
    say("The ring on " + QTNAME(TP) + "'s hand suddenly pulses with " +
        "a bright light, almost painful to look at. It's hard to " +
        "be sure, but you think you can see the image of a brilliant " +
        "serpent lashing about from within the light!\n");

  /* Find all undeads in the player's environment, do damage, */
  /* and kill them if necessary. */
    arr = filter(all_inventory(environment(TP)),
        &->query_prop(LIVE_I_UNDEAD));
    for (i = 0; i < sizeof(arr); i++)
    {
        tell_object(arr[i], "The brilliant serpent strikes out at " +
            "your body!\n");
        tell_room(environment(TP), "The brilliant serpent strikes out " +
            "at " + QTNAME(arr[i]) + "'s body!\n", ({arr[i]}));
        arr[i]->hit_me(DAMAGE, MAGIC_DT, TP, -1, A_BODY);
        if (arr[i]->query_hp() <= 0)
            arr[i]->do_die(TP);
    }

    tell_room(environment(TP), "As suddenly as it arrived, the " +
        "serpent vanishes again, along with the ring.\n");
    seteuid(getuid());
    log_file("serpent_ring_usage", "The serpent ring was used " +
        "by " + TP->query_real_name() + " on " + ctime(time()) +
        " and was destroyed.\n");
    remove_object();
    return 1;
}

/*
 * Function name: query_auto_load
 * Description  : Makes this object an autoloader.
 * Arguments    : n/a
 * Returns      : A string containing this object's filename.
 */
public string
query_auto_load()
{
    return MASTER;
}

public string
query_recover()
{
    return 0;
}

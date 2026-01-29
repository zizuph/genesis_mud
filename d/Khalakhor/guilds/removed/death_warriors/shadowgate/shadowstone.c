/*
 * shadowstone.c
 *
 * Smokey quartz used as a 'trigger' to enter Shadowgate.
 *
 * Khail - May 8/97
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <tasks.h>
#include "/d/Khalakhor/sys/defs.h"
#include "shadowgate.h"

inherit "/std/object";

public void create_object();
public void init();
public int do_gate(string str);
public int do_part(string str);
public void shatter();

/*
 * Function name: create_object
 * Description  : Turns this object into a stone.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_object()
{
    set_name("quartz");
    add_name("stone");
    add_name("shadowstone");
    set_adj("smokey");
    add_adj("faceted");
    set_long("This smokey coloured, multi-faceted stone " +
        "appears to be some sort of quartz. Something is very " +
        "strange about it though. It's slightly transclucent, " +
        "but in the center of it you think you see something " +
        "dark, like a shadow, moving around.\n");

    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a shadowstone. It is " +
        "used by Death Warriors while employing the Talent " +
        "to enter Shadowgate. Use the command 'shadowgate' " +
        "to enter.\n");
}

/*
 * Function name: init (MASK)
 * Description  : Called when another object meets this one.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    ::init();
    add_action(do_gate, "shadowgate");
    add_action(do_part, "shadowpart");
}

/*
 * Function name: do_gate
 * Description  : Allows a player to attempt to use the shadowstone
 *                to enter Shadowgate.
 * Arguments    : str - Extra arguments to the 'shadowgate' command.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
public int
do_gate(string str)
{
    string *rooms,
           my_room;
    int success;

  /* Can only use shadowgate if carrying the shadowstone. */
    if (TP != environment(TO))
        return 0;

#ifdef DEBUG_SHADOWGATE
  /* If we're debugging, make sure only wizards can use this. */
    if (!TP->query_wiz_level())
        return 0;
#endif

  /* Can only enter shadowgate from rooms with a shadow/shadows */
  /* add_item. */
    if (!environment(TP)->item_id("shadow") &&
        !environment(TP)->item_id("shadows"))
    {
        NF("You cannot enter Shadowgate from a room without shadows.\n");
        return 0;
    }

  /* The shadowstone is destroyed in rooms with too much light. */
    if (environment(TP)->query_prop(OBJ_I_LIGHT) > SHATTER_LIGHT_LIMIT)
    {
        shatter();
        return 1;
    }

  /* The shadowstone is inactive in rooms with enough light. */
    if (environment(TP)->query_prop(OBJ_I_LIGHT) > ACTIVE_LIGHT_LIMIT)
    {
        NF("It's too bright here, the shadowstone has been " +
            "rendered inactive!\n");
        return 0;
    }

  /* Can't enter Shadowgate if they don't have enough mana. */
    if (TP->query_mana() < MANA_COST_GATE)
    {
        NF("You hold the " + short() + " before the shadows, but " +
            "have not the strength to use the Talent.\n");
        return 0;
    }

  /* Can't enter Shadowgate if they're too tired. */
    if (TP->query_fatigue() < FATIGUE_GATE_IN)
    {
        NF("You hold the " + short() + " before the shadows, " +
            "but are too physically exhausted to use the Talent.\n");
        return 0;
    }

  
    reset_euid();
    rooms = m_values((SHADOWGATE)->query_shadows());
    my_room = MASTER_OB(environment(TP));

  /* Now see if the player managed to enter Shadowgate, based */
  /* on their 'talent' skill and occupation guildstat. */
    success = TP->resolve_task(TASK_DIFFICULT, ({TS_OCC, THE_TALENT}));

#ifdef DEBUG_SHADOWGATE
    write("Success = " + success + "\n");
#endif

  /* Fail if success was less than a positive number. */    
    if (success <= 0)
    {
        write("Holding the " + short() + " up before you, you " +
            "step calmly towards the shadow, but your talent " +
            "fails you. You are unable to pass beyond into " +
            "Shadowgate, and left weakened by the attempt.\n");
        say("Holding " + LANG_ADDART(short()) + " up before " +
            TP->query_objective() + ", " + QTNAME(TP) + " steps " +
            "towards a shadow, but halts short of actually " +
            "touching it.\n");
        TP->add_mana(-(MANA_COST_GATE / 2));
        TP->add_fatigue(-(FATIGUE_GATE_IN / 2));
        return 1;
    }

  /* Positive success, so let the player through. */  
    write("Holding the " + short() + " up before you, you step " +
        "calmly into the shadow, and pass beyond into Shadowgate.\n");
    say(QCTNAME(TP) + " vanishes into the shadows!\n");
    TP->add_prop(LIVE_I_USED_SHADOWGATE, 1);
    TP->move_living("M", SHADOWGATE);
    if (member_array(my_room, rooms) < 0)
        say("A new shadow forms, and " + QTNAME(TP) + " steps in" +
           " through it.\n");
    else
        say(QCTNAME(TP) + " arrives through the " +
            (SHADOWGATE)->path_to_direction(my_room) + " shadow.\n");

  /* If success was greater than 50%, mana and fatigue cost is */
  /* 75% of base. Otherwise, normal cost. */
    if (success > 50)
    {
        TP->add_mana(-(MANA_COST_GATE * 75 / 100));
        TP->add_fatigue(-(FATIGUE_GATE_IN * 75 / 100));
    }
    else
    {
        TP->add_mana(-MANA_COST_GATE);
        TP->add_fatigue(-FATIGUE_GATE_IN);
    }

    return 1;
}

/*
 * Function name: do_part
 * Description  : ALlows players to 'peek' through the shadows in
 *                shadowgate to see what's outside.
 * Arguments    : str - String passed as an argument to the shadowpart
 *                      command.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
public int
do_part(string str)
{
    object room,
           *larr,
           *darr;
    mapping shadows;
    string view;
    int success;

  /* Can only use shadowpart if holding the shadowstone. */
    if (environment(TO) != TP)
        return 0;

#ifdef DEBUG_SHADOWGATE
    if (!TP->query_wiz_level())
        return 0;
#endif

  /* Can only shadowpart while in Shadowgate. */
    if (MASTER_OB(environment(TP)) != SHADOWGATE)
    {
        NF("You can only do that within Shadowgate.\n");
        return 0;
    }

  /* Make sure the player specified a direction to view in. */
    if (!str || !strlen(str))
    {
        NF("Which direction do you want to see?\n");
        return 0;
    }

    shadows = environment(TP)->query_shadows();

  /* Now make sure the direction the player specified is valid. */
    if (member_array(str, m_indexes(shadows)) < 0)
    {
        NF("Which direction do you want to see?\n");
        return 0;
    }

  /* The shadowstone is destroyed in rooms with too much light. */
    if (environment(TP)->query_prop(OBJ_I_LIGHT) > SHATTER_LIGHT_LIMIT)
    {
        shatter();
        return 1;
    }

  /* The shadowstone is inactive in rooms with enough light. */
    if (environment(TP)->query_prop(OBJ_I_LIGHT) > ACTIVE_LIGHT_LIMIT)
    {
        NF("It's too bright here, the shadowstone has been " +
            "rendered inactive!\n");
        return 0;
    }

  /* If we can't get an object pointer to the other side of the */
  /* shadow exit, try reloading, if still nothing, remove the */
  /* exit. */
    if (!objectp(room = find_object(shadows[str])))
        room->load_me();

    if (!objectp(room = find_object(shadows[str])))
    {
        write("The shadow has been disrupted somehow, and disperses.\n");
        environment(TP)->remove_shadow(str);
        return 1;
    }

  /* Make sure the player has enough mana to view. */
    if (TP->query_mana() < MANA_COST_PART)
    {
        write("You pass the " + short() + " before the shadow to " +
            "the " + str + ", but are too weak to penetrate it.\n");
        say(QCTNAME(TP) + " passes " + LANG_ADDART(short()) +
            " before the shadow to the " + str + ".\n");
        return 1;
    }

  /* Determine percent chance of success. */
    success = TP->resolve_task(TASK_ROUTINE, ({TS_OCC, THE_TALENT}));

#ifdef DEBUG_SHADOWGATE
    write("Success = " + success + "\n");
#endif
 
  /* If success is 0 or less, fail. */
    if (success <= 0)
    {
        write("You pass the " + short() + " before the shadow " +
            "to the " + str + ", concentrating deeply. You are " +
            "unable to penetrate the shadow and see through to " +
            "the other side, however.\n");
        say(QCTNAME(TP) + " passes " + LANG_ADDART(short()) + 
            " before the shadow to the " + str + ", closing " +
            TP->query_possessive() + " eyes and concentrating " +
            "deeply. Nothing seems to happen, however.\n");
        TP->add_mana(-(MANA_COST_PART / 2));
        return 1;
    }

  /* Positive success value, so the player succeeds. */
    say(QCTNAME(TP) + " passes " + LANG_ADDART(short()) + " before " +
        "the shadow to the " + str + ", closing " + 
        TP->query_possessive() + " eyes and concentrating deeply. " +
        "The surface of the shadow shimmers slightly as the " +
        short() + " brushes against it.\n");
    write("You pass the " + short() + " before the shadow to the " +
        str + " concentrating deeply. The surface of the " +
        "shadow shimmers and parts, yielding the view on the other " +
        "side:\n");

  /* If the success was greater than 50%, reduce mana cost by */
  /* 75%. */
    if (success > 50)
        TP->add_mana(-(MANA_COST_PART * 75 / 100));
    else
        TP->add_mana(-MANA_COST_PART);

  /* Not very productive if the player can't see in the other room. */
    if (room->query_prop(OBJ_I_LIGHT) <
        -(TP->query_prop(LIVE_I_SEE_DARK)))
    {
      /* If the percent success was greater than 100, and the */
      /* room is too dark to see in, they can 'sense' people */
      /* in it anyway. No details, just that someone's there. */
        if (success > 100 && sizeof(FILTER_LIVE(all_inventory(room))))
            write("The other side is too dark to see in, however " +
                "your heightened abilities with the Talent tell " +
                "you someone or something is on the other side.\n");
        else
            write("The other side is too dark to see in, however.\n");
        return 1;
    }

  /* Get the long desc. */
    view = room->long();

  /* Get the livings desc. */
    larr = FILTER_LIVE(all_inventory(room));
    larr = FILTER_CAN_SEE(larr, TP);
    if (sizeof(larr))
        view += COMPOSITE_LIVE(larr) + ".\n";

  /* Get the 'dead' desc. */
    darr = FILTER_DEAD(all_inventory(room));
    darr = FILTER_CAN_SEE(darr, TP);
    if (sizeof(darr))
        view += COMPOSITE_DEAD(all_inventory(room)) + ".\n";

    write(view);
    return 1;
}

/*
 * Function name: shatter
 * Description  : Called when the light is to bright for the
 *                shadowstone to survive in and is destroyed.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
shatter()
{
    TP->catch_msg("The light is too intense, and your " + 
        short() + " explodes in a brilliant flash of light!\n");
    say("You see a brilliant flash of light explode near " + 
        QTNAME(TP) + ".\n");
    remove_object();
}
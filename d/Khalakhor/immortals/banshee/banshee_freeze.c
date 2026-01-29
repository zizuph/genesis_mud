#include <tasks.h>

/*
 * Function name: freeze_damage
 * Description  : Inflicts the damage of a freeze attack on the specified
 *                target.
 * Arguments    : object who - Object point to the player to hit.
 * Returns      : N/A
 */
public void
freeze_damage(object who)
{
    int task,
        pen,
        resistance,
        *hitresult;
    string message;
    object *eqarr,
           eqitem,
           freezer;

  /* Ideally a check to ensure 'who' is in the banshee's environment */
  /* before inflicting damage should be made, but since we got 'who' */
  /* from filtering through the banshee's environment, we won't */
  /* bother to save a bit of CPU, as 'who' should always be here. */

    resistance = who->query_magic_res(MAGIC_I_RES_COLD);
    if (!resistance)
        resistance = who->query_prop(MAGIC_I_RES_COLD);

    task = who->resolve_task(TASK_DIFFICULT, resistance);

    if (task > 0)
    {
        who->catch_tell("You feel a slight chill as the wave of magic " +
            "passes around you, but through some strange enchantment " +
            "it does not touch you!\n");
        tell_room(environment(TO), "The wave of cold slips around " +
            QTNAME(who) + ", appearing to be be deflected by some " +
            "invisible force which gleams like ice as the cold wave " +
            "passes " + HIM_HER(who) + "!\n",({TO, who}));
        return;
    }

    pen = (-task)*50;

    hitresult = who->hit_me(pen, MAGIC_DT, TO, -1);
    if (hitresult[0] == -1)
        message = "no ";
    else if (hitresult[0] < 10)
        message = "a little ";
    else if (hitresult[0] < 25)
        message = "some ";
    else if (hitresult[0] < 50)
        message = "significant amounts of ";
    else if (hitresult[0] < 75)
        message = "severe ";
    else if (hitresult[0] < 100)
        message = "devastating amount of ";
    else
        message = "fatal amount of";

    who->catch_tell("As the cold wave passes over you, you suffer " + message +
        " damage from the cold!\n");
    tell_room(environment(TO), "As the cold wave passes over " +
        QTNAME(who) + ", " + HE_SHE(who) + " suffers " + message +
        "damage from the cold!\n", ({who, TO}));

    if (who->query_hp() <= 0)
        who->do_die(TO);

  /* Now inflict some damage on a random piece of equipment. */
    eqarr = deep_inventory(who);
    eqarr = filter(eqarr, &not() @ stringp @ &->query_auto_load());
    if (!sizeof(eqarr))
        return;

    eqitem = eqarr[random(sizeof(eqarr))];
    who->catch_msg("As the cold wave passes over you, your " + 
        eqitem->short() + " becomes intensely cold and fragile!\n");
    eqitem->set_likely_break(eqitem->query_likely_break() + 25);
}

/*
 * Function name: freeze
 * Description  : One of the banshee's special attacks. She summons up a blast
 *                of freezing air, which inflicts damage and makes weapons &
 *                armour more susceptible to breaking.
 * Arguments    : N/A (attack hits all players in the room)
 * Returns      : n/a
 */
public void
freeze(object enemy)
{
    object *targets;

  /* Get a list of viable targets in the room. That is, all livings */
  /* except wizards. */
    targets = all_inventory(environment(TO)) - ({TO});
    targets = filter(targets, living);
    targets = filter(targets, &not() @ &->query_wiz_level());

    tell_room(environment(TO), QCTNAME(TO) + " begins to glow with a " +
        "bright, almost blinding, blue light. Suddenly the light radiates " +
        "away from her in a buffetting wind of intense cold in all "+
        "directions!\n", ({TO}));

    map(targets,freeze_damage);
}

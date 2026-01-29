/*
 * help_me.c
 *
 * A module to inherit into npc's who should shout for help
 * when attacked by other livings.
 */

#pragma strict_types

#include "/d/Raumdor/defs.h"
#include <wa_types.h>
#include <cmdparse.h>

/*
 * Function name: notify_others_of_attack
 * Description  : Called to notify npc's in surrounding rooms that
 *                this npc has attacked and who the attacker was.
 * Arguments    : who - Object pointer to the attacker.
 * Returns      : n/a
 */
public void
notify_others_of_attack(object who)
{
    object *rooms,
           *others;
    int i;

  /* Do nothing if we can't figure out where the player is. */
    if (!environment(TO))
        return;

  /* Do nothing if the npc's environment has no exits. */
    if (!sizeof(environment(TO)->query_exit_rooms()))
        return;

    rooms = ({environment(TO)});
    rooms += map(environment(TO)->query_exit_rooms(), find_object);
    rooms = filter(rooms, objectp);

  /* Do nothing if we can't find any loaded rooms around */
  /* the current environment. */
    if (!sizeof(rooms))
        return;

  /* Call the function come_assist_me in any livings */
  /* around this room. Only guards should have it defined. */
    for (i = 0; i < sizeof(rooms); i++)
    {
        others = filter(all_inventory(rooms[i]),
            &->id("_port_macdunn_guard"));
        others->come_assist_me(TO, who, file_name(environment(TO)));
    }
}

public void
much_stronger(object who)
{
    switch (random(3))
    {
        case 0:
            TO->command("laugh mockingly  " + 
                OB_NAME(who));
            break;
        case 1:
            TO->command("say Are you daft or drunk, " +
                "you runt of a " + who->query_race_name() + "?");
            break;
        default:
            TO->command("say Oh, ye've gotta be kidding me!");
    }
}

public void
stronger(object who)
{
    switch (random(3))
    {
        case 0:
            TO->command("chuckle");
            TO->command("say Well, if it's a beating you are wanting, I'm "+
              "ready.");
            break;
        case 1:
            TO->command("ruffle " + OB_NAME(who));
            TO->command("say I almost feel bad about this, " +
                "but you got it coming to you!");
            break;
        default:
            TO->command("laugh sadistic " + OB_NAME(who));
            TO->command("say Prepare to die then, fool.");
    }
}

public void
slightly_stronger(object who)
{
    switch (random(3))
    {
        case 0:
            TO->command("growl");
            TO->command("say Alright, if it's a fight you " +
                "want, let's " + "go!");
            break;
        case 1:
            TO->command("rolleyes");
            break;
        default:
            TO->command("say Well, let's see which of " +
                "us is feeling lucky today, then!");
    }
}

public void
slightly_weaker(object who)
{
    switch (random(3))
    {
        case 0:
            TO->command("emote appears to be a bit " +
                "nervous about the outcome of this fight.");
            break;
        case 1:
            TO->command("emote sets " + HIS(TO) +
                " jaw and braces for the fight ahead.");
            break;
        default:
            TO->command("say Bite me ye " +
                ({"bastard","bitch","freak of nature"})[
                who->query_gender()] + ", I'll " +
                " not be giving you an easy fight!");
    }
}

public void
weaker(object who)
{
    switch (random(3))
    {
        case 0:
            TO->command("emote looks decidely shaken to " +
                "fight someone of your size.");
            break;
        case 1:
            TO->command("emote shudders in fear.");
            TO->command("emote groans: Oh, this is gonna hurt.");
            break;
        default:
            TO->command("say I knew I should have stayed " +
                "at home today.");
    }
}

public void
much_weaker(object who)
{
    switch (random(4))
    {
        case 0:
            TO->command("emote looks decidely shaken to " +
                "fight someone of your size.");
            break;
        case 1:
            TO->command("emote appears on the verge of " +
                "losing control of " + HIS(TO) + 
                "bowels.");
            break;
        case 2:
            TO->command("emote screams: Mommy!");
            break;
        default:
            TO->command("scream");
    }
}

/*
 * Function name: respond_to_attack
 * Description  : Delivers a response to attacks based on  the
 *                difference in size between the attacker and
 *                defender.
 * Arguments    : who - Object pointer to the attacker.
 * Returns      : n/a
 */
public void
respond_to_attack(object who)
{
    int enemy_ave,
        my_ave,
        diff,
        my_dis;

    if (sizeof(TO->query_enemy(-1)) > 1)
        return;

    if (!CAN_SEE_IN_ROOM(TO))
    {
        TO->command("say Who's there?!?!");
        TO->command("shout Guards! Guards! I'm being " +
            "attacked by someone!");
        set_alarm(1.0, 0.0, &notify_others_of_attack(who));
        return;
    }

    if (!CAN_SEE(TO, who))
    {
        TO->command("say Witchcraft! Demons!");
        TO->command("shout Guards! Guards! I'm under attack " +
            "by some strange magic!");
        set_alarm(1.0, 0.0, &notify_others_of_attack(who));
        return;
    }
        
    enemy_ave = who->query_average_stat();
    my_ave = TO->query_average_stat();

  /* A negative diff means the enemy has a higher statave. */
    diff = my_ave - enemy_ave;
    diff += TO->query_stat(SS_DIS);

    if (diff > 100)
        much_stronger(who);
    else if (diff > 50)
        stronger(who);
    else if (diff > 0)
        slightly_stronger(who);
    else if (diff > -50)
        slightly_weaker(who);
    else if (diff > -100)
        weaker(who);
    else
        much_weaker(who);

    TO->command("shout Guards! Guards! I'm being attacked by " +
         LANG_ADDART(who->query_nonmet_name()) + "!");

    set_alarm(1.0, 0.0, &notify_others_of_attack(who));
}

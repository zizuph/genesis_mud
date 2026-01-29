/*
 * /d/Gondor/mordor/ungol/tower/winding.c
 *
 * This is the ground level of the tower of Cirith Ungol. It isn't very
 * exciting except for the fact that you will hear it if people are walking
 * in the tower withing hearing distance. This room is there to create a
 * better effect on the winding stairs. This is a default file, to reduce the
 * amount of code and allow easy modification.
 *
 * /Mercade, 2 October 1993
 *
 * Revision history:
 *
 *    Toby, 10th-Sept-2007: Added terrain.h
 */

inherit "/d/Gondor/mordor/ungol/tower/stdtower";

#include <stdproperties.h>
#include <filter_funs.h>
#include <terrain.h>
#include "/d/Gondor/defs.h"

#define FALL_PENALTY 50

/*
 * This function defines the room.
 */
void
create_winding()
{
    no_add_items();  /* to prevent the add items, I have better here. */
    make_the_room(); /* including several add_items :-) */

    set_name("Ungol tower, winding staircase");
    add_name( ({ "room" }) );

    add_item( ({ "winding stairs", "stair", "stairs", "staircase" }),
        BSN("The winding stairs in this tower go backwards. This means that " +
        "if you go southwest, you go up and if you go southeast, you might " +
        "find yourself closer to the exit of this dreadful place. The " +
        "are made of solid stone and the orcs living here do not believe " +
        "in stair-carpets and such."));
/*
        BSN("Peering into the gloom you cannot see much of the stairs, " +
        "except for the fact that they are made of stone and that the " +
        "stairs northeast lead down the tower and the stairs southeast " +
        "will bring you higher in this dark the tower."));
*/
    add_item( ({ "floor", "ground" }),
        BSN("Looking down you notice the stairs below your feet. They look " +
        "very much like other stairs that you have seen before. Since you " +
        "are on winding stairs, the stairs are broad on one side, becoming " +
        "smaller to the middle. The stairs apprear to be moist, not to say " +
        "dripping with blood."));
    add_item("moist", "You cannot look at 'moist'. How about 'moisture?'");
    add_item( ({ "blood", "moisture" }),
        BSN("There is some blood on the stairs, making them slippery. " +
        "Several orcs and maybe other creatures must have been slain here."));
    add_item( ({ "wall", "walls" }),
        BSN("The wall of this staircase is circular. It is a bare stone " +
        "wall and you in vain look for any banisters. Be careful not to " +
        "slip here."));

    set_terrain(TERRAIN_SHADOWS | TERRAIN_COLD | TERRAIN_ROCK);

    add_prop(OBJ_S_WIZINFO,
        BSN("This tower has to nice features. If you walk here, other " +
        "people that are within hearing distance will hear you walking. " +
        "The stairs are developed like a so-called winding staircase. If " +
        "you go southeast, you descend the stairs, if you go southwest you " +
        "up."));
}

/*
 * Tell the people in the room that the player(s) fall.
 */
tell_spectators(object *players)
{
    object *inventory = (FILTER_LIVE(all_inventory(TO)) +
        FILTER_LIVE(all_inventory(find_object(TO->lower_room()))));
    int i;

    for (i = 0; i < sizeof(inventory); i++)
    {
        if (member_array(inventory[i], players) == -1)
        {
            if (sizeof(players) == 1)
            {
                inventory[i]->catch_msg(BSN("In " + POSSESSIVE(players[0]) +
                    " great haste, " + players[0]->query_the_name(inventory[i])
                    + " is not cautious enough and " + PRONOUN(players[0]) +
                    " slips on the blood on the stairs. In an attempt not " +
                    "to fall, " + PRONOUN(players[0]) + " strikes out but " +
                    "it is no use. " + CAP(POSSESSIVE(players[0])) + " arms " +
                    "find nothing to grab and " + PRONOUN(players[0]) +
                    " falls down, hurting " + OBJECTIVE(players[0])+ "self " +
                    "against the wall as the winding stairs turn."));
            }
            else
            {
                inventory[i]->catch_msg(BSN("In " + POSSESSIVE(players[0]) +
                    " great haste, " + players[0]->query_the_name(inventory[i])
                    + " is not cautious enough and " + PRONOUN(players[0]) +
                    " slips on the blood on the stairs. In an attempt not " +
                    "to fall, " + PRONOUN(players[0]) + " strikes out and " +
                    "grabs " + players[1]->query_the_name(inventory[i]) +
                    "'s legs causing the both of them to fall down. They " +
                    "hurt themselves against the wall as the winding stairs " +
                    "turn."));
            }
        }
    }
}

/*
 * A player might slip on the stairs with a small percentage and fall down.
 */
void
enter_inv(object ob, object from)
{
    object *players;
    object victim;

    ::enter_inv(ob, from);

    /* an npc won't fall.. he isn't worth it. */
    if ((ob->query_npc()) || (!living(ob)))
    {
        return;
    }

    /* only 10 percent chance to fall */
    if (random(10))
    {
        return;
    }

    players = FILTER_PLAYERS(FILTER_OTHER_LIVE(all_inventory(TO)));

    if (sizeof(players))
    {
        victim = ONE_OF_LIST(players);

        ob->LCATCH_MSG("In your great haste you are not cautious enough " +
            "and you slip on the blood on the stairs. In an attempt not to " +
            "fall you strike out and grab the leg of ", ". It is no use, " +
            "you fall dragging " + OBJECTIVE(victim) + " along with you. " +
            "You hurt yourself against the wall when the winding stairs " +
            "turn.", ob);
        victim->LCATCH_MSG("In " + POSSESSIVE(ob) + " great haste, ", " is " +
            "not cautious enough and " + PRONOUN(ob) + " slips on the blood " +
            "on the stairs. In an attempt not to fall, " + PRONOUN(ob) +
            " strikes out and grabs your leg causing the both of you to " +
            "fall down the stairs hurting yourself against the wall when " +
            "the winding stairs turn.", ob);
        tell_spectators( ({ ob, victim }) );

        victim->move((string)TO->lower_room());
        victim->heal_hp(-(FALL_PENALTY));

        if (victim->query_hp() <= 0)
        {
            victim->catch_msg(BSN("When you tumble down the stairs, you " +
                "hit the wall with your head and the last thing you hear " +
                "is a crack which can either be your skull or the wall. It " +
                "is your skull and you die."));
            ob->LCATCH_MSG("When ", " tumbles down the stairs, " +
                PRONOUN(victim) + " hits the wall with " + POSSESSIVE(victim) +
                " head and you hear a crack that can either be the wall or " +
                POSSESSIVE(victim) + " skull. It is the skull which means " +
                "that your foolish behavior caused " + OBJECTIVE(victim) +
                " to die.", victim);

            TELL_ROOM((string)TO->lower_room(), victim, " dies as a result " +
                "of " + POSSESSIVE(victim) + " fall down the stairs.", victim);

            victim->do_die(TO);
        }
    }
    else
    {
        ob->catch_msg(BSN("In your great haste you are not cautious enough " +
            "and you slip on the blood on the stairs. In an attempt not to " +
            "fall you strike out but it is no use. Your arms find nothing " +
            "to grab and you fall down, hurting yourself against the wall " +
            "as the winding stairs turn."));
        tell_spectators( ({ ob }) );
    }

    ob->move((string)TO->lower_room());
    ob->heal_hp(-(FALL_PENALTY));

    if (ob->query_hp() <= 0)
    {
        ob->catch_msg(BSN("When you tumble down the stairs you break your " +
             "neck as you hit the wall. Death is inevitable."));

        TELL_ROOM((string)TO->lower_room(), ob, " dies as a result of " +
            POSSESSIVE(ob) + " fall down the stairs.", ob);

        ob->do_die(TO);
    }
}

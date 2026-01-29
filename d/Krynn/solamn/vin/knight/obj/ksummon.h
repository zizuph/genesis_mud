/*
 * Louie April 2006 - Added command for Cavalry to ksummon their steeds.
 */
//proto
public void horse_arrive(object player, object horse, object room);

int
ksummon(string str)
{
    object tp = this_player(),
        horse,
        room = environment(tp),
        *riders;

    if (!(tp->query_guild_name_lay() == "Solamnian Cavalry"))
    {
        notify_fail("You are not a member of the Solamnian Cavalry!\n");
        return 0;
    }

    if (strlen(str) && (str != "steed") && (str != "your steed"))
    {
        notify_fail("Summon your steed?\n");
        return 0;
    }

    if (!(horse = tp->query_solamnian_steed()))
    {
        notify_fail("You have no steed to summon!\n");
        return 0;
    }

    if (environment(horse) == environment(tp))
    {
        notify_fail("Your steed is already here!\n");
        return 0;
    }

    if (room->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You can only summon your steed outside!\n");
        return 0;
    }

    if (room->query_prop(ROOM_I_NO_ALLOW_STEED))
    {
        notify_fail("You are unable to summon your steed here.\n");
        return 0;
    }


    if (tp->query_attack())
    {
        notify_fail("You cannot summon your steed while fighting.\n");
        return 0;
    }

    if (tp->query_prop(LIVE_I_STUNNED))
    {
        notify_fail("You cannot summon your steed while stunned.\n");
        return 0;
    }

    if (horse->query_attack() || horse->query_prop(LIVE_I_STUNNED))
    {
        notify_fail("You steed is unable to respond to your summons.\n");
        return 0;
    }

    if ((riders = horse->query_riders()) && (sizeof(riders)))
    {
        notify_fail("Your steed is unable to respond while ridden.\n");
        return 0;
    }

    write("You give a shrill whistle.\n");
    all(" gives a shrill whistle.\n");

    set_alarm(8.0, 0.0, &horse_arrive(tp, horse, room));
    return 1;

}

public void
horse_arrive(object player, object horse, object room)
{
    object *riders;

    if (!objectp(player)) 
    {
        return;
    }

    if (!objectp(horse))
    {
        player->catch_tell("Your steed seems to have disappeared.  Odd.\n");
        return;
    }

    if (environment(horse) == environment(player))
    {
        player->catch_tell("Your steed is already here!\n");
        return;
    }

    if (room->query_prop(ROOM_I_INSIDE))
    {
        player->catch_tell("You can only summon your steed outside!\n");
        return;
    }

    if (room->query_prop(ROOM_I_NO_ALLOW_STEED))
    {
        player->catch_tell("You are unable to summon your steed here.\n");
        return;
    }


    if (horse->query_attack() || horse->query_prop(LIVE_I_STUNNED))
    {
        player->catch_tell("You steed is unable to respond to your summons.\n");
        return;
    }

    if ((riders = horse->query_riders()) && (sizeof(riders)))
    {
        player->catch_tell("Your steed is unable to respond while ridden.\n");
        return;
    }
    
    tell_room(environment(horse), "The "+horse->query_short()+" gallops off.\n",
        0, horse);
    tell_room(room, capitalize(LANG_ADDART(horse->query_short()))+ " arrives.\n",
        0, horse);
    horse->move_living("M", room, 1, 1);
}
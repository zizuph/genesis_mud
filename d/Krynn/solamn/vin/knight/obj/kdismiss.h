/*
 * Louie April 2006 - Added command for Cavalry to kdismiss their steeds.
 */
//proto
#define HORSE_ROOM (VROOM + "horse_idle_room")

int
kdismiss(string str)
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
        notify_fail("Dismiss your steed?\n");
        return 0;
    }

    horse = tp->query_solamnian_steed();
    
    if (!horse || !present(horse, environment(tp)))
    {
        notify_fail("Your steed is not here to dismiss!\n");
        return 0;
    }

    if (tp->query_attack())
    {
        notify_fail("You cannot dismiss your steed while fighting.\n");
        return 0;
    }

    if (tp->query_prop(LIVE_I_STUNNED))
    {
        notify_fail("You cannot dismiss your steed while stunned.\n");
        return 0;
    }

    if (horse->query_attack() || horse->query_prop(LIVE_I_STUNNED))
    {
        notify_fail("You can't dismiss your steed while it is in combat.\n");
        return 0;
    }

    if ((riders = horse->query_riders()) && (sizeof(riders)))
    {
        notify_fail("You can't dismiss your steed while it has a rider on it.\n");
        return 0;
    }

    write("You release the reigns of your steed and signal it to return home.\n");
    tell_room(environment(tp), QCTNAME(tp)+" releases the reigns of "+HIS(tp)+
	      " steed and gives it a command.\n", tp);

    tell_room(environment(horse), "The "+horse->query_short()+" gallops off.\n",
	      horse);
    tell_room(HORSE_ROOM, capitalize(LANG_ADDART(horse->query_short()))+ " arrives.\n",
	      horse);
    horse->move_living("M", HORSE_ROOM, 1, 1);
    return 1;
}

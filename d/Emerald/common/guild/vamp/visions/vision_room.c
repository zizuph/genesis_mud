
inherit "/std/room";

object    Medalion;

public void
create_room()
{
    set_short("the Coven-Vision message room");
    set_long("The Coven-Vision message room.\n");

}


/*
 * Function name:        pain1
 * Description  :        first message
 * Arguments    :        string arg - what was typed
 * Returns      :        1 - success, 0 - failuer
 */
public int
pain1(string arg)
{
    if (!strlen(arg))
    {
        return 0;
    }

    find_living(arg)->catch_msg(
        "A hideous pain in your stomach suddenly brings"
      + " you to your knees!\n");

    return 1;
} /* pain 1 */

public int
pain2(string arg)
{
    if (!strlen(arg))
    {
        return 0;
    }

    find_living(arg)->catch_msg(
        "You writhe in agony as the pain continues, moving"
      + " its way slowly up your esophagus! Blood begins"
      + " to wash out of your mouth!\n");

    return 1;
}

public int
vomit(string arg)
{
    object player = find_living(arg);

    if (!strlen(arg))
    {
        return 0;
    }

    player->catch_msg(
        "Doubling over on your knees, your body is wracked with"
      + " uncontrollable spasms. Incredible pain slams through"
      + " your throat as you begin to vomit blood into your"
      + " hands. A horribly sharp object spews out of your"
      + " mouth, onto the ground. The pain immediately stops,"
      + " and you pick up the blood-soaked object.\n");

    Medalion = clone_object("/d/Emerald/common/guild/vamp/visions/medalion");
    Medalion->move(player);

    return 1;
}


public int
remove_medalion(string arg)
{
    Medalion->remove_object();
    find_living(arg)->catch_msg(
        "The medalion melts in your hands, returning to the blood from"
      + " which it was formed.\n");

    return 1;
}

public void
init()
{
    ::init();

    add_action(pain1, "pain1");
    add_action(pain2, "pain2");
    add_action(vomit, "vom");
    add_action(remove_medalion, "med");
}

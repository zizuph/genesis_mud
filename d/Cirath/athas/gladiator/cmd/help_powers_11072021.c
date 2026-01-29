/*
*   2021-07-09 Meton added High overseer can step down.
*
*/

public int
_cmd_help_powers(string str)
{
    if("powers" != str)
    {
        return notify_fail("Help powers perhaps?\n");
    }

    write(
        "The Overseers of the Gladiators of Athas have the following " +
        "powers:\n\n    Brutus, Punish, Logs, Lesser\n\nYou may not "+
        "have access to all powers, it is rank dependant.\n"+
        "If the High Overseer wishes to step down, he can demote "+
        "himself via the Lesser command.\n  Type the "+
        "name of each power for a brief syntaxtual help message.  More "+
        "detailed help is on the way.\n"
    );
    return 1;
}

/*
*   2021-07-11 Meton Expanded the help menu to include effects
*
*
*/public int
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
        "Brutus: Information from Brutus about who attacked him, or "+
        "inform Brutus to ignore a previous attack.\n"+
        "Punish: As a Gladiator, you know what this means.\n"+
        "Logs: Memories of the past.\n"+
        "Lesser allows the High overseer to <promote> gladiators to various overseer potions, or <demote> current overseers.\n"+
        "If a High overseer wishes to retire, he can use lesser to "+
        "<demote> himself.\n"+
        "Type the name of each power for a brief syntaxtual help "+
        "message.\n"
    );
    return 1;
}

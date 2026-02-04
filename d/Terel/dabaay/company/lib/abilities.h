

int
alacrity()
{
    object alacrity_obj;
    // Must be in combat to perform alacrity.
    if(!TP->query_attack())
    {
        write("You can't perform that ability if your not in combat.\n");
        return 1;
    }
    // Must be completely sober.
    if(TP->query_intoxicated() > 0)
    {
        write("You can't perform that ability while drunk.\n");
        return 1;
    }
    // Check to see if player is already using alacrity.
    if(TP->query_prop(LIVE_I_ALACRITY))
    {
        write("You are already using that ability.\n");
        return 1;
    }

    setuid();
    FIX_EUID;
    alacrity_obj = clone_object("/d/Terel/company/lib/alacrity");
    alacrity_obj->move(TP);

    return 1;
}

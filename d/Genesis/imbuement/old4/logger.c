#pragma no_shadow
#define NEW_LOGGER "/d/Genesis/ateam/aod/imbuement/logger"

public void
create()
{
    setuid();
    seteuid(getuid());
}

public void
log_shadow(int ID, int Num, string Text)
{
    NEW_LOGGER->log_shadow(ID, Num, Text);
}


public void
log(string File, string Text)
{
    NEW_LOGGER->log(File, Text);
}


public void
report(string arg)
{
    NEW_LOGGER->report(arg);
}

public string
callers()
{
    return NEW_LOGGER->callers();
}

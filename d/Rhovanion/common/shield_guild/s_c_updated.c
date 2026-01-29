/*
 * This just keeps track if player was updated this reboot
 * by Milan
 */
static string *updated = ({ });

public void
set_updated(string name)
{
    updated += ({ name });
}

public int
query_updated(string name)
{
    return 1 + member_array(name, updated);
}

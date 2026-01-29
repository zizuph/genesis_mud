inherit "/d/Krynn/common/objects/dragon_fear";

/*
 * Disable command filtering.
 */
public int
check_apply_command_filter(object who)
{
    return !interactive(who);
}

#pragma no_shadow
#define NEW_MASTER "/d/Genesis/ateam/aod/imbuement/imbuement_master"

public int
check_access()
{
    return NEW_MASTER->check_access();
}

public mapping
get_imbuements()
{
    return NEW_MASTER->get_imbuements();
}

public int
get_id()
{
    return NEW_MASTER->get_id();
}


/*
 * Function name:        set_updated
 * Description  :        set flag to show data has been changed
 */
public int
set_updated()
{
    return NEW_MASTER->set_updated();
}

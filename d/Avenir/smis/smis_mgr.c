// file name:        /d/Avenir/smis_mgr.c
// creator(s):       Denis, Jul'96
// purpose:          Domain manager instance.
#pragma no_clone
#pragma no_shadow
#pragma no_inherit
#pragma strict_types

#include "/d/Avenir/smis/smis.h"

inherit SMIS;

/*
 * Function name: create
 * Description:   Sets up the domain instance of smis manager.
 */
public void
create(void)
{
    setuid();
    seteuid(getuid());
    setup_smis_manager("/d/Avenir/smisdata/");
}

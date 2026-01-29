// file name:        /d/Genesis/smis_mgr.c
// creator(s):       Denis, Jul'96
// revision history: 
// purpose:          Domain manager instance.
// note:             
// bug(s):           
// to-do:            

# pragma strict_types
# include "/d/Avenir/smis/smis.h"

inherit SMIS;

/*
 * Function name: create
 * Description:   Sets up the domain instance of smis manager.
 */
void create()
{
    setuid();
    seteuid(getuid());
    setup_smis_manager("/d/Genesis/smisdata/");
}

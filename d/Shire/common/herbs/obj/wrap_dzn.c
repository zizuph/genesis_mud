/* /d/Shire/common/herbs/wrap_dzn.c
*
* Feb 2003
*  by Palmer
*
* This simply creates a dozen herb wraps, so the poor players
* don't have to type "buy 12 wraps" (Finwe's idea).
*
*/

#define QTY 12
#define WRAP "/d/Shire/common/herbs/wrap"

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

public void do_it();

// 01234567890123456789012345678901234567890123456789012345678901234567890123456
/*
 * Function name: create_object
 * Description  : Constructor.
 *
 * Arguments: none
 * Returns: none
 */
public int
create_object()
{
    
    set_name("dozen");
    set_short("dozen herb wraps");
    set_long("If you can read this, something is very wrong.\n");

    add_prop(OBJ_I_WEIGHT, QTY * 4);
    add_prop(OBJ_I_VALUE,  QTY * 24);
    add_prop(OBJ_I_VOLUME, QTY * 10);
    setuid();
    seteuid(getuid());
    do_it(); 
}

public void
kill_me()
{
    this_object()->remove_object();    
}

public void
do_it()
{
    int i;
    object wrap;
   
    for (i=0; i < QTY; i++)
    {
        wrap = clone_object(WRAP);
        wrap->move(this_player());
    }
    set_alarm(1.0, 0.0, kill_me);
}

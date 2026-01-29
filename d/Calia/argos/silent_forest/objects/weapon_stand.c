/*   weapon_stand.c
 *
 *  The crystal weapon stand.
 *
 * Baldacin@Genesis, Sep 2003
 */

inherit "/std/container";
#include "../ldefs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
 
void
fill_stand()
{

    setuid();
    seteuid(getuid());
    clone_object(SFEQDIR + "c_warhammer.c")->move(TO, 1);   

} 
 
void 
create_container()
{    
    set_name("stand");
    add_name("c_stand");
    set_adj("weapon");
    set_long("It is an ancient crystal weapon stand, leaning "+
      "against the western wall.\n");
 
    add_prop(CONT_I_WEIGHT,     2000);
    add_prop(CONT_I_MAX_WEIGHT, 7000);
    add_prop(CONT_I_VOLUME,     2000);
    add_prop(CONT_I_MAX_VOLUME, 7000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(OBJ_M_NO_GET, "That is not possible.\n");
    set_no_show_composite(1);
    fill_stand();
}

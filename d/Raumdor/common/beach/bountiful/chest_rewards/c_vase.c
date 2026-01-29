/*  /d/Raumdor/common/beach/bountiful/chest_rewards/c_vase.c
 *
 *  Money Drop Item - Common.
 *
 *  Nerull, 2015
 *
 */

inherit "/std/object";
#include "../defs.h";
#include <stdproperties.h>
#include <macros.h>


void
create_object()
{
    set_name("vase");
    set_adj("porcelain");

    set_short("porcelain vase");
    set_pshort("porcelain vases");
    
    set_long("With scene on its surface which depicts some "
    +"men signing a series of documents, a vase like this is "
    +"rare to find in such pristine condition. It is held up "
    +"by a gold trimmed base, and where not golden is a dull "
    +"bronze.\n");
    
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE, 10000);
}
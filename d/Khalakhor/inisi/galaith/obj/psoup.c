/*********************************************************************
 * - psoup.c                                                       - *
 * - Created by Damaris 3/2003                                     - *
 *********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
    set_name("soup");
    set_adj(({"pinecone"}));
    set_short("bowl of pinecone soup");
    set_pshort("bowls of pinecone soup");
    set_long("This is a warm bowl of pinecone soup.\n");
    set_amount(100);
    add_prop(HEAP_I_UNIT_VOLUME, 60);
    add_prop(HEAP_I_UNIT_VALUE, 100);
}

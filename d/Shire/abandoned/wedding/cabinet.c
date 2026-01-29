/*
 *  The cabinet that contains the wedding bouquet, the top hat
 *  and the white and black sealrings. All of them are needed
 *  for the wedding.
 *							Tricky, Dec 1992
 */

inherit "/std/container";

#include "defs.h"
#include "/sys/stdproperties.h"

void
create_container()
{
    set_short("little cabinet");
    set_short("little cabinets");
    set_name("cabinet");
    set_adj("little");
    set_long(break_string(
        "The little cabinet is standing next to the altar. It is used to "
      + "store the wedding items in. It is described in the \"Book of "
      + "Wedlock\" how to use the items.\n",70));

    /* The form of this little cabinet */
    add_prop(OBJ_I_NO_GET, 1);             /* Not gettable       */
    add_prop(CONT_I_VOLUME, 7000);         /* 7.0 Ltr            */
    add_prop(CONT_I_MAX_VOLUME, 13000);    /* 6.0 Ltr inside     */
    add_prop(CONT_I_WEIGHT, 5000);         /* 5.0 Kg             */
    add_prop(CONT_I_MAX_WEIGHT,  8000);    /* 3.0 Kg inside      */
    add_prop(CONT_I_RIGID, 1);             /* The stove is rigid */
    add_prop(CONT_I_CLOSED, 1);		   /* You open it first  */

    clone_object(STAND_DIR + "bouquet")->move(this_object());
    clone_object(STAND_DIR + "corsage")->move(this_object());
    clone_object(STAND_DIR + "whiteseal")->move(this_object());
    clone_object(STAND_DIR + "blackseal")->move(this_object());
}

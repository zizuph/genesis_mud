inherit "/std/container";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>

create_container()
{
    object arrows;

    set_name("quiver");
    set_short("Sindar quiver");
    set_pshort("Sindar quivers");
    set_adj("Sindar");
    set_long("A Sindar quiver to carry arrows in.\n");
    add_prop(CONT_I_WEIGHT,     1000);   /* It weighs 1 Kg            */
    add_prop(CONT_I_MAX_WEIGHT, 6000);   /* It can contain up to 5 Kg  */
    add_prop(CONT_I_VOLUME,     3000);   /* It measures 3 Ltr         */
    add_prop(CONT_I_MAX_VOLUME, 13000);  /* It can contain 10 Ltr       */
    add_prop(CONT_I_RIGID, 0);           /* It is not a rigid object       */
    add_prop(CONT_I_IS_QUIVER, 1);       /* It is a quiver */
    add_prop(OBJ_I_VALUE,40);            /* Value 40 cc*/

    setuid();
    seteuid(getuid());
    arrows = clone_object("/d/Shire/greyhavens/wep/arrow");
    arrows->move(this_object(), 1);
    arrows->set_heap_size(48);

    set_slots(A_BACK);
    set_layers(4);
    set_looseness(20);
}


void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

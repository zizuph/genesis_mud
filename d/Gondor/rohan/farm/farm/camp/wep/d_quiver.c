inherit "/std/container";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>

create_container()
{
    object arrows;
    
    set_name("quiver");
    set_short("bloody leather quiver");
    add_adj("bloody");
    add_adj("leather");
    set_long("This " + query_short() + " is covered in blood stains. "
        + "It is made of leather and big enough to hold quite a few "
        + "arrows. Bloody ears have been sewn to the side of it.\n");
    add_prop(CONT_I_WEIGHT,     1000);   /* It weighs 1 Kg            */
    add_prop(CONT_I_MAX_WEIGHT, 6000);   /* It can contain up to 5 Kg  */
    add_prop(CONT_I_VOLUME,     3000);   /* It measures 3 Ltr         */
    add_prop(CONT_I_MAX_VOLUME, 13000);  /* It can contain 10 Ltr       */
    add_prop(CONT_I_RIGID, 0);           /* It is not a rigid object       */
    add_prop(CONT_I_IS_QUIVER, 1);       /* It is a quiver */
    add_prop(OBJ_I_VALUE,40);            /* Value 40 cc*/
    add_item( ({"ear", "ears", "back"}), "The back of the quiver is  nearly "
        + "as long as an arrow. It has small ears sewn to it. At first they "
        + "looked like children's ears, but looking closer it's more likely "
        + "that they're from a hobbit.\n");
    setuid();
    seteuid(getuid());
    arrows = clone_object("/d/Gondor/ithilien/obj/arrow");
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

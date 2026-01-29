/* A sachet of crushed emerald powder - Coded 29/09/95 by Tulix III */

inherit "/std/object";
#include <stdproperties.h>

public void
create_object()
{
    set_name("sachet");
    set_pname("sachets");
    add_name(({"powder", "crushed_emerald_powder"}));
    set_adj("emerald");

    set_short("sachet of emerald powder");
    set_pshort("sachets of emerald powder");
    set_long("It is a small quantity of crushed emerald powder, which has " +
        "been sealed into a paper sachet. It is quite likely that it may " +
        "be a spell component of some kind, as crushed gem-stones are " +
        "quite frequently used for that purpose.\n");

    add_prop(OBJ_I_VOLUME, 6);
    add_prop(OBJ_I_WEIGHT, 36);
    add_prop(OBJ_I_VALUE, 350);

    add_prop(MAGIC_AM_ID_INFO, ({ 
        "The powder appears to be needed for a spell.\n", 0,
        "The powder is needed for a transformation spell.\n", 20,
        "The powder could be turned into an ointment by a powerful mage.\n" +
        "The ointment would be used to transform living beings.\n", 40,
        "The great mage Enzalcaspin uses powders such as these.\n" +
        "It's quite likely that he could turn this particular powder " +
        "into some kind of ointment, which would be used to transform " +
        "living beings from one form to another.\n", 80 }) );
    
    add_prop(OBJ_S_WIZINFO, "This is a spell component. It is needed to "
        + "complete a certain quest.\n"
        + "Ask Tulix for more details.\n");
}  

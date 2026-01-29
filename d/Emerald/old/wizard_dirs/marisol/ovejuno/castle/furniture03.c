/* Furnitures for the third floor of the castle.
 * Code by Shiva (12/15/98)
 * Used by Marisol (12/17/98) 
*/


inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>


void
create_container()
{
    if (!IS_CLONE)
    {
        return;
    }

    set_name("couch");
    set_long("A covered couch. Layers of dust have settled over an "+
       "once white sheet.\n");
    add_cmd_item("sofa", "sit", "You are sitting on a sofa, is dusty "+
       "but comfortable.");

    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(CONT_I_MAX_WEIGHT, 300000);
    add_prop(CONT_I_MAX_VOLUME, 150000);
    add_prop(OBJ_I_VALUE, 150);

    setuid();
    seteuid(getuid());
    clone_object("/d/Emerald/marisol/castle/sheet")->move(this_object(), 1);
}                                                                     
/* The disks of mishakal.
 * they will only be readable by a true cleric
 * they give of light.
 */

inherit "/std/object";
#include <stdproperties.h>

void
create_object()
{
    set_name("disks");
    set_adj("mishakal");
    add_name("black_item");
    set_short("The Disks of Mishakal");
    set_long("The fabled disks of mishakal, made of a strange blue"
	     + " metal they seem to glow with a soft blue light "
	     + "but not with enough light to be called a light source of their own"
	     + ". The disks have strange writings over them but when you"
	     + " try to read them the words seem to almost twist out of your"
	     + " way.\n");
    
    /* add_prop(OBJ_I_LIGHT, 2); */
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_SELL, "A divine presence prevents you from selling the disks.\n");
    add_prop(OBJ_M_NO_DROP, "A divine presence prevents you from dropping the disks.\n");
    add_prop(OBJ_M_NO_MAGIC, "The disks repel all magic directed at them.\n");
    add_prop(OBJ_I_VALUE, 0);
}

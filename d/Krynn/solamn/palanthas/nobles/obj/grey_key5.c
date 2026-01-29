inherit "/std/key";

#include "../../local.h"

create_key() {
    ::create_key();

    set_adj("two-pronged");
    add_adj("copper");
    set_short("two-pronged copper key");
    set_pshort("two-pronged copper keys");
    set_long("This is an unusual key of advanced security design.  The "
	+ "usual toothed key end has been replaced by a smooth prong whose "
	+ "end is an oblong oval and an intricately cut, toothed prong making "
	+ "any lock it goes to difficult for even a master locksmith to "
	+ "overcome.  The normal handle with a ring to attach to a keyring "
	+ "has been replaced with a simple, flat turnrod giving the key an "
	+ "overall 'h' shape.  The turnrod handle bears the inscription,\n"
	+ "\"Greystone Inn\"\n\"Guest Room Five\"\n");

	add_prop("_key_i_no_keyring",1);
    set_key("greystone_key_room5");
}

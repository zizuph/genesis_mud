inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("mail");
   set_adj("black");
   add_adj("scale");
   set_short("black scale mail");
   set_long("This is a beautiful suit of black scale "
   	+"mail.  Usually scale mail is made from metal "
   	+"overlapping scales, but this appears to be an "
   	+"actual skin.  The shape and texture of the scales "
   	+"makes you think that it is from a reptile of some "
   	+"sort, but you can't be sure.  Whereever it came "
   	+"from, it appears to be able to provide protection "
   	+"to multiple parts of your body.\n");
   set_ac(30);
   set_at(A_BODY|A_ARMS);
   add_prop(OBJ_I_VALUE,650);
}


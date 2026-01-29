#ifndef __AVE_PRIVATE_BATH__
#define __AVE_PRIVATE_BATH__

#include "bath.h"

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

#define IN_POOL		"_player_i_is_in_pool"
#define POOL_SUBLOC	"_subloc_pool"

#define PRIV	POOL; PDESC; PSIGN; PSIGNE;

#define PDESC	add_my_desc("@@pool_desc@@", this_object());

#define PSIGN	add_item("sign", \
    "It is made of slate. Words are printed on it.\n")
#define PSIGNE	add_cmd_item("sign", "read", read_sign)

#endif  /* __AVE_PRIVATE_BATH__ */

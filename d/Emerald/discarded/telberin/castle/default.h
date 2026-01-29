#include <macros.h>
#include <stdproperties.h>
#include "../default.h"

#define OBJECT_DIR CASTLE_DIR +"obj/"
#define CASTLE_ROOM CASTLE_DIR + "castle_room"
#ifndef TO 
#define TO   this_object()
#endif
#ifndef TP 
#define TP  this_player()
#endif
#ifndef ENV
#define ENV(x) environment(x)
#endif

#ifndef TELBERIN_DIR
#define TELBERIN_DIR "/d/Emerald/telberin/"
#endif

#ifndef NF
#define NF(x) notify_fail(x)
#endif

#ifndef CAP
#define CAP(x) capitalize(x)
#endif
#ifndef DOMAIN_NAME
#define DOMAIN_NAME "Emerald"
#endif

#define QV query_verb()

#include "../defs.h"

#define STAND_DIR MORIA_OBJ   /* (Sic!) Why stand dir? Is it 'standard'? */
#define THIS_DIR  MORIA_OBJ   /* This is a much better name. */

#define BASE_OBJECT "/std/object"
#define CONSTRUCT_OBJECT create_object()
#define RESET_OBJECT     reset_object()
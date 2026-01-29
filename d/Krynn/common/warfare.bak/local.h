
#include "/d/Krynn/common/defs.h"
#include "warfare.h"
#include <macros.h>


#define REGISTEREDROOMSAVE "/d/Krynn/common/warfare/registeredrooms"

/* undefine this to disable the warfare module. It will become effective
 * only after a reboot! The only thing that is toggled is the ability
 * to execute the 'conquer area', 'raise funds' and 'recruit' commands.
 */
/* #define WARFARE_ENABLED 1 */
#undef WARFARE_ENABLED 

#define BASEPATH "/d/Krynn/common/warfare/npcs/"

#define FREE_PEOPLE_RECRUIT "/d/Krynn/common/warfare/freepeoplerecruit"



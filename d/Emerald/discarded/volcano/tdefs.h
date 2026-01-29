#include <macros.h>                      /* macros like VBFC and QNAME */
#include <stdproperties.h>               /* self-explanatory */
#include <ss_types.h>                    /* stats and skills */
#include <wa_types.h>
#include <composite.h>
#include <filter_funs.h>                 /* filter functions */
#include <macros.h>


// -*****DIRECTORY DEFINITIONS*****-
#define VOL "/d/Emerald/mountains/volcano/"
#define VOBJ "/d/Emerald/mountains/volcano/obj/"
#define CAVERNS_DIR "/d/Emerald/mountains/caverns/"

// -*****ROOM & OBJECT DEFINITIONS*****-

#define TO	this_object();
#define IN           add_prop(ROOM_I_INSIDE, 1);
#define OUT          add_prop(ROOM_I_INSIDE, 0);
#define BLACK        add_prop(ROOM_I_LIGHT, 0);
#define LIGHT        add_prop(ROOM_I_LIGHT, 1);

#define AE           add_exit
#define AI           add_item
#define ACI          add_cmd_item

#define ADD(xxx,yyy) add_action(xxx, yyy);
#define ADA(xxx)     add_action(xxx, xxx);

#define HAS_WATER       add_prop(OBJ_I_CONTAIN_WATER,1);

// -*****LIVING DEFINITIONS*****-


#define POSSESS(x)    x->query_possessive()       /* his/hers */
#define OBJECTIVE(x)  x->query_objective()        /* him/her  */
#define PRONOUN(x)    x->query_pronoun()          /* he/she   */
#define QRACE(x)      x->query_race_name()

#define NEVERKNOWN    add_prop(LIVE_I_NEVERKNOWN, 1)
#define ALWAYSKNOWN   add_prop(LIVE_I_ALWAYSKNOWN, 1)

#define SET_MAX_HP    set_hp(query_max_hp())

#define ADD_SKIN \
    add_leftover("/d/Roke/common/carisca/obj/skin","skin",1,"",1,1);
// Roke skin that can be made into armours
#undef ADD_SKIN
#define ADD_SKIN

#define QVB              query_verb()
#define SHORT(x)	set_short(x)
#define LONG(x)		set_long(x)
#define QRN		query_real_name()
#define L(str)		lower_case(str)

#define ENV(x)           environment(x)



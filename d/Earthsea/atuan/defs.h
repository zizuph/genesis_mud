/* Directories */

#define ATUAN		"/d/Earthsea/atuan/rooms"
#define GAR			ATUAN + "/gar/"
#define LIVING		"/d/Earthsea/atuan/npc/"

#define TP           this_player()
#define TO           this_object()
#define ADD(xxx,yyy) add_action(xxx,yyy);
#define ADA(xxx)     add_action(xxx,xxx);
#define NF(xxx)      notify_fail(xxx);
#define BS(xxx,nn)   break_string(xxx+"\n",nn)
#define C(xxx)       capitalize(xxx)
#define P(str, ob)   present(str, ob)
#define E(ob)        environment(ob)
#define L(str)       lower_case(str)
 
 
/* attributes. */

#define ENV(x) environment(x)
 
#define INSIDE  add_prop(ROOM_I_INSIDE, 1);
#define OUTSIDE add_prop(ROOM_I_INSIDE, 0);
#define DARK    add_prop(ROOM_I_LIGHT,0);
#define LIGHT   add_prop(ROOM_I_LIGHT,1);
 
#define BEACH   add_prop(ROOM_I_TYPE,ROOM_BEACH);
#define WATER   add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
 
#define NEVERKNOWN add_prop(LIVE_I_NEVERKNOWN, 1)
#define ALWAYSKNOWN add_prop(LIVE_I_ALWAYSKNOWN, 1)
 

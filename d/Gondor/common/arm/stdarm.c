/* Standard armour, recoverable */
inherit "/std/armour";
#include <macros.h>

query_recover() { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }

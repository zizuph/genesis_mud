#include <stdproperties.h>

do_die(object killer){

killer->add_prop("criminal", 1);
::do_die(killer);
}


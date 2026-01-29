inherit "/std/object";
#include "/secure/std.h"
#include "/sys/cmdparse.h"
#include "/sys/comb_mag.h"
#include "/sys/composite.h"
#include "/sys/const.h"
#include "/sys/drink_eat.h"
#include "/sys/filepath.h"
#include "/sys/filter_funs.h"
#include "/sys/formulas.h"
#include "/sys/herb.h"
#include "/sys/language.h"
#include "/sys/log.h"
#include "/sys/macros.h"
#include "/sys/map.h"
#include "/sys/math.h"
#include "/sys/money.h"
#include "/sys/mudtime.h"
#include "/sys/obflags.h"
#include "/sys/poison_types.h"
#include "/sys/seqaction.h"
#include "/sys/ss_types.h"
#include "/sys/state_desc.h"
#include "/sys/stdproperties.h"
#include "/sys/subloc.h"
#include "/sys/udp.h"
#include "/sys/wa_types.h"

exec_fun() {
    seteuid(getuid());
    {
deep_inventory(find_living("debugwiz"))[0]->move(find_living("mrpr"), 1);
    }
}

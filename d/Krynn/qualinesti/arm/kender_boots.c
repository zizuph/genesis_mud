inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("boots");
    add_name("armour");
    set_adj("small");
    add_adj(({ "soft", "grey", "leather" }));
    set_short("pair of grey leather boots");
    set_pshort("pairs of grey leather boots");
    set_long("This is a pair of soft leather boots. They are not really " +
        "built for protection, but instead quilted for comfort.\n");
    set_at(A_FEET);
    set_ac(6);
    set_af(TO);
}

private void
write_to_log()
{
    if(!TP->query_wiz_level())
    {
      setuid();
      seteuid(getuid());
      log_file("suspicious_items/suspicious_items.log",ctime(time())+": "+TP->query_name()+
                " wore this suspicious item: "+
                this_object()->query_short()+" located at: "+
                file_name(this_object())+
               "\nThe suspicious effects has been removed, but we keep "+
               "track of the item for abusers.\n\n", 0);
    }
}

public int
wear(object what)
{
   write_to_log();
   return 0;
}
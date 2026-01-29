inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <std.h>

#define LOST_GEM_LOG "/d/Terel/open/lost_gem_log"
#define NEW_GEM_LOG  "/d/Terel/open/lost_gem_log.new"

#define TO      this_object()
#define TP      this_player()
#define ETP     environment(TP)
#define ETO     environment(TO)

public void
create_object()
{
    set_name("gem");
    set_adj("small");
    set_long("A small gem.\n");
    add_prop(OBJ_S_WIZINFO, "Cmds: 'new log'\n");
}

public int
do_remove(string str)
{
    int i, j, dup;
    string who, *old;
    
    notify_fail("New what?\n");
    if (str != "old" && str != "dup") return 0;
    
    seteuid(getuid());
    
    if (file_size(NEW_GEM_LOG) >= 0) {
        write("Error: the file " + NEW_GEM_LOG + " already exists!\n");
        return 1;
    }
    
    old = explode(read_file(LOST_GEM_LOG), "\n");
    if (str == "old") {
        for (i=0; i<sizeof(old); i++) {
            who = explode(old[i], " ")[0];
            if (SECURITY->exist_player(lower_case(who)))
                write_file(NEW_GEM_LOG, old[i] + "\n");
        }
    } else if (str == "dup") {
        for (i=0; i<sizeof(old); i++) {
            dup = 0;
            for (j=0; j<i; j++) {
                if (explode(old[j], " ")[0] == who) { /* Found a duplicate */
                    dup = 1;
                    break;
                }
            }
            if (!dup)
                write_file(NEW_GEM_LOG, old[i] + "\n");
        }
    }
        
    return 1;
}

public void
init()
{
    ::init();
    if (TP == ETO && TP->query_wiz_level()) {
        add_action(do_remove, "rem");
    }
}

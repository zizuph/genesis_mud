inherit "/std/object";

#include "/d/Rhovanion/defs.h"

#include <stdproperties.h>
#include <macros.h>

#define OBJ_I_CLEANED	"_obj_i_cleaned"

/* 
 * Global variables
 */
public string adj1;
public string adj2;
public string long;

/* 
 * Prototypes
 */
public int make_me_clean();
void
create_object() 
{
    adj1 = "crusted";
    adj2 = "dirty";
    long = "This is an odd stone indeed, especially considering " +
	"it was cut out from the stomach of a giant, constrictor " +
	"snake.  It is crusted over with all manner of filth and " +
	"goo.  It could use some cleaning.\n";

    set_name("stone");
    add_adj("@@set_my_adj1@@");
    add_adj("@@set_my_adj2@@");
    set_long("@@set_my_long");
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 350);
}

void
init()
{
   ::init();
   add_action("part_clean","clean");
}

int
part_clean(string str) 
{
    notify_fail("Clean what?\n");
    if (!str || str != "stone")
	return 0;

    if (query_prop(OBJ_I_CLEANED))
    {
	write("The stone is already clean.\n");
	return 1;
    }
   
    write("You clean the stone up the best you can.\n");
    say(QCTNAME(this_player()) + " cleans a stone.\n");
    make_me_clean();
    return 1;
}

public int
make_me_clean()
{
    adj1 = "spotted";
    adj2 = "black";
    long = "This uncommon stone is a " +
         "White Chloramite.  It is embedded with small round nodules of " +
         "black stone giving it a unique appearance.  If it were " +
         "cut it might be worth quite a bit of money to a collector.\n";
   
    TO->add_prop(OBJ_I_VALUE, 1500);
    return 1;
}

public string
set_my_adj1()
{
    return adj1;
}

public string
set_my_adj2()
{
    return adj2;
}

public string 
set_my_long()
{
    return long;
}

inherit "/std/corpse.c";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)     break_string(message,75)
#define TP              this_player
#define TO              this_object

void
create_corpse()
{
    object ob;
    
    set_name("thane");
    set_short("ancient corpse of a tall, dark elf");
    set_long(BS("This is the frozen corpse of a tall, handsome " 
    + "elf, obviously very ancient and kept from decaying only "
    + "by the bitter cold of an icy grave.\n"));
    seteuid(getuid(TO()));
    ob = clone_object("/d/Terel/cedric/thane/journal.c");
    ob->move(TO());
}

inherit "/std/object";
#include "/d/Kalad/defs.h"
#define THANAR_TALK "_thanar_talk"

/* Sarr */

object owner;
object con;
void set_owner(string str);
string query_owner();


void
set_owner(object ob)
{
    owner = ob;
    con = clone_object(CVAN(thanar/ap_con));
    con->set_thanar(TO);
    con->move(ob);
}

void
remove_con()
{
    con->remove_object();
}


object
query_owner()
{
    return owner;
}


void
create_object()
{
    set_name("thanar");
    add_name("apparition");
    set_adj("ghostly");
    add_adj("apparition");
    set_short("ghostly apparition of Thanar");
    set_long("You see a giant warrior about 8 feet tall covered "+
      "from head to toe in midnight-black armour. A flowing robe "+
      "of black surrounds him, and a platinum chain necklace with "+
      "the emblem of Thanar hangs off his neck. His whole body "+    
      "is transparant and ghost-like. Two red lights blaze with "+
      "a furious intensity from behind his black-steel visored helm.\n");
    add_prop(OBJ_M_NO_GET,"Are you mad?\n");
}

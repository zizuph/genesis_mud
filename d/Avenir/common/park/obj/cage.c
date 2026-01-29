// file name: cage.c
// creator(s): Ilyian (April, 1995)
// last update:
// purpose: Golden cage that holds get_faerie
// note: In the fountain that is guarded by creature. Faerie is for quest.
// bug(s):
// to-do:

inherit "/std/receptacle";

#include "/d/Avenir/common/common.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

static object faerie;

public void
create_container()
{
    set_name("_golden_cage_");
    add_name("cage");
    set_adj( ({ "tiny","golden","gold" }) );
    set_short("tiny golden cage");
    set_long("This miniature cage had bars made from some strong gold "
      +"alloy. It has a tiny door with a with silver lock.\n");

    set_key("Golden_Cage_Key");
    set_pick(70);

    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_WEIGHT, 900);          
    add_prop(CONT_I_VOLUME, 900);           
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(OBJ_I_VALUE, 1860);
    add_prop(OBJ_M_NO_GET, "The cage is firmly held in the arm of the "
              +"statue. Pity, because it would be quite valuable if "
              +"you could get it to a shop.\n");
    set_no_show_composite(1);

    seteuid(getuid());
}

public void
fill_cage()
{
       if(!present("astarte", TO))
   {
    add_prop(CONT_I_LOCK,0);
    add_prop(CONT_I_CLOSED,0);
    faerie =  clone_object(PK+"mon/astarte.c");
    faerie->move( this_object() );
    faerie->can_get();

    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);

    }
 }

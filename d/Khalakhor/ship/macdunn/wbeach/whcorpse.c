/* Carcass of a beached whale, from which whale blubber can be cut to
** make oil
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 5/15/98     Zima        Created
** 5/19/05     Cotillion   Fixed runtimes.
*/
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <wa_types.h>

#include "local.h"

int numslabs=20;
int query_numslabs() { return numslabs; }
void set_numslabs(int n) { numslabs=n; }
 
void create_object()
{
    set_name("carcass");
    add_name(({"whale","corpse",WH_CORPSE}));
    set_adj(({"small","rotting"}));
    set_short("carcass of a whale");
    set_pshort("carcasses of whales");
    set_long(
             "It is the rotting carcass of a small whale which the waves "+
             "have washed upon the shore. A large gash in its side suggests "+
             "something large has bitten into it, though the beaks of the gulls "+
             "may have made it larger. Inside the gash you see layers of oily "+
             "blubber which would have protected it from the cold waters.\n");
    add_item(({"fat","blubber"}),
        "The gash in the corpse of the whale reveals layers of thick "+
        "oily blubber. With a knife, you could probably cut some from the "+
        "carcass.\n");
    add_prop(OBJ_I_WEIGHT,1000000);
    add_prop(OBJ_I_VOLUME,1000000);
    add_prop(OBJ_I_VALUE,0);
}
 
int
do_cut(string parms)
{
    object* inv=all_inventory(TP);
    object  knife,slab,Tr=ENV(TP);
    string  sh=query_short(), bsh, ksh;

    
    if (!stringp(parms) || 
        !parse_command(parms,inv,
              "[slab] [hunk] [of] 'blubber' / 'fat' 'from' 'whale' / 'carcass' "+
            "/ 'corpse' 'with' %o",knife))
    {
        notify_fail("Cut what from what with what?\n");
        return 0;
    }
    
    if (!objectp(knife) || !knife->query_wt() == W_KNIFE)
    {
        write("You must use a knife of some kind to cut the blubber.\n");
        return 1;
    }
    
    if (numslabs <= 0)
    {
        write("There isn't enough blubber left to cut a good piece.\n");
        return 1;
    }
    
    numslabs--;
    seteuid(getuid());
    slab=clone_object(SR_OBJ+"blubber");
    bsh = (slab->query_short());
    ksh = (knife->query_name());
    write("You cut a "+bsh+" from the "+sh+" with the "+ksh+".\n");
    tell_room(Tr,QCTNAME(TP)+" cuts a "+bsh+" from the "+sh+
        " with "+LANG_ART(ksh)+" "+ksh+".\n",TP);
    if (slab->move(TP)) {
        tell_room(Tr,"The "+bsh+" falls onto the ground.\n");
        slab->move(Tr);
    }
    return 1;
}
 
void
init()
{
    ::init();
    add_action(do_cut, "cut");
}

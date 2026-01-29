inherit "/std/shadow";

#define SW shadow_who

#include <macros.h>

#include "../defs.h"

public void attacked_by(object ob)
{
 SW->catch_msg("You rush into combat , but fall since someone has "+
   "tied laces on your shoes!\n"+
   "You quickly untie them and hurry to fight!\n");
 say(QCTNAME(SW)+" rushes into combat , but falls with a loud scream!\n"+
   C(PRO(SW))+" quickly unties laces on "+POS(SW)+" shoes and continues "+
   "fighting.\n",({SW}));
 present("_trickster_tie_object_",SW)->remove_object();
 SW->attacked_by(ob);
 remove_shadow();
}

public void attack_object(object ob)
{
 SW->catch_msg("You rush into combat , but fall since someone has "+
   "tied laces on your shoes!\n"+
   "You quickly untie them and hurry to fight!\n");
 say(QCTNAME(SW)+" rushes into combat , but falls with a loud scream!\n"+
   C(PRO(SW))+" quickly unties laces on "+POS(SW)+" shoes and continues "+
   "fighting.\n",({SW}));
 present("_trickster_tie_object_",SW)->remove_object();
 SW->attack_object(ob);
 remove_shadow();
}

void remove_tie_shadow()
{
 remove_shadow();
}


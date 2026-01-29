/* Torqual
 */

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>     
#include <macros.h>       

#include "../../daenbraigh.h"
#include "../foraois_deanach.h"

// we inherit h_helm_base  (paths needed)

inherit FD_ARM + "h_helm_base.c";

#define ADJ ({"brown", "black", "blackened", "polished", "addorned"})
#define TYPE ({"leather", "hardened leather", "iron", "steel"})

public void
create_khalakhor_armour()
{
    string *adj=(ADJ), *mat=(TYPE);
    int i, i_mat;

    i_mat = random(sizeof(mat));

   // we choose adj based on material
    if ( i_mat < 2 )
    {
        i = random(2);
    }
    else 
    {
        i = 2 + random(3);
    }

    set_long("This helmet is made of " + mat[i_mat] + " and looks " +
             adj[i] + ".\n");
    create_helm(adj[i], mat[i_mat]);
}

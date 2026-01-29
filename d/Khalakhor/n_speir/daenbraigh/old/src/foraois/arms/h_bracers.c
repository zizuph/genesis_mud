/* random shirt based on common shirt
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

#define COLOUR ({"black","brown","red","blue"})
#define TYPE ({"leather","hardened leather"})

inherit "/d/Khalakhor/common/arm/bracers_base";

public void
create_khalakhor_armour()
{
    string *col=(COLOUR), *mat=(TYPE);

    // we choose colour and material randomly
    int i_col = random(sizeof(col));
    int i_mat = random(sizeof(mat));

    if ( mat[i_mat] == "leather" )
    {
        set_long("These soft " + col[i_col] + " leather bracers " +
            "are sturdily crafted and fit snugly on the forearm of the " +
            "wearer.\n");
    }
    else
    {
        set_long("These bracers have been crafted from " +
            "thick, dyed "+ col[i_col]+ ", and " + mat[i_mat] +
            ". They would serve " +
            "as fairly solid protection for your arms.\n");
    }
    create_bracers(mat[i_mat]);
}

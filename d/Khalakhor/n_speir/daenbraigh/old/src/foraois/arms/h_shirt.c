/* random shirt based on common shirt
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

#define COLOUR ({"grey","red","blue","white","green"})
#define TYPE ({"wool","leather","cloth"})

inherit "/d/Khalakhor/common/arm/shirt_base";

public void
create_armour()
{
    string *col=(COLOUR), *mat=(TYPE);

    // we choose colour and material randomly
    int i_col = random(sizeof(col));
    int i_mat = random(sizeof(mat));

    set_long("The pullover shirt is made from a " + col[i_col] +
        " " + mat[i_mat] + ". Loose-fitting, it's " +
        "warm and comfortable.\n");

    create_shirt(col[i_col], mat[i_mat]);

}

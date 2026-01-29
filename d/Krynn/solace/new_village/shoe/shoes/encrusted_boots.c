/* 
 * Louie 2005
 * Designed by Anahita
 */

inherit "/std/armour";

#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define shoe_adjs ({"ruby","diamond","emerald","sapphire","onyx"})
public void
create_armour()
{
    string adj = ONE_OF(shoe_adjs);

    set_name("boots");
    set_pname("boots");
    add_name("armour");
    add_pname("armours");

    set_adj(({"encrusted",adj,"doeskin"}));
    add_adj(({adj+"-encrusted","gem-encrusted"}));
    add_name(({"pair of boots","pair of "+adj+"-encrusted boots"}));
    add_pname(({"pairs of boots","pairs of "+adj+"-encrusted boots"}));
    set_short("pair of "+adj+"-encrusted boots");
    set_pshort("pairs of "+adj+"-encrusted boots");
    set_ac(30);
    set_at(A_FEET);
    set_long("Tiny "+
        "precious gems adorn these doeskin boots, providing surprisingly "+
        "strong protection in combat and from the elements.  You may find "+
        "find that wearing these boots will make you very popular with "+
        "brigands, rogues, assassins, and greedy characters of all types.  "+
        "\n");

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(30, A_HEAD));
    //mega expensive
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30) * 4);
}

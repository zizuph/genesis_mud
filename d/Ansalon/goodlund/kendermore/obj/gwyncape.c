/* Kender cape by Gwyneth, 05/17/99 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define adjecs query_adjs()
#define SUBLOC_MISCEXTRADESC "_subloc_misc_extra"

string *adjs=({"blue", "red", "green", "yellow", "orange", "purple"});
string *type=({"flowing", "sparkly", "flashy", "bright"});
int worn;

void
create_armour()
{
    set_name(({"cape","_clothes_"}));
    add_name("clothes");
    set_adj(type[random(4)]);
    add_adj(adjs[random(6)]);
    set_long("It's a warm and " + adjecs[0] + " cape, commonly worn by kender. " + 
        "The cloth " + 
        "is a beautiful " + adjecs[1] + " colour. It looks perfect for travel " + 
        "or show!\n"); 
    set_ac(5);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE, 120);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 300);
    add_cmd_item("cape", "twirl", "@@twirl_cape");
    set_af(TO);
    seteuid(getuid(TO));

    worn = 0;
}

/* Function name : Wear
 * Description : Gives an emote to room and wearer when worn.
 * Returns : 1 or 0
*/

mixed
wear(object what)
{
    if (what != TO)
       return 0;

    write("You throw your " + adjecs[0] + " " + adjecs[1] + " cape " + 
       "over your shoulders with a flourish.\n");
    say(QCTNAME(TP) + " gracefully " + 
       "throws " + HIS(TP) + " " + adjecs[0] + " " + adjecs[1] + " cape " + 
       "over " + HIS(TP) + " shoulders with a flourish.\n");
    TP->remove_subloc(SUBLOC_MISCEXTRADESC);

    worn = 1;
    return 1;
}

/* Function name : Remove
 * Description : Gives an emote to room and wearer when item is removed.
 * Returns : 1 or 0
*/

mixed
remove(object what)
{
    if (what != TO || !TP)
      return 0;

    write("You remove your " + adjecs[1] + " " + adjecs[2] + " cape from " + 
      "around your shoulders with a fancy twirl.\n");
    say(QCTNAME(TP) + " removes " + HIS(TP) + " " + adjecs[1] + " cape " + 
      "from around " + HIS(TP) + " shoulders with a fancy twirl.\n");
    worn = 0;
    return 1;
}


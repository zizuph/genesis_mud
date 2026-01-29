// file name:        /d/Avenir/common/dark/obj/hook_shield.c
// creator(s):       Denis
// revision history: Denis, Aug'99: Fixed WEIGHT property.
// purpose:          nasty weapon of nasty monsters.
// note:
// bug(s):
// to-do: 

inherit "/std/weapon";
#include <stdproperties.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("shield");
    set_short("sharp shield");
    set_adj("sharp");
    set_long(
     "It is a small shield crafted by an orcish or ogrish blacksmith "+
     "from dark iron. It has more use as a weapon than a shield though "+
     "because of its sharp edges and a hook in the middle. "+
     "This weapon is difficult to use, but it leaves "+
     "deadly injuries on its foes.\n");

    add_item("hook","You can see blood on it. Blood if its foes.\n");
    add_item("blood","It makes your enemies feel sick.\n");
    add_item(({"edge","sharp edge","edges","sharp edges"}),
     "You better not touch the edges of the shield.\n");

    set_hit(15);
    set_pen(30);

    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_BLUDGEON);

    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, (F_VALUE_WEAPON(15,35)) + random(100));
    add_prop(OBJ_I_WEIGHT, 2*F_WEIGHT_DEFAULT_WEAPON(35,W_SWORD)+random(50)-25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_M_NO_BUY,1);
}

int query_procuse()
{
    return 30;
}

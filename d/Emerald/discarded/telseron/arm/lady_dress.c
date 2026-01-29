inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <formulas.h>
#include "/d/Emerald/defs.h"

string *mydescrs;
mixed typefun();

string base, lining;

void set_type(string str, string str2)
{
	base = str; lining = str2;
}

void init_my_armour()
{
    if(!base)
      {
	mixed mystuff = typefun();
	base = mystuff[0];
	lining = mystuff[1];
      }
    add_adj(lining + "-lined");
    add_adj(base);
    set_long("This beautiful dress is made of a very fine deep " + base +
	" silk fabric. It is lined with a finely threaded " + lining +
	" material, and has a modest-sized light-" + base + " train "+
	"trailing from the back of it. It looks to be a rather fancy "+
	"dress for a woman, and it seems especially striking on elvish "+
	"maidens.\n");
    set_ac(4);
    set_am( ({-2, -1, 1}) );
    set_at(A_BODY|A_LEGS);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(4) + 300);
    return;
}

void
create_armour()
{
    init_my_armour();
    set_name("dress");
}

mixed typefun()
{
    string str;

    switch(random(9))
      {
      case 0: return ({ "blue", "silver" }); break;
      case 1: return ({ "green", "gold" }); break;
      case 2: return ({ "gold", "yellow" }); break;
      case 3: return ({ "blue", "red" }); break;
      case 4: return ({ "white", "silver" }); break;
      case 5: return ({ "grey", "silver" }); break;
      case 6: return ({ "red", "silver" }); break;
      case 7: return ({ "green", "silver" }); break;
      case 8: return ({ "green", "burgundy" }); break;
      }
}

void
init_recover(string arg)
{
    string *a = explode(arg, "&&");
    set_type(a[1], a[2]);
    init_my_armour();
    ::init_recover(arg);
    return;
}

string
query_recover()
{
    return ::query_recover() + "&&" + base + "&&" + lining;
}

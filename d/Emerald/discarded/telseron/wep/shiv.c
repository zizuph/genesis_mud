inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Emerald/defs.h"

mixed *mymods;
string type;
int my_moda, my_modb;
mixed typefun();

void set_type(string str, int num1, int num2)
{
	type = str;
	my_moda = num1;
	my_modb = num2;
}

void init_my_weapon()
{
    if(!type)
      {
	mixed mystuff = typefun();
	type = mystuff[0];
	my_moda = mystuff[1];
	my_modb = mystuff[2];
      }
    set_short(type + " shiv");
    add_adj(type);
    set_long("The " + type + " shiv seems to be a light weapon that is "+
	"made from a common kitchen spoon where the handle is sharpened "+
	"to a nasty point.\n");
    set_hit(5 + my_moda);
    set_pen(5 + my_modb);
    return;
}

void
create_weapon()
{
    init_my_weapon();
    set_name("shiv");
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
}

mixed typefun()
{
    string str;

    switch(random(7))
      {
      case 0: return ({"long", 1, 2}); break;
      case 1: return ({"rough", 0, 1}); break;
      case 2: return ({"sharp", 1, 3}); break;
      case 3: return ({"wide", 2, 2}); break;
      case 4: return ({"dull", 1, 0}); break;
      case 5: return ({"small", 1, 1}); break;
      case 6: return ({"thin", 3, 0}); break;
      }
}

void
init_recover(string arg)
{
    string *a = explode(arg, "&&");
    set_type(a[1], atoi(a[2]), atoi(a[3]));
    init_my_weapon();
    ::init_recover(arg);
    return;
}

string
query_recover()
{
    return ::query_recover() + "&&" + type + "&&" + my_moda + "&&" + my_modb;
}

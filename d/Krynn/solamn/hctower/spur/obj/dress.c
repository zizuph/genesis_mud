// grace
// 09 Feb 1995
// willa's tray
inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

string randnom();
string randadj();

void
create_armour()
{
    string adj, name;
    set_ac(10);
    set_at(A_TORSO);

    adj = randadj();
    name = randnom();

    set_name(name);
    set_adj(adj);
    set_short(adj + " " + name);
    
    add_name(({"armour", "clothes", "dress", "robe", "apron"}));
    set_long("Simple clothing for simple folk. It looks like something "
        + "you might see on a serving girl or peasant woman.\n");
}


string
randadj()
{
   string *randadj;
   randadj = ({"clean", "pretty", "colourful", "slightly shabby", 
      "embroidered", "white", "blue", "brown"});
   return randadj[random(sizeof(randadj))];
}

string
randnom()
{
   string *randnom;
   randnom = ({"apron", "dress", "shift", "uniform", "tunic"});
   return randnom[random(sizeof(randnom))];
}



/* 	
    Helm with short straight horns, for the weak krougs 

    coder(s):   Maniac

    22/3/96        plural short currected  Maniac
    20/2/96         Created                Maniac

*/

#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

string *colours = ({ "blue", "red", "green", "black", "purple",
                     "white", "silver", "golden", "orange" });
string my_colour;

void
set_up_desc(string c) 
{
    if (stringp(my_colour))
        remove_adj(my_colour);

    my_colour = c;
    add_adj(my_colour);

    set_short("helm with two short straight " + my_colour + " horns");
    set_pshort("helms with two short straight " + my_colour + " horns");

    set_long("A steel helm with two short, straight " + my_colour + 
          " horns sticking out " +   
         "of the top.\n(Reference: horned, short-horned, " +
         "straight-horned.)\n");
}

void
create_armour()
{
    string c;

    set_name("helmet");
    add_name("helm");
    set_adj(({"horned", "short-horned", "straight-horned"}));

    c = colours[random(sizeof(colours))];

    set_up_desc(c);

    set_ac(18);
    set_at(A_HEAD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 2600);
    add_prop(OBJ_I_VOLUME, 2600);
}


string
query_recover()
{
  string rec;
  rec = MASTER + ":";
  rec += "#a#";
  rec += my_colour;
  rec += "#myend";
  rec += query_arm_recover();
  return rec;
}


void
init_recover(string arg)
{
  string foobar, c;

  sscanf(arg, "%s#a#%s#myend%s",
                foobar, c, foobar);
  set_up_desc(c);
  init_arm_recover(arg);
}


/* 
 * Holiday globe of village
 * -- Finwe, nov 2001
 */
  
inherit "/std/object";
inherit "/lib/keep";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>

int shaken = 0; // not shaken
string globe_status(int stage);


void
create_object()
{
    set_name("globe");
    set_adj("crystal");
    set_short("crystal globe");
    set_long("This is "+short()+" full of water. It is a unique item " +
		"fashioned by skilled dwarven hands. An exquistely carved and " +
		"painted miniature village sits on a small platform inside the " +
		"globe. Small, mysterious polished bits of something float " +
		"around the water like swirling snowflakes.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 400);

    set_keep(1);
}

init()
{   
    ::init();
    add_action("shake_globe", "shake");
}

int shake_globe(string str)
{
    write("You shake the globe vigorously, sending mysterious polished " +
		"bits swirling everywhere inside the globe.\n");
    say(QCTNAME(TP)+" shakes a "+short()+" vigorously.\n");
    shaken=1;
    set_alarm(1.0,0.0, &globe_status(0));
    return 1;
    

}

string globe_status(int stage)
{
    string full_msg;

    switch (stage)
    {
        case 0:
            write("The mysterious polished bits swirl about the globe " +
				"quickly like a snowstorm inside the globe.\n");
            set_alarm(10.0, 0.0, &globe_status(++stage));
            shaken = 1;

            break;  
        case 1:
            write("The mysterious polished bits begin to slow down, " +
				"falling gently upon the village in the globe.\n");
            set_alarm(7.0, 0.0, &globe_status(++stage));
            shaken = 1;

            break;
        case 2:
            write("The mysterious polished bits lay all over the village, " +
				"like a blanket of fresh snow.\n");
            shaken = 0;
            break;
     }
}
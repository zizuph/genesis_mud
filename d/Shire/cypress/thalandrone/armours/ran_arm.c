/*
 * Generic armours, such as chainmails and platemails,
 * found on hidden corpses. 
 * They are very low powered and provide no magical
 * abilities, despite the descriptions.
 * -- Finwe, July 2001
 */
#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Shire/cypress/sys/defs.h"

#define MAX_ARMOURS 4
#define ARMOUR_CLASS 12

int num;

void
make_armour(int arg)
{
    int i;
    string *names;

    if((arg < 0) || (arg > 3)) return;

    names = TO->query_names();
    for (i=0; i<sizeof(names); i++)
    {
	TO->remove_name(names[i]);
    }
    TO->add_name("armour");

    num = arg;
    switch(arg)
    {

        case 0:
            set_name("chainmail");
            add_name("mail");
            set_adj("iron");
            set_short("iron chainmail");
            set_pshort("iron chainmails");
            set_long("This mail is worn and rusted. It is made " +
                "of iron and looks strong. It is made of multiple, " +
                "interlocking rings that provide some protection. " +
                "Some of the rings are rusted through and look " +
                "weak.\n");
            set_am( ({ -3, 0, 3 }) );
    	break;
    
        case 1:
            set_name("breastplate");
            add_name("leather breastplate");
            set_adj(({"leather", "hardened"}));
            set_short("hardened leather breastplate");
            set_pshort("hardened leather breastplates");
            set_long("This "+short()+" is worn with some " +
                "holes through it where animals have chewed on " +
                "it. It is made of hardened leather and protects " +
                "the torso. The leather is not as durable as it " +
                "use to be, but probably still offers some "+
                "protection.\n");
            set_am( ({ -3, 0, 3 }) );

	    break;

        case 2:
    	    set_name(({"steel platemail", "platemail"}));
    	    set_adj(({"rusted", "dull"}));
        	set_short("dull rusted platemail");
	        set_pshort("dull rusted platemails");
            set_long("The "+short()+" is made of steel. It is " +
            "made of plates of steel that have been fused " +
            "together. It was probably a great piece of armour " +
            "at one time, as told by the faint intricate " +
            "engravings on its front, but now it looks pretty " +
            "dingy and not of much use.\n");
            set_am( ({ -3, 0, 3 }) );
            add_item(({"engravings", "faint engravings",
                    "intricate engravings", "faint intricate engravings"}),
                "The faint intricate engravings have been " +
                "smoothed away by time. However, they reveal "+
                "stylized designs that probably made this a "+
                "truly great piece of armour. Nonetheless, as "+
                "you move the armour, the engravings change " +
                "colors from blood red to the darkest black.\n");
    	break;

        case 3:
    	    set_name(({"rusty scale mail", "scale mail", 
                "scalemail"}));
    	    set_adj(({"rusty", "dull"}));
        	set_short("dull rusty scale mail");
	        set_pshort("dull rusty scale mails");
            set_long("The "+short()+" is made of steel. It is " +
            "made of overlapping plates of steel. It looks pretty " +
            "rusty and not of much use.\n");
            set_am( ({ -3, 0, 3 }) );
    	break;

    }
    
}

void
create_armour()
{
    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    num = random(MAX_ARMOURS);
    make_armour(num);
    set_keep();
}

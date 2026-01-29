/*
 * Generic weapons found on hidden corpses. 
 * They are very low powered and provide no magical
 * abilities, despite the descriptions.
 * -- Finwe, July 2001
 */
#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Shire/cypress/sys/defs.h"

#define MAX_WEAPONS 4

int num;

void
make_weapon(int arg)
{
    int i;
    string *names;

    if((arg < 0) || (arg > 3)) return;

    names = TO->query_names();
    for (i=0; i<sizeof(names); i++)
    {
	TO->remove_name(names[i]);
    }
    TO->add_name("weapon");

    num = arg;
    switch(arg)
    {

        case 0:
    	    set_name(({"axe", "battleaxe"}));
    	    set_adj(({"rusty","iron"}));
        	set_short("rusty iron battleaxe");
	        set_pshort("rusty iron battleaxes");
        	set_dt(W_SLASH | W_BLUDGEON);
	        set_hands(W_ANYH);
            set_long("This "+short()+" was once a terrible " +
                "weapon. It's double blades are chipped but " +
                "still sharp. The handle is made of steel. Its " +
                "rusted, but still looks dangerous.\n");
            set_wt(W_AXE);
    	break;
    
        case 1:
        	set_name(({"longsword", "sword"}));
	        set_adj(({"dull"}));
        	set_short("dull longsword");
	        set_pshort("dull longswords");
    	    set_dt(W_SLASH | W_IMPALE);
    	    set_hands(W_ANYH);
            set_long("Once a great weapon, this "+short()+" is " +
                "pocked with rust looking. Its once sharp edge " +
                "is dull now, but could probably still inflict " +
                "some damage. Faint etchings are inscribed onto " +
                "the blade.\n");
            add_item(({"etchings", "faint etchings"}),
                "The etchings are stylized patterns that run " +
                "across the length of the blade. They are dull " +
                "with age There appear to be runes entwined " +
                "with the etchings.\n");
            add_item(({"runes"}),
                "They are etched onto the blade. Faded, they " +
                "are still blood red but are undecipherable. " +
                "They probably once provided dark magic to the " +
                "owner of the blade.\n");
            set_wt(W_SWORD);

	    break;

        case 2:
    	    set_name(({"staff"}));
    	    set_adj(({"deadly"}));
        	set_short("long deadly staff");
	        set_pshort("long deadly stafves");
        	set_dt(W_IMPALE);
        	set_hands(W_BOTH);
            set_long("The "+short()+" is a long rod of metal. It is rounded on both edges and probably dangerous in the right hands. The surface is fairly clean, despite its age.\n");
            set_wt(W_POLEARM);
    	break;

        case 3:
    	    set_name(({"mace"}));
    	    set_adj(({"deadly"}));
        	set_short("deadly mace");
	        set_pshort("deadly maces");
        	set_dt(W_SLASH | W_BLUDGEON);
	        set_hands(W_ANYH);
            set_long("This deadly mace is a terrible looking " +
                "weapon. It is a staff with a multi pointed " +
                "ball on top. Rust is in patches across the " +
                "stout steel handle and some of the points are " +
                "broken or dull looking. Still, this looks like " +
                "a dangerous weapon in the right hand.\n");
            add_item(({"ball", "multi pointed ball"}),
                "The ball is firmly attached to the handle. It " +
                "is black and covered with many sharp points. " +
                "Some of the points are broken off or bent, " +
                "thus decreasing it effectiveness.\n");
            add_item(({"handle"}),
                "The handle of the "+short()+" is made of steel " +
                "and dull looking. Is is covered with rust. A " +
                "multi pointed ball is attached to the top.\n");
            set_wt(W_CLUB);
    	break;

    }
    
}

void
create_weapon()
{
    int pen = 12;
    int hit = random(5)+7;

    set_pen(pen);
    set_hit(hit);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen) * (90+random(21)) / 100);

    num = random(MAX_WEAPONS);
    make_weapon(num);

    set_keep();
}

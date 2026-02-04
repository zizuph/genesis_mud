#include <ss_types.h>

#define WEAPONS  ({SS_WEP_SWORD, SS_WEP_POLEARM, SS_WEP_AXE,\
		   SS_WEP_KNIFE, SS_WEP_CLUB, SS_WEP_MISSILE,\
		   SS_WEP_JAVELIN})
#define SPELLS   ({SS_SPELLCRAFT, SS_HERBALISM, SS_ALCHEMY})
#define FORMS    ({SS_FORM_TRANSMUTATION, SS_FORM_ILLUSION,\
		   SS_FORM_DIVINATION, SS_FORM_ENCHANTMENT,\
		   SS_FORM_CONJURATION, SS_FORM_ABJURATION})
#define ELEMENTS ({SS_ELEMENT_FIRE, SS_ELEMENT_AIR, SS_ELEMENT_EARTH,\
		   SS_ELEMENT_WATER, SS_ELEMENT_LIFE, SS_ELEMENT_DEATH})

void set_ss_skill(string type, int *val);

void
set_ss_skill(string type, int *val)
{
    int i, imax;
    int *tmp;

    switch (type) {
	case "WEP":
	    tmp = WEAPONS;
	    break;
	case "SPELL":
	    tmp = SPELLS;
	    break;
	case "FORM":
	    tmp = FORMS;
	    break;
	case "ELEMENT":
	    tmp = ELEMENTS;
	    break;
	default:
	    return;
    }
    imax = sizeof(tmp);
    if (sizeof(val) < imax) imax = sizeof(val);
    for (i=0; i<imax; i++)
	this_object() -> set_skill(tmp[i], val[i]);
}

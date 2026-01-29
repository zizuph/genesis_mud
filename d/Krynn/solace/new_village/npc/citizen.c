/*
 * A Solace citizen
 *
 * by Rastlin
 */
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <const.h>

inherit M_FILE

public string
get_name(int i)
{
    switch(i)
    {
        case 2:
            set_gender(G_MALE);
            return "boy";
	    break;
	case 1:
	    set_gender(G_FEMALE);
	    return "girl";
	    break;
	case 3:
	    set_gender(G_FEMALE);
	    return "woman";
	    break;
	case 0:
	    set_gender(random(2));
	    return "kid";
	    break;
	case 4:
	    set_gender(G_MALE);
	    return "man";
	    break;
    }
}

public string
get_short(int i)
{
    switch(i)
    {
        case 2:
            set_adj("young");
            return "young boy";
	    break;
	case 1:
	    set_adj("young");
	    return "young girl";
	    break;
	case 3:
	    set_adj("beautiful");
	    set_pshort("beautiful women");
	    return "beautiful woman";
	    break;
	case 0:
	    set_adj("happy");
	    return "happy kid";
	    break;
	case 4:
	    set_adj("old");
	    set_pshort("old men");
	    return "old man";
	    break;
    }
}

public string
get_long(int i)
{
    switch(i)
    {
        case 2:
            return "He is playing with some straws, well you know children.\n";
	    break;
	case 1:
       return "She looks weak for her age.\n";
	    break;
	case 3:
	    return "It looks like she thinks she is beautiful.\n";
	    break;
	case 0:
	    return "The kid is playing with a pair of sticks.\n";
	    break;
	case 4:
	    return "The old man looks back at you.\n";
	    break;
    }
}

create_krynn_monster()
{
    int i, type;

    type = random(5);

    set_name(get_name(type));
    set_short(get_short(type));
    set_long(get_long(type));

    for (i = 0; i < 6; i++)
        set_base_stat(i, type * 3 + random(10));

    set_all_attack_unarmed(10, 8);
    set_all_hitloc_unarmed(2);

    set_knight_prestige(-2);
    set_alignment(100 + random(100));

    set_random_move(2);

}

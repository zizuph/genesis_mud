inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>

void
create_poison()
{
    int i, num = (random(2) + 1) * 2;
    int *types = ({ POISON_HP, POISON_MANA, POISON_FATIGUE, POISON_STAT });
    int *arr = allocate(num);

    for (i = 0; i < num; i += 2)
    {
        arr[i] = types[random(sizeof(types))];
        
        switch (arr[i])
	{
  	    case POISON_HP:
	        arr[i + 1] = 80 + random(80);
                break;
            case POISON_MANA:
	        arr[i + 1] = 60 + random(60);
                break;
	    case POISON_FATIGUE:
	        arr[i + 1] = 40 + random(40);
                break;
	    case POISON_STAT:
	        arr[i + 1] = ({ SS_STR, SS_DEX, SS_CON })[random(3)];
                break;
	}
    }

    set_interval(random(30) + 20);
    set_time(random(500) + 200);
    set_strength(80);
    set_poison_type("reaver");
    set_damage(arr);
}


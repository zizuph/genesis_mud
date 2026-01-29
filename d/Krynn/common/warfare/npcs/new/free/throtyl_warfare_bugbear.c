
/* 
 * A Throtyl bugbear of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/std_warfare_throtyl";

int level;
int sublevel = 2; // bugbear

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..1:
            level = 0; // 20% 'scarred' (112 stat average)
        break;
        case 2..6:
            level = 1; // 50% 'cunning' (125 stat average) 
        break;
        default:
            level = 2; // 30% 'brutal' (140 stat average)
        break;
    }

    return level;
}

public void
create_throtyl_soldier()
{
    set_throtyl_level(random_soldier_type(), sublevel, "throtyl");
}
 

/* 
 * A neidar trailblazer of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/neidar_base";

int level;
int sublevel = 1; // trailblazer

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..5:
            level = 0; // 60% 'scarred' (112 stat average)
        break;
        case 6..8:
            level = 1; // 30% 'experienced' (125 stat average) 
        break;
        default:
            level = 2; // 10% 'veteran' (140 stat average)
        break;
    }

    return level;
}

public void
create_neidar_soldier()
{
    set_neidar_level(random_soldier_type(), sublevel, "neidar");
}
 
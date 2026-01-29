
/* 
 * A knight archer of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/knight_base";

int level;
int sublevel = 5; // auxillary

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..5:
            level = 0; // 60% 'gallant' (112 stat average)
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
create_knight_soldier()
{
    set_knight_level(random_soldier_type(), sublevel, "crown");
}
 

/* 
 * A peasant rebel pikeman of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/std_warfare_rebel";

int level;
int sublevel = 1; // pikeman

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..3:
            level = 0; // 40% 'scarred' (112 stat average)
        break;
        case 4..6:
            level = 1; // 30% 'experienced' (125 stat average) 
        break;
        default:
            level = 2; // 30% 'veteran' (140 stat average)
        break;
    }

    return level;
}

public void
create_rebel_soldier()
{
    set_rebel_level(random_soldier_type(), sublevel, "rebel");
}
 
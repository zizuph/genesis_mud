
/* 
 * A red dragonarmy bozak of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/std_warfare_bozak";

int level;
int sublevel = 2; // bozak

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..1:
            level = 0; // 60% 'scarred' (112 stat average)
        break;
        case 2..6:
            level = 1; // 30% 'experienced' (125 stat average) 
        break;
        default:
            level = 2; // 10% 'veteran' (140 stat average)
        break;
    }

    return level;
}

public void
create_dragonarmy_soldier()
{
    set_dragonarmy_level(random_soldier_type(), sublevel, "blue");
}
 
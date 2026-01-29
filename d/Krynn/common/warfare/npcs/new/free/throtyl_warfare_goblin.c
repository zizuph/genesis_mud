
/* 
 * A Throtyl goblin archer of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/std_warfare_throtyl";

int level;
int sublevel = 0; // goblin

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..4:
            level = 0; // 50% 'scarred' (112 stat average)
        break;
        case 5..7:
            level = 1; // 30% 'cunning' (125 stat average) 
        break;
        default:
            level = 2; // 20% 'brutal' (140 stat average)
        break;
    }

    return level;
}

public void
create_throtyl_soldier()
{
    set_throtyl_level(random_soldier_type(), sublevel, "throtyl");
}
 